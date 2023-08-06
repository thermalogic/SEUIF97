
#pragma once
#include "../algo/algorithm.h"
#include "../common/common.h"
#include "region2_coff.h"

static const int soI[17] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 18, 20, 21, 22, 23, 24};

static int i2soI[43] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 4, 5, 5, 5,
                        6, 6, 6, 7, 7, 8, 9, 9, 9, 10, 10, 11, 12, 12, 12,
                        13, 14, 15, 16, 16, 16};

static const int soJ[27] = {0, 1, 2, 3, 6, 4, 7,
                            36, 35, 16, 11, 25, 8, 13, 10,
                            14, 29, 50, 57, 20, 48, 21, 53, 39, 26, 40, 58};

static int j2soJ[43] = {0, 1, 2, 3, 4, 1, 2, 5, 6, 7, 0, 1, 3,
                        4, 8, 1, 2, 3, 6, 3, 9, 8, 0, 10, 11, 12, 7, 13, 5, 14, 15,
                        16, 17, 18, 19, 8, 20, 21, 22, 23, 24, 25, 26};

void solo_i_j_power_reg2(double vi, double vj, double soI_pow[], double soJ_pow[]);