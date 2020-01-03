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
#include "counter.h"
#include "avl.h"
#include "compare_int.h"

Pcounter new_counter(){
	Pcounter c = (counter*) malloc(sizeof(counter));
	PAVLTree avl = avl_tree_new((AVLTreeCompareFunc) int_compare);

	c->counters = avl;
	c->counters_tab = NULL;
	c->counters_key = NULL;
	c->iterator = 0;

	return c;
}

Pcounter free_counter(Pcounter c){
	avl_tree_free(get_counters(c));
	free(c->counters_tab);
	free(c->counters_key);
	free(c);

	return c;
}

void free_counter_bis(void *vc){
	Pcounter c = (Pcounter)vc;
	avl_tree_free(get_counters(c));
	free(c->counters_tab);
	free(c->counters_key);
	free(c);
}

unsigned int get_counter_number(Pcounter c){
	return avl_tree_num_entries(get_counters(c));
}

PAVLTree get_counters(Pcounter c){
	return c->counters;
}

void set_counter_iterator(Pcounter c, unsigned int val){
	c->iterator = val;
}

unsigned int get_counter_iterator(Pcounter c){
	return c->iterator;
}

void begin_counter_iteration(Pcounter c){
	free(c->counters_tab);
	free(c->counters_key);

	PAVLTree counters = get_counters(c);
	set_counter_iterator(c,0);
	AVLTreeValue * array1 = avl_tree_to_array(counters);
	AVLTreeValue * array2 = avl_tree_to_array_2(counters);
	c->counters_tab = array1;
	c->counters_key = array2;
}

int counter_can_iterate(Pcounter c){
	unsigned int iterator = get_counter_iterator(c);

	if (iterator < get_counter_number(c)){
		return 1;
	}
	else{
		set_counter_iterator(c,0);
		return 0;
	}
}

int get_counter_current_key(Pcounter c){
	int iterator = get_counter_iterator(c);

	AVLTreeValue* data_list = c->counters_key;
	int* data = (int*)(data_list[iterator]);

	return *data;
}

int get_counter_current_value(Pcounter c){
	int iterator = get_counter_iterator(c);

	AVLTreeValue* data_list = c->counters_tab;
	int* data = (int*)(data_list[iterator]);

	return *data;
}

void get_next_counter(Pcounter c){
	int iterator = get_counter_iterator(c);

	set_counter_iterator(c,iterator+1);
}

void print_key(void *vc){
	int *c = (int*) vc;
	printf("%d -> ",*c);
}

void print_counter(void *vc){
	Pcounter c = (Pcounter) vc;
	print_avl_tree(get_counters(c),print_int,print_key);
}

int insert_counter(Pcounter c, int* content, int* count){
	PAVLTree counters = get_counters(c);
	AVLTreeNode *res = avl_tree_insert(counters,content,count);
	if (res == NULL){
		return 0;
	}
	return 1;
}

int remove_counter(Pcounter c, int* content){
	PAVLTree counters = get_counters(c);

	int res = avl_tree_remove(counters,content);

	return res;
}

int* change_value_of_counter(Pcounter c, int* content, int* value){
	PAVLTree counters = get_counters(c);
	int* res = avl_tree_change_value(counters,content,value);

	return res;
}

int* query_counter(Pcounter c, int* content){
	PAVLTree counters = get_counters(c);
	int* d =  avl_tree_lookup(counters,content);

	return d;
}
