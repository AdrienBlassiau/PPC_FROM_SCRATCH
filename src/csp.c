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
#include "constraint.h"
#include "Sstruct.h"
#include "duo.h"
#include "count.h"

Pcsp new_csp(Pvariable v, Pconstraint cons, int* tab_int, int size, int max_dom_size){
	Pcsp c = (csp*) calloc(1,sizeof(csp));
	Pinstance instance_list = new_instance(size);
	PSstruct Sstruct_list = new_Sstruct(size);
	Pcount count_list = new_count(size);

	c->variable_list = v;
	c->constraint_list = cons;
	c->tab_int = tab_int;
	c->instance_list = instance_list;
	c->size = size;
	c->solution = 0;
	c->Sstruct_list = Sstruct_list;
	c->duo_list = new_duostack();
	c->count_list = count_list;
	c->max_dom_size = max_dom_size;

	return c;
}

Pcsp free_csp(Pcsp c){

	free_variable(c->variable_list);
	free_constraint(c->constraint_list);
	free_instance(c->instance_list);
	free_Sstruct(c->Sstruct_list);
	free_duostack(c->duo_list);
	free_count(c->count_list);
	free(c->tab_int);
	free(c);

	return c;
}

void reset_csp_count(Pcsp c){
	int size = c->size;

	Pcount count_list;
	count_list = new_count(size);

	free_count(c->count_list);
	c->count_list = count_list;
}

