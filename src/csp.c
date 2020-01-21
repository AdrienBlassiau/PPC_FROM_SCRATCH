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

#include "include.h"
#include "tools.h"
#include "csp.h"
#include "variable.h"
#include "instance.h"
#include "heuristic.h"
#include "constraint.h"
#include "Sstruct.h"
#include "duo.h"
#include "count.h"


Pcsp new_csp(Pvariable v, Pconstraint cons, int size, int max_dom_size, int constraint_number,char* name){
	Pcsp c = (csp*) calloc(1,sizeof(csp));
	Pinstance instance_list = new_instance(size);
	PSstruct Sstruct_list = new_Sstruct(size);
	Pcount count_list = new_count(size);

	c->variable_list = v;
	c->constraint_list = cons;
	c->instance_list = instance_list;
	c->size = size;
	c->cn = constraint_number;
	c->solution = 0;
	c->Sstruct_list = Sstruct_list;
	c->duo_list = new_duostack();
	c->count_list = count_list;
	c->max_dom_size = max_dom_size;
	c->domain_size = set_current_domain(c);
	c->degree_tab = set_degree_tab(c);
	c->failure_tab = set_failure_tab(c);
	c->ac = 0;
	c->fc = 0;
	c->to = 0;
	c->v = 0;
	c->name = name;

	set_var_heuristic(instance_list,2);
	set_val_heuristic(instance_list,1);

	shuffle_all_domain(c);

	return c;
}

Pcsp free_csp(Pcsp c){
	free_variable(c->variable_list);
	free_constraint(c->constraint_list);
	free_instance(c->instance_list);
	free_Sstruct(c->Sstruct_list);
	free_duostack(c->duo_list);
	free_count(c->count_list);
	free(c->domain_size);
	free(c->degree_tab);
	free_matrix(c->failure_tab,c->size);
	free(c);

	return c;
}

void set_csp_hvar(Pcsp csp, int x){
	Pinstance instance_list = csp->instance_list;
	set_var_heuristic(instance_list,x);
}

void set_csp_hval(Pcsp csp, int x){
	Pinstance instance_list = csp->instance_list;
	set_val_heuristic(instance_list,x);
}

void set_csp_ac(Pcsp csp, int x){
	csp->ac = x;
}

void set_csp_fc(Pcsp csp, int x){
	csp->fc = x;
}

void set_csp_to(Pcsp csp, double x){
	csp->to = x;
}

void set_csp_v(Pcsp csp, int x){
	csp->v = x;
}

void shuffle_all_domain(Pcsp csp){
	int i;
	int size = csp->size;
	Pinstance inst = csp->instance_list;
	Pconstraint cons = csp->constraint_list;
	Pvariable v = csp->variable_list;

	for (i = 0; i < size; ++i){
		shuffle_domain(inst,get_variable_domain(v,i),cons,i);
	}

	return;
}

int* set_current_domain(Pcsp c){
	int i;
	int size = c->size;
	int* domain_size = calloc(size,sizeof(int));
	Pvariable v = c->variable_list;

	Pdomain current_domain;

	for (i = 0; i < size; ++i){
		current_domain = get_variable_domain(v,i);
		domain_size[i] = get_domain_size(current_domain);
	}

	return domain_size;
}

int* set_degree_tab(Pcsp c){
	int i;
	int size = c->size;
	int* degree_tab = calloc(size,sizeof(int));
	Pconstraint cons = c->constraint_list;

	for (i = 0; i < size; ++i){
		degree_tab[i] = get_variable_degree(cons,i);
	}

	// for (i = 0; i < size; ++i){
	// 	printf("deg %d\n",degree_tab[i]);
	// }

	return degree_tab;
}

int** set_failure_tab(Pcsp c){
	int i;
	int size = c->size;
	int** failure_tab = calloc(size,sizeof(int*));

	for (i = 0; i < size; ++i){
		failure_tab[i] = calloc(size,sizeof(int));
	}

	return failure_tab;
}

void stop_csp(Pcsp c){
	c->solution = 1;
}

void start_time(Pcsp c){
	c->t1 = clock();
}

void stop_time(Pcsp c){
	c->t2 = clock();
}

void reset_csp_count(Pcsp c){
	int size = c->size;

	Pcount count_list;
	count_list = new_count(size);

	free_count(c->count_list);
	c->count_list = count_list;
}

void reset_csp_S(Pcsp c){
	int size = c->size;

	PSstruct Sstruct_list;
	Sstruct_list = new_Sstruct(size);

	free_Sstruct(c->Sstruct_list);

	c->Sstruct_list = Sstruct_list;
}

