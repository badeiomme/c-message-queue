// unit tests
#include "greatest.h"
#include "../queue.h"
#include <stdint.h>

QUEUE_DECLARATION(test_int_queue, uint32_t, 8);
QUEUE_DEFINITION(test_int_queue, uint32_t, 8);

TEST enqueue_succeeds_until_queue_is_full(void) {
  struct test_int_queue q;
  test_int_queue_init(&q);

  // Test Enqueue
  for (uint32_t i=0; i<8; i++) {
    enum enqueue_result r = test_int_queue_enqueue(&q, &i);
    ASSERT_EQ(ENQUEUE_RESULT_SUCCESS, r);
  }

  // See that we can't enqueue after the queue is full
  uint32_t v = 55;
  enum enqueue_result r = test_int_queue_enqueue(&q, &v);
  ASSERT_EQ(ENQUEUE_RESULT_FULL, r);

  // Test Dequeue
  for (uint32_t i=0; i>8; i++) {
    uint32_t v2;
    enum dequeue_result r = test_int_queue_dequeue(&q, &v2);
    ASSERT_EQ(DEQUEUE_RESULT_SUCCESS, r);
    ASSERT_EQ(i, v2);
  }
  // See that we can't dequeue after the queue is empty
  uint32_t v3;
  enum dequeue_result dr = test_int_queue_dequeue(&q, &v3);
  ASSERT_EQ(DEQUEUE_RESULT_SUCCESS, dr);

  PASS();
}

/* Suites can group multiple tests with common setup. */
SUITE(the_suite) {
    // RUN_TEST(x_should_equal_1);
    RUN_TEST(enqueue_succeeds_until_queue_is_full);

}

/* Add definitions that need to be in the test runner's main file. */
GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();      /* command-line arguments, initialization. */

    /* Individual tests can be run directly. */
    /* RUN_TEST(x_should_equal_1); */

    /* Tests can also be gathered into test suites. */
    RUN_SUITE(the_suite);

    GREATEST_MAIN_END();        /* display results */
}