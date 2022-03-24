/*
 * KeyGen is a key- and password generator.
 * Copyright (C) 2014-2022  offa
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

/**
 * @file        KeyGen.c
 * @author      offa
 */

#include "keygen/KeyGen.h"
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>
#include <openssl/rand.h>
#include <openssl/err.h>

/** Buffer size of error messages. */
#define ERR_MSG_LENGTH 128


/** Alphanumeric set */
const char ALPHANUMERIC_CHARS[] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E',
    'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
    'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
    'y', 'z'};

/** Number of alphanumeric chars */
const size_t ALPHANUMERIC_LENGTH = sizeof(ALPHANUMERIC_CHARS);


/** Reduced Ascii set */
const char ASCII_REDUCED_CHARS[] =
    {
        '!', '#', '$', '%', '&', '(', ')', '*', '+', ',', '-', '.', '/', '0', '1',
        '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@',
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
        'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', ']', '_', 'a',
        'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
        'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '}', '~'};

/** Number of reduced Ascii chars */
const size_t ASCII_REDUCED_LENGTH = sizeof(ASCII_REDUCED_CHARS);


/** Ascii set including blank char */
const char ASCII_BLANK_CHARS[] =
    {
        ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.',
        '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=',
        '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
        'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[',
        '\\', ']', '^', '_', '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
        'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y',
        'z', '{', '|', '}', '~'};

/** Number of Ascii chars including blank */
const size_t ASCII_BLANK_LENGTH = sizeof(ASCII_BLANK_CHARS);


/** Full Ascii chars */
const char ASCII_CHARS[] =
    {
        '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>',
        '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\',
        ']', '^', '_', '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
        'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        '{', '|', '}', '~'};

/** Number of full Ascii chars */
const size_t ASCII_LENGTH = sizeof(ASCII_CHARS);


/**
 * Transforms the buffer to the given format.
 *
 * @param buffer        Input buffer
 * @param length        Input buffer length
 * @param fmtChars      Format char's
 * @param fmtLength     Format char's length
 */
static void transformBuffer(uint8_t* buffer, const size_t length,
                            const char* fmtChars, const size_t fmtLength)
{
    assert(buffer != NULL);
    assert(length > 0);

    for (size_t i = 0; i < length; ++i)
    {
        const size_t pos = buffer[i] % fmtLength;
        buffer[i] = (uint8_t) fmtChars[pos];
    }
}

/**
 * Generates random bytes of length <code>length</code> and writes them into
 * <code>buffer</code>.
 *
 * @remark
 * On failure, the buffer is cleaned using <code>keygen_cleanBuffer()</code>.
 *
 * @param buffer        Buffer
 * @param length        Length (size)
 * @return              Returns <code>ERR_LIB_NONE</code> on success or an
 *                      error code
 */
static int getRandomBytes(uint8_t* buffer, size_t length)
{
    assert(length < INT_MAX);
    const int rtn = RAND_bytes(buffer, (int) length);

    if (rtn != ERR_LIB_NONE)
    {
        const unsigned long error = ERR_get_error();
        char errBuffer[ERR_MSG_LENGTH + 1]; // FlawFinder: ignore - Handled by ERR_error_string_n()

        ERR_error_string_n(error, errBuffer, ERR_MSG_LENGTH);
        fprintf(stderr, "%s", errBuffer);

        keygen_cleanBuffer(buffer, length);
    }

    return rtn;
}

static inline KeyGenError checkPreconditions(const uint8_t* buffer, size_t length)
{
    if (length > INT_MAX)
    {
        return KG_ERR_UNSUPPORTED;
    }

    if ((buffer == NULL) || (length < KEY_MIN_LENGTH))
    {
        return KG_ERR_ILL_ARGUMENT;
    }
    return KG_ERR_SUCCESS;
}

KeyGenError keygen_createKey(uint8_t* buffer, const size_t length, enum Format format)
{
    const KeyGenError preconditionResult = checkPreconditions(buffer, length);

    if (preconditionResult != KG_ERR_SUCCESS)
    {
        return preconditionResult;
    }

    uint8_t* tmpBuffer = malloc(length * sizeof(uint8_t));

    if (tmpBuffer == NULL)
    {
        return KG_ERR_MEMORY;
    }

    KeyGenError rtn = KG_ERR_UNKNOWN;
    const int err = getRandomBytes(tmpBuffer, length);

    if (err == ERR_LIB_NONE)
    {
        bool error = false;

        switch (format)
        {
            case ASCII:
                transformBuffer(tmpBuffer, length, ASCII_CHARS, ASCII_LENGTH);
                break;
            case ASCII_BLANKS:
                transformBuffer(tmpBuffer, length, ASCII_BLANK_CHARS, ASCII_BLANK_LENGTH);
                break;
            case ASCII_REDUCED:
                transformBuffer(tmpBuffer, length, ASCII_REDUCED_CHARS, ASCII_REDUCED_LENGTH);
                break;
            case ALPHA_NUMERIC:
                transformBuffer(tmpBuffer, length, ALPHANUMERIC_CHARS, ALPHANUMERIC_LENGTH);
                break;
            default:
                rtn = KG_ERR_ILL_ARGUMENT;
                error = true;
                break;
        }

        if (error == false)
        {
            memcpy(buffer, tmpBuffer, length); // FlawFinder: ignore - size is same as input
            rtn = KG_ERR_SUCCESS;
        }
    }
    else
    {
        rtn = KG_ERR_SECURITY;
    }

    keygen_cleanAndFreeBuffer(tmpBuffer, length);

    return rtn;
}

void keygen_cleanBuffer(uint8_t* buffer, size_t length)
{
    if (buffer != NULL && length > 0)
    {
        OPENSSL_cleanse(buffer, length);
    }
}

void keygen_cleanAndFreeBuffer(uint8_t* buffer, size_t length)
{
    keygen_cleanBuffer(buffer, length);
    free(buffer);
}
