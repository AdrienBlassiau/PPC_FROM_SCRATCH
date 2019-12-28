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
#include "compare_string.h"

Pvariables new_variables(){
	Pvariables v = (variables*) malloc(sizeof(variables));
	PAVLTree avl = avl_tree_new((AVLTreeCompareFunc) string_compare);

	v->var_dom = avl;
	v->var_dom_tab = NULL;
	v->iterator = 0;

	return v;
}

Pvariables free_variables(Pvariables v){
	avl_tree_free_and_node(get_var_dom(v),free_domain_bis);
	free(v->var_dom_tab);
	free(v);

	return v;
}

void free_variables_bis(void *vv){
	Pvariables v = (Pvariables)vv;
	avl_tree_free_and_node(get_var_dom(v),free_domain_bis);
	free(v->var_dom_tab);
	free(v);
}

unsigned int get_variables_number(Pvariables v){
	return avl_tree_num_entries(get_var_dom(v));
}

PAVLTree get_var_dom(Pvariables v){
	return v->var_dom;
}

void set_var_iterator(Pvariables v,unsigned int val){
	v->iterator = val;
}

unsigned int get_var_iterator(Pvariables v){
	return v->iterator;
}

void begin_variables_iteration(Pvariables v){
	PAVLTree var_dom = get_var_dom(v);
	set_var_iterator(v,0);
	AVLTreeValue * array = avl_tree_to_array(var_dom);
	v->var_dom_tab = array;
}

int variables_can_iterate(Pvariables v){
	unsigned int iterator = get_var_iterator(v);

	if (iterator < get_variables_number(v)){
		return 1;
	}
	else{
		set_var_iterator(v,0);
		return 0;
	}
}

Pdomain get_var_current_value(Pvariables v){
	int iterator = get_var_iterator(v);

	AVLTreeValue* data_list = v->var_dom_tab;
	Pdomain data = (Pdomain)(data_list[iterator]);

	set_var_iterator(v,iterator+1);
	return data;
}

void print_variables(Pvariables v){
	print_avl_tree(get_var_dom(v),print_domain);
}

int insert_variables(Pvariables v, char* variable, Pdomain d){
	PAVLTree var_dom = get_var_dom(v);
	AVLTreeNode *res = avl_tree_insert(var_dom,variable,d);
	if (res == NULL){
		return 0;
	}
	return 1;
}

int remove_variables(Pvariables v, char* variable){
	PAVLTree var_dom = get_var_dom(v);
	Pdomain d = query_variables(v,variable);
	free_domain_bis(d);
	int res = avl_tree_remove(var_dom,variable);

	return res;
}

Pdomain remove_value_of_variable_domain(Pvariables v, char* variable, int* value){
	PAVLTree var_dom = get_var_dom(v);
	Pdomain d = query_variables(v,variable);
	remove_from_domain(d,value);
	Pdomain res = avl_tree_change_value(var_dom,variable,d);

	return res;
}

Pdomain query_variables(Pvariables v, char* variable){
	PAVLTree var_dom = get_var_dom(v);
	Pdomain d =  avl_tree_lookup(var_dom,variable);

	return d;
}
