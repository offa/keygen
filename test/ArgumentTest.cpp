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
#include <catch2/catch.hpp>

using namespace Catch::Matchers;

TEST_CASE("tooShortLengthRejected", "[ArgumentTest]")
{
    std::array<std::uint8_t, 7> buffer{{}};

    const KeyGenError rtn = keygen_createKey(buffer.data(), buffer.size(), ASCII);
    CHECK(rtn == KG_ERR_ILL_ARGUMENT);
}

TEST_CASE("tooShortLengthDoesntChangeBuffer", "[ArgumentTest]")
{
    std::array<std::uint8_t, 7> buffer{{}};
    const std::array<std::uint8_t, 7> expected{{}};

    const KeyGenError rtn = keygen_createKey(buffer.data(), buffer.size(), ASCII);
    CHECK(rtn == KG_ERR_ILL_ARGUMENT);
    CHECK(buffer == expected);
}

TEST_CASE("allowedSizeGeneratesKey8Byte", "[ArgumentTest]")
{
    std::array<std::uint8_t, 8> buffer{{}};

    const KeyGenError rtn = keygen_createKey(buffer.data(), buffer.size(), ASCII);
    CHECK(rtn == KG_ERR_SUCCESS);
}

TEST_CASE("allowedSizeGeneratesKey1200Byte", "[ArgumentTest]")
{
    std::array<std::uint8_t, 1200> buffer{{}};

    const KeyGenError rtn = keygen_createKey(buffer.data(), buffer.size(), ASCII);
    CHECK(rtn == KG_ERR_SUCCESS);
}

