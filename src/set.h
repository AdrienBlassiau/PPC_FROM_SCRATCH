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

/** @file set.h
 *
 * @brief This file manages a set of value.
 */

#ifndef SET_H
#define SET_H

/**
 * \struct set
 * \brief set structure
 *
 * \a A set is a set of int.
 */
typedef struct set {
  int** values;
  int total_size;
  int current_size;
  int iterator;
} set, *Pset;

/**
 * This function creates a new set.
 * @param  size The size of the set.
 * @return      A new set.
 */
Pset new_set(int size);

/**
 * This function frees the allocated space on the heap for a set.
 * @param  vet The set we want to free.
 */
void free_set(void *vset);

/**
 * This function returns the occupied space of the set.
 * @param  set The set.
 * @return     The size.
 */
int get_current_size(Pset set);

/**
 * This function returns the total space of the set.
 * @param  set The set.
 * @return     The size.
 */
int get_total_size(Pset set);

/**
 * This function sets the iteration.
 * @param set      The set.
 * @param iterator A pointer to get the set iterator.
 */
void set_iterate(Pset set);

/**
 * This function returns the state of the set iteration.
 * @param  set      The set.
 * @param  iterator A pointer to get the set iterator.
 * @return          1 if we can iterate, 0 otherwise.
 */
int set_iter_has_more(Pset set);

/**
 * This function returns the current value of the set.
 * @param  set      The set.
 * @return          The current value of the set.
 */
int get_set_value(Pset set);

/**
 * This function inserts a val in a sert.
 * @param  set The set.
 * @param  val The value we want to insert.
 * @return     1 if success, 0 otherwise.
 */
int set_insert(Pset set, int val);

/**
 * This function removes a val in a sert.
 * @param  set The set.
 * @param  val The value we want to remove.
 * @return     1 if success, 0 otherwise.
 */
int set_remove(Pset set, int val);

/**
 * This function queries a val in a sert.
 * @param  set The set.
 * @param  val The value we want to query.
 * @return     1 if success, 0 otherwise.
 */
int set_query(Pset set, int val);

#endif

