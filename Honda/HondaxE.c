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

void HondaxE(){
	
	const int chf=2,cht=2,che=101,cha=3;
	const char nsp[5]="H11x",*nex="../../fortran/Output/spectra/";
	const char f[chf]={'e','m'},t[cht]={'n','a'},fn[chf][5]={"e","#mu"},tn[cht][8]={"#nu","#bar#nu"};
	char *name,cn[256];
	FILE *f140=0;
	double sp[chf][cht][che][cha];
	const int col[chf][cht]={{3,1},{2,4}},stf[chf][cht]={{3205,3259},{3245,3254}};
	int e,a,nf,nt,n,nd;
	
	TCanvas c("c","Canvas",1200,800);
	TGraphErrors grspf[chf][cht];
	TGraph grsp[chf][cht][cha-1];
	
	SetStyle();

	for(nf=0; nf<chf; nf++){
		for(nt=0; nt<cht; nt++){
			sprintf(cn,"%s%ssp%c%c.dat",nex,nsp,f[nf],t[nt]);
			f140=fopen(cn,"r");
			for(e=0; e<che; e++){
				for(a=0; a<cha; a++){
					fscanf(f140,"%le",&(sp[nf][nt][e][a]));
				}
			}
			fclose(f140);
		}
	}

	for(nd=0; nd<2; nd++){
		c.cd();
		for(nf=0; nf<chf; nf++){
			for(nt=0; nt<cht; nt++){
				for(e=1; e<che; e++){
					grspf[nf][nt].SetPoint(e-1,sp[nf][nt][e][0],0.5*(sp[nf][nt][e][1]+sp[nf][nt][e][2]));
					grspf[nf][nt].SetPointError(e-1,0,0.5*(sp[nf][nt][e][1]-sp[nf][nt][e][2]));
					grsp[nf][nt][0].SetPoint(e-1,sp[nf][nt][e][0],sp[nf][nt][e][1]);
					grsp[nf][nt][1].SetPoint(e-1,sp[nf][nt][e][0],sp[nf][nt][e][2]);
				}
			}
		}
		grspf[0][0].GetXaxis()->SetTitle("#font[132]{E_{#nu} (GeV)}");
		grspf[0][0].GetXaxis()->SetRangeUser(1e-1,1.1e3);
		grspf[0][0].GetYaxis()->SetTitle("#font[132]{E_{#nu}^{3} #Phi_{#nu}(E_{#nu},#theta) (GeV^{2} s^{-1} sr^{-1} cm^{-2})}");
		grspf[0][0].GetYaxis()->SetRangeUser(2e-4,7e-2);
		grspf[0][0].SetFillColor(col[0][0]);
		grspf[0][0].SetFillStyle(stf[0][0]);
		grspf[0][0].Draw("A3");
		for(nf=chf-1; nf>=0; nf--){
			grspf[nf][0].SetFillColor(col[nf][0]);
			grspf[nf][0].SetFillStyle(stf[nf][0]);
			grspf[nf][0].Draw("3SAME");
			grspf[nf][1].SetFillColor(col[nf][1]);
			grspf[nf][1].SetFillStyle(stf[nf][1]);
			grspf[nf][1].Draw("3SAME");
			for(nt=0; nt<cht; nt++){
				for(a=1; a<cha; a++){
					grsp[nf][nt][a-1].SetLineColor(col[nf][nt]);
					grsp[nf][nt][a-1].Draw("CSAME");
				}
			}
		}
		TLegend* legname=new TLegend(0.1,0.85,0.35,0.95);
		legname->AddEntry((TObject*)0,"#font[132]{cos#theta #in [-1,1]}","");
		legname->SetBorderSize(0);
		legname->Draw();
		nt=0;
		TLegend* legl=new TLegend(0.27,0.2,0.47,0.37);
		for(nf=0; nf<chf; nf++){
			legl->AddEntry(&grspf[nt][nf],Form("#font[132]{%s_{%s}}",tn[nt],fn[nf]),"F");
		}
		nt=1;
		TLegend* legr=new TLegend(0.42,0.2,0.62,0.37);
		for(nf=0; nf<chf; nf++){
			legr->AddEntry(&grspf[nt][nf],Form("#font[132]{%s_{%s}}",tn[nt],fn[nf]),"F");
		}
		legl->SetBorderSize(0);
		legl->Draw();
		legr->SetBorderSize(0);
		legr->Draw();
		c.SetLogx();
		c.SetLogy();
		sprintf(cn,"../pictures/spectra/H11xE.eps");
		c.Print((const char*)cn);
		delete legname;
		delete legl;
		delete legr;
	}
}