void print_csp(void * pcsp){
	Pcsp c = (Pcsp) pcsp;
	printf("VARIABLES + DOMAINES:\n");
	print_variable(c->variable_list);
	printf("\n");
	printf("CONTRAINTES:\n");
	// print_constraint(c->constraint_list,c->variable_list);
	print_constraint_light(c->constraint_list);
	printf("\n");
	printf("INSTANCIATION:\n");
	print_instance(c->instance_list);
	printf("SOLUTION: ");
	if (c->solution) printf("OUI\n");
	else printf("NON\n");
	printf("SIZE:\n");
	printf("max dom : %d\n",c->max_dom_size);
	printf("var : %d\n",c->size);
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
						// printf("%d,%d with value %d doesn't exist\n",i,j,val_linked);
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

	// printf("TUPLES À tester %d: \n",size_g);
	// for (i = 0; i < size_g; i++){
	// 	printf("(%d,%d)",test_tab[i][0],test_tab[i][1]);
	// }

	for (i = 0; i < size_g; i++){
		var1 = test_tab[i][0];
		var2 = test_tab[i][1];
		val1 = get_linked_val(inst,var1);
		val2 = get_linked_val(inst,var2);

		if(test_contraint_exists(cons,var1,var2)){
			if (!test_contraint_tuple_exists(cons,var1,var2,val1,val2)){
				// printf("%d,%d with value %d,%d doesn't exist\n",var1,var2,val1,val2);
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
	Pinstance inst = csp->instance_list;
	return pop_free_list(inst);
}

int reverse_non_instanciated(Pcsp csp, int var){
	Pinstance inst = csp->instance_list;
	return add_free_variable(inst, var);
}

Pdomain get_current_variable_domain(Pcsp csp, int var){
	Pvariable var_list = csp->variable_list;
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

void change_count(Pcsp csp, int x, int y, int* a, int* value){
	Pcount count = csp->count_list;
	insert_count_counter(count,x,y,a,value);
}

int decrement_count(Pcsp csp, int x, int y, int* a){
	Pcount count = csp->count_list;
	int* counter = query_count_counter(count,x,y,a);
	*counter=*counter-1;

	return *counter;
}

int empty_count(Pcsp csp, int x, int y, int* a){
	Pcount count = csp->count_list;
	return test_count_counter_is_empty(count,x,y,a);
}

int test_count(Pcsp csp, int x, int y, int* a, int compare){
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

void add_S(Pcsp csp, int x, int y, int a, int* b){
	PSstruct Ss = csp->Sstruct_list;
	insert_SStruct_duo(Ss,y,b,x,a);
}

Pduostack get_S(Pcsp csp, int y, int* b){
	PSstruct Ss = csp->Sstruct_list;
	Pduostack ds = query_SStruct(Ss,y,b);
	// printf("STACK\n");
	// print_duostack(ds);
	// printf("STACK\n");
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
	return get_variable_number(v)-1;
}

int get_instanciated_value(Pcsp csp, int var){
	Pinstance inst = csp->instance_list;
	return get_linked_val(inst,var);
}

int is_free_variable(Pcsp csp, int var){
	Pinstance inst = csp->instance_list;

	return is_free(inst,var);
}

int backtrack(Pcsp csp){
	// printf("ENTREE\n");
	// printf("#######\n");
	// print_instance(csp->instance_list);
	// printf("#######\n");
	int x,v,i;

	if (break_constraint(csp)){
		return 0;
	}
	if (complete(csp)){
		return 1;
	}

	x = choose_non_instanciated(csp);
	Pdomain d = get_current_variable_domain(csp,x);

	begin_domain_iteration(d);

	i = get_domain_size(d);
	while(i>0){
		v = get_current_value(d);
		// printf("ON CHOISIT : %d DE VALEUR : %d\n",x,v);
		complete_partial_instance(csp,x,v);
		if (backtrack(csp)){
			csp->solution=1;
			return 1;
		}
		remove_from_partial_instance(csp,x);
		i--;
	}
	reverse_non_instanciated(csp,x);

	return 0;
}

int initAC4(Pcsp csp, int* tab_alloc){
	int x,y,a,b,i,j,total;
	int size = get_csp_size(csp);
	Pdomain dx,dy;
	int cc=0;

	for (x = 0; x < size; x++){
		for (y = 0; y < size; y++){
			if(test_constraint(csp,x,y)){
				// printf("#################### CONSTRAINT (%d,%d) EXISTS (####################\n",x,y);

				dx = get_current_variable_domain(csp,x);

				begin_domain_iteration(dx);
				i = get_domain_size(dx);
				while(i>0){
					total = 0;

					a = get_current_value(dx);
					dy = get_current_variable_domain(csp,y);

					// printf("DOMAIN x:%d\n",x);
					// print_domain(dx);

					// printf("DOMAIN y:%d\n",y);
					// print_domain(dy);

					begin_domain_iteration(dy);

					j = get_domain_size(dy);
					while(j>0){
						b = get_current_value(dy);
						// printf("===> CURRENT TUPLE (a,b):(%d,%d)\n",a,b);

						if(test_tuple(csp,x,y,a,b)){
							// printf("%d->%d in C(%d,%d)\n",a,b,x,y);
							total++;
							tab_alloc[cc] = b;
							add_S(csp,x,y,a,&tab_alloc[cc]);
							// printf("Sstruct :\n");
							// print_Sstruct(csp->Sstruct_list);
							// printf("--\n");
							cc++;
						}
						j--;
					}
					tab_alloc[cc] = a;
					tab_alloc[cc+1] = total;
					change_count(csp,x,y,&tab_alloc[cc],&tab_alloc[cc+1]);

					// printf("Count :\n");
					// print_count_light(csp->count_list);

					if (empty_count(csp,x,y,&tab_alloc[cc])){
						// printf("IT'S EMPTY !\n");
						remove_of_domain(csp,x,tab_alloc[cc]);
						add_Q(csp,x,tab_alloc[cc]);
					}
					cc=cc+2;
					i--;
				}
			}
		}
	}
	return 1;
}

int AC4(Pcsp csp){
	int x,y,a,b,count;
	Pduostack S;
	int* tab_alloc = calloc(100000000,sizeof(int));

	initAC4(csp,tab_alloc);

	while(!Q_is_empty(csp)){
		remove_Q(csp,&y,&b);

		// printf("y:%d et b:%d\n",y,b);

		S = get_S(csp,y,&b);
		while(!S_is_empty(S)){
			get_S_tuple(S,&x,&a);
			// printf("x:%d et a:%d\n",x,a);
			S = S->next;
			// printf("AVANT\n");
			// print_count_light(csp->count_list);
			count = decrement_count(csp,x,y,&a);
			// print_count_light(csp->count_list);
			// printf("APRES\n");
			if (!count && in_domain(csp,x,a)){
				remove_of_domain(csp,x,a);
				add_Q(csp,x,a);
			}

		}
	}

	reset_csp_count(csp);
	free(tab_alloc);
	return 1;
}


int check_forward(Pcsp csp, int i, int* tab_alloc, int* cc){
	int j,k,s,m;
	int N = get_N(csp);
	int dwo = 0;
	Pdomain dj;

	for (j = 0; j < N; j++){
		if(is_free_variable(csp,j)){
			dwo = 1;

			dj = get_current_variable_domain(csp,j);
			begin_domain_iteration(dj);

			k = get_domain_size(dj);
			while(k>0){
				m = get_current_value(dj);

				printf("FORWARD : ON CHOISIT : %d DE VALEUR : %d\n",j,m);

				tab_alloc[*cc] = m;
				(*cc)++;
				if (empty_count(csp,j,j,&tab_alloc[(*cc)-1])){
					s = get_instanciated_value(csp,i);

					if (test_tuple(csp,i,j,s,m) || !test_constraint(csp,i,j)){
						printf("%d->%d in C(%d,%d)\n",s,m,i,j);
						dwo = 0;
					}
					else{
						printf("%d->%d NOT in C(%d,%d)\n",s,m,i,j);
						tab_alloc[*cc] = m;
						(*cc)++;
						tab_alloc[*cc] = i;
						change_count(csp,j,j,&tab_alloc[(*cc)-1],&tab_alloc[*cc]);
						(*cc)++;
						printf("Count :\n");
						print_count_light(csp->count_list);
					}
				}
				k--;
			}
			if (dwo){
				printf("BAD\n");
				return 0;
			}

		}
	}
	printf("GOOD\n");
	return 1;
}

void restore(Pcsp csp, int i, int* tab_alloc, int* cc){
	printf("RESTORE\n");
	int j,k,m;
	int N = get_N(csp);
	Pdomain dj;

	for (j = 0; j < N; j++){
		if(is_free_variable(csp,j)){
			printf("RESTORE %d\n",j);
			dj = get_current_variable_domain(csp,j);
			begin_domain_iteration(dj);

			k = get_domain_size(dj);
			while(k>0){
				m = get_current_value(dj);

				if (test_count(csp,j,j,&m,i)){
					tab_alloc[(*cc)] = m;
					(*cc)++;
					tab_alloc[(*cc)+1] = 0;
					change_count(csp,j,j,&tab_alloc[(*cc)-1],&tab_alloc[*cc]);
					(*cc)++;
				}

				k--;
			}
		}
	}
}

int FC(Pcsp csp, int* tab_alloc, int* cc){
	printf("ENTREE \n");
	printf("#######\n");
	print_instance(csp->instance_list);
	printf("#######\n");

	int i = choose_non_instanciated(csp);
	int j,l;

	Pdomain di;

	di = get_current_variable_domain(csp,i);
	begin_domain_iteration(di);

	j = get_domain_size(di);
	while(j>0){
		l = get_current_value(di);

		print_domain(di);
		printf("ON CHOISIT : %d DE VALEUR : %d\n",i,l);

		complete_partial_instance(csp,i,l);

		printf("#######\n");
		print_instance(csp->instance_list);
		printf("#######\n");

		tab_alloc[*cc] = l;
		(*cc)++;


		if (empty_count(csp,i,i,&tab_alloc[(*cc)-1])){
			printf("%d DE VALEUR : %d VALIDE\n",i,l);

			if (complete(csp)){
				printf("FIN\n");
				csp->solution=1;
				return 1;
			}
			else{
				printf("FORWARD CHECK\n");
				if (check_forward(csp,i,tab_alloc,cc)){
					if(FC(csp,tab_alloc,cc)){
						return 1;
					}
				}
				restore(csp,i,tab_alloc,cc);
			}
		}
		printf("%d DE VALEUR : %d INVALIDE\n",i,l);
		remove_from_partial_instance(csp,i);
		j--;
	}
	reverse_non_instanciated(csp,i);
	return 0;
}



int forward_checking(Pcsp csp){
	int* tab_alloc = calloc(100000000,sizeof(int));
	int cc = 0;
	FC(csp,tab_alloc,&cc);
	reset_csp_count(csp);
	free(tab_alloc);
	return 1;
}