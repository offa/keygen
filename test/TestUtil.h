/*
 * KeyGen is a key- and password generator.
 * Copyright (C) 2014-2025  offa
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

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

namespace test
{
    template <int streamFd>
    class DisableStream
    {
    public:
        explicit DisableStream(FILE* handle)
            : fileDescriptor(dup(streamFd)), fileHandle(handle)
        {
            fflush(fileHandle);
            [[maybe_unused]] const auto rtn = freopen("NUL", "a", fileHandle);
        }

        DisableStream(const DisableStream&) = delete;

        ~DisableStream()
        {
            fflush(fileHandle);
            dup2(fileDescriptor, streamFd);
        }

        DisableStream& operator=(const DisableStream&) = delete;


    private:
        const int fileDescriptor;
        FILE* fileHandle;
    };


    using DisableStdout = DisableStream<STDOUT_FILENO>;
    using DisableStderr = DisableStream<STDERR_FILENO>;
}
