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
#include "variable.h"
#include "domain.h"
#include "constraint.h"
#include "tuple.h"
#include "tools.h"
#include "csp.h"


Pcsp generate_8_queens_puzzle(int n){
	int i,j,k,l,count;
	Pdomain d;
	Pcsp csp;

	char var_name[256];
	int total_size = 2*n*n*n*n;

	int* tab_int = calloc(total_size,sizeof(int));

	/* FIRST : VARIABLES and DOMAINS*/
	Pvariable v = new_variable(n);
	for (i = 0; i < n; i++){
		d = new_domain();
		for (j = 0; j < n; j++){
			insert_in_domain(d, &j);
		}
		sprintf(var_name, "%d", i);
		insert_variable(v,i,var_name,d);
	}
	print_variable(v);

	/* SECOND : CONSTRAINTS*/
	Pconstraint c = new_constraint(n);
	count=0;
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			if (i != j){
				for (k = 0; k < n; k++){
					for (l = 0; l < n; l++){
						if (k != l && k-i != l-j && k+i != l+j){
							tab_int[count] = k;
							count++;
							tab_int[count] = l;
							insert_constraint_tuple(c,i,j,&tab_int[count-1],&tab_int[count]);
							count++;
						}
					}
				}
			}
		}
	}

	csp = new_csp(v,c,tab_int,n);

	return csp;
}