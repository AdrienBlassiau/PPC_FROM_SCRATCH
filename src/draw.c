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
#include "draw.h"
#include "tools.h"
#include "csp.h"
#include "variable.h"
#include "instance.h"
#include "heuristic.h"
#include "constraint.h"
#include "Sstruct.h"
#include "duo.h"
#include "count.h"
#include "Python.h"

char* alloc_string(){
	return (char*)malloc(100 * sizeof(char));
}

void init_py(){
	Py_Initialize();
	PyRun_SimpleString("import numpy as np");
	PyRun_SimpleString("import networkx as nx");
	// PyRun_SimpleString("from networkx.drawing.nx_agraph import graphviz_layout");
	PyRun_SimpleString("import matplotlib.pyplot as plt");
	PyRun_SimpleString("import random");
	PyRun_SimpleString("plt.ion()");
}

void init_graph(Pcsp csp){
	int x,y,i;
	int size = get_csp_size(csp);

	PyRun_SimpleString("color_tab=[\"#%06x\" % np.random.randint(0, 0xFFFFFF) for i in range(0,100)]");

	PyRun_SimpleString("edge_list=[]");
	PyRun_SimpleString("G = nx.Graph()");

	for (i = 0; i < size; i++){
		char *node_text = alloc_string();
		sprintf(node_text, "G.add_node(%d)",i);
		PyRun_SimpleString(node_text);
		free(node_text);
	}

	for (x = 0; x < size; x++){
		for (y = 0; y < size; y++){
			if(test_constraint(csp,x,y)){
				char *edge_text = alloc_string();
				sprintf(edge_text, "G.add_edge(%d,%d)",x,y);
				PyRun_SimpleString(edge_text);
				free(edge_text);
			}
		}
	}

	// PyRun_SimpleString("pos=graphviz_layout(G)");
	PyRun_SimpleString("pos=nx.circular_layout(G)");
	// PyRun_SimpleString("print(list(G.nodes))");
}

void end_py(){
	Py_Finalize();
}

void draw_graph(Pcsp csp){
	int i;
	double pause = 0.05;
	char *pause_string = alloc_string();
	int size = get_csp_size(csp);

	PyRun_SimpleString("plt.clf()");
	PyRun_SimpleString("color_map=[]");

	for (i = 0; i < size; i++){
		if (is_linked(csp->instance_list,i)){
			char *i_text = alloc_string();
			sprintf(i_text, "color_map.append(color_tab[%d])",get_linked_val(csp->instance_list,i));
			PyRun_SimpleString(i_text);
			free(i_text);
		}
		else{
			PyRun_SimpleString("color_map.append(\'#93a8ac\')");
		}
	}

	PyRun_SimpleString("nx.draw(G,pos=pos,node_color=color_map, with_labels=True)");
	PyRun_SimpleString("plt.show()");

	sprintf(pause_string, "plt.pause(%f)",pause);
	PyRun_SimpleString(pause_string);
	free(pause_string);
}
