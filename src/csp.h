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

/** @file csp.h
 *
 * @brief This file manages the csp structure (high level vision).
 */


#ifndef CSV__H
#define CSV__H

#include "include.h"
#include "variable.h"
#include "instance.h"
#include "constraint.h"
#include "Sstruct.h"
#include "duo.h"
#include "count.h"

/**
 * \struct csp
 * \brief csp structure
 *
 * \a An csp structure is the representation of a csp
 *
 */
typedef struct csp {
  Pvariable variable_list;
  Pconstraint constraint_list;
  Pinstance instance_list;
  PSstruct Sstruct_list;
  Pduostack duo_list;
  Pcount count_list;
  int size;
  int cn;
  int max_dom_size;
  int* domain_size;
  int* degree_tab;
  int** failure_tab;
  int solution;
  int branch_explored;
  clock_t t1;
  clock_t t2;
  int ac;
  int fc;
  double to;
  int v;
  char* name;

} csp, *Pcsp;


/**
 * This function creates a new csp.
 * @param  v                 The variable list.
 * @param  c                 The constraint list.
 * @param  size              The size of the csp (number of variables).
 * @param  max_dom_size      The maximum size of the domain of the variable.
 * @param  constraint_number The number of the constraint.
 * @param  name              The name of the problem.
 * @return                   A new csp.
 */
Pcsp new_csp(Pvariable v, Pconstraint c, int size, int max_dom_size, int constraint_number, char* name);

/**
 * This function frees the allocated space in the heap for the csp.
 * @param  c The csp we want to free.
 * @return   A NULL pointer.
 */
Pcsp free_csp(Pcsp c);

/**
 * This function sets the hvar of the csp.
 * @param csp The csp struct.
 * @param x   The value of the hvar.
 */
void set_csp_hvar(Pcsp csp, int x);

/**
 * This function sets the hval of the csp.
 * @param csp The csp struct.
 * @param x   The value of the hval.
 */
void set_csp_hval(Pcsp csp, int x);

/**
 * This function sets the arc-consistency mode of the csp.
 * @param csp The csp struct.
 * @param x   The value of the arc-consistency mode.
 */
void set_csp_ac(Pcsp csp, int x);

/**
 * This function sets the forward-checking mode of the csp.
 * @param csp The csp struct.
 * @param x   The value of the forward-checking mode.
 */
void set_csp_fc(Pcsp csp, int x);

/**
 * This function sets the time-out option of the csp.
 * @param csp The csp struct.
 * @param x   The value of the time-out.
 */
void set_csp_to(Pcsp csp, double x);

/**
 * This function sets the verbose mode of the csp.
 * @param csp The csp struct.
 * @param x   The value of the verbose mode.
 */
void set_csp_v(Pcsp csp, int x);

/**
 * This function a
 * @param c [description]
 */
void shuffle_all_domain(Pcsp c);

/**
 * This function sets the current domain.
 * @param  c The csp struc.
 * @return  A pointer over the domain tab
 */
int* set_current_domain(Pcsp c);

/**
 * This function sets the degree tab for the heuristic degree.
 * @param  c The csp struct.
 * @return   A pointer over the degree tab
 */
int* set_degree_tab(Pcsp c);

/**
 * This function sets the failure tab for the weighted degree heuristic.
 * @param  c The csp struct.
 * @return   A pointer over the failure tab
 */
int** set_failure_tab(Pcsp c);

/**
 * This function stop.
 * @param c The csp struct.
 */
void stop_csp(Pcsp c);

/**
 * This function starts the csp timer.
 * @param c The csp struct.
 */
void start_time(Pcsp c);

/**
 * This function stops the csp timer.
 * @param c The csp struct.
 */
void stop_time(Pcsp c);

/**
 * This function reset the count struct of the csp.
 * @param c The csp struct.
 */
void reset_csp_count(Pcsp c);

/**
 * This function reset the S struct of the csp (see AC4 for more).
 * @param c The csp struct.
 */
