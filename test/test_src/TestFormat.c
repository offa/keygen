
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include <KGKeyGen.h>

#include "TestUtils.h"


static void cleanUp() __attribute__((__destructor__));


static const char ALLOWED_ASCII_REDUCED[] =
{
    '!', '#', '$', '%', '&', '(', ')', '*', '+', ',', '-', '.', '/', '0', '1', 
    '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@', 
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 
    'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', ']', '_', 'a', 
    'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '}', '~'
};

static const unsigned int ALLOWED_ASCII_REDUCED_LENGTH = sizeof(ALLOWED_ASCII_REDUCED);



static bool isIn(const char* allowedChars, unsigned int allowedCharsSize, char testFor)
{
    for( unsigned int i=0; i<allowedCharsSize; i++ )
    {
        if( allowedChars[i] == testFor )
        {
            return true;
        }
    }
    
    return false;
}

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
        case ASCII_REDUCED:
            for( int i=0; i<(int)size; i++ )
            {
                if( isIn(ALLOWED_ASCII_REDUCED, ALLOWED_ASCII_REDUCED_LENGTH, buffer[i]) == false )
                {
                    printf("Test failed: <%c> is not allowed\n", buffer[i]);
                    return false;
                }
            }
            return true;
        case ALPHA_NUMERIC:
            for( int i=0; i<(int)size; i++ )
            {
                if( isalnum(buffer[i]) == false )
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
    
    // Ascii reduced
    format = ASCII_REDUCED;
    
    for( int n=0; n<NUM_RUNS; n++ )
    {
        KeyGenError rtn = keygen_createKey(buffer, SIZE, format);    

        TEST_RESULT(rtn == KG_ERR_SUCCESS);
        TEST_RESULT(testFormat(buffer, SIZE, format) == true);

        keygen_cleanBuffer(buffer, SIZE);
    }
    
    // Alphanumeric
    format = ALPHA_NUMERIC;
    
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


