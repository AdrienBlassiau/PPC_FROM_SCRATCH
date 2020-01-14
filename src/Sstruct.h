/*

Copyright (c) 2019-2020, Adrien BLASSIAU and Corentin JUVIGNY

Permission to use, copy, modify, and/or distribute this software
for any purpose with or without fee is hereby granted, provided
that the above copyright notice and this permission notice appear
in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

*/

/** @file Sstruct.h
 *
 * @brief This file manages the S struct from the AC4 algorithm.
 */


#ifndef SSTRUCT__H
#define SSTRUCT__H

#include "duo.h"
#include "avl.h"

/**
 * \struct Sstruct
 * \brief Sstruct structure
 *
 * \a A Sstruct in a tab of var linked to an avl where the key is a value and
 * the content is a stack of duo
 *
 */
typedef struct Sstruct {
  PAVLTree* duo_tree;
  int size;
} Sstruct, *PSstruct;


/**
 * This function creates a new Sstruct.
 * @param  size The size of the Sstruct.
 * @return      A new Sstruct.
 */
PSstruct new_Sstruct(int size);

/**
 * This function frees the allocated space in the heap for the Sstruct.
 * @param  Ss The Sstruct we want to free.
 * @return    A NULL pointer.
 */
PSstruct free_Sstruct(PSstruct Ss);

/**
 * This function print a Sstruct.
 * @param  Ss The Sstruct we want to print.
 */
void print_Sstruct(PSstruct Ss);

/**
 * This function inserts a duo (var1, val1) associated to (var,key.
 * @param  Ss   The Ss struct
 * @param  var  The variable.
 * @param  key  The key associated to the variable.
 * @param  var1 The variable of the duo.
 * @param  val1 The value of the duo.
 * @return      1 if success, 0 otherwise.
 */
int insert_SStruct_duo(PSstruct Ss, int var, int key, int var1, int val1);

/**
 * This function queries a Ss according to a key (value) associated to a
 * variable.
 * @param  Ss  The Ss struct
 * @param  var The variable.
 * @param  key The key associated to the variable.
 * @return     NULL or the duostack asociated to (var,key).
 */
Pduostack query_SStruct(PSstruct Ss, int var, int key);


#endif