void reset_csp_Q(Pcsp c){
	Pduostack duo_list;
	duo_list = new_duostack();

	free_duostack(c->duo_list);
	c->duo_list = duo_list;
}

void add_failure(Pcsp csp, int i, int j){
	csp->failure_tab[i][j]+=1;
	csp->failure_tab[j][i]+=1;
}

void print_csp(void * pcsp){
	Pcsp c = (Pcsp) pcsp;

	if (c->v >= 2){
		printf("Variables + Domains:\n");
		print_variable(c->variable_list);
		printf("\n");
		printf("Constraints:\n");
		print_constraint(c->constraint_list,c->variable_list);
		printf("\n");
	}

	if (c->v >= 3){
		printf("Failure tab :\n");
		print_matrix(c->failure_tab,c->size);
		printf("\n");
	}

	if (c->v >= 1){
		printf("Instanciation:\n");
		print_instance(c->instance_list);

		printf("\nSolution		: 	%s\n",c->solution?"YES":"NO");


		printf("The problem %s has	: 	%d VARIABLES and %d CONSTRAINTS\n", c->name, c->size, c->cn);

		printf("Solving method are 	: 	");
		if (c->fc == 0) printf("BACKTRACK + ");
		else printf("FORWARD-CHEKING + ");

		if (c->ac == 1) printf("AC4 (root) \n");
		else if (c->ac == 2) printf("AC4 (MAC) \n");
		else printf("NOTHING \n");

		printf("Chosen heuristic are 	: 	%s for variables and %s for values\n",get_var_heuristic(c->instance_list),get_val_heuristic(c->instance_list));
		printf("Number of nodes visited : 	%d\n\n",c->branch_explored);
		printf("Solve time 		=	%f sec.\n",(float)(c->t2-c->t1)/CLOCKS_PER_SEC);
		if (c->to > 0.){
			printf("Time out 		=	%f sec.\n",c->to);
		}
		else{
			printf("There is no time out.\n");
		}

		printf("\nVerbose mode is		:	%s\n",c->v?(c->v==1?"ON":(c->v==2?"DEBUG":"HARD DEBUG")):"OFF");
		// printf("%s,",c->name);
		// printf("%d,",c->size);
		// printf("%f,",(float)(c->t2-c->t1)/CLOCKS_PER_SEC);
		// printf("%d,", c->branch_explored);
	}
}

int test_unary_constraint(Pcsp csp){
	int i,j;
	int size = csp->size;
	int val_linked;
	Pinstance inst = csp->instance_list;
	Pconstraint cons = csp->constraint_list;

	for (i = 0; i < size; i++){
		if (is_linked(inst,i)){
			val_linked = get_linked_val(inst,i);
			for (j = 0; j < size; j++){
				if(test_contraint_exists(cons,i,j)){
					if (!test_contraint_value_exists(cons,i,j,val_linked)){
						if (csp->v >= 3){
							printf("%d,%d with value %d doesn't exist\n",i,j,val_linked);
						}
						add_failure(csp,i,j);
						return 0;
					}
				}
			}
		}
	}

	return 1;
}

int test_binary_constraint(Pcsp csp){
	int i, var1, var2, val1, val2;
	int size_g;

	Pinstance inst = csp->instance_list;
	Pconstraint cons = csp->constraint_list;

	int** test_tab = generate_instance_constraint(inst,&size_g);

	for (i = 0; i < size_g; i++){
		var1 = test_tab[i][0];
		var2 = test_tab[i][1];
		val1 = get_linked_val(inst,var1);
		val2 = get_linked_val(inst,var2);

		if(test_contraint_exists(cons,var1,var2)){
			if (!test_contraint_tuple_exists(cons,var1,var2,val1,val2)){
				if (csp->v >= 3){
					printf("%d,%d with value %d,%d doesn't exist\n",var1,var2,val1,val2);
				}
				add_failure(csp,var1,var2);
				free_matrix(test_tab,size_g);
				return 0;
			}
		}
	}

	free_matrix(test_tab,size_g);
	return 1;
}

int break_constraint(Pcsp csp){
	return !test_unary_constraint(csp) || !test_binary_constraint(csp);
}

int complete(Pcsp csp){
	Pinstance inst = csp->instance_list;
	int size = csp->size;

	return get_number_of_linked(inst) == size;
}

