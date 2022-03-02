/*
  Copyright (c)      2012 Sascha Steinbiss <steinbiss@zbh.uni-hamburg.de>
  Copyright (c) 2008      Stefan Kurtz <kurtz@zbh.uni-hamburg.de>
  Copyright (c) 2008-2012 Center for Bioinformatics, University of Hamburg

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

#ifndef RBTREE_API_H
#define RBTREE_API_H

#include "core/error_api.h"
#include "core/fptr_api.h"
#include "core/types_api.h"

typedef enum
{
  GT_RBTREE_PREORDER,
  GT_RBTREE_POSTORDER,
  GT_RBTREE_ENDORDER,
  GT_RBTREE_LEAF
} GtRBTreeContext;

/* The <GtRBTree> class. Fast logarithmic data structure. This implementation
   does not allow storage of duplicates. */
typedef struct GtRBTree GtRBTree;
typedef struct GtRBTreeIter GtRBTreeIter;

typedef int   (*GtRBTreeAction)(void *key, GtRBTreeContext, GtUword, void*);
typedef void  (*GtRBTreeFreeFunc)(void *p);

/* Returns a new <GtRBTree> object. <free> might be NULL and will be used
   to free key-object otherwise. <info> is the data for the <cmp>-function. */
GtRBTree*      gt_rbtree_new(GtCompareWithData cmp, GtRBTreeFreeFunc free,
                             void *info);
void           gt_rbtree_delete(GtRBTree *tree);
/* Deletes all tree elements */
void           gt_rbtree_clear(GtRBTree *tree);

/* Returns <key> if element was found in <tree> and NULL if not */
void*          gt_rbtree_find(const GtRBTree *tree, void *key);
void*          gt_rbtree_find_with_cmp(const GtRBTree *tree, void *key,
                                       GtCompareWithData cmpfunc, void *info);
/* inserts <key> into <tree>. If <key> is already present in <tree>, it will not
   be changed. */
void           gt_rbtree_insert(GtRBTree *tree, void *key);
void           gt_rbtree_insert_with_cmp(GtRBTree *tree, void *key,
                                         GtCompareWithData cmpfunc,
                                         void *info);
/* Returns <key>, if <key> is not present in <tree>
   it will be inserted and <nodecreated> set accordingly */
void*          gt_rbtree_search(GtRBTree *tree, void *key, bool *nodecreated);
void*          gt_rbtree_search_with_cmp(GtRBTree *tree, void *key,
                                         GtCompareWithData cmpfunc,
                                         void *info, bool *nodecreated);
/* Remove <key> from <tree>, returns -1 if no such key exists and 0 on success
*/
int            gt_rbtree_erase(GtRBTree *tree, void *key);
size_t         gt_rbtree_size(const GtRBTree *tree);
int            gt_rbtree_walk(const GtRBTree *tree, GtRBTreeAction action,
                              void *actinfo);
int            gt_rbtree_walk_stop(const GtRBTree *tree, GtRBTreeAction action,
                                   void *actinfo);
int            gt_rbtree_walk_reverse(const GtRBTree *tree,
                                      GtRBTreeAction action,
                                      void *actinfo);
void*          gt_rbtree_minimum_key(const GtRBTree *tree);
void*          gt_rbtree_maximum_key(const GtRBTree *tree);
void*          gt_rbtree_root_key(const GtRBTree *tree);
void*          gt_rbtree_next_key(const GtRBTree *tree, void *key,
                                  GtCompareWithData cmpfun,
                                  void *cmpinfo);
void*          gt_rbtree_next_equal_key(const GtRBTree *tree, void *key,
                                        GtCompareWithData cmpfun,
                                        void *cmpinfo);
void*          gt_rbtree_previous_key(const GtRBTree *tree, void *key,
                                      GtCompareWithData cmpfun,
                                      void *cmpinfo);
void*          gt_rbtree_previous_equal_key(const GtRBTree *tree, void *key,
                                            GtCompareWithData cmpfun,
                                            void *cmpinfo);
int            gt_rbtree_unit_test(GtError *err);

/* Creates an iterator from the first (smallest) element. */
GtRBTreeIter*  gt_rbtree_iter_new_from_first(const GtRBTree *tree);
/* Creates an iterator from the last (largest) element */
GtRBTreeIter*  gt_rbtree_iter_new_from_last(const GtRBTree *tree);
/* Resets the iterator to the first (smallest) element. */
void           gt_rbtree_iter_reset_from_first(GtRBTreeIter *trav);
/* Resets the iterator to the last (largest) element. */
void           gt_rbtree_iter_reset_from_last(GtRBTreeIter *trav);
/* Return next (larger) key, NULL if iterator reached end. */
void*          gt_rbtree_iter_next(GtRBTreeIter *trav);
/* Return previous (smaller) key, NULL if iterator reached end. */
void*          gt_rbtree_iter_prev(GtRBTreeIter *trav);
/* Returns data of the current node the iterator <trav> is positioned on. */
void*          gt_rbtree_iter_data (GtRBTreeIter *trav);
/* free all memory of <trav> */
void           gt_rbtree_iter_delete(GtRBTreeIter *trav);

#endif
