#include "TStyle.h"

void SetStyle(){
	gStyle->SetCanvasColor(0);
	gStyle->SetFillColor(0);
	gStyle->SetFrameFillColor(0);
	gStyle->SetPadColor(0);
	gStyle->SetStatColor(0);
	gStyle->SetTitleFillColor(0);
	gStyle->SetFrameLineWidth(3);
	gStyle->SetPadLeftMargin(0.06);
	gStyle->SetPadRightMargin(0.005);
	gStyle->SetPadTopMargin(0.01);		
	gStyle->SetPadBottomMargin(0.07);
	gStyle->SetTitleOffset(0.7,"Y");
	gStyle->SetTitleOffset(0.8,"X");
	gStyle->SetTextFont(132);
}

void oscvac2(){

	const int chf=2,cha=5001;
	const char *nex="../../fortran/Output/oscvac32.dat";
	const char f[chf]={'e','m'},fn[chf][4]={"e","#mu"};
	char *name,cn[256];
	FILE *f101=0;
	double prcos,cosin[cha],p[chf][chf][cha];
	const int col[chf][chf]={{2,4},{4,1}},sh[chf][chf]={{9,3},{3,1}},w[chf][chf]={{1,2},{2,1}};
	int a,nf1,nf2,nd;
	
	TCanvas c("c","Canvas",1200,800);
	TGraph grp[chf][chf];
	
	SetStyle();

	f101=fopen(nex,"r");
	for(a=0; a<cha; a++){
		fscanf(f101,"%le",&prcos);
		cosin[a]=-prcos;
		for(nf1=0; nf1<2; nf1++){
			for(nf2=0; nf2<2; nf2++){
				fscanf(f101,"%le",&(p[nf1][nf2][a]));
			}
		}
	}
	fclose(f101);
	
	for(nd=0; nd<2; nd++){
		for(nf1=0; nf1<2; nf1++){
			for(nf2=0; nf2<2; nf2++){
				for(a=0; a<cha; a++){
					grp[nf1][nf2].SetPoint(a,cosin[a],p[nf1][nf2][a]);
				}
			}
		}
		for(nf1=0; nf1<2; nf1++){
			for(nf2=0; nf2<2; nf2++){
				grp[nf1][nf2].SetLineColor(col[nf1][nf2]);
				grp[nf1][nf2].SetLineStyle(sh[nf1][nf2]);
				grp[nf1][nf2].SetLineWidth(w[nf1][nf2]);
			}
		}
		c.cd();
		grp[0][0].GetXaxis()->SetTitle("#font[132]{cos(#theta)  }");
		grp[0][0].GetXaxis()->SetRangeUser(0,1);
		grp[0][0].GetYaxis()->SetTitle("#font[132]{P_{#alpha#beta}}");
		grp[0][0].GetYaxis()->SetRangeUser(0,1);
		grp[0][0].Draw("AC");
		for(nf1=0; nf1<2; nf1++){
			grp[nf1][nf1].Draw("CSAME");
		}
		grp[0][1].Draw("CSAME");
		TLegend* legaa=new TLegend(0.67,0.35,0.9,0.65);
		legaa->AddEntry((TObject*)0,"oscillation","");
		legaa->AddEntry((TObject*)0,"probabilities","");
		for(nf1=0; nf1<2; nf1++){
			legaa->AddEntry(&grp[nf1][nf1],Form("P_{%s%s}",fn[nf1],fn[nf1]),"L");
		}
		legaa->AddEntry(&grp[0][1],Form("P_{%s%s}=P_{%s%s}",fn[0],fn[1],fn[1],fn[0]),"L");
		legaa->Draw("SAME");
		name="../pictures/comosc2/vac32.eps";
		c.Print((const char*)name);
		delete legaa;
	}
}
