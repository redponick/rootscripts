#include "TStyle.h"

void SetStyle(){
	gStyle->SetFillColor(0);
	gStyle->SetFrameLineWidth(1);
	gStyle->SetPadLeftMargin(0.06);
	gStyle->SetPadRightMargin(0.005);
	gStyle->SetPadTopMargin(0.01);	
	gStyle->SetPadBottomMargin(0.05);
	gStyle->SetTitleOffset(0.75,"Y");
	gStyle->SetTitleOffset(0.5,"X");
//	gStyle->SetTextFont(132);
}

void qessect(){
	
	const int chn=3,chf=3,cht=2,chv=5,che=100,cha=2;
	const char *nid="../../fortran/Output/section/",*nod="../pictures/section/";
	const char net[chn]={'F','B','E'},f[chf]={'e','m','t'},t[cht]={'n','a'},v[chv][5]={"0.90","0.95","1.10","1.20","1.35"},fn[chf][5]={"e","#mu","#tau"};
	char nof[256],pfn[256],temp[256];
	FILE *f100=0;
	double lf[chf][cht][chv][che][cha];
	const int col[chv]={2,1,8,4,6},sh[chv]={3,1,7,9,4},w[chv]={2,1,2,1,2};
	int e,a,nn,nf,nt,nv,ndr;
	
	TCanvas c("c","Canvas",1200,800);
	TGraph grlf[chv];
	
	SetStyle();
	
	nn=1;
	
	for(nt=0; nt<cht; nt++){
		for(nf=0; nf<chf; nf++){
			for(nv=0; nv<chv; nv++){
				sprintf(pfn,"%c%c",net[nn],f[nf]);
				sprintf(nof,"%s%s%c%s.dat",nid,pfn,t[nt],v[nv]);
				f100=fopen(nof,"r");
				for(e=0; e<che; e++){
					for(a=0; a<cha; a++){
						fscanf(f100,"%le",&(lf[nf][nt][nv][e][a]));
					}
				}
				fclose(f100);
			}
		}
	}
	
	for(nt=0; nt<cht; nt++){
		for(ndr=0; ndr<2; ndr++){
			c.cd();
			for(nf=0; nf<chf; nf++){
				for(nv=0; nv<chv; nv++){
					for(e=0; e<che; e++){
						grlf[nv].SetPoint(e,lf[nf][nt][nv][e][0],lf[nf][nt][nv][e][1]);
					}
				}
				sprintf(temp,"#font[132]{P_{%s} (GeV)}",fn[nf]);
				grlf[4].GetYaxis()->SetTitle("#font[132]{#sigma#times10^{38} (cm^{2})}");
				grlf[4].GetXaxis()->SetRangeUser(1e-2,1e3);
				if(nn==0){
					grlf[4].GetYaxis()->SetRangeUser(0,1.5);
					}
					else{
						grlf[4].GetYaxis()->SetRangeUser(0,1.5);
					}
				grlf[4].Draw("AC");
				for(nv=0; nv<chv; nv++){
					grlf[nv].SetLineColor(col[nv]);
					grlf[nv].SetLineStyle(sh[nv]);
					grlf[nv].SetLineWidth(w[nv]);
					grlf[nv].Draw("CSAME");
				}
				TLegend* leg=new TLegend(0.65,0.2,0.95,0.45);
				leg->AddEntry(&grlf[0],"#font[132]{M_{A}=0.90 GeV}","L");
				leg->AddEntry(&grlf[1],"#font[132]{M_{A}=0.95 GeV}","L");
				leg->AddEntry(&grlf[2],"#font[132]{M_{A}=1.10 GeV}","L");
				leg->AddEntry(&grlf[3],"#font[132]{M_{A}=1.20 GeV}","L");
				leg->AddEntry(&grlf[4],"#font[132]{M_{A}=1.35 GeV}","L");
				leg->Draw("SAME");
				c.SetLogx();
				sprintf(pfn,"%c%c",net[nn],f[nf]);
				sprintf(nof,"%s%s%c.eps",nod,pfn,t[nt]);
				c.Print((const char*)nof);
				delete leg;
			}
		}
	}
}
