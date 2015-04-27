/*
 * KeyGen is a key- and password generator.
 * Copyright (C) 2014-2015  offa
 * 
 * This file is part of KeyGen.
 *
 * KeyGen is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * KeyGen is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with KeyGen.  If not, see <http://www.gnu.org/licenses/>.
 */

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
    cr_assert_eq(KG_ERR_ILL_ARGUMENT, rtn);
}

Test(ArgumentTest, testToShortLengthDoesntChangeBuffer)
{
    size = 7 * sizeof(UByte);
    buffer = malloc(size);
    UByte expected[size];
    
    memset(expected, 0, size);
    memset(buffer, 0, size);
    
    KeyGenError rtn = keygen_createKey(buffer, size, ASCII);
    cr_assert_eq(KG_ERR_ILL_ARGUMENT, rtn);
    cr_assert_arrays_eq(expected, buffer, size);
}

Test(ArgumentTest, testAllowedSizeGeneratesKey8Byte)
{
    size = 8 * sizeof(UByte);
    buffer = malloc(size);
    
    KeyGenError rtn = keygen_createKey(buffer, size, ASCII);
    cr_assert_eq(KG_ERR_SUCCESS, rtn);
}

Test(ArgumentTest, testAllowedSizeGeneratesKey1200Byte)
{
    size = 1200 * sizeof(UByte);
    buffer = malloc(size);
    
    KeyGenError rtn = keygen_createKey(buffer, size, ASCII);
    cr_assert_eq(KG_ERR_SUCCESS, rtn);
}