int choose_non_instanciated(Pcsp csp){
	Pconstraint cons = csp->constraint_list;
	Pinstance inst = csp->instance_list;
	int** failure_tab = csp->failure_tab;
	int* dom_size = csp->domain_size;
	int* degree_tab = csp->degree_tab;
	int max_dom_size = csp->max_dom_size;
	return select_variable(inst,dom_size,max_dom_size,degree_tab,cons,failure_tab);
}

int reverse_non_instanciated(Pcsp csp, int var){
	Pinstance inst = csp->instance_list;
	return add_free_variable(inst, var);
}

Pdomain get_current_variable_domain(Pcsp csp, int var){
	Pconstraint cons = csp->constraint_list;
	Pvariable var_list = csp->variable_list;
	Pinstance inst = csp->instance_list;

	if (inst->val_heuri == DYNAMIC_SUPPPORTED){
		shuffle_domain(inst,get_variable_domain(var_list,var),cons,var);
	}

	return get_variable_domain(var_list,var);
}

int complete_partial_instance(Pcsp csp,  int v, int val){
	Pinstance inst = csp->instance_list;
	return add_linked_variable(inst,v,val);
}

int remove_from_partial_instance(Pcsp csp, int v){
	Pinstance inst = csp->instance_list;
	return remove_linked_variable(inst,v);
}

int change_count(Pcsp csp, int x, int y, int a, int* value){
	Pcount count = csp->count_list;
	return insert_count_counter(count,x,y,a,value);
}

int decrement_count(Pcsp csp, int x, int y, int a){
	Pcount count = csp->count_list;
	int* counter = query_count_counter(count,x,y,a);
	*counter=*counter-1;

	return *counter;
}

int empty_count(Pcsp csp, int x, int y, int a, int comp){
	Pcount count = csp->count_list;
	return test_count_counter_is_empty(count,x,y,a,comp);
}

int test_count(Pcsp csp, int x, int y, int a, int compare){
	Pcount count = csp->count_list;
	int* t = query_count_counter(count,x,y,a);
	if (t==NULL){
		return 0;
	}
	return *t == compare;
}

int remove_of_domain(Pcsp csp, int x, int a){
	Pvariable var = csp->variable_list;
	return remove_value_of_variable_domain(var,x,a);
}

void add_S(Pcsp csp, int x, int y, int a, int b){
	PSstruct Ss = csp->Sstruct_list;
	insert_SStruct_duo(Ss,y,b,x,a);
}

Pduostack get_S(Pcsp csp, int y, int b){
	PSstruct Ss = csp->Sstruct_list;
	Pduostack ds = query_SStruct(Ss,y,b);

	return ds;
}

int S_is_empty(Pduostack S){
	return is_empty_duostack(S);
}

void get_S_tuple(Pduostack S, int* x, int* a){
	Pduo duo = S->duo_element;
	*x = duo->var;
	*a = duo->val;
}

void add_Q(Pcsp csp, int x, int a){
	Pduostack ds = csp->duo_list;
	Pduo duo = new_duo(x,a);
	ds = push_duostack(ds,duo);
	csp->duo_list = ds;
}

int Q_is_empty(Pcsp csp){
	Pduostack ds = csp->duo_list;
	return is_empty_duostack(ds);
}

void remove_Q(Pcsp csp, int* y,int* b){
	Pduostack ds = csp->duo_list;
	Pduo duo = top_duostack(ds);
	*y = duo->var;
	*b = duo->val;
	Pduostack new_ds = pop_duostack(ds);
	csp->duo_list = new_ds;
	return;
}

int test_constraint(Pcsp csp, int x, int y){
	Pconstraint cons = csp->constraint_list;
	return test_contraint_exists(cons,x,y);
}

int test_tuple(Pcsp csp, int x, int y, int a, int b){
	Pconstraint cons = csp->constraint_list;

	return test_contraint_tuple_exists(cons,x,y,a,b);
}

int get_csp_size(Pcsp csp){
	return csp->size;
}

int in_domain(Pcsp csp, int x, int a){
	Pvariable pl =  csp->variable_list;
	return query_value_of_variable_domain(pl,x,a);
}

int get_N(Pcsp csp){
	Pvariable v =  csp->variable_list;
	return get_variable_number(v);
}

int get_instanciated_value(Pcsp csp, int var){
	Pinstance inst = csp->instance_list;
	return get_linked_val(inst,var);
}

int is_free_variable(Pcsp csp, int var){
	Pinstance inst = csp->instance_list;

	return is_free(inst,var);
}
