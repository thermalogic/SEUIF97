#include "../src/common/seuif97.h"
#include "../src/common/propertry_id.h"
#include "../Unity/unity.h"
#include "if97_data.h"

void setUp(void) {}

void tearDown(void) {}

void test_ph_reg1(void)
{

  for (int i = 0; i < 3; i++)
  {
    double p = r1_phT[i].p;
    double h = r1_phT[i].h;
    TEST_ASSERT_FLOAT_WITHIN(1.0e-1, r1_phT[i].T - 273.15, ph(p, h, OT));
  }
}

void test_ph_reg2(void)
{
  for (int i = 0; i < 3; i++)
  {
    double p = r2a_phT[i].p;
    double h = r2a_phT[i].h;
    TEST_ASSERT_EQUAL_FLOAT(r2a_phT[i].T - 273.15, ph(p, h, OT));

    p = r2b_phT[i].p;
    h = r2b_phT[i].h;
    TEST_ASSERT_EQUAL_FLOAT(r2b_phT[i].T - 273.15, ph(p, h, OT));

    p = r2c_phT[i].p;
    h = r2c_phT[i].h;
    TEST_ASSERT_EQUAL_FLOAT(r2c_phT[i].T - 273.15, ph(p, h, OT));
  }
}

void test_ph_reg3(void)
{

  double p, h;
  for (int i = 0; i < 3; i++)
  {
    double p = r3a_phTv[i].p;
    double h = r3a_phTv[i].h;
    TEST_ASSERT_EQUAL_FLOAT(r3a_phTv[i].T - 273.15, ph(p, h, OT));
    TEST_ASSERT_EQUAL_FLOAT(r3a_phTv[i].v, ph(p, h, OV));
    p = r3b_phTv[i].p;
    h = r3b_phTv[i].h;
    TEST_ASSERT_EQUAL_FLOAT(r3b_phTv[i].T - 273.15, ph(p, h, OT));
    TEST_ASSERT_EQUAL_FLOAT(r3b_phTv[i].v, ph(p, h, OV));
  }
}

void test_ph_reg4(void)
{

  double h, p, t, x;
  for (int i = 0; i < 3; i++)
  {
    double p = r4_pT[1].p;
    x = 0.36;
    h = px(p, x, OH);
    TEST_ASSERT_EQUAL_FLOAT(x, ph(p, h, OX));
  }

  for (int i = 0; i < 3; i++)
  {
    p = r4_Tp[1].p;
    x = 0.36;
    h = px(p, x, OH);
    TEST_ASSERT_EQUAL_FLOAT(x, ph(p, h, OX));
  }
}

void test_ph_reg5(void)
{

  for (int i = 0; i < 3; i++)
  {
    double p = r5_pT[i].p;
    double h = r5_pT[i].h;
    TEST_ASSERT_EQUAL_FLOAT(r5_pT[i].T - 273.15, ph(p, h, OT));
  }
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_ph_reg1);
  RUN_TEST(test_ph_reg2);
  RUN_TEST(test_ph_reg3);
  RUN_TEST(test_ph_reg4);
  RUN_TEST(test_ph_reg5);
  return UNITY_END();
}