/*
 * KeyGen is a key- and password generator.
 * Copyright (C) 2014-2022  offa
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

#include "keygen/KeyGen.h"
#include <string>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

using Catch::Matchers::Equals;

extern const char ALPHANUMERIC_CHARS[];
extern const size_t ALPHANUMERIC_LENGTH;
extern const char ASCII_REDUCED_CHARS[];
extern const size_t ASCII_REDUCED_LENGTH;
extern const char ASCII_BLANK_CHARS[];
extern const size_t ASCII_BLANK_LENGTH;
extern const char ASCII_CHARS[];
extern const size_t ASCII_LENGTH;

TEST_CASE("formatCharsLength", "[DataTest]")
{
    CHECK(94u == ASCII_LENGTH);
    CHECK(95u == ASCII_BLANK_LENGTH);
    CHECK(88u == ASCII_REDUCED_LENGTH);
    CHECK(62u == ALPHANUMERIC_LENGTH);
}

TEST_CASE("formatChars", "[DataTest]")
{
    const std::string ascii{"!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"};
    const std::string asciiBlanks{" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"};
    const std::string asciiReduced{"!#$%&()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]_abcdefghijklmnopqrstuvwxyz{}~"};
    const std::string alphaNum{"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"};

    CHECK_THAT(std::string(ASCII_CHARS, ASCII_LENGTH), Equals(ascii));
    CHECK_THAT(std::string(ASCII_BLANK_CHARS, ASCII_BLANK_LENGTH), Equals(asciiBlanks));
    CHECK_THAT(std::string(ASCII_REDUCED_CHARS, ASCII_REDUCED_LENGTH), Equals(asciiReduced));
    CHECK_THAT(std::string(ALPHANUMERIC_CHARS, ALPHANUMERIC_LENGTH), Equals(alphaNum));
}
