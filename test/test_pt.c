#include "../src/common/seuif97.h"
#include "../src/common/propertry_id.h"
#include "../Unity/unity.h"
#include "if97_data.h"

void setUp(void) {}

void tearDown(void) {}

void test_pt_reg1(void)
{

  for (int i = 0; i < 3; i++)
  {
    double p = r1_pT[i].p;
    double t = r1_pT[i].T - 273.15;
    TEST_ASSERT_EQUAL_FLOAT(r1_pT[i].v, seupt(p, t, OV));
    TEST_ASSERT_EQUAL_FLOAT(r1_pT[i].h, seupt(p, t, OH));
    TEST_ASSERT_EQUAL_FLOAT(r1_pT[i].s, seupt(p, t, OS));
    TEST_ASSERT_EQUAL_FLOAT(r1_pT[i].u, seupt(p, t, OU));
    TEST_ASSERT_EQUAL_FLOAT(r1_pT[i].cv, seupt(p, t, OCV));
    TEST_ASSERT_EQUAL_FLOAT(r1_pT[i].cp, seupt(p, t, OCP));
    TEST_ASSERT_EQUAL_FLOAT(r1_pT[i].w, seupt(p, t, OW));
  }
}

void test_pt_reg2(void)
{
  //  table15，Page17: p,T,v,h,u,s,cp,ws

  for (int i = 0; i < 3; i++)
  {
    double p = r2_pT[i].p;
    double t = r2_pT[i].T - 273.15;
    TEST_ASSERT_EQUAL_FLOAT(r2_pT[i].v, seupt(p, t, OV));
    TEST_ASSERT_EQUAL_FLOAT(r2_pT[i].h, seupt(p, t, OH));
    TEST_ASSERT_EQUAL_FLOAT(r2_pT[i].s, seupt(p, t, OS));
    TEST_ASSERT_EQUAL_FLOAT(r2_pT[i].u, seupt(p, t, OU));
    // TEST_ASSERT_EQUAL_FLOAT(r2_pT[i].cv, seupt(p,t,OCV));
    TEST_ASSERT_EQUAL_FLOAT(r2_pT[i].cp, seupt(p, t, OCP));
    TEST_ASSERT_EQUAL_FLOAT(r2_pT[i].w, seupt(p, t, OW));
  }
}

void test_pt_reg3(void)
{
  double p, t;
  for (int i = 0; i < 52; i++)
  {
    p = r3_pTv[i].p;
    t = r3_pTv[i].T - 273.15;
    TEST_ASSERT_EQUAL_FLOAT(r3_pTv[i].v, seupt(p, t, OV));
  }
}

void test_pt_reg4(void)
{
  double p, t;
  for (int i = 0; i < 3; i++)
  {
    p = r4_pT[i].p;
    TEST_ASSERT_EQUAL_FLOAT(r4_pT[i].T - 273.15, seupx(p, 0.0, OT));
  }

  for (int i = 0; i < 3; i++)
  {
    t = r4_Tp[i].T - 273.15;
    TEST_ASSERT_EQUAL_FLOAT(r4_Tp[i].p, seutx(t, 0.0, OP));
  }
}

void test_pt_reg5(void)
{

  for (int i = 0; i < 3; i++)
  {
    double p = r5_pT[i].p;
    double t = r5_pT[i].T - 273.15;
    TEST_ASSERT_EQUAL_FLOAT(r5_pT[i].v, seupt(p, t, OV));
    TEST_ASSERT_EQUAL_FLOAT(r5_pT[i].h, seupt(p, t, OH));
    TEST_ASSERT_EQUAL_FLOAT(r5_pT[i].u, seupt(p, t, OU));
    TEST_ASSERT_EQUAL_FLOAT(r5_pT[i].s, seupt(p, t, OS));
    TEST_ASSERT_EQUAL_FLOAT(r5_pT[i].cp, seupt(p, t, OCP));
    TEST_ASSERT_EQUAL_FLOAT(r5_pT[i].w, seupt(p, t, OW));
  }
}

void test_pt_critical(void)
{
  // critical point
  double tc_water = 647.096 - 273.15; // critical temperature in K
  double pc_water = 22.064;           // critical p in Mpa
  double dc_water = 322.0;            // critical density in kg/m**3
  double sc_water = 4.41202148223476; // Critic entropy
  double hc_water = 2.087546845e+03;  // Critic entropy h
  TEST_ASSERT_EQUAL_FLOAT(sc_water, seupt(pc_water, tc_water, OS));
  TEST_ASSERT_EQUAL_FLOAT(hc_water, seupt(pc_water, tc_water, OH));
  TEST_ASSERT_EQUAL_FLOAT(dc_water, seupt(pc_water, tc_water, OD));
  TEST_ASSERT_EQUAL_FLOAT(tc_water, seupt(pc_water, tc_water, OT));
  TEST_ASSERT_EQUAL_FLOAT(pc_water, seupt(pc_water, tc_water, OP));
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_pt_reg1);
  RUN_TEST(test_pt_reg2);
  RUN_TEST(test_pt_reg3);
  RUN_TEST(test_pt_reg4);
  RUN_TEST(test_pt_reg5);
  RUN_TEST(test_pt_critical);
  return UNITY_END();
}