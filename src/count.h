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


/** @file count.h
 *
 * @brief This file manages the count structure.
 */

#ifndef COUNT__H
#define COUNT__H

#include "counter.h"
#include "variable.h"
#include "domain.h"
#include "avl.h"

/**
 * \struct count
 * \brief count structure
 *
 * \a A count structure is a matrix of avl : [var,var]->(val,count)
 *
 */
typedef struct count {
  Pcounter** counters_tab;
  int size;
  int number_of_counts;
} count, *Pcount;


/**
 * This function creates a new count list.
 * @param  size The size of the structure.
 * @return The function returns a new count list.
 */
Pcount new_count(int size);

/**
 * This function free the allocated space on the heap for our count struc.
 * @param  c The count struct.
 * @return   A NULL pointer;
 */
Pcount free_count(Pcount c);

/**
 * This functions computes the total number of count we have.
 * @param  c The count struct.
 * @return   The number of count.
 */
int get_count_total_number(Pcount c);

/**
 * This function prints the count struct.
 * @param c The count struct.
 * @param v The variable struct.
 */
void print_count(Pcount c, Pvariable v);

/**
 * This function prints the count struct.
 * @param c The count struct.
 * @param v The variable struct.
 */
void print_count_light(Pcount c);

/**
 * This function inserts a value of variable2 associated to a value of
 * variable1 in a count.
 * @param  c         The count struct.
 * @param  variable1 The first variables of the count.
 * @param  variable2 The second variable of the count.
 * @param  content1  The value of the first variable.
 * @param  content2  The value of the seconde variable.
 * @return           1 if success, 0 if the content1 is already associated to
 *                   content2.
 */
int insert_count_counter(Pcount c, int variable1, int variable2, int* content1, int* content2);

/**
 * This function queries the count struct.
 * @param  c     	 The count struct we want to query.
 * @param  variable1 The first variables of the count.
 * @return           Zero if the variable is not in the struct, non-zero if the
 *                   variable is in the struct.
 */
Pcounter* query_all_count(Pcount c, int variable1);

/**
 * This function queries the count struct.
 * @param  c     	 The count struct we want to query.
 * @param  variable1 The first variables of the count.
 * @param  variable2 The second variable of the count.
 * @return           Zero if the variable is not in the struct, non-zero if the
 *                   variable is in the struct.
 */
Pcounter query_count(Pcount c, int variable1, int variable2);


/**
 * This function queries the count struct.
 * @param  c     	 The count struct we want to query.
 * @param  variable1 The first variables of the count.
 * @param  variable2 The second variable of the count.
 * @param  content   The value of the first variable.
 * @return           Zero if the variable is not in the struct, non-zero if the
 *                   variable is in the struct.
 */
int* query_count_counter(Pcount c, int variable1, int variable2, int* content);


/**
 * This function tests if a count with a value exists.
 * @param  c         The count struct.
 * @param  variable1 The first variable.
 * @param  variable2 The second variable.
 * @param  content   The value of the first variable.
 * @param  comp   	 The comparison value.
 * @return           1 if success, 0 otherwise.
 */
int test_count_counter_is_empty(Pcount c, int variable1, int variable2, int* content, int comp);


#endif

