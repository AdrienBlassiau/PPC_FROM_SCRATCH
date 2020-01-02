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


/** @file instance.h
 *
 * @brief This file manages the instance representation.
 */

#ifndef INSTANCE__H
#define INSTANCE__H

#include "queue.h"

/**
 * \struct instance
 * \brief instance structure
 *
 * \a An instance structure is a
 *
 */
typedef struct instance {
  int** linked_list;
  PQueue free_list;
  int number_of_linked;
  int size;
} instance, *Pinstance;

Pinstance new_instance(int size);

Pinstance free_instance(Pinstance inst);

int** get_linked_list(Pinstance inst);

PQueue get_free_list(Pinstance inst);

int get_number_of_linked(Pinstance inst);

int get_number_of_free(Pinstance inst);

void print_instance(void *vd);

int add_free_variable(Pinstance inst, int *v);

int remove_linked_variable(Pinstance inst, int v);

int add_linked_variable(Pinstance inst, int v, int val);

int is_free(Pinstance inst, int value);

int is_linked(Pinstance inst, int value);

int* pop_free_list(Pinstance inst);

#endif

