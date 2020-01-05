/*
 * KeyGen is a key- and password generator.
 * Copyright (C) 2014-2020  offa
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

#include "keygen/Options.h"
#include "TestUtil.h"
#include <catch2/catch.hpp>

using namespace Catch::Matchers;

TEST_CASE("option evaluation", "[OptionsTest]")
{
    optind = 0;
    test::DisableStderr d{stderr};
    static char name[] = "OptionsTest";


    SECTION("testNoArgsReturnsHelpAndExit")
    {
        char* argv[] = {name};
        const int argc{1};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.showHelp == true);
        CHECK(result.exit == true);
    }

    SECTION("testFormatArgumentAscii")
    {
        char param[] = "-a";
        char* argv[] = {name, param};
        int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.keyFormat == ASCII);
    }

    SECTION("testFormatArgumentAsciiLong")
    {
        char param[] = "--ascii";
        char* argv[] = {name, param};
        const int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.keyFormat == ASCII);
    }

    SECTION("testFormatArgumentAsciiReduced")
    {
        char param[] = "-r";
        char* argv[] = {name, param};
        const int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.keyFormat == ASCII_REDUCED);
    }

    SECTION("testFormatArgumentAsciiReducedLong")
    {
        char param[] = "--ascii-reduced";
        char* argv[] = {name, param};
        const int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.keyFormat == ASCII_REDUCED);
    }

    SECTION("testFormatArgumentAsciiBlank")
    {
        char param[] = "-w";
        char* argv[] = {name, param};
        const int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.keyFormat == ASCII_BLANKS);
    }

    SECTION("testFormatArgumentAsciiBlankLong")
    {
        char param[] = "--ascii-blank";
        char* argv[] = {name, param};
        const int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.keyFormat == ASCII_BLANKS);
    }

    SECTION("testFormatArgumentAlphaNumeric")
    {
        char param[] = "-p";
        char* argv[] = {name, param};
        const int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.keyFormat == ALPHA_NUMERIC);
    }

    SECTION("testFormatArgumentAlphaNumericLong")
    {
        char param[] = "--alphanum";
        char* argv[] = {name, param};
        const int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.keyFormat == ALPHA_NUMERIC);
    }

    SECTION("testLength")
    {
        char param[] = "-l";
        char value[] = "10";
        char* argv[] = {name, param, value};
        const int argc{3};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.keyLength == 10);
    }

    SECTION("testLengthLong")
    {
        char param[] = "--length";
        char value[] = "10";
        char* argv[] = {name, param, value};
        const int argc{3};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.keyLength == 10);
    }

    SECTION("testFormatArgumentShort")
    {
        char param[] = "-s";
        char* argv[] = {name, param};
        const int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.shortOutput == true);
    }

    SECTION("testFormatArgumentShortLong")
    {
        char param[] = "--short";
        char* argv[] = {name, param};
        const int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.shortOutput == true);
    }

    SECTION("testShowHelp")
    {
        char param[] = "-h";
        char* argv[] = {name, param};
        const int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.showHelp == true);
        CHECK(result.exit == true);
    }

    SECTION("testShowHelpLong")
    {
        char param[] = "--help";
        char* argv[] = {name, param};
        const int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.showHelp == true);
        CHECK(result.exit == true);
    }

    SECTION("testShowVersion")
    {
        char param[] = "-v";
        char* argv[] = {name, param};
        const int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.showVersion == true);
        CHECK(result.exit == true);
    }

    SECTION("testShowVersionLong")
    {
        char param[] = "--version";
        char* argv[] = {name, param};
        const int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.showVersion == true);
        CHECK(result.exit == true);
    }

    SECTION("testInvalidOptionSetsInvalidAndExit")
    {
        char param[] = "-q";
        char* argv[] = {name, param};
        const int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == false);
        CHECK(result.exit == true);
    }
}
