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


/** @file variable.h
 *
 * @brief This file manages the association list of a variable with his
 * assiociated domain.
 */

#ifndef VARIABLE__H
#define VARIABLE__H

#include "avl.h"
#include "domain.h"

/**
 * \struct variables
 * \brief variables structure
 *
 * \a A variables structure is a set of variables associated to a domain
 *
 */
typedef struct variables {
  PAVLTree var_dom;
  unsigned int iterator;
  AVLTreeValue *var_dom_tab;
} variables, *Pvariables;

/**
 * This function creates a new variables list.
 * @return The function returns a new variable list.
 */
Pvariables new_variables();

/**
 * This function free the allocated space on the heap for our variables struc.
 * @param  v The variables struct.
 * @return   A NULL pointer;
 */
Pvariables free_variables(Pvariables v);

/**
 * This function free the allocated space on the heap for our variables struc.
 * @param  v The variables struct.
 * @return   A NULL pointer;
 */
void free_variables_bis(void *v);

/**
 * This functions computes the number of variables we have.
 * @param  v The variables struct.
 * @return   The number of variables.
 */
unsigned int get_variables_number(Pvariables v);

/**
 * This function returns the domains of all variables.
 * @param  v The variables struct.
 * @return   THe domain of all variables
 */
PAVLTree get_var_dom(Pvariables v);

/**
 * This function set the variables struc iterator.
 * @param v   The variables struct.
 * @param val The value of the iterator.
 */
void set_var_iterator(Pvariables v, unsigned int val);

/**
 * This function begins the variables list iterations.
 * @param v The variables struct.
 */
void begin_variables_iteration(Pvariables v);

/**
 * This function iterates over the variables struct until it's empty.
 * @param  v The variables struct.
 * @return 1 if we can iterate, 0 otherwise.
 */
int variables_can_iterate(Pvariables v);

/**
 * This function returns the current value pointed by the iterator.
 * @param  v The variables struct.
 * @return   The domain of the current variable.
 */
Pdomain get_var_current_value(Pvariables v);

/**
 * This function returns the value of the iterator.
 * @param  v The variables struct.
 * @return   The value of the iterator.
 */
unsigned int get_var_iterator(Pvariables v);

/**
 * Thi function prints the variables struct.
 * @param v The variables struct.
 */
void print_variables(Pvariables v);

/**
 * This function inserts a variable and is associated domain.
 * @param  v        The variables struct.
 * @param  variable The variables name.
 * @param  d        The variable domain.
 * @return          1 if success, 0 if the variable already exists.
 */
int insert_variables(Pvariables v, char* variable, Pdomain d);

/**
 * This function removes a variable
 * @param  v        The variable struc.
 * @param  variable The variable we want to remove.
 * @return          1 if success, 0 if the variable do not exist.
 */
int remove_variables(Pvariables v, char* variable);

/**
 * This function removes a value of a variable domain.
 * @param  v        The variables struct.
 * @param  variable The variable we want to remove a value from its domain.
 * @param  value    The value of the variable we want to remove.
 * @return          The new domain.
 */
Pdomain remove_value_of_variable_domain(Pvariables v, char* variable, int* value);

/**
 * This function queries the variables struct.
 * @param  v     The variables struct we want to query.
 * @param  value The variable we are looking for in the variables.
 * @return       Zero if the variable is not in the struct, non-zero if the
 *               variable is in the dtruct.
 */
Pdomain query_variables(Pvariables v, char* variable);


#endif