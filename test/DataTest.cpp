/*
 * KeyGen is a key- and password generator.
 * Copyright (C) 2014-2026  offa
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
extern const char ASCII_REDUCED_CHARS[];
extern const char ASCII_BLANK_CHARS[];
extern const char ASCII_CHARS[];

TEST_CASE("formatChars", "[DataTest]")
{
    const std::string ascii{"!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"};
    const std::string asciiBlanks{" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"};
    const std::string asciiReduced{"!#$%&()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]_abcdefghijklmnopqrstuvwxyz{}~"};
    const std::string alphaNum{"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"};

    CHECK_THAT(std::string(ASCII_CHARS, 94u), Equals(ascii));
    CHECK_THAT(std::string(ASCII_BLANK_CHARS, 95u), Equals(asciiBlanks));
    CHECK_THAT(std::string(ASCII_REDUCED_CHARS, 88u), Equals(asciiReduced));
    CHECK_THAT(std::string(ALPHANUMERIC_CHARS, 62u), Equals(alphaNum));
}
