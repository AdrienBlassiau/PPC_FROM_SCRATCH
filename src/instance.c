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
#include "queue.h"
#include "instance.h"
#include "tools.h"

Pinstance new_instance(int size){
	int i;
	Pinstance inst = (instance*)malloc(sizeof(instance));
	int** linked_list;

	linked_list = calloc(size,sizeof(int*));
	for (i = 0; i < size; i++){
		linked_list[i] = calloc(2,sizeof(int));
	}
	PQueue q = queue_new();

	inst->linked_list = linked_list;
	inst->free_list = q;
	inst->number_of_linked = 0;
	inst->size = size;

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
	queue_free_bis(inst->free_list);

	free(inst);

	return inst;
}

int** get_linked_list(Pinstance inst){
	return inst->linked_list;
}

PQueue get_free_list(Pinstance inst){
	return inst->free_list;
}

int get_number_of_linked(Pinstance inst){
	return inst->number_of_linked;
}

int get_number_of_free(Pinstance inst){
	PQueue queue = get_free_list(inst);
	QueueEntry *current_queue = queue->head;
	int number = 0;
	while (current_queue != NULL) {
		number++;
		current_queue = current_queue->next;
	}
	return number;
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
}

int add_free_variable(Pinstance inst, int* v){
	PQueue free_list = get_free_list(inst);
	if (is_linked(inst,*v)){
		return 0;
	}

	queue_push_head(free_list,v);
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

int is_free(Pinstance inst, int value){
	int** linked_list = get_linked_list(inst);
	return !linked_list[value][0];
}

int is_linked(Pinstance inst, int value){
	int** linked_list = get_linked_list(inst);
	return linked_list[value][0];
}

int* pop_free_list(Pinstance inst){
	PQueue free_list = get_free_list(inst);
	return queue_pop_head(free_list);
}
