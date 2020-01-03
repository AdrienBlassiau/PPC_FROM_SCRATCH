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
#include "Sstruct.h"
#include "avl.h"
#include "duo.h"
#include "compare_int.h"

PSstruct new_Sstruct(int size){
	int i;
	PAVLTree new_avl;
	PSstruct Ss = (PSstruct)malloc(sizeof(Sstruct));

	PAVLTree* duo_tree = calloc(size,sizeof(PAVLTree));

	for (i = 0; i < size; i++){
		new_avl = avl_tree_new((AVLTreeCompareFunc) int_compare);
		duo_tree[i] = new_avl;
	}

	Ss->duo_tree = duo_tree;
	Ss->size = size;

	return Ss;
}

PSstruct free_Sstruct(PSstruct Ss){
	int size = Ss->size;
	int i;
	for (i = 0; i < size; i++){
		if (Ss->duo_tree[i]!=NULL){
			avl_tree_free_and_node(Ss->duo_tree[i],free_duostack);
		}
	}
	free(Ss->duo_tree);
	free(Ss);

	return Ss;
}

void print_Sstruct(PSstruct Ss){
	int size = Ss->size;
	int i;
	for (i = 0; i < size; i++){
		printf("%d->\n",i);
		if (Ss->duo_tree[i]!=NULL){
			print_avl_tree(Ss->duo_tree[i],print_duostack,print_int);
		}
	}
}

int insert_SStruct_duo(PSstruct Ss, int var, int* key, int var1, int val1){
	Pduostack dst = query_SStruct(Ss,var,key);
	if (dst==NULL){
		Pduostack pds = new_duostack();
		avl_tree_insert(Ss->duo_tree[var],key,pds);
	}

	Pduo duo = new_duo(var1,val1);
	dst = avl_tree_lookup(Ss->duo_tree[var],key);
	dst = push_duostack(dst,duo);
	avl_tree_change_value(Ss->duo_tree[var],key,dst);
	return 1;
}

Pduostack query_SStruct(PSstruct Ss, int var, int* key){
	PAVLTree* duo_tree =  Ss->duo_tree;
	PAVLTree duo_tree_element = duo_tree[var];

	Pduostack dst =  avl_tree_lookup(duo_tree_element,key);
	return dst;
}