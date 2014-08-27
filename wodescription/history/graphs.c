//#include<TCanvas.h>
//#include<TGraph.h>
//#include<TF1.h>
//#include<vector>

//using namespace std;

int graphs(){
  TF1 * Gamma = new TF1("Gamma", "TMath::Gamma(x)", 0, 8);
  TF1 * Log = new TF1("Log", "TMath::Log(x)", 0, 10);
  TF1 * Tan = new TF1("Tan", "TMath::Tan(x)", 0, 5);
  TF1 * Bessel = new TF1("Bessel", "TMath::BesselJ1(x)", 0, 14);

  TGraph * g1 = new TGraph(Gamma);
  TGraph * g2 = new TGraph(Log);
  TGraph * g3 = new TGraph(Tan);
  TGraph * g4 = new TGraph(Bessel);

//  std::vector<TGraph*> g;
//  g.push_back(g1);
//  g.push_back(g2);
//  g.push_back(g3);
//  g.push_back(g4);

  TCanvas * c = new TCanvas("main");
  c->Divide(2, 2, 0, 0);
  for (int i=1; i<=4; i++){
    c->cd(i);
    g[i-1]->Draw("ACP");
  }
  c->SaveAs("main.ps");
  delete Gamma;
  delete Log;
  delete Tan;
  delete Bessel;
  g.clear();
  delete g1;
  delete g2;
  delete g3;
  delete g4;
  delete c;
  return 0;
}
