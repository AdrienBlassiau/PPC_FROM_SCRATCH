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
#include "variable.h"
#include "instance.h"
#include "heuristic.h"
#include "constraint.h"
#include "Sstruct.h"
#include "duo.h"
#include "count.h"

Pvariable MAC(Pcsp csp, int var, int val){
	Pvariable v =  csp->variable_list;
	int mac = csp->mac;
	Pvariable v_copy;
	Pdomain d_copy;

	if (mac){
		v_copy = copy_variable(v);
		d_copy = get_variable_domain(v_copy,var);
		remove_all_except_one_from_domain(d_copy,val);
		csp->variable_list = v_copy;
		AC4(csp);
		// printf("AFTER AC4\n");
		// print_variable(v_copy);
		// printf("AFTER AC4\n");
		return v;
	}

	return NULL;
}

void revert_MAC(Pcsp csp, Pvariable v_copy){
	Pvariable v = csp->variable_list;
	int mac = csp->mac;
	if (mac){
		free_variable(v);
		csp->variable_list = v_copy;
		return;
	}
	return;
}

int revert_MAC_light(Pcsp csp, Pvariable v_copy){
	int mac = csp->mac;
	if (mac){
		free_variable(v_copy);
		return 1;
	}
	return 0;
}

int initAC4(Pcsp csp, int* tab_alloc){
	int x,y,a,b,i,j,total;
	int size = get_csp_size(csp);
	Pdomain dx,dy;
	int cc=0;

	for (x = 0; x < size; x++){
		for (y = 0; y < size; y++){
			if(test_constraint(csp,x,y)){
				// printf("#################### CONSTRAINT (%d,%d) EXISTS (####################\n",x,y);

				dx = get_current_variable_domain(csp,x);

				begin_domain_iteration(dx);
				i = get_domain_size(dx);
				while(i>0){
					total = 0;

					a = get_current_value(dx);
					dy = get_current_variable_domain(csp,y);

					// printf("DOMAIN x:%d\n",x);
					// print_domain(dx);

					// printf("DOMAIN y:%d\n",y);
					// print_domain(dy);

					begin_domain_iteration(dy);

					j = get_domain_size(dy);
					while(j>0){
						b = get_current_value(dy);
						// printf("===> CURRENT TUPLE (a,b):(%d,%d)\n",a,b);

						if(test_tuple(csp,x,y,a,b)){
							// printf("%d->%d in C(%d,%d)\n",a,b,x,y);
							total++;
							tab_alloc[cc] = b;
							add_S(csp,x,y,a,&tab_alloc[cc]);
							// printf("Sstruct :\n");
							// print_Sstruct(csp->Sstruct_list);
							// printf("--\n");
							cc++;
						}
						j--;
					}
					tab_alloc[cc] = a;
					tab_alloc[cc+1] = total;
					change_count(csp,x,y,&tab_alloc[cc],&tab_alloc[cc+1]);

					// printf("Count :\n");
					// print_count_light(csp->count_list);

					if (empty_count(csp,x,y,&tab_alloc[cc],0)){
						// printf("IT'S EMPTY !\n");
						remove_of_domain(csp,x,tab_alloc[cc]);
						add_Q(csp,x,tab_alloc[cc]);
					}
					cc=cc+2;
					i--;
				}
			}
		}
	}
	return 1;
}

int AC4(Pcsp csp){
	int x,y,a,b,count;
	Pduostack S;
	int* tab_alloc = calloc(100000000,sizeof(int));

	initAC4(csp,tab_alloc);

	while(!Q_is_empty(csp)){
		remove_Q(csp,&y,&b);
		// printf("y:%d et b:%d\n",y,b);

		S = get_S(csp,y,&b);
		while(!S_is_empty(S)){
			get_S_tuple(S,&x,&a);
			// printf("x:%d et a:%d\n",x,a);
			S = S->next;
			// printf("AVANT\n");
			// print_count_light(csp->count_list);
			count = decrement_count(csp,x,y,&a);
			// print_count_light(csp->count_list);
			// printf("APRES\n");
			if (!count && in_domain(csp,x,a)){
				remove_of_domain(csp,x,a);
				add_Q(csp,x,a);
			}

		}
	}
	reset_csp_count(csp);
	reset_csp_S(csp);
	reset_csp_Q(csp);
	free(tab_alloc);
	return 1;
}

int run_AC4(Pcsp csp){
	start_time(csp);
	AC4(csp);
	stop_time(csp);
	return 1;
}