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
#include "forward_checking.h"
#include "ac4.h"
#include "variable.h"
#include "instance.h"
#include "heuristic.h"
#include "constraint.h"
#include "Sstruct.h"
#include "duo.h"
#include "count.h"

#if GMODE
	#include "draw.h"
#endif

int check_forward(Pcsp csp, int i, int* tab_alloc, int* cc){
	int j,k,s,m,change;
	int N = get_N(csp);
	int dwo = 0;
	Pdomain dj;

	for (j = 0; j < N; j++){
		if(is_free_variable(csp,j)){
			dwo = 1;

			dj = get_current_variable_domain(csp,j);
			begin_domain_iteration(dj);

			k = get_domain_size(dj);
			while(k>0){
				m = get_current_value(dj);

				if (csp->v >= 3){
					printf("FORWARD : WE CHOOSE : %d OF VALUE : %d\n",j,m);
				}

				if (empty_count(csp,j,j,m,-1)){
					s = get_instanciated_value(csp,i);

					if (test_tuple(csp,i,j,s,m) || !test_constraint(csp,i,j)){

						if (csp->v >= 3){
							printf("%d->%d in C(%d,%d)\n",s,m,i,j);
						}

						dwo = 0;
					}
					else{
						add_failure(csp,i,j);

						if (csp->v >= 3){
							printf("%d->%d NOT in C(%d,%d)\n",s,m,i,j);
						}

						tab_alloc[*cc] = i;
						change = change_count(csp,j,j,m,&tab_alloc[*cc]);
						(*cc) = change ? *cc+1 : *cc;

						if (csp->v >= 3){
							printf("Count :\n");
							print_count_light(csp->count_list);
						}
					}
				}
				k--;
			}
			if (dwo){
				if (csp->v >= 3){
					printf("BAD\n");
				}
				return 0;
			}

		}
	}
	if (csp->v >= 3){
		printf("GOOD\n");
	}
	return 1;
}

void restore(Pcsp csp, int i, int* zero){
	if (csp->v >= 3){
		printf("RESTORE\n");
	}
	int j,k,m;
	int N = get_N(csp);
	Pdomain dj;

	for (j = 0; j < N; j++){
		if(is_free_variable(csp,j)){
			dj = get_current_variable_domain(csp,j);
			begin_domain_iteration(dj);

			k = get_domain_size(dj);
			while(k>0){
				m = get_current_value(dj);

				if (test_count(csp,j,j,m,i)){
					change_count(csp,j,j,m,zero);
				}

				k--;
			}
		}
	}
}

int FC(Pcsp csp, int* tab_alloc, int* cc, int* zero){
	if (csp->v >= 3){
		printf("ENTRYPOINT \n");
		printf("#######\n");
		print_instance(csp->instance_list);
		printf("#######\n");
		printf("C%d\n",*cc);
	}
	int i,j,l;
	Pdomain di;
	Pvariable vars;
	csp->branch_explored++;

	i = choose_non_instanciated(csp);
	di = get_current_variable_domain(csp,i);

	begin_domain_iteration(di);

	j = get_domain_size(di);
	while(j>0){
		l = get_current_value(di);

		if (csp->v >= 3){
			print_domain(di);
			printf("WE CHOOSE : %d OF VALUE : %d\n",i,l);
		}

		vars = MAC(csp,i,l);

		complete_partial_instance(csp,i,l);

#if GMODE
		draw_graph(csp);
#endif

		if (empty_count(csp,i,i,l,-1)){

			if (csp->v >= 3){
				printf("%d OF VALUE : %d VALID\n",i,l);
			}

			if (complete(csp)){

				if (csp->v >= 3){
					printf("END\n");
				}

				stop_csp(csp);
				revert_MAC_light(csp,vars);
				return 1;
			}
			else{

				if (csp->v >= 3){
					printf("FORWARD CHECK\n");
				}

				if (check_forward(csp,i,tab_alloc,cc)){
					if(FC(csp,tab_alloc,cc,zero)){
						revert_MAC_light(csp,vars);
						return 1;
					}
				}
				restore(csp,i,zero);
			}
		}

		if (csp->v >= 3){
			printf("%d OF VALUE : %d NOT VALID BECAUSE C(%d,%d) DOES NOT EXIST\n",i,l,i,empty_count(csp,i,i,l,-1));
		}

		remove_from_partial_instance(csp,i);
		revert_MAC(csp,vars);
		j--;
	}
	reverse_non_instanciated(csp,i);
	return 0;
}


int forward_checking(Pcsp csp){
	int zero=-1;
	int* tab_alloc = calloc(csp->max_dom_size*csp->size,sizeof(int));

	int cc = 0;
	FC(csp,tab_alloc,&cc,&zero);
	reset_csp_count(csp);
	free(tab_alloc);

	return 1;
}

int run_forward_checking(Pcsp csp){
	start_time(csp);
	forward_checking(csp);
	stop_time(csp);
	return 1;
}
