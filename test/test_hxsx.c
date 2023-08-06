#include "../src/common/seuif97.h"
#include "../src/common/propertry_id.h"
#include "../Unity/unity.h"
#include "if97_data.h"

void setUp(void) {}

void tearDown(void) {}

void test_hx(void)
{
  double t, h, x;
  x = 0.35;
  for (int i = 0; i < 3; i++)
  {
    t = r4_Tp[i].T - 273.15;
    h = seutx(t, x, OH);
    TEST_ASSERT_FLOAT_WITHIN(1.0e-1, t, seuhx(h, x, OT));
  }
}

void test_sx(void)
{
  double t, s, x;
  x = 0.35;
  for (int i = 0; i < 3; i++)
  {
    t = r4_Tp[i].T - 273.15;
    s = seutx(t, x, OS);
    TEST_ASSERT_FLOAT_WITHIN(1.0e-1, t, seusx(s, x, OT));
  }
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_hx);
  RUN_TEST(test_sx);
  return UNITY_END();
}