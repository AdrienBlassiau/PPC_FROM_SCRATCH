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
#include "tuple.h"
#include "domain.h"
#include "avl.h"
#include "compare_int.h"

Ptuple new_tuple(){
	Ptuple t = (tuple*) malloc(sizeof(tuple));
	PAVLTree avl = avl_tree_new((AVLTreeCompareFunc) int_compare);

	t->tuples = avl;
	t->tuples_tab = NULL;
	t->tuples_key = NULL;
	t->iterator = 0;

	return t;
}

Ptuple free_tuple(Ptuple t){
	avl_tree_free_and_node(get_tuples(t),free_domain_bis);
	free(t->tuples_tab);
	free(t->tuples_key);
	free(t);

	return t;
}

void free_tuple_bis(void *vt){
	Ptuple t = (Ptuple)vt;
	avl_tree_free_and_node(get_tuples(t),free_domain_bis);
	free(t->tuples_tab);
	free(t->tuples_key);
	free(t);
}

unsigned int get_tuple_number(Ptuple t){
	return avl_tree_num_entries(get_tuples(t));
}

PAVLTree get_tuples(Ptuple t){
	return t->tuples;
}

void set_tuple_iterator(Ptuple t,unsigned int val){
	t->iterator = val;
}

unsigned int get_tuple_iterator(Ptuple t){
	return t->iterator;
}

void begin_tuple_iteration(Ptuple t){
	free(t->tuples_tab);
	free(t->tuples_key);

	PAVLTree tuples = get_tuples(t);
	set_tuple_iterator(t,0);
	AVLTreeValue * array1 = avl_tree_to_array(tuples);
	AVLTreeValue * array2 = avl_tree_to_array_2(tuples);
	t->tuples_tab = array1;
	t->tuples_key = array2;
}

int tuple_can_iterate(Ptuple t){
	unsigned int iterator = get_tuple_iterator(t);

	if (iterator < get_tuple_number(t)){
		return 1;
	}
	else{
		set_tuple_iterator(t,0);
		return 0;
	}
}

int get_tuple_current_key(Ptuple t){
	int iterator = get_tuple_iterator(t);

	AVLTreeValue* data_list = t->tuples_key;
	int* data = (int*)(data_list[iterator]);

	return *data;
}

Pdomain get_tuple_current_value(Ptuple t){
	int iterator = get_tuple_iterator(t);

	AVLTreeValue* data_list = t->tuples_tab;
	Pdomain data = (Pdomain)(data_list[iterator]);

	return data;
}

void get_next_tuple(Ptuple t){
	int iterator = get_tuple_iterator(t);

	set_tuple_iterator(t,iterator+1);
}

void print_content(void *vc){
	int *c = (int*) vc;
	printf("%d -> ",*c);
}

void print_tuple(void *vt){
	Ptuple t = (Ptuple) vt;
	print_avl_tree(get_tuples(t),print_domain,print_content);
}

int insert_tuple(Ptuple t, int* content, Pdomain d){
	PAVLTree tuples = get_tuples(t);
	AVLTreeNode *res = avl_tree_insert(tuples,content,d);
	if (res == NULL){
		return 0;
	}
	return 1;
}

int remove_tuple(Ptuple t, int* content){
	PAVLTree tuples = get_tuples(t);

	Pdomain d = query_tuple(t,content);

	if (d != NULL){
		free_domain_bis(d);
	}

	int res = avl_tree_remove(tuples,content);

	return res;
}

Pdomain remove_value_of_content_domain(Ptuple t, int* content, int value){
	PAVLTree tuples = get_tuples(t);
	Pdomain d = query_tuple(t,content);
	remove_from_domain(d,value);
	Pdomain res = avl_tree_change_value(tuples,content,d);

	return res;
}

Pdomain query_tuple(Ptuple t, int* content){
	PAVLTree tuples = get_tuples(t);
	Pdomain d =  avl_tree_lookup(tuples,content);

	return d;
}
