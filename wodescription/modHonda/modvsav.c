#include "TStyle.h"

void SetStyle(){
	gStyle->SetCanvasColor(0);
	gStyle->SetFillColor(0);
	gStyle->SetFrameFillColor(0);
	gStyle->SetPadColor(0);
	gStyle->SetStatColor(0);
	gStyle->SetTitleFillColor(0);
	gStyle->SetFrameLineWidth(3);
	gStyle->SetPadLeftMargin(0.09);
	gStyle->SetPadRightMargin(0.01);
	gStyle->SetPadTopMargin(0.01);		
	gStyle->SetPadBottomMargin(0.09);
	gStyle->SetTitleOffset(1,"Y");
	gStyle->SetTitleOffset(1.1,"X");
	gStyle->SetTextFont(132);
}

void modvsav(){
	
	const int chd=2,chi=2,chf=2,cht=2,che=100,cha=2;
	const char nsp[5]="H11x",*nex="../../fortran/Output/";
	const char den[chd][4]={"2lm","wno"},i[chi]={'n','i'},f[chf]={'e','m'},t[cht]={'n','a'};
	char *name,cn[256];
	FILE *f140=0;
	double sp[chd][chi][chf][cht][che][cha],x,y;
	const int col[chf][cht]={{4,6},{1,2}},sh[chf][cht]={{9,3},{1,7}},w[chf][cht]={{1,2},{1,2}};
	int e,a,nd,ni,nf,nt,ndr;
	
	TCanvas c("c","Canvas",1200,800);
	TGraph grsp[chf][cht];
	
	SetStyle();

	for(nd=0; nd<chd; nd++){
		for(ni=0; ni<chi; ni++){
			for(nf=0; nf<chf; nf++){
				for(nt=0; nt<cht; nt++){
					sprintf(cn,"%s%s%c%s%c%c.dat",nex,den[nd],i[ni],nsp,f[nf],t[nt]);
					f140=fopen(cn,"r");
					for(e=0; e<che; e++){
						for(a=0; a<cha; a++){
							fscanf(f140,"%le",&(sp[nd][ni][nf][nt][e][a]));
						}
					}
					fclose(f140);
				}
			}
		}
	}

	for(ndr=0; ndr<2; ndr++){
		c.cd();
		for(ni=0; ni<chi; ni++){
			for(nf=0; nf<chf; nf++){
				for(nt=0; nt<cht; nt++){
					for(e=0; e<che; e++){
						grsp[nf][nt].SetPoint(e,sp[0][ni][nf][nt][e][0],sp[1][ni][nf][nt][e][1]/sp[0][ni][nf][nt][e][1]);
					}
				}
				grsp[nf][0].GetXaxis()->SetTitle("#font[132]{E_{#nu} (GeV)}");
				grsp[nf][0].GetXaxis()->SetRangeUser(1e-1,1.1e4);
				grsp[nf][0].GetYaxis()->SetTitle(Form("#font[132]{#frac{#nu_{%s}(E_{#nu})}{#nu_{%s}(E_{#nu})}}",den[1],den[0]));
				grsp[nf][0].GetYaxis()->SetRangeUser(0.9,1.5);
				for(nt=0; nt<cht; nt++){
					grsp[nf][nt].SetLineColor(col[nf][nt]);
					grsp[nf][nt].SetLineStyle(sh[nf][nt]);
					grsp[nf][nt].SetLineWidth(w[nf][nt]);
				}
			}
			grsp[0][0].Draw("AC");
			TLegend* lege=new TLegend(0.45,0.53,0.63,0.7);
			lege->AddEntry(&grsp[0][0],"#font[132]{#nu_{e}}","L");
			lege->AddEntry(&grsp[0][1],"#font[132]{#bar#nu_{e}}","L");
			TLegend* legm=new TLegend(0.63,0.53,0.81,0.7);
			legm->AddEntry(&grsp[1][0],"#font[132]{#nu_{#mu}}","L");
			legm->AddEntry(&grsp[1][1],"#font[132]{#bar#nu_{#mu}}","L");
			lege->Draw("SAME");
			legm->Draw("SAME");
			for(nf=0; nf<chf; nf++){
				for(nt=0; nt<cht; nt++){
					grsp[nf][nt].Draw("CSAME");
				}
			}
			c.SetLogx();
			sprintf(cn,"../pictures/spectra/%s%c_MSW.eps",nsp,i[ni]);
			c.Print((const char*)cn);
			delete lege;
			delete legm;
		}
	}
}
