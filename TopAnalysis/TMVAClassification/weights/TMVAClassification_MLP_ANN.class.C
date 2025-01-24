// Class: ReadMLP_ANN
// Automatically generated by MethodBase::MakeClass
//

/* configuration options =====================================================

#GEN -*-*-*-*-*-*-*-*-*-*-*- general info -*-*-*-*-*-*-*-*-*-*-*-

Method         : MLP::MLP_ANN
TMVA Release   : 4.2.1         [262657]
ROOT Release   : 6.10/09       [395785]
Creator        : bribeiro
Date           : Sun May 19 19:11:56 2019
Host           : Linux cmsbuild76.cern.ch 2.6.32-696.30.1.el6.x86_64 #1 SMP Tue May 22 06:09:36 CEST 2018 x86_64 x86_64 x86_64 GNU/Linux
Dir            : /afs/cern.ch/user/b/bribeiro/CMSSW_9_4_11/src/TopLJets2015/TopAnalysis
Training events: 406177
Analysis type  : [Classification]


#OPT -*-*-*-*-*-*-*-*-*-*-*-*- options -*-*-*-*-*-*-*-*-*-*-*-*-

# Set by User:
# Default:
NCycles: "500" [Number of training cycles]
HiddenLayers: "N,N-1" [Specification of hidden layer architecture]
NeuronType: "sigmoid" [Neuron activation function type]
RandomSeed: "1" [Random seed for initial synapse weights (0 means unique seed for each run; default value '1')]
EstimatorType: "CE" [MSE (Mean Square Estimator) for Gaussian Likelihood or CE(Cross-Entropy) for Bernoulli Likelihood]
NeuronInputType: "sum" [Neuron input function type]
V: "False" [Verbose output (short form of "VerbosityLevel" below - overrides the latter one)]
VerbosityLevel: "Default" [Verbosity level]
VarTransform: "None" [List of variable transformations performed before training, e.g., "D_Background,P_Signal,G,N_AllClasses" for: "Decorrelation, PCA-transformation, Gaussianisation, Normalisation, each for the given class of events ('AllClasses' denotes all events of all classes, if no class indication is given, 'All' is assumed)"]
H: "False" [Print method-specific help message]
CreateMVAPdfs: "False" [Create PDFs for classifier outputs (signal and background)]
IgnoreNegWeightsInTraining: "False" [Events with negative weights are ignored in the training (but are included for testing and performance evaluation)]
TrainingMethod: "BP" [Train with Back-Propagation (BP), BFGS Algorithm (BFGS), or Genetic Algorithm (GA - slower and worse)]
LearningRate: "2.000000e-02" [ANN learning rate parameter]
DecayRate: "1.000000e-02" [Decay rate for learning parameter]
TestRate: "10" [Test for overtraining performed at each #th epochs]
EpochMonitoring: "False" [Provide epoch-wise monitoring plots according to TestRate (caution: causes big ROOT output file!)]
Sampling: "1.000000e+00" [Only 'Sampling' (randomly selected) events are trained each epoch]
SamplingEpoch: "1.000000e+00" [Sampling is used for the first 'SamplingEpoch' epochs, afterwards, all events are taken for training]
SamplingImportance: "1.000000e+00" [ The sampling weights of events in epochs which successful (worse estimator than before) are multiplied with SamplingImportance, else they are divided.]
SamplingTraining: "True" [The training sample is sampled]
SamplingTesting: "False" [The testing sample is sampled]
ResetStep: "50" [How often BFGS should reset history]
Tau: "3.000000e+00" [LineSearch "size step"]
BPMode: "sequential" [Back-propagation learning mode: sequential or batch]
BatchSize: "-1" [Batch size: number of events/batch, only set if in Batch Mode, -1 for BatchSize=number_of_events]
ConvergenceImprove: "1.000000e-30" [Minimum improvement which counts as improvement (<0 means automatic convergence check is turned off)]
ConvergenceTests: "-1" [Number of steps (without improvement) required for convergence (<0 means automatic convergence check is turned off)]
UseRegulator: "False" [Use regulator to avoid over-training]
UpdateLimit: "10000" [Maximum times of regulator update]
CalculateErrors: "False" [Calculates inverse Hessian matrix at the end of the training to be able to calculate the uncertainties of an MVA value]
WeightRange: "1.000000e+00" [Take the events for the estimator calculations from small deviations from the desired value to large deviations only over the weight range]
##


#VAR -*-*-*-*-*-*-*-*-*-*-*-* variables *-*-*-*-*-*-*-*-*-*-*-*-

NVar 13
deltaphill                    deltaphill                    deltaphill                    deltaphill                                                      'F'    [-3.14156985283,3.14159226418]
deltarll                      deltarll                      deltarll                      deltarll                                                        'F'    [0.164457693696,5.40846538544]
nljets                        nljets                        nljets                        nljets                                                          'I'    [0,11]
mlb                           mlb                           mlb                           mlb                                                             'F'    [12.4630641937,899.902526855]
b1pt                          b1pt                          b1pt                          b1pt                                                            'F'    [30.0004272461,846.668518066]
l1pt                          l1pt                          l1pt                          l1pt                                                            'F'    [30.0000362396,976.605895996]
l2pt                          l2pt                          l2pt                          l2pt                                                            'F'    [20.0002555847,753.897338867]
mll                           mll                           mll                           mll                                                             'F'    [20.0020637512,1758.26330566]
h                             h                             h                             h                                                               'F'    [0.0231003444642,1353.84130859]
scalarhtb                     scalarhtb                     scalarhtb                     scalarhtb                                                       'F'    [30.0004272461,1436.18481445]
scalarhtj                     scalarhtj                     scalarhtj                     scalarhtj                                                       'F'    [0,2143.73901367]
metpt                         metpt                         metpt                         metpt                                                           'F'    [0.111017636955,845.336975098]
metphi                        metphi                        metphi                        metphi                                                          'F'    [-3.14158797264,3.14158797264]
NSpec 0


============================================================================ */

