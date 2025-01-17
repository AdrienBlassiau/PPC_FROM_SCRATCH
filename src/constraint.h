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


/** @file constraint.h
 *
 * @brief This file manages the constraint representation.
 */

#ifndef CONSTRAINT__H
#define CONSTRAINT__H

#include "tuple.h"
#include "variable.h"
#include "domain.h"
#include "avl.h"

/**
 * \struct constraint
 * \brief contraints structure
 *
 * \a A constraint structure is a map of map of set of variable
 *
 */
typedef struct constraint {
  Ptuple** tuples_tab;
  int size;
  int number_of_constraints;
} constraint, *Pconstraint;


/**
 * This function creates a new constraint list.
 * @param  size The size of the structure.
 * @return The function returns a new constraint list.
 */
Pconstraint new_constraint(int size);

/**
 * This function frees the allocated space on the heap for our constraint
 * struct.
 * @param  c The constraint struct.
 * @return   A NULL pointer;
 */
Pconstraint free_constraint(Pconstraint c);

/**
 * This functions computes the total number of constraint we have.
 * @param  c The constraint struct.
 * @return   The number of constraint.
 */
int get_constraint_total_number(Pconstraint c);

/**
 * This function prints the constraint struct.
 * @param c The constraint struct.
 * @param v The variable struct.
 */
void print_constraint(Pconstraint c, Pvariable v);

/**
 * This function prints the constraint struct without the real name of the
 * variables.
 * @param c The constraint struct.
 */
void print_constraint_light(Pconstraint c);

/**
 * This function inserts the domain associated to a value of a variable in a
 * constraint.
 * @param  c         The constraint struct.
 * @param  variable1 The first variables of the constraint.
 * @param  variable2 The second variable of the constraint.
 * @param  content   The value of the first variable.
 * @param  size   	 The size of the domain.
 * @return           1 if success, 0 if the variable1 has already
 *                   assiociated domain.
 */
int insert_constraint_tuples(Pconstraint c, int variable1, int variable2, int content, int size);

/**
 * This function inserts a value of variable2 associated to a value of
 * variable1 in a constraint.
 * @param  c         The constraint struct.
 * @param  variable1 The first variables of the constraint.
 * @param  variable2 The second variable of the constraint.
 * @param  content1  The value of the first variable.
 * @param  content2  The value of the seconde variable.
 * @param  size   	 The size of the domain.
 * @return           1 if success, 0 if the content1 is already associated to
 *                   content2.
 */
int insert_constraint_tuple(Pconstraint c, int variable1, int variable2, int content1, int content2, int size);

/**
 * This function queries the constraint struct to find if a variable belong to
 * a constraint.
 * @param  c     	 The constraint struct we want to query.
 * @param  variable1 The first variables of the constraint.
 * @return           Zero if the variable is not in the struct, non-zero if the
 *                   variable is in the struct.
 */
Ptuple* query_all_constraint(Pconstraint c, int variable1);

/**
 * This function queries the constraint struct to find if a variable tuple
 * belong to a constraint.
 * @param  c     	 The constraint struct we want to query.
 * @param  variable1 The first variables of the constraint.
 * @param  variable2 The second variable of the constraint.
 * @return           Zero if the variable is not in the struct, non-zero if the
 *                   variable is in the struct.
 */
Ptuple query_constraint(Pconstraint c, int variable1, int variable2);


/**
 * This function queries the constraint struct to find if a variable tuple
 * associated to the value of the first variable belong to a constraint.
 * @param  c     	 The constraint struct we want to query.
 * @param  variable1 The first variables of the constraint.
 * @param  variable2 The second variable of the constraint.
 * @param  content   The value of the first variable.
 * @return           Zero if the variable is not in the struct, non-zero if the
 *                   variable is in the struct.
 */
Pdomain query_constraint_tuples(Pconstraint c, int variable1, int variable2, int content);


/**
 * This function queries the constraint struct to find if a variable tuple
 * associated to the value of the first variable and the second variable
 * belong to a constraint.
 * @param  c     	 The constraint struct we want to query.
 * @param  variable1 The first variables of the constraint.
 * @param  variable2 The second variable of the constraint.
 * @param  content1  The value of the first variable.
 * @param  content2  The value of the second variable.
 * @return           Zero if the variable is not in the struct, non-zero if the
 *                   variable is in the struct.
 */
int query_constraint_tuple(Pconstraint c, int variable1, int variable2, int content1, int content2);

/**
 * This function tests if a constraint exists.
 * @param  c         The constraint struct.
 * @param  variable1 The first variable.
 * @param  variable2 The second variable.
 * @return           1 if success, 0 otherwise.
 */
int test_contraint_exists(Pconstraint c, int variable1, int variable2);

/**
 * This function tests if a constraint with a value exists.
 * @param  c         The constraint struct.
 * @param  variable1 The first variable.
 * @param  variable2 The second variable.
 * @param  val  	 The value of the first variable.
 * @return           1 if success, 0 otherwise.
 */
int test_contraint_value_exists(Pconstraint c, int variable1, int variable2, int val);

/**
 * This function tests if a constraint with a tuple exists.
 * @param  c     	 The constraint struct we want to query.
 * @param  variable1 The first variables of the constraint.
 * @param  variable2 The second variable of the constraint.
 * @param  val1  	 The value of the first variable.
 * @param  val2      The value of the seconde variable.
 * @return           Zero if the variable is not in the struct, non-zero if the
 *                   variable is in the struct.
 */
int test_contraint_tuple_exists(Pconstraint c, int variable1, int variable2, int val1, int val2);

/**
 * This function returns the degree of a variable.
 * @param  c         The constraint struct.
 * @param  variable1 The varoable we want his degree.
 * @return           The degree of v.
 */
int get_variable_degree(Pconstraint c, int variable1);

#endif

