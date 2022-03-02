/*
  Copyright (c) 2008, 2011 Gordon Gremme <gordon@gremme.org>
  Copyright (c) 2008 Center for Bioinformatics, University of Hamburg

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

#ifndef TYPE_CHECKER_OBO_API_H
#define TYPE_CHECKER_OBO_API_H

#include "extended/type_checker_api.h"

/* Implements the <GtTypeChecker> interface with types from an OBO file. */
typedef struct GtTypeCheckerOBO GtTypeCheckerOBO;

/* Create a new <GtTypeChecker*> for OBO file with given <obo_file_path>.
   If the OBO file cannot be parsed correctly, <NULL> is returned and <err> is
   set correspondingly. */
GtTypeChecker* gt_type_checker_obo_new(const char *obo_file_path, GtError *err);

#endif
