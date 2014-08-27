#include "TStyle.h"

void SetStyle(){
	gStyle->SetFillColor(0);
	gStyle->SetFrameLineWidth(1);
	gStyle->SetPadLeftMargin(0.06);
	gStyle->SetPadRightMargin(0.005);
	gStyle->SetPadTopMargin(0.01);		
	gStyle->SetPadBottomMargin(0.07);
	gStyle->SetTitleOffset(0.7,"Y");
	gStyle->SetTitleOffset(0.8,"X");
//	gStyle->SetTextFont(132);
//	gStyle->SetPalette(1);
}

void oscmat3(){

	const int chd=5,chh=2,chs=2,chf=3,cht=2,che=50,cha=50;
	const char *nid="../../fortran/Output/probanu/",*nod="../pictures/probanu/";
	const char den[chd][4]={"wno","vac","2lm","7lm","mat"},h[chh]={'n','i'},sa[chs]={'F','V'},f[chf]={'e','m','t'},t[cht]={'n','a'},fn[chf][5]={"e","#mu","#tau"},abn[3][3]={"aa","ab","ba"};
    char nof[256],pfn[256];
	FILE *f101=0;
	double prcos,prenu,cosin[cha],enu[che],p[chd][chh][cht][chf][chf][che][cha];
	const int col[chf][chf]={{2,4,2},{4,4,1},{2,1,1}},sh[chf][chf]={{9,3,9},{3,3,1},{9,1,1}},w[chf][chf]={{1,2,1},{2,2,1},{1,1,1}};
	int core,ab,e,a,nd,nh,ns,nf1,nf2,nt,nf01,nf02,ndr;
	bool alphabeta;
	
	TCanvas c("c","Canvas",1200,800);
	TGraph grp[chf][chf];
	TGraph2D grpce[chf][chf];
	
	nd=1;
	
	core=0;                                                             //0 - var cos & E, 1 - var cos, 2 - var E
	if(!core){
		SetStyle();
	}
	
	nt=0;
	nh=0;
	ns=0;
	
//	for(nd=1; nd<chd; nd++){
//		for(nt=0; nt<cht; nt++){
//			for(nh=0; nh<chh; nh++){
//				for(ns=0; ns<chs; ns++){
					sprintf(pfn,"%s3%c%c%c",den[nd],t[nt],sa[ns],h[nh]);
					sprintf(nof,"%s%s.dat",nid,pfn);
					f101=fopen(nof,"r");
					for(e=0; e<che; e++){
						for(a=0; a<cha; a++){
							fscanf(f101,"%le",&prenu);
							if(nd!=1){
								enu[e]=1e-9*prenu;
								}
								else{
									enu[e]=prenu;
								}
							fscanf(f101,"%le",&prcos);
							cosin[a]=-prcos;
							for(nf1=0; nf1<chf; nf1++){
								for(nf2=0; nf2<chf; nf2++){
									fscanf(f101,"%le",&(p[nd][nh][nt][nf1][nf2][e][a]));
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
//				for(nh=0; nh<chh; nh++){
//					for(ns=0; ns<chs; ns++){
						for(nf1=0; nf1<chf; nf1++){
							for(nf2=0; nf2<chf; nf2++){
								switch(core){
									case 0:
										for(e=0; e<che; e++){
											for(a=0; a<cha; a++){
												grpce[nf1][nf2].SetPoint(a*che+e,cosin[a],enu[e],p[nd][nh][nt][nf1][nf2][e][a]);
											}
										}
										c.cd();
										grpce[nf1][nf2].GetXaxis()->SetTitle("#font[132]{cos(#theta)  }");
										grpce[nf1][nf2].GetXaxis()->SetRangeUser(0,1);
										grpce[nf1][nf2].GetYaxis()->SetTitle("#font[132]{E_{#nu}}");
										grpce[nf1][nf2].GetYaxis()->SetRangeUser(1e-1,1e1);
										grpce[nf1][nf2].Draw("COLZ");
										c.SetLogy();
										sprintf(pfn,"%s3D%c%c%c_%c%c",den[nd],t[nt],sa[ns],h[nh],f[nf1],f[nf2]);
										sprintf(nof,"%s%s.eps",nod,pfn);
										c.Print((const char*)nof);
										break;
									case 1:
										for(a=0; a<cha; a++){
											grp[nf1][nf2].SetPoint(a,cosin[a],p[nd][nh][nt][nf1][nf2][0][a]);
										}
										break;
									case 2:
										for(e=0; e<che; e++){
											grp[nf1][nf2].SetPoint(e,enu[e],p[nd][nh][nt][nf1][nf2][e][cha-1]);
										}
										break;
								}
								if(core){
									grp[nf1][nf2].SetLineColor(col[nf1][nf2]);
									grp[nf1][nf2].SetLineStyle(sh[nf1][nf2]);
									grp[nf1][nf2].SetLineWidth(w[nf1][nf2]);
								}
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
							switch(core){
								case 0:
									break;
								case 1:
									grp[nf01][nf02].GetXaxis()->SetTitle("#font[132]{cos(#theta)  }");
									grp[nf01][nf02].GetXaxis()->SetRangeUser(0,1);
									break;
								case 2:
									grp[nf01][nf02].GetXaxis()->SetTitle("#font[132]{E_{#nu}}");
									grp[nf01][nf02].GetXaxis()->SetRangeUser(1e-1,1e1);
									break;
							}
							if(core){
								grp[nf01][nf02].GetYaxis()->SetTitle("#font[132]{P_{#alpha#beta}}");
								grp[nf01][nf02].GetYaxis()->SetRangeUser(0,1);
								grp[nf01][nf02].Draw("AC");
								TLegend* leg=new TLegend(0.15,0.8,0.22,0.95);
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
								if (core==2){
									c.SetLogx();
									sprintf(pfn,"%sE%c%c%c_%s",den[nd],t[nt],sa[ns],h[nh],abn[ab]);
									}
									else{
										sprintf(pfn,"%sc%c%c%c_%s",den[nd],t[nt],sa[ns],h[nh],abn[ab]);
									}
								sprintf(nof,"%s%s.eps",nod,pfn);
								c.Print((const char*)nof);
								delete leg;
							}
						}
//					}
//				}
//			}
//		}
//	}
}