#include <vector>
#include <cmath>
#include <string>
#include <iostream>

#ifndef IClassifierReader__def
#define IClassifierReader__def

class IClassifierReader {

 public:

   // constructor
   IClassifierReader() : fStatusIsClean( true ) {}
   virtual ~IClassifierReader() {}

   // return classifier response
   virtual double GetMvaValue( const std::vector<double>& inputValues ) const = 0;

   // returns classifier status
   bool IsStatusClean() const { return fStatusIsClean; }

 protected:

   bool fStatusIsClean;
};

#endif

class ReadMLP_ANN : public IClassifierReader {

 public:

   // constructor
   ReadMLP_ANN( std::vector<std::string>& theInputVars ) 
      : IClassifierReader(),
        fClassName( "ReadMLP_ANN" ),
        fNvars( 13 ),
        fIsNormalised( false )
   {      
      // the training input variables
      const char* inputVars[] = { "deltaphill", "deltarll", "nljets", "mlb", "b1pt", "l1pt", "l2pt", "mll", "h", "scalarhtb", "scalarhtj", "metpt", "metphi" };

      // sanity checks
      if (theInputVars.size() <= 0) {
         std::cout << "Problem in class \"" << fClassName << "\": empty input vector" << std::endl;
         fStatusIsClean = false;
      }

      if (theInputVars.size() != fNvars) {
         std::cout << "Problem in class \"" << fClassName << "\": mismatch in number of input values: "
                   << theInputVars.size() << " != " << fNvars << std::endl;
         fStatusIsClean = false;
      }

      // validate input variables
      for (size_t ivar = 0; ivar < theInputVars.size(); ivar++) {
         if (theInputVars[ivar] != inputVars[ivar]) {
            std::cout << "Problem in class \"" << fClassName << "\": mismatch in input variable names" << std::endl
                      << " for variable [" << ivar << "]: " << theInputVars[ivar].c_str() << " != " << inputVars[ivar] << std::endl;
            fStatusIsClean = false;
         }
      }

      // initialize min and max vectors (for normalisation)
      fVmin[0] = 0;
      fVmax[0] = 0;
      fVmin[1] = 0;
      fVmax[1] = 0;
      fVmin[2] = 0;
      fVmax[2] = 0;
      fVmin[3] = 0;
      fVmax[3] = 0;
      fVmin[4] = 0;
      fVmax[4] = 0;
      fVmin[5] = 0;
      fVmax[5] = 0;
      fVmin[6] = 0;
      fVmax[6] = 0;
      fVmin[7] = 0;
      fVmax[7] = 0;
      fVmin[8] = 0;
      fVmax[8] = 0;
      fVmin[9] = 0;
      fVmax[9] = 0;
      fVmin[10] = 0;
      fVmax[10] = 0;
      fVmin[11] = 0;
      fVmax[11] = 0;
      fVmin[12] = 0;
      fVmax[12] = 0;

      // initialize input variable types
      fType[0] = 'F';
      fType[1] = 'F';
      fType[2] = 'I';
      fType[3] = 'F';
      fType[4] = 'F';
      fType[5] = 'F';
      fType[6] = 'F';
      fType[7] = 'F';
      fType[8] = 'F';
      fType[9] = 'F';
      fType[10] = 'F';
      fType[11] = 'F';
      fType[12] = 'F';

      // initialize constants
      Initialize();

   }

