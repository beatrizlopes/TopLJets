void nll1dscan_r()
{
//=========Macro generated from canvas: c/c
//=========  (Mon Aug 19 18:27:03 2019) by ROOT version6.10/09

  TFile *f = new TFile("higgsCombineTest.MultiDimFit.mH0.root");
  TTree* limit = (TTree*)f->Get("limit");
  limit->Draw("2*deltaNLL:r>>hist(10000,0,2,10000,0,10)","2*deltaNLL<10","L");
  TH2F* hist = (TH2F*)gDirectory->Get("hist");  
  TCanvas* c = new TCanvas();  

   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c->SetHighLightColor(2);
   c->Range(0.7421687,-1.176471,1.224096,10.58824);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetLeftMargin(0.12);
   c->SetRightMargin(0.05);
   c->SetTopMargin(0.05);
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   
   TH1F *frame__3 = new TH1F("frame__3","",100,0,2);
   frame__3->SetMinimum(0);
   frame__3->SetMaximum(10);
   frame__3->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   frame__3->SetLineColor(ci);
   frame__3->GetXaxis()->SetTitle("#mu=#sigma/#sigma_{th}");
   frame__3->GetXaxis()->SetLabelFont(42);
   frame__3->GetXaxis()->SetLabelSize(0.035);
   frame__3->GetXaxis()->SetTitleSize(0.035);
   frame__3->GetXaxis()->SetTitleFont(42);
   frame__3->GetYaxis()->SetTitle("-2#DeltalnL");
   frame__3->GetYaxis()->SetLabelFont(42);
   frame__3->GetYaxis()->SetLabelSize(0.035);
   frame__3->GetYaxis()->SetTitleSize(0.035);
   frame__3->GetYaxis()->SetTitleOffset(0);
   frame__3->GetYaxis()->SetTitleFont(42);
   frame__3->GetZaxis()->SetLabelFont(42);
   frame__3->GetZaxis()->SetLabelSize(0.035);
   frame__3->GetZaxis()->SetTitleSize(0.035);
   frame__3->GetZaxis()->SetTitleFont(42);
   frame__3->Draw("");

   hist->Draw("same");

   TLatex *   tex = new TLatex(0.7,1.25,"68% CL");

   //   ci = TColor::GetColor("#333333");
   tex->SetTextColor(2);
   tex->SetTextFont(42);
   tex->SetTextSize(0.025);
   tex->SetLineWidth(2);
   tex->Draw();
   TLine *line = new TLine(0,1,2,1);

   // ci = TColor::GetColor("#666666");
   line->SetLineColor(2);
   line->SetLineStyle(2);
   line->Draw();
      tex = new TLatex(0.7,4.09,"95% CL");

      //   ci = TColor::GetColor("#333333");
   tex->SetTextColor(2);
   tex->SetTextFont(42);
   tex->SetTextSize(0.025);
   tex->SetLineWidth(2);
   tex->Draw();
   line = new TLine(0,3.84,2,3.84);

   // ci = TColor::GetColor("#666666");
   line->SetLineColor(2);
   line->SetLineStyle(2);
   line->Draw();
      tex = new TLatex(0.12,0.97,"#bf{CMS} #it{preliminary}");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.035);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.75,0.97,"#scale[0.8]{39.5 fb^{-1} (13 TeV)}");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.035);
   tex->SetLineWidth(2);
   tex->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
