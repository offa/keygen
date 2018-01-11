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

#ifndef TESTUTIL_H
#define TESTUTIL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

namespace test
{
    class DisableStdErr
    {
    public:

        DisableStdErr() : m_stdErrHandle(dup(STDERR_FILENO))
        {
            fflush(stderr);
            freopen("NUL", "a", stderr);
        }

        DisableStdErr(const DisableStdErr&) = delete;

        ~DisableStdErr()
        {
            fflush(stderr);
            dup2(m_stdErrHandle, STDERR_FILENO);
        }

        DisableStdErr& operator=(const DisableStdErr&) = delete;


    private:

        const int m_stdErrHandle;
    };
}

#endif /* TESTUTIL_H */

