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
#include "variable.h"
#include "domain.h"
#include "avl.h"
#include "compare_string.h"

Pvariable new_variable(){
	Pvariable v = (variable*) malloc(sizeof(variable));
	PAVLTree avl = avl_tree_new((AVLTreeCompareFunc) string_compare);

	v->variables = avl;
	v->variables_tab = NULL;
	v->variables_key = NULL;
	v->iterator = 0;

	return v;
}

Pvariable free_variable(Pvariable v){
	avl_tree_free_and_node(get_variables(v),free_domain_bis);
	free(v->variables_tab);
	free(v->variables_key);
	free(v);

	return v;
}

void free_variable_bis(void *vv){
	Pvariable v = (Pvariable)vv;
	avl_tree_free_and_node(get_variables(v),free_domain_bis);
	free(v->variables_tab);
	free(v->variables_key);
	free(v);
}

unsigned int get_variable_number(Pvariable v){
	return avl_tree_num_entries(get_variables(v));
}

PAVLTree get_variables(Pvariable v){
	return v->variables;
}

void set_var_iterator(Pvariable v,unsigned int val){
	v->iterator = val;
}

unsigned int get_var_iterator(Pvariable v){
	return v->iterator;
}

void begin_variable_iteration(Pvariable v){
	free(v->variables_tab);
	free(v->variables_key);

	PAVLTree variables = get_variables(v);
	set_var_iterator(v,0);
	AVLTreeValue * array1 = avl_tree_to_array(variables);
	AVLTreeValue * array2 = avl_tree_to_array_2(variables);
	v->variables_tab = array1;
	v->variables_key = array2;
}

int variable_can_iterate(Pvariable v){
	unsigned int iterator = get_var_iterator(v);

	if (iterator < get_variable_number(v)){
		return 1;
	}
	else{
		set_var_iterator(v,0);
		return 0;
	}
}

char* get_var_current_key(Pvariable v){
	int iterator = get_var_iterator(v);

	AVLTreeValue* data_list = v->variables_key;
	char* data = (char*)(data_list[iterator]);

	return data;
}

Pdomain get_var_current_value(Pvariable v){
	int iterator = get_var_iterator(v);

	AVLTreeValue* data_list = v->variables_tab;
	Pdomain data = (Pdomain)(data_list[iterator]);

	return data;
}

void get_next_var(Pvariable v){
	int iterator = get_var_iterator(v);

	set_var_iterator(v,iterator+1);
}

void print_variable(Pvariable v){
	print_avl_tree(get_variables(v),print_domain,print_string);
}

int insert_variable(Pvariable v, char* variable, Pdomain d){
	PAVLTree variables = get_variables(v);
	AVLTreeNode *res = avl_tree_insert(variables,variable,d);
	if (res == NULL){
		return 0;
	}
	return 1;
}

int remove_variable(Pvariable v, char* variable){
	PAVLTree variables = get_variables(v);
	Pdomain d = query_variable(v,variable);
	free_domain_bis(d);
	int res = avl_tree_remove(variables,variable);

	return res;
}

Pdomain remove_value_of_variable_domain(Pvariable v, char* variable, int* value){
	Pdomain d = query_variable(v,variable);
	remove_from_domain(d,value);

	return NULL;
}

Pdomain query_variable(Pvariable v, char* variable){
	PAVLTree variables = get_variables(v);
	Pdomain d =  avl_tree_lookup(variables,variable);

	return d;
}
