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


/** @file constraint.h
 *
 * @brief This file manages the constraint representation.
 */

#ifndef CONSTRAINT__H
#define CONSTRAINT__H

#include "avl.h"
#include "domain.h"

/**
 * \struct variables
 * \brief variables structure
 *
 * \a A variables tructure is a set of variables associated to a domain
 *
 */
typedef struct constraint {
  PAVLTree constraints;
  unsigned int iterator;
  AVLTreeValue *constraints_tab;
} constraint, *Pconstraint;

#endif