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

Pcsp new_csp(Pvariable v, Pconstraint cons, int* tab_int, int size){
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
	printf("SOLUTION:\n");
	if (c->solution) printf("OUI\n");
	else printf("NON\n");

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
						printf("%d,%d with value %d doesn't exist\n",i,j,val_linked);
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
				printf("%d,%d with value %d,%d doesn't exist\n",var1,var2,val1,val2);
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

int empty_count(Pcsp csp, int x, int y, int* a){
	Pcount count = csp->count_list;
	return test_count_counter_is_empty(count,x,y,a);
}

int remove_of_domain(Pcsp csp, int x, int* a){
	Pvariable var = csp->variable_list;
	return remove_value_of_variable_domain(var,x,a);
}

void add_S(Pcsp csp, int x, int y, int a, int* b){
	PSstruct Ss = csp->Sstruct_list;
	insert_SStruct_duo(Ss,y,b,x,a);
}


void add_Q(Pcsp csp, int x, int a){
	Pduostack ds = csp->duo_list;
	Pduo duo = new_duo(x,a);
	ds = push_duostack(ds,duo);
	csp->duo_list = ds;
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

int backtrack(Pcsp csp){
	printf("ENTREE\n");
	printf("#######\n");
	print_instance(csp->instance_list);
	printf("#######\n");
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

	i = 0;
	while(domain_can_iterate(d)){
		v = get_current_value(d);
		printf("ON CHOISIT : %d DE VALEUR : %d\n",x,v);
		complete_partial_instance(csp,x,v);
		if (backtrack(csp)){
			csp->solution=1;
			return 1;
		}
		remove_from_partial_instance(csp,x);
		i++;
	}
	reverse_non_instanciated(csp,x);

	return 0;
}

int initAC4(Pcsp csp){
	int x,y,a,b,i,j,total;
	int size = get_csp_size(csp);
	Pdomain dx,dy;
	int cc=0;
	int* tab_alloc = calloc(100000000,sizeof(int));
	int copy_a;

	for (x = 0; x < size; x++){
		for (y = 0; y < size; y++){
			if(test_constraint(csp,x,y)){
				printf("###\n");
				printf("CONSTRAINT (%d,%d) EXISTS\n",x,y);

				dx = get_current_variable_domain(csp,x);

				printf("DOMAIN x:%d\n",x);
				print_domain(dx);

				begin_domain_iteration(dx);
				i = 0;
				while(domain_can_iterate(dx)){
					total = 0;

					a = get_current_value(dx);
					printf("CURRENT VALUE a:%d\n",a);

					dy = get_current_variable_domain(csp,y);

					printf("DOMAIN y:%d\n",y);
					print_domain(dy);

					begin_domain_iteration(dy);

					j = 0;
					while(domain_can_iterate(dy)){
						b = get_current_value(dy);
						printf("CURRENT VALUE b:%d\n",b);

						if(test_tuple(csp,x,y,a,b)){
							printf("%d->%d in C(%d,%d)\n",a,b,x,y);
							total++;
							tab_alloc[cc] = b;
							add_S(csp,x,y,a,&tab_alloc[cc]);
							printf("Sstruct :\n");
							print_Sstruct(csp->Sstruct_list);
							printf("--\n");
							cc++;
						}
						j++;
					}
					tab_alloc[cc] = a;
					tab_alloc[cc+1] = total;
					change_count(csp,x,y,&tab_alloc[cc],&tab_alloc[cc+1]);

					printf("Count :\n");
					print_count_light(csp->count_list);

					if (empty_count(csp,x,y,&tab_alloc[cc])){
						printf("IT'S EMPTY !\n");
						copy_a = a;
						remove_of_domain(csp,x,&tab_alloc[cc]);
						add_Q(csp,x,tab_alloc[cc]);
					}
					cc=cc+2;
					i++;
				}
			}
		}
	}
	return 1;
}

int AC4(Pcsp csp){
	initAC4(csp);
	return 1;
}