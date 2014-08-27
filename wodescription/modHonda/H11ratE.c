#include "TStyle.h"

void SetStyle(){
	gStyle->SetFillColor(0);
	gStyle->SetFrameLineWidth(1);
	gStyle->SetPadLeftMargin(0.09);
	gStyle->SetPadRightMargin(0.007);
	gStyle->SetPadTopMargin(0.005);		
	gStyle->SetPadBottomMargin(0.09);
	gStyle->SetTitleOffset(0.65,"Y");
	gStyle->SetTitleOffset(1.15,"X");
//	gStyle->SetTextFont(132);
}

void H11ratE(){
	
	const int chd=3,chda=3,chh=2,chf=3,cht=2,che=100,cha=2;
	const char *nid="../../fortran/Output/spectra/",*nod="../pictures/specnew/";
	const char nsp[5]="H11x",den[chd][4]={"wno","vac",/*"2lm","7lm",*/"mat"},h[chh]={'n','i'},f[chf]={'e','m','t'},t[cht]={'n','a'};
	const char dn[chd][20]={"with no oscillation","vacuum",/*"2LEM","7LEM",*/"PREM"},hn[chh][3]={"NH","IH"},fn[chf][5]={"e","#mu","#tau"},tn[cht][8]={"#nu","#bar#nu"};
	char nof[256],pfn[256];
	FILE *f140=0;
	double sp[chd][chh][chf][cht][che][cha];
	const int col[chda][chh]={{4,6},{1,2},{8,42}},sh[chda][chh]={{9,3},{1,7},{4,6}},w[chda][chh]={{1,2},{1,2},{2,2}};
	int chfa,e,a,nd,nh,nf,nt,ndr;
	
	TCanvas c("c","Canvas",1200,800);
	TGraph grrat[chda][chh][chf][cht];
	
	SetStyle();
	
	chfa=chf-1;

	for(nh=0; nh<chh; nh++){
		for(nf=0; nf<chfa; nf++){
			for(nt=0; nt<cht; nt++){
				sprintf(pfn,"%s%c%s%c%c",den[0],h[nh],nsp,f[nf],t[nt]);
				sprintf(nof,"%s%s.dat",nid,pfn);
				f140=fopen(nof,"r");
				for(e=0; e<che; e++){
					for(a=0; a<cha; a++){
						fscanf(f140,"%le",&(sp[0][nh][nf][nt][e][a]));
					}
				}
				fclose(f140);
			}
		}
	}

	for(nd=1; nd<chda; nd++){
		for(nh=0; nh<chh; nh++){
			for(nf=0; nf<chfa; nf++){
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
	}
	
	c.Divide(2,2,0,0);
	for(ndr=0; ndr<2; ndr++){
		for(nf=0; nf<chfa; nf++){
			for(nt=0; nt<cht; nt++){
				c.cd(cht*nf+nt+1);
				for(nd=1; nd<chda; nd++){
					for(nh=0; nh<chh; nh++){
						for(e=0; e<che; e++){
							grrat[nd][nh][nf][nt].SetPoint(e,sp[nd][nh][nf][nt][e][0],sp[nd][nh][nf][nt][e][1]/sp[0][nh][nf][nt][e][1]);
						}
					}
				}
				grrat[1][0][nf][nt].GetXaxis()->SetRangeUser(1e-1,1.1e3);
				if(!nf){
					if(!nt){
						grrat[1][0][nf][nt].GetYaxis()->SetLabelSize(0.06);
						grrat[1][0][nf][nt].GetYaxis()->SetTitle(Form("#font[132]{#Phi_{#nu}^{osc}(E_{#nu})/#Phi_{#nu}^{%s}(E_{#nu})}",den[0]));
						grrat[1][0][nf][nt].GetYaxis()->SetTitleSize(0.07);
					}
					grrat[1][0][nf][nt].GetYaxis()->SetRangeUser(0.87,1.22);
					}
					else{
						grrat[1][0][nf][nt].GetXaxis()->SetTitle("#font[132]{E_{#nu} (GeV)}");
						grrat[1][0][nf][nt].GetXaxis()->SetTitleSize(0.04);
						grrat[1][0][nf][nt].GetYaxis()->SetRangeUser(0.5,1.05);
					}
				grrat[1][0][nf][nt].Draw("AC");
				for(nd=1; nd<chda; nd++){
					for(nh=0; nh<chh; nh++){
						grrat[nd][nh][nf][nt].SetLineColor(col[nd-1][nh]);
						grrat[nd][nh][nf][nt].SetLineStyle(sh[nd-1][nh]);
						grrat[nd][nh][nf][nt].SetLineWidth(w[nd-1][nh]);
						grrat[nd][nh][nf][nt].Draw("CSAME");
					}
				}
				if(!nf){
					if(!nt){
						TLegend* legname00=new TLegend(0.2,0.71,0.3,0.91);
						legname00->AddEntry((TObject*)0,Form("#font[132]{%s_{%s}}",tn[nt],fn[nf]),"");
						legname00->SetBorderSize(0);
						legname00->Draw();
						gPad->SetPad(0,0.62,0.5,0.995);
						gPad->SetLogx();
						}
						else{
							TLegend* legname01=new TLegend(0.2,0.76,0.3,0.9);
							legname01->AddEntry((TObject*)0,Form("#font[132]{%s_{%s}}",tn[nt],fn[nf]),"");
							legname01->SetBorderSize(0);
							legname01->Draw();
							gPad->SetPad(0.5,0.62,0.995,0.995);
							gPad->SetLogx();
						}
					}
					else{
						if(!nt){
							TLegend* legname10=new TLegend(0.2,0.78,0.3,0.895);
							legname10->AddEntry((TObject*)0,Form("#font[132]{%s_{%s}}",tn[nt],fn[nf]),"");
							legname10->SetBorderSize(0);
							legname10->Draw();
							gPad->SetPad(0,0,0.5,0.62);
							gPad->SetLogx();
							}
							else{
								TLegend* legname11=new TLegend(0.2,0.81,0.3,0.9);
								legname11->AddEntry((TObject*)0,Form("#font[132]{%s_{%s}}",tn[nt],fn[nf]),"");
								legname11->SetBorderSize(0);
								legname11->Draw();
								gPad->SetPad(0.5,0,0.995,0.62);
								gPad->SetLogx();
							}
					}
			}
		}
		c.cd();
		TLegend* leg=new TLegend(0.82,0.1,0.97,0.3);
		for(nd=1; nd<chda; nd++){
			for(nh=0; nh<chh; nh++){
				leg->AddEntry(&grrat[nd][nh][0][0],Form("#font[132]{%s, %s}",dn[nd],hn[nh]),"L");
			}
		}
		leg->SetBorderSize(0);
		leg->Draw();
		sprintf(pfn,"%smatvs%s",nsp,den[0]);
		sprintf(nof,"%s%s.eps",nod,pfn);
		c.Print((const char*)nof);
		delete legname00;
		delete legname01;
		delete legname10;
		delete legname11;
		delete leg;
	}
}
