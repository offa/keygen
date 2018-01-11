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

/**
 * @deprecated
 */
[[deprecated]]
inline uint8_t* allocate(size_t allocateSize)
{
    return static_cast<uint8_t*>(malloc(allocateSize));
}

inline int disableStdErr()
{
    fflush(stderr);
    const int origStdErr = dup(STDERR_FILENO);
    freopen("NUL", "a", stderr);
    return origStdErr;
}

inline void enableStdErr(int origStdErr)
{
    fflush(stderr);
    dup2(origStdErr, STDERR_FILENO);
}

#endif /* TESTUTIL_H */

