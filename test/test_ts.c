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

void test_ts_reg1(void)
{

  for (int i = 0; i < 3; i++)
  {
    double t = r1_pT[i].T - 273.15;
    double s = r1_pT[i].s;
    TEST_ASSERT_EQUAL_FLOAT(r1_pT[i].p, ts(t, s, OP));
  }
}

void test_ts_reg2(void)
{

  for (int i = 0; i < 3; i++)
  {
    double t = r2_pT[i].T - 273.15;
    double s = r2_pT[i].s;
    TEST_ASSERT_EQUAL_FLOAT(r2_pT[i].p, ts(t, s, OP));
  }
}

void test_ts_reg3(void)
{
  for (int i = 0; i < 3; i++)
  {
    double t = r3_Td[i].T - 273.15;
    double s = r3_Td[i].s;
    TEST_ASSERT_EQUAL_FLOAT(r3_Td[i].d, ts(t, s, OD));
  }
}
void test_ts_reg4(void)
{

  double s, t, x;
  for (int i = 0; i < 3; i++)
  {
    t = r4_pT[1].T - 273.15;
    x = 0.36;
    s = tx(t, x, OS);
    TEST_ASSERT_EQUAL_FLOAT(x, ts(t, s, OX));
  }

  for (int i = 0; i < 3; i++)
  {
    t = r4_Tp[1].T - 273.15;
    x = 0.36;
    s = tx(t, x, OS);
    TEST_ASSERT_EQUAL_FLOAT(x, ts(t, s, OX));
  }
}

void test_ts_reg5(void)
{

  for (int i = 0; i < 3; i++)
  {
    double t = r5_pT[i].T - 273.15;
    double s = r5_pT[i].s;
    TEST_ASSERT_EQUAL_FLOAT(r5_pT[i].p, ts(t, s, OP));
  }
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_ts_reg1);
  RUN_TEST(test_ts_reg2);
  RUN_TEST(test_ts_reg3);
  RUN_TEST(test_ts_reg4);
  RUN_TEST(test_ts_reg5);
  return UNITY_END();
}