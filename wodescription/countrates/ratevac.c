#include "TStyle.h"

void SetStyle(){
	gStyle->SetFillColor(0);
	gStyle->SetFrameLineWidth(1);
	gStyle->SetPadLeftMargin(0.06);
	gStyle->SetPadRightMargin(0.005);
	gStyle->SetPadTopMargin(0.01);	
	gStyle->SetPadBottomMargin(0.05);
	gStyle->SetTitleOffset(0.9,"Y");
	gStyle->SetTitleOffset(0.5,"X");
	gStyle->SetTextFont(132);
}

void ratevac(){
	
	const int chv=5,chf=2,chp=100,cha=2;
	const char nip[14]="QESintP/Evaci",*nex="../../fortran/Output/";
	const char v[chv][5]={"0.90","0.95","1.10","1.20","1.35"},f[chf]={'e','m'};
	char *name,cn[256];
	FILE *f100=0;
	double dnc[chf][chv][chp][cha],dnv[chf][chv][chp][cha];
	const int col[chv]={2,1,8,4,6},sh[chv]={3,1,7,9,4},w[chv]={2,1,2,1,2};
	int p,a,nm,nf,nv,nd;
	
	TCanvas c("c","Canvas",1200,800);
	TGraph grdn[chv];
	
	SetStyle();
	
	for(nf=0; nf<chf; nf++){
		for(nv=0; nv<chv; nv++){	
			sprintf(cn,"%s%s%c%s_c.dat",nex,nip,f[nf],v[nv]);
			f100=fopen(cn,"r");
			for(p=0; p<chp; p++){
				for(a=0; a<cha; a++){
					fscanf(f100,"%le",&(dnc[nf][nv][p][a]));
				}
			}
			fclose(f100);
		}
	}
	
	for(nf=0; nf<chf; nf++){
		for(nv=0; nv<chv; nv++){	
			sprintf(cn,"%s%s%c%s_v.dat",nex,nip,f[nf],v[nv]);
			f100=fopen(cn,"r");
			for(p=0; p<chp; p++){
				for(a=0; a<cha; a++){
					fscanf(f100,"%le",&(dnv[nf][nv][p][a]));
				}
			}
			fclose(f100);
		}
	}
	
	for(nd=0; nd<2; nd++){
		c.cd();
		for(nf=0; nf<chf; nf++){
				for(p=0; p<chp; p++){
					grdn[1].SetPoint(p,dnc[nf][3][p][0],dnv[nf][1][p][1]/dnc[nf][3][p][1]);
				}
			if(nf==0){
				grdn[1].GetXaxis()->SetTitle("#font[132]{P_{e} (GeV)}");
				}
				else{
					grdn[1].GetXaxis()->SetTitle("#font[132]{P_{#mu} (GeV)}");
				}
			grdn[1].GetYaxis()->SetTitle("#font[132]{count rate ratio}");
			grdn[1].GetXaxis()->SetRangeUser(8e-2,5e1);
			grdn[1].GetYaxis()->SetRangeUser(0.5,1.5);
			grdn[1].Draw("AC");
			//for(nv=0; nv<chv; nv++){
				//grdn[nv].SetLineColor(col[nv]);
				//grdn[nv].SetLineStyle(sh[nv]);
				//grdn[nv].SetLineWidth(w[nv]);
				//grdn[nv].Draw("CSAME");
			//}
			//TLegend* leg=new TLegend(0.1,0.7,0.7,0.95);
			//leg->AddEntry(&grdn[0],"#font[132]{M_{A}=0.9 GeV}","L");
			//leg->AddEntry(&grdn[1],"#font[132]{M_{A}=0.95 GeV (world averaged value)}","L");
			//leg->AddEntry(&grdn[2],"#font[132]{M_{A}=1.1 GeV (SK default value)}","L");
			//leg->AddEntry(&grdn[3],"#font[132]{M_{A}=1.2 GeV (K2K best fit)}","L");
			//leg->AddEntry(&grdn[4],"#font[132]{M_{A}=1.35 GeV (MiniBooNE 2010 best fit)}","L");
			//leg->Draw("SAME");
			c.SetLogx();
			sprintf(cn,"../pictures/qesintp/varMAi%c.eps",f[nf]);
			c.Print((const char*)cn);
			//delete leg;
		}
	}
}
