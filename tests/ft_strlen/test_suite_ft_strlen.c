#include "munit.h"
#include "libft.h"
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

static MunitResult test_ft_strlen_empty(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	munit_assert_size(strlen(""), ==,ft_strlen(""));
    return MUNIT_OK;
}

static MunitResult test_ft_strlen_small_str(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	munit_assert_size(strlen("abcd"), ==,ft_strlen("abcd"));
    return MUNIT_OK;
}
/*
static MunitResult test_ft_strlen_null_segfault(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	pid_t pid;
    int status;
    int strlen_segfaulted = 0;
    int ft_strlen_segfaulted = 0;

    pid = fork();
    if (pid == 0) {
		char	*s1 = (void *) 0;
		strlen(s1);
        exit(0);
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV) {
            strlen_segfaulted = 1;
        }
    } else {
        munit_error("fork() failed");
    }
    
    pid = fork();
    if (pid == 0) {
		char	*s2 = (void *) 0;
		ft_strlen(s2);
        exit(0);
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV) {
            ft_strlen_segfaulted = 1;
        }
    } else {
        munit_error("fork() failed");
    }
    
    munit_assert_int(strlen_segfaulted, ==, 1);
    munit_assert_int(ft_strlen_segfaulted, ==, 1);
    return MUNIT_OK;
}
*/
/*
static MunitResult test_ft_strlen_big_str(const MunitParameter params[], void* data) {
	char	*big_str;
	size_t	str_len = 2147483648 * 7;
    (void) params;
    (void) data;
	big_str = (char *) malloc((str_len) * sizeof(char));
	if (!big_str)
	{
		perror("Failed to allocate memory for big_str");
		exit(EXIT_FAILURE);
	}
	memset(big_str, 'A', str_len);
	munit_assert_size(strlen(big_str), ==, str_len);
    return MUNIT_OK;
}
*/

/* Test array */
static MunitTest tests_ft_strlen[] = {
    { "/empty", test_ft_strlen_empty, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/small_str", test_ft_strlen_small_str, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
//    { "/null_segfault", test_ft_strlen_null_segfault, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
//    { "/big_str", test_ft_strlen_big_str, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

/* String test suite */
const MunitSuite test_suite_ft_strlen = {
    "/test_ft_strlen",
    tests_ft_strlen,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};
