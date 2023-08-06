#pragma once
#include "../algo/algorithm.h"
#include "../common/common.h"
#include "region3_coff.h"

static const int soI[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

static int i2soI[39] = {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
                        2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4,
                        5, 5, 5, 6, 6, 6, 7, 8, 9, 9, 10, 10, 11};

static const int soJ[15] = {0, 1, 2, 7, 10, 12, 23, 6, 15, 17, 22, 26, 4, 16, 3};
static int j2soJ[39] = {0, 1, 2, 3, 4, 5, 6, 2, 7, 8, 9, 0, 2,
                        7, 3, 10, 11, 0, 2, 12, 13, 11, 0, 2, 12, 11, 1, 14, 11,
                        0, 2, 11, 2, 11, 2, 11, 0, 1, 11};

void solo_i_j_power_reg3(double vi, double vj, double soI_pow[], double soJ_pow[]);