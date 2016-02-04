/*
 * KeyGen is a key- and password generator.
 * Copyright (C) 2014-2016  offa
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

#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "keygen/Options.h"


static int origStdErr;

void setUpDisableStdErr()
{
    fflush(stderr);
    origStdErr = dup(STDERR_FILENO);
    FILE* unused = freopen("NUL", "a", stderr);
    (void) unused;
}

void tearDownResetStdErr()
{
    fflush(stderr);
    dup2(origStdErr, STDERR_FILENO);
}

void setUp()
{
    optind = 0;
}

TestSuite(OptionsTest, .init = setUp);

Test(OptionsTest, testNoArgsReturnsHelpAndExit)
{
    char* argv[] = { "OptionTest" };
    int argc = sizeof(argv) / sizeof(char*);

    struct CLOptions result = parseOptions(argc, argv);
    cr_assert_eq(true, result.valid);
    cr_assert_eq(true, result.showHelp);
    cr_assert_eq(true, result.exit);
}

Test(OptionsTest, testFormatArgumentAscii)
{
    char* argv[] = { "OptionTest", "-a" };
    int argc = sizeof(argv) / sizeof(char*);

    struct CLOptions result = parseOptions(argc, argv);

    cr_assert_eq(true, result.valid);
    cr_assert_eq(ASCII, result.keyFormat);
}

Test(OptionsTest, testFormatArgumentAsciiLong)
{
    char* argv[] = { "OptionTest", "--ascii" };
    int argc = sizeof(argv) / sizeof(char*);

    struct CLOptions result = parseOptions(argc, argv);

    cr_assert_eq(true, result.valid);
    cr_assert_eq(ASCII, result.keyFormat);
}

Test(OptionsTest, testFormatArgumentAsciiReduced)
{
    char* argv[] = { "OptionTest", "-r" };
    int argc = sizeof(argv) / sizeof(char*);

    struct CLOptions result = parseOptions(argc, argv);

    cr_assert_eq(true, result.valid);
    cr_assert_eq(ASCII_REDUCED, result.keyFormat);
}

Test(OptionsTest, testFormatArgumentAsciiReducedLong)
{
    char* argv[] = { "OptionTest", "--ascii-reduced" };
    int argc = sizeof(argv) / sizeof(char*);

    struct CLOptions result = parseOptions(argc, argv);

    cr_assert_eq(true, result.valid);
    cr_assert_eq(ASCII_REDUCED, result.keyFormat);
}

Test(OptionsTest, testFormatArgumentAsciiBlank)
{
    char* argv[] = { "OptionTest", "-w" };
    int argc = sizeof(argv) / sizeof(char*);

    struct CLOptions result = parseOptions(argc, argv);

    cr_assert_eq(true, result.valid);
    cr_assert_eq(ASCII_BLANKS, result.keyFormat);
}

Test(OptionsTest, testFormatArgumentAsciiBlankLong)
{
    char* argv[] = { "OptionTest", "--ascii-blank" };
    int argc = sizeof(argv) / sizeof(char*);

    struct CLOptions result = parseOptions(argc, argv);

    cr_assert_eq(true, result.valid);
    cr_assert_eq(ASCII_BLANKS, result.keyFormat);
}

Test(OptionsTest, testFormatArgumentAlphaNumeric)
{
    char* argv[] = { "OptionTest", "-p" };
    int argc = sizeof(argv) / sizeof(char*);

    struct CLOptions result = parseOptions(argc, argv);

    cr_assert_eq(true, result.valid);
    cr_assert_eq(ALPHA_NUMERIC, result.keyFormat);
}

Test(OptionsTest, testFormatArgumentAlphaNumericLong)
{
    char* argv[] = { "OptionTest", "--alphanum" };
    int argc = sizeof(argv) / sizeof(char*);

    struct CLOptions result = parseOptions(argc, argv);

    cr_assert_eq(true, result.valid);
    cr_assert_eq(ALPHA_NUMERIC, result.keyFormat);
}

Test(OptionsTest, testLength)
{
    char* argv[] = { "OptionTest", "-l", "10" };
    int argc = sizeof(argv) / sizeof(char*);

    struct CLOptions result = parseOptions(argc, argv);

    cr_assert_eq(true, result.valid);
    cr_assert_eq(10, result.keyLength);
}

Test(OptionsTest, testLengthLong)
{
    char* argv[] = { "OptionTest", "--length", "10" };
    int argc = sizeof(argv) / sizeof(char*);

    struct CLOptions result = parseOptions(argc, argv);

    cr_assert_eq(true, result.valid);
    cr_assert_eq(10, result.keyLength);
}

Test(OptionsTest, testFormatArgumentShort)
{
    char* argv[] = { "OptionTest", "-s" };
    int argc = sizeof(argv) / sizeof(char*);

    struct CLOptions result = parseOptions(argc, argv);

    cr_assert_eq(true, result.valid);
    cr_assert_eq(true, result.shortOutput);
}

Test(OptionsTest, testFormatArgumentShortLong)
{
    char* argv[] = { "OptionTest", "--short" };
    int argc = sizeof(argv) / sizeof(char*);

    struct CLOptions result = parseOptions(argc, argv);

    cr_assert_eq(true, result.valid);
    cr_assert_eq(true, result.shortOutput);
}

Test(OptionsTest, testShowHelp)
{
    char* argv[] = { "OptionTest", "-h" };
    int argc = sizeof(argv) / sizeof(char*);

    struct CLOptions result = parseOptions(argc, argv);

    cr_assert_eq(true, result.valid);
    cr_assert_eq(true, result.showHelp);
    cr_assert_eq(true, result.exit);
}

Test(OptionsTest, testShowHelpLong)
{
    char* argv[] = { "OptionTest", "--help" };
    int argc = sizeof(argv) / sizeof(char*);

    struct CLOptions result = parseOptions(argc, argv);

    cr_assert_eq(true, result.valid);
    cr_assert_eq(true, result.showHelp);
    cr_assert_eq(true, result.exit);
}

Test(OptionsTest, testShowVersion)
{
    char* argv[] = { "OptionTest", "-v" };
    int argc = sizeof(argv) / sizeof(char*);

    struct CLOptions result = parseOptions(argc, argv);

    cr_assert_eq(true, result.valid);
    cr_assert_eq(true, result.showVersion);
    cr_assert_eq(true, result.exit);
}

Test(OptionsTest, testShowVersionLong)
{
    char* argv[] = { "OptionTest", "--version" };
    int argc = sizeof(argv) / sizeof(char*);

    struct CLOptions result = parseOptions(argc, argv);

    cr_assert_eq(true, result.valid);
    cr_assert_eq(true, result.showVersion);
    cr_assert_eq(true, result.exit);
}

Test(OptionsTest, testInvalidOptionSetsInvalidAndExit,
        .init = setUpDisableStdErr,
        .fini = tearDownResetStdErr)
{
    char* argv[] = { "OptionTest", "-q" };
    int argc = sizeof(argv) / sizeof(char*);

    struct CLOptions result = parseOptions(argc, argv);

    cr_assert_eq(false, result.valid);
    cr_assert_eq(true, result.exit);
}
