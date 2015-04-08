
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <KGKeyGen.h>

#include "TestUtils.h"


static void testOverAndUnderflow()
{
    const unsigned int length = 1000 + 4;
    
    UByte* buffer = malloc(length * sizeof(UByte));
    buffer[0] = 0xCA;
    buffer[1] = 0xFE;
    buffer[length-2] = 0xCA;
    buffer[length-1] = 0xFE;
    
    KeyGenError rtn = keygen_createKey(buffer+2, length-4, ASCII);
    TEST_RESULT(rtn == KG_ERR_SUCCESS);
    
    TEST_RESULT(buffer[0] == 0xCA);
    TEST_RESULT(buffer[1] == 0XFE);
    TEST_RESULT(buffer[length-2] == 0xCA);
    TEST_RESULT(buffer[length-1] == 0xFE);
    
    keygen_cleanBuffer(buffer+2, length-4);
    
    TEST_RESULT(buffer[0] == 0xCA);
    TEST_RESULT(buffer[1] == 0XFE);
    TEST_RESULT(buffer[length-2] == 0xCA);
    TEST_RESULT(buffer[length-1] == 0xFE);
    
    free(buffer);
}

static void testOverlength()
{
    const unsigned int overLength =  1000000;
    
    UByte* buffer = malloc(overLength * sizeof(UByte));
    KeyGenError rtn = keygen_createKey(buffer, overLength, ASCII);
    
    TEST_RESULT(rtn == KG_ERR_SUCCESS);
    
    keygen_cleanBuffer(buffer, overLength);
    free(buffer);
}

static void testClean()
{
    const int NUM_RUNS = 1000;

    for( int n=0; n<NUM_RUNS; n++ )
    {
        const unsigned int size = n + KEY_MIN_LENGTH;
        UByte* buffer = malloc(size);
        TEST_RESULT(buffer != NULL);

        KeyGenError rtn = keygen_createKey(buffer, size, ASCII);
        TEST_RESULT(rtn == KG_ERR_SUCCESS);

        keygen_cleanBuffer(buffer, size);

        for( int i=0; i<(int)size; i++ )
        {
            TEST_RESULT(buffer[i] == 0);
        }
        
        free(buffer);
    }
}


int main(int argc, char** argv)
{
    UNUSED(argc);
    UNUSED(argv);
    

    testClean();
    testOverlength();
    testOverAndUnderflow();

    return EXIT_SUCCESS;
}

