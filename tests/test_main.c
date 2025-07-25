
#include "munit.h"

/* External test suite declarations */
extern const MunitSuite test_suite_ft_isalpha;
extern const MunitSuite test_suite_ft_isdigit;
extern const MunitSuite test_suite_ft_isalnum;
extern const MunitSuite test_suite_ft_isascii;
extern const MunitSuite test_suite_ft_isprint;
extern const MunitSuite test_suite_ft_strlen;
extern const MunitSuite test_suite_ft_memset;
extern const MunitSuite test_suite_ft_strchr;
extern const MunitSuite test_suite_ft_strrchr;
extern const MunitSuite test_suite_ft_bzero;
extern const MunitSuite test_suite_ft_memcpy;
extern const MunitSuite test_suite_ft_memmove;
extern const MunitSuite test_suite_ft_strlcpy;
extern const MunitSuite test_suite_ft_strlcat;
extern const MunitSuite test_suite_ft_toupper;
extern const MunitSuite test_suite_ft_tolower;

int main(int argc, char* argv[]) {
    /* Define the array on the stack (or heap if needed) */
    MunitSuite test_suites[] = {
        test_suite_ft_isalpha,
        test_suite_ft_isdigit,
        test_suite_ft_isalnum,
        test_suite_ft_isascii,
        test_suite_ft_isprint,
        test_suite_ft_strlen,
        test_suite_ft_memset,
        test_suite_ft_strchr,
        test_suite_ft_strrchr,
        test_suite_ft_bzero,
        test_suite_ft_memcpy,
        test_suite_ft_memmove,
        test_suite_ft_strlcpy,
        test_suite_ft_strlcat,
        test_suite_ft_toupper,
        test_suite_ft_tolower,
        { NULL, NULL, NULL, 1, MUNIT_SUITE_OPTION_NONE }
    };

    const MunitSuite main_suite = {
        "/libft",
        NULL,
        test_suites,
        1,
        MUNIT_SUITE_OPTION_NONE
    };

    return munit_suite_main(&main_suite, NULL, argc, argv);
}
