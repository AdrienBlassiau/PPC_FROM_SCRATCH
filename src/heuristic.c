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
#include "stack.h"
#include "instance.h"
#include "constraint.h"
#include "heuristic.h"

void set_var_heuristic(Pinstance inst, int heuri){
	switch (heuri){
	case 1:
		inst->var_heuri = LEX;
		break;
	case 2:
		inst->var_heuri = INVLEX;
		break;
	case 3:
		inst->var_heuri = RANDOM;
		break;
	case 4:
		inst->var_heuri = DOM_SIZE;
		break;
	case 5:
		inst->var_heuri = DEGREE;
		break;
	case 6:
		inst->var_heuri = DYNAMIC_DEGREE;
		break;
	case 7:
		inst->var_heuri = WHEIGHTED_DEGREE;
		break;
	case 8:
		inst->var_heuri = DOM_DEG;
		break;
	case 9:
		inst->var_heuri = DOM_DDEG;
		break;
	case 10:
		inst->var_heuri = DOM_WDEG;
		break;
		default:
		inst->var_heuri = LEX;
	}
}

int select_variable(Pinstance inst, int* domain_size, int max_dom_size, int* degree_tab, Pconstraint cons, int** failure_tab){
	int heuri = inst->var_heuri;

	switch (heuri){
	case LEX:
		return pop_first_var(inst);
	case INVLEX:
		return pop_last_var(inst);
	case RANDOM:
		return pop_random_var(inst);
	case DOM_SIZE:
		return pop_min_dom_var(inst, domain_size, max_dom_size);
	case DEGREE:
		return pop_max_degree_var(inst, degree_tab);
	case DYNAMIC_DEGREE:
		return pop_max_dynamic_degree_var(inst, cons);
		break;
	case WHEIGHTED_DEGREE:
		return pop_max_weighted_degree_var(inst, cons, failure_tab);
		break;
	case DOM_DEG:
		return pop_min_dom_degree_var(inst, degree_tab, domain_size, max_dom_size);
		break;
	case DOM_DDEG:
		return pop_min_dom_dynamic_degree_var(inst, cons, domain_size, max_dom_size);
		break;
	case DOM_WDEG:
		return pop_min_dom_weighted_degree_var(inst, cons, failure_tab, domain_size, max_dom_size);
		break;
		default:
		return pop_first_var(inst);
	}
}

int pop_first_var(Pinstance inst){
	int i;
	int size = inst->size;

	for (i = 0; i < size; i++){
		if (is_free(inst,i)){
			return i;
		}
	}

	return -1;
}

int pop_last_var(Pinstance inst){
	int i;
	int size = inst->size;

	for (i = size-1; i >= 0; i--){
		if (is_free(inst,i)){
			return i;
		}
	}

	return -1;
}

int pop_random_var(Pinstance inst){
	int i;
	int size = inst->size;
	int number_of_free = get_number_of_free(inst);
	int random_free = rand_int(number_of_free-1);
	int free_count = 0;
	for (i = 0; i < size; i++){
		if (is_free(inst,i)){
			if (free_count == random_free){
				return i;
			}
			free_count++;
		}
	}

	return -1;
}

int pop_min_dom_var(Pinstance inst, int* domain_size, int max_dom_size){
	int i;
	int size = inst->size;
	int min = max_dom_size;
	int min_var = 0;

	for (i = 0; i < size; i++){
		if (is_free(inst,i)){
			if (domain_size[i] <= min){
				min = domain_size[i];
				min_var = i;
			}
		}
	}

	return min_var;
}

int pop_max_degree_var(Pinstance inst, int* degree_tab){
	int i;
	int size = inst->size;
	int max = 0;
	int max_var = 0;

	for (i = 0; i < size; i++){
		if (is_free(inst,i)){
			if (degree_tab[i] >= max){
				max = degree_tab[i];
				max_var = i;
			}
		}
	}

	return max_var;
}

