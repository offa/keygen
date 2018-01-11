/*
 * KeyGen is a key- and password generator.
 * Copyright (C) 2014-2018  offa
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
#include <vector>
#include <iterator>
#include <string.h>
#include <CppUTest/TestHarness.h>

TEST_GROUP(MemoryTest)
{
    std::vector<std::uint8_t> createGuardedBuffer(std::size_t n) const
    {
        std::vector<std::uint8_t> buffer(n, 0x00);
        buffer[0] = 0xCA;
        buffer[1] = 0xFE;
        buffer[n - 2] = 0xCA;
        buffer[n - 1] = 0xFE;
        return buffer;
    }

    static constexpr std::size_t size{1000};
    static constexpr std::size_t guardedSize{size + 4};
};

TEST(MemoryTest, testCleanUp)
{
    std::vector<std::uint8_t> buffer(size);
    std::vector<std::uint8_t> expected(size, 0x00);

    const KeyGenError rtn = keygen_createKey(buffer.data(), size, ASCII);
    CHECK_EQUAL(KG_ERR_SUCCESS, rtn);

    keygen_cleanBuffer(buffer.data(), size);
    MEMCMP_EQUAL(expected.data(), buffer.data(), size);
}

TEST(MemoryTest, cleanUpBorderCheck)
{
    const auto expected = createGuardedBuffer(guardedSize);
    auto buffer = createGuardedBuffer(guardedSize);
    auto startOfData = std::next(buffer.begin(), 2);

    const KeyGenError rtn = keygen_createKey(&(*startOfData), size, ASCII);
    CHECK_EQUAL(KG_ERR_SUCCESS, rtn);

    keygen_cleanBuffer(&(*startOfData), size);
    MEMCMP_EQUAL(expected.data(), buffer.data(), guardedSize);
}

TEST(MemoryTest, overlength)
{
    const size_t overLength =  1000000 * sizeof(uint8_t);

    uint8_t* buffer = allocate(overLength * sizeof(uint8_t));
    const KeyGenError rtn = keygen_createKey(buffer, overLength, ASCII);
    CHECK_EQUAL(KG_ERR_SUCCESS, rtn);

    free(buffer);
}

TEST(MemoryTest, overAndUnderflow)
{
    uint8_t* allocBuffer = allocate(guardedSize);
    uint8_t* buffer = allocBuffer + 2;

    allocBuffer[0] = 0xCA;
    allocBuffer[1] = 0xFE;
    allocBuffer[guardedSize - 2] = 0xCA;
    allocBuffer[guardedSize - 1] = 0xFE;

    const KeyGenError rtn = keygen_createKey(buffer, size, ASCII);
    CHECK_EQUAL(KG_ERR_SUCCESS, rtn);

    CHECK_EQUAL(0xCA, allocBuffer[0]);
    CHECK_EQUAL(0XFE, allocBuffer[1]);
    CHECK_EQUAL(0xCA, allocBuffer[guardedSize - 2]);
    CHECK_EQUAL(0xFE, allocBuffer[guardedSize - 1]);

    keygen_cleanBuffer(buffer, size);

    CHECK_EQUAL(0xCA, allocBuffer[0]);
    CHECK_EQUAL(0XFE, allocBuffer[1]);
    CHECK_EQUAL(0xCA, allocBuffer[guardedSize - 2]);
    CHECK_EQUAL(0xFE, allocBuffer[guardedSize - 1]);

    free(allocBuffer);
}

