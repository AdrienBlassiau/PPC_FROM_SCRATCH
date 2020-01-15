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
#include "params.h"
#include "csp.h"
#include "ac4.h"
#include "backtrack.h"
#include "forward_checking.h"
#include "read_file.h"
#include "problem.h"

#define F 		NULL
#define Q 		5
#define AC 		0
#define FC 		0
#define TO 		-1
#define HVAR 	1
#define HVAL 	1
#define V 		1

void exitfunc(){
	fprintf(stderr,"End after time out.\n");
	_exit(1);
}

int print_help_file(char* filename){
	FILE *fp;
	char str[1000];

	fp = fopen(filename, "r");
	if (fp == NULL){
		fprintf(stderr,"%s: erreur lors de l'ouverture de %s en mode r : %s\n",nameProcessus,filename,strerror(errno));
		return 0;
	}
	while (fgets(str, 1000, fp) != NULL)
		printf("%s", str);
	fclose(fp);
	return 1;
}

int read_flag(int* i, int type, char* string_to_print, char* flag, char* argv[], void* vparam, int argc){
	char *buf;

	if (strcmp(argv[*i], flag) == 0){
		if (*i + 1 != argc){
			if (type == 0){
				int* param = (int*)vparam;
				buf = argv[*i+1];
				*param = (int) strtol(buf, NULL, 10);
			}
			else if(type==1){
				double* param = (double*)vparam;
				buf = argv[*i+1];
				*param = (double) strtod(buf, NULL);
			}
			else{
				char** param = (char**)vparam;
				*param = argv[*i+1];
			}
		}
		else{
			fprintf(stderr,"%s de %s %s manquant (--help pour plus d'informations)\n",string_to_print,flag,string_to_print);
			return 0;
		}
		(*i)++;
	}
	return 1;
}

int solve_csp(Pcsp* csp){
	if (*csp != NULL){

		signal(SIGALRM, exitfunc);

		if ((*csp)->to > 0.){
			if ((*csp)->to <= 1.){
				alarm(1);
			}
			else{
				alarm((*csp)->to);
			}
		}

		int ac = (*csp)->ac;
		int fc = (*csp)->fc;
		if (ac > 0){
			run_AC4(*csp);
		}
		if (fc){
			run_forward_checking(*csp);
		}
		else{
			run_backtrack(*csp);
		}
		return !(*csp)->solution;
	}

	return 1;

}

int show_csp(Pcsp* csp){
	if (*csp != NULL){
		print_csp(*csp);
		return 1;
	}
	return 0;
}

int clean_csp(Pcsp* csp){
	if (*csp != NULL){
		free_csp(*csp);
		return 1;
	}
	return 0;
}

int generate_csp(int argc, char* argv[], Pcsp* csp){
	int i;
	char *f = NULL;
	int q = 5;
	int ac = 0;
	int fc = 0;
	double to = -1;
	int hvar = 1;
	int hval = 1;
	int v = 1;

	for(i=0; i<argc; ++i){

		if (strcmp(argv[i], "--help") == 0){
			print_help_file("doc/help.txt");
			return 1;
		}

		if (strcmp(argv[i], "--format") == 0){
			print_help_file("doc/format.txt");
			return 1;
		}

		if (!read_flag(&i,2,"FILENAME","-f",argv,&f,argc)||
			!read_flag(&i,0,"SIZE","-q",argv,&q,argc)||
			!read_flag(&i,0,"MODE","-ac",argv,&ac,argc)||
			!read_flag(&i,0,"MODE","-fc",argv,&fc,argc)||
			!read_flag(&i,1,"TIME","-to",argv,&to,argc)||
			!read_flag(&i,0,"HEURISTIC_TYPE_1","-hvar",argv,&hvar,argc)||
			!read_flag(&i,0,"HEURISTIC_TYPE_2","-hval",argv,&hval,argc)||
			!read_flag(&i,0,"LEVEL","-v",argv,&v,argc))
		{

			return 1;
		}

	}

	/**********************/
	/* FIRST : GENERATION */
	/**********************/

	if (f != NULL){
		*csp = generate_from_file(f);
		if (*csp == NULL){
			return 0;
		}
	}
	else{
		if (q > 3){
			*csp = generate_8_queens_puzzle(q);
		}
		else{
			*csp = generate_8_queens_puzzle(Q);
		}
	}

	/*****************/
	/* SECOND : MODE */
	/*****************/

	set_csp_ac(*csp,ac);
	set_csp_fc(*csp,fc);
	set_csp_to(*csp,to);

	/***************************************/
	/* THIRD : PARAMETRISATION HEURISTIQUE */
	/***************************************/

	set_csp_hvar(*csp,hvar);
	set_csp_hval(*csp,hval);

	/**********************/
	/* FOURTH : AFFICHAGE */
	/**********************/

	set_csp_v(*csp,v);

	return 0;
}