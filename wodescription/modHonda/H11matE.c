#include "TStyle.h"

void SetStyle(){
	gStyle->SetFillColor(0);
	gStyle->SetFrameLineWidth(1);
	gStyle->SetPadLeftMargin(0.075);
	gStyle->SetPadRightMargin(0.007);
	gStyle->SetPadTopMargin(0.005);		
	gStyle->SetPadBottomMargin(0.08);
	gStyle->SetTitleOffset(1.05,"Y");
	gStyle->SetTitleOffset(1.15,"X");
//	gStyle->SetTextFont(132);
}

void H11matE(){
	
	const int chd=5,chs=2,chh=2,chf=3,cht=2,che=100,cha=2;
	const char *nid="../../fortran/Output/spectra/",*nod="../pictures/spectra/";
	const char nsp[5]="H11x",den[chd][4]={"wno","vac","2lm","7lm","mat"},sa[chs]={'F','V'},h[chh]={'n','i'},f[chf]={'e','m','t'},t[cht]={'n','a'};
	const char dn[chd][20]={"with no oscillation","vacuum","2LEM","7LEM","PREM"},hn[chh][3]={"NH","IH"},fn[chf][5]={"e","#mu","#tau"},tn[cht][8]={"#nu","#bar#nu"};
	char nof[256],pfn[256];
	FILE *f140=0;
	double sp[chd][chs][chh][chf][cht][che][cha],x,y;
	const int col[chf][cht]={{4,6},{1,2},{8,42}},sh[chf][cht]={{9,3},{1,7},{4,6}},w[chf][cht]={{1,2},{1,2},{2,2}};
	int chfa,e,a,nd,ns,nh,nf,nt,n,ndr;
	
	TCanvas c("c","Canvas",1200,800);
	TGraph grsp[chf][cht];
	
	SetStyle();
	
	nd=1;

//	for(nd=0; nd<chd; nd++){
		if(nd){
			chfa=chf;
			}
			else{
				chfa=chf-1;
			}
		for(ns=0; ns<chs; ns++){
			for(nh=0; nh<chh; nh++){
				for(nf=0; nf<chfa; nf++){
					for(nt=0; nt<cht; nt++){
						sprintf(pfn,"%s%c%s%c%c_m",den[nd],h[nh],nsp,f[nf],t[nt]);
						//sprintf(pfn,"%s%s%c%c%c%c",den[nd],nsp,sa[ns],h[nh],f[nf],t[nt]);
						sprintf(nof,"%s%s.dat",nid,pfn);
						f140=fopen(nof,"r");
						for(e=0; e<che; e++){
							for(a=0; a<cha; a++){
								fscanf(f140,"%le",&(sp[nd][ns][nh][nf][nt][e][a]));
							}
						}
						fclose(f140);
					}
				}
			}
		}
//	}
	
	for(ndr=0; ndr<2; ndr++){
		//for(nd=0; nd<chd; nd++){
			if(nd){
				chfa=chf;
				}
				else{
					chfa=chf-1;
				}
			for(ns=0; ns<chs; ns++){
				for(nh=0; nh<chh; nh++){
					c.cd();
					for(nf=0; nf<chfa; nf++){
						for(nt=0; nt<cht; nt++){
							for(e=0; e<che; e++){
								x=sp[nd][ns][nh][nf][nt][e][0];
								y=x**3*sp[nd][ns][nh][nf][nt][e][1];
								grsp[nf][nt].SetPoint(e,x,y);
							}
						}
					}
					grsp[1][0].GetXaxis()->SetTitle("#font[132]{E_{#nu} (GeV)}");
					grsp[1][0].GetXaxis()->SetRangeUser(1e-1,1.1e4);
					grsp[1][0].GetYaxis()->SetTitle("#font[132]{E_{#nu}^{3} #Phi_{#nu}(E_{#nu}) (GeV^{2} s^{-1} cm^{-2})}");
					grsp[1][0].GetYaxis()->SetRangeUser(3e-4,5e-2);
					grsp[1][0].Draw("AC");
					for(nf=0; nf<chfa; nf++){
						for(nt=0; nt<cht; nt++){
							grsp[nf][nt].SetLineColor(col[nf][nt]);
							grsp[nf][nt].SetLineStyle(sh[nf][nt]);
							grsp[nf][nt].SetLineWidth(w[nf][nt]);
							grsp[nf][nt].Draw("CSAME");
						}
					}
					nt=0;
					if(!nd){
						TLegend* legl=new TLegend(0.24,0.32,0.47,0.45);
						}
						else{
							TLegend* legl=new TLegend(0.24,0.25,0.47,0.45);
						}
					for(nf=0; nf<chfa; nf++){
						legl->AddEntry(&grsp[nf][nt],Form("#font[132]{%s_{%s}}",tn[nt],fn[nf]),"L");
					}
					nt=1;
					if(!nd){
						TLegend* legr=new TLegend(0.33,0.32,0.56,0.45);
						}
						else{
							TLegend* legr=new TLegend(0.33,0.25,0.56,0.45);
						}
					for(nf=0; nf<chfa; nf++){
						legr->AddEntry(&grsp[nf][nt],Form("#font[132]{%s_{%s}}",tn[nt],fn[nf]),"L");
					}
					legl->SetBorderSize(0);
					legl->Draw();
					legr->SetBorderSize(0);
					legr->Draw();
					c.SetLogx();
					c.SetLogy();
					sprintf(pfn,"%s%s%c",nsp,den[nd],h[nh]);
					//sprintf(pfn,"%s%s%c%c",nsp,den[nd],sa[ns],h[nh]);
					sprintf(nof,"%s%s.eps",nod,pfn);
					c.Print((const char*)nof);
					delete legl;
					delete legr;
				}	
			}
		//}
	}
}
