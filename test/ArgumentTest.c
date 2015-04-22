
#include <criterion/criterion.h>
#include <stdlib.h>
#include <KGKeyGen.h>

TestSuite(ArgumentTest);

Test(ArgumentTest, testToShortLengthRejected)
{
    const unsigned size = 7 * sizeof(UByte);
    UByte* buffer = malloc(size);
    KeyGenError rtn = keygen_createKey(buffer, size, ASCII);
    
    assert_eq(KG_ERR_ILL_ARGUMENT, rtn);
    keygen_cleanAndFreeBuffer(buffer, size);
}

Test(ArgumentTest, testToShortLengthDoesntChangeBuffer)
{
    const unsigned size = 7 * sizeof(UByte);
    UByte expected[size];
    UByte* buffer = malloc(size);
    
    memset(expected, 0, size);
    memset(buffer, 0, size);
    
    KeyGenError rtn = keygen_createKey(buffer, size, ASCII);
    
    assert_eq(KG_ERR_ILL_ARGUMENT, rtn);
    assert_arrays_eq(expected, buffer, size);
    
    keygen_cleanAndFreeBuffer(buffer, size);
}

Test(ArgumentTest, testAllowedSizeGeneratesKey8Byte)
{
    const unsigned size = 8 * sizeof(UByte);
    UByte* buffer = malloc(size);
    KeyGenError rtn = keygen_createKey(buffer, size, ASCII);
    
    assert_eq(KG_ERR_SUCCESS, rtn);
    keygen_cleanAndFreeBuffer(buffer, size); 
}

Test(ArgumentTest, testAllowedSizeGeneratesKey1200Byte)
{
    const unsigned size = 1200 * sizeof(UByte);
    UByte* buffer = malloc(size);
    KeyGenError rtn = keygen_createKey(buffer, size, ASCII);
    
    assert_eq(KG_ERR_SUCCESS, rtn);
    keygen_cleanAndFreeBuffer(buffer, size); 
}