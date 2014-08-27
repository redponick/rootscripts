#include "TStyle.h"

void SetStyle(){
	gStyle->SetFillColor(0);
	gStyle->SetFrameLineWidth(1);
	gStyle->SetPadLeftMargin(0.07);
	gStyle->SetPadRightMargin(0.007);
	gStyle->SetPadTopMargin(0.005);		
	gStyle->SetPadBottomMargin(0.08);
	gStyle->SetTitleOffset(1,"Y");
	gStyle->SetTitleOffset(1.15,"X");
//	gStyle->SetTextFont(132);
}

void H11rapE(){
	
	const int chd=5,chda=3,chh=2,chf=3,cht=2,che=100,cha=2;
	const char *nid="../../fortran/Output/spectra/",*nod="../pictures/spectra/";
	const char nsp[5]="H11x",den[chd][4]={"wno","vac","2lm","7lm","mat"},h[chh]={'n','i'},f[chf]={'e','m','t'},t[cht]={'n','a'};
	const char dn[chd][20]={"with no oscillation","vacuum","2LEM","7LEM","PREM"},hn[chh][3]={"NH","IH"},fn[chf][5]={"e","#mu","#tau"},tn[cht][8]={"#nu","#bar#nu"};
	char nof[256],pfn[256];
	FILE *f140=0;
	double sp[chd][chh][chf][cht][che][cha];
	const int col[chda][chh]={{4,6},{1,2},{8,42}},sh[chda][chh]={{9,3},{1,7},{4,6}},w[chda][chh]={{1,2},{1,2},{2,2}};
	int chfa,e,a,nd,nh,nf,nt,ndr;
	
	TCanvas c("c","Canvas",1200,800);
	TGraph grrat[chda][chh][chf][cht];
	
	SetStyle();
	
	chfa=chf-1;
	
	for(nd=0; nd<chda; nd++){
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
		for(nf=0; nf<chfa; nf++){
			for(nt=0; nt<cht; nt++){
				c.cd();
				for(nd=1; nd<chda; nd++){
					for(nh=0; nh<chh; nh++){
						for(e=0; e<che; e++){
							grrat[nd][nh][nf][nt].SetPoint(e,sp[nd][nh][nf][nt][e][0],sp[nd][nh][nf][nt][e][1]/sp[0][nh][nf][nt][e][1]);
						}
					}
				}
				grrat[1][0][nf][nt].GetXaxis()->SetTitle("#font[132]{E_{#nu} (GeV)}");
				grrat[1][0][nf][nt].GetXaxis()->SetRangeUser(1e-1,1.1e4);
				grrat[1][0][nf][nt].GetYaxis()->SetTitle(Form("#font[132]{#Phi_{#nu}^{osc}(E_{#nu})/#Phi_{#nu}^{%s}(E_{#nu})}",den[0]));
				if(!nf){
					grrat[1][0][nf][nt].GetYaxis()->SetRangeUser(0.87,1.22);
					}
					else{
						grrat[1][0][nf][nt].GetYaxis()->SetRangeUser(0.5,1.05);
					}
				grrat[1][0][nf][nt].Draw("AC");
				if(!nt){
					if(!nf){
						TLegend* legname=new TLegend(0.15,0.8,0.25,0.9);
						}
						else{
							TLegend* legname=new TLegend(0.15,0.805,0.25,0.89);
						}
					}
					else{
						if(!nf){
							TLegend* legname=new TLegend(0.15,0.825,0.25,0.895);
							}
							else{
								TLegend* legname=new TLegend(0.15,0.82,0.25,0.89);
							}
					}
				legname->AddEntry((TObject*)0,Form("#font[132]{%s_{%s}}",tn[nt],fn[nf]),"");
				legname->SetBorderSize(0);
				legname->Draw();
				TLegend* leg=new TLegend(0.7,0.2,0.85,0.4);
				for(nd=1; nd<chda; nd++){
					for(nh=0; nh<chh; nh++){
						grrat[nd][nh][nf][nt].SetLineColor(col[nd-1][nh]);
						grrat[nd][nh][nf][nt].SetLineStyle(sh[nd-1][nh]);
						grrat[nd][nh][nf][nt].SetLineWidth(w[nd-1][nh]);
						grrat[nd][nh][nf][nt].Draw("CSAME");
						leg->AddEntry(&grrat[nd][nh][nf][nt],Form("#font[132]{%s, %s}",dn[nd],hn[nh]),"L");
					}
				}
				leg->SetBorderSize(0);
				leg->Draw();
				c.SetLogx();
				sprintf(pfn,"%svs%s%c%c",nsp,den[0],f[nf],t[nt]);
				sprintf(nof,"%s%s.eps",nod,pfn);
				c.Print((const char*)nof);
				delete legname;
				delete leg;
			}
		}
	}
}