int pop_max_dynamic_degree_var(Pinstance inst, Pconstraint cons){
	int i,j,deg;
	int size = inst->size;
	int max = 0;
	int max_var = 0;

	for (i = 0; i < size; i++){
		if (is_free(inst,i)){
			deg = 0;
			for (j = 0; j < size; j++){
				if (is_free(inst,j) && test_contraint_exists(cons,i,j)){
					deg ++;
				}
			}

			if (deg >= max){
				max = deg;
				max_var = i;
			}
		}
	}

	return max_var;
}

int pop_max_weighted_degree_var(Pinstance inst, Pconstraint cons, int** failure_tab){
	int i,j,deg;
	int size = inst->size;
	int max = 0;
	int max_var = 0;

	for (i = 0; i < size; i++){
		if (is_free(inst,i)){
			deg = 0;
			for (j = 0; j < size; j++){
				if (is_free(inst,j) && test_contraint_exists(cons,i,j)){
					deg += failure_tab[i][j];
				}
			}

			if (deg >= max){
				max = deg;
				max_var = i;
			}
		}
	}

	return max_var;
}

int pop_min_dom_degree_var(Pinstance inst, int* degree_tab, int* domain_size, int max_dom_size){
	int i;
	int size = inst->size;
	int min = max_dom_size;
	int min_var = 0;
	int ratio;
	for (i = 0; i < size; i++){
		if (is_free(inst,i)){
			ratio = degree_tab[i]==0?max_dom_size:domain_size[i]/degree_tab[i];
			if (ratio <= min){
				min = ratio;
				min_var = i;
			}
		}
	}

	return min_var;
}


int pop_min_dom_dynamic_degree_var(Pinstance inst, Pconstraint cons, int* domain_size, int max_dom_size){
	int i,j,deg;
	int size = inst->size;
	int min = max_dom_size;
	int min_var = 0;
	int ratio;

	for (i = 0; i < size; i++){
		if (is_free(inst,i)){
			deg = 0;
			for (j = 0; j < size; j++){
				if (is_free(inst,j) && test_contraint_exists(cons,i,j)){
					deg ++;
				}
			}
			ratio = deg==0?max_dom_size:domain_size[i]/deg;
			if (ratio <= min){
				min = ratio;
				min_var = i;
			}
		}
	}

	return min_var;
}


int pop_min_dom_weighted_degree_var(Pinstance inst, Pconstraint cons, int** failure_tab, int* domain_size, int max_dom_size){
	int i,j,deg;
	int size = inst->size;
	int min = max_dom_size;
	int min_var = 0;
	int ratio;

	for (i = 0; i < size; i++){
		if (is_free(inst,i)){
			deg = 0;
			for (j = 0; j < size; j++){
				if (is_free(inst,j) && test_contraint_exists(cons,i,j)){
					deg += failure_tab[i][j];
				}
			}
			ratio = deg==0?max_dom_size:domain_size[i]/deg;

			if (ratio <= min){
				min = ratio;
				min_var = i;
			}
		}
	}

	return min_var;

}

char* get_var_heuristic(Pinstance inst){
	char* heuristic_name;
	int heuri = inst->var_heuri;

	switch (heuri){
	case LEX:
		heuristic_name = "LEX";
		return heuristic_name;
	case INVLEX:
		heuristic_name = "INVLEX";
		return heuristic_name;
	case RANDOM:
		heuristic_name = "RANDOM";
		return heuristic_name;
	case DOM_SIZE:
		heuristic_name = "MIN DOM_SIZE";
		return heuristic_name;
	case DEGREE:
		heuristic_name = "MAX DEGREE";
		return heuristic_name;
	case DYNAMIC_DEGREE:
		heuristic_name = "MAX DYNAMIC_DEGREE";
		return heuristic_name;
	case WHEIGHTED_DEGREE:
		heuristic_name = "MAX WHEIGHTED_DEGREE";
		return heuristic_name;
	case DOM_DEG:
		heuristic_name = "MIN DOM/DEGREE";
		return heuristic_name;
	case DOM_DDEG:
		heuristic_name = "MIN DOM/DYNAMIC_DEGREE";
		return heuristic_name;
	case DOM_WDEG:
		heuristic_name = "MIN DOM/WHEIGHTED_DEGREE";
		return heuristic_name;
		default:
		heuristic_name = "LEX";
		return heuristic_name;
	}
}

