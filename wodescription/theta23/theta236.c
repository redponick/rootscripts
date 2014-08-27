#include "TStyle.h"

void SetStyle(){
	gStyle->SetFillColor(0);
	gStyle->SetFrameLineWidth(1);
	gStyle->SetPadLeftMargin(0.05);
	gStyle->SetPadRightMargin(0.005);
	gStyle->SetPadTopMargin(0.01);
	gStyle->SetPadBottomMargin(0.05);
	gStyle->SetTitleOffset(0.5,"Y");
	gStyle->SetTitleOffset(0.5,"X");
	gStyle->SetTextFont(132);
}

void theta236(){
	
	const int chc=2,chb=3,chs=5,chn=3,chd=5,chh=2,chf=3,cht=2,chv=5,chp=100,cha=2;
	const char *nip="../../fortran/Output/QESnewP/",*nod="../pictures/qesintp/";
	const char corv[chc]={'c','v'},b[chb]={'l','c','r'},s[chs]={'0','n','m','x','1'},net[chn]={'F','B','E'},den[chd][4]={"wno","vac","2lm","7lm","mat"},h[chh]={'n','i'},f[chf]={'e','m','t'},t[cht]={'n','a'},v[chv][5]={"0.90","0.95","1.10","1.20","1.35"},fn[chf][5]={"e","#mu","#tau"};
	char *name,cn[256];
	FILE *f100=0;
	double dn[chc][chb][chs][chf][chv][chp][cha],y,ym,yp;
	const int col[chv]={1,2,8,4,6},sh[chs]={1,5,3,7,6},w[chs]={1,2,2,2,2};
	int p,a,nc,nb,ns,nn,nd,nh,nf,nt,nv,ns,ndr;
	
	TCanvas c("c","Canvas",1200,800);
	TGraph grs[chs][chf],grv[chf][chv];
	TGraphAsymmErrors grse[chs][chf],grve[chf][chv];
	
	SetStyle();
	
	nd=4;
	nh=0;
	
	nn=2;
	nt=1;
    
    ns=2;
	
//	for(nt=0; nt<cht; nt++){
		for(nf=0; nf<chf; nf++){
			//for(ns=0; ns<chs; ns++){
				for(nc=0; nc<chc; nc++){
					for(nb=0; nb<chb; nb++){
						for(nv=0; nv<chv; nv++){	
							sprintf(cn,"%s%c%s%c%c%s_%c%c%c.dat",nip,net[nn],den[nd],h[nh],f[nf],v[nv],s[ns],b[nb],corv[nc]);//t[nt],
							f100=fopen(cn,"r");
							for(p=0; p<chp; p++){
								for(a=0; a<cha; a++){
									fscanf(f100,"%le",&(dn[nc][nb][ns][nf][nv][p][a]));
								}
							}
							fclose(f100);
						}
					}
				}
			//}
		}
//	}
	
//	for(nt=0; nt<cht; nt++){
		for(ndr=0; ndr<2; ndr++){
			for(nf=0; nf<chf; nf++){
				c.cd();
				//for(ns=0; ns<chs; ns++){
					for(p=0; p<chp; p++){
						if(dn[0][1][2][nf][3][p][1]==0){
							if(dn[1][2][ns][nf][3][p][1]==0){
								y=1;
								}else{
									y=10;
								}
							}else{
								y=dn[1][1][ns][nf][1][p][1]/dn[0][1][2][nf][3][p][1];
								ym=(dn[1][1][ns][nf][1][p][1]-dn[1][0][ns][nf][1][p][1])/dn[0][1][2][nf][3][p][1];
								yp=(dn[1][2][ns][nf][1][p][1]-dn[1][1][ns][nf][1][p][1])/dn[0][1][2][nf][3][p][1];
							}
						grse[ns][nf].SetPoint(p,dn[1][1][ns][nf][3][p][0],y);
						grse[ns][nf].SetPointError(p,0,0,ym,yp);
						grs[ns][nf].SetPoint(p,dn[1][1][ns][nf][3][p][0],y);
					}
				//}
				for(nv=0; nv<chv; nv++){
					for(p=0; p<chp; p++){
						if(dn[0][1][2][nf][3][p][1]==0){
							if(dn[0][1][2][nf][nv][p][1]==0){
								y=1;
								}else{
									y=10;
								}
							}else{
								y=dn[0][1][2][nf][nv][p][1]/dn[0][1][2][nf][3][p][1];
								ym=(dn[0][1][2][nf][nv][p][1]-dn[0][0][2][nf][nv][p][1])/dn[0][1][2][nf][3][p][1];
								yp=(dn[0][2][2][nf][nv][p][1]-dn[0][1][2][nf][nv][p][1])/dn[0][1][2][nf][3][p][1];
							}
						grve[nf][nv].SetPoint(p,dn[1][1][ns][nf][3][p][0],y);
						grve[nf][nv].SetPointError(p,0,0,ym,yp);
						grv[nf][nv].SetPoint(p,dn[0][1][2][nf][nv][p][0],y);
					}
				}
				grs[2][nf].GetXaxis()->SetTitle("#font[132]{P_{lep} (GeV)}");
				grs[2][nf].GetYaxis()->SetTitle("#font[132]{R}");
				grs[2][nf].GetXaxis()->SetRangeUser(9e-2,5e1);
				if(nf==2){
					grs[2][nf].GetYaxis()->SetRangeUser(0.6,1.6);
					}else{
						grs[2][nf].GetYaxis()->SetRangeUser(0.76,1.28);
					}
				grs[2][nf].SetLineColor(0);
				grs[2][nf].Draw("AL");
				grve[nf][1].SetFillColor(8);
				grve[nf][1].SetLineColor(2);
				grve[nf][1].Draw("3SAME");
				grse[2][nf].SetFillColor(5);
				grse[2][nf].Draw("3SAME");
				grs[2][nf].SetLineColor(1);
				grs[2][nf].SetLineWidth(1);
				grs[2][nf].SetLineStyle(1);
				grs[2][nf].Draw("CSAME");
				for(nv=0; nv<chv; nv++){
					if((nv==1)||(nv==3)){
						grv[nf][nv].SetLineStyle(1);
						grv[nf][nv].SetLineColor(col[nv]);
						grv[nf][nv].Draw("CSAME");
					}
				}
				if(!nf){
					TLegend* leglep=new TLegend(0.07,0.83,0.16,0.95);
					}else{
						TLegend* leglep=new TLegend(0.07,0.83,0.15,0.95);
					}
				leglep->AddEntry((TObject*)0,Form("#font[132]{%s^{-} + %s^{+}}",fn[nf],fn[nf]),"");
				leglep->AddEntry((TObject*)0,"#font[132]{NH}","");
				leglep->SetBorderSize(0);
				leglep->Draw();
				TLegend* legv=new TLegend(0.5,0.8,0.98,0.95);
				legv->AddEntry(&grv[nf][3],"#font[132]{M_{A}=1.2 GeV (K2K best fit, SK default)}","L");
				legv->AddEntry(&grve[nf][1],"#font[132]{M_{A}=1.012#pm0.031 GeV (H,D+HE)}","FL");
				legv->AddEntry(&grse[2][nf],"#font[132]{M_{A}^{eff}}","FL");
				legv->SetBorderSize(0);
				legv->Draw();
				c.SetLogx();
				sprintf(cn,"%st23%c%s%c%c_new.eps",nod,net[nn],den[nd],h[nh],f[nf]);//,t[nt]);
				c.Print((const char*)cn);
				delete legv;
				delete leglep;
			}
		}
//	}
}
