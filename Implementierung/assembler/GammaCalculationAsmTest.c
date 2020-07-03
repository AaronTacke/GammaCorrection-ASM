#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "../hardcoded_functions/GammaValues.h"

double* logArray;
double* gammaArray;
double logValues[] = {-1000,-5.5412635451584258,-4.8481163645984813,-4.4426512564903167,-4.1549691840385359,-3.9318256327243257,-3.7495040759303713,-3.5953533961031128,-3.46182200347859,-3.3440389678222067,-3.2386784521643803,-3.1433682723600556,-3.0563568953704259,-2.9763141876968895,-2.9022062155431674,-2.8332133440562162,-2.7686748229186451,-2.7080502011022101,-2.6508917872622613,-2.5968245659919855,-2.5455312716044354,-2.4967411074350032,-2.4502210918001102,-2.4057693292292766,-2.3632097148104805,-2.3223877202902252,-2.2831670071369441,-2.2454266791540971,-2.2090590349832224,-2.1739677151719521,-2.1400661634962708,-2.10727634067328,-2.0755276423586997,-2.044755983691946,-2.0149030205422647,-1.9859154836690123,-1.9577446067023161,-1.9303456325142017,-1.9036773854320403,-1.8777018990287797,-1.8523840910444898,-1.8276914784541183,-1.8035939268750578,-1.7800634294648636,-1.757073911240165,-1.7346010553881064,-1.7126221486693312,-1.6911159434483676,-1.6700625342505353,-1.6494432470477995,-1.62924053973028,-1.6094379124341003,-1.5900198265769987,-1.5709716316063043,-1.5522794985941517,-1.5339303599259553,-1.515911854423277,-1.498212277323876,-1.4808205346120069,-1.4637261012527067,-1.4469189829363254,-1.4303896809851149,-1.4141291601133346,-1.3981288187668934,-1.3823804617987543,-1.3668762752627892,-1.3516088031320006,-1.3365709257674601,-1.3217558399823195,-1.3071570405611668,-1.2927683031090671,-1.2785836681171108,-1.2645974261423709,-1.2508041040100351,-1.2371984519542563,-1.2237754316221157,-1.2105302048720952,-1.1974581233047423,-1.1845547184688343,-1.1718156926914047,-1.1592369104845446,-1.1468143904859875,-1.1345442978941729,-1.1224229373618282,-1.1104467463151126,-1.0986122886681098,-1.0869162489049184,-1.0753554265038423,-1.0639267306802196,-1.0526271754262864,-1.041453874828161,-1.030404038641576,-1.0194749681093858,-1.0086640520051702,-0.99796876288842218,-0.98738665355788524,-0.9769153536905899,-0.96655256665504341,-0.95629606648785415,-0.94614369502383622,-0.93609335917033476,-0.92614302831716677,-0.916290731874155,-0.90653455692879037,-0.89687264601705352,-0.88730319500090282,-0.87782445104635898,-0.86843471069652001,-0.85913231803420642,-0.84991566292928244,-0.84078317936600988,-0.83173334384609199,-0.82276467386333163,-0.81387572644608563,-0.80506509676393068,-0.79633141679517605,-0.78767335405206151,-0.77908961036067004,-0.77057892069276135,-0.76214005204689672,-0.7537718023763802,-0.74547299956168511,-0.73724250042516959,-0.72907918978600861,-0.72098197955338927,-0.71294980785612505,-0.70498163820694815,-0.69707645869983481,-0.689233281238809,-0.68145114079675406,-0.67372909470284381,-0.66606622195727472,-0.65846162257205521,-0.65091441693667229,-0.64342374520751477,-0.63598876671999671,-0.62860865942237421,-0.62128261933030127,-0.61400986000122149,-0.60678961202773452,-0.59962112254912181,-0.59250365478025779,-0.58543648755716537,-0.57841891489851882,-0.57145024558242552,-0.5645298027378518,-0.55765692345008977,-0.55083095837968998,-0.54405127139431098,-0.53731723921296692,-0.53062825106217038,-0.52398370834350183,-0.51738302431214978,-0.51082562376599072,-0.50431094274479704,-0.49783842823917962,-0.49140753790888902,-0.48501773981011803,-0.47866851213145933,-0.47235934293819459,-0.46608972992459924,-0.45985918017396321,-0.45366720992604215,-0.4475133443516639,-0.44139711733422765,-0.4353180712578455,-0.4292757568018829,-0.42326973274167101,-0.41729956575516725,-0.4113648302353527,-0.40546510810816444,-0.3995999886557664,-0.39376906834497305,-0.38797195066064716,-0.38220824594389707,-0.3764775712349121,-0.37077955012027436,-0.36511381258459702,-0.35947999486634108,-0.35387773931767125,-0.3483066942682157,-0.34276651389260038,-0.33725685808163075,-0.3317773923170052,-0.32632778754944053,-0.32090772008010138,-0.31551687144522494,-0.31015492830383962,-0.30482158232847689,-0.29951653009878371,-0.29423947299793995,-0.28899011711179629,-0.28376817313064462,-0.27857335625354063,-0.27340538609509807,-0.26826398659467943,-0.26314888592790886,-0.25805981642043763,-0.25299651446389088,-0.24795872043393374,-0.24294617861038947,-0.23795863709935042,-0.23299584775722143,-0.22805756611663888,-0.22314355131420971,-0.21825356602001794,-0.21338737636884506,-0.20854475189305707,-0.20372546545710818,-0.19892929319361519,-0.19415601444095751,-0.18940541168235972,-0.18467727048641364,-0.17997137944900099,-0.17528753013657464,-0.17062551703076334,-0.16598513747426116,-0.16136619161796661,-0.15676848236933719,-0.15219181534192538,-0.14763599880606457,-0.1431008436406733,-0.13858616328614667,-0.13409177369830738,-0.12961749330338632,-0.12516314295400605,-0.12072854588614031,-0.11631352767702353,-0.11191791620398532,-0.10754154160418647,-0.10318423623523075,-0.098845834636632601,-0.0945261734921162,-0.090225091592725612,-0.085942429800724765,-0.081678031014267238,-0.077431740132816035,-0.073203404023294935,-0.068992871486951435,-0.064799993226915473,-0.060624621816434854,-0.056466611667771179,-0.052325819001739791,-0.048202101817877749,-0.044095319865224233,-0.04000533461369913,-0.035932009226063329,-0.031875208530448951,-0.027834798993443988,-0.023810648693718559,-0.019802627296179754,-0.015810606026642315,-0.011834457647002796,-0.007874056430905883,-0.0039292781398895501};

