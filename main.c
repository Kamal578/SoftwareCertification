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
    * ageLimit = (int)mock();

}
/* A test case that does nothing and succeeds. */
static void null_test_success(void **state) {
    (void) state;
}


int main(void) {
    const struct CMUnitTest tests[] = {
        // ajout sans setUP
        cmocka_unit_test(null_test_success)

    };
 //   cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests_name("toto",tests, NULL, NULL);
}
