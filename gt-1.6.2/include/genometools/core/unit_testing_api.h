/*
  Copyright (c) 2003-2011 Gordon Gremme <gordon@gremme.org>
  Copyright (c) 2003-2008 Center for Bioinformatics, University of Hamburg

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

#ifndef UNIT_TESTING_API_H
#define UNIT_TESTING_API_H

#include "core/error_api.h"

/* UnitTest module */

/* A unit test function. It is assumed to return 0 on successful test
   completion, otherwise <err> should be set accordingly. */
typedef int (*GtUnitTestFunc)(GtError*);

/* Run unit test. <key> is expected to be a C string, <value> a
   <GtUnitTestFunc>. <data> is assumed to be a pointer to an int,
   containing the test return code. <err> should not be touched. */
int gt_unit_test_run(void *key, void *value, void *data, GtError *err);

#endif
