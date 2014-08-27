#include "TStyle.h"

void SetStyle(){
	gStyle->SetCanvasColor(0);
//	gStyle->SetFillColor(0);
	gStyle->SetFrameFillColor(0);
	gStyle->SetPadColor(0);
	gStyle->SetStatColor(0);
	gStyle->SetTitleFillColor(0);
	gStyle->SetTextFont(132);
	gStyle->SetPalette(1);
}

void slayers(){

	const int cha=50,che=50,chn=9;
	const char *nex="../../fortran/Output/";
	char *name,cn[256];
	FILE *fold=1,*fnew=2,*ferr=2;
	double prcos,cosin[cha],Enu[che],pold[chn][cha][che],pnew[chn][cha][che],err[chn][cha][che];
	int a,e,n,nd;
	
	TCanvas c("c","Canvas",600,400);
	TGraph2D gr[chn];
	
	SetStyle();
	
	sprintf(cn,"%s%s.dat",nex,"512");
	fold=fopen(cn,"r");
	sprintf(cn,"%s%s.dat",nex,"1");
	fnew=fopen(cn,"r");
	sprintf(cn,"%s%s.dat",nex,"512_1");
	ferr=fopen(cn,"w");
	for(a=0; a<cha; a++){
		for(e=0; e<che; e++){
			fscanf(fold,"%le",&prcos);
			fscanf(fnew,"%le",&prcos);
			cosin[a]=-prcos;
			fprintf(ferr,"%le ",cosin[a]);
			fscanf(fold,"%le",&(Enu[e]));
			fscanf(fnew,"%le",&(Enu[e]));
			fprintf(ferr,"%le ",Enu[e]);
			for(n=0; n<9; n++){
				fscanf(fold,"%le",&(pold[n][a][e]));
				fscanf(fnew,"%le",&(pnew[n][a][e]));
				err[n][a][e]=fabs(pnew[n][a][e]-pold[n][a][e])/pold[n][a][e]*100;
				fprintf(ferr,"%le ",err[n][a][e]);
			}
			fprintf(ferr,"\n");
		}
	}
	fclose(fold);
	fclose(fnew);
	fclose(ferr);
	
//	for(nd=0; nd<2; nd++){
		for(n=0; n<9; n++){
			c.cd();
			for(a=0; a<cha; a++){
				for(e=0; e<che; e++){
					gr[n].SetPoint(a*che+e,cosin[a],log10(Enu[e]),err[n][a][e]);
				}
			}
			gr[n].GetXaxis()->SetTitle("#font[132]{cos(#theta)}");//
			gr[n].GetXaxis()->SetRangeUser(0,1);
			gr[n].GetYaxis()->SetTitle("#font[132]{lg(E_{#nu}/eV)}");
			gr[n].GetYaxis()->SetRangeUser(6,13);
			gr[n].Draw("COLZ");
			sprintf(cn,"%s%d.eps","../pictures/slayers/512_1_",n);
			c.Print((const char*)cn);
		}
//	}
}
