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
#include "read_file.h"

void full_converter(int* pos, const char* file, FILE* fp, int domain_size){
  char** line_tab;
  int line_size=0;
  int i,j,k;
  int variable_number_int;
  int constraint_number_int;
  char int_buffer[256];

  while(file[*pos] != 'p') {
    while(file[*pos] != '\n') {
      (*pos)++;
    }
    (*pos)++;
  }

  line_tab = get_line_tab(pos,&line_size,file);
  variable_number_int = (int) strtol(line_tab[2], (char **)NULL, 10);
  constraint_number_int = (int) strtol(line_tab[3], (char **)NULL, 10);

  free_matrix_string(line_tab,line_size);

  /* FIRST we write the variables name */
  for (i = 1; i < variable_number_int; i++){
    sprintf(int_buffer, "%d", i);
    fputs(int_buffer, fp);
    fputs(" ", fp);
  }
  sprintf(int_buffer, "%d", i);
  fputs(int_buffer, fp);
  fputs("\n", fp);

  /* SECOND we write the domain */
  for (i = 0; i < variable_number_int; i++){
    for (j = 1; j < domain_size; j++){
      sprintf(int_buffer, "%d", j);
      fputs(int_buffer, fp);
      fputs(" ", fp);
    }
    sprintf(int_buffer, "%d", j);
    fputs(int_buffer, fp);
    fputs("\n", fp);
  }

  /* THIRD we write the number of constraint (=number of edges) */
  sprintf(int_buffer, "%d", constraint_number_int);
  fputs(int_buffer, fp);
  fputs("\n", fp);

  /* FOURTH we wrote the constraint !*/
  int tuple_number = domain_size*(domain_size-1);

  for (i = 0; i < constraint_number_int; i++){
    line_tab = get_line_tab(pos,&line_size,file);
    fprintf(fp, "%s %s %d",line_tab[1],line_tab[2],tuple_number);
    fputs("\n", fp);
    for (j = 1; j <= domain_size; j++){
      for (k = 1; k <= domain_size; k++){
        if (j!=k){
          fprintf(fp, "%d %d",j,k);
          fputs("\n", fp);
        }
      }
    }
    // fprintf(fp, "%s %s %d",line_tab[2],line_tab[1],tuple_number);
    // fputs("\n", fp);
    // for (j = 1; j <= domain_size; j++){
    //   for (k = 1; k <= domain_size; k++){
    //     if (j!=k){
    //       fprintf(fp, "%d %d",j,k);
    //       fputs("\n", fp);
    //     }
    //   }
    // }

    free_matrix_string(line_tab,line_size);
  }

  return ;
}


int main(int argc, char const *argv[]){

  char filename1[256];
  char filename2[256];

  if ( argc > 5 || argc < 4)
  {
    printf("Usage: %s infile outfile dom_size\n",argv[0]);
    return 0;
  }

  if (argc == 4){
    sprintf(filename1, "%s", argv[1]);
    sprintf(filename2, "%s", argv[2]);
  }


  int color_number = (int) strtol(argv[3], (char **)NULL, 10);

  struct stat info;
  int pos = 0;
  char* buf;
  FILE* Fcol = fopen(filename1,"r");

  if (Fcol == NULL) {
    fprintf(stderr,"%s: error while opening %s in r mode : %s\n",nameProcessus,filename1,strerror(errno));
    return 0;
  }
  if (fstat(fileno(Fcol),&info) == -1) {
    fprintf(stderr,"%s: error stat : %s\n",nameProcessus,strerror(errno));
    return 0;
  }
  buf = xmalloc(info.st_size);
  if (fread(buf,sizeof(char),info.st_size,Fcol) == 0) {
    fprintf(stderr,"%s: error while reading of %s : %s\n",nameProcessus,filename1,strerror(errno));
    return 0;
  }
  fclose(Fcol);

  FILE * Fcspi;
  Fcspi = fopen(filename2,"w+");

  full_converter(&pos,buf,Fcspi,color_number);

  xfree(buf);
  fclose (Fcspi);

  return 1;
}