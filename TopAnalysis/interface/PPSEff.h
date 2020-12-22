// ROOT include
#include "TH1D.h"
#include "TGraphErrors.h"
#include "TFile.h"
#include "TString.h"

// cpp include
#include <iostream>
#include <string>

// PPS helper from https://twiki.cern.ch/twiki/bin/view/CMS/TaggedProtonsFiducialCuts
//#include "aperture_param_v2.h"

enum class Periods {
	era2017B  = 0,
	era2017C1 = 1,
	era2017C2 = 2,
	era2017D  = 3,
	era2017E  = 4,
	era2017F1 = 5,
	era2017F2 = 6,
	era2017F3 = 7,
};

class PPSEff
{

	public: 
	
	//Constructor 
	PPSEff(std::string filename){
        init(filename);  
	}
	
	// Destructor 
	~PPSEff() {_file0->Close();}
	
	float getEff(float xi, int arm, unsigned int runNumber){
		if(!EffInit){ std::cout << "ERROR: call getEff() w/o proper initialization" << std::endl; return 0;}
		if( xi < _xmin || xi > _xmax) return 0;
		int ibin = int( (xi-_xmin)/_bw ) + 1;
		if(arm==0){
			if(runNumber>=297050&& runNumber<=299329) return _hef201745[static_cast<int>(Periods::era2017B)]->GetBinContent(ibin);
			if(runNumber>=299368&& runNumber<=300780) return _hef201745[static_cast<int>(Periods::era2017C1)]->GetBinContent(ibin);
			if(runNumber>=300806&& runNumber<=302029) return _hef201745[static_cast<int>(Periods::era2017C2)]->GetBinContent(ibin);
			if(runNumber>=302031&& runNumber<=302663) return _hef201745[static_cast<int>(Periods::era2017D)]->GetBinContent(ibin);
			if(runNumber>=303825&& runNumber<=304797) return _hef201745[static_cast<int>(Periods::era2017E)]->GetBinContent(ibin);
			if(runNumber>=305044&& runNumber<=305114) return _hef201745[static_cast<int>(Periods::era2017F1)]->GetBinContent(ibin);
			if(runNumber>=305178&& runNumber<=305902) return _hef201745[static_cast<int>(Periods::era2017F2)]->GetBinContent(ibin);
			if(runNumber>=305967&& runNumber<=306460) return _hef201745[static_cast<int>(Periods::era2017F3)]->GetBinContent(ibin);
			return 0;
		}
		else if(arm==1){
			if(runNumber>=297050&& runNumber<=299329) return _hef201756[static_cast<int>(Periods::era2017B)]->GetBinContent(ibin);
			if(runNumber>=299368&& runNumber<=300780) return _hef201756[static_cast<int>(Periods::era2017C1)]->GetBinContent(ibin);
			if(runNumber>=300806&& runNumber<=302029) return _hef201756[static_cast<int>(Periods::era2017C2)]->GetBinContent(ibin);
			if(runNumber>=302031&& runNumber<=302663) return _hef201756[static_cast<int>(Periods::era2017D)]->GetBinContent(ibin);
			if(runNumber>=303825&& runNumber<=304797) return _hef201756[static_cast<int>(Periods::era2017E)]->GetBinContent(ibin);
			if(runNumber>=305044&& runNumber<=305114) return _hef201756[static_cast<int>(Periods::era2017F1)]->GetBinContent(ibin);
			if(runNumber>=305178&& runNumber<=305902) return _hef201756[static_cast<int>(Periods::era2017F2)]->GetBinContent(ibin);
			if(runNumber>=305967&& runNumber<=306460) return _hef201756[static_cast<int>(Periods::era2017F3)]->GetBinContent(ibin);
			return 0;
		}
		else{ std::cout <<" wrong arm number (expect 0 or 1), return 0...\n"; return 0;}
	}

