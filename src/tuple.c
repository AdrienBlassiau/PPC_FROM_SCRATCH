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

Ptuples new_tuples(){
	Ptuples t = (tuples*) malloc(sizeof(tuples));
	PAVLTree avl = avl_tree_new((AVLTreeCompareFunc) int_compare);

	t->tup_dom = avl;
	t->tup_dom_tab = NULL;
	t->iterator = 0;

	return t;
}

Ptuples free_tuples(Ptuples t){
	avl_tree_free_and_node(get_tup_dom(t),free_domain_bis);
	free(t->tup_dom_tab);
	free(t);

	return t;
}

void free_tuples_bis(void *vt){
	Ptuples t = (Ptuples)vt;
	avl_tree_free_and_node(get_tup_dom(t),free_domain_bis);
	free(t->tup_dom_tab);
	free(t);
}

unsigned int get_tuples_number(Ptuples t){
	return avl_tree_num_entries(get_tup_dom(t));
}

PAVLTree get_tup_dom(Ptuples t){
	return t->tup_dom;
}

void set_tuple_iterator(Ptuples t,unsigned int val){
	t->iterator = val;
}

unsigned int get_tuple_iterator(Ptuples t){
	return t->iterator;
}

void begin_tuples_iteration(Ptuples t){
	PAVLTree tup_dom = get_tup_dom(t);
	set_tuple_iterator(t,0);
	AVLTreeValue * array = avl_tree_to_array(tup_dom);
	t->tup_dom_tab = array;
}

int tuples_can_iterate(Ptuples t){
	unsigned int iterator = get_tuple_iterator(t);

	if (iterator < get_tuples_number(t)){
		return 1;
	}
	else{
		set_tuple_iterator(t,0);
		return 0;
	}
}

Pdomain get_tuple_current_value(Ptuples t){
	int iterator = get_tuple_iterator(t);

	AVLTreeValue* data_list = t->tup_dom_tab;
	Pdomain data = (Pdomain)(data_list[iterator]);

	set_tuple_iterator(t,iterator+1);
	return data;
}

void print_content(void *vc){
	int c= (Ptuples) vc;
	printf("%d -> \n",c);
}

void print_tuples(void *vt){
	Ptuples t = (Ptuples) vt;
	print_avl_tree(get_tup_dom(t),print_domain,print_content);
}

int insert_tuples(Ptuples t, int* content, Pdomain d){
	PAVLTree tup_dom = get_tup_dom(t);
	AVLTreeNode *res = avl_tree_insert(tup_dom,content,d);
	if (res == NULL){
		return 0;
	}
	return 1;
}

int remove_tuples(Ptuples t, int* content){
	PAVLTree tup_dom = get_tup_dom(t);
	Pdomain d = query_tuples(t,content);
	free_domain_bis(d);
	int res = avl_tree_remove(tup_dom,content);

	return res;
}

Pdomain remove_value_of_content_domain(Ptuples t, int* content, int* value){
	PAVLTree tup_dom = get_tup_dom(t);
	Pdomain d = query_tuples(t,content);
	remove_from_domain(d,value);
	Pdomain res = avl_tree_change_value(tup_dom,content,d);

	return res;
}

Pdomain query_tuples(Ptuples t, int* content){
	PAVLTree tup_dom = get_tup_dom(t);
	Pdomain d =  avl_tree_lookup(tup_dom,content);

	return d;
}
