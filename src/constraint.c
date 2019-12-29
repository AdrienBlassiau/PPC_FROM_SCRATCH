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
#include "constraint.h"
#include "tuple.h"
#include "domain.h"
#include "avl.h"
#include "compare_int.h"
#include "compare_string.h"

Pconstraint new_constraint(){
	Pconstraint c = (constraint*)malloc(sizeof(constraint));
	PAVLTree avl = avl_tree_new((AVLTreeCompareFunc) string_compare);

	c->constraints = avl;
	c->constraint_tab1 = NULL;
	c->constraint_tab2 = NULL;
	c->constraint_key1 = NULL;
	c->constraint_key2 = NULL;
	c->iterator1 = 0;
	c->iterator2 = 0;

	return c;
}

void free_constraint2(void *vt){
	PAVLTree t = (PAVLTree)vt;
	avl_tree_free_and_node(t,free_tuple_bis);
}

Pconstraint free_constraint(Pconstraint c){
	PAVLTree constraints = get_constraint(c);
	avl_tree_free_and_node(constraints,free_constraint2);
	free(c->constraint_tab1);
	free(c->constraint_tab2);
	free(c->constraint_key1);
	free(c->constraint_key2);
	free(c);

	return c;
}

PAVLTree get_constraint(Pconstraint c){
	return c->constraints;
}

unsigned int get_constraint_number1(Pconstraint c){
	PAVLTree constraints = get_constraint(c);
	return avl_tree_num_entries(constraints);
}

unsigned int get_constraint_number2(Pconstraint c, char* variable1){
	PAVLTree sub_contraints = query_all_constraint(c,variable1);
	return avl_tree_num_entries(sub_contraints);
}

unsigned int get_constraint_iterator1(Pconstraint c){
	return c->iterator1;
}

unsigned int get_constraint_iterator2(Pconstraint c){
	return c->iterator2;
}

void set_constraint_iterator1(Pconstraint c, unsigned int val){
	c->iterator1 = val;
}

void set_constraint_iterator2(Pconstraint c, unsigned int val){
	c->iterator2 = val;
}

void begin_constraint_iteration1(Pconstraint c){
	free(c->constraint_tab1);
	free(c->constraint_key1);

	PAVLTree constraints = get_constraint(c);
	set_constraint_iterator1(c,0);
	AVLTreeValue * array1 = avl_tree_to_array(constraints);
	AVLTreeValue * array2 = avl_tree_to_array_2(constraints);
	c->constraint_tab1 = array1;
	c->constraint_key1 = array2;
}

void begin_constraint_iteration2(Pconstraint c){
	free(c->constraint_tab2);
	free(c->constraint_key2);

	unsigned int iterator1 = get_constraint_iterator1(c);

	AVLTreeValue* tab = c->constraint_tab1;
	set_constraint_iterator2(c,0);

	AVLTreeValue * array1 = avl_tree_to_array(tab[iterator1]);
	AVLTreeValue * array2 = avl_tree_to_array_2(tab[iterator1]);
	c->constraint_tab2 = array1;
	c->constraint_key2 = array2;
}

int constraint_can_iterate1(Pconstraint c){
	unsigned int iterator = get_constraint_iterator1(c);

	if (iterator < get_constraint_number1(c)){
		return 1;
	}
	else{
		set_constraint_iterator1(c,0);
		return 0;
	}
}

int constraint_can_iterate2(Pconstraint c){
	unsigned int iterator = get_constraint_iterator2(c);
	char* variable1 = get_constraint_current_key1(c);

	if (iterator < get_constraint_number2(c,variable1)){
		return 1;
	}
	else{
		set_constraint_iterator2(c,0);
		return 0;
	}
}

char* get_constraint_current_key1(Pconstraint c){
	int iterator = get_constraint_iterator1(c);

	AVLTreeValue* data_list = c->constraint_key1;
	char* data = (char*)(data_list[iterator]);

	return data;
}

char* get_constraint_current_key2(Pconstraint c){
	int iterator = get_constraint_iterator2(c);

	AVLTreeValue* data_list = c->constraint_key2;
	char* data = (char*)(data_list[iterator]);

	return data;
}

PAVLTree get_constraint_current_value1(Pconstraint c){
	int iterator = get_constraint_iterator1(c);

	AVLTreeValue* data_list = c->constraint_tab1;
	PAVLTree data = (PAVLTree)(data_list[iterator]);

	return data;
}

Ptuple get_constraint_current_value2(Pconstraint c){
	int iterator = get_constraint_iterator2(c);

	AVLTreeValue* data_list = c->constraint_tab2;
	Ptuple data = (Ptuple)(data_list[iterator]);

	return data;
}

void get_next_constraint1(Pconstraint c){
	int iterator = get_constraint_iterator1(c);
	set_constraint_iterator1(c,iterator+1);
}

void get_next_constraint2(Pconstraint c){
	int iterator = get_constraint_iterator2(c);
	set_constraint_iterator2(c,iterator+1);
}