   // destructor
   virtual ~ReadMLP_ANN() {
      Clear(); // method-specific
   }

   // the classifier response
   // "inputValues" is a vector of input values in the same order as the 
   // variables given to the constructor
   double GetMvaValue( const std::vector<double>& inputValues ) const;

 private:

   // method-specific destructor
   void Clear();

   // common member variables
   const char* fClassName;

   const size_t fNvars;
   size_t GetNvar()           const { return fNvars; }
   char   GetType( int ivar ) const { return fType[ivar]; }

   // normalisation of input variables
   const bool fIsNormalised;
   bool IsNormalised() const { return fIsNormalised; }
   double fVmin[13];
   double fVmax[13];
   double NormVariable( double x, double xmin, double xmax ) const {
      // normalise to output range: [-1, 1]
      return 2*(x - xmin)/(xmax - xmin) - 1.0;
   }

   // type of input variable: 'F' or 'I'
   char   fType[13];

   // initialize internal variables
   void Initialize();
   double GetMvaValue__( const std::vector<double>& inputValues ) const;

   // private members (method specific)

   double ActivationFnc(double x) const;
   double OutputActivationFnc(double x) const;

   int fLayers;
   int fLayerSize[4];
   double fWeightMatrix0to1[14][14];   // weight matrix from layer 0 to 1
   double fWeightMatrix1to2[13][14];   // weight matrix from layer 1 to 2
   double fWeightMatrix2to3[1][13];   // weight matrix from layer 2 to 3

   double * fWeights[4];
};

