
#include "../src/common/seuif97.h"
#include "../unity/unity.h"

void setUp(void) {}

void tearDown(void) {}

void test_proc(void)
{
  double p1 = 16.1;
  double t1 = 535.2;
  double p2 = 3.56;
  double t2 = 315.1;

  double hdis = seuishd(p1, t1, p2);
  double ef = seuief(p1, t1, p2, t2);
  TEST_ASSERT_EQUAL_FLOAT(426.2965108499634, hdis);
  TEST_ASSERT_EQUAL_FLOAT(89.45513966623548, ef);
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_proc);
  return UNITY_END();
}