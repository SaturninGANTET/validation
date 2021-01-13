//LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/satutu/chafic/CUnit-2.1-3/CUnit/Sources/.libs/libcunit.so.1
//export LD_LIBRARY_PATH
//gcc -Wall -LCUnit-2.1-3/CUnit/Sources/.libs -ICUnit-2.1-3/CUnit/Headers -o main_test test.c main.o -lcunit

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"

#include "main.h"

#include <stdio.h>

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

// test arg
void CSC_test_1(void)
{
    char *arg[11];
    arg[1] = "10"; //distance
    arg[2] = "0";  //frein off
    arg[3] = "0";  //hasMessage
    CU_ASSERT_EQUAL(CSC(4, arg), 0);

    arg[1] = "2"; //distance
    CU_ASSERT_EQUAL(CSC(4, arg), 1);

    arg[2] = "1"; //frein on
    CU_ASSERT_EQUAL(CSC(4, arg), 3);

    CU_ASSERT_EQUAL(CSC(3, arg), -1);

    // message
    arg[3] = "1";
    arg[4] = "30";
    arg[5] = "30";
    arg[6] = "30";
    arg[7] = "30";
    arg[8] = "30";
    arg[9] = "30";
    arg[10] = "30";
    CU_ASSERT_EQUAL(CSC(10, arg), -1);
    CU_ASSERT_EQUAL(CSC(11, arg), 7);

    arg[1] = "50";
    CU_ASSERT_EQUAL(CSC(11, arg), 6);
    arg[3] = "0";
    CU_ASSERT_EQUAL(CSC(11, arg), 2);
}

void obstacle_test()
{
    char *arg[11];
    arg[1] = "10"; //distance
    arg[2] = "0";  //frein off
    arg[3] = "0";  //hasMessage
    CU_ASSERT_EQUAL(CSC(4, arg), 0);

    arg[1] = "5"; //distance
    CU_ASSERT_EQUAL(CSC(4, arg), 1);
}

void frein_test()
{
    char *arg[11];
    arg[1] = "10"; //distance
    arg[2] = "0";  //frein off
    arg[3] = "0";  //hasMessage
    CU_ASSERT_EQUAL(CSC(4, arg), 0);

    arg[2] = "1";
    CU_ASSERT_EQUAL(CSC(4, arg), 2);
}

void propage_message_test()
{
    char *arg[11];
    arg[1] = "10"; //distance
    arg[2] = "0";  //frein off
    arg[3] = "0";  //hasMessage
    arg[4] = "30"; //position
    arg[5] = "30";
    arg[6] = "30";
    arg[7] = "30"; //dynamique
    arg[8] = "30";
    arg[9] = "30";
    arg[10] = "30"; //temps
    CU_ASSERT_EQUAL(CSC(11, arg), -25); //0

    arg[3] = "1";
    CU_ASSERT_EQUAL(CSC(11, arg), 4);
}
int main(void)
{
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("max_test_suite", init_suite, clean_suite);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "CSC_test_1", CSC_test_1)) ||
        (NULL == CU_add_test(pSuite, "obstacle_test", obstacle_test)) ||
        (NULL == CU_add_test(pSuite, "frein_test", frein_test)) ||
        (NULL == CU_add_test(pSuite, "propage_message_test", propage_message_test)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests using the basic interface
    /*
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_basic_run_suite(pSuite);
    printf("\n");
    CU_basic_show_failures(CU_get_failure_list());
    printf("\n\n");
    */
   CU_automated_run_tests();
}