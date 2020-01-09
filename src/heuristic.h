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


/** @file heuristic.h
 *
 * @brief This file applies a chosen heuristic
 */

#ifndef HEURISTIC__H
#define HEURISTIC__H

#include "instance.h"
#include "domain.h"
#include "constraint.h"
#include "instance.h"

enum heuristic_var{
	LEX = 1,
	INVLEX = 2,
	RANDOM = 3,
	DOM_SIZE = 4,
	DEGREE = 5,
	DYNAMIC_DEGREE = 6,
	WHEIGHTED_DEGREE = 7,
	DOM_DEG = 8,
	DOM_DDEG = 9,
	DOM_WDEG = 10
};

enum heuristic_val{
	MIN_VAL = 1,
	MAX_VAL = 2,
	RANDOM_VAL = 3,
	SUPPORTED = 4,
	DYNAMIC_SUPPPORTED = 5
};

/**
 * This function change the current heuristic
 * @param  inst The instance struct.
 */
void set_var_heuristic(Pinstance inst, int heuri);

/**
 * This function change the current heuristic
 * @param  inst The instance struct.
 */
void set_val_heuristic(Pinstance inst, int heuri);

/**
 * This function returns a free variable.
 * @param  inst The instance struct.
 * @return      The free variable.
 */
int select_variable(Pinstance inst, int* domain_size, int max_dom_size, int* degree_tab, Pconstraint cons, int** failure_tab);

/**
 * This function returns the last free variable.
 * @param  inst The instance struct.
 * @return      The free variable.
 */
int pop_last_var(Pinstance inst);

/**
 * This function returns the first free variable.
 * @param  inst The instance struct.
 * @return      The free variable.
 */
int pop_first_var(Pinstance inst);

/**
 * This function returns a random var.
 * @param  inst The instance struct.
 * @return      The free variable.
 */
int pop_random_var(Pinstance inst);

/**
 * This function returns the var with the lowest domain size.
 * @param  inst The instance struct.
 * @return      The free variable.
 */
int pop_min_dom_var(Pinstance inst, int* domain_size, int max_dom_size);

/**
 * This function returns the var with the greates degree.
 * @param  inst The instance struct.
 * @return      The free variable.
 */
int pop_max_degree_var(Pinstance inst, int* degree_tab);

/**
 * This function returns the var with the greates degree.
 * @param  inst The instance struct.
 * @return      The free variable.
 */
int pop_max_dynamic_degree_var(Pinstance inst, Pconstraint cons);

/**
 * This function returns the var with the greates degree.
 * @param  inst The instance struct.
 * @return      The free variable.
 */
int pop_max_weighted_degree_var(Pinstance inst, Pconstraint cons, int** failure_tab);

/**
 * This function returns the var with the greates degree.
 * @param  inst The instance struct.
 * @return      The free variable.
 */
int pop_min_dom_degree_var(Pinstance inst, int* degree_tab, int* domain_size, int max_dom_size);

/**
 * This function returns the var with the greates degree.
 * @param  inst The instance struct.
 * @return      The free variable.
 */
int pop_min_dom_dynamic_degree_var(Pinstance inst, Pconstraint cons, int* domain_size, int max_dom_size);

/**
 * This function returns the var with the greates degree.
 * @param  inst The instance struct.
 * @return      The free variable.
 */
int pop_min_dom_weighted_degree_var(Pinstance inst, Pconstraint cons, int** failure_tab, int* domain_size, int max_dom_size);

/**
 * This function return the current heuristic
 * @param  inst The instance struct.
 * @return      The current heuristic described by a string.
 */
char* get_var_heuristic(Pinstance inst);


/**
 * This function shuffles a domain.
 * @param inst The instance struct.
 * @param d    The domain struct.
 * @param cons The constraints struct.
 * @param var  The variable associated to the domain.
 */
void shuffle_domain(Pinstance inst, Pdomain d, Pconstraint cons, int var);

/**
 * This function return the current heuristic
 * @param  inst The instance struct.
 * @return      The current heuristic described by a string.
 */
char* get_val_heuristic(Pinstance inst);

#endif

