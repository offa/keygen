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

/**
 * @file        KeyGen.c
 * @author      offa
 */

#include "keygen/KeyGen.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <openssl/rand.h>
#include <openssl/err.h>

/** Buffer size of error messages. */
#define ERR_MSG_LENGTH 128

/** Number of elements in the array */
#define COUNT_ARRAY_ELEMENTS(array) (sizeof(array) / sizeof((array)[0]))

/** Alphanumeric set */
const char ALPHANUMERIC_CHARS[] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E',
    'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
    'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
    'y', 'z'};

/** Reduced Ascii set */
const char ASCII_REDUCED_CHARS[] =
    {
        '!', '#', '$', '%', '&', '(', ')', '*', '+', ',', '-', '.', '/', '0', '1',
        '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@',
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
        'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', ']', '_', 'a',
        'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
        'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '}', '~'};

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


/**
 * Prints the last OpenSSL error message.
 */
static void printOpenSSLError(void)
{
    const unsigned long error = ERR_get_error();
    char errBuffer[ERR_MSG_LENGTH + 1]; // FlawFinder: ignore - Handled by ERR_error_string_n()

    ERR_error_string_n(error, errBuffer, sizeof(errBuffer));
    fprintf(stderr, "%s", errBuffer);
}

/**
 * Generates a single random byte.
 *
 * @param byte      Output byte
 * @return          Returns <code>KG_ERR_SUCCESS</code> on success or an
 *                  error code
 */
static KeyGenError getRandomByte(uint8_t* byte)
{
    assert(byte != NULL);

    if (RAND_bytes(byte, 1) != 1)
    {
        printOpenSSLError();
        return KG_ERR_SECURITY;
    }

    return KG_ERR_SUCCESS;
}

/**
 * Transforms the buffer to the given format.
 *
 * Each random byte is mapped onto the format using rejection sampling: values
 * at or above the largest multiple of <code>fmtLength</code> are discarded and
 * replaced by a newly generated random byte. This avoids the modulo bias that
 * would result from mapping the full <code>0-255</code> range directly.
 *
 * @param buffer        Input buffer
 * @param length        Input buffer length
 * @param fmtChars      Format char's
 * @param fmtLength     Format char's length
 * @return              Returns <code>KG_ERR_SUCCESS</code> on success or an
 *                      error code
 */
static KeyGenError transformBuffer(uint8_t* buffer, const size_t length,
                                   const char* fmtChars, const size_t fmtLength)
{
    assert(buffer != NULL);
    assert(length > 0);
    assert(fmtChars != NULL);

    const size_t numberOfByteValues = (size_t) UINT8_MAX + 1;

    if ((fmtLength == 0) || (fmtLength > numberOfByteValues))
    {
        return KG_ERR_ILL_ARGUMENT;
    }

    const size_t acceptanceLimit = numberOfByteValues - (numberOfByteValues % fmtLength);

    for (size_t i = 0; i < length; ++i)
    {
        size_t randomValue = (size_t) buffer[i];

        while (randomValue >= acceptanceLimit)
        {
            uint8_t extraByte = 0;
            const KeyGenError err = getRandomByte(&extraByte);

            if (err != KG_ERR_SUCCESS)
            {
                return err;
            }

            randomValue = (size_t) extraByte;
        }

        buffer[i] = (uint8_t) fmtChars[randomValue % fmtLength];
    }

    return KG_ERR_SUCCESS;
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
 * @return              Returns <code>KG_ERR_SUCCESS</code> on success or an
 *                      error code
 */
static KeyGenError getRandomBytes(uint8_t* buffer, size_t length)
{
    assert(length < INT_MAX);
    const int rtn = RAND_bytes(buffer, (int) length);

    if (rtn != 1)
    {
        printOpenSSLError();
        keygen_cleanBuffer(buffer, length);
        return KG_ERR_SECURITY;
    }

    return KG_ERR_SUCCESS;
}

static inline KeyGenError checkPreconditions(const uint8_t* buffer, size_t length)
{
    if ((length < KEY_MIN_LENGTH) || (length > KEY_MAX_LENGTH))
    {
        return KG_ERR_UNSUPPORTED;
    }

    if (buffer == NULL)
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
    const KeyGenError err = getRandomBytes(tmpBuffer, length);

    if (err == KG_ERR_SUCCESS)
    {
        KeyGenError transformResult = KG_ERR_UNKNOWN;

        switch (format)
        {
            case ASCII:
                transformResult = transformBuffer(tmpBuffer, length, ASCII_CHARS, COUNT_ARRAY_ELEMENTS(ASCII_CHARS));
                break;
            case ASCII_BLANKS:
                transformResult = transformBuffer(tmpBuffer, length, ASCII_BLANK_CHARS, COUNT_ARRAY_ELEMENTS(ASCII_BLANK_CHARS));
                break;
            case ASCII_REDUCED:
                transformResult = transformBuffer(tmpBuffer, length, ASCII_REDUCED_CHARS, COUNT_ARRAY_ELEMENTS(ASCII_REDUCED_CHARS));
                break;
            case ALPHA_NUMERIC:
                transformResult = transformBuffer(tmpBuffer, length, ALPHANUMERIC_CHARS, COUNT_ARRAY_ELEMENTS(ALPHANUMERIC_CHARS));
                break;
            default:
                transformResult = KG_ERR_ILL_ARGUMENT;
                break;
        }

        if (transformResult == KG_ERR_SUCCESS)
        {
            memcpy(buffer, tmpBuffer, length); // FlawFinder: ignore - size is same as input
            rtn = KG_ERR_SUCCESS;
        }
        else
        {
            rtn = transformResult;
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
