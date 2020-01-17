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

/** @file draw.h
 *
 * @brief This file manages the drawing of the tree associated to the problem.
 */


#ifndef DRAW__H
#define DRAW__H

#include "include.h"
#include "variable.h"
#include "instance.h"
#include "constraint.h"
#include "Sstruct.h"
#include "duo.h"
#include "count.h"
#include "csp.h"

#define SHOW_PYTHON 1

/**
 * This function inits the python environment.
 */
void init_py();

/**
 * THis function init the graph associated to the constraint.
 * @param csp The csp structure.
 */
void init_graph(Pcsp csp);

/**
 * This function close the python environment.
 */
void end_py();

/**
 * THis function init the graph associated to the constraint.
 * @param csp The csp structure.
 */
void draw_graph(Pcsp csp);


#endif
