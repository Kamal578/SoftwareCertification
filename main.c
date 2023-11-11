#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmocka.h"
#include <string.h>
#include "compute.h"

#define true 1
#define false 0


// declaration du mock
void recupLimitAge(int * ageLimit)
{   // dépilage de la valeur
    * ageLimit = 20;

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

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_price)
    };
 //   cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests_name("toto",tests, NULL, NULL);
}
