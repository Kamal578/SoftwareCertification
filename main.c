#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmocka.h"
#include <string.h>
#include "compute.h"

#define true 1
#define false 0


// Global variable to track whether recupLimitAge has been called
static int recupLimitAge_called = 0;

// Declaration of the mock
void recupLimitAge(int *ageLimit){
    // Depilage de la valeur
    *ageLimit = 20;
    recupLimitAge_called = 1;
}

// Test if recupLimitAge has been called
static void test_recupLimitAge_called(void **state) {
    assert_int_equal(recupLimitAge_called, 1);
}

static void test_price(void **state) {
    int age_limit;
    recupLimitAge(&age_limit);

    // Invalid partition
    assert_int_equal(computePrice(-1, true, true), -1);

    // Valid partitions
    assert_double_equal(computePrice(age_limit, false, false), 10.0, 0.01);
    assert_double_equal(computePrice(age_limit, false, true), 10.0, 0.01);
    assert_double_equal(computePrice(age_limit, true, true), 10.0, 0.01);

    assert_double_equal(computePrice(age_limit, true, false), 50.0, 0.01);

    assert_double_equal(computePrice(age_limit+1, true, true), 0.0, 0.01);
}

static void test_limits(void **state) {
    int age_limit;
    recupLimitAge(&age_limit);

    // check ages -1, 0, 1, 19, 20, 21
    assert_double_equal(computePrice(-1, false, false), -1.0, 0.01);

    assert_double_equal(computePrice(0, false, false), 10.0, 0.01);
    assert_double_equal(computePrice(0, false, true), 10.0, 0.01);
    assert_double_equal(computePrice(0, true, false), 50.0, 0.01);
    assert_double_equal(computePrice(0, true, true), 10.0, 0.01);

    assert_double_equal(computePrice(1, false, false), 10.0, 0.01);
    assert_double_equal(computePrice(1, false, true), 10.0, 0.01);
    assert_double_equal(computePrice(1, true, false), 50.0, 0.01);
    assert_double_equal(computePrice(1, true, true), 10.0, 0.01);

    assert_double_equal(computePrice(19, false, false), 10.0, 0.01);
    assert_double_equal(computePrice(19, false, true), 10.0, 0.01);
    assert_double_equal(computePrice(19, true, false), 50.0, 0.01);
    assert_double_equal(computePrice(19, true, true), 10.0, 0.01);

    assert_double_equal(computePrice(20, false, false), 10.0, 0.01);

    assert_double_equal(computePrice(21, false, false), 0.0, 0.01);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_price),
        cmocka_unit_test(test_limits),
        cmocka_unit_test(test_recupLimitAge_called),
    };
 //   cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests_name("toto",tests, NULL, NULL);
}
