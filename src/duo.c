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

#include "duo.h"
#include "stack.h"

Pduo new_duo(int var, int val){
	Pduo duo = (Pduo)malloc(sizeof(duo));
	duo->var = var;
	duo->val = val;
	return duo;
}

void free_duo(void *pduo){
	Pduo duo = (Pduo) pduo;
	free(duo);
}

void print_duo(void *pduo){
	Pduo duo = (Pduo) pduo;
	printf("(%d,%d)\n",duo->var,duo->val);
}

Pduostack new_duostack(void){
	return NULL;
}

Bool is_empty_duostack(Pduostack st){
	if(st == NULL)
		return true;

	return false;
}

Pduostack push_duostack(Pduostack st, Pduo duo){
	Pduostack element;

	element = malloc(sizeof(*element));

	if(element == NULL)
	{
		fprintf(stderr, "Probleme allocation dynamique.\n");
		exit(EXIT_FAILURE);
	}

	element->duo_element = duo;
	element->next = st;

	return element;
}

Pduostack pop_duostack(Pduostack st){
	Pduostack element;

	if(is_empty_duostack(st))
		return new_duostack();

	element = st->next;
	free(st->duo_element);
	free(st);

	return element;
}

void print_duostack(void* vst){
	Pduostack st = (Pduostack) vst;
	if(is_empty_duostack(st)){
		printf("Rien a afficher, la Pile est vide.\n");
		return;
	}

	while(!is_empty_duostack(st)){
		print_duo(st->duo_element);
		st = st->next;
	}
}


Pduo top_duostack(Pduostack st){
	if(is_empty_duostack(st)){
		return NULL;
	}

	return st->duo_element;
}

int duostack_length(Pduostack st){
	int length = 0;

	while(!is_empty_duostack(st))
	{
		length++;
		st = st->next;
	}

	return length;
}

void free_duostack(void* vst){
	Pduostack st = (Pduostack) vst;
	while(!is_empty_duostack(st))
		st = pop_duostack(st);
}