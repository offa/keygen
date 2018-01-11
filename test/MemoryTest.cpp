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
#include <string.h>
#include <CppUTest/TestHarness.h>

TEST_GROUP(MemoryTest)
{
    static constexpr std::size_t size{1000};
    static constexpr std::size_t guardedSized{size + 4};
};

TEST(MemoryTest, testCleanUp)
{
    uint8_t* buffer = allocate(size);
    uint8_t expected[size];
    memset(expected, 0, size);

    const KeyGenError rtn = keygen_createKey(buffer, size, ASCII);
    CHECK_EQUAL(KG_ERR_SUCCESS, rtn);

    keygen_cleanBuffer(buffer, size);
    MEMCMP_EQUAL(expected, buffer, size);

    free(buffer);
}

TEST(MemoryTest, cleanUpBorderCheck)
{
    uint8_t* allocBuffer = allocate(guardedSized);
    uint8_t* buffer = allocBuffer + 2;
    uint8_t expected[guardedSized];

    memset(expected, 0, guardedSized);
    expected[0] = 0xCA;
    expected[1] = 0xFE;
    expected[guardedSized - 2] = 0xCA;
    expected[guardedSized - 1] = 0xFE;

    const KeyGenError rtn = keygen_createKey(buffer, size, ASCII);
    CHECK_EQUAL(KG_ERR_SUCCESS, rtn);

    keygen_cleanBuffer(buffer, size);
    MEMCMP_EQUAL(expected + 2, buffer, size);
    CHECK_EQUAL(0xCA, expected[0]);
    CHECK_EQUAL(0xFE, expected[1]);
    CHECK_EQUAL(0xCA, expected[guardedSized - 2]);
    CHECK_EQUAL(0xFE, expected[guardedSized - 1]);

    free(allocBuffer);
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
    uint8_t* allocBuffer = allocate(guardedSized);
    uint8_t* buffer = allocBuffer + 2;

    allocBuffer[0] = 0xCA;
    allocBuffer[1] = 0xFE;
    allocBuffer[guardedSized - 2] = 0xCA;
    allocBuffer[guardedSized - 1] = 0xFE;

    const KeyGenError rtn = keygen_createKey(buffer, size, ASCII);
    CHECK_EQUAL(KG_ERR_SUCCESS, rtn);

    CHECK_EQUAL(0xCA, allocBuffer[0]);
    CHECK_EQUAL(0XFE, allocBuffer[1]);
    CHECK_EQUAL(0xCA, allocBuffer[guardedSized - 2]);
    CHECK_EQUAL(0xFE, allocBuffer[guardedSized - 1]);

    keygen_cleanBuffer(buffer, size);

    CHECK_EQUAL(0xCA, allocBuffer[0]);
    CHECK_EQUAL(0XFE, allocBuffer[1]);
    CHECK_EQUAL(0xCA, allocBuffer[guardedSized - 2]);
    CHECK_EQUAL(0xFE, allocBuffer[guardedSized - 1]);

    free(allocBuffer);
}

