#include "TStyle.h"

void SetStyle(){
	gStyle->SetFillColor(0);
	gStyle->SetFrameLineWidth(1);
//	gStyle->SetPadLeftMargin(0.075);
	gStyle->SetPadRightMargin(0.007);
	gStyle->SetPadTopMargin(0.005);		
	gStyle->SetPadBottomMargin(0.08);
//	gStyle->SetTitleOffset(1.05,"Y");
	gStyle->SetTitleOffset(1.15,"X");
//	gStyle->SetTextFont(132);
}

void HondapE(){
	
	const int chf=2,cht=2,che=101,cha=14;
	const char nsp[5]="H11x",*nex="../../fortran/Output/spectra/";
	const char f[chf]={'e','m'},t[cht]={'n','a'},fn[chf][5]={"e","#mu"},tn[cht][8]={"#nu","#bar#nu"};
	char *name,cn[256];
	FILE *f140=0;
	double sp[chf][cht][che][cha];
	const int col[cha-1]={40,2,4,6,8,46,1,46,8,6,4,2,40};//9,11,28,30,38,40,42,43,46
	int e,a,nf,nt,n,ndr;
	
	TCanvas c("c","Canvas",1200,800);
	TGraph grsp[chf][cht][cha-1];
	
	SetStyle();

	for(nf=0; nf<chf; nf++){
		for(nt=0; nt<cht; nt++){
			sprintf(cn,"%s%ssp%c%c.dat",nex,nsp,f[nf],t[nt]);
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
				grsp[nf][nt][0].GetXaxis()->SetRangeUser(1e-1,1.5e10);
				grsp[nf][nt][0].GetYaxis()->SetTitle("#font[132]{E_{#nu}^{3} #Phi_{#nu}(E_{#nu},#theta) (GeV^{2} s^{-1} sr^{-1} cm^{-2})}");
				grsp[nf][nt][0].GetYaxis()->SetTitleOffset(1.05);
				gStyle->SetPadLeftMargin(0.075);
				//if(!nf){
					//grsp[nf][nt][0].GetYaxis()->SetRangeUser(2e-4,3e-2);
					//}
					//else{
						//grsp[nf][nt][0].GetYaxis()->SetRangeUser(4e-4,7e-2);
					//}
				//grsp[nf][nt][0].GetYaxis()->SetRangeUser(2e-4,7e-2);
				grsp[nf][nt][0].GetYaxis()->SetRangeUser(1e-10,2e-1);
				grsp[nf][nt][0].Draw("AC");
				for(a=cha/2-1; a>0; a--){
					grsp[nf][nt][a-1].SetLineStyle(3);
				}
				for(a=cha/2; a<cha; a++){
					grsp[nf][nt][a-1].SetLineStyle(1);
				}
				for(a=1; a<cha; a++){
					grsp[nf][nt][a-1].SetLineColor(col[a-1]);
					grsp[nf][nt][a-1].Draw("CSAME");
				}
				TLegend* leg1=new TLegend(0.28,0.13,0.38,0.53);
				TLegend* leg2=new TLegend(0.38,0.13,0.48,0.53);
				leg1->AddEntry((TObject*)0,"#font[132]{cos#theta:}","");	
				for(a=cha/2-1; a>0; a--){
					leg1->AddEntry(&grsp[nf][nt][a-1],Form("#font[132]{%5.2f}",sp[nf][nt][0][a]),"L");
				}
				for(a=cha/2; a<cha; a++){
					leg2->AddEntry(&grsp[nf][nt][a-1],Form("#font[132]{%5.2f}",sp[nf][nt][0][a]),"L");
				}
				leg1->SetBorderSize(0);
				leg1->Draw();
				leg2->SetBorderSize(0);
				leg2->Draw();
				//if(!nt){
					//if(!nf){
						//TLegend* legname=new TLegend(0.15,0.8,0.25,0.9);
						//}
						//else{
							//TLegend* legname=new TLegend(0.15,0.805,0.25,0.89);
						//}
					//}
					//else{
						//if(!nf){
							//TLegend* legname=new TLegend(0.15,0.825,0.25,0.895);
							//}
							//else{
								//TLegend* legname=new TLegend(0.15,0.82,0.25,0.89);
							//}
					//}
				if(!nt){
					if(!nf){
						TLegend* legname=new TLegend(0.1,0.5,0.2,0.6);
						}
						else{
							TLegend* legname=new TLegend(0.1,0.505,0.2,0.59);
						}
					}
					else{
						if(!nf){
							TLegend* legname=new TLegend(0.1,0.525,0.2,0.595);
							}
							else{
								TLegend* legname=new TLegend(0.1,0.52,0.2,0.59);
							}
					}
				legname->AddEntry((TObject*)0,Form("#font[132]{%s_{%s}}",tn[nt],fn[nf]),"");
				legname->SetBorderSize(0);
				legname->Draw();
				c.SetLogx();
				c.SetLogy();
				sprintf(cn,"../pictures/spectra/H11x%c%cE-1+11.eps",f[nf],t[nt]);
				c.Print((const char*)cn);
				delete leg1;
				delete leg2;
				delete legname;
			}
		}
	}
}