unsigned int get_constraint_total_number(Pconstraint c){
	unsigned int number_of_constraints = 0;
	unsigned int avl_size;
	PAVLTree current_value;
	begin_constraint_iteration1(c);

	while(constraint_can_iterate1(c)) {
		current_value =  get_constraint_current_value1(c);
		avl_size = avl_tree_num_entries(current_value);
		number_of_constraints += avl_size;
		get_next_constraint1(c);
	}

	return number_of_constraints;
}

void print_constraint_tuple(void *vt){
	PAVLTree t = (PAVLTree)vt;
	printf("---\n");
	print_avl_tree(t,print_tuple,print_string);
	printf("---\n");
	printf("---\n");
}

void print_constraint(Pconstraint c){
	PAVLTree constraints = get_constraint(c);
	print_avl_tree(constraints,print_constraint_tuple,print_string);
}

int insert_all_constraint(Pconstraint c, char* variable1){
	PAVLTree constraints = get_constraint(c);

	if(query_all_constraint(c,variable1) == NULL){
		PAVLTree avl = avl_tree_new((AVLTreeCompareFunc) string_compare);
		AVLTreeNode *res = avl_tree_insert(constraints,variable1,avl);

		if (res == NULL){
			return 0;
		}
		return 1;

	}
	else{
		return 0;
	}
}

int insert_constraint(Pconstraint c, char* variable1, char* variable2){

	if(query_all_constraint(c,variable1) == NULL){
		insert_all_constraint(c,variable1);
	}

	PAVLTree avl1 = query_all_constraint(c,variable1);

	if(query_constraint(c,variable1,variable2) == NULL){
		Ptuple t2 = new_tuple();
		AVLTreeNode *res = avl_tree_insert(avl1,variable2,t2);

		if (res == NULL){
			return 0;
		}
		return 1;
	}
	else{
		return 0;
	}

}

int insert_constraint_tuples(Pconstraint c, char* variable1, char* variable2, int* content){

	if(query_constraint(c,variable1,variable2) == NULL){
		insert_constraint(c,variable1,variable2);
	}

	Ptuple t2 = query_constraint(c,variable1,variable2);

	if (query_constraint_tuples(c,variable1,variable2,content) == NULL)
	{
		Pdomain d = new_domain();
		int res = insert_tuple(t2,content,d);

		return res;
	}
	return 0;
}

int insert_constraint_tuple(Pconstraint c, char* variable1, char* variable2, int* content1, int* content2){

	if(query_constraint_tuples(c,variable1,variable2,content1) == NULL){
		insert_constraint_tuples(c,variable1,variable2,content1);
	}

	Pdomain d = query_constraint_tuples(c,variable1,variable2,content1);

	if (query_constraint_tuple(c,variable1,variable2,content1,content2) == 0)
	{
		int res = insert_in_domain(d,content2);
		return res;
	}

	return 0;
}


int remove_all_constraint(Pconstraint c, char* variable1){
	PAVLTree constraints = get_constraint(c);
	PAVLTree t2 = query_all_constraint(c,variable1);
	int res = avl_tree_remove(constraints,variable1);

	if (t2 != NULL){
		free_constraint2(t2);
	}


	return res;
}

int remove_constraint(Pconstraint c, char* variable1, char* variable2){
	PAVLTree t1 = query_all_constraint(c,variable1);
	Ptuple t2 = query_constraint(c,variable1, variable2);
	int res = avl_tree_remove(t1,variable2);

	if (t2 != NULL){
		free_tuple_bis(t2);
	}

	return res;
}

int remove_constraint_tuples(Pconstraint c, char* variable1, char* variable2, int* content){
	int res = 0;
	Ptuple t2 = query_constraint(c,variable1,variable2);
	if (t2 != NULL){
		res = remove_tuple(t2,content);
	}

	return res;
}

int remove_constraint_tuple(Pconstraint c, char* variable1, char* variable2, int* content1, int* content2){
	int res = 0;
	Pdomain d = query_constraint_tuples(c,variable1,variable2,content1);
	if (d != NULL){
		res = remove_from_domain(d,content2);
	}
	return res;
}

PAVLTree query_all_constraint(Pconstraint c, char* variable1){
	PAVLTree constraints = get_constraint(c);
	PAVLTree t = avl_tree_lookup(constraints,variable1);

	return t;
}

Ptuple query_constraint(Pconstraint c, char* variable1, char* variable2){
	PAVLTree constraints = get_constraint(c);
	PAVLTree t1 = avl_tree_lookup(constraints,variable1);
	if (t1 != AVL_TREE_NULL){
		Ptuple t = avl_tree_lookup(t1,variable2);
		return t;
	}
	return NULL;
}

Pdomain query_constraint_tuples(Pconstraint c, char* variable1, char* variable2, int* content){
	Ptuple t = query_constraint(c,variable1,variable2);
	if (t != NULL){
		Pdomain d = query_tuple(t,content);
		return d;
	}
	return NULL;
}

int query_constraint_tuple(Pconstraint c, char* variable1, char* variable2, int* content1, int* content2){
	Pdomain d = query_constraint_tuples(c,variable1,variable2,content1);
	if (d != NULL){
		int res = query_domain(d,content2);

		return res;
	}
	return 0;
}
