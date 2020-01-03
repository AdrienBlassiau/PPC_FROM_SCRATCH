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

Pcsp new_csp(Pvariable v, Pconstraint cons, int* tab_int, int size){
	Pcsp c = (csp*) calloc(1,sizeof(csp));
	Pinstance instance_list = new_instance(size);
	PSstruct Sstruct_list = new_Sstruct(size);

	c->variable_list = v;
	c->constraint_list = cons;
	c->tab_int = tab_int;
	c->instance_list = instance_list;
	c->size = size;
	c->solution = 0;
	c->Sstruct_list = Sstruct_list;
	c->duo_list = new_duostack();

	return c;
}

Pcsp free_csp(Pcsp c){

	free_variable(c->variable_list);
	free_constraint(c->constraint_list);
	free_instance(c->instance_list);
	free_Sstruct(c->Sstruct_list);
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
	int size = csp->size;
	Pconstraint cons = csp->constraint_list;
	PSstruct Sstruct = csp->Sstruct_list;
	Pdomain dx,dy;
	int a,b;

	for (x = 0; x < size; x++){
		for (y = 0; y < size; y++){
			if(test_contraint_exists(cons,i,j)){
				dx = get_current_variable_domain(csp,x);

				begin_domain_iteration(dx);
				i = 0;
				while(domain_can_iterate(dx)){
					a = get_current_value(dx);
					total = 0;

					dy = get_current_variable_domain(csp,y);

					begin_domain_iteration(dy);
					j = 0;
					while(domain_can_iterate(dy)){
						b = get_current_value(dy);
						if(test_contraint_tuple_exists(cons,x,y,a,b)){
							total++;
							insert_SStruct_duo(Sstruct,x,&y,a,b);
						}
						j++;
					}
					i++.
				}
			}
		}
	}
}

int AC4(Pcsp csp){
	initAC4(csp);
	return 1;
}