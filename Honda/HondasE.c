#include "TStyle.h"

void SetStyle(){
	gStyle->SetFillColor(0);
	gStyle->SetFrameLineWidth(1);
	gStyle->SetPadLeftMargin(0.105);
	gStyle->SetPadRightMargin(0.007);
	gStyle->SetPadTopMargin(0.005);		
	gStyle->SetPadBottomMargin(0.05);
	gStyle->SetTitleOffset(1.45,"Y");
	gStyle->SetTitleOffset(0.7,"X");
//	gStyle->SetTextFont(132);
}

void HondasE(){
	
	const int chf=2,cht=2,che=101,cha=7;
	const char nsp[5]="H11x",*nex="../../fortran/Output/spectra/";
	const char f[chf]={'e','m'},t[cht]={'n','a'},fn[chf][5]={"e","#mu"},tn[cht][8]={"#nu","#bar#nu"};
	char *name,cn[256];
	FILE *f140=0;
	double sp[chf][cht][che][cha];
	const int col[cha-1]={4,2,1,40,6,38},sh[cha-1]={1,5,3,7,6,9},w[cha-1]={1,2,2,2,2,1};//col[cha-1]={40,2,1,48,9,6,8,38,42,4},sh[cha-1]={2,5,3,7,8,9,4,1,6,10},w[cha-1]={2,2,2,2,2,1,2,1,2,1};//9,11,28,30,38,40,42,43,46
	int e,a,nf,nt,n,ndr;
	
	TCanvas c("c","Canvas",600,800);
	TGraph grsp[chf][cht][cha-1];
	
	SetStyle();

	for(nf=0; nf<chf; nf++){
		for(nt=0; nt<cht; nt++){
			sprintf(cn,"%s%ssp%c%c6.dat",nex,nsp,f[nf],t[nt]);
			f140=fopen(cn,"r");
			for(e=0; e<che; e++){
				for(a=0; a<cha; a++){
					fscanf(f140,"%le",&(sp[nf][nt][e][a]));
				}
			}
			fclose(f140);
		}
	}

	for(ndr=0; ndr<2; ndr++){
		for(nf=0; nf<chf; nf++){
			for(nt=0; nt<cht; nt++){
				c.cd();
				for(a=1; a<cha; a++){
					for(e=1; e<che; e++){
						grsp[nf][nt][a-1].SetPoint(e-1,sp[nf][nt][e][0],sp[nf][nt][e][a]);
					}
				}
				grsp[nf][nt][0].GetXaxis()->SetTitle("#font[132]{E_{#nu} (GeV)}");
				grsp[nf][nt][0].GetXaxis()->SetRangeUser(1e-1,5e0);
				grsp[nf][nt][0].GetYaxis()->SetTitle("#font[132]{E_{#nu}^{3} #Phi_{#nu}(E_{#nu},#theta) (GeV^{2} s^{-1} sr^{-1} cm^{-2})}");
				if(!nf){
					grsp[nf][nt][0].GetYaxis()->SetRangeUser(2e-4,3e-2);
					}
					else{
						grsp[nf][nt][0].GetYaxis()->SetRangeUser(4e-4,4e-2);
					}
				//grsp[nf][nt][0].GetYaxis()->SetRangeUser(2e-4,7e-2);
				grsp[nf][nt][0].Draw("AC");
				for(a=1; a<cha; a++){
					grsp[nf][nt][a-1].SetLineColor(col[a-1]);
					grsp[nf][nt][a-1].SetLineStyle(sh[a-1]);
					grsp[nf][nt][a-1].SetLineWidth(w[a-1]);
					grsp[nf][nt][a-1].Draw("CSAME");
				}
				TLegend* leg1=new TLegend(0.48,0.13,0.58,0.33);
				TLegend* leg2=new TLegend(0.58,0.13,0.68,0.28);
				leg1->AddEntry((TObject*)0,"#font[132]{cos#theta:}","");
				for(a=cha/2+1; a<cha; a++){
					leg1->AddEntry(&grsp[nf][nt][a-1],Form("#font[132]{%5.2f}",sp[nf][nt][0][a]),"L");
				}
				for(a=cha/2; a>0; a--){
					leg2->AddEntry(&grsp[nf][nt][a-1],Form("#font[132]{%5.2f}",sp[nf][nt][0][a]),"L");
				}
				leg1->SetBorderSize(0);
				leg1->Draw();
				leg2->SetBorderSize(0);
				leg2->Draw();
				if(!nt){
					if(!nf){
						TLegend* legname=new TLegend(0.15,0.8,0.25,0.9);
						}
						else{
							TLegend* legname=new TLegend(0.15,0.805,0.25,0.89);
						}
					}
					else{
						if(!nf){
							TLegend* legname=new TLegend(0.15,0.825,0.25,0.895);
							}
							else{
								TLegend* legname=new TLegend(0.15,0.82,0.25,0.89);
							}
					}
				legname->AddEntry((TObject*)0,Form("#font[132]{%s_{%s}}",tn[nt],fn[nf]),"");
				legname->SetBorderSize(0);
				legname->Draw();
				c.SetLogx();
				c.SetLogy();
				sprintf(cn,"../pictures/spectra/H11x%c%c6E-1+0.5.eps",f[nf],t[nt]);
				c.Print((const char*)cn);
				delete leg1;
				delete leg2;
				delete legname;
			}
		}
	}
}
