#include <stdlib.h>
#include <stdio.h>
#include "memory.h"

void test(m_err_code error, char* test_name)
{
    printf("Test \"%s\" started...\n",test_name);
    switch(error)
    {
        case M_ERR_OK: { printf("Test \"%s\" PASSED\n", test_name); break; }
        case M_ERR_INVALID_CHUNK: { printf("Test \"%s\" EXIT: M_ERR_INVALID_CHUNK\n", test_name); abort(); }
        case M_ERR_OUT_OF_BOUNDS: { printf("Test \"%s\" EXIT: M_ERR_OUT_OF_BOUNDS\n", test_name); abort(); }
        case M_ERR_ALREADY_DEALLOCATED: { printf("Test \"%s\" WARNING: M_ERR_ALREADY_DEALLOCATED\n", test_name); break; }
        case M_ERR_ALLOCATION_OUT_OF_MEMORY: { printf("Test \"%s\" WARNING: M_ERR_ALLOCATION_OUT_OF_MEMORY\n", test_name); break; }
        default:{ printf("Hello there!\n"); }
    }
    printf("\n");
}

int main()
{
    int error; m_init(500);
    segment_addr first = m_malloc(34, &error); test(error, "TEST 1");
    segment_addr second = m_malloc(36, &error); test(error, "TEST 2");
    segment_addr third = m_malloc(300, &error); test(error, "TEST 3");
    segment_addr fourth = m_malloc(64, &error); test(error, "TEST 4");
    segment_addr chunk_1 = m_malloc(13, &error); test(error, "TEST 5");
    segment_addr chunk_2 = m_malloc(20, &error); test(error, "TEST 6");
    segment_addr chunk_3 = m_malloc(50, &error); test(error, "TEST 7");
    test(m_write(chunk_1, "Hello There!", 13), "TEST 8");
    test(m_write(chunk_2, "Welcome to Hell!!", 18), "TEST 9");
    test(m_write(chunk_3, "AXXXAXAAXAXAXAXAXAXAXAXAXAA", 28), "TEST 10");

    char* buffer = malloc(50); test(m_read(chunk_1, buffer, 13), "TEST 11");

    test(m_read(chunk_2, buffer, 18), "TEST 12");
    test(m_read(chunk_3, buffer, 28), "TEST 13");
    test(m_free(chunk_1), "TEST 14");
    test(m_free(chunk_2), "TEST 15");
    test(m_free(chunk_3), "TEST 16");
}
