#include "TStyle.h"

void SetStyle(){
	gStyle->SetCanvasColor(0);
	gStyle->SetFillColor(0);
	gStyle->SetFrameFillColor(0);
	gStyle->SetPadColor(0);
	gStyle->SetStatColor(0);
	gStyle->SetTitleFillColor(0);
	gStyle->SetFrameLineWidth(3);
	gStyle->SetPadLeftMargin(0.075);
	gStyle->SetPadRightMargin(0.01);
	gStyle->SetPadTopMargin(0.01);		
	gStyle->SetPadBottomMargin(0.09);
	gStyle->SetTitleOffset(0.9,"Y");
	gStyle->SetTitleOffset(1.1,"X");
	gStyle->SetTextFont(132);
}

void CORTouE(){
	
	const double pi=3.141592653589793;
	const int chf=2,cht=2,che=273,cha=5;
	const char nsp[8]="CORTest",*nex="../../fortran/Output/CORTout/";
	const char f[chf]={'e','m'},t[cht]={'n','a'};
	char *name,cn[256];
	FILE *f140=0;
	double sp[che][cha],x,y;
	const int col[chf][cht]={{4,6},{1,2}},sh[chf][cht]={{9,3},{1,7}},w[chf][cht]={{1,2},{1,2}};	
//	const int col[cht]={4,1},sh[cht]={7,1},w[cht]={2,1};
	int e,a,nf,nt,n,nd;
	
	TCanvas c("c","Canvas",1200,800);
	TGraph grsp[chf][cht];
	
	SetStyle();

	sprintf(cn,"%s%s.dat",nex,nsp);
	f140=fopen(cn,"r");
	for(e=0; e<che; e++){
		for(a=0; a<cha; a++){
			fscanf(f140,"%le",&(sp[e][a]));
		}
	}
	fclose(f140);

	for(nd=0; nd<2; nd++){
		c.cd();
		for(nf=0; nf<chf; nf++){
			for(nt=0; nt<cht; nt++){
				for(e=16; e<che; e++){
					x=sp[e][0];
					y=(0.01)**2*x**3*sp[e][chf*nf+nt+1];
					grsp[nf][nt].SetPoint(e-16,x,y);
				}
			}
			grsp[nf][0].GetXaxis()->SetTitle("#font[132]{E_{#nu} (GeV)}");
			grsp[nf][0].GetXaxis()->SetRangeUser(1e-1,1e4);
			grsp[nf][0].GetYaxis()->SetTitle("#font[132]{E_{#nu}^{3} j_{#nu}(E_{#nu},#theta) (GeV^{2} s^{-1} sr^{-1} cm^{-2})}");
			grsp[nf][0].GetYaxis()->SetRangeUser(2e-4,7e-2);
			for(nt=0; nt<cht; nt++){
				grsp[nf][nt].SetLineColor(col[nf][nt]);
				grsp[nf][nt].SetLineStyle(sh[nf][nt]);
				grsp[nf][nt].SetLineWidth(w[nf][nt]);
			}
		}
		grsp[0][0].Draw("AC");
		TLegend* lege=new TLegend(0.25,0.33,0.43,0.5);
		lege->AddEntry(&grsp[0][0],"#font[132]{#nu_{e}}","L");
		lege->AddEntry(&grsp[0][1],"#font[132]{#bar#nu_{e}}","L");
		TLegend* legm=new TLegend(0.43,0.33,0.61,0.5);
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
		c.SetLogy();
		sprintf(cn,"../pictures/spectra/CORTouE.eps");
		c.Print((const char*)cn);
		delete lege;
		delete legm;
	}
}
