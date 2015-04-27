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
    cr_assert_eq(94, ASCII_LENGTH);
    cr_assert_eq(95, ASCII_BLANK_LENGTH);
    cr_assert_eq(88, ASCII_REDUCED_LENGTH);
    cr_assert_eq(62, ALPHANUMERIC_LENGTH);
}

Test(DataTest, testFormatChars)
{
    const char* charsAsciiReduced = "!#$%&()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]_abcdefghijklmnopqrstuvwxyz{}~";
    const char* charsAsciiBlanks = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    const char* charsAscii = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    const char* charsAlphaNum = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    
    
    int result = memcmp(charsAscii, ASCII_CHARS, ASCII_LENGTH);
    cr_assert_eq(0, result);
    
    result = memcmp(charsAsciiBlanks, ASCII_BLANK_CHARS, ASCII_BLANK_LENGTH);
    cr_assert_eq(0, result);
    
    result = memcmp(charsAsciiReduced, ASCII_REDUCED_CHARS, ASCII_REDUCED_LENGTH);
    cr_assert_eq(0, result);
    
    result = memcmp(charsAlphaNum, ALPHANUMERIC_CHARS, ALPHANUMERIC_LENGTH);
    cr_assert_eq(0, result);
}
