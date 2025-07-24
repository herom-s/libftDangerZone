#include "munit.h"
#include "libft.h"
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <stdlib.h>

static MunitResult test_ft_strrchr_base(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	char	s1[] = "caos";
	char	*res1 = strrchr(s1, 'o');
	char	*res2 = ft_strrchr(s1, 'o');
	munit_assert_ptr_equal(res1, res2);
    return MUNIT_OK;
}

static MunitResult test_ft_strrchr_s_null_segfault(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	char	*res1 = NULL;
	char	*res2 = NULL;
	pid_t pid;
    int status;
    int strrchr_segfaulted = 0;
    int ft_strrchr_segfaulted = 0;

    pid = fork();
    if (pid == 0) {
		char	*s1 = (void *) 0;
		res1 = strrchr(s1, 0);
        exit(0);
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV) {
            strrchr_segfaulted = 1;
        }
    } else {
        munit_error("fork() failed");
    }
    
    pid = fork();
    if (pid == 0) {
		char	*s2 = (void *) 0;
		res2 = ft_strrchr(s2, 0);
        exit(0);
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV) {
            ft_strrchr_segfaulted = 1;
        }
    } else {
        munit_error("fork() failed");
    }
    
	munit_assert_ptr_equal(res1, res2);
    munit_assert_int(strrchr_segfaulted, ==, 1);
    munit_assert_int(ft_strrchr_segfaulted, ==, 1);
    return MUNIT_OK;
}

static MunitResult test_ft_strrchr_c_not_in_s(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	char	s1[] = "caos";
	char	*res1 = strrchr(s1, 'v');
	char	*res2 = ft_strrchr(s1, 'v');
	munit_assert_ptr_equal(res1, res2);
    return MUNIT_OK;
}

static MunitResult test_ft_strrchr_check_null_in_the_start(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	char	s1[] = "\0caos";
	char	*res1 = strrchr(s1, '\0');
	char	*res2 = ft_strrchr(s1, '\0');
	munit_assert_ptr_equal(res1, res2);
    return MUNIT_OK;
}

static MunitResult test_ft_strrchr_check_null_in_the_mid(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	char	s1[] = "ca\0s";
	char	*res1 = strrchr(s1, '\0');
	char	*res2 = ft_strrchr(s1, '\0');
	munit_assert_ptr_equal(res1, res2);
    return MUNIT_OK;
}

static MunitResult test_ft_strrchr_check_null_as_last(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	char	s1[] = "caos";
	char	*res1 = strrchr(s1, '\0');
	char	*res2 = ft_strrchr(s1, '\0');
	munit_assert_ptr_equal(res1, res2);
    return MUNIT_OK;
}



/* Test array */
static MunitTest tests_ft_strrchr[] = {
    { "/base", test_ft_strrchr_base, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/s_null_segfault", test_ft_strrchr_s_null_segfault, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/c_not_in_s", test_ft_strrchr_c_not_in_s, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/check_null_in_the_start", test_ft_strrchr_check_null_in_the_start, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/check_null_in_the_mid", test_ft_strrchr_check_null_in_the_mid, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/check_null_as_last", test_ft_strrchr_check_null_as_last, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

/* String test suite */
const MunitSuite test_suite_ft_strrchr = {
    "/test_ft_strrchr",
    tests_ft_strrchr,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};