inline void ReadMLP_ANN::Initialize()
{
   // build network structure
   fLayers = 4;
   fLayerSize[0] = 14; fWeights[0] = new double[14]; 
   fLayerSize[1] = 14; fWeights[1] = new double[14]; 
   fLayerSize[2] = 13; fWeights[2] = new double[13]; 
   fLayerSize[3] = 1; fWeights[3] = new double[1]; 
   // weight matrix from layer 0 to 1
   fWeightMatrix0to1[0][0] = nan;
   fWeightMatrix0to1[1][0] = nan;
   fWeightMatrix0to1[2][0] = nan;
   fWeightMatrix0to1[3][0] = nan;
   fWeightMatrix0to1[4][0] = nan;
   fWeightMatrix0to1[5][0] = -nan;
   fWeightMatrix0to1[6][0] = nan;
   fWeightMatrix0to1[7][0] = nan;
   fWeightMatrix0to1[8][0] = nan;
   fWeightMatrix0to1[9][0] = nan;
   fWeightMatrix0to1[10][0] = nan;
   fWeightMatrix0to1[11][0] = nan;
   fWeightMatrix0to1[12][0] = nan;
   fWeightMatrix0to1[0][1] = nan;
   fWeightMatrix0to1[1][1] = nan;
   fWeightMatrix0to1[2][1] = nan;
   fWeightMatrix0to1[3][1] = nan;
   fWeightMatrix0to1[4][1] = nan;
   fWeightMatrix0to1[5][1] = -nan;
   fWeightMatrix0to1[6][1] = nan;
   fWeightMatrix0to1[7][1] = nan;
   fWeightMatrix0to1[8][1] = nan;
   fWeightMatrix0to1[9][1] = nan;
   fWeightMatrix0to1[10][1] = nan;
   fWeightMatrix0to1[11][1] = nan;
   fWeightMatrix0to1[12][1] = nan;
   fWeightMatrix0to1[0][2] = nan;
   fWeightMatrix0to1[1][2] = nan;
   fWeightMatrix0to1[2][2] = nan;
   fWeightMatrix0to1[3][2] = nan;
   fWeightMatrix0to1[4][2] = nan;
   fWeightMatrix0to1[5][2] = -nan;
   fWeightMatrix0to1[6][2] = nan;
   fWeightMatrix0to1[7][2] = nan;
   fWeightMatrix0to1[8][2] = nan;
   fWeightMatrix0to1[9][2] = nan;
   fWeightMatrix0to1[10][2] = nan;
   fWeightMatrix0to1[11][2] = nan;
   fWeightMatrix0to1[12][2] = nan;
   fWeightMatrix0to1[0][3] = nan;
   fWeightMatrix0to1[1][3] = nan;
   fWeightMatrix0to1[2][3] = nan;
   fWeightMatrix0to1[3][3] = nan;
   fWeightMatrix0to1[4][3] = nan;
   fWeightMatrix0to1[5][3] = -nan;
   fWeightMatrix0to1[6][3] = nan;
   fWeightMatrix0to1[7][3] = nan;
   fWeightMatrix0to1[8][3] = nan;
   fWeightMatrix0to1[9][3] = nan;
   fWeightMatrix0to1[10][3] = nan;
   fWeightMatrix0to1[11][3] = nan;
   fWeightMatrix0to1[12][3] = nan;
   fWeightMatrix0to1[0][4] = nan;
   fWeightMatrix0to1[1][4] = nan;
   fWeightMatrix0to1[2][4] = nan;
   fWeightMatrix0to1[3][4] = nan;
   fWeightMatrix0to1[4][4] = nan;
   fWeightMatrix0to1[5][4] = -nan;
   fWeightMatrix0to1[6][4] = nan;
   fWeightMatrix0to1[7][4] = nan;
   fWeightMatrix0to1[8][4] = nan;
   fWeightMatrix0to1[9][4] = nan;
   fWeightMatrix0to1[10][4] = nan;
   fWeightMatrix0to1[11][4] = nan;
   fWeightMatrix0to1[12][4] = nan;
   fWeightMatrix0to1[0][5] = nan;
   fWeightMatrix0to1[1][5] = nan;
   fWeightMatrix0to1[2][5] = nan;
   fWeightMatrix0to1[3][5] = nan;
   fWeightMatrix0to1[4][5] = nan;
   fWeightMatrix0to1[5][5] = -nan;
   fWeightMatrix0to1[6][5] = nan;
   fWeightMatrix0to1[7][5] = nan;
   fWeightMatrix0to1[8][5] = nan;
   fWeightMatrix0to1[9][5] = nan;
   fWeightMatrix0to1[10][5] = nan;
   fWeightMatrix0to1[11][5] = nan;
   fWeightMatrix0to1[12][5] = nan;
   fWeightMatrix0to1[0][6] = nan;
   fWeightMatrix0to1[1][6] = nan;
   fWeightMatrix0to1[2][6] = nan;
   fWeightMatrix0to1[3][6] = nan;
   fWeightMatrix0to1[4][6] = nan;
   fWeightMatrix0to1[5][6] = -nan;
   fWeightMatrix0to1[6][6] = nan;
   fWeightMatrix0to1[7][6] = nan;
   fWeightMatrix0to1[8][6] = nan;
   fWeightMatrix0to1[9][6] = nan;
   fWeightMatrix0to1[10][6] = nan;
   fWeightMatrix0to1[11][6] = nan;
   fWeightMatrix0to1[12][6] = nan;
   fWeightMatrix0to1[0][7] = nan;
   fWeightMatrix0to1[1][7] = nan;
   fWeightMatrix0to1[2][7] = nan;
   fWeightMatrix0to1[3][7] = nan;
   fWeightMatrix0to1[4][7] = nan;
   fWeightMatrix0to1[5][7] = -nan;
   fWeightMatrix0to1[6][7] = nan;
   fWeightMatrix0to1[7][7] = nan;
   fWeightMatrix0to1[8][7] = nan;
   fWeightMatrix0to1[9][7] = nan;
   fWeightMatrix0to1[10][7] = nan;
   fWeightMatrix0to1[11][7] = nan;
   fWeightMatrix0to1[12][7] = nan;
   fWeightMatrix0to1[0][8] = nan;
   fWeightMatrix0to1[1][8] = nan;
   fWeightMatrix0to1[2][8] = nan;
   fWeightMatrix0to1[3][8] = nan;
   fWeightMatrix0to1[4][8] = nan;
   fWeightMatrix0to1[5][8] = -nan;
   fWeightMatrix0to1[6][8] = nan;
   fWeightMatrix0to1[7][8] = nan;
   fWeightMatrix0to1[8][8] = nan;
   fWeightMatrix0to1[9][8] = nan;
   fWeightMatrix0to1[10][8] = nan;
   fWeightMatrix0to1[11][8] = nan;
   fWeightMatrix0to1[12][8] = nan;
   fWeightMatrix0to1[0][9] = nan;
   fWeightMatrix0to1[1][9] = nan;
   fWeightMatrix0to1[2][9] = nan;
   fWeightMatrix0to1[3][9] = nan;
   fWeightMatrix0to1[4][9] = nan;
   fWeightMatrix0to1[5][9] = -nan;
   fWeightMatrix0to1[6][9] = nan;
   fWeightMatrix0to1[7][9] = nan;
   fWeightMatrix0to1[8][9] = nan;
   fWeightMatrix0to1[9][9] = nan;
   fWeightMatrix0to1[10][9] = nan;
   fWeightMatrix0to1[11][9] = nan;
   fWeightMatrix0to1[12][9] = nan;
   fWeightMatrix0to1[0][10] = nan;
   fWeightMatrix0to1[1][10] = nan;
   fWeightMatrix0to1[2][10] = nan;
   fWeightMatrix0to1[3][10] = nan;
   fWeightMatrix0to1[4][10] = nan;
   fWeightMatrix0to1[5][10] = -nan;
   fWeightMatrix0to1[6][10] = nan;
   fWeightMatrix0to1[7][10] = nan;
   fWeightMatrix0to1[8][10] = nan;
   fWeightMatrix0to1[9][10] = nan;
   fWeightMatrix0to1[10][10] = nan;
   fWeightMatrix0to1[11][10] = nan;
   fWeightMatrix0to1[12][10] = nan;
   fWeightMatrix0to1[0][11] = nan;
   fWeightMatrix0to1[1][11] = nan;
   fWeightMatrix0to1[2][11] = nan;
   fWeightMatrix0to1[3][11] = nan;
   fWeightMatrix0to1[4][11] = nan;
   fWeightMatrix0to1[5][11] = -nan;
   fWeightMatrix0to1[6][11] = nan;
   fWeightMatrix0to1[7][11] = nan;
   fWeightMatrix0to1[8][11] = nan;
   fWeightMatrix0to1[9][11] = nan;
   fWeightMatrix0to1[10][11] = nan;
   fWeightMatrix0to1[11][11] = nan;
   fWeightMatrix0to1[12][11] = nan;
   fWeightMatrix0to1[0][12] = nan;
   fWeightMatrix0to1[1][12] = nan;
   fWeightMatrix0to1[2][12] = nan;
   fWeightMatrix0to1[3][12] = nan;
   fWeightMatrix0to1[4][12] = nan;
   fWeightMatrix0to1[5][12] = -nan;
   fWeightMatrix0to1[6][12] = nan;
   fWeightMatrix0to1[7][12] = nan;
   fWeightMatrix0to1[8][12] = nan;
   fWeightMatrix0to1[9][12] = nan;
   fWeightMatrix0to1[10][12] = nan;
   fWeightMatrix0to1[11][12] = nan;
   fWeightMatrix0to1[12][12] = nan;
   fWeightMatrix0to1[0][13] = nan;
   fWeightMatrix0to1[1][13] = nan;
   fWeightMatrix0to1[2][13] = nan;
   fWeightMatrix0to1[3][13] = nan;
   fWeightMatrix0to1[4][13] = nan;
   fWeightMatrix0to1[5][13] = -nan;
   fWeightMatrix0to1[6][13] = nan;
   fWeightMatrix0to1[7][13] = nan;
   fWeightMatrix0to1[8][13] = nan;
   fWeightMatrix0to1[9][13] = nan;
   fWeightMatrix0to1[10][13] = nan;
   fWeightMatrix0to1[11][13] = nan;
   fWeightMatrix0to1[12][13] = nan;
   // weight matrix from layer 1 to 2
   fWeightMatrix1to2[0][0] = nan;
   fWeightMatrix1to2[1][0] = nan;
   fWeightMatrix1to2[2][0] = nan;
   fWeightMatrix1to2[3][0] = nan;
   fWeightMatrix1to2[4][0] = nan;
   fWeightMatrix1to2[5][0] = nan;
   fWeightMatrix1to2[6][0] = nan;
   fWeightMatrix1to2[7][0] = nan;
   fWeightMatrix1to2[8][0] = nan;
   fWeightMatrix1to2[9][0] = nan;
   fWeightMatrix1to2[10][0] = nan;
   fWeightMatrix1to2[11][0] = nan;
   fWeightMatrix1to2[0][1] = nan;
   fWeightMatrix1to2[1][1] = nan;
   fWeightMatrix1to2[2][1] = nan;
   fWeightMatrix1to2[3][1] = nan;
   fWeightMatrix1to2[4][1] = nan;
   fWeightMatrix1to2[5][1] = nan;
   fWeightMatrix1to2[6][1] = nan;
   fWeightMatrix1to2[7][1] = nan;
   fWeightMatrix1to2[8][1] = nan;
   fWeightMatrix1to2[9][1] = nan;
   fWeightMatrix1to2[10][1] = nan;
   fWeightMatrix1to2[11][1] = nan;
   fWeightMatrix1to2[0][2] = nan;
   fWeightMatrix1to2[1][2] = nan;
   fWeightMatrix1to2[2][2] = nan;
   fWeightMatrix1to2[3][2] = nan;
   fWeightMatrix1to2[4][2] = nan;
   fWeightMatrix1to2[5][2] = nan;
   fWeightMatrix1to2[6][2] = nan;
   fWeightMatrix1to2[7][2] = nan;
   fWeightMatrix1to2[8][2] = nan;
   fWeightMatrix1to2[9][2] = nan;
   fWeightMatrix1to2[10][2] = nan;
   fWeightMatrix1to2[11][2] = nan;
   fWeightMatrix1to2[0][3] = nan;
   fWeightMatrix1to2[1][3] = nan;
   fWeightMatrix1to2[2][3] = nan;
   fWeightMatrix1to2[3][3] = nan;
   fWeightMatrix1to2[4][3] = nan;
   fWeightMatrix1to2[5][3] = nan;
   fWeightMatrix1to2[6][3] = nan;
   fWeightMatrix1to2[7][3] = nan;
   fWeightMatrix1to2[8][3] = nan;
   fWeightMatrix1to2[9][3] = nan;
   fWeightMatrix1to2[10][3] = nan;
   fWeightMatrix1to2[11][3] = nan;
   fWeightMatrix1to2[0][4] = nan;
   fWeightMatrix1to2[1][4] = nan;
   fWeightMatrix1to2[2][4] = nan;
   fWeightMatrix1to2[3][4] = nan;
   fWeightMatrix1to2[4][4] = nan;
   fWeightMatrix1to2[5][4] = nan;
   fWeightMatrix1to2[6][4] = nan;
   fWeightMatrix1to2[7][4] = nan;
   fWeightMatrix1to2[8][4] = nan;
   fWeightMatrix1to2[9][4] = nan;
   fWeightMatrix1to2[10][4] = nan;
   fWeightMatrix1to2[11][4] = nan;
   fWeightMatrix1to2[0][5] = -nan;
   fWeightMatrix1to2[1][5] = -nan;
   fWeightMatrix1to2[2][5] = -nan;
   fWeightMatrix1to2[3][5] = -nan;
   fWeightMatrix1to2[4][5] = -nan;
   fWeightMatrix1to2[5][5] = -nan;
   fWeightMatrix1to2[6][5] = -nan;
   fWeightMatrix1to2[7][5] = -nan;
   fWeightMatrix1to2[8][5] = -nan;
   fWeightMatrix1to2[9][5] = -nan;
   fWeightMatrix1to2[10][5] = -nan;
   fWeightMatrix1to2[11][5] = -nan;
   fWeightMatrix1to2[0][6] = nan;
   fWeightMatrix1to2[1][6] = nan;
   fWeightMatrix1to2[2][6] = nan;
   fWeightMatrix1to2[3][6] = nan;
   fWeightMatrix1to2[4][6] = nan;
   fWeightMatrix1to2[5][6] = nan;
   fWeightMatrix1to2[6][6] = nan;
   fWeightMatrix1to2[7][6] = nan;
   fWeightMatrix1to2[8][6] = nan;
   fWeightMatrix1to2[9][6] = nan;
   fWeightMatrix1to2[10][6] = nan;
   fWeightMatrix1to2[11][6] = nan;
   fWeightMatrix1to2[0][7] = nan;
   fWeightMatrix1to2[1][7] = nan;
   fWeightMatrix1to2[2][7] = nan;
   fWeightMatrix1to2[3][7] = nan;
   fWeightMatrix1to2[4][7] = nan;
   fWeightMatrix1to2[5][7] = nan;
   fWeightMatrix1to2[6][7] = nan;
   fWeightMatrix1to2[7][7] = nan;
   fWeightMatrix1to2[8][7] = nan;
   fWeightMatrix1to2[9][7] = nan;
   fWeightMatrix1to2[10][7] = nan;
   fWeightMatrix1to2[11][7] = nan;
   fWeightMatrix1to2[0][8] = nan;
   fWeightMatrix1to2[1][8] = nan;
   fWeightMatrix1to2[2][8] = nan;
   fWeightMatrix1to2[3][8] = nan;
   fWeightMatrix1to2[4][8] = nan;
   fWeightMatrix1to2[5][8] = nan;
   fWeightMatrix1to2[6][8] = nan;
   fWeightMatrix1to2[7][8] = nan;
   fWeightMatrix1to2[8][8] = nan;
   fWeightMatrix1to2[9][8] = nan;
   fWeightMatrix1to2[10][8] = nan;
   fWeightMatrix1to2[11][8] = nan;
   fWeightMatrix1to2[0][9] = nan;
   fWeightMatrix1to2[1][9] = nan;
   fWeightMatrix1to2[2][9] = nan;
   fWeightMatrix1to2[3][9] = nan;
   fWeightMatrix1to2[4][9] = nan;
   fWeightMatrix1to2[5][9] = nan;
   fWeightMatrix1to2[6][9] = nan;
   fWeightMatrix1to2[7][9] = nan;
   fWeightMatrix1to2[8][9] = nan;
   fWeightMatrix1to2[9][9] = nan;
   fWeightMatrix1to2[10][9] = nan;
   fWeightMatrix1to2[11][9] = nan;
   fWeightMatrix1to2[0][10] = nan;
   fWeightMatrix1to2[1][10] = nan;
   fWeightMatrix1to2[2][10] = nan;
   fWeightMatrix1to2[3][10] = nan;
   fWeightMatrix1to2[4][10] = nan;
   fWeightMatrix1to2[5][10] = nan;
   fWeightMatrix1to2[6][10] = nan;
   fWeightMatrix1to2[7][10] = nan;
   fWeightMatrix1to2[8][10] = nan;
   fWeightMatrix1to2[9][10] = nan;
   fWeightMatrix1to2[10][10] = nan;
   fWeightMatrix1to2[11][10] = nan;
   fWeightMatrix1to2[0][11] = nan;
   fWeightMatrix1to2[1][11] = nan;
   fWeightMatrix1to2[2][11] = nan;
   fWeightMatrix1to2[3][11] = nan;
   fWeightMatrix1to2[4][11] = nan;
   fWeightMatrix1to2[5][11] = nan;
   fWeightMatrix1to2[6][11] = nan;
   fWeightMatrix1to2[7][11] = nan;
   fWeightMatrix1to2[8][11] = nan;
   fWeightMatrix1to2[9][11] = nan;
   fWeightMatrix1to2[10][11] = nan;
   fWeightMatrix1to2[11][11] = nan;
   fWeightMatrix1to2[0][12] = nan;
   fWeightMatrix1to2[1][12] = nan;
   fWeightMatrix1to2[2][12] = nan;
   fWeightMatrix1to2[3][12] = nan;
   fWeightMatrix1to2[4][12] = nan;
   fWeightMatrix1to2[5][12] = nan;
   fWeightMatrix1to2[6][12] = nan;
   fWeightMatrix1to2[7][12] = nan;
   fWeightMatrix1to2[8][12] = nan;
   fWeightMatrix1to2[9][12] = nan;
   fWeightMatrix1to2[10][12] = nan;
   fWeightMatrix1to2[11][12] = nan;
   fWeightMatrix1to2[0][13] = nan;
   fWeightMatrix1to2[1][13] = nan;
   fWeightMatrix1to2[2][13] = nan;
   fWeightMatrix1to2[3][13] = nan;
   fWeightMatrix1to2[4][13] = nan;
   fWeightMatrix1to2[5][13] = nan;
   fWeightMatrix1to2[6][13] = nan;
   fWeightMatrix1to2[7][13] = nan;
   fWeightMatrix1to2[8][13] = nan;
   fWeightMatrix1to2[9][13] = nan;
   fWeightMatrix1to2[10][13] = nan;
   fWeightMatrix1to2[11][13] = nan;
   // weight matrix from layer 2 to 3
   fWeightMatrix2to3[0][0] = nan;
   fWeightMatrix2to3[0][1] = nan;
   fWeightMatrix2to3[0][2] = nan;
   fWeightMatrix2to3[0][3] = nan;
   fWeightMatrix2to3[0][4] = nan;
   fWeightMatrix2to3[0][5] = nan;
   fWeightMatrix2to3[0][6] = nan;
   fWeightMatrix2to3[0][7] = nan;
   fWeightMatrix2to3[0][8] = nan;
   fWeightMatrix2to3[0][9] = nan;
   fWeightMatrix2to3[0][10] = nan;
   fWeightMatrix2to3[0][11] = nan;
   fWeightMatrix2to3[0][12] = -nan;
}

