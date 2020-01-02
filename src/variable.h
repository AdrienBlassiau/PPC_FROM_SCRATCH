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
  Pdomain* variables;
  int size;
  char **variables_name;
} variable, *Pvariable;

/**
 * This function creates a new variable list.
 * @param  v 	The number of variable.
 * @param  size The size of the structure.
 * @return The function returns a new variable list.
 */
Pvariable new_variable(int size);

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
int get_variable_number(Pvariable v);

/**
 * This functions computes the name of the variable.
 * @param  v The variable struct.
 * @param  i The index of the variable.
 * @return   The name of the variable.
 */
char* get_variable_name(Pvariable v, int i);

/**
 * This function computes the index of a variable name.
 * @param  v        The variable struct.
 * @param  var_name The variable name.
 * @return          The index of the variable name.
 */
int get_variable_index(Pvariable v, char* var_name);

/**
 * This function returns the domains of all variable.
 * @param  v The variable struct.
 * @return   THe domain of all variable
 */
Pdomain* get_variables(Pvariable v);


/**
 * Thi function prints the variable struct.
 * @param v The variable struct.
 */
void print_variable(Pvariable v);

/**
 * This function inserts a variable and is associated domain.
 * @param  v        The variable struct.
 * @param  i        The integer associated to the variable.
 * @param  variable The variable name.
 * @param  d        The variable domain.
 * @return          1 if success, 0 if the variable already exists.
 */
int insert_variable(Pvariable v, int i, char* name, Pdomain d);


/**
 * This function removes a value of a variable domain.
 * @param  v        The variable struct.
 * @param  i 		The variable we want to remove a value from its domain.
 * @param  value    The value of the variable we want to remove.
 * @return          The new domain.
 */
int remove_value_of_variable_domain(Pvariable v, int i, int* value);

/**
 * This function queries a value of a variable domain.
 * @param  v        The variable struct.
 * @param  i 		The variable we want to remove a value from its domain.
 * @param  value    The value of the variable we want to remove.
 * @return          The new domain.
 */
int query_value_of_variable_domain(Pvariable v, int i, int* value);

/**
 * This function return the domain of a variable.
 * @param  v        The variable struct.
 * @param  i 		The variable we want to get its domain.
 * @return          The domain.
 */
Pdomain get_variable_domain(Pvariable v, int i);


#endif