/*
  Copyright (c) 2007 Stefan Kurtz <kurtz@zbh.uni-hamburg.de>
  Copyright (c) 2007 Center for Bioinformatics, University of Hamburg

  Permission to use, copy, modify, and distribute this software for any
  purpose with or without fee is hereby granted, provided that the above
  copyright notice and this permission notice appear in all copies.

  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#ifndef MINMAX_API_H
#define MINMAX_API_H

/*
  This file defines macros for maximum and minimum computation,
  if they are not already defined.
*/

#ifndef GT_MAX
#define GT_MAX(X,Y) (((X) > (Y)) ? (X) : (Y))
#endif

#ifndef GT_MIN
#define GT_MIN(X,Y) (((X) < (Y)) ? (X) : (Y))
#endif

#ifndef GT_MIN3
#define GT_MIN3(a, b, c) (((a)<(b))?((a)<(c)?(a):(c)):((b)<(c)?(b):(c)))
#endif

#ifndef GT_MAX3
#define GT_MAX3(a, b, c) (((a)>(b))?((a)>(c)?(a):(c)):((b)>(c)?(b):(c)))
#endif

#define GT_UPDATE_MAX(MAXVAL,NEWVAL)\
        if ((MAXVAL) < (NEWVAL))\
        {\
          MAXVAL = NEWVAL;\
        }

#endif
