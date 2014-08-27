#include "TStyle.h"

void SetStyle(){
	gStyle->SetOptStat(0);
	gStyle->SetTitleTextColor(1);
	gStyle->SetTitleH(0.045);
//	gStyle->SetFillColor(0);
	gStyle->SetFrameLineWidth(1);
	gStyle->SetPadLeftMargin(0.07);
	gStyle->SetPadRightMargin(0.14);
	gStyle->SetPadTopMargin(0.05);		
	gStyle->SetPadBottomMargin(0.05);
//	gStyle->SetTitleOffset(0.7,"Y");
//	gStyle->SetTitleOffset(0.8,"X");
	gStyle->SetTextFont(132);
//	gStyle->SetPalette(1);
}

void qesitau(){

	const int chn=3,chd=5,chh=2,chf=3,cht=2,chv=5,chp=101,che=101;
	const char *nid="../../fortran/Output/QESitau/",*nod="../pictures/qesitau/";
	const char net[chn]={'f','b','e'},den[chd][4]={"wno","vac","2lm","7lm","mat"},h[chh]={'n','i'},f[chf]={'e','m','t'},t[cht]={'n','a'},v[chv][5]={"0.90","0.95","1.10","1.20","1.35"},fn[chf][5]={"e","#mu","#tau"};
    char nof[256],pfn[256];
	FILE *f100=0;
	double zo[chd][chh][chf][chv][chp][che];
	int p,e,nn,nd,nh,nf,nt,nv,ndr;
	
	TCanvas c("c","Canvas",200,200);
	TGraph2D zerone[chv];
	TH2D hzo("hzo","H2D",che,-1,3,chp,log10(0.09),log10(50));
	
	SetStyle();
	
	nd=2;	
	nh=0;
//	nf=0;
	nv=1;
	
	nn=2;
	nt=0;
	
//	for(nd=1; nd<chd; nd++){
//		for(nh=0; nh<chh; nh++){
			for(nf=0; nf<chf; nf++){
//				for(nv=0; nv<chv; nv++){
					sprintf(pfn,"%c%s%c%c",net[nn],den[nd],h[nh],f[nf]);
					switch(nn){
						case 0:
							sprintf(nof,"%s%s%c%s.dat",nid,pfn,t[1],v[nv]);
							break;
						case 1:
							sprintf(nof,"%s%s%c%s.dat",nid,pfn,t[nt],v[nv]);
							break;
						case 2:
							sprintf(nof,"%s%s%s.dat",nid,pfn,v[nv]);
							break;
					}
					f100=fopen(nof,"r");
					for(p=0; p<chp; p++){
						for(e=0; e<che; e++){
							fscanf(f100,"%le",&(zo[nd][nh][nf][nv][p][e]));
						}
					}
					fclose(f100);
//				}
			}
//		}
//	}

//	for(ndr=0; ndr<2; ndr++){
		c.cd();
//		for(nd=0; nd<chd; nd++){
//			for(nh=0; nh<chh; nh++){
				for(nf=0; nf<chf; nf++){
//					for(nv=0; nv<chv; nv++){
						for(p=0; p<chp; p++){
							for(e=0; e<che; e++){
								//zerone[nv].SetPoint(e*chp+p,zo[nd][nh][nf][nv][0][e],zo[nd][nh][nf][nv][p][0],zo[nd][nh][nf][nv][p][e]);
								hzo.SetBinContent(e+1,p+1,zo[nd][nh][nf][nv][p][e]);
							}
						}
						c.cd();
						//zerone[nv].GetXaxis()->SetTitle("#font[132]{E_{#nu}}");
						//zerone[nv].GetXaxis()->SetRangeUser(1e-1,1e3);
						//zerone[nv].GetYaxis()->SetTitle("#font[132]{P_{lep}}");
						//zerone[nv].GetYaxis()->SetRangeUser(9e-2,5e1);
						//zerone[nv].GetZaxis()->SetRangeUser(-25,5);
						//c.SetLogx();
						//c.SetLogy();
						//c.SetLogz();
						//zerone[nv].SetNpx(che);
						//zerone[nv].SetNpy(chp);
						//zerone[nv].Draw("COLZ");
						hzo.SetTitle(Form("%c%c",f[nf],t[nt]));
						hzo.GetZaxis()->SetRangeUser(-30,0);
						hzo.Draw("COLZ");
						sprintf(pfn,"%c%s%c%c",net[nn],den[nd],h[nh],f[nf]);
						switch(nn){
							case 0:
								sprintf(nof,"%s%s%c.eps",nod,pfn,t[1]);
								break;
							case 1:
								sprintf(nof,"%s%s%c.eps",nod,pfn,t[nt]);
								break;
							case 2:
								sprintf(nof,"%s%s.eps",nod,pfn);
								break;
						}
						c.Print((const char*)nof);
//					}
				}
//			}
//		}
//	}
}
