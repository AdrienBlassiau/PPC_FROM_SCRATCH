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
#include "variable.h"
#include "domain.h"
#include "avl.h"
#include "compare_int.h"
#include "compare_tuple.h"


Pconstraints new_constraints(){
	Pconstraints c = (constraints*)malloc(sizeof(constraints));
	PAVLTree avl = avl_tree_new((AVLTreeCompareFunc) tuple_compare);

	c->constraints = avl;
	c->constraints_tab = NULL;
	c->iterator = 0;

	return c;
}

void free_content(void *vc){
	Pconstraints c = (Pconstraints)vc;
	avl_tree_free_and_node(get_constraints(c),free_domain_bis);
	free(c);
}

Pconstraints free_constraints(Pconstraints c){
	avl_tree_free_and_node(get_constraints(c),free_content);
	free(c->constraints_tab);
	free(c);

	return c;
}

unsigned int get_constraints_number(Pconstraints c){
	return avl_tree_num_entries(get_constraints(c));
}

PAVLTree get_constraints(Pconstraints c){
	return c->constraints;
}

void set_constraints_iterator(Pconstraints c,unsigned int val){
	c->iterator = val;
}

unsigned int get_constraints_iterator(Pconstraints c){
	return c->iterator;
}

void begin_constraints_iteration(Pconstraints c){
	PAVLTree constraints = get_constraints(c);
	set_constraints_iterator(c,0);
	AVLTreeValue * array = avl_tree_to_array(constraints);
	c->constraints_tab = array;
}

int constraints_can_iterate(Pconstraints c){
	unsigned int iterator = begin_constraints_iteration(c);

	if (iterator < get_constraints_number(c)){
		return 1;
	}
	else{
		set_constraints_iterator(c,0);
		return 0;
	}
}

PAVLTree get_constraints_current_tuples(Pconstraints c){
	int iterator = begin_constraints_iteration(c);

	AVLTreeValue* data_list = c->constraints_tab;
	PAVLTree data = (PAVLTree)(data_list[iterator]);

	set_constraints_iterator(c,iterator+1);
	return data;
}

void print_constraints(Pconstraint c){
	print_avl_tree(get_constraints(c),print_tuples);
}

void print_constraints_tuple(Pconstraint c, char* variable1, char* variable2);

int insert_constraints(Pconstraint c, char* variable1, char* variable2);

int insert_constraints_tuple(Pconstraint c, char* variable1, char* variable2, int content1, int content2);

int insert_constraints_tuples(Pconstraint c, char* variable1, char* variable2, int content, Pdomain d);

int remove_constraints(Pconstraint c, char* variable1, char* variable2);

int remove_constraints_tuple(Pconstraint c, char* variable1, char* variable2, int content1, int content2);

int remove_constraints_tuples(Pconstraint c, char* variable1, char* variable2, int content, Pdomain d);

Pdomain query_constraints(Pconstraint c, char* variable1, char* variable2);

Pdomain query_constraints_tuple(Pconstraint c, char* variable1, char* variable2, int content1, int content2);

Pdomain query_constraints_tuples(Pconstraint c, char* variable1, char* variable2, int content);

void print_constraints(Pconstraints c){
	print_avl_tree(get_constraints(c),print_domain);
}

int insert_constraints(Pconstraints c, char* variable, Pdomain d){
	PAVLTree constraints = get_constraints(c);
	AVLTreeNode *res = avl_tree_insert(constraints,variable,d);
	if (res == NULL){
		return 0;
	}
	return 1;
}

int remove_constraints(Pconstraints c, char* variable){
	PAVLTree constraints = get_constraints(c);
	int res = avl_tree_remove(constraints,variable);

	return res;
}

Pdomain remove_value_of_variable_domain(Pconstraints c, char* variable, int* value){
	PAVLTree constraints = get_constraints(c);
	Pdomain d = query_constraints(c,variable);
	remove_from_domain(d,value);
	Pdomain res = avl_tree_change_value(constraints,variable,d);

	return res;
}

Pdomain query_constraints(Pconstraints c, char* variable){
	PAVLTree constraints = get_constraints(c);
	Pdomain d =  avl_tree_lookup(constraints,variable);

	return d;
}