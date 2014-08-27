#include "TStyle.h"

void SetStyle(){
	gStyle->SetFillColor(0);
	gStyle->SetFrameLineWidth(1);
	gStyle->SetPadLeftMargin(0.04);
	gStyle->SetPadRightMargin(0.07);
	gStyle->SetPadTopMargin(0.01);		
	gStyle->SetPadBottomMargin(0.06);
	gStyle->SetTitleOffset(0.5,"Y");
	gStyle->SetTitleOffset(0.8,"X");
//	gStyle->SetTextFont(132);
//	gStyle->SetPalette(1);
}

void oscmat3(){

	const int chd=5,chh=2,chs=2,chf=3,cht=2,che=50,cha=50;
	const char *nid="../../fortran/Output/probanu/",*nod="../pictures/probanu/";
	const char den[chd][4]={"wno","vac","2lm","7lm","mat"},h[chh]={'n','i'},sa[chs]={'F','V'},f[chf]={'e','m','t'},t[cht]={'n','a'},fn[chf][5]={"e","#mu","#tau"},abn[3][3]={"aa","ab","ba"},pr[2]={'c','E'};
    char nof[256],pfn[256];
	FILE *f101=0;
	double prcos,prenu,cosin[cha],enu[che],pa[chd][chh][cht][chf][chf][cha],pe[chd][chh][cht][chf][chf][che];
	const int col[chf][chf]={{2,4,2},{4,4,1},{2,1,1}},sh[chf][chf]={{9,3,9},{3,3,1},{9,1,1}},w[chf][chf]={{1,2,1},{2,2,1},{1,1,1}};
	int core,ab,e,a,nd,nh,ns,nf1,nf2,nt,nf01,nf02,ndr;
	bool alphabeta;
	
	TCanvas c("c","Canvas",1200,800);
	TGraph grp[chf][chf];
	
	SetStyle();
	
	core=0;//0 - var cos & E, 1 - var cos
	
	nd=1;
	nt=0;
	nh=0;
	ns=0;
						
//	for(nd=1; nd<chd; nd++){
//		for(nt=0; nt<cht; nt++){
//			for(ns=0; ns<chs; ns++){
//				for(nh=0; nh<chh; nh++){
					sprintf(pfn,"v%c/%s%c%c%c",pr[core],den[nd],t[nt],sa[ns],h[nh]);
					sprintf(nof,"%s%s.dat",nid,pfn);
					f101=fopen(nof,"r");
					if(core){
						for(e=0; e<che; e++){
							fscanf(f101,"%le",&prenu);
							if(nd!=1){
								enu[e]=1e-9*prenu;
								}
								else{
									enu[e]=prenu;
								}
							for(nf1=0; nf1<chf; nf1++){
								for(nf2=0; nf2<chf; nf2++){
									fscanf(f101,"%le",&(pe[nd][nh][nt][nf1][nf2][e]));
								}
							}
						}
						}
						else{
							for(a=0; a<cha; a++){
								fscanf(f101,"%le",&prcos);
								cosin[a]=-prcos;
								for(nf1=0; nf1<chf; nf1++){
									for(nf2=0; nf2<chf; nf2++){
										fscanf(f101,"%le",&(pa[nd][nh][nt][nf1][nf2][a]));
									}
								}
							}
						}
					fclose(f101);
//				}
//			}
//		}
//	}

//	for(ndr=0; ndr<2; ndr++){
//		for(nd=1; nd<chd; nd++){
//			for(nt=0; nt<cht; nt++){
//				for(ns=0; ns<chs; ns++){
//					for(nh=0; nh<chh; nh++){
						for(nf1=0; nf1<chf; nf1++){
							for(nf2=0; nf2<chf; nf2++){
								if(core){
									for(e=0; e<che; e++){
										grp[nf1][nf2].SetPoint(e,enu[e],pe[nd][nh][nt][nf1][nf2][e]);
									}
									}
									else{
										for(a=0; a<cha; a++){
											grp[nf1][nf2].SetPoint(a,cosin[a],pa[nd][nh][nt][nf1][nf2][a]);
										}
									}
								grp[nf1][nf2].SetLineColor(col[nf1][nf2]);
								grp[nf1][nf2].SetLineStyle(sh[nf1][nf2]);
								grp[nf1][nf2].SetLineWidth(w[nf1][nf2]);
							}
						}
						for(ab=0; ab<3; ab++){
							switch(ab){
								case 0:
									nf01=0;
									nf02=0;
									break;
								case 1:
									nf01=0;
									nf02=1;
									break;
								case 2:
									nf01=1;
									nf02=0;
									break;
							}
							c.cd();
							if(core){
								grp[nf01][nf02].GetXaxis()->SetTitle("#font[132]{E_{#nu}  }");
								grp[nf01][nf02].GetXaxis()->SetRangeUser(1e-2,1e2);
								}
								else{
									grp[nf01][nf02].GetXaxis()->SetTitle("#font[132]{cos(#theta) }");
									grp[nf01][nf02].GetXaxis()->SetRangeUser(0,1);
								}
							grp[nf01][nf02].GetYaxis()->SetTitle("#font[132]{P_{#alpha#beta}}");
							grp[nf01][nf02].GetYaxis()->SetRangeUser(0,1);
							grp[nf01][nf02].Draw("AC");
							TLegend* leg=new TLegend(0.94,0.8,1.01,0.95);
							for(nf1=0; nf1<chf; nf1++){
								for(nf2=0; nf2<chf; nf2++){
									switch(ab){
										case 0:
											alphabeta=(nf1==nf2);
											break;
										case 1:
											alphabeta=(nf1<nf2);
											break;
										case 2:
											alphabeta=(nf1>nf2);
											break;
									}
									if(alphabeta){
										grp[nf1][nf2].Draw("CSAME");
										leg->AddEntry(&grp[nf1][nf2],Form("#font[132]{P_{%s%s}}",fn[nf1],fn[nf2]),"L");
										}
								}
							}
							leg->SetBorderSize(0);
							leg->Draw();
							if (core){
								c.SetLogx();
								}
							sprintf(pfn,"v%c/%s%c%c%c_%s",pr[core],den[nd],t[nt],sa[ns],h[nh],abn[ab]);
							sprintf(nof,"%s%s.eps",nod,pfn);
							c.Print((const char*)nof);
							delete leg;
						}
//					}
//				}
//			}
//		}
//	}
}
