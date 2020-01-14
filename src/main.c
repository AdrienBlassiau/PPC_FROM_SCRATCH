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

#include "include.h"
#include "tools.h"
#include "csp.h"
#include "ac4.h"
#include "backtrack.h"
#include "forward_checking.h"
#include "read_file.h"
#include "problem.h"

int main(){
	srand(time(NULL));
	Pcsp csp;
	int mode = 1;

	if (mode == 1){
		char* filename = "inst/test/queen5_5.cspi";
		csp = generate_from_file(filename);
	}
	else{
		csp = generate_8_queens_puzzle(15);
	}

	// print_csp(csp);
	// run_AC4(csp);
	run_forward_checking(csp);
	// print_csp(csp);
	// run_backtrack(csp);

	print_csp(csp);
	free_csp(csp);
	return 0;
}