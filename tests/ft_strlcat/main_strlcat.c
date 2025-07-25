#include "munit.h"

/* External test suite declaration */
extern const MunitSuite test_suite_ft_strlcat;

int main(int argc, char* argv[]) {
    return munit_suite_main(&test_suite_ft_strlcat, NULL, argc, argv);
}
