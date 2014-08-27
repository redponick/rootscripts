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
//	gStyle->SetTextFont(132);
}

void qesemat(){
	
	const int chn=3,chd=5,chh=2,chf=3,cht=2,chv=5,che=100,cha=2;
	const char *nid="../../fortran/Output/QESnewP/",*nod="../pictures/qesnewp/";
	const char nl='m',nb='c',nc='c',net[chn]={'F','B','E'},den[chd][4]={"wno","vac","2lm","7lm","mat"},h[chh]={'n','i'},f[chf]={'e','m','t'},t[cht]={'n','a'},v[chv][5]={"0.90","0.95","1.10","1.20","1.35"},fn[chf][5]={"e","#mu","#tau"};
	char nof[256],pfn[256],temp[256];
	FILE *f100=0;
	double lf[chd][chh][chf][chv][che][cha];
	const int col[chv]={2,1,8,4,6},sh[chv]={3,1,7,9,4},w[chv]={2,1,2,1,2};
	int e,a,nn,nd,nh,nf,nt,nv,ndr;
	
	TCanvas c("c","Canvas",1200,800);
	TGraph grlf[chv];
	
	SetStyle();
	
	nd=4;
	nh=0;
	
	for(nn=0; nn<chn; nn++){
		for(nt=0; nt<cht; nt++){
	
//	for(nd=0; nd<chd; nd++){
//		for(nh=0; nh<chh; nh++){
			for(nf=0; nf<chf; nf++){
				for(nv=0; nv<chv; nv++){
					sprintf(pfn,"%c%s%c%c",net[nn],den[nd],h[nh],f[nf]);
					switch(nn){
						case 0:
							sprintf(nof,"%s%s%c%s_%c%c%c.dat",nid,pfn,t[1],v[nv],nl,nb,nc);
							break;
						case 1:
							sprintf(nof,"%s%s%c%s_%c%c%c.dat",nid,pfn,t[nt],v[nv],nl,nb,nc);
							break;
						case 2:
							sprintf(nof,"%s%s%s_%c%c%c.dat",nid,pfn,v[nv],nl,nb,nc);
							break;
					}
					f100=fopen(nof,"r");
					for(e=0; e<che; e++){
						for(a=0; a<cha; a++){
							fscanf(f100,"%le",&(lf[nd][nh][nf][nv][e][a]));
						}
					}
					fclose(f100);
				}
			}
//		}
//	}
	
	for(ndr=0; ndr<2; ndr++){
		c.cd();
//		for(nd=0; nd<chd; nd++){
//			for(nh=0; nh<chh; nh++){
				for(nf=0; nf<chf; nf++){
					for(nv=0; nv<chv; nv++){
						for(e=0; e<che; e++){
							grlf[nv].SetPoint(e,lf[nd][nh][nf][nv][e][0],lf[nd][nh][nf][nv][e][1]);
						}
					}
					sprintf(temp,"#font[132]{P_{%s} (GeV)}",fn[nf]);
					grlf[0].GetYaxis()->SetTitle("#font[132]{count rate (kt^{-1} yr^{-1})}");
					grlf[0].GetXaxis()->SetRangeUser(8e-2,5e2);
					//if(nn==0){
						//if(nf==2){
							//grlf[0].GetYaxis()->SetRangeUser(0,0.007);
							//}
							//else{
								//grlf[0].GetYaxis()->SetRangeUser(0,7);
							//}
						//}
						//else{
							//if(nf==2){
							//grlf[0].GetYaxis()->SetRangeUser(0,0.12);
							//}
							//else{
								//grlf[0].GetYaxis()->SetRangeUser(0,120);
							//}
						//}	
					grlf[chv-1].Draw("AC");
					for(nv=0; nv<chv; nv++){
						grlf[nv].SetLineColor(col[nv]);
						grlf[nv].SetLineStyle(sh[nv]);
						grlf[nv].SetLineWidth(w[nv]);
						grlf[nv].Draw("CSAME");
					}
					TLegend* leg=new TLegend(0.35,0.75,0.95,0.95);
					leg->AddEntry(&grlf[0],"#font[132]{M_{A}=0.90 GeV}","L");
					leg->AddEntry(&grlf[1],"#font[132]{M_{A}=0.95 GeV (world averaged value)}","L");
					leg->AddEntry(&grlf[2],"#font[132]{M_{A}=1.10 GeV}","L");
					leg->AddEntry(&grlf[3],"#font[132]{M_{A}=1.20 GeV (K2K best fit, SK default)}","L");
					leg->AddEntry(&grlf[4],"#font[132]{M_{A}=1.35 GeV (MiniBooNE 2010 best fit)}","L");
					leg->Draw("SAME");
					c.SetLogx();
					sprintf(pfn,"%c%s%c%c",net[nn],den[nd],h[nh],f[nf]);
					switch(nn){
						case 0:
							sprintf(nof,"%s%s%c_%c%c%c.eps",nod,pfn,t[1],nl,nb,nc);
							break;
						case 1:
							sprintf(nof,"%s%s%c_%c%c%c.eps",nod,pfn,t[nt],nl,nb,nc);
							break;
						case 2:
							sprintf(nof,"%s%s_%c%c%c.eps",nod,pfn,nl,nb,nc);
							break;
					}
					c.Print((const char*)nof);
					delete leg;
				}
//			}
//		}
	}
	
	}
	}
}
