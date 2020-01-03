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


/** @file tuple.h
 *
 * @brief This file manages the association list of a the content of a
 * variable with his associated domain (content of the second variable of the
 * domain).
 */

#ifndef TUPLE__H
#define TUPLE__H

#include "avl.h"
#include "domain.h"

/**
 * \struct tuple
 * \brief tuple structure
 *
 * \a A tuple structure is a set of tuple associated to a domain
 *
 */
typedef struct tuple {
  PAVLTree tuples;
  unsigned int iterator;
  AVLTreeValue *tuples_tab;
  AVLTreeValue *tuples_key;
} tuple, *Ptuple;

/**
 * This function creates a new tuple list.
 * @return The function returns a new variable list.
 */
Ptuple new_tuple();

/**
 * This function free the allocated space on the heap for our tuple struc.
 * @param  t The tuple struct.
 * @return   A NULL pointer;
 */
Ptuple free_tuple(Ptuple t);

/**
 * This function free the allocated space on the heap for our tuple struc.
 * @param  t The tuple struct.
 * @return   A NULL pointer;
 */
void free_tuple_bis(void *vt);

/**
 * This functions computes the number of tuple we have.
 * @param  t The tuple struct.
 * @return   The number of tuple.
 */
unsigned int get_tuple_number(Ptuple t);

/**
 * This function returns the domains of all tuple.
 * @param  t The tuple struct.
 * @return   The domain of all tuple
 */
PAVLTree get_tuples(Ptuple t);

/**
 * This function set the tuple struc iterator.
 * @param v   The tuple struct.
 * @param val The value of the iterator.
 */
void set_tuple_iterator(Ptuple t, unsigned int val);

/**
 * This function begins the tuple list iterations.
 * @param v The tuple struct.
 */
void begin_tuple_iteration(Ptuple t);

/**
 * This function iterates over the tuple struct until it's empty.
 * @param  t The tuple struct.
 * @return 1 if we can iterate, 0 otherwise.
 */
int tuple_can_iterate(Ptuple t);

/**
 * This function returns the current value pointed by the iterator.
 * @param  t The tuple struct.
 * @return   The domain of the current variable.
 */
int get_tuple_current_key(Ptuple t);

/**
 * This function returns the current value pointed by the iterator.
 * @param  t The tuple struct.
 * @return   The domain of the current variable.
 */
Pdomain get_tuple_current_value(Ptuple t);

/**
 * This function iterates one more step/
 * @param v The vrariable structure.
 */
void get_next_tuple(Ptuple v);

/**
 * This function returns the value of the iterator.
 * @param  t The tuple struct.
 * @return   The value of the iterator.
 */
unsigned int get_tuple_iterator(Ptuple t);

/**
 * Thi function prints the tuple struct.
 * @param v The tuple struct.
 */
void print_tuple(void *t);

/**
 * This function inserts the content of a variable and is associated domain.
 * @param  t        The tuple struct.
 * @param  content  The content name.
 * @param  d        The content domain.
 * @return          1 if success, 0 if the content already exists.
 */
int insert_tuple(Ptuple t, int* content,  Pdomain d);

/**
 * This function removes a content
 * @param  t        The variable struc.
 * @param  variable The content we want to remove.
 * @return          1 if success, 0 if the content do not exist.
 */
int remove_tuple(Ptuple t, int* content);

/**
 * This function removes a value of a content domain.
 * @param  t        The tuple struct.
 * @param  content  The content we want to remove a value from its domain.
 * @param  value    The value of the content we want to remove.
 * @return          The new domain.
 */
Pdomain remove_value_of_content_domain(Ptuple t, int* content, int value);

/**
 * This function queries the tuple struct.
 * @param  t       The tuple struct we want to query.
 * @param  content The content we are looking for in the tuple.
 * @return         Zero if the variable is not in the struct, non-zero if the
 *                 variable is in the dtruct.
 */
Pdomain query_tuple(Ptuple t, int* content);


#endif