extern uint8_t* calculateWholeFunction(double gamma, double* logArray, double* gammaArray, uint8_t * functionArray);
extern uint8_t calculateFunctionBinarySearch(double gamma, uint8_t input, double* logValues);


//This method uses binary search to find a correct value for ONE input value
uint8_t calculateResult(float gamma, int input) {
    if (input == 0) return 0;
    double logResult = log((double)(input)/255)*gamma;

    int min = 0;
    int max = 256;
    while (min < max) {

        int middle = (min + max) / 2 +1;
        double logSearch = log(((double)(middle))/255);
        if (logSearch > logResult) {
            max = middle - 1;
        } else {
            min = middle;
        }

    }
    return min;
}

    //Test for the method above.
//int main() {
//    int startValue = 1;
//    for (int i = startValue; i < sizeof(gammaValues) / sizeof(float); ++i) {
//        float gammaValue = gammaValues[i];
//        for (int j = 0; j <= 255; ++j) {
//            uint8_t otherResult = pow((double)j / 255, gammaValue) * 255;
//            uint8_t ourResult = calculateResult(gammaValue, j);
//            if (otherResult != ourResult) {
//                printf("\nwrong j: %d result: %d, expected: %d = %d ^ %e\n", j, ourResult,
//                       otherResult, j, gammaValue);
//            }
//        }
//    }
//}


//This method uses a similar algorithm to the merge-algorith of mergesort
//To find all values (1-254) that belong to one gamma
uint8_t* calculateResultArrayFast(float gamma) {
    //In assembler this is done before (in section .data):
    uint8_t* res = malloc(254*sizeof(uint8_t));

    //xor registers
    int gammaCounter = 0;
    int logCounter = 0;

    //WITH SIMD in memory OR WITHOUT memory
    for(int i = 0; i < 254; i++){
        *(gammaArray+i) = *(logArray+i) * gamma;
    }

    while(gammaCounter<255){
        //Maybe the multiplication with gamma should happen directly here?
        if(*(logArray+logCounter)<*(gammaArray+gammaCounter)){
            logCounter++;
        }else{
            res[gammaCounter] = logCounter;
            gammaCounter++;
        }
    }

    return res;
}

    //Test for the method above.
