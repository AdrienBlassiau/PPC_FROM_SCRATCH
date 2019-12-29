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
  PAVLTree constraints;
  unsigned int iterator1;
  unsigned int iterator2;
  AVLTreeValue *constraint_tab1;
  AVLTreeValue *constraint_tab2;
  AVLTreeValue *constraint_key1;
  AVLTreeValue *constraint_key2;
} constraint, *Pconstraint;


/**
 * This function creates a new constraint list.
 * @return The function returns a new constraint list.
 */
Pconstraint new_constraint();

/**
 * This function free the allocated space on the heap for a constraint.
 * @param  vv A constraint struct (avl of set).
 * @return   A NULL pointer;
 */
void free_content(void *vv);

/**
 * This function free the allocated space on the heap for our constraint struc.
 * @param  c The constraint struct.
 * @return   A NULL pointer;
 */
Pconstraint free_constraint(Pconstraint c);

/**
 * This functions computes the total number of constraint we have.
 * @param  c The constraint struct.
 * @return   The number of constraint.
 */
unsigned int get_constraint_total_number(Pconstraint c);

/**
 * This functions computes the number of constraint we have (partially).
 * @param  c The constraint struct.
 * @return   The number of constraint.
 */
unsigned int get_constraint_number1(Pconstraint c);

/**
 * This functions computes the number of sub_constraint we have.
 * @param  c         The constraint struct.
 * @param  variable1 The first variables of the constraint.
 * @return           The number of constraint.
 */
unsigned int get_constraint_number2(Pconstraint c, char* variable1);

/**
 * This function returns the content of all constraint.
 * @param  c The constraint struct.
 * @return   THe domain of all constraint
 */
PAVLTree get_constraint(Pconstraint c);

/**
 * This function returns the value of the iterator.
 * @param  c The constraint struct.
 * @return   The value of the iterator.
 */
unsigned int get_constraint_iterator1(Pconstraint c);

/**
 * This function returns the value of the iterator.
 * @param  c The constraint struct.
 * @return   The value of the iterator.
 */
unsigned int get_constraint_iterator2(Pconstraint c);

/**
 * This function set the constraint struc iterator.
 * @param c   The constraint struct.
 * @param val The value of the iterator.
 */
void set_constraint_iterator1(Pconstraint c, unsigned int val);

/**
 * This function set the constraint struc iterator.
 * @param c   The constraint struct.
 * @param val The value of the iterator.
 */
void set_constraint_iterator2(Pconstraint c, unsigned int val);

/**
 * This function begins the constraint list iterations.
 * @param c The constraint struct.
 */
void begin_constraint_iteration1(Pconstraint c);

/**
 * This function begins the constraint list iterations.
 * @param c The constraint struct.
 */
void begin_constraint_iteration2(Pconstraint c);

/**
 * This function iterates over the constraint struct until it's empty.
 * @param  c The constraint struct.
 * @return 1 if we can iterate, 0 otherwise.
 */
int constraint_can_iterate1(Pconstraint c);

/**
 * This function iterates over the constraint struct until it's empty.
 * @param  c The constraint struct.
 * @return 1 if we can iterate, 0 otherwise.
 */
int constraint_can_iterate2(Pconstraint c);

/**
 * This function returns the current value pointed by the iterator.
 * @param  c The constraint struct.
 * @return   The tuples of the current constraint.
 */
char* get_constraint_current_key1(Pconstraint c);

/**
 * This function returns the current value pointed by the iterator.
 * @param  c The constraint struct.
 * @return   The tuples of the current constraint.
 */
char* get_constraint_current_key2(Pconstraint c);

/**
 * This function returns the current value pointed by the iterator.
 * @param  c The constraint struct.
 * @return   The tuples of the current constraint.
 */
PAVLTree get_constraint_current_value1(Pconstraint c);

/**
 * This function returns the current value pointed by the iterator.
 * @param  c The constraint struct.
 * @return   The tuples of the current constraint.
 */
Ptuple get_constraint_current_value2(Pconstraint c);

/**
 * This function iterates one more step.
 * @param c The constraint structure.
 */
void get_next_constraint1(Pconstraint c);

/**
 * This function iterates one more step.
 * @param c The constraint structure.
 */
void get_next_constraint2(Pconstraint c);

/**
 * This function prints the constraint struct.
 * @param c The constraint struct.
 */
void print_constraint(Pconstraint c);

/**
 * This function prints a constraint tuple.
 * @param vt The constraint struct.
 */
void print_constraint_tuple(void *vt);

/**
 * This function inserts a constraint.
 * @param  c         The constraint struct.
 * @param  variable1 The first variables of the constraint.
 * @return           1 if success, 0 the constraint already exists.
 */
