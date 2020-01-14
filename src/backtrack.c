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
#include "backtrack.h"
#include "ac4.h"
#include "variable.h"
#include "instance.h"
#include "heuristic.h"
#include "constraint.h"
#include "Sstruct.h"
#include "duo.h"
#include "count.h"

int backtrack(Pcsp csp){

	if (csp->v >= 3){
		printf("ENTREE\n");
		printf("#######\n");
		print_instance(csp->instance_list);
		printf("#######\n");
	}

	int x,v,i;
	Pdomain d;
	Pvariable vars;
	csp->branch_explored++;

	if (break_constraint(csp)){

		if (csp->v >= 3){
			printf("BREAK\n");
		}

		return 0;
	}
	if (complete(csp)){
		return 1;
	}

	x = choose_non_instanciated(csp);
	d = get_current_variable_domain(csp,x);

	begin_domain_iteration(d);

	i = get_domain_size(d);
	while(i>0){
		v = get_current_value(d);

		if (csp->v >= 3){
			printf("ON CHOISIT : %d DE VALEUR : %d\n",x,v);
		}

		vars = MAC(csp,x,v);

		if (csp->v >= 3){
			print_domain(d);
			printf("***\n");
		}

		complete_partial_instance(csp,x,v);
		if (!empty_domain(d)){

			if (csp->v >= 3){
				printf("NOT EMPTY\n");
			}

			if (backtrack(csp)){
				stop_csp(csp);
				revert_MAC_light(csp,vars);
				return 1;
			}
		}
		remove_from_partial_instance(csp,x);
		revert_MAC(csp,vars);
		i--;
	}
	reverse_non_instanciated(csp,x);

	return 0;
}

int run_backtrack(Pcsp csp){
	start_time(csp);
	backtrack(csp);
	stop_time(csp);
	return 1;
}
