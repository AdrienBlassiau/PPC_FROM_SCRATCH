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

Pvariable new_variable(int size){
	Pvariable v = (variable*) calloc(1,sizeof(variable));
	Pdomain* variables = (Pdomain*) calloc(size,sizeof(Pdomain));
	char** variables_name;

	variables_name = calloc(size,sizeof(char*));

	v->variables_name = variables_name;
	v->variables = variables;
	v->size = size;

	return v;
}

Pvariable free_variable(Pvariable v){
	int i;
	int size = v->size;
	Pdomain* variables = v->variables;
	char ** variables_name = v->variables_name;

	for (i = 0; i < size; i++){
		free_domain_bis(variables[i]);
	}

	for (i = 0; i < size; i++){
		free(variables_name[i]);
	}

	free(v->variables);
	free(v->variables_name);
	free(v);

	return v;
}

void free_variable_bis(void *vv){
	Pvariable v = (Pvariable)vv;

	int i;
	int size = v->size;
	Pdomain* variables = v->variables;

	for (i = 0; i < size; i++){
		free_domain_bis(variables[i]);
	}

	free(v->variables);
	free(v);
}

int get_variable_number(Pvariable v){
	return v->size;
}

int get_variable_index(Pvariable v, char* var_name){
	int i;
	int size = v->size;
	char** variables_name = v->variables_name;
	for (i = 0; i < size; ++i){
		if (strcmp(var_name,variables_name[i]) == 0){
			return i;
		}
	}
	return -1;
}

char* get_variable_name(Pvariable v, int i){
	return v->variables_name[i];
}

Pdomain* get_variables(Pvariable v){
	return v->variables;
}

void print_variable(Pvariable v){
	int i;
	int size = v->size;
	Pdomain* variables = v->variables;
	char** variables_name = v->variables_name;

	for (i = 0; i < size; i++){
		printf("%s\n",variables_name[i]);
		print_domain(variables[i]);
	}
}

int insert_variable(Pvariable v, int i, char* name, Pdomain d){
	char * str = calloc(256,sizeof(char));
	strcpy(str,name);
	v->variables[i] = d;
	v->variables_name[i] = str;

	return 1;
}


int remove_value_of_variable_domain(Pvariable v, int i, int* value){
	Pdomain d = v->variables[i];
	int res = remove_from_domain(d,value);

	return res;
}

int query_value_of_variable_domain(Pvariable v, int i, int* value){
	Pdomain d = v->variables[i];
	int res = query_domain(d,value);

	return res;
}
