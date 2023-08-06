#include "../src/common/seuif97.h"
#include "../src/common/propertry_id.h"
#include "../Unity/unity.h"
#include "../src/r1/region1.h"
#include "../src/r2/region2.h"
#include "../src/r3/region3.h"
#include "../src/r4/region4.h"
#include "../src/r5/region5.h"
#include "if97_data.h"

void setUp(void) {}

void tearDown(void) {}

void test_th_reg1(void)
{

  for (int i = 0; i < 3; i++)
  {
    double t = r1_pT[i].T-273.15;
    double h = r1_pT[i].h;
    TEST_ASSERT_EQUAL_FLOAT(r1_pT[i].p, seuth(t,h,OP));
  }
}

void test_th_reg2(void)
{

  for (int i = 0; i < 3; i++)
  {
    double t = r2_pT[i].T-273.15;
    double h = r2_pT[i].h;
    TEST_ASSERT_FLOAT_WITHIN(1.0e-3, r2_pT[i].p, seuth(t,h,OP));
  }
}

void test_th_reg3(void)
{

  for (int i = 0; i < 3; i++)
  {
    double t = r3_Td[i].T-273.15;
    double h = r3_Td[i].h;
    TEST_ASSERT_FLOAT_WITHIN(1.0e-6, r3_Td[i].d, seuth(t,h,OD));
  }
}

void test_th_reg4(void)
{

  double h, p, t, x;
  for (int i = 0; i < 3; i++)
  {
    t = r4_pT[1].T-273.15;
    x = 0.36;
    h = seutx(t, x, OH);
    TEST_ASSERT_EQUAL_FLOAT(x, seuth(t, h, OX));
  }

  for (int i = 0; i < 3; i++)
  {
    t = r4_Tp[1].T-273.15;
    x = 0.36;
    h = seutx(t, x, OH);
    TEST_ASSERT_EQUAL_FLOAT(x, seuth(t, h, OX));
  }
}

void test_th_reg5(void)
{

  for (int i = 0; i < 3; i++)
  {
    double t = r5_pT[i].T-273.15;
    double h = r5_pT[i].h;
    TEST_ASSERT_FLOAT_WITHIN(1.0e-3, r5_pT[i].p, seuth(t,h,OP));
  }
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_th_reg1);
  RUN_TEST(test_th_reg2);
  RUN_TEST(test_th_reg3);
  RUN_TEST(test_th_reg4);
  RUN_TEST(test_th_reg5);
  return UNITY_END();
}