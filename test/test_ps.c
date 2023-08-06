#include "../src/common/seuif97.h"
#include "../src/common/propertry_id.h"
#include "../Unity/unity.h"
#include "if97_data.h"

void setUp(void) {}

void tearDown(void) {}

void test_ps_reg1(void)
{
  for (int i = 0; i < 3; i++)
  {
    double p = r1_psT[i].p;
    double s = r1_psT[i].s;
    TEST_ASSERT_FLOAT_WITHIN(1.0e-1,r1_psT[i].T - 273.15, seups(p, s, OT));
  }
}

void test_ps_reg2(void)
{
  //  table15，Page17: p,T,v,h,u,s,cp,ws

  for (int i = 0; i < 3; i++)
  {

    double p = r2a_psT[i].p;
    double s = r2a_psT[i].s;
    TEST_ASSERT_EQUAL_FLOAT(r2a_psT[i].T - 273.15, seups(p, s, OT));
    p = r2b_psT[i].p;
    s = r2b_psT[i].s;
    TEST_ASSERT_EQUAL_FLOAT(r2b_psT[i].T - 273.15, seups(p, s, OT));
    p = r2c_psT[i].p;
    s = r2c_psT[i].s;
    TEST_ASSERT_EQUAL_FLOAT(r2c_psT[i].T - 273.15, seups(p, s, OT));
  }
}

void test_ps_reg3(void)
{

  double p, s;
  for (int i = 0; i < 3; i++)
  {
    p = r3a_psTv[i].p;
    s = r3a_psTv[i].s;
    TEST_ASSERT_EQUAL_FLOAT(r3a_psTv[i].T - 273.15, seups(p, s, OT));
    TEST_ASSERT_EQUAL_FLOAT(r3a_psTv[i].v, seups(p, s, OV));
    p = r3b_psTv[i].p;
    s = r3b_psTv[i].s;
    TEST_ASSERT_EQUAL_FLOAT(r3b_psTv[i].T - 273.15, seups(p, s, OT));
    TEST_ASSERT_EQUAL_FLOAT(r3b_psTv[i].v, seups(p, s, OV));
  }
}

void test_ps_reg4(void)
{

  double p, s, x;
  for (int i = 0; i < 3; i++)
  {
    double p = r4_pT[i].p;
    x = 0.35;
    s = seupx(p, x, OS);
    TEST_ASSERT_EQUAL_FLOAT(x, seups(p, s, OX));
  }

  for (int i = 0; i < 3; i++)
  {
    p = r4_Tp[1].p;
    x = 0.36;
    s = seupx(p, x, OS);
    TEST_ASSERT_EQUAL_FLOAT(x, seups(p, s, OX));
  }
}

void test_ps_reg5(void)
{
  for (int i = 0; i < 3; i++)
  {
    double p = r5_pT[i].p;
    double s = r5_pT[i].s;
    TEST_ASSERT_EQUAL_FLOAT(r5_pT[i].T - 273.15, seups(p, s, OT));
  }
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_ps_reg1);
  RUN_TEST(test_ps_reg2);
  RUN_TEST(test_ps_reg3);
  RUN_TEST(test_ps_reg4);
  RUN_TEST(test_ps_reg5);
  return UNITY_END();
}