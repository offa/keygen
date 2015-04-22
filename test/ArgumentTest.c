
#include <criterion/criterion.h>
#include <stdlib.h>
#include <KGKeyGen.h>


static unsigned int size;
static UByte* buffer;


void tearDown()
{
    keygen_cleanAndFreeBuffer(buffer, size);
}

TestSuite(ArgumentTest, .fini = tearDown);

Test(ArgumentTest, testToShortLengthRejected)
{
    size = 7 * sizeof(UByte);
    buffer = malloc(size);
    
    KeyGenError rtn = keygen_createKey(buffer, size, ASCII);
    assert_eq(KG_ERR_ILL_ARGUMENT, rtn);
}

Test(ArgumentTest, testToShortLengthDoesntChangeBuffer)
{
    size = 7 * sizeof(UByte);
    buffer = malloc(size);
    UByte expected[size];
    
    memset(expected, 0, size);
    memset(buffer, 0, size);
    
    KeyGenError rtn = keygen_createKey(buffer, size, ASCII);
    assert_eq(KG_ERR_ILL_ARGUMENT, rtn);
    assert_arrays_eq(expected, buffer, size);
}

Test(ArgumentTest, testAllowedSizeGeneratesKey8Byte)
{
    size = 8 * sizeof(UByte);
    buffer = malloc(size);
    
    KeyGenError rtn = keygen_createKey(buffer, size, ASCII);
    assert_eq(KG_ERR_SUCCESS, rtn);
}

Test(ArgumentTest, testAllowedSizeGeneratesKey1200Byte)
{
    size = 1200 * sizeof(UByte);
    buffer = malloc(size);
    
    KeyGenError rtn = keygen_createKey(buffer, size, ASCII);
    assert_eq(KG_ERR_SUCCESS, rtn);
}
