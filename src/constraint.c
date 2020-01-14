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
#include "variable.h"
#include "tuple.h"
#include "domain.h"
#include "avl.h"
#include "compare_int.h"
#include "compare_string.h"

Pconstraint new_constraint(int size){
	int i,j;
	Pconstraint c = (constraint*)malloc(sizeof(constraint));
	Ptuple** tuples_tab;
	Ptuple t;

	tuples_tab = malloc(size*sizeof(Ptuple*));
	for (i = 0; i < size; i++){
		tuples_tab[i] = malloc(size*sizeof(Ptuple));
		for (j = 0; j < size; j++){
			t = new_tuple();
			tuples_tab[i][j] = t;
		}
	}

	c->tuples_tab = tuples_tab;
	c->number_of_constraints = 0;
	c->size = size;

	return c;
}

Pconstraint free_constraint(Pconstraint c){
	int i,j;
	int size = c->size;

	Ptuple** tuples_tab = c->tuples_tab;

	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			free_tuple(tuples_tab[i][j]);
		}
		free(tuples_tab[i]);
	}
	free(c->tuples_tab);
	free(c);

	return c;
}

Ptuple** get_constraint(Pconstraint c){
	return c->tuples_tab;
}

int get_constraint_total_number(Pconstraint c){
	return c->number_of_constraints;
}

void print_constraint(Pconstraint c, Pvariable v){
	int i,j;
	int size = c->size;
	Ptuple** constraints = get_constraint(c);

	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			printf("C(%s,%s) : \n",get_variable_name(v,i),get_variable_name(v, j));
			print_tuple(constraints[i][j]);
		}
	}
}

void print_constraint_light(Pconstraint c){
	int i,j;
	int size = c->size;
	Ptuple** constraints = get_constraint(c);

	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			printf("C(%d,%d) : \n",i,j);
			print_tuple(constraints[i][j]);
		}
	}
}

int insert_constraint_tuples(Pconstraint c, int variable1, int variable2, int content, int size){

	Ptuple t2 = query_constraint(c,variable1,variable2);

	if (query_constraint_tuples(c,variable1,variable2,content) == NULL){
		Pdomain d = new_domain(size);
		int res = insert_tuple(t2,content,d);

		return res;
	}
	return 0;
}

int insert_constraint_tuple(Pconstraint c, int variable1, int variable2, int content1, int content2, int size){

	if(query_constraint_tuples(c,variable1,variable2,content1) == NULL){
		insert_constraint_tuples(c,variable1,variable2,content1,size);
	}

	Pdomain d = query_constraint_tuples(c,variable1,variable2,content1);

	if (query_constraint_tuple(c,variable1,variable2,content1,content2) == 0)
	{
		int res = insert_in_domain(d,content2);
		return res;
	}

	return 0;
}


Ptuple* query_all_constraint(Pconstraint c, int variable1){
	Ptuple** constraints = get_constraint(c);

	return constraints[variable1];
}

Ptuple query_constraint(Pconstraint c, int variable1, int variable2){
	Ptuple** constraints = get_constraint(c);

	return constraints[variable1][variable2];
}

Pdomain query_constraint_tuples(Pconstraint c, int variable1, int variable2, int content){
	Ptuple t = query_constraint(c,variable1,variable2);
	if (t != NULL){
		Pdomain d = query_tuple(t,content);
		return d;
	}
	return NULL;
}

int query_constraint_tuple(Pconstraint c, int variable1, int variable2, int content1, int content2){
	Pdomain d = query_constraint_tuples(c,variable1,variable2,content1);
	if (d != NULL){
		int res = query_domain(d,content2);
		return res;
	}
	return 0;
}

int test_contraint_exists(Pconstraint c, int variable1, int variable2){
	Ptuple t = query_constraint(c,variable1,variable2);

	return get_tuple_number(t);
}

int test_contraint_value_exists(Pconstraint c, int variable1, int variable2, int val){
	Pdomain d = query_constraint_tuples(c,variable1,variable2,val);

	return d!=NULL;
}

int test_contraint_tuple_exists(Pconstraint c, int variable1, int variable2, int val1, int val2){
	int res = query_constraint_tuple(c,variable1,variable2,val1,val2);

	return res;
}

int get_variable_degree(Pconstraint c, int variable1){
	int i;
	int degree = 0;
	int size = c->size;

	for (i = 0; i < size; i++){
		if(test_contraint_exists(c,variable1,i)){
			degree++;
		}
	}

	return degree;
}