	float getEffErr(float xi, int arm, unsigned int runNumber){
		if(!EffInit){ std::cout << "ERROR: call getEffErr() w/o proper initialization" << std::endl; return 0;}
		if( xi < _xmin || xi > _xmax) return 0;
		int ibin = int( (xi-_xmin)/_bw ) + 1;
		if(arm==0){
			if(runNumber>=297050&& runNumber<=299329) return _hef201745[static_cast<int>(Periods::era2017B)]->GetBinError(ibin);
			if(runNumber>=299368&& runNumber<=300780) return _hef201745[static_cast<int>(Periods::era2017C1)]->GetBinError(ibin);
			if(runNumber>=300806&& runNumber<=302029) return _hef201745[static_cast<int>(Periods::era2017C2)]->GetBinError(ibin);
			if(runNumber>=302031&& runNumber<=302663) return _hef201745[static_cast<int>(Periods::era2017D)]->GetBinError(ibin);
			if(runNumber>=303825&& runNumber<=304797) return _hef201745[static_cast<int>(Periods::era2017E)]->GetBinError(ibin);
			if(runNumber>=305044&& runNumber<=305114) return _hef201745[static_cast<int>(Periods::era2017F1)]->GetBinError(ibin);
			if(runNumber>=305178&& runNumber<=305902) return _hef201745[static_cast<int>(Periods::era2017F2)]->GetBinError(ibin);
			if(runNumber>=305967&& runNumber<=306460) return _hef201745[static_cast<int>(Periods::era2017F3)]->GetBinError(ibin);
			return 0;
		}
		else if(arm==1){
			if(runNumber>=297050&& runNumber<=299329) return _hef201756[static_cast<int>(Periods::era2017B)]->GetBinError(ibin);
			if(runNumber>=299368&& runNumber<=300780) return _hef201756[static_cast<int>(Periods::era2017C1)]->GetBinError(ibin);
			if(runNumber>=300806&& runNumber<=302029) return _hef201756[static_cast<int>(Periods::era2017C2)]->GetBinError(ibin);
			if(runNumber>=302031&& runNumber<=302663) return _hef201756[static_cast<int>(Periods::era2017D)]->GetBinError(ibin);
			if(runNumber>=303825&& runNumber<=304797) return _hef201756[static_cast<int>(Periods::era2017E)]->GetBinError(ibin);
			if(runNumber>=305044&& runNumber<=305114) return _hef201756[static_cast<int>(Periods::era2017F1)]->GetBinError(ibin);
			if(runNumber>=305178&& runNumber<=305902) return _hef201756[static_cast<int>(Periods::era2017F2)]->GetBinError(ibin);
			if(runNumber>=305967&& runNumber<=306460) return _hef201756[static_cast<int>(Periods::era2017F3)]->GetBinError(ibin);
			return 0;
		}
		else{ std::cout <<" wrong arm number (expect 0 or 1), return 0...\n"; return 0;}
	}

	float getRecoErr(float xi, int arm, unsigned int runNumber){
		if(!RecoInit){ std::cout << "ERROR: call getRecoErr() w/o proper initialization" << std::endl; return 0;}
		if(arm==0){
			if(runNumber>=297050&& runNumber<=302663) return _reco_err45[0]->Eval(xi);
			if(runNumber>=303825&& runNumber<=306460) return _reco_err45[1]->Eval(xi);
			return 0;
		}
		else if(arm==1){
			if(runNumber>=297050&& runNumber<=302663) return _reco_err56[0]->Eval(xi);
			if(runNumber>=303825&& runNumber<=306460) return _reco_err56[1]->Eval(xi);
			return 0;
		}
		else{ std::cout <<" wrong arm number (expect 0 or 1), return 0...\n"; return 0;}
	}
	
	float getXiHigh(int arm, unsigned int runNumber, float xangle){
		// from https://twiki.cern.ch/twiki/bin/view/CMS/TaggedProtonsGettingStarted#Fiducial_cuts
		if(xangle<120 || xangle>150) return 0; // sanity check
		if(arm<100){ // arm = 0
			if(runNumber<303825) return 0.066 + (3.54E-4 * xangle);
			if(runNumber>=303825) return 0.073 + (4.11E-4 * xangle);
			return 0;
		}
		else {
			if(runNumber<303825) return 0.062 + (5.96E-4 * xangle);
			if(runNumber>=303825) return 0.067 + (6.87E-4 * xangle);
			return 0;
		}
	}
	
