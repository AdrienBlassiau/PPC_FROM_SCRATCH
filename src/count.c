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
#include "count.h"
#include "variable.h"
#include "counter.h"
#include "domain.h"
#include "avl.h"
#include "compare_int.h"
#include "compare_string.h"

Pcount new_count(int size){
	int i,j;
	Pcount c = (count*)malloc(sizeof(count));
	Pcounter** counters_tab;
	Pcounter t;

	counters_tab = malloc(size*sizeof(Pcounter*));
	for (i = 0; i < size; i++){
		counters_tab[i] = malloc(size*sizeof(Pcounter));
		for (j = 0; j < size; j++){
			t = new_counter();
			counters_tab[i][j] = t;
		}
	}

	c->counters_tab = counters_tab;
	c->number_of_counts = 0;
	c->size = size;

	return c;
}

Pcount free_count(Pcount c){
	int i,j;
	int size = c->size;

	Pcounter** counters_tab = c->counters_tab;

	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			free_counter(counters_tab[i][j]);
		}
		free(counters_tab[i]);
	}
	free(c->counters_tab);
	free(c);

	return c;
}

Pcounter** get_count(Pcount c){
	return c->counters_tab;
}

int get_count_total_number(Pcount c){
	return c->number_of_counts;
}

void print_count(Pcount c, Pvariable v){
	int i,j;
	int size = c->size;
	Pcounter** counts = get_count(c);

	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			printf("C(%s,%s) : \n",get_variable_name(v,i),get_variable_name(v, j));
			print_counter(counts[i][j]);
		}
	}
}

void print_count_light(Pcount c){
	int i,j;
	int size = c->size;
	Pcounter** counts = get_count(c);

	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			printf("C(%d,%d) : \n",i,j);
			print_counter(counts[i][j]);
		}
	}
}

int insert_count_counter(Pcount c, int variable1, int variable2, int* content1, int* content2){

	Pcounter counter12 =  query_count(c,variable1,variable2);

	int* d = query_count_counter(c,variable1,variable2,content1);

	if (d==NULL){
		insert_counter(counter12,content1,content2);
	}
	else{
		change_value_of_counter(counter12,content1,content2);
	}

	return 1;
}


Pcounter* query_all_count(Pcount c, int variable1){
	Pcounter** counts = get_count(c);

	return counts[variable1];
}

Pcounter query_count(Pcount c, int variable1, int variable2){
	Pcounter** counts = get_count(c);

	return counts[variable1][variable2];
}

int* query_count_counter(Pcount c, int variable1, int variable2, int* content){
	Pcounter t = query_count(c,variable1,variable2);

	if (t != NULL){
		int* d = query_counter(t,content);
		return d;
	}
	return NULL;
}


int test_count_counter_is_empty(Pcount c, int variable1, int variable2, int* content){
	int* t = query_count_counter(c,variable1,variable2,content);
	if (t==NULL){
		return 1;
	}
	return *t == 0;
}