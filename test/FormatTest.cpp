/*
 * KeyGen is a key- and password generator.
 * Copyright (C) 2014-2016  offa
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

#include <CppUTest/TestHarness.h>
#include <string.h>
#include "keygen/KeyGen.h"
#include "TestUtil.h"

extern const char ALPHANUMERIC_CHARS[];
extern const size_t ALPHANUMERIC_LENGTH;
extern const char ASCII_REDUCED_CHARS[];
extern const size_t ASCII_REDUCED_LENGTH;

TEST_GROUP(FormatTest)
{
    void setup()
    {
        size = 2000 * sizeof(UByte);
        buffer = allocate(size);
    }

    void teardown()
    {
        keygen_cleanAndFreeBuffer(buffer, size);
    }

    bool isIn(const char allowedChars[], size_t allowedCharsSize, char testFor)
    {
        for( size_t i=0; i<allowedCharsSize; i++ )
        {
            if( strchr(allowedChars, testFor) != NULL )
            {
                return true;
            }
        }

        return false;
    }

    bool testFormat(const UByte* buffer, size_t size, enum Format format)
    {
        switch(format)
        {
            case ASCII:
                for( size_t i=0; i<size; i++ )
                {
                    if( buffer[i] <= ' ' || buffer[i] > '~' )
                    {
                        FAIL("Invalid character");
                        return false;
                    }
                }
                return true;
            case ASCII_BLANKS:
                for( size_t i=0; i<size; i++ )
                {
                    if( buffer[i] < ' ' || buffer[i] > '~' )
                    {
                        FAIL("Invalid character");
                        return false;
                    }
                }
                return true;
            case ASCII_REDUCED:
                for( size_t i=0; i<size; i++ )
                {
                    if( isIn(ASCII_REDUCED_CHARS, ASCII_REDUCED_LENGTH, buffer[i]) == false )
                    {
                        FAIL("Invalid character");
                        return false;
                    }
                }
                return true;
            case ALPHA_NUMERIC:
                for( size_t i=0; i<size; i++ )
                {
                    if( isalnum(buffer[i]) == false )
                    {
                        FAIL("Invalid character");
                        return false;
                    }
                }
                return true;
            default:
                return false;
        }
    }

    size_t size;
    UByte* buffer;
};

TEST(FormatTest, formatAscii)
{
    const enum Format format = ASCII;
    KeyGenError rtn = keygen_createKey(buffer, size, format);
    CHECK_EQUAL(KG_ERR_SUCCESS, rtn);
    CHECK_EQUAL(true, testFormat(buffer, size, format));
}

TEST(FormatTest, formatAsciiBlanks)
{
    const enum Format format = ASCII_BLANKS;
    KeyGenError rtn = keygen_createKey(buffer, size, format);
    CHECK_EQUAL(KG_ERR_SUCCESS, rtn);
    CHECK_EQUAL(true, testFormat(buffer, size, format));
}

TEST(FormatTest, formatAsciiReduced)
{
    const enum Format format = ASCII_REDUCED;
    KeyGenError rtn = keygen_createKey(buffer, size, format);
    CHECK_EQUAL(KG_ERR_SUCCESS, rtn);
    CHECK_EQUAL(true, testFormat(buffer, size, format));
}

TEST(FormatTest, formatAlphaNumeric)
{
    const enum Format format = ALPHA_NUMERIC;
    KeyGenError rtn = keygen_createKey(buffer, size, format);
    CHECK_EQUAL(KG_ERR_SUCCESS, rtn);
    CHECK_EQUAL(true, testFormat(buffer, size, format));
}

TEST(FormatTest, formatIllegal)
{
    const enum Format format = (Format) 99;
    KeyGenError rtn = keygen_createKey(buffer, size, format);
    CHECK_EQUAL(KG_ERR_ILL_ARGUMENT, rtn);
}

