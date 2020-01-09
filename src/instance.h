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


/** @file instance.h
 *
 * @brief This file manages the instance representation.
 */

#ifndef INSTANCE__H
#define INSTANCE__H

#include "stack.h"

/**
 * \struct instance
 * \brief instance structure
 *
 * \a An instance structure is a
 *
 */
typedef struct instance {
  int** var_list;
  int number_of_linked;
  int size;
  int var_heuri;
  int val_heuri;
} instance, *Pinstance;

/**
 * This function creates an instance of a given size.
 * @param  size The size of the instance.
 * @return      A new instance.
 */
Pinstance new_instance(int size);

/**
 * This function frees the allocated space in the heap for an instance struct.
 * @param  inst The instance struct.
 * @return      A NULL pointer.
 */
Pinstance free_instance(Pinstance inst);

/**
 * This function returns the list of all linked variables (=instanciated).
 * @param  inst The instance struct.
 * @return      The list of all linked variables.
 */
int** get_var_list(Pinstance inst);

/**
 * This function returns the number of linked variables.
 * @param  inst The instance struct.
 * @return      The number of linked variables.
 */
int get_number_of_linked(Pinstance inst);

/**
 * This function returns the number of free variables.
 * @param  inst The instance struct.
 * @return      The number of free variables.
 */
int get_number_of_free(Pinstance inst);

/**
 * This function prints an instance.
 * @param vd The instance we want to print.
 */
void print_instance(void *vd);

/**
 * This function generates all the tuple we have to verify if we want the
 * instance to be viable.
 * @param inst The instance struct.
 * @param size The size of the generated tab.
 * @return     The generated tab.
 */
int** generate_instance_constraint(Pinstance inst, int* size_g);

/**
 * This function adds a free variable.
 * @param  inst The instance struct.
 * @param  v    The variable we want to make free.
 * @return      1 if success, 0 otherwise.
 */
int add_free_variable(Pinstance inst, int v);

/**
 * This function removes a linked variable.
 * @param  inst The instance struct.
 * @param  v    The variable we want to remove.
 * @return      1 if success, 0 otherwise.
 */
int remove_linked_variable(Pinstance inst, int v);

/**
 * This function adds a linked variable.
 * @param  inst The instance struct.
 * @param  v    The variable we want to make linked.
 * @return      1 if success, 0 otherwise.
 */
int add_linked_variable(Pinstance inst, int v, int val);

/**
 * This function tests if a variable is free or not.
 * @param  inst  The instance struct.
 * @param  var   The variable we want to test.
 * @return       1 if success, 0 otherwise.
 */
int is_free(Pinstance inst, int var);

/**
 * This function tests if a variable is linked or not.
 * @param  inst  The instance struct.
 * @param  var   The variable we want to test.
 * @return       1 if success, 0 otherwise.
 */
int is_linked(Pinstance inst, int var);

/**
 * This function returns the var of the var.
 * @param  inst  The instance struct.
 * @param  var 	 The variable we want the value.
 * @return       The value of the variable.
 */
int get_linked_val(Pinstance inst, int var);

/**
 * This function returns the first free variable.
 * @param  inst The instance struct.
 * @return      The free variable.
 */
int pop_var_list(Pinstance inst);

#endif

