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

void oscmat4(){

	const int chf=3,cha=5000,chfi=10;
	const char *nex="../../fortran/Output/";
	const char *np[chfi]={"Angle","Pee","Pem","Pet","Pme","Pmm","Pmt","Pte","Ptm","Ptt"};
	const char f[chf]={'e','m','t'},fn[chf][5]={"e","#mu","#tau"};
	char *name,cn[256];
	FILE *f10[chfi]={0,1,2,3,4,5,6,7,8,9};
	double prcos,cosin[cha],p[chf][chf][cha];
	const int col[chf][chf]={{2,4,2},{4,4,1},{2,1,1}},sh[chf][chf]={{9,3,9},{3,3,1},{9,1,1}},w[chf][chf]={{1,2,1},{2,2,1},{1,1,1}};
	int a,nf,nfi,nf1,nf2,nd;
	
	TCanvas c("c","Canvas",1200,800);
	TGraph grp[chf][chf];
	
	SetStyle();
	
	for(nfi=0; nfi<chfi; nfi++){
		sprintf(cn,"%s4%s.txt",nex,np[nfi]);
		f10[nfi]=fopen(cn,"r");
	}
	for(a=0; a<cha; a++){
		fscanf(f10[0],"%le",&prcos);
		cosin[a]=cos(prcos);
		for(nf1=0; nf1<3; nf1++){
			for(nf2=0; nf2<3; nf2++){
				fscanf(f10[nf1*3+nf2+1],"%le",&(p[nf1][nf2][a]));
			}
		}
	}
	for(nfi=0; nfi<chfi; nfi++){
		fclose(f10[nfi]);
	}
	
	for(nd=0; nd<2; nd++){
		for(nf1=0; nf1<3; nf1++){
			for(nf2=0; nf2<3; nf2++){
				for(a=0; a<cha; a++){
					grp[nf1][nf2].SetPoint(a,cosin[a],p[nf1][nf2][a]);
				}
			}
		}
		for(nf1=0; nf1<3; nf1++){
			for(nf2=0; nf2<3; nf2++){
				grp[nf1][nf2].SetLineColor(col[nf1][nf2]);
				grp[nf1][nf2].SetLineStyle(sh[nf1][nf2]);
				grp[nf1][nf2].SetLineWidth(w[nf1][nf2]);
			}
		}
		c.cd();
		grp[0][0].GetXaxis()->SetTitle("#font[132]{cos(#theta)  }");
		grp[0][0].GetXaxis()->SetRangeUser(-1,1);
		grp[0][0].GetYaxis()->SetTitle("#font[132]{P_{#alpha#beta}}");
		grp[0][0].GetYaxis()->SetRangeUser(0,1);
		grp[0][0].Draw("AC");
		for(nf1=0; nf1<3; nf1++){
			grp[nf1][nf1].Draw("CSAME");
		}
		TLegend* legaa=new TLegend(0.6,0.35,0.9,0.65);
		legaa->AddEntry((TObject*)0,"survival","");
		legaa->AddEntry((TObject*)0,"probabilities","");
		for(nf1=0; nf1<3; nf1++){
			legaa->AddEntry(&grp[nf1][nf1],Form("P_{%s%s}",fn[nf1],fn[nf1]),"L");
		}
		legaa->Draw("SAME");
		name="../pictures/comosc4/osc4aan.eps";
		c.Print((const char*)name);
		delete legaa;
		c.cd();
		grp[0][1].GetXaxis()->SetTitle("#font[132]{cos(#theta)  }");
		grp[0][1].GetXaxis()->SetRangeUser(-1,1);
		grp[0][1].GetYaxis()->SetTitle("#font[132]{P_{#alpha#beta}}");
		grp[0][1].GetYaxis()->SetRangeUser(0,1);
		grp[0][1].Draw("AC");
		for(nf1=0; nf1<3; nf1++){
			for(nf2=0; nf2<3; nf2++){
				if(nf1!=nf2){
					grp[nf1][nf2].Draw("CSAME");
				}
			}
		}
		TLegend* legab=new TLegend(0.6,0.35,0.9,0.65);
		legab->AddEntry((TObject*)0,"oscillation","");	
		legab->AddEntry((TObject*)0,"probabilities","");
		legab->AddEntry(&grp[0][1],Form("P_{%s%s}=P_{%s%s}",fn[0],fn[1],fn[1],fn[0]),"L");
		legab->AddEntry(&grp[1][2],Form("P_{%s%s}=P_{%s%s}",fn[1],fn[2],fn[2],fn[1]),"L");
		legab->AddEntry(&grp[0][2],Form("P_{%s%s}=P_{%s%s}",fn[0],fn[2],fn[2],fn[0]),"L");
		legab->Draw("SAME");
		name="../pictures/comosc4/osc4abn.eps";
		c.Print((const char*)name);
		delete legab;
	}
}
