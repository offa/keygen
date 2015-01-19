#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <KGKeyGen.h>

#include "TestUtils.h"


extern const char ALPHANUMERIC_CHARS[];
extern const unsigned int ALPHANUMERIC_LENGTH;

extern const char ASCII_REDUCED_CHARS[];
extern const unsigned int ASCII_REDUCED_LENGTH;

extern const char ASCII_BLANK_CHARS[];
extern const unsigned int ASCII_BLANK_LENGTH;

extern const char ASCII_CHARS[];
extern const unsigned int ASCII_LENGTH;


static void testFormatCharLengths()
{
    TEST_RESULT(ASCII_LENGTH == 94);
    TEST_RESULT(ASCII_BLANK_LENGTH == 95);
    TEST_RESULT(ASCII_REDUCED_LENGTH == 88);
    TEST_RESULT(ALPHANUMERIC_LENGTH == 62);
}


static void testFormatChars()
{
    const char* charsAsciiReduced = "!#$%&()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]_abcdefghijklmnopqrstuvwxyz{}~";
    const char* charsAsciiBlanks = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    const char* charsAscii = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    const char* charsAlphaNum = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    
    
    int result = memcmp(charsAscii, ASCII_CHARS, ASCII_LENGTH);
    TEST_RESULT(result == 0);
    
    result = memcmp(charsAsciiBlanks, ASCII_BLANK_CHARS, ASCII_BLANK_LENGTH);
    TEST_RESULT(result == 0);
    
    result = memcmp(charsAsciiReduced, ASCII_REDUCED_CHARS, ASCII_REDUCED_LENGTH);
    TEST_RESULT(result == 0);
    
    result = memcmp(charsAlphaNum, ALPHANUMERIC_CHARS, ALPHANUMERIC_LENGTH);
    TEST_RESULT(result == 0);
}


int main(int argc, char** argv)
{
    UNUSED(argc);
    UNUSED(argv);

    testFormatCharLengths();
    testFormatChars();

    return EXIT_SUCCESS;
}