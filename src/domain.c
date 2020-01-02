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
#include "domain.h"
#include "set.h"
#include "compare_int.h"
#include "hash_int.h"

Pdomain new_domain(){
	Pdomain d = (domain*) malloc(sizeof(domain));
	PSet set = set_new(int_hash, int_equal);

	d->values = set;

	return d;
}

Pdomain free_domain(Pdomain d){
	if (d != NULL){
		set_free(get_domain_values(d));
		free(d);
	}


	return d;
}

void free_domain_bis(void *vd){
	Pdomain d = (Pdomain)vd;
	if (d != NULL){
		set_free(get_domain_values(d));
		free(d);
	}
}

unsigned int get_domain_size(Pdomain d){
	return set_num_entries(get_domain_values(d));
}

PSet get_domain_values(Pdomain d){
	return d->values;
}

SetIterator get_dom_iterator(Pdomain d){
	return d->iterator;
}

void begin_domain_iteration(Pdomain d){
	SetIterator iterator;
	PSet values = get_domain_values(d);
	set_iterate(values, &iterator);
	d->iterator = iterator;
}

int domain_can_iterate(Pdomain d){
	SetIterator iterator = get_dom_iterator(d);
	int more =  set_iter_has_more(&iterator);
	d->iterator = iterator;
	return more;
}

int get_current_value(Pdomain d){
	SetIterator iterator = get_dom_iterator(d);
	int value = iterator.next_chain;
	set_iter_next(&iterator);
	d->iterator = iterator;

	return value;
}

void print_domain(void* vd){
	Pdomain d = (Pdomain) vd;
	int value;
	begin_domain_iteration(d);

	while(domain_can_iterate(d)){
		value = get_current_value(d);
		printf("%d ",value);
	}
	printf("\n");
}

int insert_in_domain(Pdomain d, int* value){
	PSet values = get_domain_values(d);
	return set_insert(values,value);
}

int remove_from_domain(Pdomain d, int* value){
	PSet values = get_domain_values(d);
	return set_remove(values,value);
}

int query_domain(Pdomain d, int* value){
	PSet values = get_domain_values(d);
	return set_query(values,value);
}