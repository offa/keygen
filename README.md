# [KeyGen](https://github.com/offa/keygen)

KeyGen is a generator for random keys and passwords. It's usable as standalone application and library. 

The cryptography behind is provided by *OpenSSL*.

## Requirements

 - **OpenSSL**
 - **CMake** - for building
 - **Doxygen** - for documentation (*OPTIONAL*)

## Building

Building the library and application:

    mkdir build
    cmake ..
    make

Furthermore there are build targets either application or library. Run `make <Target>` to build them.

## Testing

After building the tests are executed within the build directory using:

    make test

*Note: CTest is used for testing.*

## Usage

The unit of length are (ascii-) characters (1 char = 1 byte). So a length of 20 means 20 (ascii-) char's = 20 Byte.

### Application

The application is used with commandline arguments. Run `keygen -h` to print the help.

#### Arguments:

     Usage: keygen [Options]

      --ascii	-a :  Generates a key of ASCII characters, ranging from '!' to '~' (default)
      --ascii-blank	-w :  Generates a key of ASCII characters, ranging from ' ' to '~'; same as --ascii, but includes blanks
      --length <n>	-l <n> :  Generates a key of <n> bytes length
      --short	-s :  Shows only the key
      --help	-h :  Shows the help
      --version	-v :  Shows version informations and license.

**Note:** For generating, the `--length` / `-l` parameter is *always* necessary.
 
**Examples:**

Key of 24 length:

    $ keygen -l 20

      Generated key:
    ----------
    amZ5QiX>9Z-=4U.XP;bD
    ----------
      Length : 20 / 20

this is equal to `keygen --ascii -l 20` and `keygen -a -l 20`.

The same key size, but with short (key only) output:

    $ keygen -s -l 20
    ZI^fD{dX<qa?uw?%'acM

Key of 4048 length and short output:

    $ keygen -s -l 4048
    dF45Wn\]}*AXI|`8.Xk5o#[m'qQ;Mo\Xa9d+USb(RP<o]#9^!MHlOU[6-SYB=*y:M' [...]

*(Reduced in this example)*

Key of 7 length (to short; not working):

    $ keygen -l 7
    A keylength of 7 is to short! A minimum length of 8 is required!

Key of 40 length, including blanks:

    $ keygen -w -l 40

        Generated key:
      ----------
      /ssA\KUJcwPPVO&r\Q"d({'XLfvWL#I<GgdH I "
      ----------
        Length : 40 / 40

Key of 4048 length, stored in a file:

    $ keygen --short --length 4048 > example.key

*(Use `--short` / `-s` to write key only)*

10 Keys of 40 length each (each key in a line):

    $ for i in {1..10}; do ./keygen -s -l 40 ; done;
    -lJ(rcm1UcD6lM}em-).w4WR;._c2}PH%3%5(+"C
    nM0c2H;CD8E`qhD)P<6(%e+P7&3L)XO"l;N%C):a
    b2KP^_Wq9WtVb+%w\k.Q(.+9D#[&8}.ZX*eb>/]a
    Aizu5%9f]5K7R_xnZu.:$-zn;CYQm09C3S"IIR'v
    Yh;%RYT8QG*hV?37@(Z5zX#7^:'URA1!-"iRLchM
    [q5Qho!s@uF*8jf8p3!&83*\`oZ,{_\mIv!:F?4/
    yGoheg3lnb/?+lP4?%C!BH`]M$,!B)dm<Qb*M3OH
    L4x(3kyry*y}]cd`w!^S(CvI1-yJ&sc[0Lf4x]')
    c;Ty$K+>,Art3+hX>}h-1P(5PH>e!<5IO31Oq+#y
    dlmn+&ECcuVk"<{AD*!g<4^6G.;YTb$4oLYN;KU9

Key of 40 length *Base64* encoded:

    $ keygen -s -l 40 | base64 
    Z1t5IWJJZUhKIi09PlVAXV1fQSRxfU57S3JPQiMnOklTMlQlNmExJgo=

A cool matrix-like screen (use fullscreen terminal for better experience):

    while :; do ./keygen -s -l $COLUMNS; sleep 0.1; done

*(Press `Ctrl+C` to quit)*

### Library

```c
#include <KeyGen.h>

// ...
const int KEY_LENGTH = 4048; // Key length
UByte buffer[KEY_LENGTH];    // Buffer holding the key

// Generate a key of Ascii characters
KeyGenError err = keygen_createKey(buffer, KEY_LENGTH, ASCII);

if( err == KG_ERR_SUCCESS )
{
    // Key generated, to something
}
else
{
    // Error - handle that case
}

// Finally clean the buffer 
keygen_cleanBuffer(buffer, length);
```

## Notes

 - The keylength is set to a minimum of 8 - lesser length is not allowed
 - Using parameter `-s` / `--short` will reduce the output to key only

## Documentation

 - [OpenSSL](https://www.openssl.org/)
 - [OpenSSL Wiki](http://wiki.openssl.org/index.php/Main_Page)

## License

**GNU General Public License (GPL)**

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
