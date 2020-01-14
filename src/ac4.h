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


Pvariable MAC(Pcsp csp, int var, int val);

void revert_MAC(Pcsp csp, Pvariable v_copy);

int revert_MAC_light(Pcsp csp, Pvariable v_copy);

int initAC4(Pcsp csp, int* tab_alloc);

int AC4(Pcsp csp);

int run_AC4(Pcsp csp);

#endif