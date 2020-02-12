#include "dataset/weights/TMVAClassification_TMlp_ANN.h"
#include <cmath>

double TMVAClassification_TMlp_ANN::Value(int index,double in0,double in1,double in2,double in3,double in4,double in5,double in6,double in7,double in8,double in9,double in10,double in11,double in12,double in13,double in14,double in15,double in16,double in17,double in18,double in19,double in20,double in21,double in22,double in23,double in24,double in25,double in26,double in27,double in28,double in29,double in30,double in31,double in32,double in33) {
   input0 = (in0 - 128.053)/78.3855;
   input1 = (in1 - 78.0516)/46.2777;
   input2 = (in2 - 0.149549)/1.85765;
   input3 = (in3 - 75.7785)/42.4931;
   input4 = (in4 - -0.0347016)/0.956063;
   input5 = (in5 - -0.0626661)/1.82388;
   input6 = (in6 - 0.0773255)/0.0504442;
   input7 = (in7 - 51.7358)/31.8874;
   input8 = (in8 - -0.00422567)/1.05991;
   input9 = (in9 - 0.0222719)/1.84286;
   input10 = (in10 - 0.0300275)/0.051492;
   input11 = (in11 - 103.005)/50.0732;
   input12 = (in12 - 0.00160838)/0.987557;
   input13 = (in13 - -0.0507469)/1.8203;
   input14 = (in14 - 13.6222)/5.09996;
   input15 = (in15 - 61.7956)/30.9632;
   input16 = (in16 - -0.0379866)/1.00667;
   input17 = (in17 - -0.0333628)/1.77844;
   input18 = (in18 - 9.68274)/3.5861;
   input19 = (in19 - 2.37161)/0.816146;
   input20 = (in20 - 0.0835048)/2.11912;
   input21 = (in21 - 69.3171)/23.7577;
   input22 = (in22 - 6854.51)/22536.4;
   input23 = (in23 - 6130.46)/15970.9;
   input24 = (in24 - 95048.1)/201239;
   input25 = (in25 - 329549)/306654;
   input26 = (in26 - -0.0137512)/0.695718;
   input27 = (in27 - 3.26598)/1.35358;
   input28 = (in28 - 0.303259)/0.532103;
   input29 = (in29 - -0.280818)/0.542746;
   input30 = (in30 - 914.574)/371.924;
   input31 = (in31 - -0.143231)/0.35412;
   input32 = (in32 - 531.05)/151.977;
   input33 = (in33 - -1.05274)/0.765535;
   switch(index) {
     case 0:
         return neuron0x7c647f0();
     default:
         return 0.;
   }
}

double TMVAClassification_TMlp_ANN::Value(int index, double* input) {
   input0 = (input[0] - 128.053)/78.3855;
   input1 = (input[1] - 78.0516)/46.2777;
   input2 = (input[2] - 0.149549)/1.85765;
   input3 = (input[3] - 75.7785)/42.4931;
   input4 = (input[4] - -0.0347016)/0.956063;
   input5 = (input[5] - -0.0626661)/1.82388;
   input6 = (input[6] - 0.0773255)/0.0504442;
   input7 = (input[7] - 51.7358)/31.8874;
   input8 = (input[8] - -0.00422567)/1.05991;
   input9 = (input[9] - 0.0222719)/1.84286;
   input10 = (input[10] - 0.0300275)/0.051492;
   input11 = (input[11] - 103.005)/50.0732;
   input12 = (input[12] - 0.00160838)/0.987557;
   input13 = (input[13] - -0.0507469)/1.8203;
   input14 = (input[14] - 13.6222)/5.09996;
   input15 = (input[15] - 61.7956)/30.9632;
   input16 = (input[16] - -0.0379866)/1.00667;
   input17 = (input[17] - -0.0333628)/1.77844;
   input18 = (input[18] - 9.68274)/3.5861;
   input19 = (input[19] - 2.37161)/0.816146;
   input20 = (input[20] - 0.0835048)/2.11912;
   input21 = (input[21] - 69.3171)/23.7577;
   input22 = (input[22] - 6854.51)/22536.4;
   input23 = (input[23] - 6130.46)/15970.9;
   input24 = (input[24] - 95048.1)/201239;
   input25 = (input[25] - 329549)/306654;
   input26 = (input[26] - -0.0137512)/0.695718;
   input27 = (input[27] - 3.26598)/1.35358;
   input28 = (input[28] - 0.303259)/0.532103;
   input29 = (input[29] - -0.280818)/0.542746;
   input30 = (input[30] - 914.574)/371.924;
   input31 = (input[31] - -0.143231)/0.35412;
   input32 = (input[32] - 531.05)/151.977;
   input33 = (input[33] - -1.05274)/0.765535;
   switch(index) {
     case 0:
         return neuron0x7c647f0();
     default:
         return 0.;
   }
}

double TMVAClassification_TMlp_ANN::neuron0x6078290() {
   return input0;
}

double TMVAClassification_TMlp_ANN::neuron0x6078540() {
   return input1;
}

double TMVAClassification_TMlp_ANN::neuron0x63d6190() {
   return input2;
}

double TMVAClassification_TMlp_ANN::neuron0x63d64d0() {
   return input3;
}

double TMVAClassification_TMlp_ANN::neuron0x6251640() {
   return input4;
}

double TMVAClassification_TMlp_ANN::neuron0x46213e0() {
   return input5;
}

double TMVAClassification_TMlp_ANN::neuron0x4621720() {
   return input6;
}

double TMVAClassification_TMlp_ANN::neuron0x54fbed0() {
   return input7;
}

double TMVAClassification_TMlp_ANN::neuron0x7376fc0() {
   return input8;
}

double TMVAClassification_TMlp_ANN::neuron0x7377300() {
   return input9;
}

double TMVAClassification_TMlp_ANN::neuron0x6a82e50() {
   return input10;
}

double TMVAClassification_TMlp_ANN::neuron0x6636ca0() {
   return input11;
}

double TMVAClassification_TMlp_ANN::neuron0x6636fe0() {
   return input12;
}

double TMVAClassification_TMlp_ANN::neuron0x51a0a30() {
   return input13;
}

double TMVAClassification_TMlp_ANN::neuron0x4d1fad0() {
   return input14;
}

double TMVAClassification_TMlp_ANN::neuron0x4d1fe10() {
   return input15;
}

double TMVAClassification_TMlp_ANN::neuron0x4c00f40() {
   return input16;
}

double TMVAClassification_TMlp_ANN::neuron0x657be70() {
   return input17;
}

double TMVAClassification_TMlp_ANN::neuron0x7ec13f0() {
   return input18;
}

double TMVAClassification_TMlp_ANN::neuron0x7ec1730() {
   return input19;
}

double TMVAClassification_TMlp_ANN::neuron0x6c315b0() {
   return input20;
}

double TMVAClassification_TMlp_ANN::neuron0x6c318f0() {
   return input21;
}

double TMVAClassification_TMlp_ANN::neuron0x638c0d0() {
   return input22;
}

double TMVAClassification_TMlp_ANN::neuron0x60b21d0() {
   return input23;
}

double TMVAClassification_TMlp_ANN::neuron0x60b2510() {
   return input24;
}

double TMVAClassification_TMlp_ANN::neuron0x4eb4da0() {
   return input25;
}

double TMVAClassification_TMlp_ANN::neuron0x4eb50e0() {
   return input26;
}

double TMVAClassification_TMlp_ANN::neuron0x6077dc0() {
   return input27;
}

double TMVAClassification_TMlp_ANN::neuron0x597c140() {
   return input28;
}

double TMVAClassification_TMlp_ANN::neuron0x597c480() {
   return input29;
}

double TMVAClassification_TMlp_ANN::neuron0x55c7800() {
   return input30;
}

double TMVAClassification_TMlp_ANN::neuron0x55c7b40() {
   return input31;
}

double TMVAClassification_TMlp_ANN::neuron0x7f7a090() {
   return input32;
}

double TMVAClassification_TMlp_ANN::neuron0x673e5e0() {
   return input33;
}

double TMVAClassification_TMlp_ANN::input0x753f310() {
   double input = -0.0545908;
   input += synapse0x7b4eee0();
   input += synapse0x6542830();
   input += synapse0x46218b0();
   input += synapse0x7377490();
   input += synapse0x51a0e90();
   input += synapse0x5b75120();
   input += synapse0x5b75160();
   input += synapse0x5b751a0();
   input += synapse0x5b751e0();
   input += synapse0x5b75220();
   input += synapse0x5b75260();
   input += synapse0x5b752a0();
   input += synapse0x5b752e0();
   input += synapse0x5b75320();
   input += synapse0x5b75360();
   input += synapse0x5b753a0();
   input += synapse0x6637170();
   input += synapse0x4d1ffa0();
   input += synapse0x657c240();
   input += synapse0x58480c0();
   input += synapse0x753f720();
   input += synapse0x7ec18c0();
   input += synapse0x7db6eb0();
   input += synapse0x7db6ef0();
   input += synapse0x74caad0();
   input += synapse0x74cab10();
   input += synapse0x73fea40();
   input += synapse0x73fea80();
   input += synapse0x63a4e90();
   input += synapse0x63a4ed0();
   input += synapse0x78c3700();
   input += synapse0x78c3740();
   input += synapse0x5a3c390();
   input += synapse0x5a3c3d0();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x753f310() {
   double input = input0x753f310();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x5b753e0() {
   double input = -0.213937;
   input += synapse0x753f530();
   input += synapse0x5b75570();
   input += synapse0x7143630();
   input += synapse0x7143670();
   input += synapse0x5397400();
   input += synapse0x5397440();
   input += synapse0x7e79e10();
   input += synapse0x7e79e50();
   input += synapse0x52693a0();
   input += synapse0x52693e0();
   input += synapse0x5b8eaa0();
   input += synapse0x5b8eae0();
   input += synapse0x66c4d40();
   input += synapse0x66c4d80();
   input += synapse0x5a3caf0();
   input += synapse0x5a3cb30();
   input += synapse0x657bdf0();
   input += synapse0x657be30();
   input += synapse0x4e1f770();
   input += synapse0x4e1f7b0();
   input += synapse0x6c948b0();
   input += synapse0x6c948f0();
   input += synapse0x6c94930();
   input += synapse0x6c94970();
   input += synapse0x6c949b0();
   input += synapse0x6c949f0();
   input += synapse0x6c94a30();
   input += synapse0x6c94a70();
   input += synapse0x6c94ab0();
   input += synapse0x6c94af0();
   input += synapse0x6c94b30();
   input += synapse0x7770a60();
   input += synapse0x4b43130();
   input += synapse0x638ed20();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x5b753e0() {
   double input = input0x5b753e0();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x64be3a0() {
   double input = 0.403588;
   input += synapse0x4e80b60();
   input += synapse0x4e80ba0();
   input += synapse0x4e80be0();
   input += synapse0x4e80c20();
   input += synapse0x4e80c60();
   input += synapse0x4e80ca0();
   input += synapse0x6a410a0();
   input += synapse0x5a6b500();
   input += synapse0x6327690();
   input += synapse0x6f46b40();
   input += synapse0x4b2e3b0();
   input += synapse0x5d37470();
   input += synapse0x6dd1390();
   input += synapse0x4b60740();
   input += synapse0x753f090();
   input += synapse0x4d68df0();
   input += synapse0x77c6a20();
   input += synapse0x5b04510();
   input += synapse0x5478800();
   input += synapse0x753f6c0();
   input += synapse0x6bfc2b0();
   input += synapse0x6bfc2f0();
   input += synapse0x6bfc330();
   input += synapse0x6bfc370();
   input += synapse0x6c94c80();
   input += synapse0x6c94cc0();
   input += synapse0x6c94d00();
   input += synapse0x6c94d40();
   input += synapse0x6c94d80();
   input += synapse0x6c94dc0();
   input += synapse0x6c94e00();
   input += synapse0x7ddcaf0();
   input += synapse0x6c94b70();
   input += synapse0x6c94bb0();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x64be3a0() {
   double input = input0x64be3a0();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x7ddcd40() {
   double input = -0.30322;
   input += synapse0x7ddcff0();
   input += synapse0x7ddd030();
   input += synapse0x7ddd070();
   input += synapse0x4ccf0a0();
   input += synapse0x4ccf0e0();
   input += synapse0x4ccf120();
   input += synapse0x4ccf160();
   input += synapse0x4ccf1a0();
   input += synapse0x4ccf1e0();
   input += synapse0x4ccf220();
   input += synapse0x4ccf260();
   input += synapse0x4ccf2a0();
   input += synapse0x4ccf2e0();
   input += synapse0x4ccf320();
   input += synapse0x4ccf360();
   input += synapse0x4ccf3a0();
   input += synapse0x6c94bf0();
   input += synapse0x6c94c30();
   input += synapse0x4ccf4f0();
   input += synapse0x4ccf530();
   input += synapse0x4ccf570();
   input += synapse0x4ccf5b0();
   input += synapse0x4ccf5f0();
   input += synapse0x5b8ec90();
   input += synapse0x5b8ecd0();
   input += synapse0x5b8ed10();
   input += synapse0x5b8ed50();
   input += synapse0x64bdf90();
   input += synapse0x64bdfd0();
   input += synapse0x64be010();
   input += synapse0x64be050();
   input += synapse0x64be090();
   input += synapse0x64be2e0();
   input += synapse0x64be320();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x7ddcd40() {
   double input = input0x7ddcd40();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x5b8ed90() {
   double input = 1.02775;
   input += synapse0x64be360();
   input += synapse0x5b8f0d0();
   input += synapse0x5b8f110();
   input += synapse0x5b8f150();
   input += synapse0x5b8f190();
   input += synapse0x5b8f1d0();
   input += synapse0x5b8f210();
   input += synapse0x4ccf3e0();
   input += synapse0x4ccf420();
   input += synapse0x4ccf460();
   input += synapse0x4ccf4a0();
   input += synapse0x66200c0();
   input += synapse0x6620100();
   input += synapse0x6620140();
   input += synapse0x6620180();
   input += synapse0x66201c0();
   input += synapse0x5b8ef20();
   input += synapse0x5b8ef60();
   input += synapse0x6620310();
   input += synapse0x6620350();
   input += synapse0x6620390();
   input += synapse0x66203d0();
   input += synapse0x6620410();
   input += synapse0x6620450();
   input += synapse0x6620490();
   input += synapse0x66204d0();
   input += synapse0x6620510();
   input += synapse0x6620550();
   input += synapse0x6620590();
   input += synapse0x66205d0();
   input += synapse0x6620610();
   input += synapse0x6613610();
   input += synapse0x6620200();
   input += synapse0x6620240();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x5b8ed90() {
   double input = input0x5b8ed90();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x6613860() {
   double input = -0.36947;
   input += synapse0x6613b10();
   input += synapse0x6613b50();
   input += synapse0x6613b90();
   input += synapse0x7da6990();
   input += synapse0x7da69d0();
   input += synapse0x7da6a10();
   input += synapse0x7da6a50();
   input += synapse0x7da6a90();
   input += synapse0x7da6ad0();
   input += synapse0x7da6b10();
   input += synapse0x7da6b50();
   input += synapse0x7da6b90();
   input += synapse0x7da6bd0();
   input += synapse0x7da6c10();
   input += synapse0x7da6c50();
   input += synapse0x7da6c90();
   input += synapse0x6620280();
   input += synapse0x66202c0();
   input += synapse0x7da6de0();
   input += synapse0x7da6e20();
   input += synapse0x7da6e60();
   input += synapse0x7da6ea0();
   input += synapse0x7da6ee0();
   input += synapse0x52d6ad0();
   input += synapse0x52d6b10();
   input += synapse0x52d6b50();
   input += synapse0x52d6b90();
   input += synapse0x52d6bd0();
   input += synapse0x52d6c10();
   input += synapse0x52d6c50();
   input += synapse0x52d6c90();
   input += synapse0x52d6cd0();
   input += synapse0x7da6cd0();
   input += synapse0x7da6d10();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x6613860() {
   double input = input0x6613860();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x5fa9b00() {
   double input = -0.0965629;
   input += synapse0x5fa9db0();
   input += synapse0x5fa9df0();
   input += synapse0x5fa9e30();
   input += synapse0x5fa9e70();
   input += synapse0x5fa9eb0();
   input += synapse0x5fa9ef0();
   input += synapse0x5fa9f30();
   input += synapse0x5fa9f70();
   input += synapse0x5fa9fb0();
   input += synapse0x5fa9ff0();
   input += synapse0x5faa030();
   input += synapse0x5faa070();
   input += synapse0x52d6f20();
   input += synapse0x52d6f60();
   input += synapse0x52d6fa0();
   input += synapse0x52d6fe0();
   input += synapse0x52d7020();
   input += synapse0x7da6d50();
   input += synapse0x7da6d90();
   input += synapse0x574e090();
   input += synapse0x574e0d0();
   input += synapse0x574e110();
   input += synapse0x574e150();
   input += synapse0x574e190();
   input += synapse0x574e1d0();
   input += synapse0x574e210();
   input += synapse0x574e250();
   input += synapse0x574e290();
   input += synapse0x574e2d0();
   input += synapse0x574e310();
   input += synapse0x574e350();
   input += synapse0x574e390();
   input += synapse0x574df80();
   input += synapse0x574dfc0();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x5fa9b00() {
   double input = input0x5fa9b00();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x6e4f550() {
   double input = -0.206118;
   input += synapse0x6e4f800();
   input += synapse0x6e4f840();
   input += synapse0x6e4f880();
   input += synapse0x6e4f8c0();
   input += synapse0x574e3d0();
   input += synapse0x574e410();
   input += synapse0x574e450();
   input += synapse0x574e490();
   input += synapse0x574e4d0();
   input += synapse0x6c8a1f0();
   input += synapse0x6c8a230();
   input += synapse0x6c8a270();
   input += synapse0x6c8a2b0();
   input += synapse0x6c8a2f0();
   input += synapse0x6c8a330();
   input += synapse0x6c8a370();
   input += synapse0x574e000();
   input += synapse0x574e040();
   input += synapse0x6c8a4c0();
   input += synapse0x6c8a500();
   input += synapse0x6c8a540();
   input += synapse0x6c8a580();
   input += synapse0x6c8a5c0();
   input += synapse0x6c8a600();
   input += synapse0x6c8a640();
   input += synapse0x6c8a680();
   input += synapse0x6c8a6c0();
   input += synapse0x6c8a700();
   input += synapse0x6c8a740();
   input += synapse0x768af40();
   input += synapse0x768af80();
   input += synapse0x768afc0();
   input += synapse0x6c8a3b0();
   input += synapse0x6c8a3f0();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x6e4f550() {
   double input = input0x6e4f550();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x768b210() {
   double input = -0.555524;
   input += synapse0x755ec50();
   input += synapse0x755ec90();
   input += synapse0x755ecd0();
   input += synapse0x755ed10();
   input += synapse0x755ed50();
   input += synapse0x755ed90();
   input += synapse0x755edd0();
   input += synapse0x755ee10();
   input += synapse0x755ee50();
   input += synapse0x755ee90();
   input += synapse0x755eed0();
   input += synapse0x755ef10();
   input += synapse0x755ef50();
   input += synapse0x755ef90();
   input += synapse0x755efd0();
   input += synapse0x755f010();
   input += synapse0x6c8a430();
   input += synapse0x6c8a470();
   input += synapse0x755f160();
   input += synapse0x755f1a0();
   input += synapse0x5f3b5c0();
   input += synapse0x5f3b600();
   input += synapse0x5f3b640();
   input += synapse0x5f3b680();
   input += synapse0x5f3b6c0();
   input += synapse0x5f3b700();
   input += synapse0x5f3b740();
   input += synapse0x5f3b780();
   input += synapse0x5f3b7c0();
   input += synapse0x5f3b800();
   input += synapse0x5f3b840();
   input += synapse0x5f3b880();
   input += synapse0x5f3bad0();
   input += synapse0x5f3bb10();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x768b210() {
   double input = input0x768b210();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x660fe00() {
   double input = 0.541218;
   input += synapse0x6610140();
   input += synapse0x6610180();
   input += synapse0x66101c0();
   input += synapse0x6610200();
   input += synapse0x6610240();
   input += synapse0x6610280();
   input += synapse0x66102c0();
   input += synapse0x6610300();
   input += synapse0x6610340();
   input += synapse0x6610380();
   input += synapse0x755f050();
   input += synapse0x755f090();
   input += synapse0x755f0d0();
   input += synapse0x755f110();
   input += synapse0x5fe8d90();
   input += synapse0x5fe8dd0();
   input += synapse0x660ff90();
   input += synapse0x660ffd0();
   input += synapse0x5fe8f20();
   input += synapse0x5fe8f60();
   input += synapse0x5fe8fa0();
   input += synapse0x5fe8fe0();
   input += synapse0x5fe9020();
   input += synapse0x5fe9060();
   input += synapse0x5fe90a0();
   input += synapse0x5fe90e0();
   input += synapse0x5fe9120();
   input += synapse0x5fe9160();
   input += synapse0x5fe91a0();
   input += synapse0x5fe91e0();
   input += synapse0x5fe9220();
   input += synapse0x5fe9260();
   input += synapse0x5fe92a0();
   input += synapse0x5fe92e0();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x660fe00() {
   double input = input0x660fe00();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x5dbd1d0() {
   double input = 0.0749373;
   input += synapse0x5dbd510();
   input += synapse0x5fe8e10();
   input += synapse0x5fe8e50();
   input += synapse0x5fe8e90();
   input += synapse0x5fe8ed0();
   input += synapse0x4c19d30();
   input += synapse0x4c19d70();
   input += synapse0x4c19db0();
   input += synapse0x4c19df0();
   input += synapse0x4c19e30();
   input += synapse0x4c19e70();
   input += synapse0x4c19eb0();
   input += synapse0x4c19ef0();
   input += synapse0x4c19f30();
   input += synapse0x4c19f70();
   input += synapse0x4c19fb0();
   input += synapse0x5dbd360();
   input += synapse0x5dbd3a0();
   input += synapse0x4c1a100();
   input += synapse0x4c1a140();
   input += synapse0x4c1a180();
   input += synapse0x4c1a1c0();
   input += synapse0x4c1a200();
   input += synapse0x4c1a240();
   input += synapse0x4c1a280();
   input += synapse0x7c6ec00();
   input += synapse0x7c6ec40();
   input += synapse0x7c6ec80();
   input += synapse0x7c6ecc0();
   input += synapse0x7c6ed00();
   input += synapse0x7c6ed40();
   input += synapse0x7c6ed80();
   input += synapse0x4c19ff0();
   input += synapse0x4c1a030();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x5dbd1d0() {
   double input = input0x5dbd1d0();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x7c6efd0() {
   double input = -0.23582;
   input += synapse0x675ca30();
   input += synapse0x675ca70();
   input += synapse0x675cab0();
   input += synapse0x675caf0();
   input += synapse0x675cb30();
   input += synapse0x675cb70();
   input += synapse0x675cbb0();
   input += synapse0x675cbf0();
   input += synapse0x675cc30();
   input += synapse0x675cc70();
   input += synapse0x675ccb0();
   input += synapse0x675ccf0();
   input += synapse0x675cd30();
   input += synapse0x675cd70();
   input += synapse0x675cdb0();
   input += synapse0x675cdf0();
   input += synapse0x7c6f160();
   input += synapse0x4c1a070();
   input += synapse0x4c1a0b0();
   input += synapse0x675ce30();
   input += synapse0x675ce70();
   input += synapse0x624f5b0();
   input += synapse0x624f5f0();
   input += synapse0x624f630();
   input += synapse0x624f670();
   input += synapse0x624f6b0();
   input += synapse0x624f6f0();
   input += synapse0x624f730();
   input += synapse0x624f770();
   input += synapse0x624f7b0();
   input += synapse0x624f7f0();
   input += synapse0x624f830();
   input += synapse0x624f4a0();
   input += synapse0x624f4e0();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x7c6efd0() {
   double input = input0x7c6efd0();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x624f870() {
   double input = 0.0698867;
   input += synapse0x762b740();
   input += synapse0x762b780();
   input += synapse0x762b7c0();
   input += synapse0x762b800();
   input += synapse0x762b840();
   input += synapse0x762b880();
   input += synapse0x762b8c0();
   input += synapse0x762b900();
   input += synapse0x762b940();
   input += synapse0x762b980();
   input += synapse0x624fa00();
   input += synapse0x565b920();
   input += synapse0x565b960();
   input += synapse0x565b9a0();
   input += synapse0x565b9e0();
   input += synapse0x565ba20();
   input += synapse0x624f520();
   input += synapse0x624f560();
   input += synapse0x565bb70();
   input += synapse0x565bbb0();
   input += synapse0x565bbf0();
   input += synapse0x565bc30();
   input += synapse0x565bc70();
   input += synapse0x565bcb0();
   input += synapse0x565bcf0();
   input += synapse0x565bd30();
   input += synapse0x565bd70();
   input += synapse0x565bdb0();
   input += synapse0x565bdf0();
   input += synapse0x565be30();
   input += synapse0x565be70();
   input += synapse0x710c860();
   input += synapse0x565ba60();
   input += synapse0x565baa0();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x624f870() {
   double input = input0x624f870();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x710cab0() {
   double input = 0.176412;
   input += synapse0x710cd60();
   input += synapse0x710cda0();
   input += synapse0x710cde0();
   input += synapse0x7ddc3c0();
   input += synapse0x7ddc400();
   input += synapse0x7ddc440();
   input += synapse0x7ddc480();
   input += synapse0x7ddc4c0();
   input += synapse0x7ddc500();
   input += synapse0x7ddc540();
   input += synapse0x7ddc580();
   input += synapse0x7ddc5c0();
   input += synapse0x7ddc600();
   input += synapse0x7ddc640();
   input += synapse0x7ddc680();
   input += synapse0x7ddc6c0();
   input += synapse0x565bae0();
   input += synapse0x565bb20();
   input += synapse0x7ddc810();
   input += synapse0x7ddc850();
   input += synapse0x7ddc890();
   input += synapse0x7ddc8d0();
   input += synapse0x7ddc910();
   input += synapse0x4d16ed0();
   input += synapse0x4d16f10();
   input += synapse0x4d16f50();
   input += synapse0x4d16f90();
   input += synapse0x4d16fd0();
   input += synapse0x4d17010();
   input += synapse0x4d17050();
   input += synapse0x4d17090();
   input += synapse0x4d170d0();
   input += synapse0x7ddc700();
   input += synapse0x7ddc740();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x710cab0() {
   double input = input0x710cab0();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x67c49b0() {
   double input = 0.700195;
   input += synapse0x67c4c60();
   input += synapse0x67c4ca0();
   input += synapse0x67c4ce0();
   input += synapse0x67c4d20();
   input += synapse0x67c4d60();
   input += synapse0x67c4da0();
   input += synapse0x67c4de0();
   input += synapse0x67c4e20();
   input += synapse0x67c4e60();
   input += synapse0x67c4ea0();
   input += synapse0x67c4ee0();
   input += synapse0x67c4f20();
   input += synapse0x4d17320();
   input += synapse0x4d17360();
   input += synapse0x4d173a0();
   input += synapse0x4d173e0();
   input += synapse0x4d17420();
   input += synapse0x7ddc780();
   input += synapse0x7ddc7c0();
   input += synapse0x4b24cb0();
   input += synapse0x4b24cf0();
   input += synapse0x4b24d30();
   input += synapse0x4b24d70();
   input += synapse0x4b24db0();
   input += synapse0x4b24df0();
   input += synapse0x4b24e30();
   input += synapse0x4b24e70();
   input += synapse0x4b24eb0();
   input += synapse0x4b24ef0();
   input += synapse0x4b24f30();
   input += synapse0x4b24f70();
   input += synapse0x4b24fb0();
   input += synapse0x4b24ba0();
   input += synapse0x4b24be0();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x67c49b0() {
   double input = input0x67c49b0();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x77723c0() {
   double input = -0.0502223;
   input += synapse0x7772670();
   input += synapse0x4b25100();
   input += synapse0x6078420();
   input += synapse0x6078460();
   input += synapse0x7689420();
   input += synapse0x7689460();
   input += synapse0x7ec1eb0();
   input += synapse0x63d63b0();
   input += synapse0x63d63f0();
   input += synapse0x753f630();
   input += synapse0x753f670();
   input += synapse0x5101260();
   input += synapse0x6251860();
   input += synapse0x62518a0();
   input += synapse0x4621600();
   input += synapse0x4621640();
   input += synapse0x4e1f4f0();
   input += synapse0x54fc0f0();
   input += synapse0x54fc130();
   input += synapse0x73771e0();
   input += synapse0x7377220();
   input += synapse0x6a40ac0();
   input += synapse0x6a83070();
   input += synapse0x6a830b0();
   input += synapse0x6636ec0();
   input += synapse0x6636f00();
   input += synapse0x653de20();
   input += synapse0x51a0c50();
   input += synapse0x51a0c90();
   input += synapse0x4d1fcf0();
   input += synapse0x4d1fd30();
   input += synapse0x6f3ce70();
   input += synapse0x51a0e00();
   input += synapse0x51a0e40();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x77723c0() {
   double input = input0x77723c0();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x5796be0() {
   double input = -0.293141;
   input += synapse0x5796d70();
   input += synapse0x5796db0();
   input += synapse0x5796df0();
   input += synapse0x5796e30();
   input += synapse0x5796e70();
   input += synapse0x5796eb0();
   input += synapse0x5796ef0();
   input += synapse0x5796f30();
   input += synapse0x5796f70();
   input += synapse0x5796fb0();
   input += synapse0x5796ff0();
   input += synapse0x5797030();
   input += synapse0x5797070();
   input += synapse0x57970b0();
   input += synapse0x57970f0();
   input += synapse0x5797130();
   input += synapse0x7f2a100();
   input += synapse0x7f2a140();
   input += synapse0x7ec1610();
   input += synapse0x7ec1650();
   input += synapse0x4e1f5c0();
   input += synapse0x4e1f600();
   input += synapse0x6c317d0();
   input += synapse0x6c31810();
   input += synapse0x638bfb0();
   input += synapse0x638bff0();
   input += synapse0x638c2f0();
   input += synapse0x638c330();
   input += synapse0x60b23f0();
   input += synapse0x60b2430();
   input += synapse0x638c410();
   input += synapse0x638c450();
   input += synapse0x4eb4fc0();
   input += synapse0x4eb5000();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x5796be0() {
   double input = input0x5796be0();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x68c4f20() {
   double input = 0.505503;
   input += synapse0x68c50b0();
   input += synapse0x68c50f0();
   input += synapse0x68c5130();
   input += synapse0x68c5170();
   input += synapse0x6078100();
   input += synapse0x6078140();
   input += synapse0x55c7a20();
   input += synapse0x55c7a60();
   input += synapse0x7f79f70();
   input += synapse0x7f79fb0();
   input += synapse0x7f7a2b0();
   input += synapse0x7f7a2f0();
   input += synapse0x7f7a3d0();
   input += synapse0x7f7a410();
   input += synapse0x4b24c20();
   input += synapse0x4b24c60();
   input += synapse0x6077ca0();
   input += synapse0x6077ce0();
   input += synapse0x6251a10();
   input += synapse0x6251a50();
   input += synapse0x54fc2a0();
   input += synapse0x54fc2e0();
   input += synapse0x6a83220();
   input += synapse0x6a83260();
   input += synapse0x77726b0();
   input += synapse0x77726f0();
   input += synapse0x7772730();
   input += synapse0x4e80ce0();
   input += synapse0x4e80d20();
   input += synapse0x4e80d60();
   input += synapse0x5fa37d0();
   input += synapse0x5fa3810();
   input += synapse0x68c4c00();
   input += synapse0x68c4c40();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x68c4f20() {
   double input = input0x68c4f20();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x5fa3a60() {
   double input = 0.578737;
   input += synapse0x5fa3d10();
   input += synapse0x5fa3d50();
   input += synapse0x669deb0();
   input += synapse0x669def0();
   input += synapse0x669df30();
   input += synapse0x669df70();
   input += synapse0x669dfb0();
   input += synapse0x669dff0();
   input += synapse0x669e030();
   input += synapse0x669e070();
   input += synapse0x669e0b0();
   input += synapse0x669e0f0();
   input += synapse0x669e130();
   input += synapse0x669e170();
   input += synapse0x669e1b0();
   input += synapse0x669e1f0();
   input += synapse0x68c4c80();
   input += synapse0x68c4cc0();
   input += synapse0x669e340();
   input += synapse0x669e380();
   input += synapse0x669e3c0();
   input += synapse0x669e400();
   input += synapse0x59a8e90();
   input += synapse0x59a8ed0();
   input += synapse0x59a8f10();
   input += synapse0x59a8f50();
   input += synapse0x59a8f90();
   input += synapse0x59a8fd0();
   input += synapse0x59a9010();
   input += synapse0x59a9050();
   input += synapse0x59a9090();
   input += synapse0x59a90d0();
   input += synapse0x669e230();
   input += synapse0x669e270();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x5fa3a60() {
   double input = input0x5fa3a60();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x58886c0() {
   double input = -0.313097;
   input += synapse0x5888970();
   input += synapse0x58889b0();
   input += synapse0x58889f0();
   input += synapse0x5888a30();
   input += synapse0x5888a70();
   input += synapse0x5888ab0();
   input += synapse0x5888af0();
   input += synapse0x5888b30();
   input += synapse0x5888b70();
   input += synapse0x5888bb0();
   input += synapse0x5888bf0();
   input += synapse0x5888c30();
   input += synapse0x59a9320();
   input += synapse0x59a9360();
   input += synapse0x59a93a0();
   input += synapse0x59a93e0();
   input += synapse0x669e2b0();
   input += synapse0x669e2f0();
   input += synapse0x7b58a90();
   input += synapse0x7b58ad0();
   input += synapse0x7b58b10();
   input += synapse0x7b58b50();
   input += synapse0x7b58b90();
   input += synapse0x7b58bd0();
   input += synapse0x7b58c10();
   input += synapse0x7b58c50();
   input += synapse0x7b58c90();
   input += synapse0x7b58cd0();
   input += synapse0x7b58d10();
   input += synapse0x7b58d50();
   input += synapse0x7b58d90();
   input += synapse0x7b58dd0();
   input += synapse0x7b58980();
   input += synapse0x7b589c0();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x58886c0() {
   double input = input0x58886c0();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x6dcd6b0() {
   double input = 0.0981711;
   input += synapse0x6dcd960();
   input += synapse0x6dcd9a0();
   input += synapse0x6dcd9e0();
   input += synapse0x6dcda20();
   input += synapse0x7b58e10();
   input += synapse0x7b58e50();
   input += synapse0x7b58e90();
   input += synapse0x7b58ed0();
   input += synapse0x61d3c10();
   input += synapse0x61d3c50();
   input += synapse0x61d3c90();
   input += synapse0x61d3cd0();
   input += synapse0x61d3d10();
   input += synapse0x61d3d50();
   input += synapse0x61d3d90();
   input += synapse0x61d3dd0();
   input += synapse0x7b58a00();
   input += synapse0x7b58a40();
   input += synapse0x61d3f20();
   input += synapse0x61d3f60();
   input += synapse0x61d3fa0();
   input += synapse0x61d3fe0();
   input += synapse0x61d4020();
   input += synapse0x61d4060();
   input += synapse0x61d40a0();
   input += synapse0x61d40e0();
   input += synapse0x61d4120();
   input += synapse0x61d4160();
   input += synapse0x7c1a1e0();
   input += synapse0x7c1a220();
   input += synapse0x7c1a260();
   input += synapse0x7c1a2a0();
   input += synapse0x61d3e10();
   input += synapse0x61d3e50();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x6dcd6b0() {
   double input = input0x6dcd6b0();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x7c1a4f0() {
   double input = 0.144774;
   input += synapse0x51663a0();
   input += synapse0x51663e0();
   input += synapse0x5166420();
   input += synapse0x5166460();
   input += synapse0x51664a0();
   input += synapse0x51664e0();
   input += synapse0x5166520();
   input += synapse0x5166560();
   input += synapse0x51665a0();
   input += synapse0x51665e0();
   input += synapse0x5166620();
   input += synapse0x5166660();
   input += synapse0x51666a0();
   input += synapse0x51666e0();
   input += synapse0x5166720();
   input += synapse0x5166760();
   input += synapse0x61d3e90();
   input += synapse0x61d3ed0();
   input += synapse0x51668b0();
   input += synapse0x51668f0();
   input += synapse0x6708be0();
   input += synapse0x6708c20();
   input += synapse0x6708c60();
   input += synapse0x6708ca0();
   input += synapse0x6708ce0();
   input += synapse0x6708d20();
   input += synapse0x6708d60();
   input += synapse0x6708da0();
   input += synapse0x6708de0();
   input += synapse0x6708e20();
   input += synapse0x6708e60();
   input += synapse0x6708ea0();
   input += synapse0x67090f0();
   input += synapse0x6709130();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x7c1a4f0() {
   double input = input0x7c1a4f0();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x7f702c0() {
   double input = 0.2942;
   input += synapse0x7f70600();
   input += synapse0x7f70640();
   input += synapse0x7f70680();
   input += synapse0x7f706c0();
   input += synapse0x7f70700();
   input += synapse0x7f70740();
   input += synapse0x7f70780();
   input += synapse0x7f707c0();
   input += synapse0x7f70800();
   input += synapse0x7f70840();
   input += synapse0x51667a0();
   input += synapse0x51667e0();
   input += synapse0x5166820();
   input += synapse0x5166860();
   input += synapse0x5bee050();
   input += synapse0x5bee090();
   input += synapse0x7f70450();
   input += synapse0x7f70490();
   input += synapse0x5bee1e0();
   input += synapse0x5bee220();
   input += synapse0x5bee260();
   input += synapse0x5bee2a0();
   input += synapse0x5bee2e0();
   input += synapse0x5bee320();
   input += synapse0x5bee360();
   input += synapse0x5bee3a0();
   input += synapse0x5bee3e0();
   input += synapse0x5bee420();
   input += synapse0x5bee460();
   input += synapse0x5bee4a0();
   input += synapse0x5bee4e0();
   input += synapse0x5bee520();
   input += synapse0x5bee560();
   input += synapse0x5bee5a0();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x7f702c0() {
   double input = input0x7f702c0();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x7887220() {
   double input = -0.636375;
   input += synapse0x7887560();
   input += synapse0x5bee0d0();
   input += synapse0x5bee110();
   input += synapse0x5bee150();
   input += synapse0x5bee190();
   input += synapse0x729a710();
   input += synapse0x729a750();
   input += synapse0x729a790();
   input += synapse0x729a7d0();
   input += synapse0x729a810();
   input += synapse0x729a850();
   input += synapse0x729a890();
   input += synapse0x729a8d0();
   input += synapse0x729a910();
   input += synapse0x729a950();
   input += synapse0x729a990();
   input += synapse0x78873b0();
   input += synapse0x78873f0();
   input += synapse0x729aae0();
   input += synapse0x729ab20();
   input += synapse0x729ab60();
   input += synapse0x729aba0();
   input += synapse0x729abe0();
   input += synapse0x729ac20();
   input += synapse0x729ac60();
   input += synapse0x79caad0();
   input += synapse0x79cab10();
   input += synapse0x79cab50();
   input += synapse0x79cab90();
   input += synapse0x79cabd0();
   input += synapse0x79cac10();
   input += synapse0x79cac50();
   input += synapse0x729a9d0();
   input += synapse0x729aa10();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x7887220() {
   double input = input0x7887220();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x79caea0() {
   double input = -0.0664895;
   input += synapse0x78f6890();
   input += synapse0x78f68d0();
   input += synapse0x78f6910();
   input += synapse0x78f6950();
   input += synapse0x78f6990();
   input += synapse0x78f69d0();
   input += synapse0x78f6a10();
   input += synapse0x78f6a50();
   input += synapse0x78f6a90();
   input += synapse0x78f6ad0();
   input += synapse0x78f6b10();
   input += synapse0x78f6b50();
   input += synapse0x78f6b90();
   input += synapse0x78f6bd0();
   input += synapse0x78f6c10();
   input += synapse0x78f6c50();
   input += synapse0x79cb030();
   input += synapse0x729aa50();
   input += synapse0x729aa90();
   input += synapse0x78f6c90();
   input += synapse0x78f6cd0();
   input += synapse0x4d36e30();
   input += synapse0x4d36e70();
   input += synapse0x4d36eb0();
   input += synapse0x4d36ef0();
   input += synapse0x4d36f30();
   input += synapse0x4d36f70();
   input += synapse0x4d36fb0();
   input += synapse0x4d36ff0();
   input += synapse0x4d37030();
   input += synapse0x4d37070();
   input += synapse0x4d370b0();
   input += synapse0x4d36d20();
   input += synapse0x4d36d60();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x79caea0() {
   double input = input0x79caea0();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x4d370f0() {
   double input = 0.0627009;
   input += synapse0x7519ca0();
   input += synapse0x7519ce0();
   input += synapse0x7519d20();
   input += synapse0x7519d60();
   input += synapse0x7519da0();
   input += synapse0x7519de0();
   input += synapse0x7519e20();
   input += synapse0x7519e60();
   input += synapse0x7519ea0();
   input += synapse0x7519ee0();
   input += synapse0x4d37280();
   input += synapse0x72af600();
   input += synapse0x72af640();
   input += synapse0x72af680();
   input += synapse0x72af6c0();
   input += synapse0x72af700();
   input += synapse0x4d36da0();
   input += synapse0x4d36de0();
   input += synapse0x72af850();
   input += synapse0x72af890();
   input += synapse0x72af8d0();
   input += synapse0x72af910();
   input += synapse0x72af950();
   input += synapse0x72af990();
   input += synapse0x72af9d0();
   input += synapse0x72afa10();
   input += synapse0x72afa50();
   input += synapse0x72afa90();
   input += synapse0x72afad0();
   input += synapse0x72afb10();
   input += synapse0x72afb50();
   input += synapse0x7c7c960();
   input += synapse0x72af740();
   input += synapse0x72af780();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x4d370f0() {
   double input = input0x4d370f0();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x7c7cbb0() {
   double input = -0.306061;
   input += synapse0x7c7ce60();
   input += synapse0x7c7cea0();
   input += synapse0x7c7cee0();
   input += synapse0x7957230();
   input += synapse0x7957270();
   input += synapse0x79572b0();
   input += synapse0x79572f0();
   input += synapse0x7957330();
   input += synapse0x7957370();
   input += synapse0x79573b0();
   input += synapse0x79573f0();
   input += synapse0x7957430();
   input += synapse0x7957470();
   input += synapse0x79574b0();
   input += synapse0x79574f0();
   input += synapse0x7957530();
   input += synapse0x72af7c0();
   input += synapse0x72af800();
   input += synapse0x7957680();
   input += synapse0x79576c0();
   input += synapse0x7957700();
   input += synapse0x7957740();
   input += synapse0x7957780();
   input += synapse0x638eee0();
   input += synapse0x638ef20();
   input += synapse0x638ef60();
   input += synapse0x638efa0();
   input += synapse0x638efe0();
   input += synapse0x638f020();
   input += synapse0x638f060();
   input += synapse0x638f0a0();
   input += synapse0x638f0e0();
   input += synapse0x7957570();
   input += synapse0x79575b0();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x7c7cbb0() {
   double input = input0x7c7cbb0();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x5751ec0() {
   double input = -0.0384165;
   input += synapse0x5752170();
   input += synapse0x57521b0();
   input += synapse0x57521f0();
   input += synapse0x5752230();
   input += synapse0x5752270();
   input += synapse0x57522b0();
   input += synapse0x57522f0();
   input += synapse0x5752330();
   input += synapse0x5752370();
   input += synapse0x57523b0();
   input += synapse0x57523f0();
   input += synapse0x5752430();
   input += synapse0x638f330();
   input += synapse0x638f370();
   input += synapse0x638f3b0();
   input += synapse0x638f3f0();
   input += synapse0x638f430();
   input += synapse0x79575f0();
   input += synapse0x7957630();
   input += synapse0x4f17030();
   input += synapse0x4f17070();
   input += synapse0x4f170b0();
   input += synapse0x4f170f0();
   input += synapse0x4f17130();
   input += synapse0x4f17170();
   input += synapse0x4f171b0();
   input += synapse0x4f171f0();
   input += synapse0x4f17230();
   input += synapse0x4f17270();
   input += synapse0x4f172b0();
   input += synapse0x4f172f0();
   input += synapse0x4f17330();
   input += synapse0x4f16f20();
   input += synapse0x4f16f60();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x5751ec0() {
   double input = input0x5751ec0();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x7da6470() {
   double input = -1.16896;
   input += synapse0x7da6720();
   input += synapse0x7da6760();
   input += synapse0x7da67a0();
   input += synapse0x7da67e0();
   input += synapse0x4f17370();
   input += synapse0x4f173b0();
   input += synapse0x4f173f0();
   input += synapse0x4f17430();
   input += synapse0x4f17470();
   input += synapse0x73df960();
   input += synapse0x73df9a0();
   input += synapse0x73df9e0();
   input += synapse0x73dfa20();
   input += synapse0x73dfa60();
   input += synapse0x73dfaa0();
   input += synapse0x73dfae0();
   input += synapse0x4f16fa0();
   input += synapse0x4f16fe0();
   input += synapse0x73dfc30();
   input += synapse0x73dfc70();
   input += synapse0x73dfcb0();
   input += synapse0x73dfcf0();
   input += synapse0x73dfd30();
   input += synapse0x73dfd70();
   input += synapse0x73dfdb0();
   input += synapse0x73dfdf0();
   input += synapse0x73dfe30();
   input += synapse0x73dfe70();
   input += synapse0x73dfeb0();
   input += synapse0x6e1ff20();
   input += synapse0x6e1ff60();
   input += synapse0x6e1ffa0();
   input += synapse0x73dfb20();
   input += synapse0x73dfb60();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x7da6470() {
   double input = input0x7da6470();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x6e201f0() {
   double input = -0.529276;
   input += synapse0x6e204a0();
   input += synapse0x6220920();
   input += synapse0x6220960();
   input += synapse0x62209a0();
   input += synapse0x62209e0();
   input += synapse0x6220a20();
   input += synapse0x6220a60();
   input += synapse0x6220aa0();
   input += synapse0x6220ae0();
   input += synapse0x6220b20();
   input += synapse0x6220b60();
   input += synapse0x6220ba0();
   input += synapse0x6220be0();
   input += synapse0x6220c20();
   input += synapse0x6220c60();
   input += synapse0x6220ca0();
   input += synapse0x73dfba0();
   input += synapse0x73dfbe0();
   input += synapse0x6220df0();
   input += synapse0x6220e30();
   input += synapse0x6220e70();
   input += synapse0x5e99310();
   input += synapse0x5e99350();
   input += synapse0x5e99390();
   input += synapse0x5e993d0();
   input += synapse0x5e99410();
   input += synapse0x5e99450();
   input += synapse0x5e99490();
   input += synapse0x5e994d0();
   input += synapse0x5e99510();
   input += synapse0x5e99550();
   input += synapse0x5e99590();
   input += synapse0x5e997e0();
   input += synapse0x5e99820();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x6e201f0() {
   double input = input0x6e201f0();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x7229820() {
   double input = 0.125606;
   input += synapse0x5e99860();
   input += synapse0x6220ce0();
   input += synapse0x6220d20();
   input += synapse0x6220d60();
   input += synapse0x6220da0();
   input += synapse0x690d990();
   input += synapse0x690d9d0();
   input += synapse0x690da10();
   input += synapse0x690da50();
   input += synapse0x690da90();
   input += synapse0x690dad0();
   input += synapse0x673e3d0();
   input += synapse0x673e410();
   input += synapse0x673e450();
   input += synapse0x673e490();
   input += synapse0x673e4d0();
   input += synapse0x72299b0();
   input += synapse0x72299f0();
   input += synapse0x673e510();
   input += synapse0x673e550();
   input += synapse0x673e590();
   input += synapse0x7229c70();
   input += synapse0x7229cb0();
   input += synapse0x7229cf0();
   input += synapse0x7229d30();
   input += synapse0x7229d70();
   input += synapse0x5fe52a0();
   input += synapse0x5fe52e0();
   input += synapse0x5fe5320();
   input += synapse0x5fe5360();
   input += synapse0x5fe53a0();
   input += synapse0x5fe53e0();
   input += synapse0x7229b60();
   input += synapse0x7229ba0();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x7229820() {
   double input = input0x7229820();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x5fe5630() {
   double input = 0.0514677;
   input += synapse0x5c98940();
   input += synapse0x4b24ff0();
   input += synapse0x4b25030();
   input += synapse0x4b25070();
   input += synapse0x4b250b0();
   input += synapse0x5c98da0();
   input += synapse0x5c98de0();
   input += synapse0x5c98e20();
   input += synapse0x7ec1da0();
   input += synapse0x7ec1de0();
   input += synapse0x7ec1e20();
   input += synapse0x7ec1e60();
   input += synapse0x5101150();
   input += synapse0x5101190();
   input += synapse0x51011d0();
   input += synapse0x5101210();
   input += synapse0x7229be0();
   input += synapse0x7229c20();
   input += synapse0x77836f0();
   input += synapse0x6a408a0();
   input += synapse0x7783730();
   input += synapse0x653d8d0();
   input += synapse0x7783770();
   input += synapse0x77837b0();
   input += synapse0x653db20();
   input += synapse0x77837f0();
   input += synapse0x7783830();
   input += synapse0x653dd70();
   input += synapse0x653ddb0();
   input += synapse0x6c76130();
   input += synapse0x6f3cd60();
   input += synapse0x6f3cda0();
   input += synapse0x6f3cde0();
   input += synapse0x6f3ce20();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x5fe5630() {
   double input = input0x5fe5630();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x6e364e0() {
   double input = 0.266809;
   input += synapse0x7f2a080();
   input += synapse0x7f2a0c0();
   input += synapse0x4e1f470();
   input += synapse0x4e1f4b0();
   input += synapse0x6a40600();
   input += synapse0x6a40640();
   input += synapse0x6c76170();
   input += synapse0x6c761b0();
   input += synapse0x6c761f0();
   input += synapse0x6c76230();
   input += synapse0x6c76270();
   input += synapse0x68d0c70();
   input += synapse0x68d0cb0();
   input += synapse0x68d0cf0();
   input += synapse0x68d0d30();
   input += synapse0x68d0d70();
   input += synapse0x68d0db0();
   input += synapse0x5de7160();
   input += synapse0x5de71a0();
   input += synapse0x4e1f3e0();
   input += synapse0x4e1f420();
   input += synapse0x520ae60();
   input += synapse0x520aea0();
   input += synapse0x520aee0();
   input += synapse0x520af20();
   input += synapse0x520af60();
   input += synapse0x520afa0();
   input += synapse0x55b1b90();
   input += synapse0x55b1bd0();
   input += synapse0x55b1c10();
   input += synapse0x55b1c50();
   input += synapse0x55b1c90();
   input += synapse0x55b1cd0();
   input += synapse0x5de7050();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x6e364e0() {
   double input = input0x6e364e0();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x70c3610() {
   double input = 0.437821;
   input += synapse0x5de7120();
   input += synapse0x7cbd6c0();
   input += synapse0x7cbd700();
   input += synapse0x4da12f0();
   input += synapse0x4da1330();
   input += synapse0x4da1370();
   input += synapse0x4da13b0();
   input += synapse0x4da13f0();
   input += synapse0x4da1430();
   input += synapse0x4a3a980();
   input += synapse0x4a3a9c0();
   input += synapse0x4a3aa00();
   input += synapse0x4a3aa40();
   input += synapse0x4a3aa80();
   input += synapse0x4a3aac0();
   input += synapse0x6a408e0();
   input += synapse0x6a40a30();
   input += synapse0x6a40a70();
   input += synapse0x5de7090();
   input += synapse0x5de70d0();
   input += synapse0x7b8bfc0();
   input += synapse0x7b8c000();
   input += synapse0x7b8c040();
   input += synapse0x7b8c080();
   input += synapse0x7b8c0c0();
   input += synapse0x7b8c100();
   input += synapse0x7b8c140();
   input += synapse0x7b8c180();
   input += synapse0x7b8c1c0();
   input += synapse0x7b8c200();
   input += synapse0x7b8c240();
   input += synapse0x7b8c280();
   input += synapse0x7b8c4d0();
   input += synapse0x7b8c510();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x70c3610() {
   double input = input0x70c3610();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x751a4c0() {
   double input = -0.494722;
   input += synapse0x7ddcf60();
   input += synapse0x7ddcfa0();
   input += synapse0x5b8f040();
   input += synapse0x5b8f080();
   input += synapse0x6613a80();
   input += synapse0x6613ac0();
   input += synapse0x5fa9d20();
   input += synapse0x5fa9d60();
   input += synapse0x6e4f770();
   input += synapse0x6e4f7b0();
   input += synapse0x768b430();
   input += synapse0x768b470();
   input += synapse0x66100b0();
   input += synapse0x66100f0();
   input += synapse0x5dbd480();
   input += synapse0x5dbd4c0();
   input += synapse0x675c9a0();
   input += synapse0x675c9e0();
   input += synapse0x762b6b0();
   input += synapse0x762b6f0();
   input += synapse0x710ccd0();
   input += synapse0x710cd10();
   input += synapse0x67c4bd0();
   input += synapse0x67c4c10();
   input += synapse0x77725e0();
   input += synapse0x7772620();
   input += synapse0x657c090();
   input += synapse0x657c0d0();
   input += synapse0x597c360();
   input += synapse0x597c3a0();
   input += synapse0x5fa3c80();
   input += synapse0x5fa3cc0();
   input += synapse0x58888e0();
   input += synapse0x5888920();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x751a4c0() {
   double input = input0x751a4c0();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x5932aa0() {
   double input = -0.234325;
   input += synapse0x78874d0();
   input += synapse0x7887510();
   input += synapse0x78f6800();
   input += synapse0x78f6840();
   input += synapse0x7519c10();
   input += synapse0x7519c50();
   input += synapse0x7c7cdd0();
   input += synapse0x7c7ce10();
   input += synapse0x57520e0();
   input += synapse0x5752120();
   input += synapse0x7da6690();
   input += synapse0x7da66d0();
   input += synapse0x6e20410();
   input += synapse0x6e20450();
   input += synapse0x7229ad0();
   input += synapse0x7229b10();
   input += synapse0x5c988b0();
   input += synapse0x5c988f0();
   input += synapse0x7f29ff0();
   input += synapse0x7f2a030();
   input += synapse0x7cbd630();
   input += synapse0x7cbd670();
   input += synapse0x5b75090();
   input += synapse0x5b750d0();
   input += synapse0x6dcd8d0();
   input += synapse0x6dcd910();
   input += synapse0x7b22ad0();
   input += synapse0x7b22b10();
   input += synapse0x7b22b50();
   input += synapse0x7b22b90();
   input += synapse0x7b22bd0();
   input += synapse0x7b22c10();
   input += synapse0x6a40920();
   input += synapse0x6a40960();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x5932aa0() {
   double input = input0x5932aa0();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x71dbc80() {
   double input = 0.016393;
   input += synapse0x67988d0();
   input += synapse0x6798910();
   input += synapse0x7ab4870();
   input += synapse0x7ab48b0();
   input += synapse0x7ab48f0();
   input += synapse0x7ab4930();
   input += synapse0x7ab4970();
   input += synapse0x7ab49b0();
   input += synapse0x4e812a0();
   input += synapse0x4e812e0();
   input += synapse0x4e81320();
   input += synapse0x4e81360();
   input += synapse0x4e813a0();
   input += synapse0x4e813e0();
   input += synapse0x4c00bf0();
   input += synapse0x4c00c30();
   input += synapse0x6a409a0();
   input += synapse0x6a409e0();
   input += synapse0x5396d70();
   input += synapse0x5396db0();
   input += synapse0x5396df0();
   input += synapse0x5396e30();
   input += synapse0x5396e70();
   input += synapse0x5396eb0();
   input += synapse0x4621dc0();
   input += synapse0x4621e00();
   input += synapse0x4621e40();
   input += synapse0x4621e80();
   input += synapse0x4621ec0();
   input += synapse0x4621f00();
   input += synapse0x597cb20();
   input += synapse0x597cb60();
   input += synapse0x597cba0();
   input += synapse0x597cbe0();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x71dbc80() {
   double input = input0x71dbc80();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x4fdac50() {
   double input = -0.0533294;
   input += synapse0x6636ad0();
   input += synapse0x6636b10();
   input += synapse0x6636b50();
   input += synapse0x6636b90();
   input += synapse0x6636bd0();
   input += synapse0x6636c10();
   input += synapse0x75e3750();
   input += synapse0x75e3790();
   input += synapse0x75e37d0();
   input += synapse0x75e3810();
   input += synapse0x75e3850();
   input += synapse0x75e3890();
   input += synapse0x5100b10();
   input += synapse0x5100b50();
   input += synapse0x5100b90();
   input += synapse0x5100bd0();
   input += synapse0x597cc20();
   input += synapse0x597cc60();
   input += synapse0x7ad5c80();
   input += synapse0x7ad5cc0();
   input += synapse0x7ad5d00();
   input += synapse0x5100c10();
   input += synapse0x5100c50();
   input += synapse0x5100c90();
   input += synapse0x7bca1f0();
   input += synapse0x7bca230();
   input += synapse0x7bca270();
   input += synapse0x7bca2b0();
   input += synapse0x7bca2f0();
   input += synapse0x7bca330();
   input += synapse0x7bca370();
   input += synapse0x5bb1fe0();
   input += synapse0x7ad5b70();
   input += synapse0x7ad5bb0();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x4fdac50() {
   double input = input0x4fdac50();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x5bb2020() {
   double input = -0.655526;
   input += synapse0x56d8270();
   input += synapse0x56d82b0();
   input += synapse0x77486b0();
   input += synapse0x77486f0();
   input += synapse0x7748730();
   input += synapse0x7748770();
   input += synapse0x77487b0();
   input += synapse0x77487f0();
   input += synapse0x7748830();
   input += synapse0x7748870();
   input += synapse0x77488b0();
   input += synapse0x77488f0();
   input += synapse0x7748930();
   input += synapse0x7748970();
   input += synapse0x77489b0();
   input += synapse0x77489f0();
   input += synapse0x7ad5bf0();
   input += synapse0x7ad5c30();
   input += synapse0x7748b40();
   input += synapse0x7748b80();
   input += synapse0x7748bc0();
   input += synapse0x7748c00();
   input += synapse0x7748c40();
   input += synapse0x6deb910();
   input += synapse0x6deb950();
   input += synapse0x6deb990();
   input += synapse0x6deb9d0();
   input += synapse0x6deba10();
   input += synapse0x6deba50();
   input += synapse0x6deba90();
   input += synapse0x6debad0();
   input += synapse0x6debb10();
   input += synapse0x7748a30();
   input += synapse0x7748a70();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x5bb2020() {
   double input = input0x5bb2020();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x6debd60() {
   double input = -0.555237;
   input += synapse0x55c7300();
   input += synapse0x55c7340();
   input += synapse0x55c7380();
   input += synapse0x55c73c0();
   input += synapse0x55c7400();
   input += synapse0x55c7440();
   input += synapse0x55c7480();
   input += synapse0x55c74c0();
   input += synapse0x55c7500();
   input += synapse0x55c7540();
   input += synapse0x55c7580();
   input += synapse0x55c75c0();
   input += synapse0x55c7600();
   input += synapse0x55c7640();
   input += synapse0x55c7680();
   input += synapse0x55c76c0();
   input += synapse0x7748ab0();
   input += synapse0x7748af0();
   input += synapse0x55c7700();
   input += synapse0x55c7740();
   input += synapse0x55c7780();
   input += synapse0x625d310();
   input += synapse0x625d350();
   input += synapse0x625d390();
   input += synapse0x625d3d0();
   input += synapse0x625d410();
   input += synapse0x625d450();
   input += synapse0x625d490();
   input += synapse0x625d4d0();
   input += synapse0x625d510();
   input += synapse0x625d550();
   input += synapse0x625d590();
   input += synapse0x625d200();
   input += synapse0x625d240();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x6debd60() {
   double input = input0x6debd60();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x4d683c0() {
   double input = -0.893731;
   input += synapse0x4d68670();
   input += synapse0x4d686b0();
   input += synapse0x4d686f0();
   input += synapse0x4d68730();
   input += synapse0x4d68770();
   input += synapse0x4d687b0();
   input += synapse0x4d687f0();
   input += synapse0x4d68830();
   input += synapse0x4d68870();
   input += synapse0x4d688b0();
   input += synapse0x4d688f0();
   input += synapse0x4d68930();
   input += synapse0x4d68970();
   input += synapse0x6630ea0();
   input += synapse0x6630ee0();
   input += synapse0x6630f20();
   input += synapse0x625d280();
   input += synapse0x625d2c0();
   input += synapse0x6631070();
   input += synapse0x66310b0();
   input += synapse0x66310f0();
   input += synapse0x6631130();
   input += synapse0x6631170();
   input += synapse0x66311b0();
   input += synapse0x66311f0();
   input += synapse0x6631230();
   input += synapse0x6631270();
   input += synapse0x66312b0();
   input += synapse0x66312f0();
   input += synapse0x6631330();
   input += synapse0x6631370();
   input += synapse0x66313b0();
   input += synapse0x66313f0();
   input += synapse0x6631430();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x4d683c0() {
   double input = input0x4d683c0();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x6ab8520() {
   double input = -0.505948;
   input += synapse0x6ab8860();
   input += synapse0x6ab88a0();
   input += synapse0x6630f60();
   input += synapse0x6630fa0();
   input += synapse0x6630fe0();
   input += synapse0x6631020();
   input += synapse0x511da20();
   input += synapse0x511da60();
   input += synapse0x511daa0();
   input += synapse0x511dae0();
   input += synapse0x511db20();
   input += synapse0x511db60();
   input += synapse0x511dba0();
   input += synapse0x511dbe0();
   input += synapse0x511dc20();
   input += synapse0x511dc60();
   input += synapse0x6ab86b0();
   input += synapse0x6ab86f0();
   input += synapse0x511ddb0();
   input += synapse0x511ddf0();
   input += synapse0x511de30();
   input += synapse0x511de70();
   input += synapse0x511deb0();
   input += synapse0x511def0();
   input += synapse0x511df30();
   input += synapse0x511df70();
   input += synapse0x511dfb0();
   input += synapse0x5fcac00();
   input += synapse0x5fcac40();
   input += synapse0x5fcac80();
   input += synapse0x5fcacc0();
   input += synapse0x5fcad00();
   input += synapse0x511dca0();
   input += synapse0x511dce0();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x6ab8520() {
   double input = input0x6ab8520();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x5fcaf50() {
   double input = -0.419063;
   input += synapse0x6819a20();
   input += synapse0x6819a60();
   input += synapse0x6819aa0();
   input += synapse0x6819ae0();
   input += synapse0x6819b20();
   input += synapse0x6819b60();
   input += synapse0x6819ba0();
   input += synapse0x6819be0();
   input += synapse0x6819c20();
   input += synapse0x6819c60();
   input += synapse0x6819ca0();
   input += synapse0x6819ce0();
   input += synapse0x6819d20();
   input += synapse0x6819d60();
   input += synapse0x6819da0();
   input += synapse0x6819de0();
   input += synapse0x6819f30();
   input += synapse0x5fcb170();
   input += synapse0x5fcb1b0();
   input += synapse0x511dd20();
   input += synapse0x511dd60();
   input += synapse0x4d1c960();
   input += synapse0x4d1c9a0();
   input += synapse0x4d1c9e0();
   input += synapse0x4d1ca20();
   input += synapse0x4d1ca60();
   input += synapse0x4d1caa0();
   input += synapse0x4d1cae0();
   input += synapse0x4d1cb20();
   input += synapse0x4d1cb60();
   input += synapse0x4d1cba0();
   input += synapse0x4d1cbe0();
   input += synapse0x6819e20();
   input += synapse0x6819e60();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x5fcaf50() {
   double input = input0x5fcaf50();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x63968b0() {
   double input = -0.0765617;
   input += synapse0x6396b60();
   input += synapse0x6396ba0();
   input += synapse0x6396be0();
   input += synapse0x6396c20();
   input += synapse0x6396c60();
   input += synapse0x6396ca0();
   input += synapse0x6396ce0();
   input += synapse0x6396d20();
   input += synapse0x6396d60();
   input += synapse0x6396da0();
   input += synapse0x6396de0();
   input += synapse0x6396e20();
   input += synapse0x6396e60();
   input += synapse0x6396ea0();
   input += synapse0x6396ee0();
   input += synapse0x4d1ce30();
   input += synapse0x6819ea0();
   input += synapse0x6819ee0();
   input += synapse0x4d1ce70();
   input += synapse0x4d1ceb0();
   input += synapse0x4d1cef0();
   input += synapse0x4d1cf30();
   input += synapse0x7766500();
   input += synapse0x7766540();
   input += synapse0x7766580();
   input += synapse0x77665c0();
   input += synapse0x7766600();
   input += synapse0x7766640();
   input += synapse0x7766680();
   input += synapse0x77666c0();
   input += synapse0x7766700();
   input += synapse0x7766740();
   input += synapse0x77663f0();
   input += synapse0x7766430();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x63968b0() {
   double input = input0x63968b0();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x7766990() {
   double input = -0.400385;
   input += synapse0x4b232e0();
   input += synapse0x4b23320();
   input += synapse0x4b23360();
   input += synapse0x4b233a0();
   input += synapse0x4b233e0();
   input += synapse0x4b23420();
   input += synapse0x4b23460();
   input += synapse0x4b234a0();
   input += synapse0x4b234e0();
   input += synapse0x4b23520();
   input += synapse0x4b23560();
   input += synapse0x4b235a0();
   input += synapse0x4b235e0();
   input += synapse0x4b23620();
   input += synapse0x4b23660();
   input += synapse0x4b236a0();
   input += synapse0x7766470();
   input += synapse0x77664b0();
   input += synapse0x4b237f0();
   input += synapse0x4b23830();
   input += synapse0x4b23870();
   input += synapse0x4b238b0();
   input += synapse0x5d668e0();
   input += synapse0x5d66920();
   input += synapse0x5d66960();
   input += synapse0x5d669a0();
   input += synapse0x5d669e0();
   input += synapse0x5d66a20();
   input += synapse0x5d66a60();
   input += synapse0x5d66aa0();
   input += synapse0x5d66ae0();
   input += synapse0x5d66b20();
   input += synapse0x4b236e0();
   input += synapse0x4b23720();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x7766990() {
   double input = input0x7766990();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x5d66d70() {
   double input = -0.676467;
   input += synapse0x5935680();
   input += synapse0x59356c0();
   input += synapse0x5935700();
   input += synapse0x5935740();
   input += synapse0x5935780();
   input += synapse0x59357c0();
   input += synapse0x5935800();
   input += synapse0x5935840();
   input += synapse0x5935880();
   input += synapse0x59358c0();
   input += synapse0x5935900();
   input += synapse0x5935940();
   input += synapse0x5935980();
   input += synapse0x59359c0();
   input += synapse0x5935a00();
   input += synapse0x5935a40();
   input += synapse0x5d66f90();
   input += synapse0x5d66fd0();
   input += synapse0x4b23760();
   input += synapse0x4b237a0();
   input += synapse0x5935b90();
   input += synapse0x5935bd0();
   input += synapse0x5935c10();
   input += synapse0x5935c50();
   input += synapse0x5935c90();
   input += synapse0x5935cd0();
   input += synapse0x4ef8380();
   input += synapse0x4ef83c0();
   input += synapse0x4ef8400();
   input += synapse0x4ef8440();
   input += synapse0x4ef8480();
   input += synapse0x4ef84c0();
   input += synapse0x5935a80();
   input += synapse0x5935ac0();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x5d66d70() {
   double input = input0x5d66d70();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x4ef8710() {
   double input = 0.0550172;
   input += synapse0x4ef89c0();
   input += synapse0x4ef8a00();
   input += synapse0x4ef8a40();
   input += synapse0x5f982b0();
   input += synapse0x5f982f0();
   input += synapse0x5f98330();
   input += synapse0x5f98370();
   input += synapse0x5f983b0();
   input += synapse0x5f983f0();
   input += synapse0x5f98430();
   input += synapse0x5f98470();
   input += synapse0x5f984b0();
   input += synapse0x5f984f0();
   input += synapse0x5f98530();
   input += synapse0x5f98570();
   input += synapse0x5f985b0();
   input += synapse0x5935b00();
   input += synapse0x5935b40();
   input += synapse0x5f98700();
   input += synapse0x5f98740();
   input += synapse0x5f98780();
   input += synapse0x5f987c0();
   input += synapse0x5f98800();
   input += synapse0x5f98840();
   input += synapse0x5f98880();
   input += synapse0x5f988c0();
   input += synapse0x5f98900();
   input += synapse0x5f98940();
   input += synapse0x5f98980();
   input += synapse0x6479270();
   input += synapse0x64792b0();
   input += synapse0x64792f0();
   input += synapse0x5f985f0();
   input += synapse0x5f98630();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x4ef8710() {
   double input = input0x4ef8710();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x6479540() {
   double input = -0.384949;
   input += synapse0x64797f0();
   input += synapse0x6479830();
   input += synapse0x6479870();
   input += synapse0x64798b0();
   input += synapse0x64798f0();
   input += synapse0x6479930();
   input += synapse0x6014830();
   input += synapse0x6014870();
   input += synapse0x60148b0();
   input += synapse0x60148f0();
   input += synapse0x6014930();
   input += synapse0x6014970();
   input += synapse0x60149b0();
   input += synapse0x60149f0();
   input += synapse0x6014a30();
   input += synapse0x6014a70();
   input += synapse0x5f98670();
   input += synapse0x5f986b0();
   input += synapse0x6014bc0();
   input += synapse0x6014c00();
   input += synapse0x6014c40();
   input += synapse0x6014c80();
   input += synapse0x6014cc0();
   input += synapse0x6014d00();
   input += synapse0x6014d40();
   input += synapse0x6014d80();
   input += synapse0x6014dc0();
   input += synapse0x6014e00();
   input += synapse0x6014e40();
   input += synapse0x6014e80();
   input += synapse0x6014ec0();
   input += synapse0x6014f00();
   input += synapse0x6014ab0();
   input += synapse0x6014af0();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x6479540() {
   double input = input0x6479540();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x56e4150() {
   double input = -0.0569105;
   input += synapse0x56e4400();
   input += synapse0x56e4440();
   input += synapse0x56e4480();
   input += synapse0x56e44c0();
   input += synapse0x56e4500();
   input += synapse0x56e4540();
   input += synapse0x56e4580();
   input += synapse0x56e45c0();
   input += synapse0x56e4600();
   input += synapse0x59663f0();
   input += synapse0x5966430();
   input += synapse0x5966470();
   input += synapse0x59664b0();
   input += synapse0x59664f0();
   input += synapse0x5966530();
   input += synapse0x5966570();
   input += synapse0x6014b30();
   input += synapse0x6014b70();
   input += synapse0x59666c0();
   input += synapse0x5966700();
   input += synapse0x5966740();
   input += synapse0x5966780();
   input += synapse0x59667c0();
   input += synapse0x5966800();
   input += synapse0x5966840();
   input += synapse0x5966880();
   input += synapse0x59668c0();
   input += synapse0x5966900();
   input += synapse0x5966940();
   input += synapse0x5966980();
   input += synapse0x59669c0();
   input += synapse0x5966a00();
   input += synapse0x5966a40();
   input += synapse0x5966a80();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x56e4150() {
   double input = input0x56e4150();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x6c951f0() {
   double input = -0.16024;
   input += synapse0x6c95530();
   input += synapse0x5966ac0();
   input += synapse0x5b75000();
   input += synapse0x5b75040();
   input += synapse0x6c95680();
   input += synapse0x6c956c0();
   input += synapse0x6bfc7e0();
   input += synapse0x6bfc820();
   input += synapse0x4e80a40();
   input += synapse0x4e80a80();
   input += synapse0x7ddced0();
   input += synapse0x7ddcf10();
   input += synapse0x5b8efb0();
   input += synapse0x5b8eff0();
   input += synapse0x66139f0();
   input += synapse0x6613a30();
   input += synapse0x5fa9c90();
   input += synapse0x5fa9cd0();
   input += synapse0x6e4f6e0();
   input += synapse0x6e4f720();
   input += synapse0x768b3a0();
   input += synapse0x768b3e0();
   input += synapse0x6610020();
   input += synapse0x6610060();
   input += synapse0x5dbd3f0();
   input += synapse0x5dbd430();
   input += synapse0x675c910();
   input += synapse0x675c950();
   input += synapse0x762b620();
   input += synapse0x762b660();
   input += synapse0x710cc40();
   input += synapse0x710cc80();
   input += synapse0x67c4b40();
   input += synapse0x67c4b80();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x6c951f0() {
   double input = input0x6c951f0();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x79ca0a0() {
   double input = -0.0168131;
   input += synapse0x79ca230();
   input += synapse0x79ca270();
   input += synapse0x79ca2b0();
   input += synapse0x79ca2f0();
   input += synapse0x79ca330();
   input += synapse0x6077fe0();
   input += synapse0x6078020();
   input += synapse0x5fa3bf0();
   input += synapse0x5fa3c30();
   input += synapse0x5888850();
   input += synapse0x5888890();
   input += synapse0x6dcd840();
   input += synapse0x6dcd880();
   input += synapse0x7c1a680();
   input += synapse0x7c1a6c0();
   input += synapse0x7f704e0();
   input += synapse0x7f70520();
   input += synapse0x7887440();
   input += synapse0x7887480();
   input += synapse0x78f6770();
   input += synapse0x78f67b0();
   input += synapse0x7519b80();
   input += synapse0x7519bc0();
   input += synapse0x7c7cd40();
   input += synapse0x7c7cd80();
   input += synapse0x5752050();
   input += synapse0x5752090();
   input += synapse0x7da6600();
   input += synapse0x7da6640();
   input += synapse0x6e20380();
   input += synapse0x6e203c0();
   input += synapse0x7229a40();
   input += synapse0x7229a80();
   input += synapse0x6a40570();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x79ca0a0() {
   double input = input0x79ca0a0();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x72cc3b0() {
   double input = -0.518663;
   input += synapse0x72cc5d0();
   input += synapse0x72cc610();
   input += synapse0x72cc650();
   input += synapse0x72cc690();
   input += synapse0x72cc6d0();
   input += synapse0x72cc710();
   input += synapse0x72cc750();
   input += synapse0x6a405b0();
   input += synapse0x5fe57c0();
   input += synapse0x5fe5800();
   input += synapse0x59b35f0();
   input += synapse0x59b3630();
   input += synapse0x59b3670();
   input += synapse0x4cfad50();
   input += synapse0x4cfad90();
   input += synapse0x4cfadd0();
   input += synapse0x7cbd5a0();
   input += synapse0x7cbd5e0();
   input += synapse0x5af6b80();
   input += synapse0x5af6bc0();
   input += synapse0x5af6c00();
   input += synapse0x6171c60();
   input += synapse0x6171ca0();
   input += synapse0x6171ce0();
   input += synapse0x5eeaa10();
   input += synapse0x5eeaa50();
   input += synapse0x5eeaa90();
   input += synapse0x63d5750();
   input += synapse0x63d5790();
   input += synapse0x63d57d0();
   input += synapse0x63d5810();
   input += synapse0x63d5850();
   input += synapse0x72cc090();
   input += synapse0x72cc0d0();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x72cc3b0() {
   double input = input0x72cc3b0();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x63d5aa0() {
   double input = -0.717672;
   input += synapse0x63d5d50();
   input += synapse0x63d5d90();
   input += synapse0x63d5dd0();
   input += synapse0x63d5e10();
   input += synapse0x51e80d0();
   input += synapse0x51e8110();
   input += synapse0x51e8150();
   input += synapse0x51e8190();
   input += synapse0x51e81d0();
   input += synapse0x51e8210();
   input += synapse0x51e8250();
   input += synapse0x51e8290();
   input += synapse0x51e82d0();
   input += synapse0x51e8310();
   input += synapse0x51e8350();
   input += synapse0x51e8390();
   input += synapse0x72cc110();
   input += synapse0x72cc150();
   input += synapse0x51e84e0();
   input += synapse0x51e8520();
   input += synapse0x51e8560();
   input += synapse0x51e85a0();
   input += synapse0x51e85e0();
   input += synapse0x51e8620();
   input += synapse0x51e8660();
   input += synapse0x51e86a0();
   input += synapse0x51e86e0();
   input += synapse0x51e8720();
   input += synapse0x51e8760();
   input += synapse0x51e87a0();
   input += synapse0x57f31a0();
   input += synapse0x57f31e0();
   input += synapse0x51e83d0();
   input += synapse0x51e8410();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x63d5aa0() {
   double input = input0x63d5aa0();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x57f3430() {
   double input = -0.566076;
   input += synapse0x57f36e0();
   input += synapse0x57f3720();
   input += synapse0x57f3760();
   input += synapse0x57f37a0();
   input += synapse0x57f37e0();
   input += synapse0x57f3820();
   input += synapse0x57f3860();
   input += synapse0x753e3f0();
   input += synapse0x753e430();
   input += synapse0x753e470();
   input += synapse0x753e4b0();
   input += synapse0x753e4f0();
   input += synapse0x753e530();
   input += synapse0x753e570();
   input += synapse0x753e5b0();
   input += synapse0x753e5f0();
   input += synapse0x51e8450();
   input += synapse0x51e8490();
   input += synapse0x753e740();
   input += synapse0x753e780();
   input += synapse0x753e7c0();
   input += synapse0x753e800();
   input += synapse0x753e840();
   input += synapse0x753e880();
   input += synapse0x753e8c0();
   input += synapse0x753e900();
   input += synapse0x753e940();
   input += synapse0x753e980();
   input += synapse0x753e9c0();
   input += synapse0x753ea00();
   input += synapse0x753ea40();
   input += synapse0x753ea80();
   input += synapse0x753eac0();
   input += synapse0x753e630();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x57f3430() {
   double input = input0x57f3430();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x54a8a50() {
   double input = -0.11847;
   input += synapse0x54a8d90();
   input += synapse0x54a8dd0();
   input += synapse0x54a8e10();
   input += synapse0x54a8e50();
   input += synapse0x54a8e90();
   input += synapse0x54a8ed0();
   input += synapse0x54a8f10();
   input += synapse0x753e670();
   input += synapse0x753e6b0();
   input += synapse0x753e6f0();
   input += synapse0x756be30();
   input += synapse0x756be70();
   input += synapse0x756beb0();
   input += synapse0x756bef0();
   input += synapse0x756bf30();
   input += synapse0x756bf70();
   input += synapse0x54a8be0();
   input += synapse0x54a8c20();
   input += synapse0x756c0c0();
   input += synapse0x756c100();
   input += synapse0x756c140();
   input += synapse0x756c180();
   input += synapse0x756c1c0();
   input += synapse0x756c200();
   input += synapse0x756c240();
   input += synapse0x756c280();
   input += synapse0x756c2c0();
   input += synapse0x756c300();
   input += synapse0x756c340();
   input += synapse0x756c380();
   input += synapse0x756c3c0();
   input += synapse0x756c400();
   input += synapse0x756bfb0();
   input += synapse0x756bff0();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x54a8a50() {
   double input = input0x54a8a50();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x71c4790() {
   double input = -0.899916;
   input += synapse0x71c4a40();
   input += synapse0x71c4a80();
   input += synapse0x71c4ac0();
   input += synapse0x71c4b00();
   input += synapse0x71c4b40();
   input += synapse0x71c4b80();
   input += synapse0x71c4bc0();
   input += synapse0x71c4c00();
   input += synapse0x71c4c40();
   input += synapse0x756c440();
   input += synapse0x756c480();
   input += synapse0x756c4c0();
   input += synapse0x756c500();
   input += synapse0x61e2380();
   input += synapse0x61e23c0();
   input += synapse0x61e2400();
   input += synapse0x756c030();
   input += synapse0x756c070();
   input += synapse0x61e2550();
   input += synapse0x61e2590();
   input += synapse0x61e25d0();
   input += synapse0x61e2610();
   input += synapse0x61e2650();
   input += synapse0x61e2690();
   input += synapse0x61e26d0();
   input += synapse0x61e2710();
   input += synapse0x61e2750();
   input += synapse0x61e2790();
   input += synapse0x61e27d0();
   input += synapse0x61e2810();
   input += synapse0x61e2850();
   input += synapse0x61e2890();
   input += synapse0x61e2440();
   input += synapse0x61e2480();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x71c4790() {
   double input = input0x71c4790();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x61e28d0() {
   double input = -0.74957;
   input += synapse0x79306f0();
   input += synapse0x7930730();
   input += synapse0x7930770();
   input += synapse0x79307b0();
   input += synapse0x79307f0();
   input += synapse0x7930830();
   input += synapse0x7930870();
   input += synapse0x79308b0();
   input += synapse0x79308f0();
   input += synapse0x7930930();
   input += synapse0x7930970();
   input += synapse0x79309b0();
   input += synapse0x79309f0();
   input += synapse0x7930a30();
   input += synapse0x7930a70();
   input += synapse0x7930ab0();
   input += synapse0x61e2a60();
   input += synapse0x61e24c0();
   input += synapse0x61e2500();
   input += synapse0x4cc4af0();
   input += synapse0x4cc4b30();
   input += synapse0x4cc4b70();
   input += synapse0x4cc4bb0();
   input += synapse0x4cc4bf0();
   input += synapse0x4cc4c30();
   input += synapse0x4cc4c70();
   input += synapse0x4cc4cb0();
   input += synapse0x4cc4cf0();
   input += synapse0x4cc4d30();
   input += synapse0x4cc4d70();
   input += synapse0x4cc4db0();
   input += synapse0x4cc4df0();
   input += synapse0x4cc5040();
   input += synapse0x4cc5080();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x61e28d0() {
   double input = input0x61e28d0();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x710df60() {
   double input = -0.163725;
   input += synapse0x710e2a0();
   input += synapse0x710e2e0();
   input += synapse0x710e320();
   input += synapse0x710e360();
   input += synapse0x710e3a0();
   input += synapse0x710e3e0();
   input += synapse0x710e420();
   input += synapse0x710e460();
   input += synapse0x710e4a0();
   input += synapse0x710e4e0();
   input += synapse0x710e520();
   input += synapse0x710e560();
   input += synapse0x710e5a0();
   input += synapse0x710e5e0();
   input += synapse0x710e620();
   input += synapse0x4cc50c0();
   input += synapse0x710e0f0();
   input += synapse0x710e130();
   input += synapse0x7c64260();
   input += synapse0x7c642a0();
   input += synapse0x7c642e0();
   input += synapse0x7c64320();
   input += synapse0x7c64360();
   input += synapse0x7c643a0();
   input += synapse0x7c643e0();
   input += synapse0x7c64420();
   input += synapse0x7c64460();
   input += synapse0x7c644a0();
   input += synapse0x7c644e0();
   input += synapse0x7c64520();
   input += synapse0x7c64560();
   input += synapse0x7c645a0();
   input += synapse0x4cc49e0();
   input += synapse0x4cc4a20();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x710df60() {
   double input = input0x710df60();
   return ((input < -709. ? 0. : (1/(1+exp(-input)))) * 1)+0;
}

double TMVAClassification_TMlp_ANN::input0x7c647f0() {
   double input = 0.0120113;
   input += synapse0x4c013a0();
   input += synapse0x5e95540();
   input += synapse0x5e95580();
   input += synapse0x5e955c0();
   input += synapse0x5e95600();
   input += synapse0x5e95640();
   input += synapse0x5e95680();
   input += synapse0x5e956c0();
   input += synapse0x5e95700();
   input += synapse0x5e95740();
   input += synapse0x5e95780();
   input += synapse0x5e957c0();
   input += synapse0x5e95800();
   input += synapse0x5e95840();
   input += synapse0x5e95880();
   input += synapse0x5e958c0();
   input += synapse0x4cc4a60();
   input += synapse0x4cc4aa0();
   input += synapse0x5e95a10();
   input += synapse0x5e95a50();
   input += synapse0x5e95a90();
   input += synapse0x5e95ad0();
   input += synapse0x5e95b10();
   input += synapse0x5e95b50();
   return input;
}

double TMVAClassification_TMlp_ANN::neuron0x7c647f0() {
   double input = input0x7c647f0();
   return (input * 1)+0;
}

double TMVAClassification_TMlp_ANN::synapse0x7b4eee0() {
   return (neuron0x6078290()*-0.881705);
}

double TMVAClassification_TMlp_ANN::synapse0x6542830() {
   return (neuron0x6078540()*-0.302026);
}

double TMVAClassification_TMlp_ANN::synapse0x46218b0() {
   return (neuron0x63d6190()*0.440019);
}

double TMVAClassification_TMlp_ANN::synapse0x7377490() {
   return (neuron0x63d64d0()*-0.732279);
}

double TMVAClassification_TMlp_ANN::synapse0x51a0e90() {
   return (neuron0x6251640()*-0.356669);
}

double TMVAClassification_TMlp_ANN::synapse0x5b75120() {
   return (neuron0x46213e0()*-0.476582);
}

double TMVAClassification_TMlp_ANN::synapse0x5b75160() {
   return (neuron0x4621720()*0.964088);
}

double TMVAClassification_TMlp_ANN::synapse0x5b751a0() {
   return (neuron0x54fbed0()*1.1486);
}

double TMVAClassification_TMlp_ANN::synapse0x5b751e0() {
   return (neuron0x7376fc0()*-0.774941);
}

double TMVAClassification_TMlp_ANN::synapse0x5b75220() {
   return (neuron0x7377300()*0.744146);
}

double TMVAClassification_TMlp_ANN::synapse0x5b75260() {
   return (neuron0x6a82e50()*-0.414141);
}

double TMVAClassification_TMlp_ANN::synapse0x5b752a0() {
   return (neuron0x6636ca0()*0.574959);
}

double TMVAClassification_TMlp_ANN::synapse0x5b752e0() {
   return (neuron0x6636fe0()*-0.367371);
}

double TMVAClassification_TMlp_ANN::synapse0x5b75320() {
   return (neuron0x51a0a30()*-0.535818);
}

double TMVAClassification_TMlp_ANN::synapse0x5b75360() {
   return (neuron0x4d1fad0()*-0.227541);
}

double TMVAClassification_TMlp_ANN::synapse0x5b753a0() {
   return (neuron0x4d1fe10()*0.560453);
}

double TMVAClassification_TMlp_ANN::synapse0x6637170() {
   return (neuron0x4c00f40()*-0.111061);
}

double TMVAClassification_TMlp_ANN::synapse0x4d1ffa0() {
   return (neuron0x657be70()*-0.171733);
}

double TMVAClassification_TMlp_ANN::synapse0x657c240() {
   return (neuron0x7ec13f0()*-0.172248);
}

double TMVAClassification_TMlp_ANN::synapse0x58480c0() {
   return (neuron0x7ec1730()*-0.813737);
}

double TMVAClassification_TMlp_ANN::synapse0x753f720() {
   return (neuron0x6c315b0()*-0.0364308);
}

double TMVAClassification_TMlp_ANN::synapse0x7ec18c0() {
   return (neuron0x6c318f0()*0.276008);
}

double TMVAClassification_TMlp_ANN::synapse0x7db6eb0() {
   return (neuron0x638c0d0()*-0.0493882);
}

double TMVAClassification_TMlp_ANN::synapse0x7db6ef0() {
   return (neuron0x60b21d0()*0.0208218);
}

double TMVAClassification_TMlp_ANN::synapse0x74caad0() {
   return (neuron0x60b2510()*0.419486);
}

double TMVAClassification_TMlp_ANN::synapse0x74cab10() {
   return (neuron0x4eb4da0()*0.589544);
}

double TMVAClassification_TMlp_ANN::synapse0x73fea40() {
   return (neuron0x4eb50e0()*-0.143361);
}

double TMVAClassification_TMlp_ANN::synapse0x73fea80() {
   return (neuron0x6077dc0()*-0.342734);
}

double TMVAClassification_TMlp_ANN::synapse0x63a4e90() {
   return (neuron0x597c140()*-0.352373);
}

double TMVAClassification_TMlp_ANN::synapse0x63a4ed0() {
   return (neuron0x597c480()*-0.359821);
}

double TMVAClassification_TMlp_ANN::synapse0x78c3700() {
   return (neuron0x55c7800()*0.322512);
}

double TMVAClassification_TMlp_ANN::synapse0x78c3740() {
   return (neuron0x55c7b40()*1.06898);
}

double TMVAClassification_TMlp_ANN::synapse0x5a3c390() {
   return (neuron0x7f7a090()*0.136868);
}

double TMVAClassification_TMlp_ANN::synapse0x5a3c3d0() {
   return (neuron0x673e5e0()*-0.319732);
}

double TMVAClassification_TMlp_ANN::synapse0x753f530() {
   return (neuron0x6078290()*-0.722432);
}

double TMVAClassification_TMlp_ANN::synapse0x5b75570() {
   return (neuron0x6078540()*-0.440804);
}

double TMVAClassification_TMlp_ANN::synapse0x7143630() {
   return (neuron0x63d6190()*-0.0241625);
}

double TMVAClassification_TMlp_ANN::synapse0x7143670() {
   return (neuron0x63d64d0()*1.04633);
}

double TMVAClassification_TMlp_ANN::synapse0x5397400() {
   return (neuron0x6251640()*-1.04428);
}

double TMVAClassification_TMlp_ANN::synapse0x5397440() {
   return (neuron0x46213e0()*0.0781008);
}

double TMVAClassification_TMlp_ANN::synapse0x7e79e10() {
   return (neuron0x4621720()*0.0433913);
}

double TMVAClassification_TMlp_ANN::synapse0x7e79e50() {
   return (neuron0x54fbed0()*-0.284505);
}

double TMVAClassification_TMlp_ANN::synapse0x52693a0() {
   return (neuron0x7376fc0()*0.174506);
}

double TMVAClassification_TMlp_ANN::synapse0x52693e0() {
   return (neuron0x7377300()*-0.653271);
}

double TMVAClassification_TMlp_ANN::synapse0x5b8eaa0() {
   return (neuron0x6a82e50()*-0.598608);
}

double TMVAClassification_TMlp_ANN::synapse0x5b8eae0() {
   return (neuron0x6636ca0()*-0.309431);
}

double TMVAClassification_TMlp_ANN::synapse0x66c4d40() {
   return (neuron0x6636fe0()*-0.226635);
}

double TMVAClassification_TMlp_ANN::synapse0x66c4d80() {
   return (neuron0x51a0a30()*-0.719346);
}

double TMVAClassification_TMlp_ANN::synapse0x5a3caf0() {
   return (neuron0x4d1fad0()*0.786452);
}

double TMVAClassification_TMlp_ANN::synapse0x5a3cb30() {
   return (neuron0x4d1fe10()*-0.56638);
}

double TMVAClassification_TMlp_ANN::synapse0x657bdf0() {
   return (neuron0x4c00f40()*-0.523193);
}

double TMVAClassification_TMlp_ANN::synapse0x657be30() {
   return (neuron0x657be70()*-0.215144);
}

double TMVAClassification_TMlp_ANN::synapse0x4e1f770() {
   return (neuron0x7ec13f0()*-0.0433606);
}

double TMVAClassification_TMlp_ANN::synapse0x4e1f7b0() {
   return (neuron0x7ec1730()*-1.26969);
}

double TMVAClassification_TMlp_ANN::synapse0x6c948b0() {
   return (neuron0x6c315b0()*-0.0298811);
}

double TMVAClassification_TMlp_ANN::synapse0x6c948f0() {
   return (neuron0x6c318f0()*-0.386697);
}

double TMVAClassification_TMlp_ANN::synapse0x6c94930() {
   return (neuron0x638c0d0()*0.831389);
}

double TMVAClassification_TMlp_ANN::synapse0x6c94970() {
   return (neuron0x60b21d0()*0.325106);
}

double TMVAClassification_TMlp_ANN::synapse0x6c949b0() {
   return (neuron0x60b2510()*0.621628);
}

double TMVAClassification_TMlp_ANN::synapse0x6c949f0() {
   return (neuron0x4eb4da0()*0.0963563);
}

double TMVAClassification_TMlp_ANN::synapse0x6c94a30() {
   return (neuron0x4eb50e0()*-0.324854);
}

double TMVAClassification_TMlp_ANN::synapse0x6c94a70() {
   return (neuron0x6077dc0()*1.12869);
}

double TMVAClassification_TMlp_ANN::synapse0x6c94ab0() {
   return (neuron0x597c140()*-0.256464);
}

double TMVAClassification_TMlp_ANN::synapse0x6c94af0() {
   return (neuron0x597c480()*-0.94088);
}

double TMVAClassification_TMlp_ANN::synapse0x6c94b30() {
   return (neuron0x55c7800()*1.98751);
}

double TMVAClassification_TMlp_ANN::synapse0x7770a60() {
   return (neuron0x55c7b40()*1.30439);
}

double TMVAClassification_TMlp_ANN::synapse0x4b43130() {
   return (neuron0x7f7a090()*-0.702336);
}

double TMVAClassification_TMlp_ANN::synapse0x638ed20() {
   return (neuron0x673e5e0()*0.117896);
}

double TMVAClassification_TMlp_ANN::synapse0x4e80b60() {
   return (neuron0x6078290()*-0.554157);
}

double TMVAClassification_TMlp_ANN::synapse0x4e80ba0() {
   return (neuron0x6078540()*-0.13061);
}

double TMVAClassification_TMlp_ANN::synapse0x4e80be0() {
   return (neuron0x63d6190()*0.271253);
}

double TMVAClassification_TMlp_ANN::synapse0x4e80c20() {
   return (neuron0x63d64d0()*0.0647425);
}

double TMVAClassification_TMlp_ANN::synapse0x4e80c60() {
   return (neuron0x6251640()*-0.216111);
}

double TMVAClassification_TMlp_ANN::synapse0x4e80ca0() {
   return (neuron0x46213e0()*-0.364002);
}

double TMVAClassification_TMlp_ANN::synapse0x6a410a0() {
   return (neuron0x4621720()*0.245452);
}

double TMVAClassification_TMlp_ANN::synapse0x5a6b500() {
   return (neuron0x54fbed0()*0.505577);
}

double TMVAClassification_TMlp_ANN::synapse0x6327690() {
   return (neuron0x7376fc0()*0.600694);
}

double TMVAClassification_TMlp_ANN::synapse0x6f46b40() {
   return (neuron0x7377300()*0.522005);
}

double TMVAClassification_TMlp_ANN::synapse0x4b2e3b0() {
   return (neuron0x6a82e50()*0.0039166);
}

double TMVAClassification_TMlp_ANN::synapse0x5d37470() {
   return (neuron0x6636ca0()*-0.51582);
}

double TMVAClassification_TMlp_ANN::synapse0x6dd1390() {
   return (neuron0x6636fe0()*-0.115889);
}

double TMVAClassification_TMlp_ANN::synapse0x4b60740() {
   return (neuron0x51a0a30()*0.464136);
}

double TMVAClassification_TMlp_ANN::synapse0x753f090() {
   return (neuron0x4d1fad0()*0.236365);
}

double TMVAClassification_TMlp_ANN::synapse0x4d68df0() {
   return (neuron0x4d1fe10()*0.235729);
}

double TMVAClassification_TMlp_ANN::synapse0x77c6a20() {
   return (neuron0x4c00f40()*-0.00533438);
}

double TMVAClassification_TMlp_ANN::synapse0x5b04510() {
   return (neuron0x657be70()*-0.44385);
}

double TMVAClassification_TMlp_ANN::synapse0x5478800() {
   return (neuron0x7ec13f0()*-0.284686);
}

double TMVAClassification_TMlp_ANN::synapse0x753f6c0() {
   return (neuron0x7ec1730()*-0.0339795);
}

double TMVAClassification_TMlp_ANN::synapse0x6bfc2b0() {
   return (neuron0x6c315b0()*0.746205);
}

double TMVAClassification_TMlp_ANN::synapse0x6bfc2f0() {
   return (neuron0x6c318f0()*-0.350209);
}

double TMVAClassification_TMlp_ANN::synapse0x6bfc330() {
   return (neuron0x638c0d0()*-0.243241);
}

double TMVAClassification_TMlp_ANN::synapse0x6bfc370() {
   return (neuron0x60b21d0()*0.346089);
}

double TMVAClassification_TMlp_ANN::synapse0x6c94c80() {
   return (neuron0x60b2510()*0.123884);
}

double TMVAClassification_TMlp_ANN::synapse0x6c94cc0() {
   return (neuron0x4eb4da0()*0.220736);
}

double TMVAClassification_TMlp_ANN::synapse0x6c94d00() {
   return (neuron0x4eb50e0()*-0.21548);
}

double TMVAClassification_TMlp_ANN::synapse0x6c94d40() {
   return (neuron0x6077dc0()*0.0362954);
}

double TMVAClassification_TMlp_ANN::synapse0x6c94d80() {
   return (neuron0x597c140()*0.38923);
}

double TMVAClassification_TMlp_ANN::synapse0x6c94dc0() {
   return (neuron0x597c480()*0.107967);
}

double TMVAClassification_TMlp_ANN::synapse0x6c94e00() {
   return (neuron0x55c7800()*0.102705);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddcaf0() {
   return (neuron0x55c7b40()*-0.437144);
}

double TMVAClassification_TMlp_ANN::synapse0x6c94b70() {
   return (neuron0x7f7a090()*-0.544759);
}

double TMVAClassification_TMlp_ANN::synapse0x6c94bb0() {
   return (neuron0x673e5e0()*0.123473);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddcff0() {
   return (neuron0x6078290()*0.138252);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddd030() {
   return (neuron0x6078540()*-0.156117);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddd070() {
   return (neuron0x63d6190()*0.0114593);
}

double TMVAClassification_TMlp_ANN::synapse0x4ccf0a0() {
   return (neuron0x63d64d0()*0.12387);
}

double TMVAClassification_TMlp_ANN::synapse0x4ccf0e0() {
   return (neuron0x6251640()*-0.394993);
}

double TMVAClassification_TMlp_ANN::synapse0x4ccf120() {
   return (neuron0x46213e0()*0.351487);
}

double TMVAClassification_TMlp_ANN::synapse0x4ccf160() {
   return (neuron0x4621720()*0.438143);
}

double TMVAClassification_TMlp_ANN::synapse0x4ccf1a0() {
   return (neuron0x54fbed0()*0.197365);
}

double TMVAClassification_TMlp_ANN::synapse0x4ccf1e0() {
   return (neuron0x7376fc0()*-0.079545);
}

double TMVAClassification_TMlp_ANN::synapse0x4ccf220() {
   return (neuron0x7377300()*-0.554628);
}

double TMVAClassification_TMlp_ANN::synapse0x4ccf260() {
   return (neuron0x6a82e50()*0.315235);
}

double TMVAClassification_TMlp_ANN::synapse0x4ccf2a0() {
   return (neuron0x6636ca0()*-0.104571);
}

double TMVAClassification_TMlp_ANN::synapse0x4ccf2e0() {
   return (neuron0x6636fe0()*0.0946354);
}

double TMVAClassification_TMlp_ANN::synapse0x4ccf320() {
   return (neuron0x51a0a30()*0.164157);
}

double TMVAClassification_TMlp_ANN::synapse0x4ccf360() {
   return (neuron0x4d1fad0()*-0.161305);
}

double TMVAClassification_TMlp_ANN::synapse0x4ccf3a0() {
   return (neuron0x4d1fe10()*-0.0594282);
}

double TMVAClassification_TMlp_ANN::synapse0x6c94bf0() {
   return (neuron0x4c00f40()*-0.403076);
}

double TMVAClassification_TMlp_ANN::synapse0x6c94c30() {
   return (neuron0x657be70()*0.00783578);
}

double TMVAClassification_TMlp_ANN::synapse0x4ccf4f0() {
   return (neuron0x7ec13f0()*-0.216925);
}

double TMVAClassification_TMlp_ANN::synapse0x4ccf530() {
   return (neuron0x7ec1730()*-0.435424);
}

double TMVAClassification_TMlp_ANN::synapse0x4ccf570() {
   return (neuron0x6c315b0()*0.0780926);
}

double TMVAClassification_TMlp_ANN::synapse0x4ccf5b0() {
   return (neuron0x6c318f0()*-0.470154);
}

double TMVAClassification_TMlp_ANN::synapse0x4ccf5f0() {
   return (neuron0x638c0d0()*0.404331);
}

double TMVAClassification_TMlp_ANN::synapse0x5b8ec90() {
   return (neuron0x60b21d0()*0.538777);
}

double TMVAClassification_TMlp_ANN::synapse0x5b8ecd0() {
   return (neuron0x60b2510()*0.354386);
}

double TMVAClassification_TMlp_ANN::synapse0x5b8ed10() {
   return (neuron0x4eb4da0()*0.484245);
}

double TMVAClassification_TMlp_ANN::synapse0x5b8ed50() {
   return (neuron0x4eb50e0()*0.0558852);
}

double TMVAClassification_TMlp_ANN::synapse0x64bdf90() {
   return (neuron0x6077dc0()*0.0626838);
}

double TMVAClassification_TMlp_ANN::synapse0x64bdfd0() {
   return (neuron0x597c140()*0.232421);
}

double TMVAClassification_TMlp_ANN::synapse0x64be010() {
   return (neuron0x597c480()*0.164421);
}

double TMVAClassification_TMlp_ANN::synapse0x64be050() {
   return (neuron0x55c7800()*0.159096);
}

double TMVAClassification_TMlp_ANN::synapse0x64be090() {
   return (neuron0x55c7b40()*-0.0375476);
}

double TMVAClassification_TMlp_ANN::synapse0x64be2e0() {
   return (neuron0x7f7a090()*-0.289848);
}

double TMVAClassification_TMlp_ANN::synapse0x64be320() {
   return (neuron0x673e5e0()*-0.449048);
}

double TMVAClassification_TMlp_ANN::synapse0x64be360() {
   return (neuron0x6078290()*0.62987);
}

double TMVAClassification_TMlp_ANN::synapse0x5b8f0d0() {
   return (neuron0x6078540()*-0.489602);
}

double TMVAClassification_TMlp_ANN::synapse0x5b8f110() {
   return (neuron0x63d6190()*0.177512);
}

double TMVAClassification_TMlp_ANN::synapse0x5b8f150() {
   return (neuron0x63d64d0()*-0.0873219);
}

double TMVAClassification_TMlp_ANN::synapse0x5b8f190() {
   return (neuron0x6251640()*0.938821);
}

double TMVAClassification_TMlp_ANN::synapse0x5b8f1d0() {
   return (neuron0x46213e0()*-0.500705);
}

double TMVAClassification_TMlp_ANN::synapse0x5b8f210() {
   return (neuron0x4621720()*0.364522);
}

double TMVAClassification_TMlp_ANN::synapse0x4ccf3e0() {
   return (neuron0x54fbed0()*0.94158);
}

double TMVAClassification_TMlp_ANN::synapse0x4ccf420() {
   return (neuron0x7376fc0()*0.495241);
}

double TMVAClassification_TMlp_ANN::synapse0x4ccf460() {
   return (neuron0x7377300()*0.152635);
}

double TMVAClassification_TMlp_ANN::synapse0x4ccf4a0() {
   return (neuron0x6a82e50()*-0.567079);
}

double TMVAClassification_TMlp_ANN::synapse0x66200c0() {
   return (neuron0x6636ca0()*0.285346);
}

double TMVAClassification_TMlp_ANN::synapse0x6620100() {
   return (neuron0x6636fe0()*-0.171792);
}

double TMVAClassification_TMlp_ANN::synapse0x6620140() {
   return (neuron0x51a0a30()*0.0679409);
}

double TMVAClassification_TMlp_ANN::synapse0x6620180() {
   return (neuron0x4d1fad0()*-0.338077);
}

double TMVAClassification_TMlp_ANN::synapse0x66201c0() {
   return (neuron0x4d1fe10()*0.732138);
}

double TMVAClassification_TMlp_ANN::synapse0x5b8ef20() {
   return (neuron0x4c00f40()*0.228503);
}

double TMVAClassification_TMlp_ANN::synapse0x5b8ef60() {
   return (neuron0x657be70()*-0.026094);
}

double TMVAClassification_TMlp_ANN::synapse0x6620310() {
   return (neuron0x7ec13f0()*0.520018);
}

double TMVAClassification_TMlp_ANN::synapse0x6620350() {
   return (neuron0x7ec1730()*0.374924);
}

double TMVAClassification_TMlp_ANN::synapse0x6620390() {
   return (neuron0x6c315b0()*-0.912668);
}

double TMVAClassification_TMlp_ANN::synapse0x66203d0() {
   return (neuron0x6c318f0()*-0.254524);
}

double TMVAClassification_TMlp_ANN::synapse0x6620410() {
   return (neuron0x638c0d0()*0.435043);
}

double TMVAClassification_TMlp_ANN::synapse0x6620450() {
   return (neuron0x60b21d0()*0.735481);
}

double TMVAClassification_TMlp_ANN::synapse0x6620490() {
   return (neuron0x60b2510()*0.656605);
}

double TMVAClassification_TMlp_ANN::synapse0x66204d0() {
   return (neuron0x4eb4da0()*0.466489);
}

double TMVAClassification_TMlp_ANN::synapse0x6620510() {
   return (neuron0x4eb50e0()*0.0589046);
}

double TMVAClassification_TMlp_ANN::synapse0x6620550() {
   return (neuron0x6077dc0()*-0.394169);
}

double TMVAClassification_TMlp_ANN::synapse0x6620590() {
   return (neuron0x597c140()*-0.422362);
}

double TMVAClassification_TMlp_ANN::synapse0x66205d0() {
   return (neuron0x597c480()*0.421619);
}

double TMVAClassification_TMlp_ANN::synapse0x6620610() {
   return (neuron0x55c7800()*0.637201);
}

double TMVAClassification_TMlp_ANN::synapse0x6613610() {
   return (neuron0x55c7b40()*0.235419);
}

double TMVAClassification_TMlp_ANN::synapse0x6620200() {
   return (neuron0x7f7a090()*0.234786);
}

double TMVAClassification_TMlp_ANN::synapse0x6620240() {
   return (neuron0x673e5e0()*0.182794);
}

double TMVAClassification_TMlp_ANN::synapse0x6613b10() {
   return (neuron0x6078290()*0.597781);
}

double TMVAClassification_TMlp_ANN::synapse0x6613b50() {
   return (neuron0x6078540()*1.14362);
}

double TMVAClassification_TMlp_ANN::synapse0x6613b90() {
   return (neuron0x63d6190()*-0.368151);
}

double TMVAClassification_TMlp_ANN::synapse0x7da6990() {
   return (neuron0x63d64d0()*1.35814);
}

double TMVAClassification_TMlp_ANN::synapse0x7da69d0() {
   return (neuron0x6251640()*0.654905);
}

double TMVAClassification_TMlp_ANN::synapse0x7da6a10() {
   return (neuron0x46213e0()*-0.704864);
}

double TMVAClassification_TMlp_ANN::synapse0x7da6a50() {
   return (neuron0x4621720()*-0.411426);
}

double TMVAClassification_TMlp_ANN::synapse0x7da6a90() {
   return (neuron0x54fbed0()*-0.141061);
}

double TMVAClassification_TMlp_ANN::synapse0x7da6ad0() {
   return (neuron0x7376fc0()*-0.426216);
}

double TMVAClassification_TMlp_ANN::synapse0x7da6b10() {
   return (neuron0x7377300()*0.877328);
}

double TMVAClassification_TMlp_ANN::synapse0x7da6b50() {
   return (neuron0x6a82e50()*-0.797533);
}

double TMVAClassification_TMlp_ANN::synapse0x7da6b90() {
   return (neuron0x6636ca0()*-0.882905);
}

double TMVAClassification_TMlp_ANN::synapse0x7da6bd0() {
   return (neuron0x6636fe0()*0.509915);
}

double TMVAClassification_TMlp_ANN::synapse0x7da6c10() {
   return (neuron0x51a0a30()*0.581754);
}

double TMVAClassification_TMlp_ANN::synapse0x7da6c50() {
   return (neuron0x4d1fad0()*0.377426);
}

double TMVAClassification_TMlp_ANN::synapse0x7da6c90() {
   return (neuron0x4d1fe10()*-0.10381);
}

double TMVAClassification_TMlp_ANN::synapse0x6620280() {
   return (neuron0x4c00f40()*0.262232);
}

double TMVAClassification_TMlp_ANN::synapse0x66202c0() {
   return (neuron0x657be70()*0.332734);
}

double TMVAClassification_TMlp_ANN::synapse0x7da6de0() {
   return (neuron0x7ec13f0()*-0.226519);
}

double TMVAClassification_TMlp_ANN::synapse0x7da6e20() {
   return (neuron0x7ec1730()*0.743986);
}

double TMVAClassification_TMlp_ANN::synapse0x7da6e60() {
   return (neuron0x6c315b0()*0.0317237);
}

double TMVAClassification_TMlp_ANN::synapse0x7da6ea0() {
   return (neuron0x6c318f0()*0.13242);
}

double TMVAClassification_TMlp_ANN::synapse0x7da6ee0() {
   return (neuron0x638c0d0()*-0.182662);
}

double TMVAClassification_TMlp_ANN::synapse0x52d6ad0() {
   return (neuron0x60b21d0()*0.328081);
}

double TMVAClassification_TMlp_ANN::synapse0x52d6b10() {
   return (neuron0x60b2510()*-0.232964);
}

double TMVAClassification_TMlp_ANN::synapse0x52d6b50() {
   return (neuron0x4eb4da0()*-0.19337);
}

double TMVAClassification_TMlp_ANN::synapse0x52d6b90() {
   return (neuron0x4eb50e0()*0.927352);
}

double TMVAClassification_TMlp_ANN::synapse0x52d6bd0() {
   return (neuron0x6077dc0()*-0.421145);
}

double TMVAClassification_TMlp_ANN::synapse0x52d6c10() {
   return (neuron0x597c140()*1.27489);
}

double TMVAClassification_TMlp_ANN::synapse0x52d6c50() {
   return (neuron0x597c480()*0.632821);
}

double TMVAClassification_TMlp_ANN::synapse0x52d6c90() {
   return (neuron0x55c7800()*0.380096);
}

double TMVAClassification_TMlp_ANN::synapse0x52d6cd0() {
   return (neuron0x55c7b40()*-0.0529681);
}

double TMVAClassification_TMlp_ANN::synapse0x7da6cd0() {
   return (neuron0x7f7a090()*-0.106012);
}

double TMVAClassification_TMlp_ANN::synapse0x7da6d10() {
   return (neuron0x673e5e0()*0.239987);
}

double TMVAClassification_TMlp_ANN::synapse0x5fa9db0() {
   return (neuron0x6078290()*-0.584868);
}

double TMVAClassification_TMlp_ANN::synapse0x5fa9df0() {
   return (neuron0x6078540()*0.273406);
}

double TMVAClassification_TMlp_ANN::synapse0x5fa9e30() {
   return (neuron0x63d6190()*0.709649);
}

double TMVAClassification_TMlp_ANN::synapse0x5fa9e70() {
   return (neuron0x63d64d0()*-1.1471);
}

double TMVAClassification_TMlp_ANN::synapse0x5fa9eb0() {
   return (neuron0x6251640()*0.151786);
}

double TMVAClassification_TMlp_ANN::synapse0x5fa9ef0() {
   return (neuron0x46213e0()*0.20368);
}

double TMVAClassification_TMlp_ANN::synapse0x5fa9f30() {
   return (neuron0x4621720()*-0.449959);
}

double TMVAClassification_TMlp_ANN::synapse0x5fa9f70() {
   return (neuron0x54fbed0()*-0.289873);
}

double TMVAClassification_TMlp_ANN::synapse0x5fa9fb0() {
   return (neuron0x7376fc0()*-0.145811);
}

double TMVAClassification_TMlp_ANN::synapse0x5fa9ff0() {
   return (neuron0x7377300()*-0.6329);
}

double TMVAClassification_TMlp_ANN::synapse0x5faa030() {
   return (neuron0x6a82e50()*-0.327424);
}

double TMVAClassification_TMlp_ANN::synapse0x5faa070() {
   return (neuron0x6636ca0()*0.40864);
}

double TMVAClassification_TMlp_ANN::synapse0x52d6f20() {
   return (neuron0x6636fe0()*-1.13607);
}

double TMVAClassification_TMlp_ANN::synapse0x52d6f60() {
   return (neuron0x51a0a30()*0.287778);
}

double TMVAClassification_TMlp_ANN::synapse0x52d6fa0() {
   return (neuron0x4d1fad0()*-0.204772);
}

double TMVAClassification_TMlp_ANN::synapse0x52d6fe0() {
   return (neuron0x4d1fe10()*-0.23405);
}

double TMVAClassification_TMlp_ANN::synapse0x52d7020() {
   return (neuron0x4c00f40()*0.198283);
}

double TMVAClassification_TMlp_ANN::synapse0x7da6d50() {
   return (neuron0x657be70()*-0.102266);
}

double TMVAClassification_TMlp_ANN::synapse0x7da6d90() {
   return (neuron0x7ec13f0()*0.711225);
}

double TMVAClassification_TMlp_ANN::synapse0x574e090() {
   return (neuron0x7ec1730()*-1.27485);
}

double TMVAClassification_TMlp_ANN::synapse0x574e0d0() {
   return (neuron0x6c315b0()*-0.358671);
}

double TMVAClassification_TMlp_ANN::synapse0x574e110() {
   return (neuron0x6c318f0()*0.617547);
}

double TMVAClassification_TMlp_ANN::synapse0x574e150() {
   return (neuron0x638c0d0()*0.243005);
}

double TMVAClassification_TMlp_ANN::synapse0x574e190() {
   return (neuron0x60b21d0()*1.05291);
}

double TMVAClassification_TMlp_ANN::synapse0x574e1d0() {
   return (neuron0x60b2510()*0.986158);
}

double TMVAClassification_TMlp_ANN::synapse0x574e210() {
   return (neuron0x4eb4da0()*-0.0607744);
}

double TMVAClassification_TMlp_ANN::synapse0x574e250() {
   return (neuron0x4eb50e0()*-0.497896);
}

double TMVAClassification_TMlp_ANN::synapse0x574e290() {
   return (neuron0x6077dc0()*0.0132517);
}

double TMVAClassification_TMlp_ANN::synapse0x574e2d0() {
   return (neuron0x597c140()*-0.0617903);
}

double TMVAClassification_TMlp_ANN::synapse0x574e310() {
   return (neuron0x597c480()*0.228328);
}

double TMVAClassification_TMlp_ANN::synapse0x574e350() {
   return (neuron0x55c7800()*1.25727);
}

double TMVAClassification_TMlp_ANN::synapse0x574e390() {
   return (neuron0x55c7b40()*0.520987);
}

double TMVAClassification_TMlp_ANN::synapse0x574df80() {
   return (neuron0x7f7a090()*-0.571492);
}

double TMVAClassification_TMlp_ANN::synapse0x574dfc0() {
   return (neuron0x673e5e0()*0.113904);
}

double TMVAClassification_TMlp_ANN::synapse0x6e4f800() {
   return (neuron0x6078290()*-0.137133);
}

double TMVAClassification_TMlp_ANN::synapse0x6e4f840() {
   return (neuron0x6078540()*0.249997);
}

double TMVAClassification_TMlp_ANN::synapse0x6e4f880() {
   return (neuron0x63d6190()*-0.178328);
}

double TMVAClassification_TMlp_ANN::synapse0x6e4f8c0() {
   return (neuron0x63d64d0()*-0.483776);
}

double TMVAClassification_TMlp_ANN::synapse0x574e3d0() {
   return (neuron0x6251640()*-0.0249863);
}

double TMVAClassification_TMlp_ANN::synapse0x574e410() {
   return (neuron0x46213e0()*0.311304);
}

double TMVAClassification_TMlp_ANN::synapse0x574e450() {
   return (neuron0x4621720()*-0.536071);
}

double TMVAClassification_TMlp_ANN::synapse0x574e490() {
   return (neuron0x54fbed0()*-0.0284635);
}

double TMVAClassification_TMlp_ANN::synapse0x574e4d0() {
   return (neuron0x7376fc0()*0.387795);
}

double TMVAClassification_TMlp_ANN::synapse0x6c8a1f0() {
   return (neuron0x7377300()*0.224804);
}

double TMVAClassification_TMlp_ANN::synapse0x6c8a230() {
   return (neuron0x6a82e50()*0.00768163);
}

double TMVAClassification_TMlp_ANN::synapse0x6c8a270() {
   return (neuron0x6636ca0()*-0.0198229);
}

double TMVAClassification_TMlp_ANN::synapse0x6c8a2b0() {
   return (neuron0x6636fe0()*0.184003);
}

double TMVAClassification_TMlp_ANN::synapse0x6c8a2f0() {
   return (neuron0x51a0a30()*0.877975);
}

double TMVAClassification_TMlp_ANN::synapse0x6c8a330() {
   return (neuron0x4d1fad0()*0.382988);
}

double TMVAClassification_TMlp_ANN::synapse0x6c8a370() {
   return (neuron0x4d1fe10()*0.357925);
}

double TMVAClassification_TMlp_ANN::synapse0x574e000() {
   return (neuron0x4c00f40()*-0.721935);
}

double TMVAClassification_TMlp_ANN::synapse0x574e040() {
   return (neuron0x657be70()*-0.804161);
}

double TMVAClassification_TMlp_ANN::synapse0x6c8a4c0() {
   return (neuron0x7ec13f0()*0.424544);
}

double TMVAClassification_TMlp_ANN::synapse0x6c8a500() {
   return (neuron0x7ec1730()*0.249094);
}

double TMVAClassification_TMlp_ANN::synapse0x6c8a540() {
   return (neuron0x6c315b0()*-0.292297);
}

double TMVAClassification_TMlp_ANN::synapse0x6c8a580() {
   return (neuron0x6c318f0()*0.503955);
}

double TMVAClassification_TMlp_ANN::synapse0x6c8a5c0() {
   return (neuron0x638c0d0()*-0.641827);
}

double TMVAClassification_TMlp_ANN::synapse0x6c8a600() {
   return (neuron0x60b21d0()*-0.0252039);
}

double TMVAClassification_TMlp_ANN::synapse0x6c8a640() {
   return (neuron0x60b2510()*0.0426474);
}

double TMVAClassification_TMlp_ANN::synapse0x6c8a680() {
   return (neuron0x4eb4da0()*-0.268408);
}

double TMVAClassification_TMlp_ANN::synapse0x6c8a6c0() {
   return (neuron0x4eb50e0()*-0.0191492);
}

double TMVAClassification_TMlp_ANN::synapse0x6c8a700() {
   return (neuron0x6077dc0()*0.177768);
}

double TMVAClassification_TMlp_ANN::synapse0x6c8a740() {
   return (neuron0x597c140()*0.561759);
}

double TMVAClassification_TMlp_ANN::synapse0x768af40() {
   return (neuron0x597c480()*-0.17373);
}

double TMVAClassification_TMlp_ANN::synapse0x768af80() {
   return (neuron0x55c7800()*-0.382766);
}

double TMVAClassification_TMlp_ANN::synapse0x768afc0() {
   return (neuron0x55c7b40()*-0.0918635);
}

double TMVAClassification_TMlp_ANN::synapse0x6c8a3b0() {
   return (neuron0x7f7a090()*0.322466);
}

double TMVAClassification_TMlp_ANN::synapse0x6c8a3f0() {
   return (neuron0x673e5e0()*0.471062);
}

double TMVAClassification_TMlp_ANN::synapse0x755ec50() {
   return (neuron0x6078290()*-0.0736193);
}

double TMVAClassification_TMlp_ANN::synapse0x755ec90() {
   return (neuron0x6078540()*0.570336);
}

double TMVAClassification_TMlp_ANN::synapse0x755ecd0() {
   return (neuron0x63d6190()*0.436759);
}

double TMVAClassification_TMlp_ANN::synapse0x755ed10() {
   return (neuron0x63d64d0()*0.0451138);
}

double TMVAClassification_TMlp_ANN::synapse0x755ed50() {
   return (neuron0x6251640()*0.64583);
}

double TMVAClassification_TMlp_ANN::synapse0x755ed90() {
   return (neuron0x46213e0()*0.404836);
}

double TMVAClassification_TMlp_ANN::synapse0x755edd0() {
   return (neuron0x4621720()*0.133892);
}

double TMVAClassification_TMlp_ANN::synapse0x755ee10() {
   return (neuron0x54fbed0()*-0.00717638);
}

double TMVAClassification_TMlp_ANN::synapse0x755ee50() {
   return (neuron0x7376fc0()*0.250108);
}

double TMVAClassification_TMlp_ANN::synapse0x755ee90() {
   return (neuron0x7377300()*-0.0995999);
}

double TMVAClassification_TMlp_ANN::synapse0x755eed0() {
   return (neuron0x6a82e50()*-0.492975);
}

double TMVAClassification_TMlp_ANN::synapse0x755ef10() {
   return (neuron0x6636ca0()*0.303022);
}

double TMVAClassification_TMlp_ANN::synapse0x755ef50() {
   return (neuron0x6636fe0()*-0.616877);
}

double TMVAClassification_TMlp_ANN::synapse0x755ef90() {
   return (neuron0x51a0a30()*-0.156002);
}

double TMVAClassification_TMlp_ANN::synapse0x755efd0() {
   return (neuron0x4d1fad0()*0.0434515);
}

double TMVAClassification_TMlp_ANN::synapse0x755f010() {
   return (neuron0x4d1fe10()*0.133987);
}

double TMVAClassification_TMlp_ANN::synapse0x6c8a430() {
   return (neuron0x4c00f40()*-0.647461);
}

double TMVAClassification_TMlp_ANN::synapse0x6c8a470() {
   return (neuron0x657be70()*-0.215766);
}

double TMVAClassification_TMlp_ANN::synapse0x755f160() {
   return (neuron0x7ec13f0()*-0.19287);
}

double TMVAClassification_TMlp_ANN::synapse0x755f1a0() {
   return (neuron0x7ec1730()*-0.833834);
}

double TMVAClassification_TMlp_ANN::synapse0x5f3b5c0() {
   return (neuron0x6c315b0()*-0.668388);
}

double TMVAClassification_TMlp_ANN::synapse0x5f3b600() {
   return (neuron0x6c318f0()*0.276222);
}

double TMVAClassification_TMlp_ANN::synapse0x5f3b640() {
   return (neuron0x638c0d0()*-0.314832);
}

double TMVAClassification_TMlp_ANN::synapse0x5f3b680() {
   return (neuron0x60b21d0()*0.354156);
}

double TMVAClassification_TMlp_ANN::synapse0x5f3b6c0() {
   return (neuron0x60b2510()*0.109402);
}

double TMVAClassification_TMlp_ANN::synapse0x5f3b700() {
   return (neuron0x4eb4da0()*-0.552367);
}

double TMVAClassification_TMlp_ANN::synapse0x5f3b740() {
   return (neuron0x4eb50e0()*-0.572898);
}

double TMVAClassification_TMlp_ANN::synapse0x5f3b780() {
   return (neuron0x6077dc0()*-0.706389);
}

double TMVAClassification_TMlp_ANN::synapse0x5f3b7c0() {
   return (neuron0x597c140()*-0.0867572);
}

double TMVAClassification_TMlp_ANN::synapse0x5f3b800() {
   return (neuron0x597c480()*0.524906);
}

double TMVAClassification_TMlp_ANN::synapse0x5f3b840() {
   return (neuron0x55c7800()*-0.218614);
}

double TMVAClassification_TMlp_ANN::synapse0x5f3b880() {
   return (neuron0x55c7b40()*0.0306066);
}

double TMVAClassification_TMlp_ANN::synapse0x5f3bad0() {
   return (neuron0x7f7a090()*0.0189551);
}

double TMVAClassification_TMlp_ANN::synapse0x5f3bb10() {
   return (neuron0x673e5e0()*-0.00431196);
}

double TMVAClassification_TMlp_ANN::synapse0x6610140() {
   return (neuron0x6078290()*-0.666053);
}

double TMVAClassification_TMlp_ANN::synapse0x6610180() {
   return (neuron0x6078540()*-0.221469);
}

double TMVAClassification_TMlp_ANN::synapse0x66101c0() {
   return (neuron0x63d6190()*-0.296483);
}

double TMVAClassification_TMlp_ANN::synapse0x6610200() {
   return (neuron0x63d64d0()*-0.771142);
}

double TMVAClassification_TMlp_ANN::synapse0x6610240() {
   return (neuron0x6251640()*-0.0153353);
}

double TMVAClassification_TMlp_ANN::synapse0x6610280() {
   return (neuron0x46213e0()*0.504683);
}

double TMVAClassification_TMlp_ANN::synapse0x66102c0() {
   return (neuron0x4621720()*0.642799);
}

double TMVAClassification_TMlp_ANN::synapse0x6610300() {
   return (neuron0x54fbed0()*0.301678);
}

double TMVAClassification_TMlp_ANN::synapse0x6610340() {
   return (neuron0x7376fc0()*0.741588);
}

double TMVAClassification_TMlp_ANN::synapse0x6610380() {
   return (neuron0x7377300()*-0.864293);
}

double TMVAClassification_TMlp_ANN::synapse0x755f050() {
   return (neuron0x6a82e50()*-1.0014);
}

double TMVAClassification_TMlp_ANN::synapse0x755f090() {
   return (neuron0x6636ca0()*-0.603605);
}

double TMVAClassification_TMlp_ANN::synapse0x755f0d0() {
   return (neuron0x6636fe0()*-0.0671411);
}

double TMVAClassification_TMlp_ANN::synapse0x755f110() {
   return (neuron0x51a0a30()*0.793504);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe8d90() {
   return (neuron0x4d1fad0()*-0.074611);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe8dd0() {
   return (neuron0x4d1fe10()*-0.355954);
}

double TMVAClassification_TMlp_ANN::synapse0x660ff90() {
   return (neuron0x4c00f40()*-0.276088);
}

double TMVAClassification_TMlp_ANN::synapse0x660ffd0() {
   return (neuron0x657be70()*0.169676);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe8f20() {
   return (neuron0x7ec13f0()*0.202305);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe8f60() {
   return (neuron0x7ec1730()*-0.146377);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe8fa0() {
   return (neuron0x6c315b0()*0.591569);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe8fe0() {
   return (neuron0x6c318f0()*0.700581);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe9020() {
   return (neuron0x638c0d0()*0.0619917);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe9060() {
   return (neuron0x60b21d0()*0.82842);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe90a0() {
   return (neuron0x60b2510()*0.58381);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe90e0() {
   return (neuron0x4eb4da0()*-0.566993);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe9120() {
   return (neuron0x4eb50e0()*0.315153);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe9160() {
   return (neuron0x6077dc0()*-0.616938);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe91a0() {
   return (neuron0x597c140()*-0.319916);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe91e0() {
   return (neuron0x597c480()*0.46598);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe9220() {
   return (neuron0x55c7800()*0.621675);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe9260() {
   return (neuron0x55c7b40()*0.200435);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe92a0() {
   return (neuron0x7f7a090()*-1.21864);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe92e0() {
   return (neuron0x673e5e0()*0.664507);
}

double TMVAClassification_TMlp_ANN::synapse0x5dbd510() {
   return (neuron0x6078290()*0.489252);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe8e10() {
   return (neuron0x6078540()*0.46439);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe8e50() {
   return (neuron0x63d6190()*0.261441);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe8e90() {
   return (neuron0x63d64d0()*0.0832034);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe8ed0() {
   return (neuron0x6251640()*-1.65508);
}

double TMVAClassification_TMlp_ANN::synapse0x4c19d30() {
   return (neuron0x46213e0()*-0.291818);
}

double TMVAClassification_TMlp_ANN::synapse0x4c19d70() {
   return (neuron0x4621720()*0.894634);
}

double TMVAClassification_TMlp_ANN::synapse0x4c19db0() {
   return (neuron0x54fbed0()*-0.162886);
}

double TMVAClassification_TMlp_ANN::synapse0x4c19df0() {
   return (neuron0x7376fc0()*0.236541);
}

double TMVAClassification_TMlp_ANN::synapse0x4c19e30() {
   return (neuron0x7377300()*-1.04565);
}

double TMVAClassification_TMlp_ANN::synapse0x4c19e70() {
   return (neuron0x6a82e50()*0.0126832);
}

double TMVAClassification_TMlp_ANN::synapse0x4c19eb0() {
   return (neuron0x6636ca0()*-0.0287914);
}

double TMVAClassification_TMlp_ANN::synapse0x4c19ef0() {
   return (neuron0x6636fe0()*-0.71116);
}

double TMVAClassification_TMlp_ANN::synapse0x4c19f30() {
   return (neuron0x51a0a30()*-0.834903);
}

double TMVAClassification_TMlp_ANN::synapse0x4c19f70() {
   return (neuron0x4d1fad0()*0.301252);
}

double TMVAClassification_TMlp_ANN::synapse0x4c19fb0() {
   return (neuron0x4d1fe10()*0.0686043);
}

double TMVAClassification_TMlp_ANN::synapse0x5dbd360() {
   return (neuron0x4c00f40()*-0.582541);
}

double TMVAClassification_TMlp_ANN::synapse0x5dbd3a0() {
   return (neuron0x657be70()*0.22007);
}

double TMVAClassification_TMlp_ANN::synapse0x4c1a100() {
   return (neuron0x7ec13f0()*-0.327559);
}

double TMVAClassification_TMlp_ANN::synapse0x4c1a140() {
   return (neuron0x7ec1730()*0.977787);
}

double TMVAClassification_TMlp_ANN::synapse0x4c1a180() {
   return (neuron0x6c315b0()*1.35678);
}

double TMVAClassification_TMlp_ANN::synapse0x4c1a1c0() {
   return (neuron0x6c318f0()*-0.205029);
}

double TMVAClassification_TMlp_ANN::synapse0x4c1a200() {
   return (neuron0x638c0d0()*-0.447164);
}

double TMVAClassification_TMlp_ANN::synapse0x4c1a240() {
   return (neuron0x60b21d0()*-0.0184512);
}

double TMVAClassification_TMlp_ANN::synapse0x4c1a280() {
   return (neuron0x60b2510()*-0.227446);
}

double TMVAClassification_TMlp_ANN::synapse0x7c6ec00() {
   return (neuron0x4eb4da0()*-0.497151);
}

double TMVAClassification_TMlp_ANN::synapse0x7c6ec40() {
   return (neuron0x4eb50e0()*-0.845988);
}

double TMVAClassification_TMlp_ANN::synapse0x7c6ec80() {
   return (neuron0x6077dc0()*-0.887272);
}

double TMVAClassification_TMlp_ANN::synapse0x7c6ecc0() {
   return (neuron0x597c140()*-1.28151);
}

double TMVAClassification_TMlp_ANN::synapse0x7c6ed00() {
   return (neuron0x597c480()*-0.12793);
}

double TMVAClassification_TMlp_ANN::synapse0x7c6ed40() {
   return (neuron0x55c7800()*0.176597);
}

double TMVAClassification_TMlp_ANN::synapse0x7c6ed80() {
   return (neuron0x55c7b40()*0.596568);
}

double TMVAClassification_TMlp_ANN::synapse0x4c19ff0() {
   return (neuron0x7f7a090()*0.46323);
}

double TMVAClassification_TMlp_ANN::synapse0x4c1a030() {
   return (neuron0x673e5e0()*0.41548);
}

double TMVAClassification_TMlp_ANN::synapse0x675ca30() {
   return (neuron0x6078290()*0.0840298);
}

double TMVAClassification_TMlp_ANN::synapse0x675ca70() {
   return (neuron0x6078540()*0.7906);
}

double TMVAClassification_TMlp_ANN::synapse0x675cab0() {
   return (neuron0x63d6190()*0.364016);
}

double TMVAClassification_TMlp_ANN::synapse0x675caf0() {
   return (neuron0x63d64d0()*1.24001);
}

double TMVAClassification_TMlp_ANN::synapse0x675cb30() {
   return (neuron0x6251640()*-0.564294);
}

double TMVAClassification_TMlp_ANN::synapse0x675cb70() {
   return (neuron0x46213e0()*0.0504834);
}

double TMVAClassification_TMlp_ANN::synapse0x675cbb0() {
   return (neuron0x4621720()*0.0770766);
}

double TMVAClassification_TMlp_ANN::synapse0x675cbf0() {
   return (neuron0x54fbed0()*0.391787);
}

double TMVAClassification_TMlp_ANN::synapse0x675cc30() {
   return (neuron0x7376fc0()*-0.0873239);
}

double TMVAClassification_TMlp_ANN::synapse0x675cc70() {
   return (neuron0x7377300()*-0.745083);
}

double TMVAClassification_TMlp_ANN::synapse0x675ccb0() {
   return (neuron0x6a82e50()*-0.739063);
}

double TMVAClassification_TMlp_ANN::synapse0x675ccf0() {
   return (neuron0x6636ca0()*0.144118);
}

double TMVAClassification_TMlp_ANN::synapse0x675cd30() {
   return (neuron0x6636fe0()*-0.273413);
}

double TMVAClassification_TMlp_ANN::synapse0x675cd70() {
   return (neuron0x51a0a30()*-0.0791881);
}

double TMVAClassification_TMlp_ANN::synapse0x675cdb0() {
   return (neuron0x4d1fad0()*0.127039);
}

double TMVAClassification_TMlp_ANN::synapse0x675cdf0() {
   return (neuron0x4d1fe10()*-0.725964);
}

double TMVAClassification_TMlp_ANN::synapse0x7c6f160() {
   return (neuron0x4c00f40()*-0.278959);
}

double TMVAClassification_TMlp_ANN::synapse0x4c1a070() {
   return (neuron0x657be70()*0.117313);
}

double TMVAClassification_TMlp_ANN::synapse0x4c1a0b0() {
   return (neuron0x7ec13f0()*-0.467062);
}

double TMVAClassification_TMlp_ANN::synapse0x675ce30() {
   return (neuron0x7ec1730()*0.454221);
}

double TMVAClassification_TMlp_ANN::synapse0x675ce70() {
   return (neuron0x6c315b0()*-0.240334);
}

double TMVAClassification_TMlp_ANN::synapse0x624f5b0() {
   return (neuron0x6c318f0()*-0.705049);
}

double TMVAClassification_TMlp_ANN::synapse0x624f5f0() {
   return (neuron0x638c0d0()*0.394485);
}

double TMVAClassification_TMlp_ANN::synapse0x624f630() {
   return (neuron0x60b21d0()*0.339242);
}

double TMVAClassification_TMlp_ANN::synapse0x624f670() {
   return (neuron0x60b2510()*-0.0704479);
}

double TMVAClassification_TMlp_ANN::synapse0x624f6b0() {
   return (neuron0x4eb4da0()*0.86481);
}

double TMVAClassification_TMlp_ANN::synapse0x624f6f0() {
   return (neuron0x4eb50e0()*-0.72642);
}

double TMVAClassification_TMlp_ANN::synapse0x624f730() {
   return (neuron0x6077dc0()*-0.176955);
}

double TMVAClassification_TMlp_ANN::synapse0x624f770() {
   return (neuron0x597c140()*0.18303);
}

double TMVAClassification_TMlp_ANN::synapse0x624f7b0() {
   return (neuron0x597c480()*-0.754409);
}

double TMVAClassification_TMlp_ANN::synapse0x624f7f0() {
   return (neuron0x55c7800()*0.448381);
}

double TMVAClassification_TMlp_ANN::synapse0x624f830() {
   return (neuron0x55c7b40()*-0.717256);
}

double TMVAClassification_TMlp_ANN::synapse0x624f4a0() {
   return (neuron0x7f7a090()*0.0985989);
}

double TMVAClassification_TMlp_ANN::synapse0x624f4e0() {
   return (neuron0x673e5e0()*-0.745858);
}

double TMVAClassification_TMlp_ANN::synapse0x762b740() {
   return (neuron0x6078290()*0.180148);
}

double TMVAClassification_TMlp_ANN::synapse0x762b780() {
   return (neuron0x6078540()*-0.233149);
}

double TMVAClassification_TMlp_ANN::synapse0x762b7c0() {
   return (neuron0x63d6190()*-0.405832);
}

double TMVAClassification_TMlp_ANN::synapse0x762b800() {
   return (neuron0x63d64d0()*0.27909);
}

double TMVAClassification_TMlp_ANN::synapse0x762b840() {
   return (neuron0x6251640()*-0.226023);
}

double TMVAClassification_TMlp_ANN::synapse0x762b880() {
   return (neuron0x46213e0()*0.0748029);
}

double TMVAClassification_TMlp_ANN::synapse0x762b8c0() {
   return (neuron0x4621720()*-0.00736895);
}

double TMVAClassification_TMlp_ANN::synapse0x762b900() {
   return (neuron0x54fbed0()*-0.611868);
}

double TMVAClassification_TMlp_ANN::synapse0x762b940() {
   return (neuron0x7376fc0()*0.735281);
}

double TMVAClassification_TMlp_ANN::synapse0x762b980() {
   return (neuron0x7377300()*0.58458);
}

double TMVAClassification_TMlp_ANN::synapse0x624fa00() {
   return (neuron0x6a82e50()*-0.32018);
}

double TMVAClassification_TMlp_ANN::synapse0x565b920() {
   return (neuron0x6636ca0()*-0.418808);
}

double TMVAClassification_TMlp_ANN::synapse0x565b960() {
   return (neuron0x6636fe0()*0.511008);
}

double TMVAClassification_TMlp_ANN::synapse0x565b9a0() {
   return (neuron0x51a0a30()*0.0144856);
}

double TMVAClassification_TMlp_ANN::synapse0x565b9e0() {
   return (neuron0x4d1fad0()*-0.0717687);
}

double TMVAClassification_TMlp_ANN::synapse0x565ba20() {
   return (neuron0x4d1fe10()*-0.524336);
}

double TMVAClassification_TMlp_ANN::synapse0x624f520() {
   return (neuron0x4c00f40()*0.351325);
}

double TMVAClassification_TMlp_ANN::synapse0x624f560() {
   return (neuron0x657be70()*0.0658361);
}

double TMVAClassification_TMlp_ANN::synapse0x565bb70() {
   return (neuron0x7ec13f0()*-0.260725);
}

double TMVAClassification_TMlp_ANN::synapse0x565bbb0() {
   return (neuron0x7ec1730()*0.0621825);
}

double TMVAClassification_TMlp_ANN::synapse0x565bbf0() {
   return (neuron0x6c315b0()*-0.0346879);
}

double TMVAClassification_TMlp_ANN::synapse0x565bc30() {
   return (neuron0x6c318f0()*0.474368);
}

double TMVAClassification_TMlp_ANN::synapse0x565bc70() {
   return (neuron0x638c0d0()*-0.274632);
}

double TMVAClassification_TMlp_ANN::synapse0x565bcb0() {
   return (neuron0x60b21d0()*-0.00519652);
}

double TMVAClassification_TMlp_ANN::synapse0x565bcf0() {
   return (neuron0x60b2510()*-0.262733);
}

double TMVAClassification_TMlp_ANN::synapse0x565bd30() {
   return (neuron0x4eb4da0()*-0.136187);
}

double TMVAClassification_TMlp_ANN::synapse0x565bd70() {
   return (neuron0x4eb50e0()*0.296494);
}

double TMVAClassification_TMlp_ANN::synapse0x565bdb0() {
   return (neuron0x6077dc0()*0.319208);
}

double TMVAClassification_TMlp_ANN::synapse0x565bdf0() {
   return (neuron0x597c140()*0.470807);
}

double TMVAClassification_TMlp_ANN::synapse0x565be30() {
   return (neuron0x597c480()*0.307338);
}

double TMVAClassification_TMlp_ANN::synapse0x565be70() {
   return (neuron0x55c7800()*0.260661);
}

double TMVAClassification_TMlp_ANN::synapse0x710c860() {
   return (neuron0x55c7b40()*0.290448);
}

double TMVAClassification_TMlp_ANN::synapse0x565ba60() {
   return (neuron0x7f7a090()*-0.191228);
}

double TMVAClassification_TMlp_ANN::synapse0x565baa0() {
   return (neuron0x673e5e0()*-0.330502);
}

double TMVAClassification_TMlp_ANN::synapse0x710cd60() {
   return (neuron0x6078290()*0.165426);
}

double TMVAClassification_TMlp_ANN::synapse0x710cda0() {
   return (neuron0x6078540()*0.334937);
}

double TMVAClassification_TMlp_ANN::synapse0x710cde0() {
   return (neuron0x63d6190()*-0.64433);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddc3c0() {
   return (neuron0x63d64d0()*-0.274417);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddc400() {
   return (neuron0x6251640()*0.2614);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddc440() {
   return (neuron0x46213e0()*-0.443867);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddc480() {
   return (neuron0x4621720()*0.265846);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddc4c0() {
   return (neuron0x54fbed0()*0.539073);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddc500() {
   return (neuron0x7376fc0()*0.302771);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddc540() {
   return (neuron0x7377300()*0.0719186);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddc580() {
   return (neuron0x6a82e50()*-0.476565);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddc5c0() {
   return (neuron0x6636ca0()*-0.358258);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddc600() {
   return (neuron0x6636fe0()*-0.199349);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddc640() {
   return (neuron0x51a0a30()*-0.251673);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddc680() {
   return (neuron0x4d1fad0()*-0.198378);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddc6c0() {
   return (neuron0x4d1fe10()*-0.233668);
}

double TMVAClassification_TMlp_ANN::synapse0x565bae0() {
   return (neuron0x4c00f40()*-0.466519);
}

double TMVAClassification_TMlp_ANN::synapse0x565bb20() {
   return (neuron0x657be70()*-0.076922);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddc810() {
   return (neuron0x7ec13f0()*0.609262);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddc850() {
   return (neuron0x7ec1730()*-0.331487);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddc890() {
   return (neuron0x6c315b0()*-0.123118);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddc8d0() {
   return (neuron0x6c318f0()*0.0297384);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddc910() {
   return (neuron0x638c0d0()*0.176384);
}

double TMVAClassification_TMlp_ANN::synapse0x4d16ed0() {
   return (neuron0x60b21d0()*0.305537);
}

double TMVAClassification_TMlp_ANN::synapse0x4d16f10() {
   return (neuron0x60b2510()*-0.428446);
}

double TMVAClassification_TMlp_ANN::synapse0x4d16f50() {
   return (neuron0x4eb4da0()*0.343016);
}

double TMVAClassification_TMlp_ANN::synapse0x4d16f90() {
   return (neuron0x4eb50e0()*0.0304092);
}

double TMVAClassification_TMlp_ANN::synapse0x4d16fd0() {
   return (neuron0x6077dc0()*0.0780011);
}

double TMVAClassification_TMlp_ANN::synapse0x4d17010() {
   return (neuron0x597c140()*-0.228822);
}

double TMVAClassification_TMlp_ANN::synapse0x4d17050() {
   return (neuron0x597c480()*0.198906);
}

double TMVAClassification_TMlp_ANN::synapse0x4d17090() {
   return (neuron0x55c7800()*-0.783768);
}

double TMVAClassification_TMlp_ANN::synapse0x4d170d0() {
   return (neuron0x55c7b40()*0.197045);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddc700() {
   return (neuron0x7f7a090()*-0.32272);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddc740() {
   return (neuron0x673e5e0()*0.636938);
}

double TMVAClassification_TMlp_ANN::synapse0x67c4c60() {
   return (neuron0x6078290()*-0.0597745);
}

double TMVAClassification_TMlp_ANN::synapse0x67c4ca0() {
   return (neuron0x6078540()*-0.454941);
}

double TMVAClassification_TMlp_ANN::synapse0x67c4ce0() {
   return (neuron0x63d6190()*0.807326);
}

double TMVAClassification_TMlp_ANN::synapse0x67c4d20() {
   return (neuron0x63d64d0()*0.336534);
}

double TMVAClassification_TMlp_ANN::synapse0x67c4d60() {
   return (neuron0x6251640()*0.424157);
}

double TMVAClassification_TMlp_ANN::synapse0x67c4da0() {
   return (neuron0x46213e0()*0.234365);
}

double TMVAClassification_TMlp_ANN::synapse0x67c4de0() {
   return (neuron0x4621720()*0.928287);
}

double TMVAClassification_TMlp_ANN::synapse0x67c4e20() {
   return (neuron0x54fbed0()*0.38187);
}

double TMVAClassification_TMlp_ANN::synapse0x67c4e60() {
   return (neuron0x7376fc0()*0.76405);
}

double TMVAClassification_TMlp_ANN::synapse0x67c4ea0() {
   return (neuron0x7377300()*-0.0216805);
}

double TMVAClassification_TMlp_ANN::synapse0x67c4ee0() {
   return (neuron0x6a82e50()*-0.590851);
}

double TMVAClassification_TMlp_ANN::synapse0x67c4f20() {
   return (neuron0x6636ca0()*-0.19297);
}

double TMVAClassification_TMlp_ANN::synapse0x4d17320() {
   return (neuron0x6636fe0()*0.513214);
}

double TMVAClassification_TMlp_ANN::synapse0x4d17360() {
   return (neuron0x51a0a30()*0.226876);
}

double TMVAClassification_TMlp_ANN::synapse0x4d173a0() {
   return (neuron0x4d1fad0()*-0.234652);
}

double TMVAClassification_TMlp_ANN::synapse0x4d173e0() {
   return (neuron0x4d1fe10()*0.121074);
}

double TMVAClassification_TMlp_ANN::synapse0x4d17420() {
   return (neuron0x4c00f40()*0.181032);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddc780() {
   return (neuron0x657be70()*0.651352);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddc7c0() {
   return (neuron0x7ec13f0()*0.233147);
}

double TMVAClassification_TMlp_ANN::synapse0x4b24cb0() {
   return (neuron0x7ec1730()*0.467863);
}

double TMVAClassification_TMlp_ANN::synapse0x4b24cf0() {
   return (neuron0x6c315b0()*0.39488);
}

double TMVAClassification_TMlp_ANN::synapse0x4b24d30() {
   return (neuron0x6c318f0()*-0.741435);
}

double TMVAClassification_TMlp_ANN::synapse0x4b24d70() {
   return (neuron0x638c0d0()*-0.693791);
}

double TMVAClassification_TMlp_ANN::synapse0x4b24db0() {
   return (neuron0x60b21d0()*0.40601);
}

double TMVAClassification_TMlp_ANN::synapse0x4b24df0() {
   return (neuron0x60b2510()*-0.370323);
}

double TMVAClassification_TMlp_ANN::synapse0x4b24e30() {
   return (neuron0x4eb4da0()*-0.454147);
}

double TMVAClassification_TMlp_ANN::synapse0x4b24e70() {
   return (neuron0x4eb50e0()*0.00344865);
}

double TMVAClassification_TMlp_ANN::synapse0x4b24eb0() {
   return (neuron0x6077dc0()*-1.00123);
}

double TMVAClassification_TMlp_ANN::synapse0x4b24ef0() {
   return (neuron0x597c140()*0.0715723);
}

double TMVAClassification_TMlp_ANN::synapse0x4b24f30() {
   return (neuron0x597c480()*0.182205);
}

double TMVAClassification_TMlp_ANN::synapse0x4b24f70() {
   return (neuron0x55c7800()*-0.554178);
}

double TMVAClassification_TMlp_ANN::synapse0x4b24fb0() {
   return (neuron0x55c7b40()*-1.57021);
}

double TMVAClassification_TMlp_ANN::synapse0x4b24ba0() {
   return (neuron0x7f7a090()*-0.119554);
}

double TMVAClassification_TMlp_ANN::synapse0x4b24be0() {
   return (neuron0x673e5e0()*0.931521);
}

double TMVAClassification_TMlp_ANN::synapse0x7772670() {
   return (neuron0x6078290()*-0.0678303);
}

double TMVAClassification_TMlp_ANN::synapse0x4b25100() {
   return (neuron0x6078540()*0.384802);
}

double TMVAClassification_TMlp_ANN::synapse0x6078420() {
   return (neuron0x63d6190()*0.477183);
}

double TMVAClassification_TMlp_ANN::synapse0x6078460() {
   return (neuron0x63d64d0()*0.29718);
}

double TMVAClassification_TMlp_ANN::synapse0x7689420() {
   return (neuron0x6251640()*-0.229571);
}

double TMVAClassification_TMlp_ANN::synapse0x7689460() {
   return (neuron0x46213e0()*-0.515177);
}

double TMVAClassification_TMlp_ANN::synapse0x7ec1eb0() {
   return (neuron0x4621720()*-0.197612);
}

double TMVAClassification_TMlp_ANN::synapse0x63d63b0() {
   return (neuron0x54fbed0()*-0.788964);
}

double TMVAClassification_TMlp_ANN::synapse0x63d63f0() {
   return (neuron0x7376fc0()*0.248481);
}

double TMVAClassification_TMlp_ANN::synapse0x753f630() {
   return (neuron0x7377300()*0.436604);
}

double TMVAClassification_TMlp_ANN::synapse0x753f670() {
   return (neuron0x6a82e50()*0.0203583);
}

double TMVAClassification_TMlp_ANN::synapse0x5101260() {
   return (neuron0x6636ca0()*-0.264681);
}

double TMVAClassification_TMlp_ANN::synapse0x6251860() {
   return (neuron0x6636fe0()*-0.3189);
}

double TMVAClassification_TMlp_ANN::synapse0x62518a0() {
   return (neuron0x51a0a30()*-0.394877);
}

double TMVAClassification_TMlp_ANN::synapse0x4621600() {
   return (neuron0x4d1fad0()*-0.391488);
}

double TMVAClassification_TMlp_ANN::synapse0x4621640() {
   return (neuron0x4d1fe10()*0.207658);
}

double TMVAClassification_TMlp_ANN::synapse0x4e1f4f0() {
   return (neuron0x4c00f40()*0.329075);
}

double TMVAClassification_TMlp_ANN::synapse0x54fc0f0() {
   return (neuron0x657be70()*-0.0388235);
}

double TMVAClassification_TMlp_ANN::synapse0x54fc130() {
   return (neuron0x7ec13f0()*-0.143999);
}

double TMVAClassification_TMlp_ANN::synapse0x73771e0() {
   return (neuron0x7ec1730()*-0.187774);
}

double TMVAClassification_TMlp_ANN::synapse0x7377220() {
   return (neuron0x6c315b0()*-0.15617);
}

double TMVAClassification_TMlp_ANN::synapse0x6a40ac0() {
   return (neuron0x6c318f0()*-0.297069);
}

double TMVAClassification_TMlp_ANN::synapse0x6a83070() {
   return (neuron0x638c0d0()*0.118362);
}

double TMVAClassification_TMlp_ANN::synapse0x6a830b0() {
   return (neuron0x60b21d0()*-0.284707);
}

double TMVAClassification_TMlp_ANN::synapse0x6636ec0() {
   return (neuron0x60b2510()*0.305949);
}

double TMVAClassification_TMlp_ANN::synapse0x6636f00() {
   return (neuron0x4eb4da0()*0.423155);
}

double TMVAClassification_TMlp_ANN::synapse0x653de20() {
   return (neuron0x4eb50e0()*-0.34417);
}

double TMVAClassification_TMlp_ANN::synapse0x51a0c50() {
   return (neuron0x6077dc0()*0.196747);
}

double TMVAClassification_TMlp_ANN::synapse0x51a0c90() {
   return (neuron0x597c140()*0.172734);
}

double TMVAClassification_TMlp_ANN::synapse0x4d1fcf0() {
   return (neuron0x597c480()*0.362331);
}

double TMVAClassification_TMlp_ANN::synapse0x4d1fd30() {
   return (neuron0x55c7800()*0.17073);
}

double TMVAClassification_TMlp_ANN::synapse0x6f3ce70() {
   return (neuron0x55c7b40()*-0.0303738);
}

double TMVAClassification_TMlp_ANN::synapse0x51a0e00() {
   return (neuron0x7f7a090()*0.541147);
}

double TMVAClassification_TMlp_ANN::synapse0x51a0e40() {
   return (neuron0x673e5e0()*0.518075);
}

double TMVAClassification_TMlp_ANN::synapse0x5796d70() {
   return (neuron0x6078290()*-0.213437);
}

double TMVAClassification_TMlp_ANN::synapse0x5796db0() {
   return (neuron0x6078540()*-0.495184);
}

double TMVAClassification_TMlp_ANN::synapse0x5796df0() {
   return (neuron0x63d6190()*0.144456);
}

double TMVAClassification_TMlp_ANN::synapse0x5796e30() {
   return (neuron0x63d64d0()*0.112911);
}

double TMVAClassification_TMlp_ANN::synapse0x5796e70() {
   return (neuron0x6251640()*0.497198);
}

double TMVAClassification_TMlp_ANN::synapse0x5796eb0() {
   return (neuron0x46213e0()*0.425574);
}

double TMVAClassification_TMlp_ANN::synapse0x5796ef0() {
   return (neuron0x4621720()*0.232762);
}

double TMVAClassification_TMlp_ANN::synapse0x5796f30() {
   return (neuron0x54fbed0()*0.129051);
}

double TMVAClassification_TMlp_ANN::synapse0x5796f70() {
   return (neuron0x7376fc0()*-0.391258);
}

double TMVAClassification_TMlp_ANN::synapse0x5796fb0() {
   return (neuron0x7377300()*0.229952);
}

double TMVAClassification_TMlp_ANN::synapse0x5796ff0() {
   return (neuron0x6a82e50()*0.384982);
}

double TMVAClassification_TMlp_ANN::synapse0x5797030() {
   return (neuron0x6636ca0()*0.158786);
}

double TMVAClassification_TMlp_ANN::synapse0x5797070() {
   return (neuron0x6636fe0()*-0.0837735);
}

double TMVAClassification_TMlp_ANN::synapse0x57970b0() {
   return (neuron0x51a0a30()*-0.0723273);
}

double TMVAClassification_TMlp_ANN::synapse0x57970f0() {
   return (neuron0x4d1fad0()*0.116373);
}

double TMVAClassification_TMlp_ANN::synapse0x5797130() {
   return (neuron0x4d1fe10()*-0.301644);
}

double TMVAClassification_TMlp_ANN::synapse0x7f2a100() {
   return (neuron0x4c00f40()*-0.579935);
}

double TMVAClassification_TMlp_ANN::synapse0x7f2a140() {
   return (neuron0x657be70()*0.354256);
}

double TMVAClassification_TMlp_ANN::synapse0x7ec1610() {
   return (neuron0x7ec13f0()*0.171221);
}

double TMVAClassification_TMlp_ANN::synapse0x7ec1650() {
   return (neuron0x7ec1730()*-0.468451);
}

double TMVAClassification_TMlp_ANN::synapse0x4e1f5c0() {
   return (neuron0x6c315b0()*0.557552);
}

double TMVAClassification_TMlp_ANN::synapse0x4e1f600() {
   return (neuron0x6c318f0()*0.391399);
}

double TMVAClassification_TMlp_ANN::synapse0x6c317d0() {
   return (neuron0x638c0d0()*-0.279436);
}

double TMVAClassification_TMlp_ANN::synapse0x6c31810() {
   return (neuron0x60b21d0()*0.291761);
}

double TMVAClassification_TMlp_ANN::synapse0x638bfb0() {
   return (neuron0x60b2510()*0.317605);
}

double TMVAClassification_TMlp_ANN::synapse0x638bff0() {
   return (neuron0x4eb4da0()*0.506054);
}

double TMVAClassification_TMlp_ANN::synapse0x638c2f0() {
   return (neuron0x4eb50e0()*0.295873);
}

double TMVAClassification_TMlp_ANN::synapse0x638c330() {
   return (neuron0x6077dc0()*-0.225312);
}

double TMVAClassification_TMlp_ANN::synapse0x60b23f0() {
   return (neuron0x597c140()*-0.228225);
}

double TMVAClassification_TMlp_ANN::synapse0x60b2430() {
   return (neuron0x597c480()*-0.23528);
}

double TMVAClassification_TMlp_ANN::synapse0x638c410() {
   return (neuron0x55c7800()*-0.162621);
}

double TMVAClassification_TMlp_ANN::synapse0x638c450() {
   return (neuron0x55c7b40()*-0.557667);
}

double TMVAClassification_TMlp_ANN::synapse0x4eb4fc0() {
   return (neuron0x7f7a090()*-0.449488);
}

double TMVAClassification_TMlp_ANN::synapse0x4eb5000() {
   return (neuron0x673e5e0()*0.300533);
}

double TMVAClassification_TMlp_ANN::synapse0x68c50b0() {
   return (neuron0x6078290()*-0.441756);
}

double TMVAClassification_TMlp_ANN::synapse0x68c50f0() {
   return (neuron0x6078540()*0.305189);
}

double TMVAClassification_TMlp_ANN::synapse0x68c5130() {
   return (neuron0x63d6190()*-0.528832);
}

double TMVAClassification_TMlp_ANN::synapse0x68c5170() {
   return (neuron0x63d64d0()*-0.477035);
}

double TMVAClassification_TMlp_ANN::synapse0x6078100() {
   return (neuron0x6251640()*0.244484);
}

double TMVAClassification_TMlp_ANN::synapse0x6078140() {
   return (neuron0x46213e0()*0.0737381);
}

double TMVAClassification_TMlp_ANN::synapse0x55c7a20() {
   return (neuron0x4621720()*0.755363);
}

double TMVAClassification_TMlp_ANN::synapse0x55c7a60() {
   return (neuron0x54fbed0()*-0.829529);
}

double TMVAClassification_TMlp_ANN::synapse0x7f79f70() {
   return (neuron0x7376fc0()*-0.174734);
}

double TMVAClassification_TMlp_ANN::synapse0x7f79fb0() {
   return (neuron0x7377300()*0.182457);
}

double TMVAClassification_TMlp_ANN::synapse0x7f7a2b0() {
   return (neuron0x6a82e50()*-0.0486599);
}

double TMVAClassification_TMlp_ANN::synapse0x7f7a2f0() {
   return (neuron0x6636ca0()*1.15083);
}

double TMVAClassification_TMlp_ANN::synapse0x7f7a3d0() {
   return (neuron0x6636fe0()*0.71126);
}

double TMVAClassification_TMlp_ANN::synapse0x7f7a410() {
   return (neuron0x51a0a30()*-0.262967);
}

double TMVAClassification_TMlp_ANN::synapse0x4b24c20() {
   return (neuron0x4d1fad0()*0.645807);
}

double TMVAClassification_TMlp_ANN::synapse0x4b24c60() {
   return (neuron0x4d1fe10()*1.05074);
}

double TMVAClassification_TMlp_ANN::synapse0x6077ca0() {
   return (neuron0x4c00f40()*0.00924734);
}

double TMVAClassification_TMlp_ANN::synapse0x6077ce0() {
   return (neuron0x657be70()*0.788889);
}

double TMVAClassification_TMlp_ANN::synapse0x6251a10() {
   return (neuron0x7ec13f0()*0.198293);
}

double TMVAClassification_TMlp_ANN::synapse0x6251a50() {
   return (neuron0x7ec1730()*0.752166);
}

double TMVAClassification_TMlp_ANN::synapse0x54fc2a0() {
   return (neuron0x6c315b0()*0.00659331);
}

double TMVAClassification_TMlp_ANN::synapse0x54fc2e0() {
   return (neuron0x6c318f0()*-0.672702);
}

double TMVAClassification_TMlp_ANN::synapse0x6a83220() {
   return (neuron0x638c0d0()*-0.296248);
}

double TMVAClassification_TMlp_ANN::synapse0x6a83260() {
   return (neuron0x60b21d0()*0.0102821);
}

double TMVAClassification_TMlp_ANN::synapse0x77726b0() {
   return (neuron0x60b2510()*-0.528882);
}

double TMVAClassification_TMlp_ANN::synapse0x77726f0() {
   return (neuron0x4eb4da0()*-0.291934);
}

double TMVAClassification_TMlp_ANN::synapse0x7772730() {
   return (neuron0x4eb50e0()*0.27293);
}

double TMVAClassification_TMlp_ANN::synapse0x4e80ce0() {
   return (neuron0x6077dc0()*0.648518);
}

double TMVAClassification_TMlp_ANN::synapse0x4e80d20() {
   return (neuron0x597c140()*0.000819349);
}

double TMVAClassification_TMlp_ANN::synapse0x4e80d60() {
   return (neuron0x597c480()*0.00399327);
}

double TMVAClassification_TMlp_ANN::synapse0x5fa37d0() {
   return (neuron0x55c7800()*0.304869);
}

double TMVAClassification_TMlp_ANN::synapse0x5fa3810() {
   return (neuron0x55c7b40()*0.472779);
}

double TMVAClassification_TMlp_ANN::synapse0x68c4c00() {
   return (neuron0x7f7a090()*0.815583);
}

double TMVAClassification_TMlp_ANN::synapse0x68c4c40() {
   return (neuron0x673e5e0()*0.727501);
}

double TMVAClassification_TMlp_ANN::synapse0x5fa3d10() {
   return (neuron0x6078290()*0.533333);
}

double TMVAClassification_TMlp_ANN::synapse0x5fa3d50() {
   return (neuron0x6078540()*0.360208);
}

double TMVAClassification_TMlp_ANN::synapse0x669deb0() {
   return (neuron0x63d6190()*-0.162867);
}

double TMVAClassification_TMlp_ANN::synapse0x669def0() {
   return (neuron0x63d64d0()*0.204451);
}

double TMVAClassification_TMlp_ANN::synapse0x669df30() {
   return (neuron0x6251640()*-0.239067);
}

double TMVAClassification_TMlp_ANN::synapse0x669df70() {
   return (neuron0x46213e0()*-1.12553);
}

double TMVAClassification_TMlp_ANN::synapse0x669dfb0() {
   return (neuron0x4621720()*0.477552);
}

double TMVAClassification_TMlp_ANN::synapse0x669dff0() {
   return (neuron0x54fbed0()*0.429074);
}

double TMVAClassification_TMlp_ANN::synapse0x669e030() {
   return (neuron0x7376fc0()*-0.566255);
}

double TMVAClassification_TMlp_ANN::synapse0x669e070() {
   return (neuron0x7377300()*-0.0287974);
}

double TMVAClassification_TMlp_ANN::synapse0x669e0b0() {
   return (neuron0x6a82e50()*-0.398427);
}

double TMVAClassification_TMlp_ANN::synapse0x669e0f0() {
   return (neuron0x6636ca0()*-0.349199);
}

double TMVAClassification_TMlp_ANN::synapse0x669e130() {
   return (neuron0x6636fe0()*0.226693);
}

double TMVAClassification_TMlp_ANN::synapse0x669e170() {
   return (neuron0x51a0a30()*0.425084);
}

double TMVAClassification_TMlp_ANN::synapse0x669e1b0() {
   return (neuron0x4d1fad0()*-0.381322);
}

double TMVAClassification_TMlp_ANN::synapse0x669e1f0() {
   return (neuron0x4d1fe10()*0.322675);
}

double TMVAClassification_TMlp_ANN::synapse0x68c4c80() {
   return (neuron0x4c00f40()*-0.118476);
}

double TMVAClassification_TMlp_ANN::synapse0x68c4cc0() {
   return (neuron0x657be70()*0.298124);
}

double TMVAClassification_TMlp_ANN::synapse0x669e340() {
   return (neuron0x7ec13f0()*-0.216143);
}

double TMVAClassification_TMlp_ANN::synapse0x669e380() {
   return (neuron0x7ec1730()*-0.309437);
}

double TMVAClassification_TMlp_ANN::synapse0x669e3c0() {
   return (neuron0x6c315b0()*-0.770678);
}

double TMVAClassification_TMlp_ANN::synapse0x669e400() {
   return (neuron0x6c318f0()*-0.372876);
}

double TMVAClassification_TMlp_ANN::synapse0x59a8e90() {
   return (neuron0x638c0d0()*-0.106099);
}

double TMVAClassification_TMlp_ANN::synapse0x59a8ed0() {
   return (neuron0x60b21d0()*0.180027);
}

double TMVAClassification_TMlp_ANN::synapse0x59a8f10() {
   return (neuron0x60b2510()*-0.181021);
}

double TMVAClassification_TMlp_ANN::synapse0x59a8f50() {
   return (neuron0x4eb4da0()*0.700301);
}

double TMVAClassification_TMlp_ANN::synapse0x59a8f90() {
   return (neuron0x4eb50e0()*0.535105);
}

double TMVAClassification_TMlp_ANN::synapse0x59a8fd0() {
   return (neuron0x6077dc0()*0.309336);
}

double TMVAClassification_TMlp_ANN::synapse0x59a9010() {
   return (neuron0x597c140()*-0.227211);
}

double TMVAClassification_TMlp_ANN::synapse0x59a9050() {
   return (neuron0x597c480()*-0.0409171);
}

double TMVAClassification_TMlp_ANN::synapse0x59a9090() {
   return (neuron0x55c7800()*0.714828);
}

double TMVAClassification_TMlp_ANN::synapse0x59a90d0() {
   return (neuron0x55c7b40()*-0.118191);
}

double TMVAClassification_TMlp_ANN::synapse0x669e230() {
   return (neuron0x7f7a090()*-0.239332);
}

double TMVAClassification_TMlp_ANN::synapse0x669e270() {
   return (neuron0x673e5e0()*0.384404);
}

double TMVAClassification_TMlp_ANN::synapse0x5888970() {
   return (neuron0x6078290()*0.487564);
}

double TMVAClassification_TMlp_ANN::synapse0x58889b0() {
   return (neuron0x6078540()*0.59424);
}

double TMVAClassification_TMlp_ANN::synapse0x58889f0() {
   return (neuron0x63d6190()*-0.601292);
}

double TMVAClassification_TMlp_ANN::synapse0x5888a30() {
   return (neuron0x63d64d0()*-0.801681);
}

double TMVAClassification_TMlp_ANN::synapse0x5888a70() {
   return (neuron0x6251640()*0.778509);
}

double TMVAClassification_TMlp_ANN::synapse0x5888ab0() {
   return (neuron0x46213e0()*0.497156);
}

double TMVAClassification_TMlp_ANN::synapse0x5888af0() {
   return (neuron0x4621720()*0.0350412);
}

double TMVAClassification_TMlp_ANN::synapse0x5888b30() {
   return (neuron0x54fbed0()*0.307966);
}

double TMVAClassification_TMlp_ANN::synapse0x5888b70() {
   return (neuron0x7376fc0()*0.0681159);
}

double TMVAClassification_TMlp_ANN::synapse0x5888bb0() {
   return (neuron0x7377300()*0.201624);
}

double TMVAClassification_TMlp_ANN::synapse0x5888bf0() {
   return (neuron0x6a82e50()*0.161681);
}

double TMVAClassification_TMlp_ANN::synapse0x5888c30() {
   return (neuron0x6636ca0()*-0.251214);
}

double TMVAClassification_TMlp_ANN::synapse0x59a9320() {
   return (neuron0x6636fe0()*-0.176681);
}

double TMVAClassification_TMlp_ANN::synapse0x59a9360() {
   return (neuron0x51a0a30()*-0.907225);
}

double TMVAClassification_TMlp_ANN::synapse0x59a93a0() {
   return (neuron0x4d1fad0()*-0.649104);
}

double TMVAClassification_TMlp_ANN::synapse0x59a93e0() {
   return (neuron0x4d1fe10()*0.202759);
}

double TMVAClassification_TMlp_ANN::synapse0x669e2b0() {
   return (neuron0x4c00f40()*0.162902);
}

double TMVAClassification_TMlp_ANN::synapse0x669e2f0() {
   return (neuron0x657be70()*-0.218462);
}

double TMVAClassification_TMlp_ANN::synapse0x7b58a90() {
   return (neuron0x7ec13f0()*0.062998);
}

double TMVAClassification_TMlp_ANN::synapse0x7b58ad0() {
   return (neuron0x7ec1730()*-0.236669);
}

double TMVAClassification_TMlp_ANN::synapse0x7b58b10() {
   return (neuron0x6c315b0()*-0.209372);
}

double TMVAClassification_TMlp_ANN::synapse0x7b58b50() {
   return (neuron0x6c318f0()*0.293941);
}

double TMVAClassification_TMlp_ANN::synapse0x7b58b90() {
   return (neuron0x638c0d0()*0.468666);
}

double TMVAClassification_TMlp_ANN::synapse0x7b58bd0() {
   return (neuron0x60b21d0()*-0.113554);
}

double TMVAClassification_TMlp_ANN::synapse0x7b58c10() {
   return (neuron0x60b2510()*-0.128615);
}

double TMVAClassification_TMlp_ANN::synapse0x7b58c50() {
   return (neuron0x4eb4da0()*-0.000191283);
}

double TMVAClassification_TMlp_ANN::synapse0x7b58c90() {
   return (neuron0x4eb50e0()*-0.129133);
}

double TMVAClassification_TMlp_ANN::synapse0x7b58cd0() {
   return (neuron0x6077dc0()*0.726607);
}

double TMVAClassification_TMlp_ANN::synapse0x7b58d10() {
   return (neuron0x597c140()*-0.346327);
}

double TMVAClassification_TMlp_ANN::synapse0x7b58d50() {
   return (neuron0x597c480()*-0.321419);
}

double TMVAClassification_TMlp_ANN::synapse0x7b58d90() {
   return (neuron0x55c7800()*0.356352);
}

double TMVAClassification_TMlp_ANN::synapse0x7b58dd0() {
   return (neuron0x55c7b40()*0.294271);
}

double TMVAClassification_TMlp_ANN::synapse0x7b58980() {
   return (neuron0x7f7a090()*-0.333007);
}

double TMVAClassification_TMlp_ANN::synapse0x7b589c0() {
   return (neuron0x673e5e0()*0.625586);
}

double TMVAClassification_TMlp_ANN::synapse0x6dcd960() {
   return (neuron0x6078290()*-0.3336);
}

double TMVAClassification_TMlp_ANN::synapse0x6dcd9a0() {
   return (neuron0x6078540()*1.04042);
}

double TMVAClassification_TMlp_ANN::synapse0x6dcd9e0() {
   return (neuron0x63d6190()*-0.236773);
}

double TMVAClassification_TMlp_ANN::synapse0x6dcda20() {
   return (neuron0x63d64d0()*-0.382201);
}

double TMVAClassification_TMlp_ANN::synapse0x7b58e10() {
   return (neuron0x6251640()*0.162429);
}

double TMVAClassification_TMlp_ANN::synapse0x7b58e50() {
   return (neuron0x46213e0()*0.49551);
}

double TMVAClassification_TMlp_ANN::synapse0x7b58e90() {
   return (neuron0x4621720()*1.06846);
}

double TMVAClassification_TMlp_ANN::synapse0x7b58ed0() {
   return (neuron0x54fbed0()*-0.886691);
}

double TMVAClassification_TMlp_ANN::synapse0x61d3c10() {
   return (neuron0x7376fc0()*0.124428);
}

double TMVAClassification_TMlp_ANN::synapse0x61d3c50() {
   return (neuron0x7377300()*0.141886);
}

double TMVAClassification_TMlp_ANN::synapse0x61d3c90() {
   return (neuron0x6a82e50()*-0.750399);
}

double TMVAClassification_TMlp_ANN::synapse0x61d3cd0() {
   return (neuron0x6636ca0()*-0.064825);
}

double TMVAClassification_TMlp_ANN::synapse0x61d3d10() {
   return (neuron0x6636fe0()*-0.575426);
}

double TMVAClassification_TMlp_ANN::synapse0x61d3d50() {
   return (neuron0x51a0a30()*0.881187);
}

double TMVAClassification_TMlp_ANN::synapse0x61d3d90() {
   return (neuron0x4d1fad0()*-0.792874);
}

double TMVAClassification_TMlp_ANN::synapse0x61d3dd0() {
   return (neuron0x4d1fe10()*-0.556222);
}

double TMVAClassification_TMlp_ANN::synapse0x7b58a00() {
   return (neuron0x4c00f40()*-0.182877);
}

double TMVAClassification_TMlp_ANN::synapse0x7b58a40() {
   return (neuron0x657be70()*-0.635647);
}

double TMVAClassification_TMlp_ANN::synapse0x61d3f20() {
   return (neuron0x7ec13f0()*-0.114981);
}

double TMVAClassification_TMlp_ANN::synapse0x61d3f60() {
   return (neuron0x7ec1730()*0.332864);
}

double TMVAClassification_TMlp_ANN::synapse0x61d3fa0() {
   return (neuron0x6c315b0()*0.611897);
}

double TMVAClassification_TMlp_ANN::synapse0x61d3fe0() {
   return (neuron0x6c318f0()*1.19583);
}

double TMVAClassification_TMlp_ANN::synapse0x61d4020() {
   return (neuron0x638c0d0()*0.63166);
}

double TMVAClassification_TMlp_ANN::synapse0x61d4060() {
   return (neuron0x60b21d0()*1.183);
}

double TMVAClassification_TMlp_ANN::synapse0x61d40a0() {
   return (neuron0x60b2510()*0.275095);
}

double TMVAClassification_TMlp_ANN::synapse0x61d40e0() {
   return (neuron0x4eb4da0()*-0.077462);
}

double TMVAClassification_TMlp_ANN::synapse0x61d4120() {
   return (neuron0x4eb50e0()*-0.371238);
}

double TMVAClassification_TMlp_ANN::synapse0x61d4160() {
   return (neuron0x6077dc0()*-0.150426);
}

double TMVAClassification_TMlp_ANN::synapse0x7c1a1e0() {
   return (neuron0x597c140()*0.0597289);
}

double TMVAClassification_TMlp_ANN::synapse0x7c1a220() {
   return (neuron0x597c480()*0.102861);
}

double TMVAClassification_TMlp_ANN::synapse0x7c1a260() {
   return (neuron0x55c7800()*1.88451);
}

double TMVAClassification_TMlp_ANN::synapse0x7c1a2a0() {
   return (neuron0x55c7b40()*0.187215);
}

double TMVAClassification_TMlp_ANN::synapse0x61d3e10() {
   return (neuron0x7f7a090()*-1.67627);
}

double TMVAClassification_TMlp_ANN::synapse0x61d3e50() {
   return (neuron0x673e5e0()*0.243755);
}

double TMVAClassification_TMlp_ANN::synapse0x51663a0() {
   return (neuron0x6078290()*0.304415);
}

double TMVAClassification_TMlp_ANN::synapse0x51663e0() {
   return (neuron0x6078540()*0.394575);
}

double TMVAClassification_TMlp_ANN::synapse0x5166420() {
   return (neuron0x63d6190()*0.157006);
}

double TMVAClassification_TMlp_ANN::synapse0x5166460() {
   return (neuron0x63d64d0()*0.256787);
}

double TMVAClassification_TMlp_ANN::synapse0x51664a0() {
   return (neuron0x6251640()*-0.126057);
}

double TMVAClassification_TMlp_ANN::synapse0x51664e0() {
   return (neuron0x46213e0()*0.435021);
}

double TMVAClassification_TMlp_ANN::synapse0x5166520() {
   return (neuron0x4621720()*0.2179);
}

double TMVAClassification_TMlp_ANN::synapse0x5166560() {
   return (neuron0x54fbed0()*-0.200972);
}

double TMVAClassification_TMlp_ANN::synapse0x51665a0() {
   return (neuron0x7376fc0()*-0.37834);
}

double TMVAClassification_TMlp_ANN::synapse0x51665e0() {
   return (neuron0x7377300()*-0.0853581);
}

double TMVAClassification_TMlp_ANN::synapse0x5166620() {
   return (neuron0x6a82e50()*0.0270796);
}

double TMVAClassification_TMlp_ANN::synapse0x5166660() {
   return (neuron0x6636ca0()*-0.164379);
}

double TMVAClassification_TMlp_ANN::synapse0x51666a0() {
   return (neuron0x6636fe0()*-0.569217);
}

double TMVAClassification_TMlp_ANN::synapse0x51666e0() {
   return (neuron0x51a0a30()*-0.146473);
}

double TMVAClassification_TMlp_ANN::synapse0x5166720() {
   return (neuron0x4d1fad0()*-0.251914);
}

double TMVAClassification_TMlp_ANN::synapse0x5166760() {
   return (neuron0x4d1fe10()*0.328878);
}

double TMVAClassification_TMlp_ANN::synapse0x61d3e90() {
   return (neuron0x4c00f40()*0.391662);
}

double TMVAClassification_TMlp_ANN::synapse0x61d3ed0() {
   return (neuron0x657be70()*-0.347051);
}

double TMVAClassification_TMlp_ANN::synapse0x51668b0() {
   return (neuron0x7ec13f0()*1.03797);
}

double TMVAClassification_TMlp_ANN::synapse0x51668f0() {
   return (neuron0x7ec1730()*-0.0269846);
}

double TMVAClassification_TMlp_ANN::synapse0x6708be0() {
   return (neuron0x6c315b0()*0.488552);
}

double TMVAClassification_TMlp_ANN::synapse0x6708c20() {
   return (neuron0x6c318f0()*-0.480577);
}

double TMVAClassification_TMlp_ANN::synapse0x6708c60() {
   return (neuron0x638c0d0()*0.501197);
}

double TMVAClassification_TMlp_ANN::synapse0x6708ca0() {
   return (neuron0x60b21d0()*0.490567);
}

double TMVAClassification_TMlp_ANN::synapse0x6708ce0() {
   return (neuron0x60b2510()*-0.0338232);
}

double TMVAClassification_TMlp_ANN::synapse0x6708d20() {
   return (neuron0x4eb4da0()*0.103412);
}

double TMVAClassification_TMlp_ANN::synapse0x6708d60() {
   return (neuron0x4eb50e0()*0.0715091);
}

double TMVAClassification_TMlp_ANN::synapse0x6708da0() {
   return (neuron0x6077dc0()*0.296286);
}

double TMVAClassification_TMlp_ANN::synapse0x6708de0() {
   return (neuron0x597c140()*0.559707);
}

double TMVAClassification_TMlp_ANN::synapse0x6708e20() {
   return (neuron0x597c480()*0.153931);
}

double TMVAClassification_TMlp_ANN::synapse0x6708e60() {
   return (neuron0x55c7800()*-0.525132);
}

double TMVAClassification_TMlp_ANN::synapse0x6708ea0() {
   return (neuron0x55c7b40()*-0.420577);
}

double TMVAClassification_TMlp_ANN::synapse0x67090f0() {
   return (neuron0x7f7a090()*0.677478);
}

double TMVAClassification_TMlp_ANN::synapse0x6709130() {
   return (neuron0x673e5e0()*0.437204);
}

double TMVAClassification_TMlp_ANN::synapse0x7f70600() {
   return (neuron0x6078290()*-0.29346);
}

double TMVAClassification_TMlp_ANN::synapse0x7f70640() {
   return (neuron0x6078540()*-0.138291);
}

double TMVAClassification_TMlp_ANN::synapse0x7f70680() {
   return (neuron0x63d6190()*-0.108821);
}

double TMVAClassification_TMlp_ANN::synapse0x7f706c0() {
   return (neuron0x63d64d0()*-0.498513);
}

double TMVAClassification_TMlp_ANN::synapse0x7f70700() {
   return (neuron0x6251640()*-0.349254);
}

double TMVAClassification_TMlp_ANN::synapse0x7f70740() {
   return (neuron0x46213e0()*0.0312776);
}

double TMVAClassification_TMlp_ANN::synapse0x7f70780() {
   return (neuron0x4621720()*0.171287);
}

double TMVAClassification_TMlp_ANN::synapse0x7f707c0() {
   return (neuron0x54fbed0()*-0.256404);
}

double TMVAClassification_TMlp_ANN::synapse0x7f70800() {
   return (neuron0x7376fc0()*-0.357525);
}

double TMVAClassification_TMlp_ANN::synapse0x7f70840() {
   return (neuron0x7377300()*-0.140127);
}

double TMVAClassification_TMlp_ANN::synapse0x51667a0() {
   return (neuron0x6a82e50()*-0.142351);
}

double TMVAClassification_TMlp_ANN::synapse0x51667e0() {
   return (neuron0x6636ca0()*-0.0702901);
}

double TMVAClassification_TMlp_ANN::synapse0x5166820() {
   return (neuron0x6636fe0()*-0.524762);
}

double TMVAClassification_TMlp_ANN::synapse0x5166860() {
   return (neuron0x51a0a30()*0.0852392);
}

double TMVAClassification_TMlp_ANN::synapse0x5bee050() {
   return (neuron0x4d1fad0()*0.205922);
}

double TMVAClassification_TMlp_ANN::synapse0x5bee090() {
   return (neuron0x4d1fe10()*-0.289565);
}

double TMVAClassification_TMlp_ANN::synapse0x7f70450() {
   return (neuron0x4c00f40()*-0.243391);
}

double TMVAClassification_TMlp_ANN::synapse0x7f70490() {
   return (neuron0x657be70()*-0.0313683);
}

double TMVAClassification_TMlp_ANN::synapse0x5bee1e0() {
   return (neuron0x7ec13f0()*0.0719391);
}

double TMVAClassification_TMlp_ANN::synapse0x5bee220() {
   return (neuron0x7ec1730()*0.17476);
}

double TMVAClassification_TMlp_ANN::synapse0x5bee260() {
   return (neuron0x6c315b0()*0.661473);
}

double TMVAClassification_TMlp_ANN::synapse0x5bee2a0() {
   return (neuron0x6c318f0()*-0.205421);
}

double TMVAClassification_TMlp_ANN::synapse0x5bee2e0() {
   return (neuron0x638c0d0()*0.378666);
}

double TMVAClassification_TMlp_ANN::synapse0x5bee320() {
   return (neuron0x60b21d0()*0.171784);
}

double TMVAClassification_TMlp_ANN::synapse0x5bee360() {
   return (neuron0x60b2510()*0.298317);
}

double TMVAClassification_TMlp_ANN::synapse0x5bee3a0() {
   return (neuron0x4eb4da0()*-0.256826);
}

double TMVAClassification_TMlp_ANN::synapse0x5bee3e0() {
   return (neuron0x4eb50e0()*-0.0614091);
}

double TMVAClassification_TMlp_ANN::synapse0x5bee420() {
   return (neuron0x6077dc0()*-0.124225);
}

double TMVAClassification_TMlp_ANN::synapse0x5bee460() {
   return (neuron0x597c140()*0.143232);
}

double TMVAClassification_TMlp_ANN::synapse0x5bee4a0() {
   return (neuron0x597c480()*-0.652814);
}

double TMVAClassification_TMlp_ANN::synapse0x5bee4e0() {
   return (neuron0x55c7800()*0.589993);
}

double TMVAClassification_TMlp_ANN::synapse0x5bee520() {
   return (neuron0x55c7b40()*-0.149517);
}

double TMVAClassification_TMlp_ANN::synapse0x5bee560() {
   return (neuron0x7f7a090()*0.168306);
}

double TMVAClassification_TMlp_ANN::synapse0x5bee5a0() {
   return (neuron0x673e5e0()*0.113576);
}

double TMVAClassification_TMlp_ANN::synapse0x7887560() {
   return (neuron0x6078290()*0.331969);
}

double TMVAClassification_TMlp_ANN::synapse0x5bee0d0() {
   return (neuron0x6078540()*0.111174);
}

double TMVAClassification_TMlp_ANN::synapse0x5bee110() {
   return (neuron0x63d6190()*0.564271);
}

double TMVAClassification_TMlp_ANN::synapse0x5bee150() {
   return (neuron0x63d64d0()*0.161448);
}

double TMVAClassification_TMlp_ANN::synapse0x5bee190() {
   return (neuron0x6251640()*-0.409662);
}

double TMVAClassification_TMlp_ANN::synapse0x729a710() {
   return (neuron0x46213e0()*-0.0714108);
}

double TMVAClassification_TMlp_ANN::synapse0x729a750() {
   return (neuron0x4621720()*0.300202);
}

double TMVAClassification_TMlp_ANN::synapse0x729a790() {
   return (neuron0x54fbed0()*-0.444057);
}

double TMVAClassification_TMlp_ANN::synapse0x729a7d0() {
   return (neuron0x7376fc0()*0.163216);
}

double TMVAClassification_TMlp_ANN::synapse0x729a810() {
   return (neuron0x7377300()*-0.476211);
}

double TMVAClassification_TMlp_ANN::synapse0x729a850() {
   return (neuron0x6a82e50()*0.0350032);
}

double TMVAClassification_TMlp_ANN::synapse0x729a890() {
   return (neuron0x6636ca0()*0.417106);
}

double TMVAClassification_TMlp_ANN::synapse0x729a8d0() {
   return (neuron0x6636fe0()*-0.0128278);
}

double TMVAClassification_TMlp_ANN::synapse0x729a910() {
   return (neuron0x51a0a30()*-0.326808);
}

double TMVAClassification_TMlp_ANN::synapse0x729a950() {
   return (neuron0x4d1fad0()*0.123856);
}

double TMVAClassification_TMlp_ANN::synapse0x729a990() {
   return (neuron0x4d1fe10()*0.54016);
}

double TMVAClassification_TMlp_ANN::synapse0x78873b0() {
   return (neuron0x4c00f40()*-0.563535);
}

double TMVAClassification_TMlp_ANN::synapse0x78873f0() {
   return (neuron0x657be70()*-0.478347);
}

double TMVAClassification_TMlp_ANN::synapse0x729aae0() {
   return (neuron0x7ec13f0()*0.229966);
}

double TMVAClassification_TMlp_ANN::synapse0x729ab20() {
   return (neuron0x7ec1730()*0.25422);
}

double TMVAClassification_TMlp_ANN::synapse0x729ab60() {
   return (neuron0x6c315b0()*0.116248);
}

double TMVAClassification_TMlp_ANN::synapse0x729aba0() {
   return (neuron0x6c318f0()*-0.125982);
}

double TMVAClassification_TMlp_ANN::synapse0x729abe0() {
   return (neuron0x638c0d0()*0.20689);
}

double TMVAClassification_TMlp_ANN::synapse0x729ac20() {
   return (neuron0x60b21d0()*-0.431169);
}

double TMVAClassification_TMlp_ANN::synapse0x729ac60() {
   return (neuron0x60b2510()*-0.176271);
}

double TMVAClassification_TMlp_ANN::synapse0x79caad0() {
   return (neuron0x4eb4da0()*-0.203727);
}

double TMVAClassification_TMlp_ANN::synapse0x79cab10() {
   return (neuron0x4eb50e0()*0.0919878);
}

double TMVAClassification_TMlp_ANN::synapse0x79cab50() {
   return (neuron0x6077dc0()*-0.298352);
}

double TMVAClassification_TMlp_ANN::synapse0x79cab90() {
   return (neuron0x597c140()*-0.500043);
}

double TMVAClassification_TMlp_ANN::synapse0x79cabd0() {
   return (neuron0x597c480()*-0.277746);
}

double TMVAClassification_TMlp_ANN::synapse0x79cac10() {
   return (neuron0x55c7800()*0.601836);
}

double TMVAClassification_TMlp_ANN::synapse0x79cac50() {
   return (neuron0x55c7b40()*0.105733);
}

double TMVAClassification_TMlp_ANN::synapse0x729a9d0() {
   return (neuron0x7f7a090()*0.465173);
}

double TMVAClassification_TMlp_ANN::synapse0x729aa10() {
   return (neuron0x673e5e0()*0.336201);
}

double TMVAClassification_TMlp_ANN::synapse0x78f6890() {
   return (neuron0x6078290()*0.195009);
}

double TMVAClassification_TMlp_ANN::synapse0x78f68d0() {
   return (neuron0x6078540()*0.45459);
}

double TMVAClassification_TMlp_ANN::synapse0x78f6910() {
   return (neuron0x63d6190()*0.229798);
}

double TMVAClassification_TMlp_ANN::synapse0x78f6950() {
   return (neuron0x63d64d0()*0.191894);
}

double TMVAClassification_TMlp_ANN::synapse0x78f6990() {
   return (neuron0x6251640()*0.801747);
}

double TMVAClassification_TMlp_ANN::synapse0x78f69d0() {
   return (neuron0x46213e0()*-0.0484706);
}

double TMVAClassification_TMlp_ANN::synapse0x78f6a10() {
   return (neuron0x4621720()*-0.0197433);
}

double TMVAClassification_TMlp_ANN::synapse0x78f6a50() {
   return (neuron0x54fbed0()*-0.324596);
}

double TMVAClassification_TMlp_ANN::synapse0x78f6a90() {
   return (neuron0x7376fc0()*0.182818);
}

double TMVAClassification_TMlp_ANN::synapse0x78f6ad0() {
   return (neuron0x7377300()*0.433241);
}

double TMVAClassification_TMlp_ANN::synapse0x78f6b10() {
   return (neuron0x6a82e50()*-0.322864);
}

double TMVAClassification_TMlp_ANN::synapse0x78f6b50() {
   return (neuron0x6636ca0()*0.586153);
}

double TMVAClassification_TMlp_ANN::synapse0x78f6b90() {
   return (neuron0x6636fe0()*-0.0384697);
}

double TMVAClassification_TMlp_ANN::synapse0x78f6bd0() {
   return (neuron0x51a0a30()*0.30118);
}

double TMVAClassification_TMlp_ANN::synapse0x78f6c10() {
   return (neuron0x4d1fad0()*0.632419);
}

double TMVAClassification_TMlp_ANN::synapse0x78f6c50() {
   return (neuron0x4d1fe10()*0.515624);
}

double TMVAClassification_TMlp_ANN::synapse0x79cb030() {
   return (neuron0x4c00f40()*-0.221819);
}

double TMVAClassification_TMlp_ANN::synapse0x729aa50() {
   return (neuron0x657be70()*-0.106201);
}

double TMVAClassification_TMlp_ANN::synapse0x729aa90() {
   return (neuron0x7ec13f0()*-0.366584);
}

double TMVAClassification_TMlp_ANN::synapse0x78f6c90() {
   return (neuron0x7ec1730()*0.0430961);
}

double TMVAClassification_TMlp_ANN::synapse0x78f6cd0() {
   return (neuron0x6c315b0()*0.502283);
}

double TMVAClassification_TMlp_ANN::synapse0x4d36e30() {
   return (neuron0x6c318f0()*0.0832432);
}

double TMVAClassification_TMlp_ANN::synapse0x4d36e70() {
   return (neuron0x638c0d0()*-0.106114);
}

double TMVAClassification_TMlp_ANN::synapse0x4d36eb0() {
   return (neuron0x60b21d0()*0.637949);
}

double TMVAClassification_TMlp_ANN::synapse0x4d36ef0() {
   return (neuron0x60b2510()*0.100353);
}

double TMVAClassification_TMlp_ANN::synapse0x4d36f30() {
   return (neuron0x4eb4da0()*-0.00880767);
}

double TMVAClassification_TMlp_ANN::synapse0x4d36f70() {
   return (neuron0x4eb50e0()*0.128201);
}

double TMVAClassification_TMlp_ANN::synapse0x4d36fb0() {
   return (neuron0x6077dc0()*-0.0357427);
}

double TMVAClassification_TMlp_ANN::synapse0x4d36ff0() {
   return (neuron0x597c140()*0.443862);
}

double TMVAClassification_TMlp_ANN::synapse0x4d37030() {
   return (neuron0x597c480()*0.490542);
}

double TMVAClassification_TMlp_ANN::synapse0x4d37070() {
   return (neuron0x55c7800()*0.503274);
}

double TMVAClassification_TMlp_ANN::synapse0x4d370b0() {
   return (neuron0x55c7b40()*-0.477364);
}

double TMVAClassification_TMlp_ANN::synapse0x4d36d20() {
   return (neuron0x7f7a090()*-0.494559);
}

double TMVAClassification_TMlp_ANN::synapse0x4d36d60() {
   return (neuron0x673e5e0()*0.254187);
}

double TMVAClassification_TMlp_ANN::synapse0x7519ca0() {
   return (neuron0x6078290()*-0.21387);
}

double TMVAClassification_TMlp_ANN::synapse0x7519ce0() {
   return (neuron0x6078540()*0.0628141);
}

double TMVAClassification_TMlp_ANN::synapse0x7519d20() {
   return (neuron0x63d6190()*-0.571593);
}

double TMVAClassification_TMlp_ANN::synapse0x7519d60() {
   return (neuron0x63d64d0()*0.441413);
}

double TMVAClassification_TMlp_ANN::synapse0x7519da0() {
   return (neuron0x6251640()*-0.208825);
}

double TMVAClassification_TMlp_ANN::synapse0x7519de0() {
   return (neuron0x46213e0()*-0.048466);
}

double TMVAClassification_TMlp_ANN::synapse0x7519e20() {
   return (neuron0x4621720()*-0.738312);
}

double TMVAClassification_TMlp_ANN::synapse0x7519e60() {
   return (neuron0x54fbed0()*0.00675715);
}

double TMVAClassification_TMlp_ANN::synapse0x7519ea0() {
   return (neuron0x7376fc0()*0.609203);
}

double TMVAClassification_TMlp_ANN::synapse0x7519ee0() {
   return (neuron0x7377300()*0.0910121);
}

double TMVAClassification_TMlp_ANN::synapse0x4d37280() {
   return (neuron0x6a82e50()*0.273523);
}

double TMVAClassification_TMlp_ANN::synapse0x72af600() {
   return (neuron0x6636ca0()*-0.123252);
}

double TMVAClassification_TMlp_ANN::synapse0x72af640() {
   return (neuron0x6636fe0()*-0.0222662);
}

double TMVAClassification_TMlp_ANN::synapse0x72af680() {
   return (neuron0x51a0a30()*-0.212585);
}

double TMVAClassification_TMlp_ANN::synapse0x72af6c0() {
   return (neuron0x4d1fad0()*-0.805382);
}

double TMVAClassification_TMlp_ANN::synapse0x72af700() {
   return (neuron0x4d1fe10()*-0.411577);
}

double TMVAClassification_TMlp_ANN::synapse0x4d36da0() {
   return (neuron0x4c00f40()*0.918238);
}

double TMVAClassification_TMlp_ANN::synapse0x4d36de0() {
   return (neuron0x657be70()*0.199531);
}

double TMVAClassification_TMlp_ANN::synapse0x72af850() {
   return (neuron0x7ec13f0()*-0.471729);
}

double TMVAClassification_TMlp_ANN::synapse0x72af890() {
   return (neuron0x7ec1730()*0.165866);
}

double TMVAClassification_TMlp_ANN::synapse0x72af8d0() {
   return (neuron0x6c315b0()*0.670033);
}

double TMVAClassification_TMlp_ANN::synapse0x72af910() {
   return (neuron0x6c318f0()*0.568637);
}

double TMVAClassification_TMlp_ANN::synapse0x72af950() {
   return (neuron0x638c0d0()*0.0700533);
}

double TMVAClassification_TMlp_ANN::synapse0x72af990() {
   return (neuron0x60b21d0()*-0.0857697);
}

double TMVAClassification_TMlp_ANN::synapse0x72af9d0() {
   return (neuron0x60b2510()*-0.302581);
}

double TMVAClassification_TMlp_ANN::synapse0x72afa10() {
   return (neuron0x4eb4da0()*-0.726749);
}

double TMVAClassification_TMlp_ANN::synapse0x72afa50() {
   return (neuron0x4eb50e0()*0.291449);
}

double TMVAClassification_TMlp_ANN::synapse0x72afa90() {
   return (neuron0x6077dc0()*0.244368);
}

double TMVAClassification_TMlp_ANN::synapse0x72afad0() {
   return (neuron0x597c140()*0.569417);
}

double TMVAClassification_TMlp_ANN::synapse0x72afb10() {
   return (neuron0x597c480()*0.280494);
}

double TMVAClassification_TMlp_ANN::synapse0x72afb50() {
   return (neuron0x55c7800()*-0.425598);
}

double TMVAClassification_TMlp_ANN::synapse0x7c7c960() {
   return (neuron0x55c7b40()*0.296285);
}

double TMVAClassification_TMlp_ANN::synapse0x72af740() {
   return (neuron0x7f7a090()*-0.072485);
}

double TMVAClassification_TMlp_ANN::synapse0x72af780() {
   return (neuron0x673e5e0()*-0.665995);
}

double TMVAClassification_TMlp_ANN::synapse0x7c7ce60() {
   return (neuron0x6078290()*0.331093);
}

double TMVAClassification_TMlp_ANN::synapse0x7c7cea0() {
   return (neuron0x6078540()*-0.0992712);
}

double TMVAClassification_TMlp_ANN::synapse0x7c7cee0() {
   return (neuron0x63d6190()*0.426731);
}

double TMVAClassification_TMlp_ANN::synapse0x7957230() {
   return (neuron0x63d64d0()*0.115743);
}

double TMVAClassification_TMlp_ANN::synapse0x7957270() {
   return (neuron0x6251640()*0.149862);
}

double TMVAClassification_TMlp_ANN::synapse0x79572b0() {
   return (neuron0x46213e0()*0.0791576);
}

double TMVAClassification_TMlp_ANN::synapse0x79572f0() {
   return (neuron0x4621720()*-0.391894);
}

double TMVAClassification_TMlp_ANN::synapse0x7957330() {
   return (neuron0x54fbed0()*-0.294168);
}

double TMVAClassification_TMlp_ANN::synapse0x7957370() {
   return (neuron0x7376fc0()*0.574286);
}

double TMVAClassification_TMlp_ANN::synapse0x79573b0() {
   return (neuron0x7377300()*0.447675);
}

double TMVAClassification_TMlp_ANN::synapse0x79573f0() {
   return (neuron0x6a82e50()*0.830445);
}

double TMVAClassification_TMlp_ANN::synapse0x7957430() {
   return (neuron0x6636ca0()*0.124355);
}

double TMVAClassification_TMlp_ANN::synapse0x7957470() {
   return (neuron0x6636fe0()*-0.0414608);
}

double TMVAClassification_TMlp_ANN::synapse0x79574b0() {
   return (neuron0x51a0a30()*-0.24563);
}

double TMVAClassification_TMlp_ANN::synapse0x79574f0() {
   return (neuron0x4d1fad0()*-0.205787);
}

double TMVAClassification_TMlp_ANN::synapse0x7957530() {
   return (neuron0x4d1fe10()*0.375272);
}

double TMVAClassification_TMlp_ANN::synapse0x72af7c0() {
   return (neuron0x4c00f40()*0.00503192);
}

double TMVAClassification_TMlp_ANN::synapse0x72af800() {
   return (neuron0x657be70()*0.0354121);
}

double TMVAClassification_TMlp_ANN::synapse0x7957680() {
   return (neuron0x7ec13f0()*-0.715603);
}

double TMVAClassification_TMlp_ANN::synapse0x79576c0() {
   return (neuron0x7ec1730()*-0.00218513);
}

double TMVAClassification_TMlp_ANN::synapse0x7957700() {
   return (neuron0x6c315b0()*-0.745715);
}

double TMVAClassification_TMlp_ANN::synapse0x7957740() {
   return (neuron0x6c318f0()*-0.355252);
}

double TMVAClassification_TMlp_ANN::synapse0x7957780() {
   return (neuron0x638c0d0()*0.323056);
}

double TMVAClassification_TMlp_ANN::synapse0x638eee0() {
   return (neuron0x60b21d0()*-0.228328);
}

double TMVAClassification_TMlp_ANN::synapse0x638ef20() {
   return (neuron0x60b2510()*-0.242853);
}

double TMVAClassification_TMlp_ANN::synapse0x638ef60() {
   return (neuron0x4eb4da0()*0.430252);
}

double TMVAClassification_TMlp_ANN::synapse0x638efa0() {
   return (neuron0x4eb50e0()*0.503494);
}

double TMVAClassification_TMlp_ANN::synapse0x638efe0() {
   return (neuron0x6077dc0()*-0.408173);
}

double TMVAClassification_TMlp_ANN::synapse0x638f020() {
   return (neuron0x597c140()*-0.935785);
}

double TMVAClassification_TMlp_ANN::synapse0x638f060() {
   return (neuron0x597c480()*-0.193243);
}

double TMVAClassification_TMlp_ANN::synapse0x638f0a0() {
   return (neuron0x55c7800()*0.0812231);
}

double TMVAClassification_TMlp_ANN::synapse0x638f0e0() {
   return (neuron0x55c7b40()*0.128921);
}

double TMVAClassification_TMlp_ANN::synapse0x7957570() {
   return (neuron0x7f7a090()*-0.0520147);
}

double TMVAClassification_TMlp_ANN::synapse0x79575b0() {
   return (neuron0x673e5e0()*0.427064);
}

double TMVAClassification_TMlp_ANN::synapse0x5752170() {
   return (neuron0x6078290()*-0.0454463);
}

double TMVAClassification_TMlp_ANN::synapse0x57521b0() {
   return (neuron0x6078540()*0.103562);
}

double TMVAClassification_TMlp_ANN::synapse0x57521f0() {
   return (neuron0x63d6190()*-0.443461);
}

double TMVAClassification_TMlp_ANN::synapse0x5752230() {
   return (neuron0x63d64d0()*0.557565);
}

double TMVAClassification_TMlp_ANN::synapse0x5752270() {
   return (neuron0x6251640()*-0.169935);
}

double TMVAClassification_TMlp_ANN::synapse0x57522b0() {
   return (neuron0x46213e0()*0.276177);
}

double TMVAClassification_TMlp_ANN::synapse0x57522f0() {
   return (neuron0x4621720()*-0.393438);
}

double TMVAClassification_TMlp_ANN::synapse0x5752330() {
   return (neuron0x54fbed0()*-0.645535);
}

double TMVAClassification_TMlp_ANN::synapse0x5752370() {
   return (neuron0x7376fc0()*-0.500752);
}

double TMVAClassification_TMlp_ANN::synapse0x57523b0() {
   return (neuron0x7377300()*-0.107337);
}

double TMVAClassification_TMlp_ANN::synapse0x57523f0() {
   return (neuron0x6a82e50()*-0.431734);
}

double TMVAClassification_TMlp_ANN::synapse0x5752430() {
   return (neuron0x6636ca0()*0.176641);
}

double TMVAClassification_TMlp_ANN::synapse0x638f330() {
   return (neuron0x6636fe0()*0.065872);
}

double TMVAClassification_TMlp_ANN::synapse0x638f370() {
   return (neuron0x51a0a30()*0.128983);
}

double TMVAClassification_TMlp_ANN::synapse0x638f3b0() {
   return (neuron0x4d1fad0()*-0.149246);
}

double TMVAClassification_TMlp_ANN::synapse0x638f3f0() {
   return (neuron0x4d1fe10()*0.118939);
}

double TMVAClassification_TMlp_ANN::synapse0x638f430() {
   return (neuron0x4c00f40()*0.464121);
}

double TMVAClassification_TMlp_ANN::synapse0x79575f0() {
   return (neuron0x657be70()*0.024104);
}

double TMVAClassification_TMlp_ANN::synapse0x7957630() {
   return (neuron0x7ec13f0()*0.166241);
}

double TMVAClassification_TMlp_ANN::synapse0x4f17030() {
   return (neuron0x7ec1730()*0.448276);
}

double TMVAClassification_TMlp_ANN::synapse0x4f17070() {
   return (neuron0x6c315b0()*-0.262602);
}

double TMVAClassification_TMlp_ANN::synapse0x4f170b0() {
   return (neuron0x6c318f0()*-0.658894);
}

double TMVAClassification_TMlp_ANN::synapse0x4f170f0() {
   return (neuron0x638c0d0()*-0.0618282);
}

double TMVAClassification_TMlp_ANN::synapse0x4f17130() {
   return (neuron0x60b21d0()*0.277841);
}

double TMVAClassification_TMlp_ANN::synapse0x4f17170() {
   return (neuron0x60b2510()*-0.132329);
}

double TMVAClassification_TMlp_ANN::synapse0x4f171b0() {
   return (neuron0x4eb4da0()*0.223548);
}

double TMVAClassification_TMlp_ANN::synapse0x4f171f0() {
   return (neuron0x4eb50e0()*0.231776);
}

double TMVAClassification_TMlp_ANN::synapse0x4f17230() {
   return (neuron0x6077dc0()*0.101033);
}

double TMVAClassification_TMlp_ANN::synapse0x4f17270() {
   return (neuron0x597c140()*-0.148382);
}

double TMVAClassification_TMlp_ANN::synapse0x4f172b0() {
   return (neuron0x597c480()*0.120447);
}

double TMVAClassification_TMlp_ANN::synapse0x4f172f0() {
   return (neuron0x55c7800()*1.06899);
}

double TMVAClassification_TMlp_ANN::synapse0x4f17330() {
   return (neuron0x55c7b40()*0.500968);
}

double TMVAClassification_TMlp_ANN::synapse0x4f16f20() {
   return (neuron0x7f7a090()*0.0395088);
}

double TMVAClassification_TMlp_ANN::synapse0x4f16f60() {
   return (neuron0x673e5e0()*0.251272);
}

double TMVAClassification_TMlp_ANN::synapse0x7da6720() {
   return (neuron0x6078290()*0.182861);
}

double TMVAClassification_TMlp_ANN::synapse0x7da6760() {
   return (neuron0x6078540()*0.885433);
}

double TMVAClassification_TMlp_ANN::synapse0x7da67a0() {
   return (neuron0x63d6190()*-0.480881);
}

double TMVAClassification_TMlp_ANN::synapse0x7da67e0() {
   return (neuron0x63d64d0()*0.0220756);
}

double TMVAClassification_TMlp_ANN::synapse0x4f17370() {
   return (neuron0x6251640()*0.427879);
}

double TMVAClassification_TMlp_ANN::synapse0x4f173b0() {
   return (neuron0x46213e0()*-0.511348);
}

double TMVAClassification_TMlp_ANN::synapse0x4f173f0() {
   return (neuron0x4621720()*-0.255109);
}

double TMVAClassification_TMlp_ANN::synapse0x4f17430() {
   return (neuron0x54fbed0()*0.415212);
}

double TMVAClassification_TMlp_ANN::synapse0x4f17470() {
   return (neuron0x7376fc0()*1.33839);
}

double TMVAClassification_TMlp_ANN::synapse0x73df960() {
   return (neuron0x7377300()*-0.523009);
}

double TMVAClassification_TMlp_ANN::synapse0x73df9a0() {
   return (neuron0x6a82e50()*0.210734);
}

double TMVAClassification_TMlp_ANN::synapse0x73df9e0() {
   return (neuron0x6636ca0()*0.0312869);
}

double TMVAClassification_TMlp_ANN::synapse0x73dfa20() {
   return (neuron0x6636fe0()*1.14454);
}

double TMVAClassification_TMlp_ANN::synapse0x73dfa60() {
   return (neuron0x51a0a30()*0.203341);
}

double TMVAClassification_TMlp_ANN::synapse0x73dfaa0() {
   return (neuron0x4d1fad0()*-0.0436059);
}

double TMVAClassification_TMlp_ANN::synapse0x73dfae0() {
   return (neuron0x4d1fe10()*-0.777956);
}

double TMVAClassification_TMlp_ANN::synapse0x4f16fa0() {
   return (neuron0x4c00f40()*0.39891);
}

double TMVAClassification_TMlp_ANN::synapse0x4f16fe0() {
   return (neuron0x657be70()*-0.220034);
}

double TMVAClassification_TMlp_ANN::synapse0x73dfc30() {
   return (neuron0x7ec13f0()*0.289787);
}

double TMVAClassification_TMlp_ANN::synapse0x73dfc70() {
   return (neuron0x7ec1730()*-0.616046);
}

double TMVAClassification_TMlp_ANN::synapse0x73dfcb0() {
   return (neuron0x6c315b0()*0.0387418);
}

double TMVAClassification_TMlp_ANN::synapse0x73dfcf0() {
   return (neuron0x6c318f0()*0.177706);
}

double TMVAClassification_TMlp_ANN::synapse0x73dfd30() {
   return (neuron0x638c0d0()*0.479429);
}

double TMVAClassification_TMlp_ANN::synapse0x73dfd70() {
   return (neuron0x60b21d0()*0.424753);
}

double TMVAClassification_TMlp_ANN::synapse0x73dfdb0() {
   return (neuron0x60b2510()*0.605458);
}

double TMVAClassification_TMlp_ANN::synapse0x73dfdf0() {
   return (neuron0x4eb4da0()*-0.180965);
}

double TMVAClassification_TMlp_ANN::synapse0x73dfe30() {
   return (neuron0x4eb50e0()*1.2526);
}

double TMVAClassification_TMlp_ANN::synapse0x73dfe70() {
   return (neuron0x6077dc0()*-0.667563);
}

double TMVAClassification_TMlp_ANN::synapse0x73dfeb0() {
   return (neuron0x597c140()*0.143346);
}

double TMVAClassification_TMlp_ANN::synapse0x6e1ff20() {
   return (neuron0x597c480()*0.573672);
}

double TMVAClassification_TMlp_ANN::synapse0x6e1ff60() {
   return (neuron0x55c7800()*0.518515);
}

double TMVAClassification_TMlp_ANN::synapse0x6e1ffa0() {
   return (neuron0x55c7b40()*-2.62298);
}

double TMVAClassification_TMlp_ANN::synapse0x73dfb20() {
   return (neuron0x7f7a090()*-0.352547);
}

double TMVAClassification_TMlp_ANN::synapse0x73dfb60() {
   return (neuron0x673e5e0()*1.35345);
}

double TMVAClassification_TMlp_ANN::synapse0x6e204a0() {
   return (neuron0x6078290()*-0.0929096);
}

double TMVAClassification_TMlp_ANN::synapse0x6220920() {
   return (neuron0x6078540()*-0.532972);
}

double TMVAClassification_TMlp_ANN::synapse0x6220960() {
   return (neuron0x63d6190()*-0.671859);
}

double TMVAClassification_TMlp_ANN::synapse0x62209a0() {
   return (neuron0x63d64d0()*-0.193931);
}

double TMVAClassification_TMlp_ANN::synapse0x62209e0() {
   return (neuron0x6251640()*0.177595);
}

double TMVAClassification_TMlp_ANN::synapse0x6220a20() {
   return (neuron0x46213e0()*0.0743617);
}

double TMVAClassification_TMlp_ANN::synapse0x6220a60() {
   return (neuron0x4621720()*-0.173526);
}

double TMVAClassification_TMlp_ANN::synapse0x6220aa0() {
   return (neuron0x54fbed0()*-0.326231);
}

double TMVAClassification_TMlp_ANN::synapse0x6220ae0() {
   return (neuron0x7376fc0()*-0.673761);
}

double TMVAClassification_TMlp_ANN::synapse0x6220b20() {
   return (neuron0x7377300()*-0.217805);
}

double TMVAClassification_TMlp_ANN::synapse0x6220b60() {
   return (neuron0x6a82e50()*0.702835);
}

double TMVAClassification_TMlp_ANN::synapse0x6220ba0() {
   return (neuron0x6636ca0()*-0.0364614);
}

double TMVAClassification_TMlp_ANN::synapse0x6220be0() {
   return (neuron0x6636fe0()*0.31533);
}

double TMVAClassification_TMlp_ANN::synapse0x6220c20() {
   return (neuron0x51a0a30()*-0.0752184);
}

double TMVAClassification_TMlp_ANN::synapse0x6220c60() {
   return (neuron0x4d1fad0()*0.57739);
}

double TMVAClassification_TMlp_ANN::synapse0x6220ca0() {
   return (neuron0x4d1fe10()*-0.316065);
}

double TMVAClassification_TMlp_ANN::synapse0x73dfba0() {
   return (neuron0x4c00f40()*1.10311);
}

double TMVAClassification_TMlp_ANN::synapse0x73dfbe0() {
   return (neuron0x657be70()*-0.334919);
}

double TMVAClassification_TMlp_ANN::synapse0x6220df0() {
   return (neuron0x7ec13f0()*0.100338);
}

double TMVAClassification_TMlp_ANN::synapse0x6220e30() {
   return (neuron0x7ec1730()*0.025216);
}

double TMVAClassification_TMlp_ANN::synapse0x6220e70() {
   return (neuron0x6c315b0()*-0.430329);
}

double TMVAClassification_TMlp_ANN::synapse0x5e99310() {
   return (neuron0x6c318f0()*-0.685813);
}

double TMVAClassification_TMlp_ANN::synapse0x5e99350() {
   return (neuron0x638c0d0()*-0.220006);
}

double TMVAClassification_TMlp_ANN::synapse0x5e99390() {
   return (neuron0x60b21d0()*0.211502);
}

double TMVAClassification_TMlp_ANN::synapse0x5e993d0() {
   return (neuron0x60b2510()*-0.10418);
}

double TMVAClassification_TMlp_ANN::synapse0x5e99410() {
   return (neuron0x4eb4da0()*0.159636);
}

double TMVAClassification_TMlp_ANN::synapse0x5e99450() {
   return (neuron0x4eb50e0()*0.684993);
}

double TMVAClassification_TMlp_ANN::synapse0x5e99490() {
   return (neuron0x6077dc0()*-0.0439046);
}

double TMVAClassification_TMlp_ANN::synapse0x5e994d0() {
   return (neuron0x597c140()*-0.0501858);
}

double TMVAClassification_TMlp_ANN::synapse0x5e99510() {
   return (neuron0x597c480()*0.373104);
}

double TMVAClassification_TMlp_ANN::synapse0x5e99550() {
   return (neuron0x55c7800()*0.567988);
}

double TMVAClassification_TMlp_ANN::synapse0x5e99590() {
   return (neuron0x55c7b40()*-0.578766);
}

double TMVAClassification_TMlp_ANN::synapse0x5e997e0() {
   return (neuron0x7f7a090()*0.0378762);
}

double TMVAClassification_TMlp_ANN::synapse0x5e99820() {
   return (neuron0x673e5e0()*0.313975);
}

double TMVAClassification_TMlp_ANN::synapse0x5e99860() {
   return (neuron0x6078290()*0.376371);
}

double TMVAClassification_TMlp_ANN::synapse0x6220ce0() {
   return (neuron0x6078540()*0.0587148);
}

double TMVAClassification_TMlp_ANN::synapse0x6220d20() {
   return (neuron0x63d6190()*-0.691928);
}

double TMVAClassification_TMlp_ANN::synapse0x6220d60() {
   return (neuron0x63d64d0()*-0.399599);
}

double TMVAClassification_TMlp_ANN::synapse0x6220da0() {
   return (neuron0x6251640()*-0.882617);
}

double TMVAClassification_TMlp_ANN::synapse0x690d990() {
   return (neuron0x46213e0()*-0.0746002);
}

double TMVAClassification_TMlp_ANN::synapse0x690d9d0() {
   return (neuron0x4621720()*0.529145);
}

double TMVAClassification_TMlp_ANN::synapse0x690da10() {
   return (neuron0x54fbed0()*0.610528);
}

double TMVAClassification_TMlp_ANN::synapse0x690da50() {
   return (neuron0x7376fc0()*0.704368);
}

double TMVAClassification_TMlp_ANN::synapse0x690da90() {
   return (neuron0x7377300()*-0.919725);
}

double TMVAClassification_TMlp_ANN::synapse0x690dad0() {
   return (neuron0x6a82e50()*0.690319);
}

double TMVAClassification_TMlp_ANN::synapse0x673e3d0() {
   return (neuron0x6636ca0()*0.21412);
}

double TMVAClassification_TMlp_ANN::synapse0x673e410() {
   return (neuron0x6636fe0()*-0.491772);
}

double TMVAClassification_TMlp_ANN::synapse0x673e450() {
   return (neuron0x51a0a30()*0.767889);
}

double TMVAClassification_TMlp_ANN::synapse0x673e490() {
   return (neuron0x4d1fad0()*1.05522);
}

double TMVAClassification_TMlp_ANN::synapse0x673e4d0() {
   return (neuron0x4d1fe10()*-0.682033);
}

double TMVAClassification_TMlp_ANN::synapse0x72299b0() {
   return (neuron0x4c00f40()*0.0733487);
}

double TMVAClassification_TMlp_ANN::synapse0x72299f0() {
   return (neuron0x657be70()*-0.468498);
}

double TMVAClassification_TMlp_ANN::synapse0x673e510() {
   return (neuron0x7ec13f0()*1.03298);
}

double TMVAClassification_TMlp_ANN::synapse0x673e550() {
   return (neuron0x7ec1730()*-0.0561451);
}

double TMVAClassification_TMlp_ANN::synapse0x673e590() {
   return (neuron0x6c315b0()*-0.78445);
}

double TMVAClassification_TMlp_ANN::synapse0x7229c70() {
   return (neuron0x6c318f0()*-0.0389927);
}

double TMVAClassification_TMlp_ANN::synapse0x7229cb0() {
   return (neuron0x638c0d0()*-0.536614);
}

double TMVAClassification_TMlp_ANN::synapse0x7229cf0() {
   return (neuron0x60b21d0()*-0.875433);
}

double TMVAClassification_TMlp_ANN::synapse0x7229d30() {
   return (neuron0x60b2510()*-0.348277);
}

double TMVAClassification_TMlp_ANN::synapse0x7229d70() {
   return (neuron0x4eb4da0()*-0.235984);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe52a0() {
   return (neuron0x4eb50e0()*-0.190812);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe52e0() {
   return (neuron0x6077dc0()*-0.65563);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe5320() {
   return (neuron0x597c140()*-0.624011);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe5360() {
   return (neuron0x597c480()*-0.392511);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe53a0() {
   return (neuron0x55c7800()*-1.15137);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe53e0() {
   return (neuron0x55c7b40()*1.84343);
}

double TMVAClassification_TMlp_ANN::synapse0x7229b60() {
   return (neuron0x7f7a090()*0.229721);
}

double TMVAClassification_TMlp_ANN::synapse0x7229ba0() {
   return (neuron0x673e5e0()*-1.0912);
}

double TMVAClassification_TMlp_ANN::synapse0x5c98940() {
   return (neuron0x6078290()*0.150963);
}

double TMVAClassification_TMlp_ANN::synapse0x4b24ff0() {
   return (neuron0x6078540()*0.285986);
}

double TMVAClassification_TMlp_ANN::synapse0x4b25030() {
   return (neuron0x63d6190()*-0.0646825);
}

double TMVAClassification_TMlp_ANN::synapse0x4b25070() {
   return (neuron0x63d64d0()*0.591714);
}

double TMVAClassification_TMlp_ANN::synapse0x4b250b0() {
   return (neuron0x6251640()*-0.365668);
}

double TMVAClassification_TMlp_ANN::synapse0x5c98da0() {
   return (neuron0x46213e0()*-1.05108);
}

double TMVAClassification_TMlp_ANN::synapse0x5c98de0() {
   return (neuron0x4621720()*-0.697566);
}

double TMVAClassification_TMlp_ANN::synapse0x5c98e20() {
   return (neuron0x54fbed0()*0.188945);
}

double TMVAClassification_TMlp_ANN::synapse0x7ec1da0() {
   return (neuron0x7376fc0()*0.316619);
}

double TMVAClassification_TMlp_ANN::synapse0x7ec1de0() {
   return (neuron0x7377300()*0.449095);
}

double TMVAClassification_TMlp_ANN::synapse0x7ec1e20() {
   return (neuron0x6a82e50()*1.4312);
}

double TMVAClassification_TMlp_ANN::synapse0x7ec1e60() {
   return (neuron0x6636ca0()*-0.168237);
}

double TMVAClassification_TMlp_ANN::synapse0x5101150() {
   return (neuron0x6636fe0()*0.543036);
}

double TMVAClassification_TMlp_ANN::synapse0x5101190() {
   return (neuron0x51a0a30()*-0.465442);
}

double TMVAClassification_TMlp_ANN::synapse0x51011d0() {
   return (neuron0x4d1fad0()*0.249668);
}

double TMVAClassification_TMlp_ANN::synapse0x5101210() {
   return (neuron0x4d1fe10()*-0.028822);
}

double TMVAClassification_TMlp_ANN::synapse0x7229be0() {
   return (neuron0x4c00f40()*-0.0907555);
}

double TMVAClassification_TMlp_ANN::synapse0x7229c20() {
   return (neuron0x657be70()*-0.778767);
}

double TMVAClassification_TMlp_ANN::synapse0x77836f0() {
   return (neuron0x7ec13f0()*0.768926);
}

double TMVAClassification_TMlp_ANN::synapse0x6a408a0() {
   return (neuron0x7ec1730()*0.58048);
}

double TMVAClassification_TMlp_ANN::synapse0x7783730() {
   return (neuron0x6c315b0()*-0.688303);
}

double TMVAClassification_TMlp_ANN::synapse0x653d8d0() {
   return (neuron0x6c318f0()*-0.907213);
}

double TMVAClassification_TMlp_ANN::synapse0x7783770() {
   return (neuron0x638c0d0()*0.880654);
}

double TMVAClassification_TMlp_ANN::synapse0x77837b0() {
   return (neuron0x60b21d0()*-0.0029903);
}

double TMVAClassification_TMlp_ANN::synapse0x653db20() {
   return (neuron0x60b2510()*0.32758);
}

double TMVAClassification_TMlp_ANN::synapse0x77837f0() {
   return (neuron0x4eb4da0()*0.41612);
}

double TMVAClassification_TMlp_ANN::synapse0x7783830() {
   return (neuron0x4eb50e0()*-0.216267);
}

double TMVAClassification_TMlp_ANN::synapse0x653dd70() {
   return (neuron0x6077dc0()*0.31652);
}

double TMVAClassification_TMlp_ANN::synapse0x653ddb0() {
   return (neuron0x597c140()*0.719684);
}

double TMVAClassification_TMlp_ANN::synapse0x6c76130() {
   return (neuron0x597c480()*0.631882);
}

double TMVAClassification_TMlp_ANN::synapse0x6f3cd60() {
   return (neuron0x55c7800()*0.38536);
}

double TMVAClassification_TMlp_ANN::synapse0x6f3cda0() {
   return (neuron0x55c7b40()*-0.0152432);
}

double TMVAClassification_TMlp_ANN::synapse0x6f3cde0() {
   return (neuron0x7f7a090()*-0.335053);
}

double TMVAClassification_TMlp_ANN::synapse0x6f3ce20() {
   return (neuron0x673e5e0()*-0.038272);
}

double TMVAClassification_TMlp_ANN::synapse0x7f2a080() {
   return (neuron0x6078290()*-0.438183);
}

double TMVAClassification_TMlp_ANN::synapse0x7f2a0c0() {
   return (neuron0x6078540()*-0.130077);
}

double TMVAClassification_TMlp_ANN::synapse0x4e1f470() {
   return (neuron0x63d6190()*-0.129688);
}

double TMVAClassification_TMlp_ANN::synapse0x4e1f4b0() {
   return (neuron0x63d64d0()*0.141646);
}

double TMVAClassification_TMlp_ANN::synapse0x6a40600() {
   return (neuron0x6251640()*-0.0971799);
}

double TMVAClassification_TMlp_ANN::synapse0x6a40640() {
   return (neuron0x46213e0()*-0.131665);
}

double TMVAClassification_TMlp_ANN::synapse0x6c76170() {
   return (neuron0x4621720()*0.203227);
}

double TMVAClassification_TMlp_ANN::synapse0x6c761b0() {
   return (neuron0x54fbed0()*0.364273);
}

double TMVAClassification_TMlp_ANN::synapse0x6c761f0() {
   return (neuron0x7376fc0()*0.39262);
}

double TMVAClassification_TMlp_ANN::synapse0x6c76230() {
   return (neuron0x7377300()*-0.134786);
}

double TMVAClassification_TMlp_ANN::synapse0x6c76270() {
   return (neuron0x6a82e50()*-0.332538);
}

double TMVAClassification_TMlp_ANN::synapse0x68d0c70() {
   return (neuron0x6636ca0()*0.573695);
}

double TMVAClassification_TMlp_ANN::synapse0x68d0cb0() {
   return (neuron0x6636fe0()*-0.0296264);
}

double TMVAClassification_TMlp_ANN::synapse0x68d0cf0() {
   return (neuron0x51a0a30()*-0.581702);
}

double TMVAClassification_TMlp_ANN::synapse0x68d0d30() {
   return (neuron0x4d1fad0()*-0.191724);
}

double TMVAClassification_TMlp_ANN::synapse0x68d0d70() {
   return (neuron0x4d1fe10()*0.334529);
}

double TMVAClassification_TMlp_ANN::synapse0x68d0db0() {
   return (neuron0x4c00f40()*-0.00820721);
}

double TMVAClassification_TMlp_ANN::synapse0x5de7160() {
   return (neuron0x657be70()*0.0810599);
}

double TMVAClassification_TMlp_ANN::synapse0x5de71a0() {
   return (neuron0x7ec13f0()*0.0195022);
}

double TMVAClassification_TMlp_ANN::synapse0x4e1f3e0() {
   return (neuron0x7ec1730()*-0.733704);
}

double TMVAClassification_TMlp_ANN::synapse0x4e1f420() {
   return (neuron0x6c315b0()*0.409675);
}

double TMVAClassification_TMlp_ANN::synapse0x520ae60() {
   return (neuron0x6c318f0()*0.131767);
}

double TMVAClassification_TMlp_ANN::synapse0x520aea0() {
   return (neuron0x638c0d0()*0.170048);
}

double TMVAClassification_TMlp_ANN::synapse0x520aee0() {
   return (neuron0x60b21d0()*0.202733);
}

double TMVAClassification_TMlp_ANN::synapse0x520af20() {
   return (neuron0x60b2510()*0.572005);
}

double TMVAClassification_TMlp_ANN::synapse0x520af60() {
   return (neuron0x4eb4da0()*0.0453056);
}

double TMVAClassification_TMlp_ANN::synapse0x520afa0() {
   return (neuron0x4eb50e0()*0.561579);
}

double TMVAClassification_TMlp_ANN::synapse0x55b1b90() {
   return (neuron0x6077dc0()*0.728708);
}

double TMVAClassification_TMlp_ANN::synapse0x55b1bd0() {
   return (neuron0x597c140()*0.181185);
}

double TMVAClassification_TMlp_ANN::synapse0x55b1c10() {
   return (neuron0x597c480()*-0.309296);
}

double TMVAClassification_TMlp_ANN::synapse0x55b1c50() {
   return (neuron0x55c7800()*0.724923);
}

double TMVAClassification_TMlp_ANN::synapse0x55b1c90() {
   return (neuron0x55c7b40()*0.0341999);
}

double TMVAClassification_TMlp_ANN::synapse0x55b1cd0() {
   return (neuron0x7f7a090()*0.129492);
}

double TMVAClassification_TMlp_ANN::synapse0x5de7050() {
   return (neuron0x673e5e0()*-0.0634023);
}

double TMVAClassification_TMlp_ANN::synapse0x5de7120() {
   return (neuron0x6078290()*-0.0647244);
}

double TMVAClassification_TMlp_ANN::synapse0x7cbd6c0() {
   return (neuron0x6078540()*-0.142904);
}

double TMVAClassification_TMlp_ANN::synapse0x7cbd700() {
   return (neuron0x63d6190()*-0.363713);
}

double TMVAClassification_TMlp_ANN::synapse0x4da12f0() {
   return (neuron0x63d64d0()*-0.537266);
}

double TMVAClassification_TMlp_ANN::synapse0x4da1330() {
   return (neuron0x6251640()*0.471159);
}

double TMVAClassification_TMlp_ANN::synapse0x4da1370() {
   return (neuron0x46213e0()*0.451896);
}

double TMVAClassification_TMlp_ANN::synapse0x4da13b0() {
   return (neuron0x4621720()*0.165096);
}

double TMVAClassification_TMlp_ANN::synapse0x4da13f0() {
   return (neuron0x54fbed0()*-0.128876);
}

double TMVAClassification_TMlp_ANN::synapse0x4da1430() {
   return (neuron0x7376fc0()*0.00144169);
}

double TMVAClassification_TMlp_ANN::synapse0x4a3a980() {
   return (neuron0x7377300()*-0.58608);
}

double TMVAClassification_TMlp_ANN::synapse0x4a3a9c0() {
   return (neuron0x6a82e50()*-0.271868);
}

double TMVAClassification_TMlp_ANN::synapse0x4a3aa00() {
   return (neuron0x6636ca0()*0.598891);
}

double TMVAClassification_TMlp_ANN::synapse0x4a3aa40() {
   return (neuron0x6636fe0()*0.677006);
}

double TMVAClassification_TMlp_ANN::synapse0x4a3aa80() {
   return (neuron0x51a0a30()*0.635278);
}

double TMVAClassification_TMlp_ANN::synapse0x4a3aac0() {
   return (neuron0x4d1fad0()*0.025147);
}

double TMVAClassification_TMlp_ANN::synapse0x6a408e0() {
   return (neuron0x4d1fe10()*-0.229293);
}

double TMVAClassification_TMlp_ANN::synapse0x6a40a30() {
   return (neuron0x4c00f40()*-0.409398);
}

double TMVAClassification_TMlp_ANN::synapse0x6a40a70() {
   return (neuron0x657be70()*-0.543203);
}

double TMVAClassification_TMlp_ANN::synapse0x5de7090() {
   return (neuron0x7ec13f0()*0.308939);
}

double TMVAClassification_TMlp_ANN::synapse0x5de70d0() {
   return (neuron0x7ec1730()*0.559438);
}

double TMVAClassification_TMlp_ANN::synapse0x7b8bfc0() {
   return (neuron0x6c315b0()*0.00543576);
}

double TMVAClassification_TMlp_ANN::synapse0x7b8c000() {
   return (neuron0x6c318f0()*0.261361);
}

double TMVAClassification_TMlp_ANN::synapse0x7b8c040() {
   return (neuron0x638c0d0()*0.230194);
}

double TMVAClassification_TMlp_ANN::synapse0x7b8c080() {
   return (neuron0x60b21d0()*-0.396123);
}

double TMVAClassification_TMlp_ANN::synapse0x7b8c0c0() {
   return (neuron0x60b2510()*-0.305113);
}

double TMVAClassification_TMlp_ANN::synapse0x7b8c100() {
   return (neuron0x4eb4da0()*-0.176712);
}

double TMVAClassification_TMlp_ANN::synapse0x7b8c140() {
   return (neuron0x4eb50e0()*-0.0420983);
}

double TMVAClassification_TMlp_ANN::synapse0x7b8c180() {
   return (neuron0x6077dc0()*0.384631);
}

double TMVAClassification_TMlp_ANN::synapse0x7b8c1c0() {
   return (neuron0x597c140()*0.293484);
}

double TMVAClassification_TMlp_ANN::synapse0x7b8c200() {
   return (neuron0x597c480()*0.395338);
}

double TMVAClassification_TMlp_ANN::synapse0x7b8c240() {
   return (neuron0x55c7800()*-0.833121);
}

double TMVAClassification_TMlp_ANN::synapse0x7b8c280() {
   return (neuron0x55c7b40()*-0.247365);
}

double TMVAClassification_TMlp_ANN::synapse0x7b8c4d0() {
   return (neuron0x7f7a090()*0.230359);
}

double TMVAClassification_TMlp_ANN::synapse0x7b8c510() {
   return (neuron0x673e5e0()*-0.524935);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddcf60() {
   return (neuron0x753f310()*-0.501638);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddcfa0() {
   return (neuron0x5b753e0()*0.355088);
}

double TMVAClassification_TMlp_ANN::synapse0x5b8f040() {
   return (neuron0x64be3a0()*0.161641);
}

double TMVAClassification_TMlp_ANN::synapse0x5b8f080() {
   return (neuron0x7ddcd40()*0.251509);
}

double TMVAClassification_TMlp_ANN::synapse0x6613a80() {
   return (neuron0x5b8ed90()*-0.223747);
}

double TMVAClassification_TMlp_ANN::synapse0x6613ac0() {
   return (neuron0x6613860()*-0.156007);
}

double TMVAClassification_TMlp_ANN::synapse0x5fa9d20() {
   return (neuron0x5fa9b00()*-0.0922528);
}

double TMVAClassification_TMlp_ANN::synapse0x5fa9d60() {
   return (neuron0x6e4f550()*-0.4628);
}

double TMVAClassification_TMlp_ANN::synapse0x6e4f770() {
   return (neuron0x768b210()*-0.206425);
}

double TMVAClassification_TMlp_ANN::synapse0x6e4f7b0() {
   return (neuron0x660fe00()*-0.351208);
}

double TMVAClassification_TMlp_ANN::synapse0x768b430() {
   return (neuron0x5dbd1d0()*-0.477607);
}

double TMVAClassification_TMlp_ANN::synapse0x768b470() {
   return (neuron0x7c6efd0()*0.255087);
}

double TMVAClassification_TMlp_ANN::synapse0x66100b0() {
   return (neuron0x624f870()*0.170005);
}

double TMVAClassification_TMlp_ANN::synapse0x66100f0() {
   return (neuron0x710cab0()*0.313626);
}

double TMVAClassification_TMlp_ANN::synapse0x5dbd480() {
   return (neuron0x67c49b0()*-0.415764);
}

double TMVAClassification_TMlp_ANN::synapse0x5dbd4c0() {
   return (neuron0x77723c0()*-0.344023);
}

double TMVAClassification_TMlp_ANN::synapse0x675c9a0() {
   return (neuron0x5796be0()*0.176564);
}

double TMVAClassification_TMlp_ANN::synapse0x675c9e0() {
   return (neuron0x68c4f20()*-0.19472);
}

double TMVAClassification_TMlp_ANN::synapse0x762b6b0() {
   return (neuron0x5fa3a60()*0.270757);
}

double TMVAClassification_TMlp_ANN::synapse0x762b6f0() {
   return (neuron0x58886c0()*-0.299088);
}

double TMVAClassification_TMlp_ANN::synapse0x710ccd0() {
   return (neuron0x6dcd6b0()*0.233955);
}

double TMVAClassification_TMlp_ANN::synapse0x710cd10() {
   return (neuron0x7c1a4f0()*-0.113657);
}

double TMVAClassification_TMlp_ANN::synapse0x67c4bd0() {
   return (neuron0x7f702c0()*-0.63355);
}

double TMVAClassification_TMlp_ANN::synapse0x67c4c10() {
   return (neuron0x7887220()*-0.147296);
}

double TMVAClassification_TMlp_ANN::synapse0x77725e0() {
   return (neuron0x79caea0()*-0.10831);
}

double TMVAClassification_TMlp_ANN::synapse0x7772620() {
   return (neuron0x4d370f0()*0.234013);
}

double TMVAClassification_TMlp_ANN::synapse0x657c090() {
   return (neuron0x7c7cbb0()*-0.473131);
}

double TMVAClassification_TMlp_ANN::synapse0x657c0d0() {
   return (neuron0x5751ec0()*0.0568192);
}

double TMVAClassification_TMlp_ANN::synapse0x597c360() {
   return (neuron0x7da6470()*0.433128);
}

double TMVAClassification_TMlp_ANN::synapse0x597c3a0() {
   return (neuron0x6e201f0()*0.31366);
}

double TMVAClassification_TMlp_ANN::synapse0x5fa3c80() {
   return (neuron0x7229820()*-0.419602);
}

double TMVAClassification_TMlp_ANN::synapse0x5fa3cc0() {
   return (neuron0x5fe5630()*-0.102418);
}

double TMVAClassification_TMlp_ANN::synapse0x58888e0() {
   return (neuron0x6e364e0()*-0.423765);
}

double TMVAClassification_TMlp_ANN::synapse0x5888920() {
   return (neuron0x70c3610()*-0.589718);
}

double TMVAClassification_TMlp_ANN::synapse0x78874d0() {
   return (neuron0x753f310()*-0.588499);
}

double TMVAClassification_TMlp_ANN::synapse0x7887510() {
   return (neuron0x5b753e0()*0.246562);
}

double TMVAClassification_TMlp_ANN::synapse0x78f6800() {
   return (neuron0x64be3a0()*-0.535276);
}

double TMVAClassification_TMlp_ANN::synapse0x78f6840() {
   return (neuron0x7ddcd40()*-0.411119);
}

double TMVAClassification_TMlp_ANN::synapse0x7519c10() {
   return (neuron0x5b8ed90()*-0.417529);
}

double TMVAClassification_TMlp_ANN::synapse0x7519c50() {
   return (neuron0x6613860()*0.0865717);
}

double TMVAClassification_TMlp_ANN::synapse0x7c7cdd0() {
   return (neuron0x5fa9b00()*0.163479);
}

double TMVAClassification_TMlp_ANN::synapse0x7c7ce10() {
   return (neuron0x6e4f550()*-0.244754);
}

double TMVAClassification_TMlp_ANN::synapse0x57520e0() {
   return (neuron0x768b210()*0.189074);
}

double TMVAClassification_TMlp_ANN::synapse0x5752120() {
   return (neuron0x660fe00()*0.0236008);
}

double TMVAClassification_TMlp_ANN::synapse0x7da6690() {
   return (neuron0x5dbd1d0()*0.0191944);
}

double TMVAClassification_TMlp_ANN::synapse0x7da66d0() {
   return (neuron0x7c6efd0()*-0.171349);
}

double TMVAClassification_TMlp_ANN::synapse0x6e20410() {
   return (neuron0x624f870()*0.235253);
}

double TMVAClassification_TMlp_ANN::synapse0x6e20450() {
   return (neuron0x710cab0()*-0.0758761);
}

double TMVAClassification_TMlp_ANN::synapse0x7229ad0() {
   return (neuron0x67c49b0()*-0.420928);
}

double TMVAClassification_TMlp_ANN::synapse0x7229b10() {
   return (neuron0x77723c0()*-0.340087);
}

double TMVAClassification_TMlp_ANN::synapse0x5c988b0() {
   return (neuron0x5796be0()*-0.570949);
}

double TMVAClassification_TMlp_ANN::synapse0x5c988f0() {
   return (neuron0x68c4f20()*-0.245791);
}

double TMVAClassification_TMlp_ANN::synapse0x7f29ff0() {
   return (neuron0x5fa3a60()*-0.227921);
}

double TMVAClassification_TMlp_ANN::synapse0x7f2a030() {
   return (neuron0x58886c0()*-0.464363);
}

double TMVAClassification_TMlp_ANN::synapse0x7cbd630() {
   return (neuron0x6dcd6b0()*-0.347085);
}

double TMVAClassification_TMlp_ANN::synapse0x7cbd670() {
   return (neuron0x7c1a4f0()*0.341606);
}

double TMVAClassification_TMlp_ANN::synapse0x5b75090() {
   return (neuron0x7f702c0()*-0.150311);
}

double TMVAClassification_TMlp_ANN::synapse0x5b750d0() {
   return (neuron0x7887220()*0.249125);
}

double TMVAClassification_TMlp_ANN::synapse0x6dcd8d0() {
   return (neuron0x79caea0()*-0.413895);
}

double TMVAClassification_TMlp_ANN::synapse0x6dcd910() {
   return (neuron0x4d370f0()*-0.277173);
}

double TMVAClassification_TMlp_ANN::synapse0x7b22ad0() {
   return (neuron0x7c7cbb0()*0.0313304);
}

double TMVAClassification_TMlp_ANN::synapse0x7b22b10() {
   return (neuron0x5751ec0()*-0.453019);
}

double TMVAClassification_TMlp_ANN::synapse0x7b22b50() {
   return (neuron0x7da6470()*-0.103219);
}

double TMVAClassification_TMlp_ANN::synapse0x7b22b90() {
   return (neuron0x6e201f0()*-0.116373);
}

double TMVAClassification_TMlp_ANN::synapse0x7b22bd0() {
   return (neuron0x7229820()*-0.0280842);
}

double TMVAClassification_TMlp_ANN::synapse0x7b22c10() {
   return (neuron0x5fe5630()*-0.293569);
}

double TMVAClassification_TMlp_ANN::synapse0x6a40920() {
   return (neuron0x6e364e0()*-0.0505939);
}

double TMVAClassification_TMlp_ANN::synapse0x6a40960() {
   return (neuron0x70c3610()*0.0401524);
}

double TMVAClassification_TMlp_ANN::synapse0x67988d0() {
   return (neuron0x753f310()*-0.152779);
}

double TMVAClassification_TMlp_ANN::synapse0x6798910() {
   return (neuron0x5b753e0()*-0.191892);
}

double TMVAClassification_TMlp_ANN::synapse0x7ab4870() {
   return (neuron0x64be3a0()*-0.251231);
}

double TMVAClassification_TMlp_ANN::synapse0x7ab48b0() {
   return (neuron0x7ddcd40()*0.128839);
}

double TMVAClassification_TMlp_ANN::synapse0x7ab48f0() {
   return (neuron0x5b8ed90()*0.0850269);
}

double TMVAClassification_TMlp_ANN::synapse0x7ab4930() {
   return (neuron0x6613860()*-0.424808);
}

double TMVAClassification_TMlp_ANN::synapse0x7ab4970() {
   return (neuron0x5fa9b00()*-0.31425);
}

double TMVAClassification_TMlp_ANN::synapse0x7ab49b0() {
   return (neuron0x6e4f550()*-0.632051);
}

double TMVAClassification_TMlp_ANN::synapse0x4e812a0() {
   return (neuron0x768b210()*0.24778);
}

double TMVAClassification_TMlp_ANN::synapse0x4e812e0() {
   return (neuron0x660fe00()*-0.392118);
}

double TMVAClassification_TMlp_ANN::synapse0x4e81320() {
   return (neuron0x5dbd1d0()*0.200477);
}

double TMVAClassification_TMlp_ANN::synapse0x4e81360() {
   return (neuron0x7c6efd0()*-0.0267904);
}

double TMVAClassification_TMlp_ANN::synapse0x4e813a0() {
   return (neuron0x624f870()*-0.189889);
}

double TMVAClassification_TMlp_ANN::synapse0x4e813e0() {
   return (neuron0x710cab0()*0.0266817);
}

double TMVAClassification_TMlp_ANN::synapse0x4c00bf0() {
   return (neuron0x67c49b0()*-0.507341);
}

double TMVAClassification_TMlp_ANN::synapse0x4c00c30() {
   return (neuron0x77723c0()*-0.132075);
}

double TMVAClassification_TMlp_ANN::synapse0x6a409a0() {
   return (neuron0x5796be0()*0.164339);
}

double TMVAClassification_TMlp_ANN::synapse0x6a409e0() {
   return (neuron0x68c4f20()*-0.361803);
}

double TMVAClassification_TMlp_ANN::synapse0x5396d70() {
   return (neuron0x5fa3a60()*-0.50983);
}

double TMVAClassification_TMlp_ANN::synapse0x5396db0() {
   return (neuron0x58886c0()*0.209875);
}

double TMVAClassification_TMlp_ANN::synapse0x5396df0() {
   return (neuron0x6dcd6b0()*-0.69507);
}

double TMVAClassification_TMlp_ANN::synapse0x5396e30() {
   return (neuron0x7c1a4f0()*-0.266083);
}

double TMVAClassification_TMlp_ANN::synapse0x5396e70() {
   return (neuron0x7f702c0()*-0.309345);
}

double TMVAClassification_TMlp_ANN::synapse0x5396eb0() {
   return (neuron0x7887220()*-0.0818859);
}

double TMVAClassification_TMlp_ANN::synapse0x4621dc0() {
   return (neuron0x79caea0()*0.126824);
}

double TMVAClassification_TMlp_ANN::synapse0x4621e00() {
   return (neuron0x4d370f0()*-0.140913);
}

double TMVAClassification_TMlp_ANN::synapse0x4621e40() {
   return (neuron0x7c7cbb0()*-0.474449);
}

double TMVAClassification_TMlp_ANN::synapse0x4621e80() {
   return (neuron0x5751ec0()*-0.353857);
}

double TMVAClassification_TMlp_ANN::synapse0x4621ec0() {
   return (neuron0x7da6470()*-0.632091);
}

double TMVAClassification_TMlp_ANN::synapse0x4621f00() {
   return (neuron0x6e201f0()*-0.559242);
}

double TMVAClassification_TMlp_ANN::synapse0x597cb20() {
   return (neuron0x7229820()*-0.445851);
}

double TMVAClassification_TMlp_ANN::synapse0x597cb60() {
   return (neuron0x5fe5630()*0.397572);
}

double TMVAClassification_TMlp_ANN::synapse0x597cba0() {
   return (neuron0x6e364e0()*0.0242585);
}

double TMVAClassification_TMlp_ANN::synapse0x597cbe0() {
   return (neuron0x70c3610()*-0.0339604);
}

double TMVAClassification_TMlp_ANN::synapse0x6636ad0() {
   return (neuron0x753f310()*-0.700028);
}

double TMVAClassification_TMlp_ANN::synapse0x6636b10() {
   return (neuron0x5b753e0()*-0.634269);
}

double TMVAClassification_TMlp_ANN::synapse0x6636b50() {
   return (neuron0x64be3a0()*0.118845);
}

double TMVAClassification_TMlp_ANN::synapse0x6636b90() {
   return (neuron0x7ddcd40()*-0.119377);
}

double TMVAClassification_TMlp_ANN::synapse0x6636bd0() {
   return (neuron0x5b8ed90()*-0.428168);
}

double TMVAClassification_TMlp_ANN::synapse0x6636c10() {
   return (neuron0x6613860()*-0.27102);
}

double TMVAClassification_TMlp_ANN::synapse0x75e3750() {
   return (neuron0x5fa9b00()*-0.221077);
}

double TMVAClassification_TMlp_ANN::synapse0x75e3790() {
   return (neuron0x6e4f550()*-0.488919);
}

double TMVAClassification_TMlp_ANN::synapse0x75e37d0() {
   return (neuron0x768b210()*-0.274117);
}

double TMVAClassification_TMlp_ANN::synapse0x75e3810() {
   return (neuron0x660fe00()*-0.229686);
}

double TMVAClassification_TMlp_ANN::synapse0x75e3850() {
   return (neuron0x5dbd1d0()*-0.459599);
}

double TMVAClassification_TMlp_ANN::synapse0x75e3890() {
   return (neuron0x7c6efd0()*-0.0269869);
}

double TMVAClassification_TMlp_ANN::synapse0x5100b10() {
   return (neuron0x624f870()*-0.498886);
}

double TMVAClassification_TMlp_ANN::synapse0x5100b50() {
   return (neuron0x710cab0()*0.121232);
}

double TMVAClassification_TMlp_ANN::synapse0x5100b90() {
   return (neuron0x67c49b0()*0.0337546);
}

double TMVAClassification_TMlp_ANN::synapse0x5100bd0() {
   return (neuron0x77723c0()*0.266092);
}

double TMVAClassification_TMlp_ANN::synapse0x597cc20() {
   return (neuron0x5796be0()*-0.0235261);
}

double TMVAClassification_TMlp_ANN::synapse0x597cc60() {
   return (neuron0x68c4f20()*-0.664518);
}

double TMVAClassification_TMlp_ANN::synapse0x7ad5c80() {
   return (neuron0x5fa3a60()*-0.0280831);
}

double TMVAClassification_TMlp_ANN::synapse0x7ad5cc0() {
   return (neuron0x58886c0()*0.179511);
}

double TMVAClassification_TMlp_ANN::synapse0x7ad5d00() {
   return (neuron0x6dcd6b0()*-0.507478);
}

double TMVAClassification_TMlp_ANN::synapse0x5100c10() {
   return (neuron0x7c1a4f0()*-0.520265);
}

double TMVAClassification_TMlp_ANN::synapse0x5100c50() {
   return (neuron0x7f702c0()*-0.373015);
}

double TMVAClassification_TMlp_ANN::synapse0x5100c90() {
   return (neuron0x7887220()*-0.172434);
}

double TMVAClassification_TMlp_ANN::synapse0x7bca1f0() {
   return (neuron0x79caea0()*0.126853);
}

double TMVAClassification_TMlp_ANN::synapse0x7bca230() {
   return (neuron0x4d370f0()*-0.204683);
}

double TMVAClassification_TMlp_ANN::synapse0x7bca270() {
   return (neuron0x7c7cbb0()*0.246127);
}

double TMVAClassification_TMlp_ANN::synapse0x7bca2b0() {
   return (neuron0x5751ec0()*0.0425103);
}

double TMVAClassification_TMlp_ANN::synapse0x7bca2f0() {
   return (neuron0x7da6470()*0.121753);
}

double TMVAClassification_TMlp_ANN::synapse0x7bca330() {
   return (neuron0x6e201f0()*-0.648288);
}

double TMVAClassification_TMlp_ANN::synapse0x7bca370() {
   return (neuron0x7229820()*0.347038);
}

double TMVAClassification_TMlp_ANN::synapse0x5bb1fe0() {
   return (neuron0x5fe5630()*-0.768731);
}

double TMVAClassification_TMlp_ANN::synapse0x7ad5b70() {
   return (neuron0x6e364e0()*-0.662497);
}

double TMVAClassification_TMlp_ANN::synapse0x7ad5bb0() {
   return (neuron0x70c3610()*0.34341);
}

double TMVAClassification_TMlp_ANN::synapse0x56d8270() {
   return (neuron0x753f310()*-0.138321);
}

double TMVAClassification_TMlp_ANN::synapse0x56d82b0() {
   return (neuron0x5b753e0()*-0.582056);
}

double TMVAClassification_TMlp_ANN::synapse0x77486b0() {
   return (neuron0x64be3a0()*-0.432025);
}

double TMVAClassification_TMlp_ANN::synapse0x77486f0() {
   return (neuron0x7ddcd40()*-0.608697);
}

double TMVAClassification_TMlp_ANN::synapse0x7748730() {
   return (neuron0x5b8ed90()*-0.109354);
}

double TMVAClassification_TMlp_ANN::synapse0x7748770() {
   return (neuron0x6613860()*-0.153431);
}

double TMVAClassification_TMlp_ANN::synapse0x77487b0() {
   return (neuron0x5fa9b00()*-0.325607);
}

double TMVAClassification_TMlp_ANN::synapse0x77487f0() {
   return (neuron0x6e4f550()*0.0800661);
}

double TMVAClassification_TMlp_ANN::synapse0x7748830() {
   return (neuron0x768b210()*-0.35003);
}

double TMVAClassification_TMlp_ANN::synapse0x7748870() {
   return (neuron0x660fe00()*0.208912);
}

double TMVAClassification_TMlp_ANN::synapse0x77488b0() {
   return (neuron0x5dbd1d0()*-0.200237);
}

double TMVAClassification_TMlp_ANN::synapse0x77488f0() {
   return (neuron0x7c6efd0()*-0.0616799);
}

double TMVAClassification_TMlp_ANN::synapse0x7748930() {
   return (neuron0x624f870()*0.267633);
}

double TMVAClassification_TMlp_ANN::synapse0x7748970() {
   return (neuron0x710cab0()*-0.215432);
}

double TMVAClassification_TMlp_ANN::synapse0x77489b0() {
   return (neuron0x67c49b0()*-0.450091);
}

double TMVAClassification_TMlp_ANN::synapse0x77489f0() {
   return (neuron0x77723c0()*-0.0983415);
}

double TMVAClassification_TMlp_ANN::synapse0x7ad5bf0() {
   return (neuron0x5796be0()*-0.0488176);
}

double TMVAClassification_TMlp_ANN::synapse0x7ad5c30() {
   return (neuron0x68c4f20()*-0.0545505);
}

double TMVAClassification_TMlp_ANN::synapse0x7748b40() {
   return (neuron0x5fa3a60()*-0.553306);
}

double TMVAClassification_TMlp_ANN::synapse0x7748b80() {
   return (neuron0x58886c0()*-0.018343);
}

double TMVAClassification_TMlp_ANN::synapse0x7748bc0() {
   return (neuron0x6dcd6b0()*-0.361999);
}

double TMVAClassification_TMlp_ANN::synapse0x7748c00() {
   return (neuron0x7c1a4f0()*0.230121);
}

double TMVAClassification_TMlp_ANN::synapse0x7748c40() {
   return (neuron0x7f702c0()*-0.530162);
}

double TMVAClassification_TMlp_ANN::synapse0x6deb910() {
   return (neuron0x7887220()*-0.143728);
}

double TMVAClassification_TMlp_ANN::synapse0x6deb950() {
   return (neuron0x79caea0()*0.0239731);
}

double TMVAClassification_TMlp_ANN::synapse0x6deb990() {
   return (neuron0x4d370f0()*0.128952);
}

double TMVAClassification_TMlp_ANN::synapse0x6deb9d0() {
   return (neuron0x7c7cbb0()*-0.547483);
}

double TMVAClassification_TMlp_ANN::synapse0x6deba10() {
   return (neuron0x5751ec0()*-0.283853);
}

double TMVAClassification_TMlp_ANN::synapse0x6deba50() {
   return (neuron0x7da6470()*0.0642282);
}

double TMVAClassification_TMlp_ANN::synapse0x6deba90() {
   return (neuron0x6e201f0()*0.0510717);
}

double TMVAClassification_TMlp_ANN::synapse0x6debad0() {
   return (neuron0x7229820()*-0.393514);
}

double TMVAClassification_TMlp_ANN::synapse0x6debb10() {
   return (neuron0x5fe5630()*-0.462873);
}

double TMVAClassification_TMlp_ANN::synapse0x7748a30() {
   return (neuron0x6e364e0()*-0.0301166);
}

double TMVAClassification_TMlp_ANN::synapse0x7748a70() {
   return (neuron0x70c3610()*0.150354);
}

double TMVAClassification_TMlp_ANN::synapse0x55c7300() {
   return (neuron0x753f310()*-0.176581);
}

double TMVAClassification_TMlp_ANN::synapse0x55c7340() {
   return (neuron0x5b753e0()*0.257561);
}

double TMVAClassification_TMlp_ANN::synapse0x55c7380() {
   return (neuron0x64be3a0()*-0.401191);
}

double TMVAClassification_TMlp_ANN::synapse0x55c73c0() {
   return (neuron0x7ddcd40()*-0.290185);
}

double TMVAClassification_TMlp_ANN::synapse0x55c7400() {
   return (neuron0x5b8ed90()*0.08328);
}

double TMVAClassification_TMlp_ANN::synapse0x55c7440() {
   return (neuron0x6613860()*0.363995);
}

double TMVAClassification_TMlp_ANN::synapse0x55c7480() {
   return (neuron0x5fa9b00()*-0.346666);
}

double TMVAClassification_TMlp_ANN::synapse0x55c74c0() {
   return (neuron0x6e4f550()*0.189391);
}

double TMVAClassification_TMlp_ANN::synapse0x55c7500() {
   return (neuron0x768b210()*-0.379772);
}

double TMVAClassification_TMlp_ANN::synapse0x55c7540() {
   return (neuron0x660fe00()*0.105353);
}

double TMVAClassification_TMlp_ANN::synapse0x55c7580() {
   return (neuron0x5dbd1d0()*0.26299);
}

double TMVAClassification_TMlp_ANN::synapse0x55c75c0() {
   return (neuron0x7c6efd0()*-0.601299);
}

double TMVAClassification_TMlp_ANN::synapse0x55c7600() {
   return (neuron0x624f870()*0.174127);
}

double TMVAClassification_TMlp_ANN::synapse0x55c7640() {
   return (neuron0x710cab0()*0.202846);
}

double TMVAClassification_TMlp_ANN::synapse0x55c7680() {
   return (neuron0x67c49b0()*-0.505042);
}

double TMVAClassification_TMlp_ANN::synapse0x55c76c0() {
   return (neuron0x77723c0()*0.106892);
}

double TMVAClassification_TMlp_ANN::synapse0x7748ab0() {
   return (neuron0x5796be0()*-0.536468);
}

double TMVAClassification_TMlp_ANN::synapse0x7748af0() {
   return (neuron0x68c4f20()*-0.544349);
}

double TMVAClassification_TMlp_ANN::synapse0x55c7700() {
   return (neuron0x5fa3a60()*-0.0107099);
}

double TMVAClassification_TMlp_ANN::synapse0x55c7740() {
   return (neuron0x58886c0()*0.254467);
}

double TMVAClassification_TMlp_ANN::synapse0x55c7780() {
   return (neuron0x6dcd6b0()*-0.597925);
}

double TMVAClassification_TMlp_ANN::synapse0x625d310() {
   return (neuron0x7c1a4f0()*-0.143557);
}

double TMVAClassification_TMlp_ANN::synapse0x625d350() {
   return (neuron0x7f702c0()*-0.292186);
}

double TMVAClassification_TMlp_ANN::synapse0x625d390() {
   return (neuron0x7887220()*-0.124119);
}

double TMVAClassification_TMlp_ANN::synapse0x625d3d0() {
   return (neuron0x79caea0()*-0.263283);
}

double TMVAClassification_TMlp_ANN::synapse0x625d410() {
   return (neuron0x4d370f0()*-0.519697);
}

double TMVAClassification_TMlp_ANN::synapse0x625d450() {
   return (neuron0x7c7cbb0()*0.122715);
}

double TMVAClassification_TMlp_ANN::synapse0x625d490() {
   return (neuron0x5751ec0()*-0.290102);
}

double TMVAClassification_TMlp_ANN::synapse0x625d4d0() {
   return (neuron0x7da6470()*-0.506063);
}

double TMVAClassification_TMlp_ANN::synapse0x625d510() {
   return (neuron0x6e201f0()*-0.0330519);
}

double TMVAClassification_TMlp_ANN::synapse0x625d550() {
   return (neuron0x7229820()*-0.427704);
}

double TMVAClassification_TMlp_ANN::synapse0x625d590() {
   return (neuron0x5fe5630()*-0.511955);
}

double TMVAClassification_TMlp_ANN::synapse0x625d200() {
   return (neuron0x6e364e0()*-0.0790166);
}

double TMVAClassification_TMlp_ANN::synapse0x625d240() {
   return (neuron0x70c3610()*0.258937);
}

double TMVAClassification_TMlp_ANN::synapse0x4d68670() {
   return (neuron0x753f310()*-1.62429);
}

double TMVAClassification_TMlp_ANN::synapse0x4d686b0() {
   return (neuron0x5b753e0()*-3.17115);
}

double TMVAClassification_TMlp_ANN::synapse0x4d686f0() {
   return (neuron0x64be3a0()*0.772619);
}

double TMVAClassification_TMlp_ANN::synapse0x4d68730() {
   return (neuron0x7ddcd40()*-0.108836);
}

double TMVAClassification_TMlp_ANN::synapse0x4d68770() {
   return (neuron0x5b8ed90()*-2.06872);
}

double TMVAClassification_TMlp_ANN::synapse0x4d687b0() {
   return (neuron0x6613860()*1.82583);
}

double TMVAClassification_TMlp_ANN::synapse0x4d687f0() {
   return (neuron0x5fa9b00()*-2.12341);
}

double TMVAClassification_TMlp_ANN::synapse0x4d68830() {
   return (neuron0x6e4f550()*0.863525);
}

double TMVAClassification_TMlp_ANN::synapse0x4d68870() {
   return (neuron0x768b210()*1.20729);
}

double TMVAClassification_TMlp_ANN::synapse0x4d688b0() {
   return (neuron0x660fe00()*-1.95394);
}

double TMVAClassification_TMlp_ANN::synapse0x4d688f0() {
   return (neuron0x5dbd1d0()*2.25377);
}

double TMVAClassification_TMlp_ANN::synapse0x4d68930() {
   return (neuron0x7c6efd0()*-1.9375);
}

double TMVAClassification_TMlp_ANN::synapse0x4d68970() {
   return (neuron0x624f870()*-0.510737);
}

double TMVAClassification_TMlp_ANN::synapse0x6630ea0() {
   return (neuron0x710cab0()*-0.746936);
}

double TMVAClassification_TMlp_ANN::synapse0x6630ee0() {
   return (neuron0x67c49b0()*2.00512);
}

double TMVAClassification_TMlp_ANN::synapse0x6630f20() {
   return (neuron0x77723c0()*0.588528);
}

double TMVAClassification_TMlp_ANN::synapse0x625d280() {
   return (neuron0x5796be0()*-0.624236);
}

double TMVAClassification_TMlp_ANN::synapse0x625d2c0() {
   return (neuron0x68c4f20()*-2.07668);
}

double TMVAClassification_TMlp_ANN::synapse0x6631070() {
   return (neuron0x5fa3a60()*1.07207);
}

double TMVAClassification_TMlp_ANN::synapse0x66310b0() {
   return (neuron0x58886c0()*0.983434);
}

double TMVAClassification_TMlp_ANN::synapse0x66310f0() {
   return (neuron0x6dcd6b0()*-3.0325);
}

double TMVAClassification_TMlp_ANN::synapse0x6631130() {
   return (neuron0x7c1a4f0()*-1.12622);
}

double TMVAClassification_TMlp_ANN::synapse0x6631170() {
   return (neuron0x7f702c0()*0.380208);
}

double TMVAClassification_TMlp_ANN::synapse0x66311b0() {
   return (neuron0x7887220()*0.948103);
}

double TMVAClassification_TMlp_ANN::synapse0x66311f0() {
   return (neuron0x79caea0()*-1.00535);
}

double TMVAClassification_TMlp_ANN::synapse0x6631230() {
   return (neuron0x4d370f0()*-1.14882);
}

double TMVAClassification_TMlp_ANN::synapse0x6631270() {
   return (neuron0x7c7cbb0()*-1.03659);
}

double TMVAClassification_TMlp_ANN::synapse0x66312b0() {
   return (neuron0x5751ec0()*0.968979);
}

double TMVAClassification_TMlp_ANN::synapse0x66312f0() {
   return (neuron0x7da6470()*-3.28632);
}

double TMVAClassification_TMlp_ANN::synapse0x6631330() {
   return (neuron0x6e201f0()*1.3647);
}

double TMVAClassification_TMlp_ANN::synapse0x6631370() {
   return (neuron0x7229820()*2.48675);
}

double TMVAClassification_TMlp_ANN::synapse0x66313b0() {
   return (neuron0x5fe5630()*-1.66908);
}

double TMVAClassification_TMlp_ANN::synapse0x66313f0() {
   return (neuron0x6e364e0()*0.0646833);
}

double TMVAClassification_TMlp_ANN::synapse0x6631430() {
   return (neuron0x70c3610()*0.860537);
}

double TMVAClassification_TMlp_ANN::synapse0x6ab8860() {
   return (neuron0x753f310()*0.253445);
}

double TMVAClassification_TMlp_ANN::synapse0x6ab88a0() {
   return (neuron0x5b753e0()*-0.458812);
}

double TMVAClassification_TMlp_ANN::synapse0x6630f60() {
   return (neuron0x64be3a0()*-0.169617);
}

double TMVAClassification_TMlp_ANN::synapse0x6630fa0() {
   return (neuron0x7ddcd40()*0.0150385);
}

double TMVAClassification_TMlp_ANN::synapse0x6630fe0() {
   return (neuron0x5b8ed90()*-0.0834126);
}

double TMVAClassification_TMlp_ANN::synapse0x6631020() {
   return (neuron0x6613860()*0.402395);
}

double TMVAClassification_TMlp_ANN::synapse0x511da20() {
   return (neuron0x5fa9b00()*-0.354647);
}

double TMVAClassification_TMlp_ANN::synapse0x511da60() {
   return (neuron0x6e4f550()*-0.361744);
}

double TMVAClassification_TMlp_ANN::synapse0x511daa0() {
   return (neuron0x768b210()*0.0881074);
}

double TMVAClassification_TMlp_ANN::synapse0x511dae0() {
   return (neuron0x660fe00()*-0.38119);
}

double TMVAClassification_TMlp_ANN::synapse0x511db20() {
   return (neuron0x5dbd1d0()*-0.413665);
}

double TMVAClassification_TMlp_ANN::synapse0x511db60() {
   return (neuron0x7c6efd0()*-0.415034);
}

double TMVAClassification_TMlp_ANN::synapse0x511dba0() {
   return (neuron0x624f870()*-0.242344);
}

double TMVAClassification_TMlp_ANN::synapse0x511dbe0() {
   return (neuron0x710cab0()*0.326571);
}

double TMVAClassification_TMlp_ANN::synapse0x511dc20() {
   return (neuron0x67c49b0()*-0.323704);
}

double TMVAClassification_TMlp_ANN::synapse0x511dc60() {
   return (neuron0x77723c0()*0.19462);
}

double TMVAClassification_TMlp_ANN::synapse0x6ab86b0() {
   return (neuron0x5796be0()*0.216722);
}

double TMVAClassification_TMlp_ANN::synapse0x6ab86f0() {
   return (neuron0x68c4f20()*-0.434422);
}

double TMVAClassification_TMlp_ANN::synapse0x511ddb0() {
   return (neuron0x5fa3a60()*-0.129271);
}

double TMVAClassification_TMlp_ANN::synapse0x511ddf0() {
   return (neuron0x58886c0()*-0.182202);
}

double TMVAClassification_TMlp_ANN::synapse0x511de30() {
   return (neuron0x6dcd6b0()*-0.0623899);
}

double TMVAClassification_TMlp_ANN::synapse0x511de70() {
   return (neuron0x7c1a4f0()*0.158282);
}

double TMVAClassification_TMlp_ANN::synapse0x511deb0() {
   return (neuron0x7f702c0()*-0.447324);
}

double TMVAClassification_TMlp_ANN::synapse0x511def0() {
   return (neuron0x7887220()*0.196966);
}

double TMVAClassification_TMlp_ANN::synapse0x511df30() {
   return (neuron0x79caea0()*-0.518527);
}

double TMVAClassification_TMlp_ANN::synapse0x511df70() {
   return (neuron0x4d370f0()*-0.506351);
}

double TMVAClassification_TMlp_ANN::synapse0x511dfb0() {
   return (neuron0x7c7cbb0()*-0.568881);
}

double TMVAClassification_TMlp_ANN::synapse0x5fcac00() {
   return (neuron0x5751ec0()*0.240325);
}

double TMVAClassification_TMlp_ANN::synapse0x5fcac40() {
   return (neuron0x7da6470()*0.451917);
}

double TMVAClassification_TMlp_ANN::synapse0x5fcac80() {
   return (neuron0x6e201f0()*-0.437716);
}

double TMVAClassification_TMlp_ANN::synapse0x5fcacc0() {
   return (neuron0x7229820()*-0.46093);
}

double TMVAClassification_TMlp_ANN::synapse0x5fcad00() {
   return (neuron0x5fe5630()*0.40741);
}

double TMVAClassification_TMlp_ANN::synapse0x511dca0() {
   return (neuron0x6e364e0()*-0.576531);
}

double TMVAClassification_TMlp_ANN::synapse0x511dce0() {
   return (neuron0x70c3610()*-0.091775);
}

double TMVAClassification_TMlp_ANN::synapse0x6819a20() {
   return (neuron0x753f310()*-0.105377);
}

double TMVAClassification_TMlp_ANN::synapse0x6819a60() {
   return (neuron0x5b753e0()*-0.337193);
}

double TMVAClassification_TMlp_ANN::synapse0x6819aa0() {
   return (neuron0x64be3a0()*0.131243);
}

double TMVAClassification_TMlp_ANN::synapse0x6819ae0() {
   return (neuron0x7ddcd40()*-0.197513);
}

double TMVAClassification_TMlp_ANN::synapse0x6819b20() {
   return (neuron0x5b8ed90()*-0.55463);
}

double TMVAClassification_TMlp_ANN::synapse0x6819b60() {
   return (neuron0x6613860()*0.279115);
}

double TMVAClassification_TMlp_ANN::synapse0x6819ba0() {
   return (neuron0x5fa9b00()*0.21384);
}

double TMVAClassification_TMlp_ANN::synapse0x6819be0() {
   return (neuron0x6e4f550()*-0.0926682);
}

double TMVAClassification_TMlp_ANN::synapse0x6819c20() {
   return (neuron0x768b210()*0.045823);
}

double TMVAClassification_TMlp_ANN::synapse0x6819c60() {
   return (neuron0x660fe00()*-0.520594);
}

double TMVAClassification_TMlp_ANN::synapse0x6819ca0() {
   return (neuron0x5dbd1d0()*0.122046);
}

double TMVAClassification_TMlp_ANN::synapse0x6819ce0() {
   return (neuron0x7c6efd0()*-0.0135128);
}

double TMVAClassification_TMlp_ANN::synapse0x6819d20() {
   return (neuron0x624f870()*0.214088);
}

double TMVAClassification_TMlp_ANN::synapse0x6819d60() {
   return (neuron0x710cab0()*-0.0816291);
}

double TMVAClassification_TMlp_ANN::synapse0x6819da0() {
   return (neuron0x67c49b0()*-0.157301);
}

double TMVAClassification_TMlp_ANN::synapse0x6819de0() {
   return (neuron0x77723c0()*-0.415);
}

double TMVAClassification_TMlp_ANN::synapse0x6819f30() {
   return (neuron0x5796be0()*-0.373456);
}

double TMVAClassification_TMlp_ANN::synapse0x5fcb170() {
   return (neuron0x68c4f20()*0.0823066);
}

double TMVAClassification_TMlp_ANN::synapse0x5fcb1b0() {
   return (neuron0x5fa3a60()*-0.631392);
}

double TMVAClassification_TMlp_ANN::synapse0x511dd20() {
   return (neuron0x58886c0()*-0.280641);
}

double TMVAClassification_TMlp_ANN::synapse0x511dd60() {
   return (neuron0x6dcd6b0()*-0.340438);
}

double TMVAClassification_TMlp_ANN::synapse0x4d1c960() {
   return (neuron0x7c1a4f0()*-0.487343);
}

double TMVAClassification_TMlp_ANN::synapse0x4d1c9a0() {
   return (neuron0x7f702c0()*-0.551524);
}

double TMVAClassification_TMlp_ANN::synapse0x4d1c9e0() {
   return (neuron0x7887220()*-0.0516359);
}

double TMVAClassification_TMlp_ANN::synapse0x4d1ca20() {
   return (neuron0x79caea0()*0.0836439);
}

double TMVAClassification_TMlp_ANN::synapse0x4d1ca60() {
   return (neuron0x4d370f0()*-0.0472621);
}

double TMVAClassification_TMlp_ANN::synapse0x4d1caa0() {
   return (neuron0x7c7cbb0()*-0.0818487);
}

double TMVAClassification_TMlp_ANN::synapse0x4d1cae0() {
   return (neuron0x5751ec0()*-0.269754);
}

double TMVAClassification_TMlp_ANN::synapse0x4d1cb20() {
   return (neuron0x7da6470()*-0.461686);
}

double TMVAClassification_TMlp_ANN::synapse0x4d1cb60() {
   return (neuron0x6e201f0()*-0.0964147);
}

double TMVAClassification_TMlp_ANN::synapse0x4d1cba0() {
   return (neuron0x7229820()*-0.0995413);
}

double TMVAClassification_TMlp_ANN::synapse0x4d1cbe0() {
   return (neuron0x5fe5630()*0.0926204);
}

double TMVAClassification_TMlp_ANN::synapse0x6819e20() {
   return (neuron0x6e364e0()*0.146621);
}

double TMVAClassification_TMlp_ANN::synapse0x6819e60() {
   return (neuron0x70c3610()*-0.320852);
}

double TMVAClassification_TMlp_ANN::synapse0x6396b60() {
   return (neuron0x753f310()*0.275193);
}

double TMVAClassification_TMlp_ANN::synapse0x6396ba0() {
   return (neuron0x5b753e0()*-0.176961);
}

double TMVAClassification_TMlp_ANN::synapse0x6396be0() {
   return (neuron0x64be3a0()*0.101304);
}

double TMVAClassification_TMlp_ANN::synapse0x6396c20() {
   return (neuron0x7ddcd40()*-0.0830956);
}

double TMVAClassification_TMlp_ANN::synapse0x6396c60() {
   return (neuron0x5b8ed90()*-0.211381);
}

double TMVAClassification_TMlp_ANN::synapse0x6396ca0() {
   return (neuron0x6613860()*-0.294688);
}

double TMVAClassification_TMlp_ANN::synapse0x6396ce0() {
   return (neuron0x5fa9b00()*-0.376235);
}

double TMVAClassification_TMlp_ANN::synapse0x6396d20() {
   return (neuron0x6e4f550()*-0.515925);
}

double TMVAClassification_TMlp_ANN::synapse0x6396d60() {
   return (neuron0x768b210()*0.11027);
}

double TMVAClassification_TMlp_ANN::synapse0x6396da0() {
   return (neuron0x660fe00()*-0.635765);
}

double TMVAClassification_TMlp_ANN::synapse0x6396de0() {
   return (neuron0x5dbd1d0()*-0.106949);
}

double TMVAClassification_TMlp_ANN::synapse0x6396e20() {
   return (neuron0x7c6efd0()*-0.762835);
}

double TMVAClassification_TMlp_ANN::synapse0x6396e60() {
   return (neuron0x624f870()*-0.360777);
}

double TMVAClassification_TMlp_ANN::synapse0x6396ea0() {
   return (neuron0x710cab0()*-0.530831);
}

double TMVAClassification_TMlp_ANN::synapse0x6396ee0() {
   return (neuron0x67c49b0()*0.285475);
}

double TMVAClassification_TMlp_ANN::synapse0x4d1ce30() {
   return (neuron0x77723c0()*-0.239819);
}

double TMVAClassification_TMlp_ANN::synapse0x6819ea0() {
   return (neuron0x5796be0()*-0.391458);
}

double TMVAClassification_TMlp_ANN::synapse0x6819ee0() {
   return (neuron0x68c4f20()*0.198644);
}

double TMVAClassification_TMlp_ANN::synapse0x4d1ce70() {
   return (neuron0x5fa3a60()*-0.39295);
}

double TMVAClassification_TMlp_ANN::synapse0x4d1ceb0() {
   return (neuron0x58886c0()*-0.388834);
}

double TMVAClassification_TMlp_ANN::synapse0x4d1cef0() {
   return (neuron0x6dcd6b0()*-0.509621);
}

double TMVAClassification_TMlp_ANN::synapse0x4d1cf30() {
   return (neuron0x7c1a4f0()*-0.16804);
}

double TMVAClassification_TMlp_ANN::synapse0x7766500() {
   return (neuron0x7f702c0()*-0.100139);
}

double TMVAClassification_TMlp_ANN::synapse0x7766540() {
   return (neuron0x7887220()*0.305838);
}

double TMVAClassification_TMlp_ANN::synapse0x7766580() {
   return (neuron0x79caea0()*-0.625983);
}

double TMVAClassification_TMlp_ANN::synapse0x77665c0() {
   return (neuron0x4d370f0()*-0.504879);
}

double TMVAClassification_TMlp_ANN::synapse0x7766600() {
   return (neuron0x7c7cbb0()*0.347782);
}

double TMVAClassification_TMlp_ANN::synapse0x7766640() {
   return (neuron0x5751ec0()*-0.355016);
}

double TMVAClassification_TMlp_ANN::synapse0x7766680() {
   return (neuron0x7da6470()*-0.212034);
}

double TMVAClassification_TMlp_ANN::synapse0x77666c0() {
   return (neuron0x6e201f0()*0.109115);
}

double TMVAClassification_TMlp_ANN::synapse0x7766700() {
   return (neuron0x7229820()*-0.0883431);
}

double TMVAClassification_TMlp_ANN::synapse0x7766740() {
   return (neuron0x5fe5630()*-0.13312);
}

double TMVAClassification_TMlp_ANN::synapse0x77663f0() {
   return (neuron0x6e364e0()*-0.112026);
}

double TMVAClassification_TMlp_ANN::synapse0x7766430() {
   return (neuron0x70c3610()*0.0964683);
}

double TMVAClassification_TMlp_ANN::synapse0x4b232e0() {
   return (neuron0x753f310()*0.14162);
}

double TMVAClassification_TMlp_ANN::synapse0x4b23320() {
   return (neuron0x5b753e0()*-0.513866);
}

double TMVAClassification_TMlp_ANN::synapse0x4b23360() {
   return (neuron0x64be3a0()*-0.0746001);
}

double TMVAClassification_TMlp_ANN::synapse0x4b233a0() {
   return (neuron0x7ddcd40()*-0.571428);
}

double TMVAClassification_TMlp_ANN::synapse0x4b233e0() {
   return (neuron0x5b8ed90()*-0.125432);
}

double TMVAClassification_TMlp_ANN::synapse0x4b23420() {
   return (neuron0x6613860()*0.1554);
}

double TMVAClassification_TMlp_ANN::synapse0x4b23460() {
   return (neuron0x5fa9b00()*-0.373235);
}

double TMVAClassification_TMlp_ANN::synapse0x4b234a0() {
   return (neuron0x6e4f550()*0.00624104);
}

double TMVAClassification_TMlp_ANN::synapse0x4b234e0() {
   return (neuron0x768b210()*0.334586);
}

double TMVAClassification_TMlp_ANN::synapse0x4b23520() {
   return (neuron0x660fe00()*-0.264009);
}

double TMVAClassification_TMlp_ANN::synapse0x4b23560() {
   return (neuron0x5dbd1d0()*0.0188681);
}

double TMVAClassification_TMlp_ANN::synapse0x4b235a0() {
   return (neuron0x7c6efd0()*-0.533281);
}

double TMVAClassification_TMlp_ANN::synapse0x4b235e0() {
   return (neuron0x624f870()*0.00499703);
}

double TMVAClassification_TMlp_ANN::synapse0x4b23620() {
   return (neuron0x710cab0()*-0.0722927);
}

double TMVAClassification_TMlp_ANN::synapse0x4b23660() {
   return (neuron0x67c49b0()*0.0519759);
}

double TMVAClassification_TMlp_ANN::synapse0x4b236a0() {
   return (neuron0x77723c0()*-0.538271);
}

double TMVAClassification_TMlp_ANN::synapse0x7766470() {
   return (neuron0x5796be0()*-0.200509);
}

double TMVAClassification_TMlp_ANN::synapse0x77664b0() {
   return (neuron0x68c4f20()*-0.617988);
}

double TMVAClassification_TMlp_ANN::synapse0x4b237f0() {
   return (neuron0x5fa3a60()*-0.303698);
}

double TMVAClassification_TMlp_ANN::synapse0x4b23830() {
   return (neuron0x58886c0()*-0.404811);
}

double TMVAClassification_TMlp_ANN::synapse0x4b23870() {
   return (neuron0x6dcd6b0()*0.0950693);
}

double TMVAClassification_TMlp_ANN::synapse0x4b238b0() {
   return (neuron0x7c1a4f0()*-0.344664);
}

double TMVAClassification_TMlp_ANN::synapse0x5d668e0() {
   return (neuron0x7f702c0()*-0.478686);
}

double TMVAClassification_TMlp_ANN::synapse0x5d66920() {
   return (neuron0x7887220()*0.00749637);
}

double TMVAClassification_TMlp_ANN::synapse0x5d66960() {
   return (neuron0x79caea0()*-0.307317);
}

double TMVAClassification_TMlp_ANN::synapse0x5d669a0() {
   return (neuron0x4d370f0()*-0.337908);
}

double TMVAClassification_TMlp_ANN::synapse0x5d669e0() {
   return (neuron0x7c7cbb0()*0.150007);
}

double TMVAClassification_TMlp_ANN::synapse0x5d66a20() {
   return (neuron0x5751ec0()*-0.203909);
}

double TMVAClassification_TMlp_ANN::synapse0x5d66a60() {
   return (neuron0x7da6470()*-0.162547);
}

double TMVAClassification_TMlp_ANN::synapse0x5d66aa0() {
   return (neuron0x6e201f0()*-0.404693);
}

double TMVAClassification_TMlp_ANN::synapse0x5d66ae0() {
   return (neuron0x7229820()*0.224944);
}

double TMVAClassification_TMlp_ANN::synapse0x5d66b20() {
   return (neuron0x5fe5630()*0.273559);
}

double TMVAClassification_TMlp_ANN::synapse0x4b236e0() {
   return (neuron0x6e364e0()*-0.634067);
}

double TMVAClassification_TMlp_ANN::synapse0x4b23720() {
   return (neuron0x70c3610()*0.0766367);
}

double TMVAClassification_TMlp_ANN::synapse0x5935680() {
   return (neuron0x753f310()*-0.373717);
}

double TMVAClassification_TMlp_ANN::synapse0x59356c0() {
   return (neuron0x5b753e0()*0.125765);
}

double TMVAClassification_TMlp_ANN::synapse0x5935700() {
   return (neuron0x64be3a0()*-0.0865205);
}

double TMVAClassification_TMlp_ANN::synapse0x5935740() {
   return (neuron0x7ddcd40()*-0.488084);
}

double TMVAClassification_TMlp_ANN::synapse0x5935780() {
   return (neuron0x5b8ed90()*-0.443532);
}

double TMVAClassification_TMlp_ANN::synapse0x59357c0() {
   return (neuron0x6613860()*0.211139);
}

double TMVAClassification_TMlp_ANN::synapse0x5935800() {
   return (neuron0x5fa9b00()*-0.0289893);
}

double TMVAClassification_TMlp_ANN::synapse0x5935840() {
   return (neuron0x6e4f550()*-0.0036288);
}

double TMVAClassification_TMlp_ANN::synapse0x5935880() {
   return (neuron0x768b210()*-0.47035);
}

double TMVAClassification_TMlp_ANN::synapse0x59358c0() {
   return (neuron0x660fe00()*-0.166543);
}

double TMVAClassification_TMlp_ANN::synapse0x5935900() {
   return (neuron0x5dbd1d0()*0.0120306);
}

double TMVAClassification_TMlp_ANN::synapse0x5935940() {
   return (neuron0x7c6efd0()*-0.309224);
}

double TMVAClassification_TMlp_ANN::synapse0x5935980() {
   return (neuron0x624f870()*-0.386247);
}

double TMVAClassification_TMlp_ANN::synapse0x59359c0() {
   return (neuron0x710cab0()*0.129539);
}

double TMVAClassification_TMlp_ANN::synapse0x5935a00() {
   return (neuron0x67c49b0()*-0.152065);
}

double TMVAClassification_TMlp_ANN::synapse0x5935a40() {
   return (neuron0x77723c0()*0.0967326);
}

double TMVAClassification_TMlp_ANN::synapse0x5d66f90() {
   return (neuron0x5796be0()*0.01743);
}

double TMVAClassification_TMlp_ANN::synapse0x5d66fd0() {
   return (neuron0x68c4f20()*-0.0801818);
}

double TMVAClassification_TMlp_ANN::synapse0x4b23760() {
   return (neuron0x5fa3a60()*0.0685393);
}

double TMVAClassification_TMlp_ANN::synapse0x4b237a0() {
   return (neuron0x58886c0()*-0.134251);
}

double TMVAClassification_TMlp_ANN::synapse0x5935b90() {
   return (neuron0x6dcd6b0()*0.180926);
}

double TMVAClassification_TMlp_ANN::synapse0x5935bd0() {
   return (neuron0x7c1a4f0()*-0.534461);
}

double TMVAClassification_TMlp_ANN::synapse0x5935c10() {
   return (neuron0x7f702c0()*0.332426);
}

double TMVAClassification_TMlp_ANN::synapse0x5935c50() {
   return (neuron0x7887220()*0.40036);
}

double TMVAClassification_TMlp_ANN::synapse0x5935c90() {
   return (neuron0x79caea0()*-0.0285615);
}

double TMVAClassification_TMlp_ANN::synapse0x5935cd0() {
   return (neuron0x4d370f0()*-0.38651);
}

double TMVAClassification_TMlp_ANN::synapse0x4ef8380() {
   return (neuron0x7c7cbb0()*0.00824359);
}

double TMVAClassification_TMlp_ANN::synapse0x4ef83c0() {
   return (neuron0x5751ec0()*-0.0428962);
}

double TMVAClassification_TMlp_ANN::synapse0x4ef8400() {
   return (neuron0x7da6470()*-0.315937);
}

double TMVAClassification_TMlp_ANN::synapse0x4ef8440() {
   return (neuron0x6e201f0()*-0.185074);
}

double TMVAClassification_TMlp_ANN::synapse0x4ef8480() {
   return (neuron0x7229820()*-0.133813);
}

double TMVAClassification_TMlp_ANN::synapse0x4ef84c0() {
   return (neuron0x5fe5630()*0.0550208);
}

double TMVAClassification_TMlp_ANN::synapse0x5935a80() {
   return (neuron0x6e364e0()*-0.573217);
}

double TMVAClassification_TMlp_ANN::synapse0x5935ac0() {
   return (neuron0x70c3610()*-0.716278);
}

double TMVAClassification_TMlp_ANN::synapse0x4ef89c0() {
   return (neuron0x753f310()*-0.453314);
}

double TMVAClassification_TMlp_ANN::synapse0x4ef8a00() {
   return (neuron0x5b753e0()*-0.460231);
}

double TMVAClassification_TMlp_ANN::synapse0x4ef8a40() {
   return (neuron0x64be3a0()*-0.393167);
}

double TMVAClassification_TMlp_ANN::synapse0x5f982b0() {
   return (neuron0x7ddcd40()*-0.465864);
}

double TMVAClassification_TMlp_ANN::synapse0x5f982f0() {
   return (neuron0x5b8ed90()*-0.158598);
}

double TMVAClassification_TMlp_ANN::synapse0x5f98330() {
   return (neuron0x6613860()*-0.395608);
}

double TMVAClassification_TMlp_ANN::synapse0x5f98370() {
   return (neuron0x5fa9b00()*-0.438594);
}

double TMVAClassification_TMlp_ANN::synapse0x5f983b0() {
   return (neuron0x6e4f550()*-0.0490701);
}

double TMVAClassification_TMlp_ANN::synapse0x5f983f0() {
   return (neuron0x768b210()*-0.391742);
}

double TMVAClassification_TMlp_ANN::synapse0x5f98430() {
   return (neuron0x660fe00()*0.15117);
}

double TMVAClassification_TMlp_ANN::synapse0x5f98470() {
   return (neuron0x5dbd1d0()*-0.288829);
}

double TMVAClassification_TMlp_ANN::synapse0x5f984b0() {
   return (neuron0x7c6efd0()*0.249521);
}

double TMVAClassification_TMlp_ANN::synapse0x5f984f0() {
   return (neuron0x624f870()*0.0754707);
}

double TMVAClassification_TMlp_ANN::synapse0x5f98530() {
   return (neuron0x710cab0()*-0.618296);
}

double TMVAClassification_TMlp_ANN::synapse0x5f98570() {
   return (neuron0x67c49b0()*-0.146975);
}

double TMVAClassification_TMlp_ANN::synapse0x5f985b0() {
   return (neuron0x77723c0()*0.0577637);
}

double TMVAClassification_TMlp_ANN::synapse0x5935b00() {
   return (neuron0x5796be0()*0.0273019);
}

double TMVAClassification_TMlp_ANN::synapse0x5935b40() {
   return (neuron0x68c4f20()*-0.458394);
}

double TMVAClassification_TMlp_ANN::synapse0x5f98700() {
   return (neuron0x5fa3a60()*-0.639577);
}

double TMVAClassification_TMlp_ANN::synapse0x5f98740() {
   return (neuron0x58886c0()*0.160362);
}

double TMVAClassification_TMlp_ANN::synapse0x5f98780() {
   return (neuron0x6dcd6b0()*-0.180906);
}

double TMVAClassification_TMlp_ANN::synapse0x5f987c0() {
   return (neuron0x7c1a4f0()*-0.588708);
}

double TMVAClassification_TMlp_ANN::synapse0x5f98800() {
   return (neuron0x7f702c0()*0.0360932);
}

double TMVAClassification_TMlp_ANN::synapse0x5f98840() {
   return (neuron0x7887220()*0.041442);
}

double TMVAClassification_TMlp_ANN::synapse0x5f98880() {
   return (neuron0x79caea0()*-0.320563);
}

double TMVAClassification_TMlp_ANN::synapse0x5f988c0() {
   return (neuron0x4d370f0()*0.193103);
}

double TMVAClassification_TMlp_ANN::synapse0x5f98900() {
   return (neuron0x7c7cbb0()*0.0907811);
}

double TMVAClassification_TMlp_ANN::synapse0x5f98940() {
   return (neuron0x5751ec0()*-0.640945);
}

double TMVAClassification_TMlp_ANN::synapse0x5f98980() {
   return (neuron0x7da6470()*0.0327775);
}

double TMVAClassification_TMlp_ANN::synapse0x6479270() {
   return (neuron0x6e201f0()*-0.455674);
}

double TMVAClassification_TMlp_ANN::synapse0x64792b0() {
   return (neuron0x7229820()*0.309158);
}

double TMVAClassification_TMlp_ANN::synapse0x64792f0() {
   return (neuron0x5fe5630()*-0.147393);
}

double TMVAClassification_TMlp_ANN::synapse0x5f985f0() {
   return (neuron0x6e364e0()*-0.068421);
}

double TMVAClassification_TMlp_ANN::synapse0x5f98630() {
   return (neuron0x70c3610()*0.175641);
}

double TMVAClassification_TMlp_ANN::synapse0x64797f0() {
   return (neuron0x753f310()*0.0682821);
}

double TMVAClassification_TMlp_ANN::synapse0x6479830() {
   return (neuron0x5b753e0()*0.139497);
}

double TMVAClassification_TMlp_ANN::synapse0x6479870() {
   return (neuron0x64be3a0()*-0.337083);
}

double TMVAClassification_TMlp_ANN::synapse0x64798b0() {
   return (neuron0x7ddcd40()*0.121194);
}

double TMVAClassification_TMlp_ANN::synapse0x64798f0() {
   return (neuron0x5b8ed90()*-0.718179);
}

double TMVAClassification_TMlp_ANN::synapse0x6479930() {
   return (neuron0x6613860()*-0.0095156);
}

double TMVAClassification_TMlp_ANN::synapse0x6014830() {
   return (neuron0x5fa9b00()*-0.092783);
}

double TMVAClassification_TMlp_ANN::synapse0x6014870() {
   return (neuron0x6e4f550()*-0.285146);
}

double TMVAClassification_TMlp_ANN::synapse0x60148b0() {
   return (neuron0x768b210()*-0.379792);
}

double TMVAClassification_TMlp_ANN::synapse0x60148f0() {
   return (neuron0x660fe00()*-0.172377);
}

double TMVAClassification_TMlp_ANN::synapse0x6014930() {
   return (neuron0x5dbd1d0()*0.111865);
}

double TMVAClassification_TMlp_ANN::synapse0x6014970() {
   return (neuron0x7c6efd0()*-0.810492);
}

double TMVAClassification_TMlp_ANN::synapse0x60149b0() {
   return (neuron0x624f870()*-0.151627);
}

double TMVAClassification_TMlp_ANN::synapse0x60149f0() {
   return (neuron0x710cab0()*-0.557348);
}

double TMVAClassification_TMlp_ANN::synapse0x6014a30() {
   return (neuron0x67c49b0()*-0.489585);
}

double TMVAClassification_TMlp_ANN::synapse0x6014a70() {
   return (neuron0x77723c0()*0.163389);
}

double TMVAClassification_TMlp_ANN::synapse0x5f98670() {
   return (neuron0x5796be0()*-0.543723);
}

double TMVAClassification_TMlp_ANN::synapse0x5f986b0() {
   return (neuron0x68c4f20()*0.0441403);
}

double TMVAClassification_TMlp_ANN::synapse0x6014bc0() {
   return (neuron0x5fa3a60()*0.209007);
}

double TMVAClassification_TMlp_ANN::synapse0x6014c00() {
   return (neuron0x58886c0()*-0.304913);
}

double TMVAClassification_TMlp_ANN::synapse0x6014c40() {
   return (neuron0x6dcd6b0()*-0.487756);
}

double TMVAClassification_TMlp_ANN::synapse0x6014c80() {
   return (neuron0x7c1a4f0()*0.139214);
}

double TMVAClassification_TMlp_ANN::synapse0x6014cc0() {
   return (neuron0x7f702c0()*-0.220853);
}

double TMVAClassification_TMlp_ANN::synapse0x6014d00() {
   return (neuron0x7887220()*-0.492878);
}

double TMVAClassification_TMlp_ANN::synapse0x6014d40() {
   return (neuron0x79caea0()*0.00968745);
}

double TMVAClassification_TMlp_ANN::synapse0x6014d80() {
   return (neuron0x4d370f0()*-0.0210521);
}

double TMVAClassification_TMlp_ANN::synapse0x6014dc0() {
   return (neuron0x7c7cbb0()*-0.0222583);
}

double TMVAClassification_TMlp_ANN::synapse0x6014e00() {
   return (neuron0x5751ec0()*0.0423979);
}

double TMVAClassification_TMlp_ANN::synapse0x6014e40() {
   return (neuron0x7da6470()*-0.238436);
}

double TMVAClassification_TMlp_ANN::synapse0x6014e80() {
   return (neuron0x6e201f0()*-0.0104514);
}

double TMVAClassification_TMlp_ANN::synapse0x6014ec0() {
   return (neuron0x7229820()*0.239903);
}

double TMVAClassification_TMlp_ANN::synapse0x6014f00() {
   return (neuron0x5fe5630()*-0.5818);
}

double TMVAClassification_TMlp_ANN::synapse0x6014ab0() {
   return (neuron0x6e364e0()*0.222582);
}

double TMVAClassification_TMlp_ANN::synapse0x6014af0() {
   return (neuron0x70c3610()*0.107414);
}

double TMVAClassification_TMlp_ANN::synapse0x56e4400() {
   return (neuron0x753f310()*0.240054);
}

double TMVAClassification_TMlp_ANN::synapse0x56e4440() {
   return (neuron0x5b753e0()*-0.280903);
}

double TMVAClassification_TMlp_ANN::synapse0x56e4480() {
   return (neuron0x64be3a0()*-0.184265);
}

double TMVAClassification_TMlp_ANN::synapse0x56e44c0() {
   return (neuron0x7ddcd40()*-0.1788);
}

double TMVAClassification_TMlp_ANN::synapse0x56e4500() {
   return (neuron0x5b8ed90()*-0.200391);
}

double TMVAClassification_TMlp_ANN::synapse0x56e4540() {
   return (neuron0x6613860()*-0.0675967);
}

double TMVAClassification_TMlp_ANN::synapse0x56e4580() {
   return (neuron0x5fa9b00()*-0.542984);
}

double TMVAClassification_TMlp_ANN::synapse0x56e45c0() {
   return (neuron0x6e4f550()*-0.422311);
}

double TMVAClassification_TMlp_ANN::synapse0x56e4600() {
   return (neuron0x768b210()*0.303642);
}

double TMVAClassification_TMlp_ANN::synapse0x59663f0() {
   return (neuron0x660fe00()*-0.583413);
}

double TMVAClassification_TMlp_ANN::synapse0x5966430() {
   return (neuron0x5dbd1d0()*-0.578494);
}

double TMVAClassification_TMlp_ANN::synapse0x5966470() {
   return (neuron0x7c6efd0()*-0.17545);
}

double TMVAClassification_TMlp_ANN::synapse0x59664b0() {
   return (neuron0x624f870()*-0.716848);
}

double TMVAClassification_TMlp_ANN::synapse0x59664f0() {
   return (neuron0x710cab0()*0.275138);
}

double TMVAClassification_TMlp_ANN::synapse0x5966530() {
   return (neuron0x67c49b0()*0.249522);
}

double TMVAClassification_TMlp_ANN::synapse0x5966570() {
   return (neuron0x77723c0()*-0.195377);
}

double TMVAClassification_TMlp_ANN::synapse0x6014b30() {
   return (neuron0x5796be0()*-0.165947);
}

double TMVAClassification_TMlp_ANN::synapse0x6014b70() {
   return (neuron0x68c4f20()*-0.112385);
}

double TMVAClassification_TMlp_ANN::synapse0x59666c0() {
   return (neuron0x5fa3a60()*0.250001);
}

double TMVAClassification_TMlp_ANN::synapse0x5966700() {
   return (neuron0x58886c0()*-0.192534);
}

double TMVAClassification_TMlp_ANN::synapse0x5966740() {
   return (neuron0x6dcd6b0()*-0.00476488);
}

double TMVAClassification_TMlp_ANN::synapse0x5966780() {
   return (neuron0x7c1a4f0()*-0.419675);
}

double TMVAClassification_TMlp_ANN::synapse0x59667c0() {
   return (neuron0x7f702c0()*0.170645);
}

double TMVAClassification_TMlp_ANN::synapse0x5966800() {
   return (neuron0x7887220()*0.0606847);
}

double TMVAClassification_TMlp_ANN::synapse0x5966840() {
   return (neuron0x79caea0()*-0.293327);
}

double TMVAClassification_TMlp_ANN::synapse0x5966880() {
   return (neuron0x4d370f0()*0.212452);
}

double TMVAClassification_TMlp_ANN::synapse0x59668c0() {
   return (neuron0x7c7cbb0()*-0.249959);
}

double TMVAClassification_TMlp_ANN::synapse0x5966900() {
   return (neuron0x5751ec0()*-0.283943);
}

double TMVAClassification_TMlp_ANN::synapse0x5966940() {
   return (neuron0x7da6470()*-0.42564);
}

double TMVAClassification_TMlp_ANN::synapse0x5966980() {
   return (neuron0x6e201f0()*0.206092);
}

double TMVAClassification_TMlp_ANN::synapse0x59669c0() {
   return (neuron0x7229820()*0.129895);
}

double TMVAClassification_TMlp_ANN::synapse0x5966a00() {
   return (neuron0x5fe5630()*-0.362798);
}

double TMVAClassification_TMlp_ANN::synapse0x5966a40() {
   return (neuron0x6e364e0()*-0.564431);
}

double TMVAClassification_TMlp_ANN::synapse0x5966a80() {
   return (neuron0x70c3610()*-0.305445);
}

double TMVAClassification_TMlp_ANN::synapse0x6c95530() {
   return (neuron0x753f310()*-0.175411);
}

double TMVAClassification_TMlp_ANN::synapse0x5966ac0() {
   return (neuron0x5b753e0()*0.181502);
}

double TMVAClassification_TMlp_ANN::synapse0x5b75000() {
   return (neuron0x64be3a0()*0.00913116);
}

double TMVAClassification_TMlp_ANN::synapse0x5b75040() {
   return (neuron0x7ddcd40()*-0.0249344);
}

double TMVAClassification_TMlp_ANN::synapse0x6c95680() {
   return (neuron0x5b8ed90()*0.00363315);
}

double TMVAClassification_TMlp_ANN::synapse0x6c956c0() {
   return (neuron0x6613860()*-0.400079);
}

double TMVAClassification_TMlp_ANN::synapse0x6bfc7e0() {
   return (neuron0x5fa9b00()*0.076972);
}

double TMVAClassification_TMlp_ANN::synapse0x6bfc820() {
   return (neuron0x6e4f550()*0.134749);
}

double TMVAClassification_TMlp_ANN::synapse0x4e80a40() {
   return (neuron0x768b210()*-0.433965);
}

double TMVAClassification_TMlp_ANN::synapse0x4e80a80() {
   return (neuron0x660fe00()*0.198055);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddced0() {
   return (neuron0x5dbd1d0()*-0.0343476);
}

double TMVAClassification_TMlp_ANN::synapse0x7ddcf10() {
   return (neuron0x7c6efd0()*-0.126711);
}

double TMVAClassification_TMlp_ANN::synapse0x5b8efb0() {
   return (neuron0x624f870()*-0.476351);
}

double TMVAClassification_TMlp_ANN::synapse0x5b8eff0() {
   return (neuron0x710cab0()*-0.0341357);
}

double TMVAClassification_TMlp_ANN::synapse0x66139f0() {
   return (neuron0x67c49b0()*-0.0917103);
}

double TMVAClassification_TMlp_ANN::synapse0x6613a30() {
   return (neuron0x77723c0()*-0.363384);
}

double TMVAClassification_TMlp_ANN::synapse0x5fa9c90() {
   return (neuron0x5796be0()*-0.314207);
}

double TMVAClassification_TMlp_ANN::synapse0x5fa9cd0() {
   return (neuron0x68c4f20()*-0.404045);
}

double TMVAClassification_TMlp_ANN::synapse0x6e4f6e0() {
   return (neuron0x5fa3a60()*-0.0953336);
}

double TMVAClassification_TMlp_ANN::synapse0x6e4f720() {
   return (neuron0x58886c0()*-0.353418);
}

double TMVAClassification_TMlp_ANN::synapse0x768b3a0() {
   return (neuron0x6dcd6b0()*-0.270312);
}

double TMVAClassification_TMlp_ANN::synapse0x768b3e0() {
   return (neuron0x7c1a4f0()*0.00727357);
}

double TMVAClassification_TMlp_ANN::synapse0x6610020() {
   return (neuron0x7f702c0()*-0.0840652);
}

double TMVAClassification_TMlp_ANN::synapse0x6610060() {
   return (neuron0x7887220()*0.0258525);
}

double TMVAClassification_TMlp_ANN::synapse0x5dbd3f0() {
   return (neuron0x79caea0()*-0.594601);
}

double TMVAClassification_TMlp_ANN::synapse0x5dbd430() {
   return (neuron0x4d370f0()*-0.490271);
}

double TMVAClassification_TMlp_ANN::synapse0x675c910() {
   return (neuron0x7c7cbb0()*-0.385782);
}

double TMVAClassification_TMlp_ANN::synapse0x675c950() {
   return (neuron0x5751ec0()*0.310127);
}

double TMVAClassification_TMlp_ANN::synapse0x762b620() {
   return (neuron0x7da6470()*0.128275);
}

double TMVAClassification_TMlp_ANN::synapse0x762b660() {
   return (neuron0x6e201f0()*-0.400941);
}

double TMVAClassification_TMlp_ANN::synapse0x710cc40() {
   return (neuron0x7229820()*0.29308);
}

double TMVAClassification_TMlp_ANN::synapse0x710cc80() {
   return (neuron0x5fe5630()*-0.153306);
}

double TMVAClassification_TMlp_ANN::synapse0x67c4b40() {
   return (neuron0x6e364e0()*-0.660181);
}

double TMVAClassification_TMlp_ANN::synapse0x67c4b80() {
   return (neuron0x70c3610()*-0.26033);
}

double TMVAClassification_TMlp_ANN::synapse0x79ca230() {
   return (neuron0x753f310()*-0.303503);
}

double TMVAClassification_TMlp_ANN::synapse0x79ca270() {
   return (neuron0x5b753e0()*0.153605);
}

double TMVAClassification_TMlp_ANN::synapse0x79ca2b0() {
   return (neuron0x64be3a0()*-0.40161);
}

double TMVAClassification_TMlp_ANN::synapse0x79ca2f0() {
   return (neuron0x7ddcd40()*0.232549);
}

double TMVAClassification_TMlp_ANN::synapse0x79ca330() {
   return (neuron0x5b8ed90()*-0.155459);
}

double TMVAClassification_TMlp_ANN::synapse0x6077fe0() {
   return (neuron0x6613860()*-0.136456);
}

double TMVAClassification_TMlp_ANN::synapse0x6078020() {
   return (neuron0x5fa9b00()*-0.133808);
}

double TMVAClassification_TMlp_ANN::synapse0x5fa3bf0() {
   return (neuron0x6e4f550()*-0.504891);
}

double TMVAClassification_TMlp_ANN::synapse0x5fa3c30() {
   return (neuron0x768b210()*-0.0337393);
}

double TMVAClassification_TMlp_ANN::synapse0x5888850() {
   return (neuron0x660fe00()*-0.565164);
}

double TMVAClassification_TMlp_ANN::synapse0x5888890() {
   return (neuron0x5dbd1d0()*-0.190181);
}

double TMVAClassification_TMlp_ANN::synapse0x6dcd840() {
   return (neuron0x7c6efd0()*0.0755387);
}

double TMVAClassification_TMlp_ANN::synapse0x6dcd880() {
   return (neuron0x624f870()*0.119526);
}

double TMVAClassification_TMlp_ANN::synapse0x7c1a680() {
   return (neuron0x710cab0()*-0.141979);
}

double TMVAClassification_TMlp_ANN::synapse0x7c1a6c0() {
   return (neuron0x67c49b0()*-0.267372);
}

double TMVAClassification_TMlp_ANN::synapse0x7f704e0() {
   return (neuron0x77723c0()*-0.413051);
}

double TMVAClassification_TMlp_ANN::synapse0x7f70520() {
   return (neuron0x5796be0()*-0.193429);
}

double TMVAClassification_TMlp_ANN::synapse0x7887440() {
   return (neuron0x68c4f20()*-0.229207);
}

double TMVAClassification_TMlp_ANN::synapse0x7887480() {
   return (neuron0x5fa3a60()*0.0718772);
}

double TMVAClassification_TMlp_ANN::synapse0x78f6770() {
   return (neuron0x58886c0()*-0.595346);
}

double TMVAClassification_TMlp_ANN::synapse0x78f67b0() {
   return (neuron0x6dcd6b0()*-0.142989);
}

double TMVAClassification_TMlp_ANN::synapse0x7519b80() {
   return (neuron0x7c1a4f0()*-0.0477922);
}

double TMVAClassification_TMlp_ANN::synapse0x7519bc0() {
   return (neuron0x7f702c0()*0.0608871);
}

double TMVAClassification_TMlp_ANN::synapse0x7c7cd40() {
   return (neuron0x7887220()*-0.0381555);
}

double TMVAClassification_TMlp_ANN::synapse0x7c7cd80() {
   return (neuron0x79caea0()*0.0323506);
}

double TMVAClassification_TMlp_ANN::synapse0x5752050() {
   return (neuron0x4d370f0()*0.227608);
}

double TMVAClassification_TMlp_ANN::synapse0x5752090() {
   return (neuron0x7c7cbb0()*-0.102274);
}

double TMVAClassification_TMlp_ANN::synapse0x7da6600() {
   return (neuron0x5751ec0()*-0.712892);
}

double TMVAClassification_TMlp_ANN::synapse0x7da6640() {
   return (neuron0x7da6470()*-0.00965484);
}

double TMVAClassification_TMlp_ANN::synapse0x6e20380() {
   return (neuron0x6e201f0()*0.21603);
}

double TMVAClassification_TMlp_ANN::synapse0x6e203c0() {
   return (neuron0x7229820()*-0.465263);
}

double TMVAClassification_TMlp_ANN::synapse0x7229a40() {
   return (neuron0x5fe5630()*-0.466696);
}

double TMVAClassification_TMlp_ANN::synapse0x7229a80() {
   return (neuron0x6e364e0()*-0.353242);
}

double TMVAClassification_TMlp_ANN::synapse0x6a40570() {
   return (neuron0x70c3610()*-0.0395475);
}

double TMVAClassification_TMlp_ANN::synapse0x72cc5d0() {
   return (neuron0x753f310()*0.298295);
}

double TMVAClassification_TMlp_ANN::synapse0x72cc610() {
   return (neuron0x5b753e0()*-0.475001);
}

double TMVAClassification_TMlp_ANN::synapse0x72cc650() {
   return (neuron0x64be3a0()*0.0964242);
}

double TMVAClassification_TMlp_ANN::synapse0x72cc690() {
   return (neuron0x7ddcd40()*-0.0582445);
}

double TMVAClassification_TMlp_ANN::synapse0x72cc6d0() {
   return (neuron0x5b8ed90()*0.00428263);
}

double TMVAClassification_TMlp_ANN::synapse0x72cc710() {
   return (neuron0x6613860()*-0.549523);
}

double TMVAClassification_TMlp_ANN::synapse0x72cc750() {
   return (neuron0x5fa9b00()*-0.0116887);
}

double TMVAClassification_TMlp_ANN::synapse0x6a405b0() {
   return (neuron0x6e4f550()*0.028309);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe57c0() {
   return (neuron0x768b210()*-0.563722);
}

double TMVAClassification_TMlp_ANN::synapse0x5fe5800() {
   return (neuron0x660fe00()*-0.205423);
}

double TMVAClassification_TMlp_ANN::synapse0x59b35f0() {
   return (neuron0x5dbd1d0()*0.0583493);
}

double TMVAClassification_TMlp_ANN::synapse0x59b3630() {
   return (neuron0x7c6efd0()*0.0926591);
}

double TMVAClassification_TMlp_ANN::synapse0x59b3670() {
   return (neuron0x624f870()*-0.44935);
}

double TMVAClassification_TMlp_ANN::synapse0x4cfad50() {
   return (neuron0x710cab0()*0.226203);
}

double TMVAClassification_TMlp_ANN::synapse0x4cfad90() {
   return (neuron0x67c49b0()*-0.304925);
}

double TMVAClassification_TMlp_ANN::synapse0x4cfadd0() {
   return (neuron0x77723c0()*0.138484);
}

double TMVAClassification_TMlp_ANN::synapse0x7cbd5a0() {
   return (neuron0x5796be0()*-0.450986);
}

double TMVAClassification_TMlp_ANN::synapse0x7cbd5e0() {
   return (neuron0x68c4f20()*-0.0133477);
}

double TMVAClassification_TMlp_ANN::synapse0x5af6b80() {
   return (neuron0x5fa3a60()*-0.0761457);
}

double TMVAClassification_TMlp_ANN::synapse0x5af6bc0() {
   return (neuron0x58886c0()*-0.436175);
}

double TMVAClassification_TMlp_ANN::synapse0x5af6c00() {
   return (neuron0x6dcd6b0()*-0.0430247);
}

double TMVAClassification_TMlp_ANN::synapse0x6171c60() {
   return (neuron0x7c1a4f0()*-0.281142);
}

double TMVAClassification_TMlp_ANN::synapse0x6171ca0() {
   return (neuron0x7f702c0()*-0.723016);
}

double TMVAClassification_TMlp_ANN::synapse0x6171ce0() {
   return (neuron0x7887220()*-0.216125);
}

double TMVAClassification_TMlp_ANN::synapse0x5eeaa10() {
   return (neuron0x79caea0()*-0.135424);
}

double TMVAClassification_TMlp_ANN::synapse0x5eeaa50() {
   return (neuron0x4d370f0()*0.0598009);
}

double TMVAClassification_TMlp_ANN::synapse0x5eeaa90() {
   return (neuron0x7c7cbb0()*0.379641);
}

double TMVAClassification_TMlp_ANN::synapse0x63d5750() {
   return (neuron0x5751ec0()*-0.106622);
}

double TMVAClassification_TMlp_ANN::synapse0x63d5790() {
   return (neuron0x7da6470()*0.0932463);
}

double TMVAClassification_TMlp_ANN::synapse0x63d57d0() {
   return (neuron0x6e201f0()*-0.404521);
}

double TMVAClassification_TMlp_ANN::synapse0x63d5810() {
   return (neuron0x7229820()*-0.500532);
}

double TMVAClassification_TMlp_ANN::synapse0x63d5850() {
   return (neuron0x5fe5630()*0.257106);
}

double TMVAClassification_TMlp_ANN::synapse0x72cc090() {
   return (neuron0x6e364e0()*-0.532161);
}

double TMVAClassification_TMlp_ANN::synapse0x72cc0d0() {
   return (neuron0x70c3610()*-0.466293);
}

double TMVAClassification_TMlp_ANN::synapse0x63d5d50() {
   return (neuron0x753f310()*0.142029);
}

double TMVAClassification_TMlp_ANN::synapse0x63d5d90() {
   return (neuron0x5b753e0()*-0.373852);
}

double TMVAClassification_TMlp_ANN::synapse0x63d5dd0() {
   return (neuron0x64be3a0()*-0.162952);
}

double TMVAClassification_TMlp_ANN::synapse0x63d5e10() {
   return (neuron0x7ddcd40()*-0.443878);
}

double TMVAClassification_TMlp_ANN::synapse0x51e80d0() {
   return (neuron0x5b8ed90()*-0.163462);
}

double TMVAClassification_TMlp_ANN::synapse0x51e8110() {
   return (neuron0x6613860()*-0.495755);
}

double TMVAClassification_TMlp_ANN::synapse0x51e8150() {
   return (neuron0x5fa9b00()*-0.707068);
}

double TMVAClassification_TMlp_ANN::synapse0x51e8190() {
   return (neuron0x6e4f550()*0.070196);
}

double TMVAClassification_TMlp_ANN::synapse0x51e81d0() {
   return (neuron0x768b210()*-0.280952);
}

double TMVAClassification_TMlp_ANN::synapse0x51e8210() {
   return (neuron0x660fe00()*-0.760134);
}

double TMVAClassification_TMlp_ANN::synapse0x51e8250() {
   return (neuron0x5dbd1d0()*-0.129758);
}

double TMVAClassification_TMlp_ANN::synapse0x51e8290() {
   return (neuron0x7c6efd0()*-0.115601);
}

double TMVAClassification_TMlp_ANN::synapse0x51e82d0() {
   return (neuron0x624f870()*-0.487034);
}

double TMVAClassification_TMlp_ANN::synapse0x51e8310() {
   return (neuron0x710cab0()*-0.0278383);
}

double TMVAClassification_TMlp_ANN::synapse0x51e8350() {
   return (neuron0x67c49b0()*0.133594);
}

double TMVAClassification_TMlp_ANN::synapse0x51e8390() {
   return (neuron0x77723c0()*0.287022);
}

double TMVAClassification_TMlp_ANN::synapse0x72cc110() {
   return (neuron0x5796be0()*0.223209);
}

double TMVAClassification_TMlp_ANN::synapse0x72cc150() {
   return (neuron0x68c4f20()*-0.487127);
}

double TMVAClassification_TMlp_ANN::synapse0x51e84e0() {
   return (neuron0x5fa3a60()*0.26512);
}

double TMVAClassification_TMlp_ANN::synapse0x51e8520() {
   return (neuron0x58886c0()*-0.590132);
}

double TMVAClassification_TMlp_ANN::synapse0x51e8560() {
   return (neuron0x6dcd6b0()*-0.724147);
}

double TMVAClassification_TMlp_ANN::synapse0x51e85a0() {
   return (neuron0x7c1a4f0()*0.164879);
}

double TMVAClassification_TMlp_ANN::synapse0x51e85e0() {
   return (neuron0x7f702c0()*0.0931459);
}

double TMVAClassification_TMlp_ANN::synapse0x51e8620() {
   return (neuron0x7887220()*0.168617);
}

double TMVAClassification_TMlp_ANN::synapse0x51e8660() {
   return (neuron0x79caea0()*-0.390402);
}

double TMVAClassification_TMlp_ANN::synapse0x51e86a0() {
   return (neuron0x4d370f0()*0.171416);
}

double TMVAClassification_TMlp_ANN::synapse0x51e86e0() {
   return (neuron0x7c7cbb0()*0.416991);
}

double TMVAClassification_TMlp_ANN::synapse0x51e8720() {
   return (neuron0x5751ec0()*-0.491384);
}

double TMVAClassification_TMlp_ANN::synapse0x51e8760() {
   return (neuron0x7da6470()*-0.126125);
}

double TMVAClassification_TMlp_ANN::synapse0x51e87a0() {
   return (neuron0x6e201f0()*0.0376101);
}

double TMVAClassification_TMlp_ANN::synapse0x57f31a0() {
   return (neuron0x7229820()*0.113862);
}

double TMVAClassification_TMlp_ANN::synapse0x57f31e0() {
   return (neuron0x5fe5630()*-0.536385);
}

double TMVAClassification_TMlp_ANN::synapse0x51e83d0() {
   return (neuron0x6e364e0()*-0.351241);
}

double TMVAClassification_TMlp_ANN::synapse0x51e8410() {
   return (neuron0x70c3610()*-0.263317);
}

double TMVAClassification_TMlp_ANN::synapse0x57f36e0() {
   return (neuron0x753f310()*0.0076921);
}

double TMVAClassification_TMlp_ANN::synapse0x57f3720() {
   return (neuron0x5b753e0()*-0.688466);
}

double TMVAClassification_TMlp_ANN::synapse0x57f3760() {
   return (neuron0x64be3a0()*-0.374032);
}

double TMVAClassification_TMlp_ANN::synapse0x57f37a0() {
   return (neuron0x7ddcd40()*-0.145179);
}

double TMVAClassification_TMlp_ANN::synapse0x57f37e0() {
   return (neuron0x5b8ed90()*0.0688948);
}

double TMVAClassification_TMlp_ANN::synapse0x57f3820() {
   return (neuron0x6613860()*-0.122014);
}

double TMVAClassification_TMlp_ANN::synapse0x57f3860() {
   return (neuron0x5fa9b00()*-1.27853);
}

double TMVAClassification_TMlp_ANN::synapse0x753e3f0() {
   return (neuron0x6e4f550()*0.0785668);
}

double TMVAClassification_TMlp_ANN::synapse0x753e430() {
   return (neuron0x768b210()*-0.118586);
}

double TMVAClassification_TMlp_ANN::synapse0x753e470() {
   return (neuron0x660fe00()*-0.274114);
}

double TMVAClassification_TMlp_ANN::synapse0x753e4b0() {
   return (neuron0x5dbd1d0()*-0.0918381);
}

double TMVAClassification_TMlp_ANN::synapse0x753e4f0() {
   return (neuron0x7c6efd0()*0.508635);
}

double TMVAClassification_TMlp_ANN::synapse0x753e530() {
   return (neuron0x624f870()*0.418976);
}

double TMVAClassification_TMlp_ANN::synapse0x753e570() {
   return (neuron0x710cab0()*-0.371836);
}

double TMVAClassification_TMlp_ANN::synapse0x753e5b0() {
   return (neuron0x67c49b0()*0.454888);
}

double TMVAClassification_TMlp_ANN::synapse0x753e5f0() {
   return (neuron0x77723c0()*-0.677873);
}

double TMVAClassification_TMlp_ANN::synapse0x51e8450() {
   return (neuron0x5796be0()*-0.708925);
}

double TMVAClassification_TMlp_ANN::synapse0x51e8490() {
   return (neuron0x68c4f20()*0.287115);
}

double TMVAClassification_TMlp_ANN::synapse0x753e740() {
   return (neuron0x5fa3a60()*-0.299834);
}

double TMVAClassification_TMlp_ANN::synapse0x753e780() {
   return (neuron0x58886c0()*-0.426403);
}

double TMVAClassification_TMlp_ANN::synapse0x753e7c0() {
   return (neuron0x6dcd6b0()*-0.846196);
}

double TMVAClassification_TMlp_ANN::synapse0x753e800() {
   return (neuron0x7c1a4f0()*-0.168708);
}

double TMVAClassification_TMlp_ANN::synapse0x753e840() {
   return (neuron0x7f702c0()*-0.309891);
}

double TMVAClassification_TMlp_ANN::synapse0x753e880() {
   return (neuron0x7887220()*0.257156);
}

double TMVAClassification_TMlp_ANN::synapse0x753e8c0() {
   return (neuron0x79caea0()*-0.637085);
}

double TMVAClassification_TMlp_ANN::synapse0x753e900() {
   return (neuron0x4d370f0()*0.320355);
}

double TMVAClassification_TMlp_ANN::synapse0x753e940() {
   return (neuron0x7c7cbb0()*-0.502291);
}

double TMVAClassification_TMlp_ANN::synapse0x753e980() {
   return (neuron0x5751ec0()*0.28095);
}

double TMVAClassification_TMlp_ANN::synapse0x753e9c0() {
   return (neuron0x7da6470()*-0.782034);
}

double TMVAClassification_TMlp_ANN::synapse0x753ea00() {
   return (neuron0x6e201f0()*-0.271069);
}

double TMVAClassification_TMlp_ANN::synapse0x753ea40() {
   return (neuron0x7229820()*0.617541);
}

double TMVAClassification_TMlp_ANN::synapse0x753ea80() {
   return (neuron0x5fe5630()*-0.178639);
}

double TMVAClassification_TMlp_ANN::synapse0x753eac0() {
   return (neuron0x6e364e0()*-1.35833);
}

double TMVAClassification_TMlp_ANN::synapse0x753e630() {
   return (neuron0x70c3610()*-0.0154749);
}

double TMVAClassification_TMlp_ANN::synapse0x54a8d90() {
   return (neuron0x753f310()*0.0230026);
}

double TMVAClassification_TMlp_ANN::synapse0x54a8dd0() {
   return (neuron0x5b753e0()*-0.0909164);
}

double TMVAClassification_TMlp_ANN::synapse0x54a8e10() {
   return (neuron0x64be3a0()*-0.429225);
}

double TMVAClassification_TMlp_ANN::synapse0x54a8e50() {
   return (neuron0x7ddcd40()*-0.393014);
}

double TMVAClassification_TMlp_ANN::synapse0x54a8e90() {
   return (neuron0x5b8ed90()*-0.16105);
}

double TMVAClassification_TMlp_ANN::synapse0x54a8ed0() {
   return (neuron0x6613860()*-0.00315776);
}

double TMVAClassification_TMlp_ANN::synapse0x54a8f10() {
   return (neuron0x5fa9b00()*-0.0280385);
}

double TMVAClassification_TMlp_ANN::synapse0x753e670() {
   return (neuron0x6e4f550()*0.245754);
}

double TMVAClassification_TMlp_ANN::synapse0x753e6b0() {
   return (neuron0x768b210()*0.168687);
}

double TMVAClassification_TMlp_ANN::synapse0x753e6f0() {
   return (neuron0x660fe00()*-0.370434);
}

double TMVAClassification_TMlp_ANN::synapse0x756be30() {
   return (neuron0x5dbd1d0()*0.208078);
}

double TMVAClassification_TMlp_ANN::synapse0x756be70() {
   return (neuron0x7c6efd0()*0.261147);
}

double TMVAClassification_TMlp_ANN::synapse0x756beb0() {
   return (neuron0x624f870()*-0.124907);
}

double TMVAClassification_TMlp_ANN::synapse0x756bef0() {
   return (neuron0x710cab0()*0.130972);
}

double TMVAClassification_TMlp_ANN::synapse0x756bf30() {
   return (neuron0x67c49b0()*-0.00202953);
}

double TMVAClassification_TMlp_ANN::synapse0x756bf70() {
   return (neuron0x77723c0()*-0.287643);
}

double TMVAClassification_TMlp_ANN::synapse0x54a8be0() {
   return (neuron0x5796be0()*-0.0397434);
}

double TMVAClassification_TMlp_ANN::synapse0x54a8c20() {
   return (neuron0x68c4f20()*-0.704307);
}

double TMVAClassification_TMlp_ANN::synapse0x756c0c0() {
   return (neuron0x5fa3a60()*-0.514962);
}

double TMVAClassification_TMlp_ANN::synapse0x756c100() {
   return (neuron0x58886c0()*-0.114412);
}

double TMVAClassification_TMlp_ANN::synapse0x756c140() {
   return (neuron0x6dcd6b0()*-0.608291);
}

double TMVAClassification_TMlp_ANN::synapse0x756c180() {
   return (neuron0x7c1a4f0()*-0.158333);
}

double TMVAClassification_TMlp_ANN::synapse0x756c1c0() {
   return (neuron0x7f702c0()*-0.398371);
}

double TMVAClassification_TMlp_ANN::synapse0x756c200() {
   return (neuron0x7887220()*0.252303);
}

double TMVAClassification_TMlp_ANN::synapse0x756c240() {
   return (neuron0x79caea0()*-0.38209);
}

double TMVAClassification_TMlp_ANN::synapse0x756c280() {
   return (neuron0x4d370f0()*-0.570655);
}

double TMVAClassification_TMlp_ANN::synapse0x756c2c0() {
   return (neuron0x7c7cbb0()*-0.0908046);
}

double TMVAClassification_TMlp_ANN::synapse0x756c300() {
   return (neuron0x5751ec0()*0.137843);
}

double TMVAClassification_TMlp_ANN::synapse0x756c340() {
   return (neuron0x7da6470()*0.0502175);
}

double TMVAClassification_TMlp_ANN::synapse0x756c380() {
   return (neuron0x6e201f0()*-0.313693);
}

double TMVAClassification_TMlp_ANN::synapse0x756c3c0() {
   return (neuron0x7229820()*-0.130444);
}

double TMVAClassification_TMlp_ANN::synapse0x756c400() {
   return (neuron0x5fe5630()*-0.673637);
}

double TMVAClassification_TMlp_ANN::synapse0x756bfb0() {
   return (neuron0x6e364e0()*-0.02686);
}

double TMVAClassification_TMlp_ANN::synapse0x756bff0() {
   return (neuron0x70c3610()*-0.540898);
}

double TMVAClassification_TMlp_ANN::synapse0x71c4a40() {
   return (neuron0x753f310()*0.467872);
}

double TMVAClassification_TMlp_ANN::synapse0x71c4a80() {
   return (neuron0x5b753e0()*0.399359);
}

double TMVAClassification_TMlp_ANN::synapse0x71c4ac0() {
   return (neuron0x64be3a0()*-1.06243);
}

double TMVAClassification_TMlp_ANN::synapse0x71c4b00() {
   return (neuron0x7ddcd40()*-0.398532);
}

double TMVAClassification_TMlp_ANN::synapse0x71c4b40() {
   return (neuron0x5b8ed90()*-0.194551);
}

double TMVAClassification_TMlp_ANN::synapse0x71c4b80() {
   return (neuron0x6613860()*0.189396);
}

double TMVAClassification_TMlp_ANN::synapse0x71c4bc0() {
   return (neuron0x5fa9b00()*-0.991902);
}

double TMVAClassification_TMlp_ANN::synapse0x71c4c00() {
   return (neuron0x6e4f550()*-1.03359);
}

double TMVAClassification_TMlp_ANN::synapse0x71c4c40() {
   return (neuron0x768b210()*-0.444619);
}

double TMVAClassification_TMlp_ANN::synapse0x756c440() {
   return (neuron0x660fe00()*-0.74689);
}

double TMVAClassification_TMlp_ANN::synapse0x756c480() {
   return (neuron0x5dbd1d0()*-0.860259);
}

double TMVAClassification_TMlp_ANN::synapse0x756c4c0() {
   return (neuron0x7c6efd0()*-0.773405);
}

double TMVAClassification_TMlp_ANN::synapse0x756c500() {
   return (neuron0x624f870()*0.647483);
}

double TMVAClassification_TMlp_ANN::synapse0x61e2380() {
   return (neuron0x710cab0()*-0.68635);
}

double TMVAClassification_TMlp_ANN::synapse0x61e23c0() {
   return (neuron0x67c49b0()*-0.87104);
}

double TMVAClassification_TMlp_ANN::synapse0x61e2400() {
   return (neuron0x77723c0()*0.279837);
}

double TMVAClassification_TMlp_ANN::synapse0x756c030() {
   return (neuron0x5796be0()*-0.47445);
}

double TMVAClassification_TMlp_ANN::synapse0x756c070() {
   return (neuron0x68c4f20()*0.387575);
}

double TMVAClassification_TMlp_ANN::synapse0x61e2550() {
   return (neuron0x5fa3a60()*-0.427749);
}

double TMVAClassification_TMlp_ANN::synapse0x61e2590() {
   return (neuron0x58886c0()*0.218407);
}

double TMVAClassification_TMlp_ANN::synapse0x61e25d0() {
   return (neuron0x6dcd6b0()*-0.838378);
}

double TMVAClassification_TMlp_ANN::synapse0x61e2610() {
   return (neuron0x7c1a4f0()*-0.963643);
}

double TMVAClassification_TMlp_ANN::synapse0x61e2650() {
   return (neuron0x7f702c0()*-0.810261);
}

double TMVAClassification_TMlp_ANN::synapse0x61e2690() {
   return (neuron0x7887220()*-0.0791534);
}

double TMVAClassification_TMlp_ANN::synapse0x61e26d0() {
   return (neuron0x79caea0()*0.307639);
}

double TMVAClassification_TMlp_ANN::synapse0x61e2710() {
   return (neuron0x4d370f0()*-0.00130441);
}

double TMVAClassification_TMlp_ANN::synapse0x61e2750() {
   return (neuron0x7c7cbb0()*-0.348168);
}

double TMVAClassification_TMlp_ANN::synapse0x61e2790() {
   return (neuron0x5751ec0()*-0.0693646);
}

double TMVAClassification_TMlp_ANN::synapse0x61e27d0() {
   return (neuron0x7da6470()*-0.818704);
}

double TMVAClassification_TMlp_ANN::synapse0x61e2810() {
   return (neuron0x6e201f0()*-0.195672);
}

double TMVAClassification_TMlp_ANN::synapse0x61e2850() {
   return (neuron0x7229820()*0.352016);
}

double TMVAClassification_TMlp_ANN::synapse0x61e2890() {
   return (neuron0x5fe5630()*0.38994);
}

double TMVAClassification_TMlp_ANN::synapse0x61e2440() {
   return (neuron0x6e364e0()*0.721789);
}

double TMVAClassification_TMlp_ANN::synapse0x61e2480() {
   return (neuron0x70c3610()*0.309139);
}

double TMVAClassification_TMlp_ANN::synapse0x79306f0() {
   return (neuron0x753f310()*-0.305378);
}

double TMVAClassification_TMlp_ANN::synapse0x7930730() {
   return (neuron0x5b753e0()*-0.181831);
}

double TMVAClassification_TMlp_ANN::synapse0x7930770() {
   return (neuron0x64be3a0()*-0.774398);
}

double TMVAClassification_TMlp_ANN::synapse0x79307b0() {
   return (neuron0x7ddcd40()*-0.287271);
}

double TMVAClassification_TMlp_ANN::synapse0x79307f0() {
   return (neuron0x5b8ed90()*0.303688);
}

double TMVAClassification_TMlp_ANN::synapse0x7930830() {
   return (neuron0x6613860()*-0.115781);
}

double TMVAClassification_TMlp_ANN::synapse0x7930870() {
   return (neuron0x5fa9b00()*-0.589133);
}

double TMVAClassification_TMlp_ANN::synapse0x79308b0() {
   return (neuron0x6e4f550()*0.393131);
}

double TMVAClassification_TMlp_ANN::synapse0x79308f0() {
   return (neuron0x768b210()*0.047877);
}

double TMVAClassification_TMlp_ANN::synapse0x7930930() {
   return (neuron0x660fe00()*-0.890589);
}

double TMVAClassification_TMlp_ANN::synapse0x7930970() {
   return (neuron0x5dbd1d0()*-0.469997);
}

double TMVAClassification_TMlp_ANN::synapse0x79309b0() {
   return (neuron0x7c6efd0()*0.0691343);
}

double TMVAClassification_TMlp_ANN::synapse0x79309f0() {
   return (neuron0x624f870()*-0.479087);
}

double TMVAClassification_TMlp_ANN::synapse0x7930a30() {
   return (neuron0x710cab0()*-0.414082);
}

double TMVAClassification_TMlp_ANN::synapse0x7930a70() {
   return (neuron0x67c49b0()*0.253869);
}

double TMVAClassification_TMlp_ANN::synapse0x7930ab0() {
   return (neuron0x77723c0()*0.0318295);
}

double TMVAClassification_TMlp_ANN::synapse0x61e2a60() {
   return (neuron0x5796be0()*0.456279);
}

double TMVAClassification_TMlp_ANN::synapse0x61e24c0() {
   return (neuron0x68c4f20()*-0.356058);
}

double TMVAClassification_TMlp_ANN::synapse0x61e2500() {
   return (neuron0x5fa3a60()*-0.406613);
}

double TMVAClassification_TMlp_ANN::synapse0x4cc4af0() {
   return (neuron0x58886c0()*0.104476);
}

double TMVAClassification_TMlp_ANN::synapse0x4cc4b30() {
   return (neuron0x6dcd6b0()*-0.385787);
}

double TMVAClassification_TMlp_ANN::synapse0x4cc4b70() {
   return (neuron0x7c1a4f0()*0.182652);
}

double TMVAClassification_TMlp_ANN::synapse0x4cc4bb0() {
   return (neuron0x7f702c0()*-0.383399);
}

double TMVAClassification_TMlp_ANN::synapse0x4cc4bf0() {
   return (neuron0x7887220()*-0.223826);
}

double TMVAClassification_TMlp_ANN::synapse0x4cc4c30() {
   return (neuron0x79caea0()*-0.306138);
}

double TMVAClassification_TMlp_ANN::synapse0x4cc4c70() {
   return (neuron0x4d370f0()*-0.297388);
}

double TMVAClassification_TMlp_ANN::synapse0x4cc4cb0() {
   return (neuron0x7c7cbb0()*0.238346);
}

double TMVAClassification_TMlp_ANN::synapse0x4cc4cf0() {
   return (neuron0x5751ec0()*-0.395177);
}

double TMVAClassification_TMlp_ANN::synapse0x4cc4d30() {
   return (neuron0x7da6470()*-0.860114);
}

double TMVAClassification_TMlp_ANN::synapse0x4cc4d70() {
   return (neuron0x6e201f0()*0.113644);
}

double TMVAClassification_TMlp_ANN::synapse0x4cc4db0() {
   return (neuron0x7229820()*0.0535062);
}

double TMVAClassification_TMlp_ANN::synapse0x4cc4df0() {
   return (neuron0x5fe5630()*-0.637667);
}

double TMVAClassification_TMlp_ANN::synapse0x4cc5040() {
   return (neuron0x6e364e0()*-0.20693);
}

double TMVAClassification_TMlp_ANN::synapse0x4cc5080() {
   return (neuron0x70c3610()*0.268485);
}

double TMVAClassification_TMlp_ANN::synapse0x710e2a0() {
   return (neuron0x753f310()*-0.469601);
}

double TMVAClassification_TMlp_ANN::synapse0x710e2e0() {
   return (neuron0x5b753e0()*-0.271182);
}

double TMVAClassification_TMlp_ANN::synapse0x710e320() {
   return (neuron0x64be3a0()*0.0261393);
}

double TMVAClassification_TMlp_ANN::synapse0x710e360() {
   return (neuron0x7ddcd40()*-0.465796);
}

double TMVAClassification_TMlp_ANN::synapse0x710e3a0() {
   return (neuron0x5b8ed90()*-0.198035);
}

double TMVAClassification_TMlp_ANN::synapse0x710e3e0() {
   return (neuron0x6613860()*0.233111);
}

double TMVAClassification_TMlp_ANN::synapse0x710e420() {
   return (neuron0x5fa9b00()*-0.516852);
}

double TMVAClassification_TMlp_ANN::synapse0x710e460() {
   return (neuron0x6e4f550()*0.175794);
}

double TMVAClassification_TMlp_ANN::synapse0x710e4a0() {
   return (neuron0x768b210()*0.210488);
}

double TMVAClassification_TMlp_ANN::synapse0x710e4e0() {
   return (neuron0x660fe00()*-0.292058);
}

double TMVAClassification_TMlp_ANN::synapse0x710e520() {
   return (neuron0x5dbd1d0()*-0.101691);
}

double TMVAClassification_TMlp_ANN::synapse0x710e560() {
   return (neuron0x7c6efd0()*-0.459424);
}

double TMVAClassification_TMlp_ANN::synapse0x710e5a0() {
   return (neuron0x624f870()*-0.604955);
}

double TMVAClassification_TMlp_ANN::synapse0x710e5e0() {
   return (neuron0x710cab0()*-0.298498);
}

double TMVAClassification_TMlp_ANN::synapse0x710e620() {
   return (neuron0x67c49b0()*-0.178466);
}

double TMVAClassification_TMlp_ANN::synapse0x4cc50c0() {
   return (neuron0x77723c0()*-0.101039);
}

double TMVAClassification_TMlp_ANN::synapse0x710e0f0() {
   return (neuron0x5796be0()*-0.559533);
}

double TMVAClassification_TMlp_ANN::synapse0x710e130() {
   return (neuron0x68c4f20()*-0.438451);
}

double TMVAClassification_TMlp_ANN::synapse0x7c64260() {
   return (neuron0x5fa3a60()*-0.651189);
}

double TMVAClassification_TMlp_ANN::synapse0x7c642a0() {
   return (neuron0x58886c0()*-0.434826);
}

double TMVAClassification_TMlp_ANN::synapse0x7c642e0() {
   return (neuron0x6dcd6b0()*-0.153646);
}

double TMVAClassification_TMlp_ANN::synapse0x7c64320() {
   return (neuron0x7c1a4f0()*0.183083);
}

double TMVAClassification_TMlp_ANN::synapse0x7c64360() {
   return (neuron0x7f702c0()*-0.534557);
}

double TMVAClassification_TMlp_ANN::synapse0x7c643a0() {
   return (neuron0x7887220()*0.029663);
}

double TMVAClassification_TMlp_ANN::synapse0x7c643e0() {
   return (neuron0x79caea0()*0.0773759);
}

double TMVAClassification_TMlp_ANN::synapse0x7c64420() {
   return (neuron0x4d370f0()*0.0245837);
}

double TMVAClassification_TMlp_ANN::synapse0x7c64460() {
   return (neuron0x7c7cbb0()*0.266721);
}

double TMVAClassification_TMlp_ANN::synapse0x7c644a0() {
   return (neuron0x5751ec0()*-0.289971);
}

double TMVAClassification_TMlp_ANN::synapse0x7c644e0() {
   return (neuron0x7da6470()*0.21588);
}

double TMVAClassification_TMlp_ANN::synapse0x7c64520() {
   return (neuron0x6e201f0()*-0.30253);
}

double TMVAClassification_TMlp_ANN::synapse0x7c64560() {
   return (neuron0x7229820()*-0.245142);
}

double TMVAClassification_TMlp_ANN::synapse0x7c645a0() {
   return (neuron0x5fe5630()*-0.320533);
}

double TMVAClassification_TMlp_ANN::synapse0x4cc49e0() {
   return (neuron0x6e364e0()*-0.0253495);
}

double TMVAClassification_TMlp_ANN::synapse0x4cc4a20() {
   return (neuron0x70c3610()*0.146177);
}

double TMVAClassification_TMlp_ANN::synapse0x4c013a0() {
   return (neuron0x751a4c0()*-0.145741);
}

double TMVAClassification_TMlp_ANN::synapse0x5e95540() {
   return (neuron0x5932aa0()*-0.00131713);
}

double TMVAClassification_TMlp_ANN::synapse0x5e95580() {
   return (neuron0x71dbc80()*-0.0437446);
}

double TMVAClassification_TMlp_ANN::synapse0x5e955c0() {
   return (neuron0x4fdac50()*0.287157);
}

double TMVAClassification_TMlp_ANN::synapse0x5e95600() {
   return (neuron0x5bb2020()*-0.168311);
}

double TMVAClassification_TMlp_ANN::synapse0x5e95640() {
   return (neuron0x6debd60()*-0.155307);
}

double TMVAClassification_TMlp_ANN::synapse0x5e95680() {
   return (neuron0x4d683c0()*1.97267);
}

double TMVAClassification_TMlp_ANN::synapse0x5e956c0() {
   return (neuron0x6ab8520()*0.254135);
}

double TMVAClassification_TMlp_ANN::synapse0x5e95700() {
   return (neuron0x5fcaf50()*-0.230921);
}

double TMVAClassification_TMlp_ANN::synapse0x5e95740() {
   return (neuron0x63968b0()*-0.231831);
}

double TMVAClassification_TMlp_ANN::synapse0x5e95780() {
   return (neuron0x7766990()*-0.0668302);
}

double TMVAClassification_TMlp_ANN::synapse0x5e957c0() {
   return (neuron0x5d66d70()*-0.144979);
}

double TMVAClassification_TMlp_ANN::synapse0x5e95800() {
   return (neuron0x4ef8710()*0.157836);
}

double TMVAClassification_TMlp_ANN::synapse0x5e95840() {
   return (neuron0x6479540()*-0.212219);
}

double TMVAClassification_TMlp_ANN::synapse0x5e95880() {
   return (neuron0x56e4150()*0.238579);
}

double TMVAClassification_TMlp_ANN::synapse0x5e958c0() {
   return (neuron0x6c951f0()*0.209186);
}

double TMVAClassification_TMlp_ANN::synapse0x4cc4a60() {
   return (neuron0x79ca0a0()*0.228157);
}

double TMVAClassification_TMlp_ANN::synapse0x4cc4aa0() {
   return (neuron0x72cc3b0()*-0.102585);
}

double TMVAClassification_TMlp_ANN::synapse0x5e95a10() {
   return (neuron0x63d5aa0()*-0.349864);
}

double TMVAClassification_TMlp_ANN::synapse0x5e95a50() {
   return (neuron0x57f3430()*-1.14135);
}

double TMVAClassification_TMlp_ANN::synapse0x5e95a90() {
   return (neuron0x54a8a50()*0.008708);
}

double TMVAClassification_TMlp_ANN::synapse0x5e95ad0() {
   return (neuron0x71c4790()*1.68605);
}

double TMVAClassification_TMlp_ANN::synapse0x5e95b10() {
   return (neuron0x61e28d0()*-0.606272);
}

double TMVAClassification_TMlp_ANN::synapse0x5e95b50() {
   return (neuron0x710df60()*-0.0193622);
}

