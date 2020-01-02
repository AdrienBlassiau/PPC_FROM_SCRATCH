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
#include "stack.h"
#include "instance.h"
#include "tools.h"

Pinstance new_instance(int size){
	int i;
	Pinstance inst = (instance*)malloc(sizeof(instance));
	int** linked_list;

	Pstack stack = new_stack();

	linked_list = calloc(size,sizeof(int*));

	for (i = 0; i < size; i++){
		linked_list[i] = calloc(2,sizeof(int));
	}


	inst->linked_list = linked_list;
	inst->free_list = stack;
	inst->number_of_linked = 0;
	inst->size = size;

	for (i = 0; i < size; i++){
		add_free_variable(inst,i);
	}

	return inst;
}

Pinstance free_instance(Pinstance inst){
	int i;
	int size = inst->size;

	int** linked_list = get_linked_list(inst);

	for (i = 0; i < size; i++){
		free(linked_list[i]);
	}
	free(inst->linked_list);
	free_stack(inst->free_list);

	free(inst);

	return inst;
}

int** get_linked_list(Pinstance inst){
	return inst->linked_list;
}

Pstack get_free_list(Pinstance inst){
	return inst->free_list;
}

int get_number_of_linked(Pinstance inst){
	return inst->number_of_linked;
}

int get_number_of_free(Pinstance inst){
	Pstack stack = get_free_list(inst);

	return stack_length(stack);
}

void print_instance(void *vinst){
	Pinstance inst = (Pinstance) vinst;
	int i;
	int size = inst->size;
	int** linked_list = get_linked_list(inst);
	char free_variable[10] = "free";
	char linked_variable[10] = "linked";

	for (i = 0; i < size; i++){
		printf("%d(%s): ",i,linked_list[i][0]?linked_variable:free_variable);
		if (linked_list[i][0]){
			printf("%d\n",linked_list[i][1]);
		}
		else{
			printf("-\n");
		}
	}
	print_stack(inst->free_list);
}

int** generate_instance_constraint(Pinstance inst, int* size_g){
	int i,j,k,first_element,second_element;
	int size = inst->size;

	int number_of_linked = get_number_of_linked(inst);
	int number_of_tuples = (number_of_linked*(number_of_linked-1))/2;

	int reduce_linked_list[number_of_linked];

	int** generated_list = calloc(number_of_tuples,sizeof(int*));
	for (i = 0; i < number_of_tuples; i++){
		generated_list[i] = calloc(2,sizeof(int));
	}

	k = 0;
	for (i = 0; i < size; i++){
		if (is_linked(inst,i)){
			reduce_linked_list[k] = i;
			k++;
		}
	}

	k=0;
	for (i = 0; i < number_of_linked; i++){
		first_element = reduce_linked_list[i];
		for (j = first_element; j < number_of_linked; j++){
			second_element = reduce_linked_list[j];
			if (first_element!=second_element){
				generated_list[k][0] = first_element;
				generated_list[k][1] = second_element;
				k++;
			}
		}
	}

	*size_g = number_of_tuples;
	return generated_list;
}

int add_free_variable(Pinstance inst, int v){
	Pstack free_list = get_free_list(inst);
	if (is_linked(inst,v)){
		return 0;
	}

	Pstack stack = push_stack(free_list,v);
	inst->free_list = stack;
	return 1;
}

int remove_linked_variable(Pinstance inst, int v){
	int** linked_list = get_linked_list(inst);
	if (!is_linked(inst,v)){
		return 0;
	}

	linked_list[v][0] = 0;
	inst->number_of_linked --;
	return 1;
}

int add_linked_variable(Pinstance inst, int v, int val){
	int** linked_list = get_linked_list(inst);
	if (is_linked(inst,v)){
		return 0;
	}
	linked_list[v][0] = 1;
	linked_list[v][1] = val;
	inst->number_of_linked ++;
	return 1;
}

int is_free(Pinstance inst, int var){
	int** linked_list = get_linked_list(inst);
	return !linked_list[var][0];
}

int is_linked(Pinstance inst, int var){
	int** linked_list = get_linked_list(inst);
	return linked_list[var][0];
}

int get_linked_val(Pinstance inst, int var){
	int** linked_list = get_linked_list(inst);
	return linked_list[var][1];
}

int pop_free_list(Pinstance inst){
	Pstack free_list = get_free_list(inst);

	int res = top_stack(free_list);

	Pstack stack = pop_stack(free_list);
	inst->free_list = stack;

	return res;
}
