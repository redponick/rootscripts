#include "TStyle.h"

void SetStyle(){
	gStyle->SetFillColor(0);
	gStyle->SetFrameLineWidth(1);
	gStyle->SetPadLeftMargin(0.055);
	gStyle->SetPadRightMargin(0.005);
	gStyle->SetPadTopMargin(0.005);		
	gStyle->SetPadBottomMargin(0.04);
	gStyle->SetTitleOffset(0.7,"Y");
	gStyle->SetTitleOffset(0.4,"X");
//	gStyle->SetTextFont(132);
}

void HondapC(){
	
	const int chf=2,cht=2,che=7,cha=101;
	const char nsp[5]="H11x",*nex="../../fortran/Output/spectra/";
	const char f[chf]={'e','m'},t[cht]={'n','a'},fn[chf][5]={"e","#mu"},tn[cht][8]={"#nu","#bar#nu"};
	char *name,cn[256];
	FILE *f140=0;
	double sp[chf][cht][che][cha];
	const int col[che-1]={4,2,8,6,1,46},sh[che-1]={9,7,4,3,1,6},w[che-1]={1,2,2,2,1,2};
	int chea,e,a,nf,nt,n,nd;
	
	TCanvas c("c","Canvas",1200,800);
	TGraph grsp[chf][cht][che-1];
	
	SetStyle();
	
	chea=che-1;

	for(nf=0; nf<chf; nf++){
		for(nt=0; nt<cht; nt++){
			sprintf(cn,"%s%sza%c%c.dat",nex,nsp,f[nf],t[nt]);
			f140=fopen(cn,"r");
			for(e=0; e<che; e++){
				for(a=0; a<cha; a++){
					fscanf(f140,"%le",&(sp[nf][nt][e][a]));
				}
			}
			fclose(f140);
		}
	}

	for(nd=0; nd<2; nd++){
		for(nf=0; nf<chf; nf++){
			for(nt=0; nt<cht; nt++){
				c.cd();
				for(e=1; e<chea; e++){
					for(a=1; a<cha; a++){
						grsp[nf][nt][e-1].SetPoint(a-1,sp[nf][nt][0][a],sp[nf][nt][e][a]);
					}
				}
				grsp[nf][nt][0].GetXaxis()->SetTitle("#font[132]{cos#theta}  ");
				grsp[nf][nt][0].GetXaxis()->SetRangeUser(-1,1);
				grsp[nf][nt][0].GetYaxis()->SetTitle("#font[132]{#Phi_{#nu}(E_{#nu},#theta)/#Phi_{#nu}(E_{#nu},0)}");
				if(!nf){
					grsp[nf][nt][0].GetYaxis()->SetRangeUser(0.5,11.5);
					}
					else{
						if(che-chea){
							grsp[nf][nt][0].GetYaxis()->SetRangeUser(0.8,4.4);
							}
							else{
								grsp[nf][nt][0].GetYaxis()->SetRangeUser(0.5,6.8);
							}
					}
				grsp[nf][nt][0].Draw("AC");
				for(e=1; e<chea; e++){
					grsp[nf][nt][e-1].SetLineColor(col[e-1]);
					grsp[nf][nt][e-1].SetLineStyle(sh[e-1]);
					grsp[nf][nt][e-1].SetLineWidth(w[e-1]);
					grsp[nf][nt][e-1].Draw("CSAME");
				}
				TLegend* leg=new TLegend(0.7,0.6,0.99,0.95);
				leg->AddEntry((TObject*)0,"#font[132]{E_{#nu}:}","");	
				for(e=chea-1; e>0; e--){
					leg->AddEntry(&grsp[nf][nt][e-1],Form("#font[132]{10^{%d} GeV}",e-2),"L");
				}
				leg->SetBorderSize(0);
				leg->Draw();
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
				sprintf(cn,"../pictures/spectra/H11x%c%cC.eps",f[nf],t[nt]);
				c.Print((const char*)cn);
				delete leg;
				delete legname;
			}
		}
	}
}
