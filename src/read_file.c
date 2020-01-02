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
#include "csv.h"

char** get_line_tab(int* pos, int* line_size, const char* file){
	int i,k;
    int element_number = 0;
    int max_var_size;
    int line_pos = *pos;

    /* FIRST : We count the number of elementes of the line */
    i=0;
    while(file[*pos] != '\n') {
    	if (file[*pos] == ' '){
    		element_number+=1;
    	}
        i++;
        (*pos)++;
    }
    (*pos)++;

    if (i != 0) element_number +=1;
    max_var_size = i-2*(element_number-1);

    /* SECOND : We store each variable */
    char** line_tab = xcalloc(element_number,sizeof(char*));

    k = 0;
    for (i = 0; i < element_number; i++){
    	line_tab[i] = xcalloc(max_var_size+1,sizeof(char));
    	while(file[line_pos] != ' ' && file[line_pos] != '\n') {
    	    line_tab[i][k] = file[line_pos];
    	    line_pos++;
    	    k++;
    	}
    	k = 0;
    	line_pos++;
    }

    *line_size = element_number;
    return line_tab;
}

Pvariable make_var_dom(int* pos, const char* file, char** var_tab, int variable_number, Pvariable v){
	int i,j;
	int line_size=0;
	char** line_tab;
	Pdomain d;
	int str_to_int_res = 0;

    for (i = 0; i < variable_number; i++){
    	d = new_domain();
    	line_tab = get_line_tab(pos,&line_size,file);
    	for (j = 0; j < line_size; j++){
    		str_to_int_res = (int) strtol(line_tab[j], (char **)NULL, 10);
    		insert_in_domain(d, &str_to_int_res);
    	}
    	insert_variable(v,i,var_tab[i],d);
    	free_matrix_string(line_tab,line_size);
    }
    free_matrix_string(var_tab,variable_number);
	return v;
}

int get_constraint_number(int* pos, const char* file){
	int line_size=0;
    char** line_tab;
    int str_to_int_res = 0;

    line_tab = get_line_tab(pos,&line_size,file);

    if (line_size != 1){
    	return -1;
    }

    str_to_int_res = (int) strtol(line_tab[0], (char **)NULL, 10);

    free_matrix_string(line_tab,line_size);
    return str_to_int_res;
}

Pconstraint make_constraint(int* pos, const char* file, int constraint_number, Pconstraint c, Pvariable v, int* tab_int){
	int i,j,k;
	int line_size = 0;
	char ** first_constraint_line;
	char ** current_constraint_line;
	char* constraint1;
	char* constraint2;
	char* number_of_tuples;
	char* tuple1;
	char* tuple2;
	int constraint1_int;
	int constraint2_int;
	int number_of_tuples_int;

	i = 0;
	k = 0;

	while(i < constraint_number) {
		first_constraint_line = get_line_tab(pos,&line_size,file);
		constraint1 = first_constraint_line[0];
		constraint1_int = get_variable_index(v,constraint1);
		constraint2 = first_constraint_line[1];
		constraint2_int = get_variable_index(v,constraint2);
		number_of_tuples = first_constraint_line[2];
		number_of_tuples_int = (int) strtol(number_of_tuples, (char **)NULL, 10);
		free_matrix_string(first_constraint_line,line_size);

		for (j = 0; j < number_of_tuples_int; j++){

			current_constraint_line = get_line_tab(pos,&line_size,file);
			tuple1 = current_constraint_line[0];
			tuple2 = current_constraint_line[1];
			tab_int[k] = (int) strtol(tuple1, (char **)NULL, 10);
			k++;
			tab_int[k] = (int) strtol(tuple2, (char **)NULL, 10);

			insert_constraint_tuple(c,constraint1_int,constraint2_int,&tab_int[k-1],&tab_int[k]);
			k++;
			free_matrix_string(current_constraint_line,line_size);
		}
	    i++;
	}

	return c;
}

Pcsv read_file(char* filename){
  struct stat info;
  int pos = 0;
  int line_size = 0;
  int variable_number = 0;
  int constraint_number = 0;
  char* buf;
  Pcsv csv;
  FILE* fd = fopen(filename,"r");
  char** var_tab;

  if (fd == NULL) {
    fprintf(stderr,"%s: error while opening %s in r mode : %s\n",nameProcessus,filename,strerror(errno));
    return NULL;
  }
  if (fstat(fileno(fd),&info) == -1) {
    fprintf(stderr,"%s: error stat : %s\n",nameProcessus,strerror(errno));
    return NULL;
  }
  buf = xmalloc(info.st_size);
  if (fread(buf,sizeof(char),info.st_size,fd) == 0) {
    fprintf(stderr,"%s: error while reading of %s : %s\n",nameProcessus,filename,strerror(errno));
    return NULL;
  }
  fclose(fd);

  int size = (int)(info.st_size);

  int* tab_int = calloc(size,sizeof(int));

  var_tab = get_line_tab(&pos,&line_size,buf);
  variable_number = line_size;
  Pvariable v = new_variable(variable_number);
  make_var_dom(&pos, buf, var_tab, variable_number, v);

  constraint_number = get_constraint_number(&pos,buf);

  Pconstraint c = new_constraint(variable_number);
  make_constraint(&pos, buf, constraint_number, c, v, tab_int);

  csv = new_csv(v,c,tab_int);

  xfree(buf);

  return csv;
}
