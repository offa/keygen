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

#include "keygen/Options.h"
#include "TestUtil.h"
#include <catch.hpp>

using namespace Catch::Matchers;

namespace
{
    void reset()
    {
        optind = 0;
    }

    static char name[] = "OptionsTest";
}


TEST_CASE("testNoArgsReturnsHelpAndExit", "[OptionsTest]")
{
    reset();
    char* argv[] = {name};
    const int argc{1};

    const CLOptions result = parseOptions(argc, argv);

    CHECK(result.valid == true);
    CHECK(result.showHelp == true);
    CHECK(result.exit == true);
}

TEST_CASE("testFormatArgumentAscii", "[OptionsTest]")
{
    reset();
    char param[] = "-a";
    char* argv[] = {name, param};
    int argc{2};

    const CLOptions result = parseOptions(argc, argv);

    CHECK(result.valid == true);
    CHECK(result.keyFormat == ASCII);
}

TEST_CASE("testFormatArgumentAsciiLong", "[OptionsTest]")
{
    reset();
    char param[] = "--ascii";
    char* argv[] = {name, param};
    const int argc{2};

    const CLOptions result = parseOptions(argc, argv);

    CHECK(result.valid == true);
    CHECK(result.keyFormat == ASCII);
}

TEST_CASE("testFormatArgumentAsciiReduced", "[OptionsTest]")
{
    reset();
    char param[] = "-r";
    char* argv[] = {name, param};
    const int argc{2};

    const CLOptions result = parseOptions(argc, argv);

    CHECK(result.valid == true);
    CHECK(result.keyFormat == ASCII_REDUCED);
}

TEST_CASE("testFormatArgumentAsciiReducedLong", "[OptionsTest]")
{
    reset();
    char param[] = "--ascii-reduced";
    char* argv[] = {name, param};
    const int argc{2};

    const CLOptions result = parseOptions(argc, argv);

    CHECK(result.valid == true);
    CHECK(result.keyFormat == ASCII_REDUCED);
}

TEST_CASE("testFormatArgumentAsciiBlank", "[OptionsTest]")
{
    reset();
    char param[] = "-w";
    char* argv[] = {name, param};
    const int argc{2};

    const CLOptions result = parseOptions(argc, argv);

    CHECK(result.valid == true);
    CHECK(result.keyFormat == ASCII_BLANKS);
}

TEST_CASE("testFormatArgumentAsciiBlankLong", "[OptionsTest]")
{
    reset();
    char param[] = "--ascii-blank";
    char* argv[] = {name, param};
    const int argc{2};

    const CLOptions result = parseOptions(argc, argv);

    CHECK(result.valid == true);
    CHECK(result.keyFormat == ASCII_BLANKS);
}

TEST_CASE("testFormatArgumentAlphaNumeric", "[OptionsTest]")
{
    reset();
    char param[] = "-p";
    char* argv[] = {name, param};
    const int argc{2};

    const CLOptions result = parseOptions(argc, argv);

    CHECK(result.valid == true);
    CHECK(result.keyFormat == ALPHA_NUMERIC);
}

TEST_CASE("testFormatArgumentAlphaNumericLong", "[OptionsTest]")
{
    reset();
    char param[] = "--alphanum";
    char* argv[] = {name, param};
    const int argc{2};

    const CLOptions result = parseOptions(argc, argv);

    CHECK(result.valid == true);
    CHECK(result.keyFormat == ALPHA_NUMERIC);
}

TEST_CASE("testLength", "[OptionsTest]")
{
    reset();
    char param[] = "-l";
    char value[] = "10";
    char* argv[] = {name, param, value};
    const int argc{3};

    const CLOptions result = parseOptions(argc, argv);

    CHECK(result.valid == true);
    CHECK(result.keyLength == 10);
}

TEST_CASE("testLengthLong", "[OptionsTest]")
{
    reset();
    char param[] = "--length";
    char value[] = "10";
    char* argv[] = {name, param, value};
    const int argc{3};

    const CLOptions result = parseOptions(argc, argv);

    CHECK(result.valid == true);
    CHECK(result.keyLength == 10);
}

TEST_CASE("testFormatArgumentShort", "[OptionsTest]")
{
    reset();
    char param[] = "-s";
    char* argv[] = {name, param};
    const int argc{2};

    const CLOptions result = parseOptions(argc, argv);

    CHECK(result.valid == true);
    CHECK(result.shortOutput == true);
}

TEST_CASE("testFormatArgumentShortLong", "[OptionsTest]")
{
    reset();
    char param[] = "--short";
    char* argv[] = {name, param};
    const int argc{2};

    const CLOptions result = parseOptions(argc, argv);

    CHECK(result.valid == true);
    CHECK(result.shortOutput == true);
}

TEST_CASE("testShowHelp", "[OptionsTest]")
{
    reset();
    char param[] = "-h";
    char* argv[] = {name, param};
    const int argc{2};

    const CLOptions result = parseOptions(argc, argv);

    CHECK(result.valid == true);
    CHECK(result.showHelp == true);
    CHECK(result.exit == true);
}

TEST_CASE("testShowHelpLong", "[OptionsTest]")
{
    reset();
    char param[] = "--help";
    char* argv[] = {name, param};
    const int argc{2};

    const CLOptions result = parseOptions(argc, argv);

    CHECK(result.valid == true);
    CHECK(result.showHelp == true);
    CHECK(result.exit == true);
}

TEST_CASE("testShowVersion", "[OptionsTest]")
{
    reset();
    char param[] = "-v";
    char* argv[] = {name, param};
    const int argc{2};

    const CLOptions result = parseOptions(argc, argv);

    CHECK(result.valid == true);
    CHECK(result.showVersion == true);
    CHECK(result.exit == true);
}

TEST_CASE("testShowVersionLong", "[OptionsTest]")
{
    reset();
    char param[] = "--version";
    char* argv[] = {name, param};
    const int argc{2};

    const CLOptions result = parseOptions(argc, argv);

    CHECK(result.valid == true);
    CHECK(result.showVersion == true);
    CHECK(result.exit == true);
}

TEST_CASE("testInvalidOptionSetsInvalidAndExit", "[OptionsTest]")
{
    reset();
    char param[] = "-q";
    char* argv[] = {name, param};
    const int argc{2};

    test::DisableStdErr d;
    const CLOptions result = parseOptions(argc, argv);

    CHECK(result.valid == false);
    CHECK(result.exit == true);
}
