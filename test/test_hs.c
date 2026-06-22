#include "../src/common/seuif97.h"
#include "../src/common/property_id.h"
#include "../Unity/unity.h"
#include "if97_data.h"

void setUp(void) {}

void tearDown(void) {}

void test_hs_reg1(void)
{

  for (int i = 0; i < 3; i++)
  {
    double h = r1_hspT[i].h;
    double s = r1_hspT[i].s;
    double t = r1_hspT[i].T - 273.15;
    TEST_ASSERT_FLOAT_WITHIN(1.0e-1, t, hs(h, s, OT));
    TEST_ASSERT_FLOAT_WITHIN(1.0e-1, r1_hspT[i].p, hs(h, s, OP));
  }
}

void test_hs_reg2(void)
{
  //  table15，Page17: p,T,v,h,u,s,cp,ws

  for (int i = 0; i < 3; i++)
  {
    double h = r2a_hsP[i].h;
    double s = r2a_hsP[i].s;
    TEST_ASSERT_EQUAL_FLOAT(r2a_hsP[i].p, hs(h, s, OP));

    h = r2b_hsP[i].h;
    s = r2b_hsP[i].s;
    TEST_ASSERT_EQUAL_FLOAT(r2b_hsP[i].p, hs(h, s, OP));

    h = r2c_hsP[i].h;
    s = r2c_hsP[i].s;
    TEST_ASSERT_EQUAL_FLOAT(r2c_hsP[i].p, hs(h, s, OP));
  }
}

void test_hs_reg3(void)
{
  double h, s;
  for (int i = 0; i < 3; i++)
  {
    h = r3a_hsP[i].h;
    s = r3a_hsP[i].s;
   TEST_ASSERT_FLOAT_WITHIN(1.0e-2,r3a_hsP[i].p, hs(h, s, OP));
    h = r3b_hsP[i].h;
    s = r3b_hsP[i].s;
   TEST_ASSERT_FLOAT_WITHIN(1.0e-1,r3b_hsP[i].p, hs(h, s, OP));
  }
}

void test_hs_reg4(void)
{
  for (int i = 0; i < 3; i++)
  {
    double h = r4_hsT[i].h;
    double s = r4_hsT[i].s;
    TEST_ASSERT_EQUAL_FLOAT(r4_hsT[i].T - 273.15, hs(h, s, OT));
  }
}

 void test_hs_x_reg4(void)
 {    
//r4_pT = [[0.1, 372.755919], [1.0, 453.035632], [10.0, 584.149488]];
 for(int i=0; i<2;i++) {
        double p = r4_pT[i].p;
        double T = r4_pT[i].T;
        double x = 0.6;
        double s = px(p, x, OS);
        double h = px(p, x, OH);
        TEST_ASSERT_EQUAL_FLOAT(T-273.15, hs(h, s, OT));
        TEST_ASSERT_EQUAL_FLOAT(p, hs(h, s, OP));
        TEST_ASSERT_EQUAL_FLOAT(x, hs(h, s, OX));
    }

   for(int i=0; i<2;i++) {
        double p = r4_pT[i].p;
        double T = r4_pT[i].T;
        double x = 0.02;
        double s = px(p, x, OS);
        double h = px(p, x, OH);
        TEST_ASSERT_EQUAL_FLOAT(T-273.15, hs(h, s, OT));
        TEST_ASSERT_EQUAL_FLOAT(p, hs(h, s, OP));
        TEST_ASSERT_EQUAL_FLOAT(x, hs(h, s, OX));
    }
    
    TEST_ASSERT_FLOAT_WITHIN(1.0e-4, 0.03653974055475902, hs(1800.0, 5.3, OP));
    TEST_ASSERT_FLOAT_WITHIN(1.0e-4,0.270298590472939, hs(1500.0, 4.0, OP));
    
}

void test_hs_reg5(void)
{
  for (int i = 0; i < 3; i++)
  {
    double h = r5_pT[i].h;
    double s = r5_pT[i].s;
    TEST_ASSERT_EQUAL_FLOAT(r5_pT[i].T - 273.15, hs(h, s, OT));
  }
}


int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_hs_reg1);
  RUN_TEST(test_hs_reg2);
  RUN_TEST(test_hs_reg3);
  RUN_TEST(test_hs_reg4);
  RUN_TEST(test_hs_x_reg4);
  RUN_TEST(test_hs_reg5);
  return UNITY_END();
}