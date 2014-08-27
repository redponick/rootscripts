#include "TStyle.h"

void SetStyle(){
	gStyle->SetOptStat(0);
	gStyle->SetTitleTextColor(1);
	gStyle->SetTitleH(0.045);
//	gStyle->SetFillColor(0);
	gStyle->SetFrameLineWidth(1);
	gStyle->SetPadLeftMargin(0.07);
	gStyle->SetPadRightMargin(0.12);
	gStyle->SetPadTopMargin(0.05);		
	gStyle->SetPadBottomMargin(0.05);
//	gStyle->SetTitleOffset(0.7,"Y");
//	gStyle->SetTitleOffset(0.8,"X");
	gStyle->SetTextFont(132);
//	gStyle->SetPalette(1);
}

void ogramms(){

	const double pi=3.141592653589793238462643383279503;
	const int chd=5,chs=2,chh=2,chf=3,cht=2,che=50,cha=50,mult=1;
	const char *nid="../../fortran/Output/probanu/3D/",*nod="../pictures/probanu/3D/";
	const char den[chd][4]={"wno","vac","2lm","7lm","mat"},sa[chs]={'F','V'},h[chh]={'n','i'},f[chf]={'e','m','t'},t[cht]={'n','a'},fn[chf][5]={"e","#mu","#tau"};
    char nof[256],pfn[256];
	FILE *f101=0;
	double prcos,prenu,cosin[cha],lgenu[che],p[chd][chs][chh][cht][chf][chf][che][cha];//p[chf][chf][che][cha];
	int e,a,nd,ns,nh,nf1,nf2,nt,ndr,hf;
	
	TCanvas c("c","Canvas",200,200);
	TGraph2D grpce;
	TH2D hpce("hp","H2D",cha,0,1,che,-2,2);
	
	SetStyle();
	
	hf=1;
	
	nd=1;	
	//nt=0;
	//nh=1;
	//ns=1;
	
	//nf1=0;
	//nf2=0;
	
//	for(nd=1; nd<chd; nd++){
		for(nt=0; nt<cht; nt++){
			for(ns=0; ns<chs; ns++){
				for(nh=0; nh<chh; nh++){
					for(nf1=0; nf1<chf; nf1++){
						for(nf2=0; nf2<chf; nf2++){
							sprintf(pfn,"%s%c%c%c_%c%c",den[nd],t[nt],sa[ns],h[nh],f[nf1],f[nf2]);
							sprintf(nof,"%s%s.dat",nid,pfn);
							f101=fopen(nof,"r");
							fscanf(f101,"%le",&prcos);//zero
							for(a=0; a<cha; a++){
								fscanf(f101,"%le",&prcos);
								cosin[a]=-prcos;
							}
							for(e=0; e<che; e++){
								fscanf(f101,"%le",&prenu);
									if(nd!=1){
										lgenu[e]=prenu-9;
										}
										else{
											lgenu[e]=prenu;
										}
								for(a=0; a<cha; a++){
									fscanf(f101,"%le",&(p[nd][ns][nh][nt][nf1][nf2][e][a]));//&(p[nf1][nf2][e][a]));
								}
							}
							fclose(f101);
						}
					}
				}
			}
		}
//	}
	
//	for(ndr=0; ndr<2; ndr++){
//		for(nd=1; nd<chd; nd++){
			for(nt=0; nt<cht; nt++){
				for(ns=0; ns<chs; ns++){
					for(nh=0; nh<chh; nh++){
						for(nf1=0; nf1<chf; nf1++){
							for(nf2=0; nf2<chf; nf2++){
								for(e=0; e<che; e++){
									for(a=0; a<cha; a++){
										if(!hf){
											grpce.SetPoint(a*che+e,cosin[a],lgenu[e],p[nd][ns][nh][nt][nf1][nf2][e][a]);//p[nf1][nf2][e][a]);
										}else{
											hpce.SetBinContent(a+1,e+1,p[nd][ns][nh][nt][nf1][nf2][e][a]);//p[nf1][nf2][e][a]);
										}
									}
								}
								c.cd();
								if(!hf){
									grpce.SetTitle(Form("#font[132]{P_{%s%s}}",fn[nf1],fn[nf2]));
									grpce.GetXaxis()->SetTitle("#font[132]{cos(#theta)  }");
									grpce.GetXaxis()->SetRangeUser(0,1);
									grpce.GetYaxis()->SetTitle("#font[132]{E_{#nu}}");
									grpce.GetYaxis()->SetRangeUser(-2,2);
									grpce.GetZaxis()->SetRangeUser(0,1);
									grpce.SetNpx(mult*cha);
									grpce.SetNpy(mult*che);
									grpce.Draw("COLZ");
								}else{
									hpce.SetTitle(Form("#font[132]{P_{%s%s}}",fn[nf1],fn[nf2]));
									hpce.GetZaxis()->SetRangeUser(0,1);
									hpce.Draw("COLZ");
								}
								sprintf(pfn,"%s%c%c%c_%c%c",den[nd],t[nt],sa[ns],h[nh],f[nf1],f[nf2]);
								sprintf(nof,"%s%s.eps",nod,pfn);
								c.Print((const char*)nof);
							}
						}
					}
				}
			}
//		}
//	}
}
