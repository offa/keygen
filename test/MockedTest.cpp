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
#include "TestUtil.h"
#include <cstdio>
#include <cstring>
#include <limits>
#include <array>
#include <catch2/catch_test_macros.hpp>
#include <catch2/trompeloeil.hpp>

extern const char ALPHANUMERIC_CHARS[];
extern const char ASCII_CHARS[];

namespace
{
    struct GeneratorMock
    {
        MAKE_MOCK2(randBytes, int(unsigned char*, int));
    };

    GeneratorMock m;
}

extern "C" int RAND_bytes(unsigned char* buf, int num)
{
    return m.randBytes(buf, num);
}

TEST_CASE("fail if generation of random bytes fails", "[MockedTest]")
{
    using trompeloeil::_;
    std::array<std::uint8_t, 10> buffer{{}};
    REQUIRE_CALL(m, randBytes(_, _)).RETURN(100);

    const test::DisableStderr d{stderr};
    const KeyGenError rtn = keygen_createKey(buffer.data(), buffer.size(), ASCII);
    CHECK(rtn == KG_ERR_SECURITY);
}

TEST_CASE("keysize exceeding int fails", "[MockedTest]")
{
    using trompeloeil::_;
    REQUIRE_CALL(m, randBytes(_, _)).TIMES(0);

    const test::DisableStderr d{stderr};
    constexpr std::size_t greaterThanInt = static_cast<std::size_t>(std::numeric_limits<int>::max()) + 30;
    const KeyGenError rtn = keygen_createKey(nullptr, greaterThanInt, ASCII);
    CHECK(rtn == KG_ERR_UNSUPPORTED);
}

TEST_CASE("keysize lower limit fails", "[MockedTest]")
{
    using trompeloeil::_;
    REQUIRE_CALL(m, randBytes(_, _)).TIMES(0);

    const test::DisableStderr d{stderr};
    const KeyGenError rtn = keygen_createKey(nullptr, 3, ASCII);
    CHECK(rtn == KG_ERR_UNSUPPORTED);
}

TEST_CASE("values below acceptance limit are mapped without rejection", "[MockedTest]")
{
    using trompeloeil::_;

    constexpr std::size_t length{8};
    std::array<std::uint8_t, length> initialBytes{};
    std::array<std::uint8_t, length> expected{};
    std::array<std::uint8_t, length> buffer{};

    for (std::size_t i = 0; i < length; ++i)
    {
        initialBytes[i] = static_cast<std::uint8_t>(i);
        expected[i] = static_cast<std::uint8_t>(ASCII_CHARS[i]);
    }

    REQUIRE_CALL(m, randBytes(_, static_cast<int>(length)))
        .LR_SIDE_EFFECT((std::memcpy(_1, initialBytes.data(), length)))
        .RETURN(1);
    REQUIRE_CALL(m, randBytes(_, 1)).TIMES(0);

    const KeyGenError rtn = keygen_createKey(buffer.data(), length, ASCII);

    CHECK(rtn == KG_ERR_SUCCESS);
    CHECK(buffer == expected);
}

TEST_CASE("rejected values are replaced by new random bytes", "[MockedTest]")
{
    using trompeloeil::_;

    constexpr std::size_t length{8};
    std::array<std::uint8_t, length> expected{};
    std::array<std::uint8_t, length> buffer{};
    expected.fill(static_cast<std::uint8_t>(ALPHANUMERIC_CHARS[0]));

    REQUIRE_CALL(m, randBytes(_, static_cast<int>(length)))
        .LR_SIDE_EFFECT((std::memset(_1, 0xFF, length)))
        .RETURN(1);
    REQUIRE_CALL(m, randBytes(_, 1))
        .TIMES(length)
        .LR_SIDE_EFFECT((std::memset(_1, 0x00, 1)))
        .RETURN(1);

    const KeyGenError rtn = keygen_createKey(buffer.data(), length, ALPHA_NUMERIC);

    CHECK(rtn == KG_ERR_SUCCESS);
    CHECK(buffer == expected);
}

TEST_CASE("failure during rejection leaves buffer untouched", "[MockedTest]")
{
    using trompeloeil::_;

    constexpr std::size_t length{8};
    std::array<std::uint8_t, length> buffer{};
    buffer.fill(static_cast<std::uint8_t>(0xAA));
    const auto expected = buffer;

    REQUIRE_CALL(m, randBytes(_, static_cast<int>(length)))
        .LR_SIDE_EFFECT((std::memset(_1, 0xFF, length)))
        .RETURN(1);
    REQUIRE_CALL(m, randBytes(_, 1))
        .RETURN(0);

    const test::DisableStderr d{stderr};
    const KeyGenError rtn = keygen_createKey(buffer.data(), length, ALPHA_NUMERIC);

    CHECK(rtn == KG_ERR_SECURITY);
    CHECK(buffer == expected);
}
