
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

  TEST_ASSERT_EQUAL_FLOAT(426.30304, ishd(p1, t1, p2));
  TEST_ASSERT_FLOAT_WITHIN(1.0e-2,89.45, ief(p1, t1, p2, t2));
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_proc);
  return UNITY_END();
}