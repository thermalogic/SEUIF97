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

void test_pv_reg1(void)
{

  for (int i = 0; i < 3; i++)
  {
    double p = r1_pT[i].p;
    double v = r1_pT[i].v;
    TEST_ASSERT_EQUAL_FLOAT(r1_pT[i].T - 273.15, pv(p, v, OT));
  }
}

void test_pv_reg2(void)
{

  for (int i = 0; i < 3; i++)
  {
    double p = r2_pT[i].p;
    double v = r2_pT[i].v;
    TEST_ASSERT_EQUAL_FLOAT(r2_pT[i].T - 273.15, pv(p, v, OT));
  }
}

void test_pv_reg3(void)
{

  for (int i = 0; i < 3; i++)
  {
    double p = r3_Td[i].p;
    double v = 1.0 / r3_Td[i].d;
    TEST_ASSERT_EQUAL_FLOAT(r3_Td[i].T - 273.15, pv(p, v, OT));
  }
}

void test_pv_reg4(void)
{
  double p, v, x;
  for (int i = 0; i < 3; i++)
  {
    double p = r4_pT[1].p;
    x = 0.36;
    v = px(p, x, OV);
    TEST_ASSERT_EQUAL_FLOAT(x, pv(p, v, OX));
  }

  for (int i = 0; i < 3; i++)
  {
    p = r4_Tp[1].p;
    x = 0.36;
    v = px(p, x, OV);
    TEST_ASSERT_EQUAL_FLOAT(x, pv(p, v, OX));
  }
}

void test_pv_reg5(void)
{

  for (int i = 0; i < 3; i++)
  {
    double p = r5_pT[i].p;
    double v = r5_pT[i].v;
    TEST_ASSERT_EQUAL_FLOAT(r5_pT[i].T - 273.15, pv(p, v, OT));
  }
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_pv_reg1);
  RUN_TEST(test_pv_reg2);
  RUN_TEST(test_pv_reg3);
  RUN_TEST(test_pv_reg4);
  RUN_TEST(test_pv_reg5);
  return UNITY_END();
}