void reset_csp_S(Pcsp c);

/**
 * This function reset the Q struct of the csp (see AC4 for more).
 * @param c The csp struct.
 */
void reset_csp_Q(Pcsp c);

/**
 * This function add a constraint to the failure tab.
 * @param csp The csp struct
 * @param i   The first variable of the constraint.
 * @param j   The second variable if the constaint.
 */
void add_failure(Pcsp csp, int i, int j);

/**
 * This function prints the csp.
 * @param pcsp A void pointer over the csp.
 */
void print_csp(void * pcsp);

/**
 * This functions tests if the current instantiation satisfies all the unary
 * constraints
 * @param  csp The csp struct
 * @return     1 if success, 0 otherwise.
 */
int test_unary_constraint(Pcsp csp);

/**
 * This functions tests if the current instantiation satisfies all the binary
 * constraints
 * @param  csp The csp struct
 * @return     1 if success, 0 otherwise.
 */
int test_binary_constraint(Pcsp csp);

/**
 * This function tests if the current instantiation satisfies all the unary
 * and binary constraint.
 * @param  csp The csp struct.
 * @return     1 if success, 0 otherwise.
 */
int break_constraint(Pcsp csp);

/**
 * This function returns if the instantiation is complete.
 * @param  csp The csp structure.
 * @return 1 if success, 0 otherwise.
 */
int complete(Pcsp csp);

/**
 * This function returns a non instantiated variable.
 * @param  csp The csp struct.
 * @return     A non instantiated value.
 */
int choose_non_instanciated(Pcsp csp);

/**
 * This function reverse an instantiation.
 * @param  csp The csp struct.
 * @param  var The variable struct.
 * @return     1 if success, 0 otherwise.
 */
int reverse_non_instanciated(Pcsp csp, int var);

/**
 * This function returns the current domain of a variable.
 * @param  csp The csp struct.
 * @param  var The variable we want the doamain.
 * @return     The domain of the variable.
 */
Pdomain get_current_variable_domain(Pcsp csp, int var);

/**
 * This function completes the partial instantiation with a new value for a
 * given variable.
 * @param  csp The csp struct
 * @param  v   The variable we want to instantiate.
 * @param  val The value of the variable we want to instantiate.
 * @return     1 if success, 0 otherwise.
 */
int complete_partial_instance(Pcsp csp,  int v, int val);


/**
 * This function removes the partial instantiation with a value for a
 * given variable.
 * @param  csp The csp struct
 * @param  v   The variable we want to remove from the instantiation.
 * @return     1 if success, 0 otherwise.
 */
int remove_from_partial_instance(Pcsp csp, int v);

/**This function change the count of c of (x,y) -> a,c in the count structure.
 * @param  csp   The csp structure.
 * @param  x     The first variable of the tuple.
 * @param  y     The second variable of the tuple.
 * @param  a     The first value associated to the tuple.
 * @param  value The second value associated to the tuple.
 * @return     1 if success, 0 otherwise.
 */
int change_count(Pcsp csp, int x, int y, int a, int* value);

/**This function decrement the count of c of (x,y) -> a,c in the count
   structure.
 * @param  csp   The csp structure.
 * @param  x     The first variable of the tuple.
 * @param  y     The second variable of the tuple.
 * @param  a     The first value associated to the tuple.
 * @return     1 if success, 0 otherwise.
 */
int decrement_count(Pcsp csp, int x, int y, int a);

/**This function tests if the count structure is empty according to a empty
  value (comp) and by considering the tuple (x,y) -> a, c
 * @param  csp   The csp structure.
 * @param  x     The first variable of the tuple.
 * @param  y     The second variable of the tuple.
 * @param  a     The first value associated to the tuple.
 * @param  comp  The empty reference.
 * @return     1 if success, 0 otherwise.
 */
int empty_count(Pcsp csp, int x, int y, int a, int comp);

