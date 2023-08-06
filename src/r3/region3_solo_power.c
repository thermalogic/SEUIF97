/*
  The solo power in region 3
   -   use Horner’s rule to get the soI_pow,soJ_pow quickly
 */ 
void solo_i_j_power_reg3(double vi, double vj, double soI_pow[], double soJ_pow[])
{
    // [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11];
    soI_pow[0] = 1.0;
    for (int k = 1; k <= 12; k++)
    {
        soI_pow[k] = soI_pow[k - 1] * vi;
    }

    // j  [0, 1, 2, 7, 10, 12, 23, 6, 15, 17, 22, 26, 4, 16, 3];
    soJ_pow[0] = 1.0;
    soJ_pow[1] = vj;
    soJ_pow[2] = vj * vj;

    double J_pow3 = soJ_pow[1] * soJ_pow[2];
    double J_pow4 = soJ_pow[2] * soJ_pow[2];

    soJ_pow[3] = J_pow3 * J_pow4;         // 7
    soJ_pow[4] = J_pow3 * soJ_pow[3];     // 10
    soJ_pow[5] = soJ_pow[4] * soJ_pow[2]; // 12

    double J_pow22 = soJ_pow[5] * soJ_pow[4];

    soJ_pow[6] = J_pow22 * vj;            // 23
    soJ_pow[7] = J_pow3 * J_pow3;         // 6
    soJ_pow[8] = J_pow3 * soJ_pow[5];     // 15
    soJ_pow[9] = soJ_pow[8] * soJ_pow[2]; // 17
    soJ_pow[10] = J_pow22;                // 22

    soJ_pow[11] = J_pow22 * J_pow4; // 26
    soJ_pow[12] = J_pow4;           // 4
    soJ_pow[13] = soJ_pow[8] * vj;  // 16
    soJ_pow[14] = J_pow3;           // 3
}
