/*
 * KeyGen is a key- and password generator.
 * Copyright (C) 2014  offa
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
 * @file        KGKeyGen.c
 * 
 * @version     0.2
 * @author      offa
 * @date        21.10.2014
 */

#include <KGKeyGen.h>

#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <openssl/rand.h>
#include <openssl/err.h>

/** Buffer size of error messages. */
#define ERR_MSG_LENGTH              128

/** Ascii lower bound. */
#define LIM_ASCII_LOWER             '!'
/** Ascii upper bound. */
#define LIM_ASCII_UPPER             ( '~' - LIM_ASCII_LOWER )
/** Ascii lower bound (including blanks). */
#define LIM_ASCII_LOWER_BLANK       ' '
/** Ascii upper bound (including blanks). */
#define LIM_ASCII_UPPER_BLANK       ( '~' - LIM_ASCII_LOWER_BLANK )

static const char ALPHANUMERIC_CHARS[] =
{
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E',
    'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
    'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
    'y', 'z'
};

static const unsigned int ALPHANUMERIC_LENGTH = sizeof(ALPHANUMERIC_CHARS);


/**
 * Transforms the buffer to ascii.
 * 
 * @param buffer        Key buffer
 * @param length        Length (size)
 */
static inline void transformAscii(UByte* buffer, const unsigned int length)
{
    for( unsigned int i=0; i<length; i++ )
    {
        buffer[i] = LIM_ASCII_LOWER + ( buffer[i] % LIM_ASCII_UPPER );
    }
}

/**
 * Transforms the buffer to ascii with blanks.
 * 
 * @param buffer        Key buffer
 * @param length        Length (size)
 */
static inline void transformAsciiBlanks(UByte* buffer, const unsigned int length)
{
    for( unsigned int i=0; i<length; i++ )
    {
        buffer[i] = LIM_ASCII_LOWER_BLANK + ( buffer[i] % LIM_ASCII_UPPER_BLANK );
    }
}

/**
 * Transforms the buffer to alphanumeric.
 * 
 * @param buffer        Key buffer
 * @param length        Length (size)
 */
static inline void transformAlphaNumeric(UByte* buffer, const unsigned int length)
{
    for( unsigned i=0; i<length; i++ )
    {
        const unsigned int pos = buffer[i] % ALPHANUMERIC_LENGTH;
        assert(pos < ALPHANUMERIC_LENGTH);

        buffer[i] = ALPHANUMERIC_CHARS[pos];
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
static int getRandomBytes(UByte* buffer, int length)
{
    int rtn = RAND_bytes(buffer, length);

    if( rtn != ERR_LIB_NONE )
    {
        const unsigned long error = ERR_get_error();
        char errBuffer[ERR_MSG_LENGTH];

        ERR_error_string_n(error, errBuffer, ERR_MSG_LENGTH);
        fprintf(stderr, "%s", errBuffer);
        
        keygen_cleanBuffer(buffer, length);
    }

    return rtn;
}

KeyGenError keygen_createKey(UByte* buffer, const unsigned int length, enum Format format)
{
    if( buffer == NULL || length < KEY_MIN_LENGTH )
    {
        return KG_ERR_ILL_ARGUMENT;
    }
    
    KeyGenError rtn = KG_ERR_UNKNOWN;
    UByte random[length];
    int err = getRandomBytes(random, length);
    
    if( err == ERR_LIB_NONE )
    {
        bool error = false;
        
        switch(format)
        {
            case ASCII:
                transformAscii(random, length);
                break;
            case ASCII_BLANKS:
                transformAsciiBlanks(random, length);
                break;
            case ALPHA_NUMERIC:
                transformAlphaNumeric(random, length);
                break;
            default:
                rtn = KG_ERR_ILL_ARGUMENT;
                error = true;
                break;
        }
        
        if( error == false )
        {
            memcpy(buffer, random, length);
            rtn = KG_ERR_SUCCESS;
        }
        else
        {
            keygen_cleanBuffer(random, length);
        }
    }
    else
    {
        rtn = KG_ERR_SECURITY;
    }
    
    keygen_cleanBuffer(random, length);
    
    return rtn;
}

void keygen_cleanBuffer(UByte* buffer, unsigned int length)
{
    if( buffer != NULL && length > 0 )
    {
        OPENSSL_cleanse(buffer, length);
    }
}