	float getThXStarHigh(int arm, unsigned int runNumber, float xi, float xangle){
    // from https://twiki.cern.ch/twiki/bin/view/CMS/TaggedProtonsFiducialCuts
        if(xangle<120 || xangle>150) return 999; // sanity check
		float thX_max = 0;
        if(arm<100){ // arm = 0
            if(runNumber<303825) thX_max= -(8.71198E-07*xangle-0.000134726)+((xi<(0.000264704*xangle+0.081951))*-(4.32065E-05*xangle-0.0130746)+(xi>=(0.000264704*xangle+0.081951))*-(0.000183472*xangle-0.0395241))*(xi-(0.000264704*xangle+0.081951));
            else thX_max= -(8.92079E-07*xangle-0.000150214)+((xi<(0.000278622*xangle+0.0964383))*-(3.9541e-05*xangle-0.0115104)+(xi>=(0.000278622*xangle+0.0964383))*-(0.000108249*xangle-0.0249303))*(xi-(0.000278622*xangle+0.0964383));
        }
        else {
            if(runNumber<303825) thX_max= 3.43116E-05+((xi<(0.000626936*xangle+0.061324))*0.00654394+(xi>=(0.000626936*xangle+0.061324))*-(0.000145164*xangle-0.0272919))*(xi-(0.000626936*xangle+0.061324));
            else thX_max= 4.56961E-05+((xi<(0.00075625*xangle+0.0643361))*-(3.01107e-05*xangle-0.00985126)+(xi>=(0.00075625*xangle+0.0643361))*-(8.95437e-05*xangle-0.0169474))*(xi-(0.00075625*xangle+0.0643361));
        }
		return -thX_max;
    }
	
