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
 * \struct variable
 * \brief variable structure
 *
 * \a A variable structure is a set of variable associated to a domain
 *
 */
typedef struct variable {
  PAVLTree variables;
  unsigned int iterator;
  AVLTreeValue *variables_tab;
  AVLTreeValue *variables_key;
} variable, *Pvariable;

/**
 * This function creates a new variable list.
 * @return The function returns a new variable list.
 */
Pvariable new_variable();

/**
 * This function free the allocated space on the heap for our variable struc.
 * @param  v The variable struct.
 * @return   A NULL pointer;
 */
Pvariable free_variable(Pvariable v);

/**
 * This function free the allocated space on the heap for our variable struc.
 * @param  v The variable struct.
 * @return   A NULL pointer;
 */
void free_variable_bis(void *v);

/**
 * This functions computes the number of variable we have.
 * @param  v The variable struct.
 * @return   The number of variable.
 */
unsigned int get_variable_number(Pvariable v);

/**
 * This function returns the domains of all variable.
 * @param  v The variable struct.
 * @return   THe domain of all variable
 */
PAVLTree get_variables(Pvariable v);

/**
 * This function returns the value of the iterator.
 * @param  v The variable struct.
 * @return   The value of the iterator.
 */
unsigned int get_var_iterator(Pvariable v);

/**
 * This function set the variable struc iterator.
 * @param v   The variable struct.
 * @param val The value of the iterator.
 */
void set_var_iterator(Pvariable v, unsigned int val);

/**
 * This function begins the variable list iterations.
 * @param v The variable struct.
 */
void begin_variable_iteration(Pvariable v);

/**
 * This function iterates over the variable struct until it's empty.
 * @param  v The variable struct.
 * @return 1 if we can iterate, 0 otherwise.
 */
int variable_can_iterate(Pvariable v);

/**
 * This function returns the current value pointed by the iterator.
 * @param  v The variable struct.
 * @return   The name of the current variable.
 */
char* get_var_current_key(Pvariable v);

/**
 * This function returns the current value pointed by the iterator.
 * @param  v The variable struct.
 * @return   The domain of the current variable.
 */
Pdomain get_var_current_value(Pvariable v);

/**
 * This function iterates one more step/
 * @param v The vrariable structure.
 */
void get_next_var(Pvariable v);

/**
 * Thi function prints the variable struct.
 * @param v The variable struct.
 */
void print_variable(Pvariable v);

/**
 * This function inserts a variable and is associated domain.
 * @param  v        The variable struct.
 * @param  variable The variable name.
 * @param  d        The variable domain.
 * @return          1 if success, 0 if the variable already exists.
 */
int insert_variable(Pvariable v, char* variable, Pdomain d);

/**
 * This function removes a variable
 * @param  v        The variable struc.
 * @param  variable The variable we want to remove.
 * @return          1 if success, 0 if the variable do not exist.
 */
int remove_variable(Pvariable v, char* variable);

/**
 * This function removes a value of a variable domain.
 * @param  v        The variable struct.
 * @param  variable The variable we want to remove a value from its domain.
 * @param  value    The value of the variable we want to remove.
 * @return          The new domain.
 */
Pdomain remove_value_of_variable_domain(Pvariable v, char* variable, int* value);

/**
 * This function queries the variable struct.
 * @param  v     The variable struct we want to query.
 * @param  value The variable we are looking for in the variable.
 * @return       Zero if the variable is not in the struct, non-zero if the
 *               variable is in the dtruct.
 */
Pdomain query_variable(Pvariable v, char* variable);


#endif