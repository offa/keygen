#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <KGKeyGen.h>

#include "TestUtils.h"

static void cleanUp() __attribute__((__destructor__));

static const unsigned int SIZE = 2000;
static UByte* buffer;


static inline unsigned int size(unsigned int n)
{
    return ( n < SIZE ? n : SIZE );
}


int main(int argc, char** argv)
{
    UNUSED(argc);
    UNUSED(argv);

    UByte* buffer = malloc(SIZE);

    KeyGenError expected = KG_ERR_ILL_ARGUMENT;
    TEST_RESULT(keygen_createKey(NULL, 100, ASCII) == expected);

    for( int num=1; num<KEY_MIN_LENGTH; num++ )
    {
        TEST_RESULT(keygen_createKey(buffer, num, ASCII) == expected); 
    } 

    expected = KG_ERR_SUCCESS;

    TEST_RESULT(keygen_createKey(buffer, size(10), ASCII) == expected);
    TEST_RESULT(keygen_createKey(buffer, size(500), ASCII) == expected);
    TEST_RESULT(keygen_createKey(buffer, size(1000), ASCII) == expected);
    TEST_RESULT(keygen_createKey(buffer, size(8), ASCII) == expected);
    TEST_RESULT(keygen_createKey(buffer, size(9), ASCII) == expected);
    TEST_RESULT(keygen_createKey(buffer, size(15), ASCII) == expected);
    TEST_RESULT(keygen_createKey(buffer, size(24), ASCII) == expected);
    TEST_RESULT(keygen_createKey(buffer, size(334), ASCII) == expected);
    TEST_RESULT(keygen_createKey(buffer, size(1234), ASCII) == expected);
    TEST_RESULT(keygen_createKey(buffer, size(56), ASCII) == expected);
    TEST_RESULT(keygen_createKey(buffer, size(99), ASCII) == expected);
    TEST_RESULT(keygen_createKey(buffer, size(80), ASCII) == expected);
    TEST_RESULT(keygen_createKey(buffer, size(13), ASCII) == expected);

    return EXIT_SUCCESS;
}


static void cleanUp()
{
    keygen_cleanBuffer(buffer, SIZE);
    free(buffer);
}


