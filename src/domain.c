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
#include "set.h"
#include "domain.h"
#include "compare_int.h"

Pdomain new_domain(int size){
	Pdomain d = (Pdomain) malloc(sizeof(domain));
	Pset set = new_set(size);

	d->values = set;

	return d;
}

Pdomain free_domain(Pdomain d){
	if (d != NULL){
		free_set(get_domain_values(d));
		free(d);
	}

	return d;
}

void free_domain_bis(void *vd){
	Pdomain d = (Pdomain)vd;
	if (d != NULL){
		free_set(get_domain_values(d));
		free(d);
	}
}

int get_domain_size(Pdomain d){
	return get_current_size(get_domain_values(d));
}

Pset get_domain_values(Pdomain d){
	return d->values;
}


void begin_domain_iteration(Pdomain d){
	Pset values = get_domain_values(d);
	set_iterate(values);
}

int domain_can_iterate(Pdomain d, int i){
	return i < get_domain_size(d);
}

int get_current_value(Pdomain d){
	Pset values = get_domain_values(d);
	int value = get_set_value(values);

	return value;
}

void print_domain(void* vd){
	int i;
	Pdomain d = (Pdomain) vd;
	int value;
	int iterator = d->values->iterator;

	if (get_domain_size(d)==0){
		printf("Empty domain\n");
		return;
	}

	begin_domain_iteration(d);

	i=0;
	while(domain_can_iterate(d,i)){
		value = get_current_value(d);
		printf("%d ",value);
		i++;
	}
	printf("\n");
	d->values->iterator = iterator;
}

int insert_in_domain(Pdomain d, int value){
	Pset values = get_domain_values(d);
	return set_insert(values,value);
}

int remove_from_domain(Pdomain d, int value){
	Pset values = get_domain_values(d);
	return set_remove(values,value);
}

void set_iterator(Pdomain d, int it){
	d->values->iterator = it;
}

int get_iterator(Pdomain d){
	return d->values->iterator;
}

int remove_all_except_one_from_domain(Pdomain d, int value){
	int i,v;
	int iterator = d->values->iterator;
	begin_domain_iteration(d);

	i = get_domain_size(d);
	while(i>0){
		v = get_current_value(d);
		remove_from_domain(d,v);
		i--;
	}
	insert_in_domain(d,value);
	d->values->iterator = iterator;

	return 1;
}

int fill_domain(Pdomain d, Pdomain d_copy){
	int i,v;
	int iterator = d->values->iterator;
	begin_domain_iteration(d);

	i = get_domain_size(d_copy);
	while(i>0){
		v = get_current_value(d_copy);
		insert_in_domain(d,v);
		i--;
	}
	d->values->iterator = iterator;

	return 1;
}

Pdomain copy_domain(Pdomain d){
	int i,v;
	Pset values = get_domain_values(d);
	int size = get_total_size(values);
	Pdomain d_copy = new_domain(size);

	int iterator = d->values->iterator;
	begin_domain_iteration(d);

	i = get_domain_size(d);
	while(i>0){
		v = get_current_value(d);
		insert_in_domain(d_copy,v);
		i--;
	}
	d->values->iterator = iterator;

	return d_copy;
}

int query_domain(Pdomain d, int value){
	Pset values = get_domain_values(d);
	return set_query(values,value);
}

int empty_domain(Pdomain d){
	return get_domain_size(d) == 0;
}
