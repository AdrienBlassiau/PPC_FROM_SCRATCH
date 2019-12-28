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
 * \struct tuples
 * \brief tuples structure
 *
 * \a A tuples structure is a set of tuples associated to a domain
 *
 */
typedef struct tuples {
  PAVLTree tup_dom;
  unsigned int iterator;
  AVLTreeValue *tup_dom_tab;
} tuples, *Ptuples;

/**
 * This function creates a new tuples list.
 * @return The function returns a new variable list.
 */
Ptuples new_tuples();

/**
 * This function free the allocated space on the heap for our tuples struc.
 * @param  t The tuples struct.
 * @return   A NULL pointer;
 */
Ptuples free_tuples(Ptuples t);

/**
 * This function free the allocated space on the heap for our tuples struc.
 * @param  t The tuples struct.
 * @return   A NULL pointer;
 */
void free_tuples_bis(void *vt);

/**
 * This functions computes the number of tuples we have.
 * @param  t The tuples struct.
 * @return   The number of tuples.
 */
unsigned int get_tuples_number(Ptuples t);

/**
 * This function returns the domains of all tuples.
 * @param  t The tuples struct.
 * @return   The domain of all tuples
 */
PAVLTree get_tup_dom(Ptuples t);

/**
 * This function set the tuples struc iterator.
 * @param v   The tuples struct.
 * @param val The value of the iterator.
 */
void set_tuple_iterator(Ptuples t, unsigned int val);

/**
 * This function begins the tuples list iterations.
 * @param v The tuples struct.
 */
void begin_tuples_iteration(Ptuples t);

/**
 * This function iterates over the tuples struct until it's empty.
 * @param  t The tuples struct.
 * @return 1 if we can iterate, 0 otherwise.
 */
int tuples_can_iterate(Ptuples t);

/**
 * This function returns the current value pointed by the iterator.
 * @param  t The tuples struct.
 * @return   The domain of the current variable.
 */
Pdomain get_tuple_current_value(Ptuples t);

/**
 * This function returns the value of the iterator.
 * @param  t The tuples struct.
 * @return   The value of the iterator.
 */
unsigned int get_tuple_iterator(Ptuples t);

/**
 * Thi function prints the tuples struct.
 * @param v The tuples struct.
 */
void print_tuples(void *t);

/**
 * This function inserts the content of a variable and is associated domain.
 * @param  t        The tuples struct.
 * @param  content  The content name.
 * @param  d        The content domain.
 * @return          1 if success, 0 if the content already exists.
 */
int insert_tuples(Ptuples t, int* content,  Pdomain d);

/**
 * This function removes a content
 * @param  t        The variable struc.
 * @param  variable The content we want to remove.
 * @return          1 if success, 0 if the content do not exist.
 */
int remove_tuples(Ptuples t, int* content);

/**
 * This function removes a value of a content domain.
 * @param  t        The tuples struct.
 * @param  content  The content we want to remove a value from its domain.
 * @param  value    The value of the content we want to remove.
 * @return          The new domain.
 */
Pdomain remove_value_of_content_domain(Ptuples t, int* content, int* value);

/**
 * This function queries the tuples struct.
 * @param  t       The tuples struct we want to query.
 * @param  content The content we are looking for in the tuples.
 * @return         Zero if the variable is not in the struct, non-zero if the
 *                 variable is in the dtruct.
 */
Pdomain query_tuples(Ptuples t, int* content);


#endif