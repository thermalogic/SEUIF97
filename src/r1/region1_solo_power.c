/*
 The solo powers in region1
*/
#include "../algo/algorithm.h"
#include "region1.h"
#include "region1_coff.h"
#include "region1_solo_ij.h"

void solo_ij_pow_reg1(double vi,double vj,double *soI_pow,double *soJ_pow)
{
    // [0, 1, 2, 3, 4, 5, 8, 21, 23, 29, 30, 31, 32];
   
    soI_pow[0] = 1.0;
    for(int k=1; k<=5;k++) {
        soI_pow[k] = soI_pow[k - 1] * vi;
    }
    double vi2 = vi * vi;
    soI_pow[6] = soI_pow[5] * vi2 * vi; //8
    soI_pow[7] = soI_pow[6] * soI_pow[6] * soI_pow[5]; //21
    soI_pow[8] = soI_pow[7] * vi2; //23
    soI_pow[9] = soI_pow[6] * soI_pow[7];
    for(int k=10; k<=12;k++) {
        soI_pow[k] = soI_pow[k - 1] * vi;
    }

    //  -2, -1, 0, 1, 2, 3, 4, 5, -9, -7, -3, 17, -4, 6, -5, 10, -8, -11, -6, -29, -31, -38, -39, -40, -41,
    double vj2 = vj * vj;
    soJ_pow[0] = 1.0 / vj2; //-2
    soJ_pow[1] = 1.0 / vj; //-1
    soJ_pow[2] = 1.0; // 0
    soJ_pow[3] = vj; // 1
    soJ_pow[4] = vj2; //2
    soJ_pow[5]=soJ_pow[4]*vj; //3
    soJ_pow[6]=soJ_pow[5]*vj;  //4
    soJ_pow[7]=soJ_pow[6]*vj; //5
   
    double J_pow7 = vj2 * soJ_pow[7];
    double J_pow9 = soJ_pow[6] * soJ_pow[7];
    double J_pow10 = J_pow9 *vj;
  
    soJ_pow[8] = 1.0 / J_pow9; //-9
    soJ_pow[9] = 1.0 / J_pow7; // -7
    soJ_pow[10] = 1.0 / soJ_pow[5]; // -3

    soJ_pow[11] = J_pow7 * J_pow10; // 17
    soJ_pow[12] = 1.0 / soJ_pow[6]; // -4
    soJ_pow[13] = soJ_pow[7] * vj; //6
    soJ_pow[14] = 1.0 / soJ_pow[7]; //-5
    soJ_pow[15] = J_pow10; // 10

    soJ_pow[16] = 1.0 / J_pow7/ vj; //-8
    soJ_pow[17] = 1.0 / soJ_pow[15]/ vj; //-11
    soJ_pow[18] = 1.0 / soJ_pow[13]; //-6
    soJ_pow[19] = (1.0 / J_pow10) * soJ_pow[16] * soJ_pow[17]; // -29
    soJ_pow[20] = soJ_pow[19] * soJ_pow[0]; //-31

    soJ_pow[21] = soJ_pow[20] * soJ_pow[9]; //-38
    for(int k=22; k<=24; k++) {
        //  -39, -40, -41
        soJ_pow[k] = soJ_pow[k - 1] / vj;
    }
    
    
    /*for(int k=0; k<13; k++) {
        soI_pow[k] = IPOW(vi, soI[k]);
    }
    for(int k=0; k<25; k++) {
        soJ_pow[k] = IPOW(vj, soJ[k]);
    }*/
}
