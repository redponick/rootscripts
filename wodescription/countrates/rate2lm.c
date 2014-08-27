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

void rate2lm(){
	
	const int chv=5,chf=2,chp=100,cha=2;
	const char nip[14]="QESintP/E2lmn",*nex="../../fortran/Output/";
	const char v[chv][5]={"0.90","0.95","1.10","1.20","1.35"},f[chf]={'e','m'};
	char *name,cn[256];
	FILE *f100=0;
	double dn[chf][chv][chp][cha];
	const int col[chv]={2,1,8,4,6},sh[chv]={3,1,7,9,4},w[chv]={2,1,2,1,2};
	int p,a,nm,nf,nv,nd;
	
	TCanvas c("c","Canvas",1200,800);
	TGraph grdn[chv];
	
	SetStyle();
	
	for(nf=0; nf<chf; nf++){
		for(nv=0; nv<chv; nv++){	
			sprintf(cn,"%s%s%c%s_v.dat",nex,nip,f[nf],v[nv]);
			f100=fopen(cn,"r");
			for(p=0; p<chp; p++){
				for(a=0; a<cha; a++){
					fscanf(f100,"%le",&(dn[nf][nv][p][a]));
				}
			}
			fclose(f100);
		}
	}
	
	for(nd=0; nd<2; nd++){
		c.cd();
		for(nf=0; nf<chf; nf++){
			for(nv=0; nv<chv; nv++){
				for(p=0; p<chp; p++){
					grdn[nv].SetPoint(p,dn[nf][nv][p][0],dn[nf][nv][p][1]/dn[nf][1][p][1]);
				}
				//if(nf==0){
					//grdn[nv].RemovePoint(8);
					//grdn[nv].RemovePoint(54);
					//grdn[nv].RemovePoint(66);
					//grdn[nv].RemovePoint(67);
					//grdn[nv].RemovePoint(94);
				//}
					//else{
						//grdn[nv].RemovePoint(17);
						//grdn[nv].RemovePoint(25);
						//grdn[nv].RemovePoint(34);
						//grdn[nv].RemovePoint(76);
						//grdn[nv].RemovePoint(76);
						//grdn[nv].RemovePoint(82);
						//grdn[nv].RemovePoint(85);
						//grdn[nv].RemovePoint(88);
					//}
			}
			if(nf==0){
				grdn[0].GetXaxis()->SetTitle("#font[132]{P_{e} (GeV)}");
				}
				else{
					grdn[0].GetXaxis()->SetTitle("#font[132]{P_{#mu} (GeV)}");
				}
			grdn[0].GetYaxis()->SetTitle("#font[132]{count rate ratio}");
			grdn[0].GetXaxis()->SetRangeUser(8e-2,5e1);
			grdn[0].GetYaxis()->SetRangeUser(0.85,1.6);
			grdn[0].Draw("AC");
			for(nv=0; nv<chv; nv++){
				grdn[nv].SetLineColor(col[nv]);
				grdn[nv].SetLineStyle(sh[nv]);
				grdn[nv].SetLineWidth(w[nv]);
				grdn[nv].Draw("CSAME");
			}
			TLegend* leg=new TLegend(0.1,0.7,0.7,0.95);
			leg->AddEntry(&grdn[0],"#font[132]{M_{A}=0.9 GeV}","L");
			leg->AddEntry(&grdn[1],"#font[132]{M_{A}=0.95 GeV (world averaged value)}","L");
			leg->AddEntry(&grdn[2],"#font[132]{M_{A}=1.1 GeV (SK default value)}","L");
			leg->AddEntry(&grdn[3],"#font[132]{M_{A}=1.2 GeV (K2K best fit)}","L");
			leg->AddEntry(&grdn[4],"#font[132]{M_{A}=1.35 GeV (MiniBooNE 2010 best fit)}","L");
			leg->Draw("SAME");
			c.SetLogx();
			sprintf(cn,"../pictures/qesintp/rat2lmn%c_v.eps",f[nf]);
			c.Print((const char*)cn);
			delete leg;
		}
	}
}
