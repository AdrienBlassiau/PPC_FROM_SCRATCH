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

#include "avl.h"
#include "domain.h"

/**
 * \struct constraints
 * \brief contraints structure
 *
 * \a A constraint structure is a map of map of set of variable
 *
 */
typedef struct constraint {
  PAVLTree constraints;
  unsigned int iterator;
  AVLTreeValue *constraints_tab;
} constraint, *Pconstraint;


/**
 * This function creates a new constraints list.
 * @return The function returns a new constraint list.
 */
Pconstraint new_constraints();

/**
 * This function free the allocated space on the heap for a constraint.
 * @param  vv A constraint struct (avl of set).
 * @return   A NULL pointer;
 */
void free_content(void *vv);

/**
 * This function free the allocated space on the heap for our constraints struc.
 * @param  c The constraints struct.
 * @return   A NULL pointer;
 */
Pconstraint free_constraints(Pconstraint c);

/**
 * This functions computes the number of constraints we have.
 * @param  c The constraints struct.
 * @return   The number of constraints.
 */
unsigned int get_constraints_number(Pconstraint c);

/**
 * This function returns the content of all constraints.
 * @param  c The constraints struct.
 * @return   THe domain of all constraints
 */
PAVLTree get_constraints(Pconstraint c);

/**
 * This function set the constraints struc iterator.
 * @param c   The constraints struct.
 * @param val The value of the iterator.
 */
void set_constraints_iterator(Pconstraint c, unsigned int val);

/**
 * This function begins the constraints list iterations.
 * @param c The constraints struct.
 */
void begin_constraints_iteration(Pconstraint c);

/**
 * This function iterates over the constraints struct until it's empty.
 * @param  c The constraints struct.
 * @return 1 if we can iterate, 0 otherwise.
 */
int constraints_can_iterate(Pconstraint c);

/**
 * This function returns the current value pointed by the iterator.
 * @param  c The constraints struct.
 * @return   The tuples of the current constraints.
 */
PAVLTree get_constraints_current_tuples(Pconstraint c);

/**
 * This function returns the value of the iterator.
 * @param  c The constraints struct.
 * @return   The value of the iterator.
 */
unsigned int get_constraints_iterator(Pconstraint c);

/**
 * This function prints the constraints struct.
 * @param c The constraints struct.
 */
void print_constraints(Pconstraint c);

/**
 * This function prints a constraint tuple.
 * @param c The constraints struct.
 */
void print_constraints_tuple(Pconstraint c, char* variable1, char* variable2);

/**
 * This function inserts a constraints.
 * @param  c         The constraints struct.
 * @param  variable1 The first variables of the constraint.
 * @param  variable2 The second variable of the constraint.
 * @return           1 if success, 0 the constraint already exists.
 */
int insert_constraints(Pconstraint c, char* variable1, char* variable2);


/**
 * This function inserts a value of variable2 associated to a value of
 * variable1 in a constraint.
 * @param  c         The constraints struct.
 * @param  variable1 The first variables of the constraint.
 * @param  variable2 The second variable of the constraint.
 * @param  content1  The value of the first variable.
 * @param  content2  The value of the seconde variable.
 * @return           1 if success, 0 if the content1 is already associated to
 *                   content2.
 */
int insert_constraints_tuple(Pconstraint c, char* variable1, char* variable2, int content1, int content2);

/**
 * This function inserts the domain associated to a value of a variable in a
 * constraint.
 * @param  c         The constraints struct.
 * @param  variable1 The first variables of the constraint.
 * @param  variable2 The second variable of the constraint.
 * @param  content   The value of the first variable.
 * @param  d         The domain of the value of the second variable associated
 *                   to the first variable.
 * @return           1 if success, 0 if the variable1 has already
 *                   assiociated domain.
 */
int insert_constraints_tuples(Pconstraint c, char* variable1, char* variable2, int content, Pdomain d);


/**
 * This function removes a constraints.
 * @param  c         The constraints struct.
 * @param  variable1 The first variables of the constraint.
 * @param  variable2 The second variable of the constraint.
 * @return           1 if success, 0 the constraint do not aready exists.
 */
int remove_constraints(Pconstraint c, char* variable1, char* variable2);


/**
 * This function removes a value of variable2 associated to a value of
 * variable1 in a constraint.
 * @param  c         The constraints struct.
 * @param  variable1 The first variables of the constraint.
 * @param  variable2 The second variable of the constraint.
 * @param  content1  The value of the first variable.
 * @param  content2  The value of the seconde variable.
 * @return           1 if success, 0 if the content1 is already associated to
 *                   content2.
 */
int remove_constraints_tuple(Pconstraint c, char* variable1, char* variable2, int content1, int content2);

/**
 * This function removes the domain associated to a value of a variable in a constraint.
 * @param  c         The constraints struct.
 * @param  variable1 The first variables of the constraint.
 * @param  variable2 The second variable of the constraint.
 * @param  content   The value of the first variable.
 * @param  d         The domain of the value of the second variable associated
 *                   to the first variable.
 * @return           1 if success, 0 if the variable1 has already
 *                   assiociated domain.
 */
int remove_constraints_tuples(Pconstraint c, char* variable1, char* variable2, int content, Pdomain d);


/**
 * This function queries the constraints struct.
 * @param  c     	 The constraints struct we want to query.
 * @param  variable1 The first variables of the constraint.
 * @param  variable2 The second variable of the constraint.
 * @return           Zero if the variable is not in the struct, non-zero if the
 *                   variable is in the struct.
 */
Pdomain query_constraints(Pconstraint c, char* variable1, char* variable2);


/**
 * This function queries the constraints struct.
 * @param  c     	 The constraints struct we want to query.
 * @param  variable1 The first variables of the constraint.
 * @param  variable2 The second variable of the constraint.
 * @param  content1  The value of the first variable.
 * @param  content2  The value of the seconde variable.
 * @return           Zero if the variable is not in the struct, non-zero if the
 *                   variable is in the struct.
 */
Pdomain query_constraints_tuple(Pconstraint c, char* variable1, char* variable2, int content1, int content2);

/**
 * This function queries the constraints struct.
 * @param  c     	 The constraints struct we want to query.
 * @param  variable1 The first variables of the constraint.
 * @param  variable2 The second variable of the constraint.
 * @param  content   The value of the first variable.
 * @return           Zero if the variable is not in the struct, non-zero if the
 *                   variable is in the struct.
 */
Pdomain query_constraints_tuples(Pconstraint c, char* variable1, char* variable2, int content);


#endif

