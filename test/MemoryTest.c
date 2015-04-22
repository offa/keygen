
#include <criterion/criterion.h>
#include <stdlib.h>
#include <KGKeyGen.h>

TestSuite(MemoryTest);

Test(MemoryTest, testCleanUp)
{
    const unsigned int size = 1000 * sizeof(UByte);
    UByte* buffer = malloc(size);
    UByte expected[size];
    
    memset(expected, 0, size);
    
    KeyGenError rtn = keygen_createKey(buffer, size, ASCII);
    assert_eq(KG_ERR_SUCCESS, rtn);
    
    keygen_cleanBuffer(buffer, size);
    assert_arrays_eq(expected, buffer, size);
    
    free(buffer);
}

Test(MemoryTest, testCleanUpBorderCheck)
{
    const unsigned int size = 1000 * sizeof(UByte);
    const unsigned int allocSize = size + 4;
    UByte* allocBuffer = malloc(allocSize);
    UByte* buffer = allocBuffer + 2;
    UByte expected[size];
    
    memset(expected, 0, allocSize);
    expected[0] = 0xCA;
    expected[1] = 0xFE;
    expected[allocSize - 2] = 0xCA;
    expected[allocSize - 1] = 0xFE;
    
    KeyGenError rtn = keygen_createKey(buffer, size, ASCII);
    assert_eq(KG_ERR_SUCCESS, rtn);
    
    keygen_cleanBuffer(buffer, size);
    assert_arrays_eq(expected + 2, buffer, size);
    assert_eq(0xCA, expected[0]);
    assert_eq(0xFE, expected[1]);
    assert_eq(0xCA, expected[allocSize - 2]);
    assert_eq(0xFE, expected[allocSize - 1]);
    
    free(allocBuffer);
}

Test(MemoryTest, testOverlength)
{
    const unsigned int overLength =  1000000 * sizeof(UByte);
    
    UByte* buffer = malloc(overLength * sizeof(UByte));
    KeyGenError rtn = keygen_createKey(buffer, overLength, ASCII);
    
    assert_eq(KG_ERR_SUCCESS, rtn);
    
    keygen_cleanAndFreeBuffer(buffer, overLength);
}

Test(MemoryTest, testOverAndUnderflow)
{
    const unsigned int size = 1000 * sizeof(UByte);
    const unsigned int allocSize = size + 4;
    UByte* allocBuffer = malloc(allocSize);
    UByte* buffer = allocBuffer + 2;
    
    allocBuffer[0] = 0xCA;
    allocBuffer[1] = 0xFE;
    allocBuffer[allocSize - 2] = 0xCA;
    allocBuffer[allocSize - 1] = 0xFE;
    
    KeyGenError rtn = keygen_createKey(buffer, size, ASCII);
    assert_eq(KG_ERR_SUCCESS, rtn);
    
    assert_eq(0xCA, allocBuffer[0]);
    assert_eq(0XFE, allocBuffer[1]);
    assert_eq(0xCA, allocBuffer[allocSize - 2]);
    assert_eq(0xFE, allocBuffer[allocSize - 1]);
    
    keygen_cleanBuffer(buffer, size);
    
    assert_eq(0xCA, allocBuffer[0]);
    assert_eq(0XFE, allocBuffer[1]);
    assert_eq(0xCA, allocBuffer[allocSize - 2]);
    assert_eq(0xFE, allocBuffer[allocSize - 1]);
    
    free(allocBuffer);
}