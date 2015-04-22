
#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <KGKeyGen.h>

static bool testFormat(UByte* buffer, unsigned int size, enum Format format);


TestSuite(FormatTest);

Test(ArgumentTest, testFormatAscii)
{
    const enum Format format = ASCII;
    const unsigned size = 2000 * sizeof(UByte);
    UByte* buffer = malloc(size);
    
    KeyGenError rtn = keygen_createKey(buffer, size, format);
    
    assert_eq(KG_ERR_SUCCESS, rtn);
    assert_eq(true, testFormat(buffer, size, format));
    keygen_cleanAndFreeBuffer(buffer, size);
}

Test(ArgumentTest, testFormatAsciiBlanks)
{
    const enum Format format = ASCII_BLANKS;
    const unsigned size = 2000 * sizeof(UByte);
    UByte* buffer = malloc(size);
    
    KeyGenError rtn = keygen_createKey(buffer, size, format);
    
    assert_eq(KG_ERR_SUCCESS, rtn);
    assert_eq(true, testFormat(buffer, size, format));
    keygen_cleanAndFreeBuffer(buffer, size);
}

Test(ArgumentTest, testFormatAsciiReduced)
{
    const enum Format format = ASCII_REDUCED;
    const unsigned size = 2000 * sizeof(UByte);
    UByte* buffer = malloc(size);
    
    KeyGenError rtn = keygen_createKey(buffer, size, format);
    
    assert_eq(KG_ERR_SUCCESS, rtn);
    assert_eq(true, testFormat(buffer, size, format));
    keygen_cleanAndFreeBuffer(buffer, size);
}

Test(ArgumentTest, testFormatAlphaNumeric)
{
    const enum Format format = ALPHA_NUMERIC;
    const unsigned size = 2000 * sizeof(UByte);
    UByte* buffer = malloc(size);
    
    KeyGenError rtn = keygen_createKey(buffer, size, format);
    
    assert_eq(KG_ERR_SUCCESS, rtn);
    assert_eq(true, testFormat(buffer, size, format));
    keygen_cleanAndFreeBuffer(buffer, size);
}

Test(ArgumentTest, testFormatIllegal)
{
    const enum Format format = 99;
    const unsigned size = 2000 * sizeof(UByte);
    UByte* buffer = malloc(size);
    
    KeyGenError rtn = keygen_createKey(buffer, size, format);
    
    assert_eq(KG_ERR_ILL_ARGUMENT, rtn);
    keygen_cleanAndFreeBuffer(buffer, size);
}


extern const char ALPHANUMERIC_CHARS[];
extern const unsigned int ALPHANUMERIC_LENGTH;

extern const char ASCII_REDUCED_CHARS[];
extern const unsigned int ASCII_REDUCED_LENGTH;

static bool isIn(const char allowedChars[], unsigned int allowedCharsSize, char testFor)
{
    for( unsigned int i=0; i<allowedCharsSize; i++ )
    {
        if( strchr(allowedChars, testFor) != NULL )
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
                if( isIn(ASCII_REDUCED_CHARS, ASCII_REDUCED_LENGTH, buffer[i]) == false )
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
