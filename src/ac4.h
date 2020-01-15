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

/** @file ac4.h
 *
 * @brief This file features the AC4 algorithm.
 */

#ifndef AC4__H
#define AC4__H

#include "csp.h"
#include "variable.h"

/**
 * This function runs AC4 during the MAC procedure.
 * @param  csp The csp structure.
 * @param  var The current variable.
 * @param  val The current value of the variable
 * @return     A copy of the variable structure before AC4.
 */
Pvariable MAC(Pcsp csp, int var, int val);

/**
 * This function applies the former state of the csp, before doing AC4.
 * @param csp    The csp we want to revert.
 * @param v_copy A copy of the former variable structure before doing AC4.
 */
void revert_MAC(Pcsp csp, Pvariable v_copy);

/**
 * This function clean the copy of the variable struct, before doing AC4.
 * @param csp    The csp we want to revert.
 * @param v_copy 1 if MAC was on, 0 otherwise.
 */
int revert_MAC_light(Pcsp csp, Pvariable v_copy);

/**
 * This function initializes the AC4 procedure.
 * @param  csp       The csp structure.
 * @param  tab_alloc A tab of allocated space for some data used during AC4.
 * @return           Always 1.
 */
int initAC4(Pcsp csp, int* tab_alloc);

/**
 * THis function runs the AC4 algorithm
 * @param  csp The cs sructure
 * @return     Always 1.
 */
int AC4(Pcsp csp);

/**
 * THis function runs the AC4 algorithm and measures time.
 * @param  csp The csp structure.
 * @return     Always 1
 */
int run_AC4(Pcsp csp);

#endif