int insert_all_constraint(Pconstraint c, char* variable1);

/**
 * This function inserts a constraint.
 * @param  c         The constraint struct.
 * @param  variable1 The first variables of the constraint.
 * @param  variable2 The second variable of the constraint.
 * @return           1 if success, 0 the constraint already exists.
 */
int insert_constraint(Pconstraint c, char* variable1, char* variable2);

/**
 * This function inserts the domain associated to a value of a variable in a
 * constraint.
 * @param  c         The constraint struct.
 * @param  variable1 The first variables of the constraint.
 * @param  variable2 The second variable of the constraint.
 * @param  content   The value of the first variable.
 * @return           1 if success, 0 if the variable1 has already
 *                   assiociated domain.
 */
int insert_constraint_tuples(Pconstraint c, char* variable1, char* variable2, int* content);

/**
 * This function inserts a value of variable2 associated to a value of
 * variable1 in a constraint.
 * @param  c         The constraint struct.
 * @param  variable1 The first variables of the constraint.
 * @param  variable2 The second variable of the constraint.
 * @param  content1  The value of the first variable.
 * @param  content2  The value of the seconde variable.
 * @return           1 if success, 0 if the content1 is already associated to
 *                   content2.
 */
int insert_constraint_tuple(Pconstraint c, char* variable1, char* variable2, int* content1, int* content2);

/**
 * This function removes all constraint assiociated to a variable.
 * @param  c         The constraint struct.
 * @param  variable1 The first variables of the constraint.
 * @return           1 if success, 0 the constraint do not aready exists.
 */
int remove_all_constraint(Pconstraint c, char* variable1);

/**
 * This function removes a constraint associated to a variable .
 * @param  c         The constraint struct.
 * @param  variable1 The first variables of the constraint.
 * @param  variable2 The second variable of the constraint.
 * @return           1 if success, 0 the constraint do not aready exists.
 */
int remove_constraint(Pconstraint c, char* variable1, char* variable2);


/**
 * This function removes a value of variable2 associated to a value of
 * variable1 in a constraint.
 * @param  c         The constraint struct.
 * @param  variable1 The first variables of the constraint.
 * @param  variable2 The second variable of the constraint.
 * @param  content1  The value of the first variable.
 * @param  content2  The value of the seconde variable.
 * @return           1 if success, 0 if the content1 is already associated to
 *                   content2.
 */
int remove_constraint_tuple(Pconstraint c, char* variable1, char* variable2, int* content1, int* content2);

/**
 * This function removes the domain associated to a value of a variable in a constraint.
 * @param  c         The constraint struct.
 * @param  variable1 The first variables of the constraint.
 * @param  variable2 The second variable of the constraint.
 * @param  content   The value of the first variable.
 * @return           1 if success, 0 if the variable1 has already
 *                   assiociated domain.
 */
int remove_constraint_tuples(Pconstraint c, char* variable1, char* variable2, int* content);

/**
 * This function queries the constraint struct.
 * @param  c     	 The constraint struct we want to query.
 * @param  variable1 The first variables of the constraint.
 * @return           Zero if the variable is not in the struct, non-zero if the
 *                   variable is in the struct.
 */
PAVLTree query_all_constraint(Pconstraint c, char* variable1);

/**
 * This function queries the constraint struct.
 * @param  c     	 The constraint struct we want to query.
 * @param  variable1 The first variables of the constraint.
 * @param  variable2 The second variable of the constraint.
 * @return           Zero if the variable is not in the struct, non-zero if the
 *                   variable is in the struct.
 */
Ptuple query_constraint(Pconstraint c, char* variable1, char* variable2);


/**
 * This function queries the constraint struct.
 * @param  c     	 The constraint struct we want to query.
 * @param  variable1 The first variables of the constraint.
 * @param  variable2 The second variable of the constraint.
 * @param  content   The value of the first variable.
 * @return           Zero if the variable is not in the struct, non-zero if the
 *                   variable is in the struct.
 */
Pdomain query_constraint_tuples(Pconstraint c, char* variable1, char* variable2, int* content);


/**
 * This function queries the constraint struct.
 * @param  c     	 The constraint struct we want to query.
 * @param  variable1 The first variables of the constraint.
 * @param  variable2 The second variable of the constraint.
 * @param  content1  The value of the first variable.
 * @param  content2  The value of the seconde variable.
 * @return           Zero if the variable is not in the struct, non-zero if the
 *                   variable is in the struct.
 */
int query_constraint_tuple(Pconstraint c, char* variable1, char* variable2, int* content1, int* content2);



#endif