/*int main() {
    gammaArray = malloc(254 * sizeof(double));

    logArray = malloc(255 * sizeof(double));
    for(int i = 0; i < 254; i++){
        *(logArray+i) = log(((double)(i+1))/255);
    }
    *(logArray+254) = 1.79769e+308;

    int startValue = 0;
    for (int i = startValue; i < sizeof(gammaValues) / sizeof(float); ++i) {
        float gammaValue = gammaValues[i];
        uint8_t* res = calculateResultArrayFast(gammaValue);
        for (int j = 1; j <= 254; ++j) {
            uint8_t otherResult = pow((double)j / 255, gammaValue) * 255;
            if (otherResult != res[j-1]) {
                printf("\nwrong j: %d result: %d, expected: %d = %d ^ %e\n", j, res[j-1],
                       otherResult, j, gammaValue);
            }
        }
    }
}*/


//This method encrypts the Function so it can be stored in 512 bits.
//Still work in progress.
//Question: Will it ever be faster to decrypt it (~512 comparisons) than a cache hit??
int* calculateResultArrayFastEncrypted(float gamma) {
    int* bits = malloc(508);
    printf("\n");

    int gammaCounter = 0;
    int logCounter = 0;

    //WITH SIMD in memory OR WITHOUT memory
    for(int i = 0; i < 254; i++){
        *(gammaArray+i) = *(logArray+i) * gamma;
    }

    for(int i = 0; i < 508; i++){
        if(*(logArray+logCounter)<*(gammaArray+gammaCounter)){
            //0 an i-te Stelle schreiben
            printf("0");
            bits[i] = 0;
            logCounter++;
        }else{
            //1 and i-te Stelle schreiben
            printf("1");
            bits[i] = 1;
            gammaCounter++;
        }
    }

    printf("\n");
    return bits;
}
void testAssemblerCalculateWholeFunction(){
    gammaArray = malloc(254 * sizeof(double));
    uint8_t* resultArray = malloc(254 * sizeof(uint8_t));

    logArray = malloc(255 * sizeof(double));
    for(int i = 0; i < 254; i++){
        *(logArray+i) = log(((double)(i+1))/255);
    }
    *(logArray+254) = 1.79769e+308;
    int startValue = 1;
    for (int i = startValue; i < sizeof(gammaValues) / sizeof(float); ++i) {
        float gammaValue = gammaValues[i];
        uint8_t* resC = calculateResultArrayFast(gammaValue);
        uint8_t* resASM = calculateWholeFunction(gammaValue, logArray, gammaArray, resultArray);
        for (int j = 0; j <= 254; ++j) {
            if (resC[j] != resASM[j]){
                printf("error with j=%d g=%e expected %d, got %d\n", j, gammaValue, resC[j], resASM[j]);
            }
        }
    }
}
void testAssemblerCalculateFunctionBinarySearch(){
   int startValue = 1;
    for (int i = startValue; i < sizeof(gammaValues) / sizeof(float); ++i) {
        float gamma = gammaValues[i];
        for (int j = 0; j < 255; ++j) {
            uint8_t assemblerResult = calculateFunctionBinarySearch(gamma, j, logValues);
            uint8_t cResult = calculateResult(gamma, j);
            if (assemblerResult != cResult){
                printf("error with g=%e j=%d expected %d, got %d\n",gamma, j, cResult, assemblerResult);
            }
        }
    }
}


int main(){
    //testAssemblerCalculateFunctionBinarySearch();
    testAssemblerCalculateWholeFunction();
}

    //Test for the method above.
//int main(){
//    gammaArray = malloc(255 * sizeof(double));
//    *(gammaArray+254) = -1.79769e+308;
//
//    logArray = malloc(255 * sizeof(double));
//    for(int i = 0; i < 254; i++){
//        *(logArray+i) = log(((double)(i+1))/255);
//    }
//    *(logArray+254) = 1.79769e+308;
//
//    float gamma = 1;
//    calculateResultArrayFastEncrypted(gamma);
//
//}
