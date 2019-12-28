/*

Copyright (c) 2005-2008, Simon Howard

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

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "compare_string.h"

/* Comparison functions for strings */

int tuple_compare(void *tuple1, void *tuple2)
{
	int result1, result2;
	char** t1 = (char**)tuple1;
	char** t2 = (char**)tuple2;

	char* t11 = t1[0];
	char* t12 = t1[1];
	char* t21 = t2[0];
	char* t22 = t2[1];

	result1 = strcmp((char *) t11, (char *) t21);
	result2 = strcmp((char *) t12, (char *) t22);

	if (result1 < 0) {
		return -1;
	} else if (result1 > 0) {
		return 1;
	} else {
		if (result2 < 0) {
			return -1;
		} else if (result2 > 0) {
			return 1;
		} else {
			return 0;
		}
	}
}