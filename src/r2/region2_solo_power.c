/*
 the solo powers in region2
*/
#include "../algo/algorithm.h"
#include "region2.h"
#include "region2_coff.h"
#include "region2_solo_ij.h"

void solo_i_j_power_reg2(double vi, double vj, double soI_pow[], double soJ_pow[])
{
  //  [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 18, 20, 21, 22, 23, 24];
  soI_pow[0] = vi;
  for (int k = 1; k <= 9; k++)
  {
    soI_pow[k] = soI_pow[k - 1] * vi;
  }
  double vi2 = vi * vi;
  soI_pow[10] = soI_pow[9] * vi2 * vi2 * vi2;
  soI_pow[11] = soI_pow[10] * vi2;
  soI_pow[12] = soI_pow[11] * vi2;
  for (int k = 13; k <= 16; k++)
  {
    soI_pow[k] = soI_pow[k - 1] * vi;
  }

  //  0, 1, 2, 3, 6, 4, 7, 36, 35, 16, 11, 25, 8, 13, 10, 14, 29, 50, 57, 20, 48, 21, 53, 39, 26, 40,  58,

  soJ_pow[0] = 1.0;                     // 0
  soJ_pow[1] = vj;                      // 1
  soJ_pow[2] = vj * vj;                 // 2
  soJ_pow[3] = vj * soJ_pow[2];         // 3
  soJ_pow[4] = soJ_pow[3] * soJ_pow[3]; // 6

  soJ_pow[5] = soJ_pow[3] * vj; // 4
  soJ_pow[6] = soJ_pow[4] * vj; // 7

  double J_pow8 = soJ_pow[6] * vj;
  double J_pow10 = J_pow8 * soJ_pow[2];
  double J_pow11 = J_pow8 * soJ_pow[3];
  double J_pow16 = J_pow10 * soJ_pow[4];
  double J_pow20 = J_pow10 * J_pow10;

  soJ_pow[7] = J_pow20 * J_pow16; // 36
  soJ_pow[8] = soJ_pow[7] / vj;   // 35
  soJ_pow[9] = J_pow16;           // 16
  soJ_pow[10] = J_pow11;          // 11

  soJ_pow[11] = soJ_pow[8] / J_pow10; // 25
  soJ_pow[12] = J_pow8;               // 8
  soJ_pow[13] = J_pow10 * soJ_pow[3]; // 13
  soJ_pow[14] = J_pow10;              // 10
  soJ_pow[15] = J_pow10 * soJ_pow[5]; // 14

  soJ_pow[16] = J_pow16 * soJ_pow[13];    // 29
  soJ_pow[17] = soJ_pow[7] * soJ_pow[15]; // 50
  soJ_pow[18] = soJ_pow[17] * soJ_pow[6]; // 57
  soJ_pow[19] = J_pow20;                  // 20
  soJ_pow[20] = soJ_pow[8] * soJ_pow[13]; // 48

  soJ_pow[21] = J_pow20 * vj;             // 21
  soJ_pow[22] = soJ_pow[17] * soJ_pow[3]; // 53
  soJ_pow[23] = soJ_pow[7] * soJ_pow[3];  // 39
  soJ_pow[24] = soJ_pow[11] * vj;         // 26
  soJ_pow[25] = J_pow20 * J_pow20;        // 40
  soJ_pow[26] = soJ_pow[18] * vj;         // 58

  // for (int k = 0; k < 27; k++)
  //{
  //   soJ_pow[k] = IPOW(vj, soJ[k]);
  // }
}