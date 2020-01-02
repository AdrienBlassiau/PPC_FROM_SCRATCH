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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"


Pstack new_stack(void)
{
	return NULL;
}

Bool is_empty_stack(Pstack st)
{
	if(st == NULL)
		return true;

	return false;
}

Pstack push_stack(Pstack st, int x)
{
	StackElement *element;

	element = malloc(sizeof(*element));

	if(element == NULL)
	{
		fprintf(stderr, "Probleme allocation dynamique.\n");
		exit(EXIT_FAILURE);
	}

	element->value = x;
	element->next = st;

	return element;
}

Pstack pop_stack(Pstack st)
{
	StackElement *element;

	if(is_empty_stack(st))
		return new_stack();

	element = st->next;
	free(st);

	return element;
}

void print_stack(Pstack st)
{
	if(is_empty_stack(st))
	{
		printf("Rien a afficher, la Pile est vide.\n");
		return;
	}

	while(!is_empty_stack(st))
	{
		printf("[%d]\n", st->value);
		st = st->next;
	}
}


int top_stack(Pstack st)
{
	if(is_empty_stack(st)){
		return -1;
	}

	return st->value;
}

int stack_length(Pstack st)
{
	int length = 0;

	while(!is_empty_stack(st))
	{
		length++;
		st = st->next;
	}

	return length;
}

Pstack free_stack(Pstack st)
{
	while(!is_empty_stack(st))
		st = pop_stack(st);

	return new_stack();
}