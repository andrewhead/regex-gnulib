/* Look at first character in UTF-8 string.
   Copyright (C) 1999-2000, 2002, 2006-2007, 2009-2016 Free Software
   Foundation, Inc.
   Written by Bruno Haible <bruno@clisp.org>, 2002.

   This program is free software: you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include <config.h>

/* Specification.  */
#include "unistr.h"

int
u8_strmbtouc (ucs4_t *puc, const uint8_t *s)
{
  /* Keep in sync with unistr.h and u8-mbtouc-aux.c.  */
  uint8_t c = *s;

  if (c < 0x80)
    {
      *puc = c;
      return (c != 0 ? 1 : 0);
    }
  if (c >= 0xc2)
    {
      if (c < 0xe0)
        {
#if CONFIG_UNICODE_SAFETY
          if ((s[1] ^ 0x80) < 0x40)
#else
          if (s[1] != 0)
#endif
            {
              *puc = ((unsigned int) (c & 0x1f) << 6)
                     | (unsigned int) (s[1] ^ 0x80);
              return 2;
            }
        }
      else if (c < 0xf0)
        {
#if CONFIG_UNICODE_SAFETY
          if ((s[1] ^ 0x80) < 0x40 && (s[2] ^ 0x80) < 0x40
              && (c >= 0xe1 || s[1] >= 0xa0)
              && (c != 0xed || s[1] < 0xa0))
#else
          if (s[1] != 0 && s[2] != 0)
#endif
            {
              *puc = ((unsigned int) (c & 0x0f) << 12)
                     | ((unsigned int) (s[1] ^ 0x80) << 6)
                     | (unsigned int) (s[2] ^ 0x80);
              return 3;
            }
        }
      else if (c < 0xf8)
        {
#if CONFIG_UNICODE_SAFETY
          if ((s[1] ^ 0x80) < 0x40 && (s[2] ^ 0x80) < 0x40
              && (s[3] ^ 0x80) < 0x40
              && (c >= 0xf1 || s[1] >= 0x90)
#if 1
              && (c < 0xf4 || (c == 0xf4 && s[1] < 0x90))
#endif
             )
#else
          if (s[1] != 0 && s[2] != 0 && s[3] != 0)
#endif
            {
              *puc = ((unsigned int) (c & 0x07) << 18)
                     | ((unsigned int) (s[1] ^ 0x80) << 12)
                     | ((unsigned int) (s[2] ^ 0x80) << 6)
                     | (unsigned int) (s[3] ^ 0x80);
              return 4;
            }
        }
#if 0
      else if (c < 0xfc)
        {
#if CONFIG_UNICODE_SAFETY
          if ((s[1] ^ 0x80) < 0x40 && (s[2] ^ 0x80) < 0x40
              && (s[3] ^ 0x80) < 0x40 && (s[4] ^ 0x80) < 0x40
              && (c >= 0xf9 || s[1] >= 0x88))
#else
          if (s[1] != 0 && s[2] != 0 && s[3] != 0 && s[4] != 0)
#endif
            {
              *puc = ((unsigned int) (c & 0x03) << 24)
                     | ((unsigned int) (s[1] ^ 0x80) << 18)
                     | ((unsigned int) (s[2] ^ 0x80) << 12)
                     | ((unsigned int) (s[3] ^ 0x80) << 6)
                     | (unsigned int) (s[4] ^ 0x80);
              return 5;
            }
        }
      else if (c < 0xfe)
        {
#if CONFIG_UNICODE_SAFETY
          if ((s[1] ^ 0x80) < 0x40 && (s[2] ^ 0x80) < 0x40
              && (s[3] ^ 0x80) < 0x40 && (s[4] ^ 0x80) < 0x40
              && (s[5] ^ 0x80) < 0x40
              && (c >= 0xfd || s[1] >= 0x84))
#else
          if (s[1] != 0 && s[2] != 0 && s[3] != 0 && s[4] != 0 && s[5] != 0)
#endif
            {
              *puc = ((unsigned int) (c & 0x01) << 30)
                     | ((unsigned int) (s[1] ^ 0x80) << 24)
                     | ((unsigned int) (s[2] ^ 0x80) << 18)
                     | ((unsigned int) (s[3] ^ 0x80) << 12)
                     | ((unsigned int) (s[4] ^ 0x80) << 6)
                     | (unsigned int) (s[5] ^ 0x80);
              return 6;
            }
        }
#endif
    }
  /* invalid or incomplete multibyte character */
  return -1;
}
