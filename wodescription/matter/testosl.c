#include "TStyle.h"

void SetStyle(){
	gStyle->SetCanvasColor(0);
	gStyle->SetFillColor(0);
	gStyle->SetFrameFillColor(0);
	gStyle->SetPadColor(0);
	gStyle->SetStatColor(0);
	gStyle->SetTitleFillColor(0);
	gStyle->SetPadLeftMargin(0.06);
	gStyle->SetPadRightMargin(0.01);
	gStyle->SetPadTopMargin(0.05);		
	gStyle->SetPadBottomMargin(0.09);
	gStyle->SetTitleOffset(0.8,"Y");
	gStyle->SetTitleOffset(1.1,"X");
	gStyle->SetTextFont(132);
	gStyle->SetPalette(1);
}

void testosl(){

	const int chh=2,chf=2,cht=2,che=100;
	const char nsp[5]="H11x",*nex="../../fortran/Output/testmat/";
	const char h[chh]={'n','i'},f[chf]={'e','m'},t[cht]={'n','a'};
	char *name,cn[256];
	FILE *fold=1,*fnew=2,*ferr=2;
	double Enu[che],spold[chh][chf][cht][che],spnew[chh][chf][cht][che],err[chh][chf][cht][che];
	const int col[chf][cht]={{4,6},{1,2}},sh[chh]={1,2};
	int nh,nf,nt,e;
	
	TCanvas c("c","Canvas",600,400);
	TGraph gr[chh][chf][cht];
	
	SetStyle();
	
	nh=0;
	nf=0;
	nt=0;
	
//	for(nh=0; nh<chh; nh++){
//		for(nf=0; nf<chf; nf++){
//			for(nt=0; nt<cht; nt++){
				sprintf(cn,"%s%s%c%s%c%c.dat",nex,"500",h[nh],nsp,f[nf],t[nt]);
				fold=fopen(cn,"r");
				sprintf(cn,"%s%s%c%s%c%c.dat",nex,"032",h[nh],nsp,f[nf],t[nt]);
				fnew=fopen(cn,"r");
				sprintf(cn,"%s%s%c%s%c%c.dat",nex,"500_032",h[nh],nsp,f[nf],t[nt]);
				ferr=fopen(cn,"w");
				for(e=0; e<che; e++){
					fscanf(fold,"%le",&(Enu[e]));
					fscanf(fnew,"%le",&(Enu[e]));
					fscanf(fold,"%le",&(spold[nh][nf][nt][e]));
					fscanf(fnew,"%le",&(spnew[nh][nf][nt][e]));
					err[nh][nf][nt][e]=fabs(spnew[nh][nf][nt][e]-spold[nh][nf][nt][e])/spold[nh][nf][nt][e]*100;
					fprintf(ferr,"%le %le\n",Enu[e],err[nh][nf][nt][e]);
				}
				fclose(fold);
				fclose(fnew);
				fclose(ferr);
//			}
//		}
//	}
	
	c.cd();
//	for(nh=0; nh<chh; nh++){
//		for(nf=0; nf<chf; nf++){
//			for(nt=0; nt<cht; nt++){
				for(e=0; e<che; e++){
					gr[nh][nf][nt].SetPoint(e,Enu[e],err[nh][nf][nt][e]);
				}
//			}
//		}
//	}
	gr[0][0][0].GetXaxis()->SetTitle("#font[132]{E_{#nu} (GeV)}");
	gr[0][0][0].GetXaxis()->SetRangeUser(1e-1,1.1e4);
	gr[0][0][0].GetYaxis()->SetTitle("#font[132]{relative error (%)}");
	gr[0][0][0].GetYaxis()->SetRangeUser(0,1e-4);
	gr[0][0][0].Draw("AC");
//	for(nh=0; nh<chh; nh++){
//		for(nf=0; nf<chf; nf++){
//			for(nt=0; nt<cht; nt++){
				gr[nh][nf][nt].SetLineColor(col[nf][nt]);
				gr[nh][nf][nt].SetLineStyle(sh[nh]);
				gr[nh][nf][nt].Draw("CSAME");
//			}
//		}
//	}
	TLegend* leg=new TLegend(0.6,0.4,0.8,0.75);
//	for(nh=0; nh<chh; nh++){
//		for(nf=0; nf<chf; nf++){
//			for(nt=0; nt<cht; nt++){
				leg->AddEntry(&gr[nh][nf][nt],Form("#font[132]{%c, %c, %c}",h[nh],f[nf],t[nt]),"L");
//			}
//		}
//	}
	leg->Draw("SAME");
	c.SetLogx();
	sprintf(cn,"../pictures/slayers/500vs032_%snen.eps",nsp);
	c.Print((const char*)cn);
	delete leg;
}
