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

void H11nhrE(){
	
	const int chd=5,chh=2,chf=3,cht=2,che=100,cha=2;
	const char *nid="../../fortran/Output/spectra/",*nod="../pictures/spectra/";
	const char nsp[5]="H11x",den[chd][4]={"wno","vac","2lm","7lm","mat"},h[chh]={'n','i'},f[chf]={'e','m','t'},t[cht]={'n','a'};
	const char dn[chd][20]={"with no oscillation","vacuum","2LEM","7LEM","PREM"},hn[chh][3]={"NH","IH"},fn[chf][5]={"e","#mu","#tau"},tn[cht][8]={"#nu","#bar#nu"};
	char nof[256],pfn[256];
	FILE *f140=0;
	double sp[chd][chh][chf][cht][che][cha];
	const int col[chf][cht]={{4,6},{1,2},{8,42}},sh[chf][cht]={{9,3},{1,7},{4,6}},w[chf][cht]={{1,2},{1,2},{2,2}};
	int e,a,nd,nh,nf,nt,ndr;
	
	TCanvas c("c","Canvas",1200,800);
	TGraph grsph[chf][cht];
	
	SetStyle();
	
	for(nd=0; nd<chd; nd++){
		if(nd){
			chfa=chf;
			}
			else{
				chfa=chf-1;
			}
		for(nh=0; nh<chh; nh++){
			for(nf=0; nf<chfa; nf++){
				for(nt=0; nt<cht; nt++){
					sprintf(pfn,"%s%c%s%c%c",den[nd],h[nh],nsp,f[nf],t[nt]);
					sprintf(nof,"%s%s.dat",nid,pfn);
					f140=fopen(nof,"r");
					for(e=0; e<che; e++){
						for(a=0; a<cha; a++){
							fscanf(f140,"%le",&(sp[nd][nh][nf][nt][e][a]));
						}
					}
					fclose(f140);
				}
			}
		}
	}
	
	for(ndr=0; ndr<2; ndr++){
		for(nd=1; nd<chd; nd++){
			for(nf=0; nf<chf; nf++){
				for(nt=0; nt<cht; nt++){
					for(e=0; e<che; e++){
						grsph[nf][nt].SetPoint(e,sp[nd][0][nf][nt][e][0],sp[nd][1][nf][nt][e][1]/sp[nd][0][nf][nt][e][1]);
					}
				}
			}
			grsph[1][0].GetXaxis()->SetTitle("#font[132]{E_{#nu} (GeV)}");
			grsph[1][0].GetXaxis()->SetRangeUser(1e-1,1.1e4);
			grsph[1][0].GetYaxis()->SetTitle("#font[132]{#Phi_{#nu}^{IH}(E_{#nu})/#Phi_{#nu}^{NH}(E_{#nu})}");
			grsph[1][0].GetYaxis()->SetRangeUser(0.82,1.23);
			grsph[1][0].Draw("AC");
			for(nf=0; nf<chf; nf++){
				for(nt=0; nt<cht; nt++){
					grsph[nf][nt].SetLineColor(col[nf][nt]);
					grsph[nf][nt].SetLineStyle(sh[nf][nt]);
					grsph[nf][nt].SetLineWidth(w[nf][nt]);
					grsph[nf][nt].Draw("CSAME");
				}
			}
			nt=0;
			TLegend* legl=new TLegend(0.67,0.75,0.9,0.95);
			for(nf=0; nf<chf; nf++){
				legl->AddEntry(&grsph[nf][nt],Form("#font[132]{%s_{%s}}",tn[nt],fn[nf]),"L");
			}
			nt=1;
			TLegend* legr=new TLegend(0.76,0.75,0.99,0.95);
			for(nf=0; nf<chf; nf++){
				legr->AddEntry(&grsph[nf][nt],Form("#font[132]{%s_{%s}}",tn[nt],fn[nf]),"L");
			}
			legl->SetBorderSize(0);
			legl->Draw();
			legr->SetBorderSize(0);
			legr->Draw();
			c.SetLogx();
			sprintf(pfn,"%snhr%s",nsp,den[nd]);
			sprintf(nof,"%s%s.eps",nod,pfn);
			c.Print((const char*)nof);
			delete legl;
			delete legr;
		}
	}
}