void set_val_heuristic(Pinstance inst, int heuri){
	switch (heuri){
	case 1:
		inst->val_heuri = MIN_VAL;
		break;
	case 2:
		inst->val_heuri = MAX_VAL;
		break;
	case 3:
		inst->val_heuri = RANDOM_VAL;
		break;
	case 4:
		inst->val_heuri = SUPPORTED;
		break;
	case 5:
		inst->val_heuri = DYNAMIC_SUPPPORTED;
		break;
	default:
		inst->val_heuri = MIN_VAL;
	}
}

int comp_success (const void * elem1, const void * elem2){
	int* tab1 = *(int**)elem1;
	int* tab2 = *(int**)elem2;

	if (tab1[2] < tab2[2]) return  1;
	if (tab1[2] > tab2[2]) return -1;
	return 0;
}

int comp_dec (const void * elem1, const void * elem2){
	int* tab1 = *(int**)elem1;
	int* tab2 = *(int**)elem2;

	if (tab1[1] < tab2[1]) return  1;
	if (tab1[1] > tab2[1]) return -1;
	return 0;
}

int comp_inc(const void * elem1, const void * elem2){
	int* tab1 = *(int**)elem1;
	int* tab2 = *(int**)elem2;

	if (tab1[1] > tab2[1]) return  1;
	if (tab1[1] < tab2[1]) return -1;
	return 0;
}

int comp_random(){
	int random1 = rand_int(2)-1;
	int random2 = rand_int(2)-1;

	if (random1 > random2) return  1;
	if (random2 < random1) return -1;

	return 0;
}

int supported_number(Pinstance inst, Pconstraint cons, int var, int val, int dynamic){
	int i;
	int support = 0;
	int size = cons->size;

	for (i = 0; i < size; i++){
		if (dynamic){
			if (is_free(inst,i)){
				support+=test_contraint_value_exists(cons,var,i,val);
			}
		}
		else{
			support+=test_contraint_value_exists(cons,var,i,val);
		}

	}

	return support;

}

void shuffle_domain(Pinstance inst, Pdomain d, Pconstraint cons, int var){
	int i;
	Pset set = get_domain_values(d);
	int** values = set->values;
	int size = set->total_size;
	int heuri = inst->val_heuri;

	switch (heuri){
		case MIN_VAL:
			qsort(values,size,sizeof(values[0]),comp_inc);
			break;
		case MAX_VAL:
			qsort(values,size,sizeof(values[0]),comp_dec);
			break;
		case RANDOM_VAL:
			qsort(values,size,sizeof(values[0]),comp_random);
			break;
		case SUPPORTED:
			for (i = 0 ; i < size ; i++){
				values[i][2] = supported_number(inst, cons, var, values[i][1], 0);
			}
			qsort(values,size,sizeof(values[0]),comp_success);
			break;
		case DYNAMIC_SUPPPORTED:
			for (i = 0 ; i < size ; i++){
				values[i][2] = supported_number(inst, cons, var, values[i][1], 1);
			}
			qsort(values,size,sizeof(values[0]),comp_success);
			break;
		default:
			qsort(values,size,sizeof(values[0]),comp_inc);
			break;
	}

	return;
}

char* get_val_heuristic(Pinstance inst){
	char* heuristic_name;
	int heuri = inst->val_heuri;

	switch (heuri){
		case MIN_VAL:
			heuristic_name = "MIN_VAL";
			return heuristic_name;
		case MAX_VAL:
			heuristic_name = "MAX_VAL";
			return heuristic_name;
		case RANDOM_VAL:
			heuristic_name = "RANDOM_VAL";
			return heuristic_name;
		case SUPPORTED:
			heuristic_name = "MAX SUPPORTED";
			return heuristic_name;
		case DYNAMIC_SUPPPORTED:
			heuristic_name = "MAX DYNAMIC_SUPPPORTED";
			return heuristic_name;
		default:
			heuristic_name = "MIN_VAL";
			return heuristic_name;
	}
}