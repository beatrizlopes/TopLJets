#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TChain.h>
#include <TCut.h>
#include <TString.h>
#include <TObject.h>
#include <TRandom3.h>
#include <TDirectory.h>

#include "TMVA/Factory.h"
#include "TMVA/Tools.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <fstream>

void printHelp();
bool fileExists(std::string);

int ApplyRegression_systs(TString filename)
{
  
  //define variable for regression
  //  TString var = "mass"; 
  
  TMVA::Tools::Instance();

  //TString filename = "eee";

  TString systNames[] = { "nom","thsysts","puup",        "pudn",
			  "eetrigup",    "eetrigdn",
                          "emtrigup",    "emtrigdn",
                          "mmtrigup",    "mmtrigdn",
                          "eselup",      "eseldn",
                          "mselup",      "mseldn",
                          "l1prefireup", "l1prefiredn",
                          "ees1up", "ees1dn", "ees2up", "ees2dn", "ees3up", "ees3dn", "ees4up", "ees4dn",  "ees5up", "ees5dn",
			  "ees6up", 
			  "ees6dn",
                          "mes1up", "mes1dn", "mes2up", "mes2dn", "mes3up", "mes3dn", "mes4up", "mes4dn",
                          "btaglfup",         "btaglfdn",
                          "btaghfup",         "btaghfdn",
                          "JERup",       "JERdn",
                          "topptup",     "topptdn",
                          "AbsoluteStatJECup","AbsoluteScaleJECup","AbsoluteMPFBiasJECup","FragmentationJECup","SinglePionECALJECup",
                          "SinglePionHCALJECup","FlavorPureGluonJECup","FlavorPureQuarkJECup","FlavorPureCharmJECup",
                          "FlavorPureBottomJECup","TimePtEtaJECup","RelativeJEREC1JECup","RelativeJEREC2JECup","RelativeJERHFJECup",
                          "RelativePtBBJECup","RelativePtEC1JECup","RelativePtEC2JECup","RelativePtHFJECup","RelativeBalJECup",
                          "RelativeFSRJECup","RelativeStatFSRJECup","RelativeStatECJECup","RelativeStatHFJECup","PileUpDataMCJECup",
                          "PileUpPtRefJECup","PileUpPtBBJECup","PileUpPtEC1JECup","PileUpPtEC2JECup","PileUpPtHFJECup",
                          "AbsoluteStatJECdn","AbsoluteScaleJECdn","AbsoluteMPFBiasJECdn","FragmentationJECdn","SinglePionECALJECdn",
                          "SinglePionHCALJECdn","FlavorPureGluonJECdn","FlavorPureQuarkJECdn","FlavorPureCharmJECdn",
                          "FlavorPureBottomJECdn","TimePtEtaJECdn","RelativeJEREC1JECdn","RelativeJEREC2JECdn","RelativeJERHFJECdn",
                          "RelativePtBBJECdn","RelativePtEC1JECdn","RelativePtEC2JECdn","RelativePtHFJECdn","RelativeBalJECdn",
                          "RelativeFSRJECdn","RelativeStatFSRJECdn","RelativeStatECJECdn","RelativeStatHFJECdn","PileUpDataMCJECdn",
                          "PileUpPtRefJECdn","PileUpPtBBJECdn","PileUpPtEC1JECdn","PileUpPtEC2JECdn","PileUpPtHFJECdn",
                          "bfragup", "bfragdn"};

  size_t nexpSysts=sizeof(systNames)/sizeof(TString);
  std::cout << "there are " << nexpSysts << "variations to analyse." << std::endl;

  // Create a new root output file.
  TString outfileName(filename);
  TFile* outputFile = TFile::Open( outfileName, "UPDATE" );

  outputFile->cd();                                                                                                                           
                                    
  std::vector<TNtuple*> outTrees; 

  TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );
  TMVA::Reader *reader1 = new TMVA::Reader( "!Color:!Silent" );

  Float_t classifier_m, classifier_y, reg_mtt, reg_ytt, xi0tt, xi1tt;

  std::cout << "==> Start TMVA Reader" << std::endl;

  Float_t run,lumi,ev,rho,channel,mll,nljets,nbjets,ht,metpt,metphi,l1pt,l1eta,l1phi,l1m,l2pt,l2eta,l2phi,l2m,b1pt,b1eta,b1phi,b1m,b2pt,b2eta,b2phi,b2m,px2,py2,pz2,E2,yvis,ysum,max_dy,min_dy,deltarll,deltaphill,mlb,xi0,xi1,mpp,ypp,gen_mtt,gen_ytt,rec_mtt,rec_ytt,correction,weight;

  Float_t w_muRup, w_muRdn, w_muFup, w_muFdn, w_muRmuFup, w_muRmuFdn;
  Float_t w_PDF[103];

  TString method =  "BDT method";

  // Add the feature variables, names reference branches in inputFile ttree
  reader->AddSpectator("run",&run);
  reader->AddSpectator("lumi",&lumi);
  reader->AddSpectator("ev",&ev);
  reader->AddSpectator("rho",&rho);
  //  reader->AddSpectator("nvtx",&nvtx);
  reader->AddSpectator("channel",&channel);
  reader->AddVariable("mll",&mll);
  reader->AddVariable("nljets",&nljets);
  reader->AddVariable("nbjets",&nbjets);
  //  loader->AddSpectator("ht");                                                                                                                                                     
  reader->AddVariable("metpt",&metpt);
  reader->AddVariable("metphi",&metphi);
  reader->AddVariable("l1pt",&l1pt);
  reader->AddVariable("l1eta",&l1eta);
  reader->AddVariable("l1phi",&l1phi);
  reader->AddVariable("l1m",&l1m);
  reader->AddVariable("l2pt",&l2pt);
  reader->AddVariable("l2eta",&l2eta);
  reader->AddVariable("l2phi",&l2phi);
  reader->AddVariable("l2m",&l2m);
  reader->AddVariable("b1pt",&b1pt);
  reader->AddVariable("b1eta",&b1eta);
  reader->AddVariable("b1phi",&b1phi);
  reader->AddVariable("b1m",&b1m);
  reader->AddVariable("b2pt",&b2pt);
  reader->AddVariable("b2eta",&b2eta);
  reader->AddVariable("b2phi",&b2phi);
  reader->AddVariable("b2m",&b2m);
  reader->AddVariable("deltarll",&deltarll);
  reader->AddVariable("deltaphill",&deltaphill);
  reader->AddVariable("mlb",&mlb);
  reader->AddVariable("px2",&px2);
  reader->AddVariable("py2",&py2);
  reader->AddVariable("pz2",&pz2);
  reader->AddVariable("E2",&E2);
  reader->AddVariable("yvis",&yvis);
  reader->AddVariable("ysum",&ysum);
  reader->AddVariable("max_dy",&max_dy);
  reader->AddVariable("min_dy",&min_dy);
  
  reader->AddSpectator("mpp",&mpp);
  reader->AddSpectator("ypp",&ypp);
  //  reader->AddSpectator("newmpp",&newmpp);
  // reader->AddSpectator("newypp",&newypp);
  reader->AddSpectator("gen_mtt",&gen_mtt);
  reader->AddSpectator("gen_ytt",&gen_ytt);
  reader->AddVariable("rec_ytt",&rec_ytt);
  reader->AddVariable("rec_mtt",&rec_mtt);
  reader->AddSpectator("weight",&weight);
  
  reader1->AddSpectator("run",&run);
  reader1->AddSpectator("lumi",&lumi);
  reader1->AddSpectator("ev",&ev);
  reader1->AddSpectator("rho",&rho);
  //  reader1->AddSpectator("nvtx",&nvtx);
  reader1->AddSpectator("channel",&channel);
  reader1->AddVariable("mll",&mll);
  reader1->AddVariable("nljets",&nljets);
  reader1->AddVariable("nbjets",&nbjets);
  //  loader->AddSpectator("ht");                                                                                                                                                  
  reader1->AddVariable("metpt",&metpt);
  reader1->AddVariable("metphi",&metphi);
  reader1->AddVariable("l1pt",&l1pt);
  reader1->AddVariable("l1eta",&l1eta);
  reader1->AddVariable("l1phi",&l1phi);
  reader1->AddVariable("l1m",&l1m);
  reader1->AddVariable("l2pt",&l2pt);
  reader1->AddVariable("l2eta",&l2eta);
  reader1->AddVariable("l2phi",&l2phi);
  reader1->AddVariable("l2m",&l2m);
  reader1->AddVariable("b1pt",&b1pt);
  reader1->AddVariable("b1eta",&b1eta);
  reader1->AddVariable("b1phi",&b1phi);
  reader1->AddVariable("b1m",&b1m);
  reader1->AddVariable("b2pt",&b2pt);
  reader1->AddVariable("b2eta",&b2eta);
  reader1->AddVariable("b2phi",&b2phi);
  reader1->AddVariable("b2m",&b2m);
  reader1->AddVariable("deltarll",&deltarll);
  reader1->AddVariable("deltaphill",&deltaphill);
  reader1->AddVariable("mlb",&mlb);
  reader1->AddVariable("px2",&px2);
  reader1->AddVariable("py2",&py2);
  reader1->AddVariable("pz2",&pz2);
  reader1->AddVariable("E2",&E2);
  reader1->AddVariable("yvis",&yvis);
  reader1->AddVariable("ysum",&ysum);
  reader1->AddVariable("max_dy",&max_dy);
  reader1->AddVariable("min_dy",&min_dy);

  reader1->AddSpectator("mpp",&mpp);
  reader1->AddSpectator("ypp",&ypp);
  //  reader1->AddSpectator("newmpp",&newmpp);
  //  reader1->AddSpectator("newypp",&newypp);
  
  reader1->AddSpectator("gen_mtt",&gen_mtt);
  reader1->AddSpectator("gen_ytt",&gen_ytt);
  reader1->AddVariable("rec_ytt",&rec_ytt);
  reader1->AddVariable("rec_mtt",&rec_mtt);
  reader1->AddSpectator("weight",&weight);
  
  reader->BookMVA( "BDT method", "/afs/cern.ch/user/b/bribeiro/CMSSW_9_4_11/src/TopLJets2015/TopAnalysis/dataset/weights/TMVARegression_BDTG_LS_mass.weights.xml" );
  reader1->BookMVA( "BDT method", "/afs/cern.ch/user/b/bribeiro/CMSSW_9_4_11/src/TopLJets2015/TopAnalysis/dataset/weights/TMVARegression_BDTG_LS_y.weights.xml" );

  if(filename.Contains("Data")) nexpSysts=1;
  bool thsyst = false;
  
  for(size_t is = 0; is <nexpSysts; is++)
    {

      const char * s_name = systNames[is];

      std::cout << s_name << std::endl;

      // load the input trees
      TChain* bkgchain = (strcmp("nom",s_name)==0) ? new TChain("Sel") : new TChain(Form("Sel_%s",s_name));
      bkgchain->AddFile(filename);

      //create the output trees
      if(strcmp("nom",s_name)==0)       
	{
	  outTrees.push_back(new TNtuple("SEL","SEL","run:lumi:ev:rho:channel:mll:nljets:nbjets:ht:metpt:metphi:l1pt:l1eta:l1phi:l1m:l2pt:l2eta:l2phi:l2m:b1pt:b1eta:b1phi:b1m:b2pt:b2eta:b2phi:b2m:px2:py2:pz2:E2:yvis:ysum:max_dy:min_dy:deltarll:deltaphill:mlb:xi0:xi1:mpp:ypp:gen_mtt:gen_ytt:rec_mtt:rec_ytt:reg_mtt:reg_ytt:weight"));
	  outTrees[0]->SetDirectory(outputFile);
	}

      else      
	{
	  if(outputFile->GetListOfKeys()->Contains(Form("SEL_%s",s_name))) continue;
	  if(strcmp(s_name,"thsysts")!=0) outTrees.push_back(new TNtuple(Form("SEL_%s",s_name),Form("SEL_%s",s_name),"run:lumi:ev:rho:channel:mll:nljets:nbjets:ht:metpt:metphi:l1pt:l1eta:l1phi:l1m:l2pt:l2eta:l2phi:l2m:b1pt:b1eta:b1phi:b1m:b2pt:b2eta:b2phi:b2m:px2:py2:pz2:E2:yvis:ysum:max_dy:min_dy:deltarll:deltaphill:mlb:xi0:xi1:mpp:ypp:gen_mtt:gen_ytt:rec_mtt:rec_ytt:reg_mtt:reg_ytt:weight"));
	  else 
	    {
	      thsyst=true;
	      outTrees.push_back(new TNtuple(Form("SEL_%s",s_name),Form("SEL_%s",s_name),"run:lumi:ev:rho:channel:mll:nljets:nbjets:ht:metpt:metphi:l1pt:l1eta:l1phi:l1m:l2pt:l2eta:l2phi:l2m:b1pt:b1eta:b1phi:b1m:b2pt:b2eta:b2phi:b2m:px2:py2:pz2:E2:yvis:ysum:max_dy:min_dy:deltarll:deltaphill:mlb:xi0:xi1:mpp:ypp:gen_mtt:gen_ytt:rec_mtt:rec_ytt:reg_mtt:reg_ytt:weight:w_muRup:w_muRdn:w_muFup:w_muFdn:w_muRmuFup:w_muRmuFdn:w_PDF000:w_PDF001:w_PDF002:w_PDF003:w_PDF004:w_PDF005:w_PDF006:w_PDF007:w_PDF008:w_PDF009:w_PDF010:w_PDF011:w_PDF012:w_PDF013:w_PDF014:w_PDF015:w_PDF016:w_PDF017:w_PDF018:w_PDF019:w_PDF020:w_PDF021:w_PD022:w_PDF023:w_PDF024:w_PDF025:w_PDF026:w_PDF027:w_PDF028:w_PDF029:w_PDF030:w_PDF031:w_PDF032:w_PDF033:w_PDF034:w_PDF035:w_PDF036:w_PDF037:w_PDF038:w_PDF039:w_PDF040:w_PDF041:w_PDF042:w_PDF043:w_PDF044:w_PDF045:w_PDF046:w_PDF047:w_PDF048:w_PDF049:w_PDF050:w_PDF051:w_PDF052:w_PDF053:w_PDF054:w_PDF055:w_PDF056:w_PDF057:w_PDF058:w_PDF059:w_PDF060:w_PDF061:w_PDF062:w_PDF063:w_PDF064:w_PDF065:w_PDF066:w_PDF067:w_PDF068:w_PDF069:w_PDF070:w_PDF071:w_PDF072:w_PDF073:w_PDF074:w_PDF075:w_PDF076:w_PDF077:w_PDF078:w_PDF079:w_PDF080:w_PDF081:w_PDF082:w_PDF083:w_PDF084:w_PDF085:w_PDF086:w_PDF087:w_PDF088:w_PDF089:w_PDF090:w_PDF091:w_PDF092:w_PDF093:w_PDF094:w_PDF095:w_PDF096:w_PDF097:w_PDF098:w_PDF099:w_PDF100:w_PDF101:w_PDF102"));

	      bkgchain->SetBranchAddress("w_muRup",&w_muRup);
	      bkgchain->SetBranchAddress("w_muRdn",&w_muRdn);
	      bkgchain->SetBranchAddress("w_muFup",&w_muFup);
	      bkgchain->SetBranchAddress("w_muFdn",&w_muFdn);
	      bkgchain->SetBranchAddress("w_muRmuFup",&w_muRmuFup);
	      bkgchain->SetBranchAddress("w_muRmuFdn",&w_muRmuFdn);
	      for(int i=0;i<103;i++)
		bkgchain->SetBranchAddress(Form("w_PDF%03d",i),&w_PDF[i]);
	    }
	  outTrees.back()->SetDirectory(outputFile);
	}
      
      Long64_t nBEvent = bkgchain->GetEntries();
  
      bkgchain->SetBranchAddress("run",&run);
      bkgchain->SetBranchAddress("lumi",&lumi);
      bkgchain->SetBranchAddress("ev",&ev);  
      bkgchain->SetBranchAddress("rho",&rho);
      //  bkgchain->SetBranchAddress("nvtx",&nvtx);
      bkgchain->SetBranchAddress("channel",&channel);
      bkgchain->SetBranchAddress("mll",&mll);
      bkgchain->SetBranchAddress("nljets",&nljets);
      bkgchain->SetBranchAddress("nbjets",&nbjets);
      //  loader->AddSpectator("ht");   
  
      bkgchain->SetBranchAddress("metpt",&metpt);
      bkgchain->SetBranchAddress("metphi",&metphi);
      bkgchain->SetBranchAddress("l1pt",&l1pt);
      bkgchain->SetBranchAddress("l1eta",&l1eta);
      bkgchain->SetBranchAddress("l1phi",&l1phi);
      bkgchain->SetBranchAddress("l1m",&l1m);
      bkgchain->SetBranchAddress("l2pt",&l2pt);
      bkgchain->SetBranchAddress("l2eta",&l2eta);
      bkgchain->SetBranchAddress("l2phi",&l2phi);
      bkgchain->SetBranchAddress("l2m",&l2m);
      bkgchain->SetBranchAddress("b1pt",&b1pt);
      bkgchain->SetBranchAddress("b1eta",&b1eta);
      bkgchain->SetBranchAddress("b1phi",&b1phi);
      bkgchain->SetBranchAddress("b1m",&b1m);
      bkgchain->SetBranchAddress("b2pt",&b2pt);
      bkgchain->SetBranchAddress("b2eta",&b2eta);
      bkgchain->SetBranchAddress("b2phi",&b2phi);
      bkgchain->SetBranchAddress("b2m",&b2m);
      bkgchain->SetBranchAddress("deltarll",&deltarll);
      bkgchain->SetBranchAddress("deltaphill",&deltaphill);
      bkgchain->SetBranchAddress("mlb",&mlb);
      bkgchain->SetBranchAddress("px2",&px2);
      bkgchain->SetBranchAddress("py2",&py2);
      bkgchain->SetBranchAddress("pz2",&pz2);
      bkgchain->SetBranchAddress("E2",&E2);
      bkgchain->SetBranchAddress("yvis",&yvis);
      bkgchain->SetBranchAddress("ysum",&ysum);
      bkgchain->SetBranchAddress("max_dy",&max_dy);
      bkgchain->SetBranchAddress("min_dy",&min_dy);

      bkgchain->SetBranchAddress("xi0",&xi1);
      bkgchain->SetBranchAddress("xi1",&xi0);

      bkgchain->SetBranchAddress("mpp",&mpp);
      bkgchain->SetBranchAddress("ypp",&ypp);
      //  bkgchain->SetBranchAddress("newmpp",&newmpp);
      //  bkgchain->SetBranchAddress("newypp",&newypp);
      
      bkgchain->SetBranchAddress("gen_mtt",&gen_mtt);
      bkgchain->SetBranchAddress("gen_ytt",&gen_ytt);
      bkgchain->SetBranchAddress("rec_ytt",&rec_ytt);
      bkgchain->SetBranchAddress("rec_mtt",&rec_mtt);  
      bkgchain->SetBranchAddress("weight",&weight);  

      for (Long64_t ievt=0; ievt<nBEvent; ievt++) {
	if (ievt%100000 == 0){
	  std::cout << "--- ... Processing event: " << ievt << std::endl;
	}
	
	bkgchain->GetEntry(ievt);

	if(rec_mtt<0) continue;
	// get the classifiers for each of the signal/background classifications

	classifier_m = reader->EvaluateRegression(0, method );
	classifier_y = reader1->EvaluateRegression(0, method );
	
	reg_mtt=rec_mtt/classifier_m;
	reg_ytt=rec_ytt-classifier_y;
	
	//	xi0tt=reg_mtt/(13000*exp(-reg_ytt));
	//      xi1tt=reg_mtt/(13000*exp(+reg_ytt));
	// cout << xi0tt << "      " << xi1tt << endl;
	
	
	if(!thsyst)
	  {	  float vars[50] = {run,lumi,ev,rho,channel,mll,nljets,
			    nbjets,ht,
			    metpt,metphi,l1pt,l1eta,l1phi,l1m,l2pt,l2eta,
			    l2phi,l2m,
			    b1pt,b1eta,b1phi,b1m,b2pt,b2eta,b2phi,b2m,
				    px2,py2,pz2,E2,yvis,ysum,max_dy,min_dy,
			    deltarll,deltaphill,mlb,xi0,xi1,mpp,ypp,gen_mtt,gen_ytt,
				    rec_mtt,rec_ytt,reg_mtt,reg_ytt,weight};
	    outTrees[is]->Fill(vars);
	  }
	else
	  {
	    float vars[160] = {run,lumi,ev,rho,channel,mll,nljets,
                            nbjets,ht,
                            metpt,metphi,l1pt,l1eta,l1phi,l1m,l2pt,l2eta,
                            l2phi,l2m,
                            b1pt,b1eta,b1phi,b1m,b2pt,b2eta,b2phi,b2m,
                            px2,py2,pz2,E2,yvis,ysum,max_dy,min_dy,
                            deltarll,deltaphill,mlb,xi0,xi1,mpp,ypp,gen_mtt,gen_ytt,
			       rec_mtt,rec_ytt,reg_mtt,reg_ytt,weight,w_muRup,w_muRdn, w_muFup, w_muFdn, w_muRmuFup, w_muRmuFdn,
			       w_PDF[0], w_PDF[1], w_PDF[2],
			       w_PDF[3], w_PDF[4], w_PDF[5],
			       w_PDF[6], w_PDF[7], w_PDF[8],
			       w_PDF[9],
			       w_PDF[10], w_PDF[11], w_PDF[12],
			       w_PDF[13], w_PDF[14], w_PDF[15],
			       w_PDF[16], w_PDF[17], w_PDF[18],
			       w_PDF[19],
			       w_PDF[20], w_PDF[21], w_PDF[22],
			       w_PDF[23], w_PDF[24], w_PDF[25],
			       w_PDF[26], w_PDF[27], w_PDF[28],
			       w_PDF[29],
			       w_PDF[30], w_PDF[31], w_PDF[32],
			       w_PDF[33], w_PDF[34], w_PDF[35],
			       w_PDF[36], w_PDF[37], w_PDF[38],
			       w_PDF[39],
			       w_PDF[40], w_PDF[41], w_PDF[42],
			       w_PDF[43], w_PDF[44], w_PDF[45],
		  w_PDF[46], w_PDF[47], w_PDF[48],
		  w_PDF[49],
		  w_PDF[50], w_PDF[51], w_PDF[52],
		  w_PDF[53], w_PDF[54], w_PDF[55],
		  w_PDF[56], w_PDF[57], w_PDF[58],
		  w_PDF[59],
		  w_PDF[60], w_PDF[61], w_PDF[62],
		  w_PDF[63], w_PDF[64], w_PDF[65],
		  w_PDF[66], w_PDF[67], w_PDF[68],
		  w_PDF[69],
		  w_PDF[70], w_PDF[71], w_PDF[72],
		  w_PDF[73], w_PDF[74], w_PDF[75],
		  w_PDF[76], w_PDF[77], w_PDF[78],
		  w_PDF[79],
		  w_PDF[80], w_PDF[81], w_PDF[82],
		  w_PDF[83], w_PDF[84], w_PDF[85],
		  w_PDF[86], w_PDF[87], w_PDF[88],
		  w_PDF[89],
		  w_PDF[90], w_PDF[91], w_PDF[92],
		  w_PDF[93], w_PDF[94], w_PDF[95],
		  w_PDF[96], w_PDF[97], w_PDF[98],
		  w_PDF[99],
		  w_PDF[100], w_PDF[101], w_PDF[102]

	    };
	    
	    outTrees[is]->Fill(vars);
	  }
      }

      outTrees[is]->Write("",TObject::kOverwrite);
      //      gDirectory->Delete(Form("Sel_%s;*",s_name));
    }

  outputFile->Write();
  outputFile->Close();

  return 0;
}
