/*
   the solo I,j
*/
#pragma once

#include "../algo/algorithm.h"

static const int soI[13] = {0, 1, 2, 3, 4, 5, 8, 21, 23, 29, 30, 31, 32};

static int i2soI[34] = {0, 0, 0, 0, 0,
                      0, 0, 0, 1, 1,
                      1, 1, 1, 1, 2,
                      2, 2, 2, 2, 3,
                      3, 3, 4, 4, 4,
                      5, 6, 6, 7, 8,
                      9, 10, 11, 12};

static const int soJ[25] = {-2, -1, 0, 1, 2, 3, 4, 5, -9, -7, -3, 17, -4, 6, -5, 10,
                            -8, -11, -6, -29, -31, -38, -39, -40, -41};

static int j2soJ[34] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 5, 10, 2, 3, 5, 11, 12, 2,
                      13, 14, 0, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};

void solo_ij_pow_reg1(double vi, double vj, double *soI_pow, double *soJ_pow);