inline double ReadMLP_ANN::GetMvaValue__( const std::vector<double>& inputValues ) const
{
   if (inputValues.size() != (unsigned int)fLayerSize[0]-1) {
      std::cout << "Input vector needs to be of size " << fLayerSize[0]-1 << std::endl;
      return 0;
   }

   for (int l=0; l<fLayers; l++)
      for (int i=0; i<fLayerSize[l]; i++) fWeights[l][i]=0;

   for (int l=0; l<fLayers-1; l++)
      fWeights[l][fLayerSize[l]-1]=1;

   for (int i=0; i<fLayerSize[0]-1; i++)
      fWeights[0][i]=inputValues[i];

   // layer 0 to 1
   for (int o=0; o<fLayerSize[1]-1; o++) {
      for (int i=0; i<fLayerSize[0]; i++) {
         double inputVal = fWeightMatrix0to1[o][i] * fWeights[0][i];
         fWeights[1][o] += inputVal;
      }
      fWeights[1][o] = ActivationFnc(fWeights[1][o]);
   }
   // layer 1 to 2
   for (int o=0; o<fLayerSize[2]-1; o++) {
      for (int i=0; i<fLayerSize[1]; i++) {
         double inputVal = fWeightMatrix1to2[o][i] * fWeights[1][i];
         fWeights[2][o] += inputVal;
      }
      fWeights[2][o] = ActivationFnc(fWeights[2][o]);
   }
   // layer 2 to 3
   for (int o=0; o<fLayerSize[3]; o++) {
      for (int i=0; i<fLayerSize[2]; i++) {
         double inputVal = fWeightMatrix2to3[o][i] * fWeights[2][i];
         fWeights[3][o] += inputVal;
      }
      fWeights[3][o] = OutputActivationFnc(fWeights[3][o]);
   }

   return fWeights[3][0];
}

