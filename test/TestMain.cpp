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

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <trompeloeil.hpp>


namespace trompeloeil
{
    template <>
    void reporter<specialized>::send(severity s, const char* file, unsigned long line, const char* msg)
    {
        std::ostringstream os;

        if( line )
        {
            os << file << ':' << line << '\n';
        }

        os << msg;
        const  auto failure = os.str();

        if( s == severity::fatal )
        {
            FAIL(failure);
        }
        else
        {
            CAPTURE(failure);
            CHECK(failure.empty());
        }
    }
}
