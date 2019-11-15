/*
 * KeyGen is a key- and password generator.
 * Copyright (C) 2014-2019  offa
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
#include <array>
#include <algorithm>
#include <catch2/catch.hpp>

using namespace Catch::Matchers;

extern const char ALPHANUMERIC_CHARS[];
extern const size_t ALPHANUMERIC_LENGTH;
extern const char ASCII_REDUCED_CHARS[];
extern const size_t ASCII_REDUCED_LENGTH;

namespace
{

    template<class Container>
    void testFormat(const Container& buffer, Format format)
    {
        std::for_each(buffer.cbegin(), buffer.cend(), [format](const auto& c)
        {
            switch( format )
            {
                case ASCII:
                    CHECK_FALSE(((c <= ' ') || (c > '~')));
                    break;
                case ASCII_BLANKS:
                    CHECK_FALSE(((c < ' ') || (c > '~')));
                    break;
                case ASCII_REDUCED:
                    CHECK(std::find(ASCII_REDUCED_CHARS, std::next(ASCII_REDUCED_CHARS, ASCII_REDUCED_LENGTH), c));
                    break;
                case ALPHA_NUMERIC:
                    CHECK(std::isalnum(c));
                    break;
                default:
                    FAIL("Invalid format");
                    break;
            }
        });
    }

    static constexpr std::size_t size{1000};
}

TEST_CASE("formatAscii", "[FormatTest]")
{
    constexpr Format format = ASCII;
    std::array<std::uint8_t, size> buffer{{}};
    const KeyGenError rtn = keygen_createKey(buffer.data(), buffer.size(), format);
    CHECK(rtn == KG_ERR_SUCCESS);
    testFormat(buffer, format);
}

TEST_CASE("formatAsciiBlanks", "[FormatTest]")
{
    constexpr Format format = ASCII_BLANKS;
    std::array<std::uint8_t, size> buffer{{}};
    const KeyGenError rtn = keygen_createKey(buffer.data(), buffer.size(), format);
    CHECK(rtn == KG_ERR_SUCCESS);
    testFormat(buffer, format);
}

TEST_CASE("formatAsciiReduced", "[FormatTest]")
{
    constexpr Format format = ASCII_REDUCED;
    std::array<std::uint8_t, size> buffer{{}};
    const KeyGenError rtn = keygen_createKey(buffer.data(), buffer.size(), format);
    CHECK(rtn == KG_ERR_SUCCESS);
    testFormat(buffer, format);
}

TEST_CASE("formatAlphaNumeric", "[FormatTest]")
{
    constexpr Format format = ALPHA_NUMERIC;
    std::array<std::uint8_t, size> buffer{{}};
    const KeyGenError rtn = keygen_createKey(buffer.data(), buffer.size(), format);
    CHECK(rtn == KG_ERR_SUCCESS);
    testFormat(buffer, format);
}

TEST_CASE("formatIllegal", "[FormatTest]")
{
    constexpr Format format = static_cast<Format>(99);
    std::array<std::uint8_t, size> buffer{{}};
    const KeyGenError rtn = keygen_createKey(buffer.data(), buffer.size(), format);
    CHECK(rtn == KG_ERR_ILL_ARGUMENT);
}