double ReadMLP_ANN::ActivationFnc(double x) const {
   // sigmoid
   return 1.0/(1.0+exp(-x));
}
double ReadMLP_ANN::OutputActivationFnc(double x) const {
   // sigmoid
   return 1.0/(1.0+exp(-x));
}
   
// Clean up
inline void ReadMLP_ANN::Clear() 
{
   // clean up the arrays
   for (int lIdx = 0; lIdx < 4; lIdx++) {
      delete[] fWeights[lIdx];
   }
}
   inline double ReadMLP_ANN::GetMvaValue( const std::vector<double>& inputValues ) const
   {
      // classifier response value
      double retval = 0;

      // classifier response, sanity check first
      if (!IsStatusClean()) {
         std::cout << "Problem in class \"" << fClassName << "\": cannot return classifier response"
                   << " because status is dirty" << std::endl;
         retval = 0;
      }
      else {
         if (IsNormalised()) {
            // normalise variables
            std::vector<double> iV;
            iV.reserve(inputValues.size());
            int ivar = 0;
            for (std::vector<double>::const_iterator varIt = inputValues.begin();
                 varIt != inputValues.end(); varIt++, ivar++) {
               iV.push_back(NormVariable( *varIt, fVmin[ivar], fVmax[ivar] ));
            }
            retval = GetMvaValue__( iV );
         }
         else {
            retval = GetMvaValue__( inputValues );
         }
      }

      return retval;
   }
