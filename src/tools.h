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

/** @file tools.h
 *
 * @brief This file manages all the matrix functions.
 */


#ifndef TOOLS__H
#define TOOLS__H

#include "include.h"

/**
 * This function print a string.
 * @param vs    The string we want to print.
 */
void print_string(void *vs);

/**
 * This function print the content of a matrix.
 * @param m    The matrix we want to print.
 * @param size The size of the matrix we want to print.
 */
void print_matrix(int** m, int size);


/**
 * This function print the content of an array.
 * @param a    The array we want to print.
 * @param size The size of the array we want to print.
 */
void print_array(int* a, int size);

/**
 * This function allocate a matrix, given a size m.
 * @param m    	 A null pointer.
 * @param  size1 The size of the matrix.
 * @param  size2 The size of the sub-matrix.
 * @return       1 if succeed otherwise 0.
 */
int allocate_matrix(int*** m, int size1, int size2);

/**
 * This function frees an allocated matrix in the heap.
 * @param  m    The allocated matrix.
 * @param  size The size of the allocated matrix.
 * @return		1 if succeed otherwise 0.
 */
int free_matrix(int** m, int size);

#endif