/**
 * This function tests the count content.
 * @param  csp      The csp structure.
 * @param  x        The first variable of the tuple.
 * @param  y        The second variable of the tuple.
 * @param  a        The first value associated to the tuple.
 * @param  compare  The comparison value .
 * @return 1        if success, 0 otherwise.
 */
int test_count(Pcsp csp, int x, int y, int a, int compare);

/**
 * This function removes a value from the domain of a variable.
 * @param  csp The csp struct.
 * @param  x   The variable.
 * @param  a   The value.
 * @return     1 if success, 0 otherwise.
 */
int remove_of_domain(Pcsp csp, int x, int a);

/**
 * This function add a (y,b) -> (x,a) to the S struct.
 * @param csp The csp struct.
 * @param x   The first variable.
 * @param y   The second variable.
 * @param a   The first value.
 * @param b   The second value.
 */
void add_S(Pcsp csp, int x, int y, int a, int b);

/**
 * This function returns the content (x,a) of a (y,b) -> (x,a) S element.
 * @param csp The csp struct.
 * @param y   The second variable.
 * @param b   The second value.
 */
Pduostack get_S(Pcsp csp, int y, int b);

/**
 * This funcion tests if the S struct is empty.
 * @param  S The S struct.
 * @return   1 if the S struct is empty, 0 otherwise.
 */
int S_is_empty(Pduostack S);

/**
 * THi function contructs a tuple.
 * @param S The S struct.
 * @param x The first element of the tuple.
 * @param a The second element of the tuple.
 */
void get_S_tuple(Pduostack S, int* x, int* a);

/**
 * This function add an element to the Q structure.
 * @param csp The csp struct.
 * @param x   The first element of the struct.
 * @param a   The second element of the sruct.
 */
void add_Q(Pcsp csp, int x, int a);

/**
 * This function test if the Q struct is empty.
 * @param  csp The csp struct.
 * @return     1 if the Q struct is empty, 0 otherwise.
 */
int Q_is_empty(Pcsp csp);

/**
 * This function removes an (y,b) element from the Q struct.
 * @param csp The csp struct.
 * @param y   The first element.
 * @param b   The second element.
 */
void remove_Q(Pcsp csp, int* y,int* b);

/**
 * This function tests if the constraints (x,y) exists.
 * @param  csp The csp struct.
 * @param  x   The first variable of the constraint.
 * @param  y   The second element of the constraint.
 * @return     1 if the constraint exists, 0 otherwise.
 */
int test_constraint(Pcsp csp, int x, int y);

/**
 * This function tests if the constraint (x,y) with the tuple (a,b) exists.
 * @param  csp The csp struct.
 * @param  x   The first variable of the constraint.
 * @param  y   The second variable of the constraint.
 * @param  a   The first value of the constraint.
 * @param  b   The second value of the constraint.
 * @return     1 if (x,y) -> (a,b) exists, 0 otherwise.
 */
int test_tuple(Pcsp csp, int x, int y, int a, int b);

/**
 * This function returns the size of the csp.
 * @param  csp The csp struct.
 * @return     The csp size
 */
int get_csp_size(Pcsp csp);

/**
 * This function tests if a is in the domain of x.
 * @param  csp The csp struct.
 * @param  x   The variable x.
 * @param  a   The value a.
 * @return     1 if a is in dom(x), 0 otherwise.
 */
int in_domain(Pcsp csp, int x, int a);

/**
 * This function returns the variables number of the csp.
 * @param  csp The csp struct.
 * @return     The number of variables of the csp.
 */
int get_N(Pcsp csp);

/**
 * This function returns the content of an instantiated variable.
 * @param  csp The csp struct.
 * @param  var The variable.
 * @return     The value of the variable.
 */
int get_instanciated_value(Pcsp csp, int var);

/**
 * This function if a variable is instantiated.
 * @param  csp The csp struct.
 * @param  var The variable we want to test.
 * @return     1 of the variable is instantiated 0 otherwise.
 */
int is_free_variable(Pcsp csp, int var);

#endif
