/*

Copyright (c) 2005-2008, Simon Howard

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
#include "set.h"

Pset new_set(int size){
	int i;
	Pset s = (Pset)malloc(sizeof(set));

	int** val = (int**)calloc(size,sizeof(int*));

	for (i = 0; i < size; i++){
		val[i] = (int*)calloc(2,sizeof(int));
	}

	s->values = val;
	s->iterator = 0;
	s->total_size = size;
	s->current_size = 0;

	return s;
}

void free_set(void *vset){
	int i;
	Pset set = (Pset) vset;
	int** values = set->values;
	int size = set->total_size;

	for (i = 0; i < size; i++){
		free(values[i]);
	}
	free(values);

	free(set);
}

int get_current_size(Pset set){
	return set->current_size;
}

int get_total_size(Pset set){
	return set->total_size;
}

void set_iterate(Pset set){
	set->iterator = 0;
}

int set_iter_has_more(Pset set){
	int iterator = set->iterator;
	int size = get_total_size(set);
	if (iterator < size){
		return 1;
	}
	return 0;
}

int get_set_value(Pset set){
	int i;
	int iterator = set->iterator;
	int** values = set->values;
	int size = get_total_size(set);
	for (i = iterator; i < size; i++){
		if (values[i][0]){
			set->iterator = i+1;
			return values[i][1];
		}
	}
	set->iterator = i+1;

	return -1;
}

int set_insert(Pset set, int val){
	int i;
	int size = set->total_size;
	int** values = set->values;

	if (set_query(set,val)){
		return 0;
	}

	for (i = 0; i < size; i++){
		if (!values[i][0]){
			set->values[i][0] = 1;
			set->values[i][1] = val;
			set->current_size = set->current_size + 1;
			return 1;
		}
	}

	return 0;
}


int set_remove(Pset set, int val){
	int i;
	int size = set->total_size;
	int** values = set->values;

	for (i = 0; i < size; i++){
		if (values[i][0] == 1 && values[i][1] == val){
			set->values[i][0] = 0;
			set->current_size = set->current_size - 1;
			return 1;
		}
	}

	return 0;
}


int set_query(Pset set, int val){
	int i;
	int size = set->total_size;
	int** values = set->values;

	for (i = 0; i < size; i++){
		if (values[i][0] == 1 && values[i][1] == val){
			return 1;
		}
	}

	return 0;
}

void print_set(Pset set){
	int i;
	int size = set->total_size;
	int** values = set->values;

	for (i = 0; i < size; i++){
		printf("[%d]: open:%d et value:%d \n",i,values[i][0],values[i][1]);
	}
}