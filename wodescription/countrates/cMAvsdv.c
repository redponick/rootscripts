#include "TStyle.h"

void SetStyle(){
	gStyle->SetFillColor(0);
	gStyle->SetFrameLineWidth(1);
	gStyle->SetPadLeftMargin(0.095);
	gStyle->SetPadRightMargin(0.005);
	gStyle->SetPadTopMargin(0.01);	
	gStyle->SetPadBottomMargin(0.05);
	gStyle->SetTitleOffset(1.05,"Y");
	gStyle->SetTitleOffset(0.5,"X");
	gStyle->SetTextFont(132);
}

void cMAvsdv(){
	
	const int chv=5,chs=6,chf=2,chp=100,cha=2;
	const char nip[14]="QESintP/Ewnon",*nex="../../fortran/Output/";
	const char v[chv][5]={"0.90","0.95","1.10","1.20","1.35"},s[chs]={'c','v','l','h','i','f'},f[chf]={'e','m'};
	char *name,cn[256];
	FILE *f100=0;
	double dn[chs][chf][chv][chp][cha];
	const int col[chv]={2,2,8,4,6},cf[chf]={3,5},sh[chf]={3,1},w[chf]={2,1};
	int p,a,nm,nf,nv,,ns,nd;
	
	TCanvas c("c","Canvas",1200,800);
	TGraphAsymmErrors grdnc[chf][chv];
	TGraphAsymmErrors grdnv[chf];
	TGraph grdncc[chf][chv];
	
	SetStyle();
	
	for(nf=0; nf<chf; nf++){
		for(ns=0; ns<chs; ns++){
			for(nv=0; nv<chv; nv++){	
				sprintf(cn,"%s%s%c%s_%c.dat",nex,nip,f[nf],v[nv],s[ns]);
				f100=fopen(cn,"r");
				for(p=0; p<chp; p++){
					for(a=0; a<cha; a++){
						fscanf(f100,"%le",&(dn[ns][nf][nv][p][a]));
					}
				}
				fclose(f100);
			}
		}
	}
	
	for(nd=0; nd<2; nd++){
		c.cd();
		for(nf=0; nf<chf; nf++){
			for(p=0; p<chp; p++){
				for(nv=0; nv<chv; nv++){
					grdncc[nf][nv].SetPoint(p,dn[0][nf][nv][p][0],dn[0][nf][nv][p][1]/dn[1][nf][1][p][1]);
					grdnc[nf][nv].SetPoint(p,dn[0][nf][nv][p][0],dn[0][nf][nv][p][1]/dn[1][nf][1][p][1]);
					grdnc[nf][nv].SetPointError(p,0,0,(dn[0][nf][nv][p][1]-dn[4][nf][nv][p][1])/dn[1][nf][1][p][1],(dn[5][nf][nv][p][1]-dn[0][nf][nv][p][1])/dn[1][nf][1][p][1]);
				}
					grdnv[nf].SetPoint(p,dn[0][nf][1][p][0],dn[1][nf][1][p][1]/dn[1][nf][1][p][1]);
					//grdnv[nf].SetPointError(p,0,0,(dn[1][nf][1][p][1]-dn[2][nf][1][p][1])/dn[1][nf][1][p][1],(dn[3][nf][1][p][1]-dn[1][nf][1][p][1])/dn[1][nf][1][p][1]);
			}
			for(nv=0; nv<chv; nv++){
				grdnc[nf][nv].RemovePoint(12);
				grdnc[nf][nv].RemovePoint(22);
				grdnc[nf][nv].RemovePoint(32);
				grdnc[nf][nv].RemovePoint(42);
				grdnc[nf][nv].RemovePoint(45);
				grdnc[nf][nv].RemovePoint(68);
				grdnc[nf][nv].RemovePoint(73);
				grdnc[nf][nv].RemovePoint(81);
				grdnc[nf][nv].RemovePoint(84);
				grdnc[nf][nv].RemovePoint(87);
				grdncc[nf][nv].RemovePoint(12);
				grdncc[nf][nv].RemovePoint(22);
				grdncc[nf][nv].RemovePoint(32);
				grdncc[nf][nv].RemovePoint(42);
				grdncc[nf][nv].RemovePoint(45);
				grdncc[nf][nv].RemovePoint(68);
				grdncc[nf][nv].RemovePoint(73);
				grdncc[nf][nv].RemovePoint(81);
				grdncc[nf][nv].RemovePoint(84);
				grdncc[nf][nv].RemovePoint(87);
			}
		}
		grdnc[0][1].GetXaxis()->SetTitle("#font[132]{P_{lep} (GeV)}");
		grdnc[0][1].GetYaxis()->SetTitle("#font[132]{#frac{#Phi_{lep}^{curr}}{#Phi_{lep}^{eff}}}");
		grdnc[0][1].GetXaxis()->SetRangeUser(9e-2,5e1);
		grdnc[0][1].GetYaxis()->SetRangeUser(0.6,1.65);
		for(nf=0; nf<chf; nf++){
			for(nv=0; nv<chv; nv++){
				grdnc[nf][nv].SetLineColor(0);
			}
		}
		grdnc[0][1].Draw("AP");
		for(nf=0; nf<chf; nf++){
			grdnc[nf][1].SetFillColor(col[1]);
			grdnc[nf][1].Draw("3SAME");
			grdnc[nf][3].SetFillColor(col[3]);
			grdnc[nf][3].Draw("3SAME");
			grdnc[nf][4].SetFillColor(col[4]);
			grdnc[nf][4].Draw("3SAME");
		}
		for(nf=0; nf<chf; nf++){
			for(nv=0; nv<chv; nv++){
				grdncc[nf][nv].SetLineWidth(w[nf]);
				grdncc[nf][nv].SetLineColor(cf[nf]);
				grdncc[nf][nv].SetLineStyle(sh[nf]);
			}
			grdncc[nf][1].Draw("CSAME");
			grdncc[nf][3].Draw("CSAME");
			grdncc[nf][4].Draw("CSAME");
			grdnv[nf].SetLineColor(1);
			grdnv[nf].Draw("CSAME");
			//grdnv[nf].SetFillColor(5);
			//grdnv[nf].Draw("3SAME");
		}
		TLegend* leg=new TLegend(0.1,0.76,0.6,0.95);
		leg->AddEntry(&grdnc[0][1],"#font[132]{M_{A}=0.973 GeV (world averaged value)}","F");
		leg->AddEntry(&grdnc[0][3],"#font[132]{M_{A}=1.20 GeV (K2K best fit, SK default)}","F");
		leg->AddEntry(&grdnc[0][4],"#font[132]{M_{A}=1.35 GeV (MiniBooNE 2010 best fit)}","F");
		leg->AddEntry(&grdnv[0],"#font[132]{variable M_{A}^{eff}, M_{A(0)}=0.964 GeV}","L");
		leg->SetBorderSize(0);
		leg->Draw();
		TLegend* leglep=new TLegend(0.15,0.65,0.4,0.75);
		leglep->AddEntry(&grdncc[0][2],"#font[132]{e^{-} +  e^{+}}","L");
		leglep->AddEntry(&grdncc[1][2],"#font[132]{#mu^{-} + #mu^{+}}","L");
		leglep->SetBorderSize(0);
		leglep->Draw();
		c.SetLogx();
		sprintf(cn,"../pictures/qesintp/cvsvwnon.eps");
		c.Print((const char*)cn);
		delete leg;
		delete leglep;
	}
}
