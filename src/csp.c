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
#include "csp.h"
#include "variable.h"
#include "instance.h"
#include "constraint.h"
#include "tools.h"

Pcsp new_csp(Pvariable v, Pconstraint cons, int* tab_int, int size){
	Pcsp c = (csp*) calloc(1,sizeof(csp));
	Pinstance instance_list = new_instance(size);

	c->variable_list = v;
	c->constraint_list = cons;
	c->tab_int = tab_int;
	c->instance_list = instance_list;
	c->size = size;

	return c;
}

Pcsp free_csp(Pcsp c){

	free_variable(c->variable_list);
	free_constraint(c->constraint_list);
	free_instance(c->instance_list);
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
	print_constraint(c->constraint_list,c->variable_list);
	print_constraint_light(c->constraint_list);
	printf("\n");
	printf("INSTANCIATION:\n");
	print_instance(c->instance_list);
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
					}
				}
			}
		}
	}

	return 1;
}

// int binary_constraint(){

// }

// int break_constraint(){

// }

int backtrack(Pcsp c){
	int size_g;
	Pinstance inst = c->instance_list;
	add_linked_variable(inst,2,3);
	add_linked_variable(inst,1,3);
	add_linked_variable(inst,0,4);
	add_linked_variable(inst,3,1);
	print_csp(c);
	int** test_tab = generate_instance_constraint(inst,&size_g);
	test_unary_constraint(c);
	free_matrix(test_tab,size_g);
	return 1;
}