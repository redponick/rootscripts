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

void CRTwnor(){
	
	const int chv=3,chf=2,chp=100,cha=2;
	const char nip[14]="CRTintP/Ewnon",*nex="../../fortran/Output/";
	const char v[chv]={'l','n','w'},f[chf]={'e','m'};
	char *name,cn[256];
	FILE *f100=0;
	double dn[chf][chv][chp][cha];
	const int col[chv]={2,1,8},sh[chv]={3,1,7},w[chv]={2,1,2};
	int p,a,nm,nf,nv,nd;
	
	TCanvas c("c","Canvas",1200,800);
	TGraph grdn[chv];
	
	SetStyle();
	
	for(nf=0; nf<chf; nf++){
		for(nv=0; nv<chv; nv++){	
			sprintf(cn,"%s%s%c0.95%c.dat",nex,nip,f[nf],v[nv]);
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
			}
			if(nf==0){
				grdn[0].GetXaxis()->SetTitle("#font[132]{P_{e} (GeV)}");
				}
				else{
					grdn[0].GetXaxis()->SetTitle("#font[132]{P_{#mu} (GeV)}");
				}
			grdn[0].GetYaxis()->SetTitle("#font[132]{count rate ratio}");
			grdn[0].GetXaxis()->SetRangeUser(8e-2,5e2);
			grdn[0].GetYaxis()->SetRangeUser(0,11);
			grdn[0].Draw("AC");
			for(nv=0; nv<chv; nv++){
				grdn[nv].SetLineColor(col[nv]);
				grdn[nv].SetLineStyle(sh[nv]);
				grdn[nv].SetLineWidth(w[nv]);
				grdn[nv].Draw("CSAME");
			}
			TLegend* leg=new TLegend(0.25,0.7,0.85,0.95);
			leg->AddEntry(&grdn[0],"#font[132]{E_{#nu}#in[0.05,     10^{3}] GeV}","L");
			leg->AddEntry(&grdn[1],"#font[132]{E_{#nu}#in[0.1,       10^{3}] GeV}","L");
			leg->AddEntry(&grdn[2],"#font[132]{E_{#nu}#in[0.1,9.9#times10^{5}] GeV}","L");
			leg->Draw("SAME");
			c.SetLogx();
			sprintf(cn,"../pictures/qesintp/CRTwnor%c.eps",f[nf]);
			c.Print((const char*)cn);
			delete leg;
		}
	}
}
