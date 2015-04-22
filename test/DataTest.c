
#include <criterion/criterion.h>
#include <stdlib.h>
#include <KGKeyGen.h>

extern const char ALPHANUMERIC_CHARS[];
extern const unsigned int ALPHANUMERIC_LENGTH;

extern const char ASCII_REDUCED_CHARS[];
extern const unsigned int ASCII_REDUCED_LENGTH;

extern const char ASCII_BLANK_CHARS[];
extern const unsigned int ASCII_BLANK_LENGTH;

extern const char ASCII_CHARS[];
extern const unsigned int ASCII_LENGTH;


TestSuite(DataTest);

Test(DataTest, testFormatCharsLength)
{
    assert_eq(94, ASCII_LENGTH);
    assert_eq(95, ASCII_BLANK_LENGTH);
    assert_eq(88, ASCII_REDUCED_LENGTH);
    assert_eq(62, ALPHANUMERIC_LENGTH);
}

Test(DataTest, testFormatChars)
{
    const char* charsAsciiReduced = "!#$%&()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]_abcdefghijklmnopqrstuvwxyz{}~";
    const char* charsAsciiBlanks = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    const char* charsAscii = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    const char* charsAlphaNum = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    
    
    int result = memcmp(charsAscii, ASCII_CHARS, ASCII_LENGTH);
    assert_eq(0, result);
    
    result = memcmp(charsAsciiBlanks, ASCII_BLANK_CHARS, ASCII_BLANK_LENGTH);
    assert_eq(0, result);
    
    result = memcmp(charsAsciiReduced, ASCII_REDUCED_CHARS, ASCII_REDUCED_LENGTH);
    assert_eq(0, result);
    
    result = memcmp(charsAlphaNum, ALPHANUMERIC_CHARS, ALPHANUMERIC_LENGTH);
    assert_eq(0, result);
}