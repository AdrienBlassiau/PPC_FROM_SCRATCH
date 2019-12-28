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

/** @file domain.h
 *
 * @brief This file manages a domain of values.
 */

#ifndef DOMAIN__H
#define DOMAIN__H

#include "set.h"

/**
 * \struct domain
 * \brief domain structure
 *
 * \a A domain is a set of values associated to a variable or an other
 * variable.
 */
typedef struct domain {
  PSet values;
  SetIterator iterator;
} domain, *Pdomain;



/**
 * This function create a new domain d.
 * @return A new domain.
 */
Pdomain new_domain();


/**
 * This functions frees the space allocated in the heap for a domain d.
 * @param d The domain d we want to free.
 * @return A NULL pointer.
 */
Pdomain free_domain(Pdomain d);

/**
 * This functions frees the space allocated in the heap for a domain d.
 * @param d The domain d we want to free.
 */
void free_domain_bis(void *d);

/**
 * This function computes the size of the domain.
 * @param d      The domain d.
 * @param return The size of the domain.
 */
unsigned int get_domain_size(Pdomain d);

/**
 * This function returns the set of value of the domain.
 * @param d 	 The domain d.
 * @param return The set of values of the domain.
 */
PSet get_domain_values(Pdomain d);

/**
 * This function begins the set of values iteration.
 * @param d The domain d.
 */
void begin_domain_iteration(Pdomain d);

/**
 * This function iterates over the domain while it is possible.
 * @param d The domain d.
 * @return  The next value from the set, or @ref SET_NULL if no
 *          more values are available.
 */
int domain_can_iterate(Pdomain d);

/**
 * This function iterates and get the current value of the iteration.
 * @param d The domain d.
 */
int get_current_value(Pdomain d);

/**
 * This function returns the iterator of the set of values.
 * @param d 	 The domain d.
 * @param return The iterator.
 */
SetIterator get_dom_iterator(Pdomain d);


/**
 * This function prints the domain d.
 * @param vd The domain d.
 */
void print_domain(void *vd);

/**
 * This function inserts in the domain d a value.
 * @param d     The domain d.
 * @param value The value we want to insert in the domain.
 * @return      Non-zero (true) if the value was added to the set,
 *              zero (false) if it already exists in the set, or
 *              if it was not possible to allocate memory for the
 *              new entry.
 */
int insert_in_domain(Pdomain d, int* value);

/**
 * This function removes a value in the domain d.
 * @param d     The domain d.
 * @param value The value we want to remove.
 * @return      Non-zero (true) if the value was found and removed
 *              from the set, zero (false) if the value was not
 *              found in the set.
 */
int remove_from_domain(Pdomain d, int* value);

/**
 * This function queries the domain
 * @param  d     The domain we want to query.
 * @param  value The value we are looking for in the domain.
 * @return       Zero if the value is not in the set, non-zero if the
 *               value is in the set.
 */
int query_domain(Pdomain d, int* value);

#endif