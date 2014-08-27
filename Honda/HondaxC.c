#include "TStyle.h"

void SetStyle(){
	gStyle->SetFillColor(0);
	gStyle->SetFrameLineWidth(1);
	gStyle->SetPadLeftMargin(0.07);
	gStyle->SetPadRightMargin(0.005);
	gStyle->SetPadTopMargin(0.005);		
	gStyle->SetPadBottomMargin(0.1);
	gStyle->SetTitleOffset(0.8,"Y");
	gStyle->SetTitleOffset(0.5,"X");
//	gStyle->SetTextFont(132);
}

void HondaxC(){
	
	const int chf=2,cht=2,che=7,cha=101;
	const char nsp[5]="H11x",*nex="../../fortran/Output/spectra/";
	const char f[chf]={'e','m'},t[cht]={'n','a'},fn[chf][5]={"e","#mu"},tn[cht][8]={"#nu","#bar#nu"};
	char *name,cn[256];
	FILE *f140=0;
	double sp[chf][cht][che][cha];
	const int col[che-1]={4,2,8,6,1,46},sh[che-1]={9,7,4,3,1,6},w[che-1]={1,2,2,2,1,2};
	int chea,e,a,nf,nt,n,nd;
	
	TCanvas c("c","multipads",1200,800);
	TGraph grsp[chf][cht][che-1];
	
	SetStyle();
	
	chea=che-1;

	for(nf=0; nf<chf; nf++){
		for(nt=0; nt<cht; nt++){
			sprintf(cn,"%s%sza%c%c.dat",nex,nsp,f[nf],t[nt]);
			f140=fopen(cn,"r");
			for(e=0; e<che; e++){
				for(a=0; a<cha; a++){
					fscanf(f140,"%le",&(sp[nf][nt][e][a]));
				}
			}
			fclose(f140);
		}
	}

	c.Divide(2,2,0,0);

	for(nf=0; nf<chf; nf++){
		for(nt=0; nt<cht; nt++){
			c.cd(cht*nf+nt+1);
			for(e=1; e<che; e++){
				for(a=1; a<cha; a++){
					grsp[nf][nt][e-1].SetPoint(a-1,sp[nf][nt][0][a],sp[nf][nt][e][a]);
				}
			}
			grsp[nf][nt][0].GetXaxis()->SetRangeUser(-1,1);
			if(!nf){
				if(!nt){
					grsp[nf][nt][0].GetYaxis()->SetTitle("#font[132]{#Phi_{#nu}(E_{#nu},#theta)/#Phi_{#nu}(E_{#nu},0)}");
					grsp[nf][nt][0].GetYaxis()->SetTitleSize(0.04);
				}
				grsp[nf][nt][0].GetYaxis()->SetRangeUser(0.5,11.5);
				}
				else{
					grsp[nf][nt][0].GetXaxis()->SetTitle("#font[132]{cos#theta} ");
					grsp[nf][nt][0].GetXaxis()->SetTitleSize(0.08);
					grsp[nf][nt][0].GetYaxis()->SetRangeUser(0.5,6.8);
				}
			grsp[nf][nt][0].Draw("AC");
			for(e=1; e<chea; e++){
				grsp[nf][nt][e-1].SetLineColor(col[e-1]);
				grsp[nf][nt][e-1].SetLineStyle(sh[e-1]);
				grsp[nf][nt][e-1].SetLineWidth(w[e-1]);
				grsp[nf][nt][e-1].Draw("CSAME");
			}
			if(!nf){
				if(!nt){
					TLegend* legname00=new TLegend(0.2,0.78,0.3,0.91);
					legname00->AddEntry((TObject*)0,Form("#font[132]{%s_{%s}}",tn[nt],fn[nf]),"");
					legname00->SetBorderSize(0);
					legname00->Draw();
					gPad->SetPad(0,0.39,0.5,0.99);
					}
					else{
						TLegend* legname01=new TLegend(0.2,0.81,0.3,0.9);
						legname01->AddEntry((TObject*)0,Form("#font[132]{%s_{%s}}",tn[nt],fn[nf]),"");
						legname01->SetBorderSize(0);
						legname01->Draw();
						gPad->SetPad(0.5,0.39,0.995,0.99);
					}
				}
				else{
					if(!nt){
						TLegend* legname10=new TLegend(0.2,0.72,0.3,0.9);
						legname10->AddEntry((TObject*)0,Form("#font[132]{%s_{%s}}",tn[nt],fn[nf]),"");
						legname10->SetBorderSize(0);
						legname10->Draw();
						gPad->SetPad(0,0,0.5,0.39);
						}
						else{
							TLegend* legname11=new TLegend(0.2,0.76,0.3,0.9);
							legname11->AddEntry((TObject*)0,Form("#font[132]{%s_{%s}}",tn[nt],fn[nf]),"");
							legname11->SetBorderSize(0);
							legname11->Draw();
							gPad->SetPad(0.5,0,0.995,0.39);
						}
				}
		}
	}
	c.cd();
	TLegend* leg=new TLegend(0.45,0.6,0.6,0.9);
	leg->AddEntry((TObject*)0,"#font[132]{E_{#nu}:}","");	
	for(e=chea-1; e>0; e--){
		leg->AddEntry(&grsp[0][0][e-1],Form("#font[132]{10^{%d} GeV}",e-2),"L");
	}
	leg->SetBorderSize(0);
	leg->Draw();
	sprintf(cn,"../pictures/spectra/H11xC.eps");
	c.Print((const char*)cn);
	delete legname00;
	delete legname01;
	delete legname10;
	delete legname11;
	delete leg;
}
