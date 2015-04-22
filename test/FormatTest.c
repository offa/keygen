
#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <KGKeyGen.h>

static bool testFormat(UByte* buffer, unsigned int size, enum Format format);


static unsigned int size;
static UByte* buffer;


void setUp()
{
    size = 2000 * sizeof(UByte);
    buffer = malloc(size);
}

void tearDown()
{
    keygen_cleanAndFreeBuffer(buffer, size);
}


TestSuite(FormatTest, .init = setUp, .fini = tearDown);

Test(FormatTest, testFormatAscii)
{
    const enum Format format = ASCII;
    KeyGenError rtn = keygen_createKey(buffer, size, format);
    assert_eq(KG_ERR_SUCCESS, rtn);
    assert_eq(true, testFormat(buffer, size, format));
}

Test(FormatTest, testFormatAsciiBlanks)
{
    const enum Format format = ASCII_BLANKS;
    KeyGenError rtn = keygen_createKey(buffer, size, format);
    assert_eq(KG_ERR_SUCCESS, rtn);
    assert_eq(true, testFormat(buffer, size, format));
}

Test(FormatTest, testFormatAsciiReduced)
{
    const enum Format format = ASCII_REDUCED;
    KeyGenError rtn = keygen_createKey(buffer, size, format);
    assert_eq(KG_ERR_SUCCESS, rtn);
    assert_eq(true, testFormat(buffer, size, format));
}

Test(FormatTest, testFormatAlphaNumeric)
{
    const enum Format format = ALPHA_NUMERIC;
    KeyGenError rtn = keygen_createKey(buffer, size, format);
    assert_eq(KG_ERR_SUCCESS, rtn);
    assert_eq(true, testFormat(buffer, size, format));
}

Test(FormatTest, testFormatIllegal)
{
    const enum Format format = 99;
    KeyGenError rtn = keygen_createKey(buffer, size, format);
    assert_eq(KG_ERR_ILL_ARGUMENT, rtn);
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
