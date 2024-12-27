// #include <string.h>
// #include <stddef.h>
// #include <stdio.h>

// #include "graph.h"
// #include "graph.c"

// void print_graph(graph_t *g) {
//     assert(g != NULL);
//     fprintf(stderr, "Graph has %d edges and %d edges are allocated\
//     n", g->num_edges, g->capacity);
//     edge_t *e = g->edges;
//     for (int i = 0; i < g->num_edges; ++i, e++) {
//         printf("%d %d %d\n", e->from, e->to, e->cost);
//     }
// }

// int main(int argc, char *argv[]) {
//     int ret = 0;
//     int print = 0;
//     char *fname;
//     int c = 1;

//     if (argc > 2 && strcmp(argv[c], "-p") == 0) {
//         print = 1;
//         c += 1;
//     }

//     fname = argc > 1 ? argv[c] : NULL;
//     fprintf(stderr, "Load file ’%s’\n", fname);

//     graph_t *graph = allocate_graph();
//     int e = load_graph(fname, graph);
    
//     fprintf(stderr, "Load %d edges\n", e);
    
//     if (print) {
//         print_graph(graph);
//     }
    
//     free_graph(&graph);
//     return ret;
// } 

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void print_graph(const graph_t *graph) {
    // Print the graph's edges
    printf("Graph contains %ld edges:\n", graph->num_of_edges);
    for (int i = 0; i < graph->num_of_edges; i++) {
        printf("Edge %d: From vertex %d to vertex %d, Price: %d\n", 
               i + 1, graph->edges[i].from_vertex, graph->edges[i].to_vertex, graph->edges[i].price);
    }
}

int main() {
    // Allocate a new graph
    graph_t *graph = allocate_graph();

    // Load graph from text file
    printf("Loading graph from text file...\n");
    load_txt("graph.txt", graph);
    print_graph(graph);
    save_txt(graph, "txt_out_txt.txt");
    save_bin(graph, "txt_out_bin.txt");

    // Save graph to binary file
    printf("Saving graph to binary file...\n");

    // Free the graph's memory
    free_graph(&graph);

    // Allocate a new graph for testing binary loading
    graph = allocate_graph();

    // Load graph from binary file
    printf("Loading graph from binary file...\n");
    // load_txt("graph.txt", graph);
    load_bin("txt_out_bin.txt", graph);
    printf("hahah Graph contains %ld edges:\n", graph->num_of_edges);
    print_graph(graph);

    // Save graph to text file
    printf("Saving graph to text file...\n");
    save_bin(graph, "bin_out_bin.txt");
    save_txt(graph, "bin_out_txt.txt");

    // Free the graph's memory
    free_graph(&graph);

    return 0;
}