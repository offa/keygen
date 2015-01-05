
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <KGKeyGen.h>

#include "TestUtils.h"




static const int NUM_RUNS = 1000;


int main(int argc, char** argv)
{
    UNUSED(argc);
    UNUSED(argv);


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

    return EXIT_SUCCESS;
}

