#include "munit.h"
#include "libft.h"
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

static MunitResult test_ft_bzero_normal(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    char buffer1[20];
    char buffer2[20];
    
    // Fill buffers with some data
    memset(buffer1, 'A', 20);
    memset(buffer2, 'A', 20);
    
    // Test bzero
    bzero(buffer1, 10);
    ft_bzero(buffer2, 10);
    
    munit_assert_memory_equal(20, buffer1, buffer2);
    return MUNIT_OK;
}

static MunitResult test_ft_bzero_zero_size(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    char buffer1[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    char buffer2[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    
    // Test with zero size - should not change anything
    bzero(buffer1, 0);
    ft_bzero(buffer2, 0);
    
    munit_assert_memory_equal(10, buffer1, buffer2);
    return MUNIT_OK;
}

static MunitResult test_ft_bzero_full_buffer(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    char buffer1[15];
    char buffer2[15];
    
    // Fill buffers with data
    memset(buffer1, 'X', 15);
    memset(buffer2, 'X', 15);
    
    // Zero entire buffer
    bzero(buffer1, 15);
    ft_bzero(buffer2, 15);
    
    munit_assert_memory_equal(15, buffer1, buffer2);
    return MUNIT_OK;
}

static MunitResult test_ft_bzero_null_segfault(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	pid_t pid;
    int status;
    int bzero_segfaulted = 0;
    int ft_bzero_segfaulted = 0;

    pid = fork();
    if (pid == 0) {
		char	*s1 = (void *) 0;
		bzero(s1, 10);
        exit(0);
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV) {
            bzero_segfaulted = 1;
        }
    } else {
        munit_error("fork() failed");
    }
    
    pid = fork();
    if (pid == 0) {
		char	*s2 = (void *) 0;
		ft_bzero(s2, 10);
        exit(0);
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV) {
            ft_bzero_segfaulted = 1;
        }
    } else {
        munit_error("fork() failed");
    }
    
    munit_assert_int(bzero_segfaulted, ==, 1);
    munit_assert_int(ft_bzero_segfaulted, ==, 1);
    return MUNIT_OK;
}

/* Test array */
static MunitTest tests_ft_bzero[] = {
    { "/normal", test_ft_bzero_normal, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/zero_size", test_ft_bzero_zero_size, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/full_buffer", test_ft_bzero_full_buffer, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/null_segfault", test_ft_bzero_null_segfault, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

/* Test suite */
const MunitSuite test_suite_ft_bzero = {
    "/test_ft_bzero",
    tests_ft_bzero,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};
