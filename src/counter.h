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


/** @file counter.h
 *
 * @brief This file manages the association list of a the value and a number.
 */

#ifndef COUNTER__H
#define COUNTER__H

#include "avl.h"

/**
 * \struct counter
 * \brief counter structure
 *
 * \a A counter structure is a avl (var,count)
 *
 */
typedef struct counter {
  PAVLTree counters;
  unsigned int iterator;
  AVLTreeValue *counters_tab;
  int* counters_key;
} counter, *Pcounter;

/**
 * This function creates a new counter list.
 * @return The function returns a new variable list.
 */
Pcounter new_counter();

/**
 * This function free the allocated space on the heap for our counter struc.
 * @param  t The counter struct.
 * @return   A NULL pointer;
 */
Pcounter free_counter(Pcounter c);

/**
 * This function free the allocated space on the heap for our counter struc.
 * @param  t The counter struct.
 * @return   A NULL pointer;
 */
void free_counter_bis(void *vt);

/**
 * This functions computes the number of counter we have.
 * @param  t The counter struct.
 * @return   The number of counter.
 */
unsigned int get_counter_number(Pcounter c);

/**
 * This function returns the domains of all counter.
 * @param  t The counter struct.
 * @return   The domain of all counter
 */
PAVLTree get_counters(Pcounter c);

/**
 * This function set the counter struc iterator.
 * @param v   The counter struct.
 * @param val The value of the iterator.
 */
void set_counter_iterator(Pcounter c, unsigned int val);

/**
 * This function begins the counter list iterations.
 * @param v The counter struct.
 */
void begin_counter_iteration(Pcounter c);

/**
 * This function iterates over the counter struct until it's empty.
 * @param  t The counter struct.
 * @return 1 if we can iterate, 0 otherwise.
 */
int counter_can_iterate(Pcounter c);

/**
 * This function returns the current value pointed by the iterator.
 * @param  t The counter struct.
 * @return   The domain of the current variable.
 */
int get_counter_current_key(Pcounter c);

/**
 * This function returns the current value pointed by the iterator.
 * @param  t The counter struct.
 * @return   The domain of the current variable.
 */
int get_counter_current_value(Pcounter c);

/**
 * This function iterates one more step/
 * @param v The vrariable structure.
 */
void get_next_counter(Pcounter v);

/**
 * This function returns the value of the iterator.
 * @param  t The counter struct.
 * @return   The value of the iterator.
 */
unsigned int get_counter_iterator(Pcounter c);

/**
 * Thi function prints the counter struct.
 * @param v The counter struct.
 */
void print_counter(void *t);

/**
 * This function inserts the content of a variable and is associated count.
 * @param  t        The counter struct.
 * @param  content  The content name.
 * @param  count    The count.
 * @return          1 if success, 0 if the content already exists.
 */
int insert_counter(Pcounter c, int content,  int* count);

/**
 * This function removes a content
 * @param  t        The variable struc.
 * @param  variable The content we want to remove.
 * @return          1 if success, 0 if the content do not exist.
 */
int remove_counter(Pcounter c, int content);

/**
 * This function removes a value of a content domain.
 * @param  t        The counter struct.
 * @param  content  The content we want to remove a value from its domain.
 * @param  value    The value of the content we want to remove.
 * @return          The new value.
 */
int* change_value_of_counter(Pcounter c, int content, int* value);

/**
 * This function queries the counter struct.
 * @param  t       The counter struct we want to query.
 * @param  content The content we are looking for in the counter.
 * @return         Zero if the variable is not in the struct, non-zero if the
 *                 variable is in the dtruct.
 */
int* query_counter(Pcounter c, int content);


#endif