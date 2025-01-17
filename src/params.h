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

/** @file params.h
 *
 * @brief This file manages the parameters of the executable.
 */

#ifndef PARAMS__H
#define PARAMS__H

#include "include.h"
#include "csp.h"

/**
 * This function solves the csp.
 * @param  csp The csp struct.
 * @return     0 if success, 1 otherwise (warning !).
 */
int solve_csp(Pcsp* csp);

/**
 * THis function print the csp if it exists.
 * @param  csp The csp struct.
 * @return     1 if success, 0 otherwise.
 */
int show_csp(Pcsp* csp);

/**
 * THis function cleans the csp if it exists
 * @param  csp The csp struct.
 * @return     1 if success, 0 otherwise.
 */
int clean_csp(Pcsp* csp);

/**
 * This function creates the csp according to the given parameters.
 * @param  argc The argc of the main function (number of arguments).
 * @param  argv The argv array of the main function (list of arguments).
 * @param  csp  The csp struct.
 * @return      The created csp.
 */
int generate_csp(int argc, char* argv[], Pcsp* csp);

#endif