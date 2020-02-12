void nuisances()
{
//=========Macro generated from canvas: c/c
//=========  (Mon Aug 19 18:27:03 2019) by ROOT version6.10/09
   TCanvas *c = new TCanvas("c", "c",0,0,500,1500);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c->SetHighLightColor(2);
   c->Range(0,0,1,1);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetGridy();
   c->SetLeftMargin(0.3);
   c->SetRightMargin(0.05);
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   
   TH2F *frame__1 = new TH2F("frame__1","",1,-3,3,1,0,0);
   frame__1->SetDirectory(0);
   frame__1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   frame__1->SetLineColor(ci);
   frame__1->GetXaxis()->SetTitle("N x #sigma_{pre-fit}");
   frame__1->GetXaxis()->SetRange(1,1);
   frame__1->GetXaxis()->SetLabelFont(42);
   frame__1->GetXaxis()->SetLabelSize(0.035);
   frame__1->GetXaxis()->SetTitleSize(0.035);
   frame__1->GetXaxis()->SetTitleFont(42);
   frame__1->GetYaxis()->SetLabelFont(42);
   frame__1->GetYaxis()->SetLabelSize(0.025);
   frame__1->GetYaxis()->SetTitleSize(0.035);
   frame__1->GetYaxis()->SetTitleOffset(0);
   frame__1->GetYaxis()->SetTitleFont(42);
   frame__1->GetZaxis()->SetLabelFont(42);
   frame__1->GetZaxis()->SetLabelSize(0.035);
   frame__1->GetZaxis()->SetTitleSize(0.035);
   frame__1->GetZaxis()->SetTitleFont(42);
   frame__1->Draw("");
   
   Double_t gr2s_fx1[5] = {
   -2,
   -2,
   2,
   2,
   -2};
   Double_t gr2s_fy1[5] = {
   0,
   0,
   0,
   0,
   0};
   TGraph *graph = new TGraph(5,gr2s_fx1,gr2s_fy1);
   graph->SetName("gr2s");
   graph->SetTitle("");
   graph->SetFillColor(18);
   graph->SetLineColor(18);
   graph->SetMarkerColor(18);
   
   TH1F *Graph_gr2s1 = new TH1F("Graph_gr2s1","",100,-2.4,2.4);
   Graph_gr2s1->SetMinimum(0);
   Graph_gr2s1->SetMaximum(1.1);
   Graph_gr2s1->SetDirectory(0);
   Graph_gr2s1->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gr2s1->SetLineColor(ci);
   Graph_gr2s1->GetXaxis()->SetLabelFont(42);
   Graph_gr2s1->GetXaxis()->SetLabelSize(0.035);
   Graph_gr2s1->GetXaxis()->SetTitleSize(0.035);
   Graph_gr2s1->GetXaxis()->SetTitleFont(42);
   Graph_gr2s1->GetYaxis()->SetLabelFont(42);
   Graph_gr2s1->GetYaxis()->SetLabelSize(0.035);
   Graph_gr2s1->GetYaxis()->SetTitleSize(0.035);
   Graph_gr2s1->GetYaxis()->SetTitleOffset(0);
   Graph_gr2s1->GetYaxis()->SetTitleFont(42);
   Graph_gr2s1->GetZaxis()->SetLabelFont(42);
   Graph_gr2s1->GetZaxis()->SetLabelSize(0.035);
   Graph_gr2s1->GetZaxis()->SetTitleSize(0.035);
   Graph_gr2s1->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_gr2s1);
   
   graph->Draw("f");
   
   Double_t gr1s_fx2[5] = {
   -1,
   -1,
   1,
   1,
   -1};
   Double_t gr1s_fy2[5] = {
   0,
   0,
   0,
   0,
   0};
   graph = new TGraph(5,gr1s_fx2,gr1s_fy2);
   graph->SetName("gr1s");
   graph->SetTitle("");
   graph->SetFillColor(19);
   graph->SetLineColor(19);
   graph->SetMarkerColor(19);
   
   TH1F *Graph_gr1s2 = new TH1F("Graph_gr1s2","",100,-1.2,1.2);
   Graph_gr1s2->SetMinimum(0);
   Graph_gr1s2->SetMaximum(1.1);
   Graph_gr1s2->SetDirectory(0);
   Graph_gr1s2->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gr1s2->SetLineColor(ci);
   Graph_gr1s2->GetXaxis()->SetLabelFont(42);
   Graph_gr1s2->GetXaxis()->SetLabelSize(0.035);
   Graph_gr1s2->GetXaxis()->SetTitleSize(0.035);
   Graph_gr1s2->GetXaxis()->SetTitleFont(42);
   Graph_gr1s2->GetYaxis()->SetLabelFont(42);
   Graph_gr1s2->GetYaxis()->SetLabelSize(0.035);
   Graph_gr1s2->GetYaxis()->SetTitleSize(0.035);
   Graph_gr1s2->GetYaxis()->SetTitleOffset(0);
   Graph_gr1s2->GetYaxis()->SetTitleFont(42);
   Graph_gr1s2->GetZaxis()->SetLabelFont(42);
   Graph_gr1s2->GetZaxis()->SetLabelSize(0.035);
   Graph_gr1s2->GetZaxis()->SetTitleSize(0.035);
   Graph_gr1s2->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_gr1s2);
   
   graph->Draw("f");
   
   TLegend *leg = new TLegend(0.1,0.93,0.6,0.96,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.03);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   leg->Draw();
   
   leg = new TLegend(0.1,0.9,0.6,0.93,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.03);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   leg->Draw();
   TLatex *   tex = new TLatex(0.8,0.5,"-1#sigma");

   ci = TColor::GetColor("#333333");
   tex->SetTextColor(ci);
   tex->SetTextFont(42);
   tex->SetTextSize(0.025);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(1.8,0.5,"+2#sigma");

   ci = TColor::GetColor("#333333");
   tex->SetTextColor(ci);
   tex->SetTextFont(42);
   tex->SetTextSize(0.025);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(-1.2,0.5,"-1#sigma");

   ci = TColor::GetColor("#333333");
   tex->SetTextColor(ci);
   tex->SetTextFont(42);
   tex->SetTextSize(0.025);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(-2.2,0.5,"-2#sigma");

   ci = TColor::GetColor("#333333");
   tex->SetTextColor(ci);
   tex->SetTextFont(42);
   tex->SetTextSize(0.025);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.12,0.97,"#bf{CMS} #it{preliminary}");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.035);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.75,0.97,"#scale[0.8]{2.2 fb^{-1} (13 TeV)}");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.035);
   tex->SetLineWidth(2);
   tex->Draw();
   
   TH2F *frame_copy__2 = new TH2F("frame_copy__2","",1,-3,3,1,0,0);
   frame_copy__2->SetDirectory(0);
   frame_copy__2->SetStats(0);

   ci = TColor::GetColor("#000099");
   frame_copy__2->SetLineColor(ci);
   frame_copy__2->GetXaxis()->SetTitle("N x #sigma_{pre-fit}");
   frame_copy__2->GetXaxis()->SetRange(1,1);
   frame_copy__2->GetXaxis()->SetLabelFont(42);
   frame_copy__2->GetXaxis()->SetLabelSize(0.035);
   frame_copy__2->GetXaxis()->SetTitleSize(0.035);
   frame_copy__2->GetXaxis()->SetTitleFont(42);
   frame_copy__2->GetYaxis()->SetLabelFont(42);
   frame_copy__2->GetYaxis()->SetLabelSize(0.025);
   frame_copy__2->GetYaxis()->SetTitleSize(0.035);
   frame_copy__2->GetYaxis()->SetTitleOffset(0);
   frame_copy__2->GetYaxis()->SetTitleFont(42);
   frame_copy__2->GetZaxis()->SetLabelFont(42);
   frame_copy__2->GetZaxis()->SetLabelSize(0.035);
   frame_copy__2->GetZaxis()->SetTitleSize(0.035);
   frame_copy__2->GetZaxis()->SetTitleFont(42);
   frame_copy__2->Draw("sameaxis");
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
