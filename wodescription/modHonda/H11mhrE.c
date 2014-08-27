#include "TStyle.h"

void SetStyle(){
	gStyle->SetFillColor(0);
	gStyle->SetFrameLineWidth(1);
	gStyle->SetPadLeftMargin(0.05);
	gStyle->SetPadRightMargin(0.007);
	gStyle->SetPadTopMargin(0.005);		
	gStyle->SetPadBottomMargin(0.13);
	gStyle->SetTitleOffset(0.3,"Y");
	gStyle->SetTitleOffset(0.93,"X");
//	gStyle->SetTextFont(132);
}

void H11mhrE(){
	
	const int chd=5,chh=2,chf=3,cht=2,che=100,cha=2;
	const char *nid="../../fortran/Output/spectra/",*nod="../pictures/specnew/";
	const char nsp[5]="H11x",den[chd][4]={"wno","vac","2lm","7lm","mat"},h[chh]={'n','i'},f[chf]={'e','m','t'},t[cht]={'n','a'};
	const char dn[chd][20]={"with no oscillation","vacuum","2LEM","7LEM","PREM"},hn[chh][3]={"NH","IH"},fn[chf][5]={"e","#mu","#tau"},tn[cht][8]={"#nu","#bar#nu"};
	char nof[256],pfn[256];
	FILE *f140=0;
	double sp[chd][chh][chf][cht][che][cha],x,y;
	const int col[chf][cht]={{4,6},{1,2},{8,42}},sh[chf][cht]={{9,3},{1,7},{4,6}},w[chf][cht]={{1,2},{1,2},{2,2}};
	int e,a,nd,nh,nf,nt,n,ndr;
	
	TCanvas c("c","Canvas",1200,800);
	TGraph grsp[chf][cht],grsph[chf][cht];
	
	SetStyle();

	nd=4;
	//for(nd=1; nd<chd; nd++){
		for(nh=0; nh<chh; nh++){
			for(nf=0; nf<chf; nf++){
				for(nt=0; nt<cht; nt++){
					sprintf(pfn,"%s%c%s%c%c",den[nd],h[nh],nsp,f[nf],t[nt]);
					sprintf(nof,"%s%s_m.dat",nid,pfn);
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
	//}
	
	//for(nd=1; nd<chd; nd++){
		c.Clear();
		c.Divide(1,2,0,0);
		for(ndr=0; ndr<2; ndr++){
			c.cd(1);
			for(nf=0; nf<chf; nf++){
				for(nt=0; nt<cht; nt++){
					for(e=0; e<che; e++){
						x=sp[nd][0][nf][nt][e][0];
						y=x**3*sp[nd][0][nf][nt][e][1];
						grsp[nf][nt].SetPoint(e,x,y);
					}
				}
			}
			grsp[1][0].GetXaxis()->SetRangeUser(1e-1,1.1e3);
			grsp[1][0].GetYaxis()->SetLabelSize(0.04);
			grsp[1][0].GetYaxis()->SetTitle("#font[132]{E_{#nu}^{3} #Phi_{#nu}(E_{#nu}) (GeV^{2} s^{-1} cm^{-2})}");
			grsp[1][0].GetYaxis()->SetTitleSize(0.04);
			grsp[1][0].GetYaxis()->SetTitleOffset(0.65);
			grsp[1][0].GetYaxis()->SetRangeUser(3e-4,5e-2);
			grsp[1][0].Draw("AC");
			for(nf=0; nf<chf; nf++){
				for(nt=0; nt<cht; nt++){
					grsp[nf][nt].SetLineColor(col[nf][nt]);
					grsp[nf][nt].SetLineStyle(sh[nf][nt]);
					grsp[nf][nt].SetLineWidth(w[nf][nt]);
					grsp[nf][nt].Draw("CSAME");
				}
			}
			gPad->SetPad(0,0.35,0.995,0.995);
			gPad->SetLogx();
			gPad->SetLogy();
			c.cd(2);
			for(nf=0; nf<chf; nf++){
				for(nt=0; nt<cht; nt++){
					for(e=0; e<che; e++){
						grsph[nf][nt].SetPoint(e,sp[nd][0][nf][nt][e][0],sp[nd][1][nf][nt][e][1]/sp[nd][0][nf][nt][e][1]);
					}
				}
			}
			grsph[1][0].GetXaxis()->SetRangeUser(1e-1,1.1e3);
			grsph[1][0].GetXaxis()->SetLabelSize(0.07);
			grsph[1][0].GetXaxis()->SetTitle("#font[132]{E_{#nu} (GeV)}");
			grsph[1][0].GetXaxis()->SetTitleSize(0.08);
			grsph[1][0].GetYaxis()->SetLabelSize(0.07);
			grsph[1][0].GetYaxis()->SetTitle("#font[132]{#Phi_{#nu}^{IH}(E_{#nu})/#Phi_{#nu}^{NH}(E_{#nu})}");
			grsph[1][0].GetYaxis()->SetTitleSize(0.075);
			grsph[1][0].GetYaxis()->SetTitleOffset(0.35);
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
			gPad->SetPad(0,0,0.995,0.35);
			gPad->SetLogx();
			c.cd();
			TLegend* legname=new TLegend(0.07,0.85,0.15,0.98);
			legname->AddEntry((TObject*)0,"#font[132]{NH}","");
			legname->SetBorderSize(0);
			legname->Draw();
			nt=0;
			TLegend* legl=new TLegend(0.24,0.38,0.47,0.58);
			for(nf=0; nf<chf; nf++){
				legl->AddEntry(&grsp[nf][nt],Form("#font[132]{%s_{%s}}",tn[nt],fn[nf]),"L");
			}
			nt=1;
			TLegend* legr=new TLegend(0.33,0.38,0.56,0.58);
			for(nf=0; nf<chf; nf++){
				legr->AddEntry(&grsp[nf][nt],Form("#font[132]{%s_{%s}}",tn[nt],fn[nf]),"L");
			}
			legl->SetBorderSize(0);
			legl->Draw();
			legr->SetBorderSize(0);
			legr->Draw();
			sprintf(pfn,"%s%s",nsp,den[nd]);
			sprintf(nof,"%s%s.eps",nod,pfn);
			c.Print((const char*)nof);
			delete legname;
			delete legl;
			delete legr;	
		}
	//}
}
