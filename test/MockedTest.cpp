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
#include <stdio.h>
#include <unistd.h>
#include <array>
#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

extern "C" int RAND_bytes(unsigned char* buf, int num)
{
    return mock().actualCall("RAND_bytes")
            .withOutputParameter("buf", buf)
            .withParameter("num", num)
            .returnIntValue();
}

TEST_GROUP(MockedTest)
{
    void setup()
    {
        disableStdErr();
    }

    void teardown()
    {
        mock().checkExpectations();
        mock().clear();

        enableStdErr();
    }

    void disableStdErr()
    {
        fflush(stderr);
        origStdErr = dup(STDERR_FILENO);
        freopen("NUL", "a", stderr);
    }

    void enableStdErr()
    {
        fflush(stderr);
        dup2(origStdErr, STDERR_FILENO);
    }


    int origStdErr;
};

TEST(MockedTest, returnErrorCodeOnFailedRandom)
{
    mock().expectOneCall("RAND_bytes")
            .ignoreOtherParameters()
            .andReturnValue(100);
    std::array<std::uint8_t, 10> buffer;

    const KeyGenError rtn = keygen_createKey(buffer.data(), buffer.size(), ASCII);
    CHECK_EQUAL(KG_ERR_SECURITY, rtn);
}
