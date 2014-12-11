
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <KGKeyGen.h>

#include "TestUtils.h"


static void cleanUp() __attribute__((__destructor__));


static bool testFormat(UByte* buffer, unsigned int size, enum Format format)
{
    switch(format)
    {
        case ASCII:
            for( int i=0; i<(int)size; i++ )
            {
                if( buffer[i] <= ' ' || buffer[i] > '~' )
                {
                    printf("Test failed: <%c> is not allowed\n", buffer[i]);
                    return false;
                }
            }
            return true;
        case ASCII_BLANKS:
            for( int i=0; i<(int)size; i++ )
            {
                if( buffer[i] < ' ' || buffer[i] > '~' )
                {
                    printf("Test failed: <%c> is not allowed\n", buffer[i]);
                    return false;
                }
            }
            return true;
        default:
            break;
    }

    return false;
}


static const unsigned int SIZE = 2000;
static UByte* buffer;

static const int NUM_RUNS = 1000;


int main(int arg, char** argv)
{
    UNUSED(arg);
    UNUSED(argv);

    
    buffer = malloc(SIZE);
    TEST_RESULT(buffer != NULL);

    // Test Ascii format
    enum Format format = ASCII;
    
    for( int n=0; n<NUM_RUNS; n++ )
    {
        KeyGenError rtn = keygen_createKey(buffer, SIZE, format);    

        TEST_RESULT(rtn == KG_ERR_SUCCESS);
        TEST_RESULT(testFormat(buffer, SIZE, format) == true);

        keygen_cleanBuffer(buffer, SIZE);
    }

    // Ascii with blanks
    format = ASCII_BLANKS;
    
    for( int n=0; n<NUM_RUNS; n++ )
    {
        KeyGenError rtn = keygen_createKey(buffer, SIZE, format);    

        TEST_RESULT(rtn == KG_ERR_SUCCESS);
        TEST_RESULT(testFormat(buffer, SIZE, format) == true);

        keygen_cleanBuffer(buffer, SIZE);
    }

    return EXIT_SUCCESS;
}


static void cleanUp()
{
    keygen_cleanBuffer(buffer, SIZE);
    free(buffer);
}


