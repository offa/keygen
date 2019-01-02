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
#include "TestUtil.h"
#include <array>
#include <iterator>
#include <string.h>
#include <catch2/catch.hpp>

using namespace Catch::Matchers;

namespace
{
    static constexpr std::size_t size{1000};
    static constexpr std::size_t guardedSize{size + 4};

    template<std::size_t n>
    constexpr std::array<std::uint8_t, n> createGuardedBuffer()
    {
        std::array<std::uint8_t, n> buffer{{0}};
        buffer[0] = 0xCA;
        buffer[1] = 0xFE;
        buffer[n - 2] = 0xCA;
        buffer[n - 1] = 0xFE;
        return buffer;
    }

    template<class Container>
    void checkGuards(const Container& buffer)
    {
        CHECK(buffer[0] == 0xCA);
        CHECK(buffer[1] == 0xFE);
        CHECK(buffer[guardedSize - 2] == 0xCA);
        CHECK(buffer[guardedSize - 1] == 0xFE);
    }

}

TEST_CASE("testCleanUp", "[MemoryTest]")
{
    std::array<std::uint8_t, size> buffer{{0}};
    std::array<std::uint8_t, size> expected{{0}};

    const KeyGenError rtn = keygen_createKey(buffer.data(), size, ASCII);
    CHECK(rtn == KG_ERR_SUCCESS);

    keygen_cleanBuffer(buffer.data(), size);
    CHECK(buffer == expected);
}

TEST_CASE("cleanUpBorderCheck", "[MemoryTest]")
{
    const auto expected = createGuardedBuffer<guardedSize>();
    auto buffer = createGuardedBuffer<guardedSize>();
    auto startOfData = std::next(buffer.begin(), 2);

    const KeyGenError rtn = keygen_createKey(&(*startOfData), size, ASCII);
    CHECK(rtn == KG_ERR_SUCCESS);

    keygen_cleanBuffer(&(*startOfData), size);
    CHECK(buffer == expected);
}

TEST_CASE("overlength", "[MemoryTest]")
{
    constexpr std::size_t overLength{2048};
    std::array<std::uint8_t, overLength> buffer{{0}};

    const KeyGenError rtn = keygen_createKey(buffer.data(), overLength, ASCII);
    CHECK(rtn == KG_ERR_SUCCESS);
}

TEST_CASE("overAndUnderflow", "[MemoryTest]")
{
    auto buffer = createGuardedBuffer<guardedSize>();
    auto startOfData = std::next(buffer.begin(), 2);

    const KeyGenError rtn = keygen_createKey(&(*startOfData), size, ASCII);
    CHECK(rtn == KG_ERR_SUCCESS);

    checkGuards(buffer);
    keygen_cleanBuffer(&(*startOfData), size);
    checkGuards(buffer);
}

