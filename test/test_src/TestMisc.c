#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <KGKeyGen.h>

#include "TestUtils.h"


extern const char ALPHANUMERIC_CHARS[];
extern const unsigned int ALPHANUMERIC_LENGTH;

extern const char ASCII_BLANK_CHARS[];
extern const unsigned int ASCII_BLANK_LENGTH;

extern const char ASCII_CHARS[];
extern const unsigned int ASCII_LENGTH;


static void testFormatCharLengths()
{
    TEST_RESULT(ASCII_LENGTH == 94);
    TEST_RESULT(ASCII_BLANK_LENGTH == 95);
    TEST_RESULT(ALPHANUMERIC_LENGTH == 62);
}


int main(int argc, char** argv)
{
    UNUSED(argc);
    UNUSED(argv);

    testFormatCharLengths();

    return EXIT_SUCCESS;
}