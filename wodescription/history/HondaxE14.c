#include "TStyle.h"

void SetStyle(){
	gStyle->SetCanvasColor(0);
	gStyle->SetFillColor(0);
	gStyle->SetFrameFillColor(0);
	gStyle->SetPadColor(0);
	gStyle->SetStatColor(0);
	gStyle->SetTitleFillColor(0);
	gStyle->SetFrameLineWidth(3);
	gStyle->SetPadLeftMargin(0.08);
	gStyle->SetPadRightMargin(0.01);
	gStyle->SetPadTopMargin(0.02);		
	gStyle->SetPadBottomMargin(0.09);
	gStyle->SetTitleOffset(0.9,"Y");
	gStyle->SetTitleOffset(1.1,"X");
	gStyle->SetTextFont(132);
}

void HondaxE(){
	
	const int chf=2,cht=2,che=101,cha=14;
	const char nsp[5]="H11x",*nex="../../fortran/Output/";
	const char f[chf]={'e','m'},t[cht]={'n','a'};
	char *name,cn[256];
	FILE *f140=0;
	double sp[chf][cht][che][cha];
	const int col[cha-1]={40,2,4,6,8,46,1,46,8,6,4,2,40};
	int e,a,nf,nt,n,nd;
	
	TCanvas c("c","Canvas",1200,800);
	TGraph grsp[chf][cht][cha-1];
	
	SetStyle();

	for(nf=0; nf<chf; nf++){
		for(nt=0; nt<cht; nt++){
			sprintf(cn,"%s%ssp%c%c14.dat",nex,nsp,f[nf],t[nt]);
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
				for(a=1; a<cha; a++){
					for(e=1; e<che; e++){
						grsp[nf][nt][a-1].SetPoint(e-1,sp[nf][nt][e][0],sp[nf][nt][e][a]/sp[nf][nt][e][cha-1]);
					}
				}
				grsp[nf][nt][0].GetXaxis()->SetTitle("#font[132]{E_{#nu} (GeV)}");
				grsp[nf][nt][0].GetXaxis()->SetRangeUser(1e-1,1.1e4);
				grsp[nf][nt][0].GetYaxis()->SetTitle("#font[132]{#frac{j_{#nu}(E_{#nu},#theta)}{j_{#nu}(E_{#nu},0)}}");
				if(nf==0){
					grsp[nf][nt][0].GetYaxis()->SetRangeUser(0,12);
					}
					else{
						grsp[nf][nt][0].GetYaxis()->SetRangeUser(0,7);
					}
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
				TLegend* leg1=new TLegend(0.15,0.40,0.25,0.80);
				TLegend* leg2=new TLegend(0.25,0.40,0.35,0.80);
				leg1->AddEntry((TObject*)0,"#font[132]{cos#theta:}","");	
				for(a=cha/2-1; a>0; a--){
					leg1->AddEntry(&grsp[nf][nt][a-1],Form("#font[132]{%5.2f}",sp[nf][nt][0][a]),"L");
				}
				for(a=cha/2; a<cha; a++){
					leg2->AddEntry(&grsp[nf][nt][a-1],Form("#font[132]{%5.2f}",sp[nf][nt][0][a]),"L");
				}
				leg1->Draw("SAME");
				leg2->Draw("SAME");
				if(nt==0){
					if(nf==0){
						TLegend* legname=new TLegend(0.15,0.79,0.25,0.92);
						legname->AddEntry((TObject*)0,"#font[132]{#nu_{e}}","");
						}
						else{
							TLegend* legname=new TLegend(0.15,0.8,0.25,0.9);
							legname->AddEntry((TObject*)0,"#font[132]{#nu_{#mu}}","");
						}
					}
					else{
						if(nf==0){
							TLegend* legname=new TLegend(0.15,0.81,0.25,0.89);
							legname->AddEntry((TObject*)0,"#font[132]{#bar#nu_{e}}","");
							}
							else{
								TLegend* legname=new TLegend(0.15,0.81,0.25,0.89);
								legname->AddEntry((TObject*)0,"#font[132]{#bar#nu_{#mu}}","");
							}
					}
				legname->Draw("SAME");
				c.SetLogx();
//				c.SetLogy();
				sprintf(cn,"../pictures/spectra/H11x%c%cE_ratio.eps",f[nf],t[nt]);
				c.Print((const char*)cn);
				delete leg1;
				delete leg2;
				delete legname;
			}
		}
	}
}
