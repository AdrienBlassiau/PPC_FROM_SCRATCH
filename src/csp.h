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
 * \a An csp structure is the reprensetation of a csp
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



Pcsp new_csp(Pvariable v, Pconstraint c, int size, int max_dom_size, int constraint_number, char* name);

Pcsp free_csp(Pcsp c);

void set_csp_hvar(Pcsp csp, int x);

void set_csp_hval(Pcsp csp, int x);

void set_csp_ac(Pcsp csp, int x);

void set_csp_fc(Pcsp csp, int x);

void set_csp_to(Pcsp csp, double x);

void set_csp_v(Pcsp csp, int x);

void shuffle_all_domain(Pcsp c);

int* set_current_domain(Pcsp c);

int* set_degree_tab(Pcsp c);

int** set_failure_tab(Pcsp c);

void stop_csp(Pcsp c);

void start_time(Pcsp c);

void stop_time(Pcsp c);

void reset_csp_count(Pcsp c);

void reset_csp_S(Pcsp c);

void reset_csp_Q(Pcsp c);

void add_failure(Pcsp csp, int i, int j);

void print_csp(void * pcsp);

int test_unary_constraint(Pcsp csp);

int test_binary_constraint(Pcsp csp);

int break_constraint(Pcsp csp);

int complete(Pcsp csp);

int choose_non_instanciated(Pcsp csp);

int reverse_non_instanciated(Pcsp csp, int var);

Pdomain get_current_variable_domain(Pcsp csp, int var);

int complete_partial_instance(Pcsp csp,  int v, int val);

int remove_from_partial_instance(Pcsp csp, int v);

int change_count(Pcsp csp, int x, int y, int a, int* value);

int decrement_count(Pcsp csp, int x, int y, int a);

int empty_count(Pcsp csp, int x, int y, int a, int comp);

int test_count(Pcsp csp, int x, int y, int a, int compare);

int remove_of_domain(Pcsp csp, int x, int a);

void add_S(Pcsp csp, int x, int y, int a, int b);

Pduostack get_S(Pcsp csp, int y, int b);

int S_is_empty(Pduostack S);

void get_S_tuple(Pduostack S, int* x, int* a);

void add_Q(Pcsp csp, int x, int a);

int Q_is_empty(Pcsp csp);

void remove_Q(Pcsp csp, int* y,int* b);

int test_constraint(Pcsp csp, int x, int y);

int test_tuple(Pcsp csp, int x, int y, int a, int b);

int get_csp_size(Pcsp csp);

int in_domain(Pcsp csp, int x, int a);

int get_N(Pcsp csp);

int get_instanciated_value(Pcsp csp, int var);

int is_free_variable(Pcsp csp, int var);

#endif
