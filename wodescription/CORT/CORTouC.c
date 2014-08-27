#include "TStyle.h"

void SetStyle(){
	gStyle->SetFillColor(0);
	gStyle->SetPadLeftMargin(0.1);
	gStyle->SetPadRightMargin(0.005);
	gStyle->SetPadTopMargin(0.005);		
	gStyle->SetPadBottomMargin(0.1);
//	gStyle->SetTitleOffset(0.5,"Y");
	gStyle->SetTitleOffset(0.5,"X");
	gStyle->SetTextFont(132);
}

void CORTouC(){
	
	const int chf=2,cht=2,che=7,cha=101;
	const char nsp[5]="CRTn",*nex="../../fortran/Output/";
	const char f[chf]={'e','m'},t[cht]={'n','a'};
	char *name,cn[256];
	FILE *f140=0;
	double sp[chf][cht][che][cha];
	const int col[che-1]={4,2,1,6,8,46};//40
	int e,a,nf,nt,n,nd;
	
	TCanvas c("c","multipads",1200,800);
	TGraph grsp[chf][cht][che-1];
	
	SetStyle();

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
			grsp[nf][nt][0].GetXaxis()->SetTitle("#font[132]{cos#theta}  ");
			grsp[nf][nt][0].GetXaxis()->SetRangeUser(-1,1);
			grsp[nf][nt][0].GetYaxis()->SetTitle("#font[132]{#frac{j_{#nu}(E_{#nu},#theta)}{j_{#nu}(E_{#nu},0)}}");
			if(nf==0){
				grsp[nf][nt][0].GetXaxis()->SetTitleSize(0.04);
				grsp[nf][nt][0].GetYaxis()->SetTitleSize(0.04);
				grsp[nf][nt][0].GetYaxis()->SetTitleOffset(0.95);
				grsp[nf][nt][0].GetYaxis()->SetRangeUser(0.5,11.5);
				}
				else{
					grsp[nf][nt][0].GetXaxis()->SetTitleSize(0.08);
					grsp[nf][nt][0].GetYaxis()->SetTitleSize(0.06);
					grsp[nf][nt][0].GetYaxis()->SetTitleOffset(0.7);
					grsp[nf][nt][0].GetYaxis()->SetRangeUser(0.5,6.8);
				}
			grsp[nf][nt][0].Draw("AC");
			for(e=1; e<che; e++){
				grsp[nf][nt][e-1].SetLineWidth(1);
				grsp[nf][nt][e-1].SetLineColor(col[e-1]);
				grsp[nf][nt][e-1].Draw("CSAME");
			}
			if(nf==0){
				if(nt==0){
					TLegend* legname00=new TLegend(0.2,0.79,0.3,0.92);
					legname00->AddEntry((TObject*)0,"#font[132]{#nu_{e}}","");
					legname00->Draw("SAME");
					gPad->SetPad(0,0.38,0.5,0.99);
					}
					else{
						TLegend* legname01=new TLegend(0.2,0.81,0.3,0.89);
						legname01->AddEntry((TObject*)0,"#font[132]{#bar#nu_{e}}","");
						legname01->Draw("SAME");
						gPad->SetPad(0.5,0.38,0.995,0.99);
					}
				}
				else{
					if(nt==0){
						TLegend* legname10=new TLegend(0.2,0.72,0.3,0.9);
						legname10->AddEntry((TObject*)0,"#font[132]{#nu_{#mu}}","");
						legname10->Draw("SAME");
						gPad->SetPad(0,0,0.5,0.38);
						}
						else{
							TLegend* legname11=new TLegend(0.2,0.76,0.3,0.89);
							legname11->AddEntry((TObject*)0,"#font[132]{#bar#nu_{#mu}}","");
							legname11->Draw("SAME");
							gPad->SetPad(0.5,0,0.995,0.38);
						}
				}
		}
	}
	c.cd();
	TLegend* leg=new TLegend(0.4,0.6,0.55,0.9);
	leg->AddEntry((TObject*)0,"#font[132]{E_{#nu}:}","");	
	for(e=che-1; e>0; e--){
		leg->AddEntry(&grsp[0][0][e-1],Form("#font[132]{10^{%d} GeV}",e-2),"L");
	}
	leg->Draw("SAME");
	sprintf(cn,"../pictures/spectra/CRTnxC.eps");
	c.Print((const char*)cn);
	delete leg;
	delete legname00;
	delete legname01;
	delete legname10;
	delete legname11;
}