	private: 
	int _nbins; float _bw, _xmin=0, _xmax=0.2;
	bool RecoInit = false, EffInit = false;
	TFile * _file0 = NULL;
	TH1D *_hef201745[8], *_hef201756[8];
	TGraphErrors * _reco_err45[2], * _reco_err56[2];
	void init(std::string filename){
		if(filename.empty()) {
			std::cout << "Warning: PPSEff::init() No initialization file specified" << std::endl;
			return;
		}
		std::cout << "INFO: PPSEff::init() Reads eff histogram from "<<filename.c_str() << std::endl;
		_file0 = TFile::Open(filename.c_str());
		if(!_file0) std::cout  <<"ERROR: PPSEff::init() no such file "<< filename.c_str() << std::endl;
		
		if(filename.find("reco")!=std::string::npos){
			_reco_err45[0] = (TGraphErrors *)_file0->Get("2017_preTS2/multi rp-0/xi/g_systematics_vs_xi");
			_reco_err45[1] = (TGraphErrors *)_file0->Get("2017_postTS2/multi rp-0/xi/g_systematics_vs_xi");
			_reco_err56[0] = (TGraphErrors *)_file0->Get("2017_preTS2/multi rp-1/xi/g_systematics_vs_xi");
			_reco_err56[1] = (TGraphErrors *)_file0->Get("2017_postTS2/multi rp-1/xi/g_systematics_vs_xi");

			RecoInit=true;
		}
		else if(filename.find("Pixel")!=std::string::npos){
		// load the efficiency histograms
		_hef201745[static_cast<int>(Periods::era2017B)]  = (TH1D *)_file0->Get("Pixel/2017/2017B/h45_220_2017B_all_1D");
		_hef201756[static_cast<int>(Periods::era2017B)]  = (TH1D *)_file0->Get("Pixel/2017/2017B/h56_220_2017B_all_1D");
		_hef201745[static_cast<int>(Periods::era2017C1)] = (TH1D *)_file0->Get("Pixel/2017/2017C1/h45_220_2017C1_all_1D");
		_hef201756[static_cast<int>(Periods::era2017C1)] = (TH1D *)_file0->Get("Pixel/2017/2017C1/h56_220_2017C1_all_1D");
		_hef201745[static_cast<int>(Periods::era2017C2)] = (TH1D *)_file0->Get("Pixel/2017/2017C2/h45_220_2017C2_all_1D");
		_hef201756[static_cast<int>(Periods::era2017C2)] = (TH1D *)_file0->Get("Pixel/2017/2017C2/h56_220_2017C2_all_1D");
		_hef201745[static_cast<int>(Periods::era2017D)]  = (TH1D *)_file0->Get("Pixel/2017/2017D/h45_220_2017D_all_1D");
		_hef201756[static_cast<int>(Periods::era2017D)]  = (TH1D *)_file0->Get("Pixel/2017/2017D/h56_220_2017D_all_1D");
		_hef201745[static_cast<int>(Periods::era2017E)]  = (TH1D *)_file0->Get("Pixel/2017/2017E/h45_220_2017E_all_1D");
		_hef201756[static_cast<int>(Periods::era2017E)]  = (TH1D *)_file0->Get("Pixel/2017/2017E/h56_220_2017E_all_1D");
		_hef201745[static_cast<int>(Periods::era2017F1)] = (TH1D *)_file0->Get("Pixel/2017/2017F1/h45_220_2017F1_all_1D");
		_hef201756[static_cast<int>(Periods::era2017F1)] = (TH1D *)_file0->Get("Pixel/2017/2017F1/h56_220_2017F1_all_1D");
		_hef201745[static_cast<int>(Periods::era2017F2)] = (TH1D *)_file0->Get("Pixel/2017/2017F2/h45_220_2017F2_all_1D");
		_hef201756[static_cast<int>(Periods::era2017F2)] = (TH1D *)_file0->Get("Pixel/2017/2017F2/h56_220_2017F2_all_1D");
		_hef201745[static_cast<int>(Periods::era2017F3)] = (TH1D *)_file0->Get("Pixel/2017/2017F3/h45_220_2017F3_all_1D");
		_hef201756[static_cast<int>(Periods::era2017F3)] = (TH1D *)_file0->Get("Pixel/2017/2017F3/h56_220_2017F3_all_1D");
		
		_nbins = _hef201756[0]->GetNbinsX();
		_bw    = _hef201756[0]->GetBinWidth(1);
		_xmin  = _hef201756[0]->GetBinCenter(1) - 0.5 * _bw;
		_xmax  = _hef201756[0]->GetBinCenter(_nbins) + 0.5 * _bw;	
		
		EffInit=true;
		
		}
		else if(filename.find("Strips")!=std::string::npos){
		
		_hef201745[static_cast<int>(Periods::era2017B)]  = (TH1D *)_file0->Get("Strips/2017/2017B/h45_2017B_all_1D");
		_hef201756[static_cast<int>(Periods::era2017B)]  = (TH1D *)_file0->Get("Strips/2017/2017B/h56_2017B_all_1D");
		_hef201745[static_cast<int>(Periods::era2017C1)] = (TH1D *)_file0->Get("Strips/2017/2017C1/h45_2017C1_all_1D");
		_hef201756[static_cast<int>(Periods::era2017C1)] = (TH1D *)_file0->Get("Strips/2017/2017C1/h56_2017C1_all_1D");
		_hef201745[static_cast<int>(Periods::era2017C2)] = (TH1D *)_file0->Get("Strips/2017/2017C2/h45_2017C2_all_1D");
		_hef201756[static_cast<int>(Periods::era2017C2)] = (TH1D *)_file0->Get("Strips/2017/2017C2/h56_2017C2_all_1D");
		_hef201745[static_cast<int>(Periods::era2017D)]  = (TH1D *)_file0->Get("Strips/2017/2017D/h45_2017D_all_1D");
		_hef201756[static_cast<int>(Periods::era2017D)]  = (TH1D *)_file0->Get("Strips/2017/2017D/h56_2017D_all_1D");
		_hef201745[static_cast<int>(Periods::era2017E)]  = (TH1D *)_file0->Get("Strips/2017/2017E/h45_2017E_all_1D");
		_hef201756[static_cast<int>(Periods::era2017E)]  = (TH1D *)_file0->Get("Strips/2017/2017E/h56_2017E_all_1D");
		_hef201745[static_cast<int>(Periods::era2017F1)] = (TH1D *)_file0->Get("Strips/2017/2017F1/h45_2017F1_all_1D");
		_hef201756[static_cast<int>(Periods::era2017F1)] = (TH1D *)_file0->Get("Strips/2017/2017F1/h56_2017F1_all_1D");
		_hef201745[static_cast<int>(Periods::era2017F2)] = (TH1D *)_file0->Get("Strips/2017/2017F2/h45_2017F2_all_1D");
		_hef201756[static_cast<int>(Periods::era2017F2)] = (TH1D *)_file0->Get("Strips/2017/2017F2/h56_2017F2_all_1D");
		_hef201745[static_cast<int>(Periods::era2017F3)] = (TH1D *)_file0->Get("Strips/2017/2017F3/h45_2017F3_all_1D");
		_hef201756[static_cast<int>(Periods::era2017F3)] = (TH1D *)_file0->Get("Strips/2017/2017F3/h56_2017F3_all_1D");
		
		_nbins = _hef201756[0]->GetNbinsX();
		_bw    = _hef201756[0]->GetBinWidth(1);
		_xmin  = _hef201756[0]->GetBinCenter(1) - 0.5 * _bw;
		_xmax  = _hef201756[0]->GetBinCenter(_nbins) + 0.5 * _bw;	
		
		EffInit=true;

		}
	}
	
	
};

