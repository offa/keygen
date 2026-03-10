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

#include "keygen/Options.h"
#include "TestUtil.h"
#include <algorithm>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("option evaluation", "[OptionsTest]")
{
    optind = 0;
    test::DisableStderr d{stderr};
    static char name[] = "OptionsTest";


    SECTION("testNoArgsReturnsHelpAndExit", "[OptionsTest]")
    {
        char* argv[] = {name};
        const int argc{1};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.showHelp == true);
        CHECK(result.exit == true);
    }

    SECTION("testFormatArgumentAscii", "[OptionsTest]")
    {
        char param[] = "-a";
        char* argv[] = {name, param};
        int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.keyFormat == ASCII);
    }

    SECTION("testFormatArgumentAsciiLong", "[OptionsTest]")
    {
        char param[] = "--ascii";
        char* argv[] = {name, param};
        const int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.keyFormat == ASCII);
    }

    SECTION("testFormatArgumentAsciiReduced", "[OptionsTest]")
    {
        char param[] = "-r";
        char* argv[] = {name, param};
        const int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.keyFormat == ASCII_REDUCED);
    }

    SECTION("testFormatArgumentAsciiReducedLong", "[OptionsTest]")
    {
        char param[] = "--ascii-reduced";
        char* argv[] = {name, param};
        const int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.keyFormat == ASCII_REDUCED);
    }

    SECTION("testFormatArgumentAsciiBlank", "[OptionsTest]")
    {
        char param[] = "-w";
        char* argv[] = {name, param};
        const int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.keyFormat == ASCII_BLANKS);
    }

    SECTION("testFormatArgumentAsciiBlankLong", "[OptionsTest]")
    {
        char param[] = "--ascii-blank";
        char* argv[] = {name, param};
        const int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.keyFormat == ASCII_BLANKS);
    }

    SECTION("testFormatArgumentAlphaNumeric", "[OptionsTest]")
    {
        char param[] = "-p";
        char* argv[] = {name, param};
        const int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.keyFormat == ALPHA_NUMERIC);
    }

    SECTION("testFormatArgumentAlphaNumericLong", "[OptionsTest]")
    {
        char param[] = "--alphanum";
        char* argv[] = {name, param};
        const int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.keyFormat == ALPHA_NUMERIC);
    }

    SECTION("testLength", "[OptionsTest]")
    {
        char param[] = "-l";
        char value[] = "10";
        char* argv[] = {name, param, value};
        const int argc{3};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.keyLength == 10);
    }

    SECTION("testLengthLong", "[OptionsTest]")
    {
        char param[] = "--length";
        char value[] = "10";
        char* argv[] = {name, param, value};
        const int argc{3};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.keyLength == 10);
    }

    SECTION("testLengthTooShort", "[OptionsTest]")
    {
        char param[] = "--length";
        char value[] = "1";
        char* argv[] = {name, param, value};
        const int argc{3};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == false);
        CHECK(result.exit == true);
    }

    SECTION("testLengthTooLong", "[OptionsTest]")
    {
        char param[] = "--length";
        const std::string oversize = std::to_string(static_cast<std::size_t>(std::numeric_limits<int>::max()) + 5);
        char value[32];
        std::copy_n(oversize.cbegin(), oversize.size() + 1, value);

        char* argv[] = {name, param, value};
        const int argc{3};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == false);
        CHECK(result.exit == true);
    }

    SECTION("testFormatArgumentShort", "[OptionsTest]")
    {
        char param[] = "-s";
        char* argv[] = {name, param};
        const int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.shortOutput == true);
    }

    SECTION("testFormatArgumentShortLong", "[OptionsTest]")
    {
        char param[] = "--short";
        char* argv[] = {name, param};
        const int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.shortOutput == true);
    }

    SECTION("testShowHelp", "[OptionsTest]")
    {
        char param[] = "-h";
        char* argv[] = {name, param};
        const int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.showHelp == true);
        CHECK(result.exit == true);
    }

    SECTION("testShowHelpLong", "[OptionsTest]")
    {
        char param[] = "--help";
        char* argv[] = {name, param};
        const int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.showHelp == true);
        CHECK(result.exit == true);
    }

    SECTION("testShowVersion", "[OptionsTest]")
    {
        char param[] = "-v";
        char* argv[] = {name, param};
        const int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.showVersion == true);
        CHECK(result.exit == true);
    }

    SECTION("testShowVersionLong", "[OptionsTest]")
    {
        char param[] = "--version";
        char* argv[] = {name, param};
        const int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == true);
        CHECK(result.showVersion == true);
        CHECK(result.exit == true);
    }

    SECTION("testInvalidOptionSetsInvalidAndExit", "[OptionsTest]")
    {
        char param[] = "-q";
        char* argv[] = {name, param};
        const int argc{2};

        const CLOptions result = parseOptions(argc, argv);

        CHECK(result.valid == false);
        CHECK(result.exit == true);
    }
}
