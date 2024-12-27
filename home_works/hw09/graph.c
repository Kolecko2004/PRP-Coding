#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "graph.h"

#ifndef INIT_SIZE
#define INIT_SIZE 10
#endif

/* This is a testing file just to be able to compile the 
 * examples of binary files to convert graph from txt->bin
 * and bin -> txt
 */

// - function -----------------------------------------------------------------
graph_t* allocate_graph() 
{
   fprintf(stdout, "make it alloc\n");

   graph_t *graph = (graph_t*) malloc(sizeof(graph_t));
   if (graph == NULL) {
      fprintf(stderr, "Malloc failed\n");
      exit(-1);
   }

   graph->num_of_edges = 0;
   graph->capacity = 0;
   graph->edges = NULL;

   return graph;
}

// - function -----------------------------------------------------------------
void free_graph(graph_t **graph)
{
   assert(graph != NULL && *graph != NULL);

   if ((*graph)->capacity > 0) {
      free((*graph)->edges);
   }

   free(*graph);
   *graph = NULL;
}

graph_t* enlarge_graph(graph_t *graph)
{
   assert(graph != NULL);
   int new_capacity = graph->capacity == 0? INIT_SIZE : graph->capacity * 2;
   edge_t *new_edges = (edge_t*) malloc(new_capacity * sizeof(edge_t));
   if (new_edges == NULL) {
      fprintf(stderr, "Malloc failed\n");
      exit(-1);
   }

   if (graph->edges != NULL) {
      memcpy(new_edges, graph->edges, graph->num_of_edges * sizeof(edge_t));
      free(graph->edges);
   }
   
   graph->edges = new_edges;
   graph->capacity = new_capacity;
   return graph;
}

// - function -----------------------------------------------------------------
void load_txt(const char *fname, graph_t *graph)
{
   int num_of_loaded_edges = 0;
   FILE *file = fopen(fname, "r");

   if (file == NULL) {
      fprintf(stderr, "Failed to open file: %s\n", fname);
      exit(-1);
   }

   while (1) {
      if (graph->capacity == graph->num_of_edges) {
         enlarge_graph(graph);
         fprintf(stdout, "make it bigger\n");
      }

      edge_t * edge = graph->edges + graph->num_of_edges;
      
      while (graph->num_of_edges < graph->capacity) {
         int scan_result = fscanf(file, "%d %d %d\n", &(edge->from_vertex), &(edge->to_vertex), &(edge->price));
         fprintf(stdout, "make it %d\n", scan_result);
         if (scan_result == 3) {
            fprintf(stdout, "make it haha\n");
            graph->num_of_edges += 1;
            num_of_loaded_edges += 1;
            fprintf(stdout, "%d %d %d\n", edge->from_vertex, edge->to_vertex, edge->price);
            edge += 1;
         }
         else if (feof(file)) {
            fprintf(stdout, "End of file reached.\n");
            return;
         }
         else {
            break;
         }
      }
   } 

   fclose(file);
}

void load_bin(const char *fname, graph_t *graph) {
   FILE *file = fopen(fname, "rb");

   if (file == NULL) {
      fprintf(stderr, "Failed to open file %s\n", fname);
      exit(-1);
   }

   unsigned char buffer[12];
   while (fread(buffer, 1, 12, file) == 12) {
      if (graph->capacity == graph->num_of_edges) {
         enlarge_graph(graph);
      }
        
      edge_t * edge = graph->edges + graph->num_of_edges++;
      
      edge->from_vertex = (unsigned int)(buffer[0]) |
         (unsigned int)(buffer[1] << 8) |
         (unsigned int)(buffer[2] << 16) |
         (unsigned int)(buffer[3] << 24);
      
      edge->to_vertex = (unsigned int)(buffer[4]) |
         (unsigned int)(buffer[5] << 8) |
         (unsigned int)(buffer[6] << 16) |
         (unsigned int)(buffer[7] << 24);
      
      edge->price = (unsigned int)(buffer[8]) |
         (unsigned int)(buffer[9] << 8) |
         (unsigned int)(buffer[10] << 16) |
         (unsigned int)(buffer[11] << 24);
   }

   fclose(file);
}

// - function -----------------------------------------------------------------
void save_txt(const graph_t * const graph, const char *fname) {
   FILE *file = fopen(fname, "w");
   if (file == NULL) {
      fprintf(stderr, "Failed to open file %s\n", fname);
      exit(-1);
   }

   edge_t *edge = graph->edges;
   for (int i = 0; i < graph->num_of_edges; i++, edge++) {
      fprintf(file, "%d %d %d\n", edge->from_vertex, edge->to_vertex, edge->price);
   }

   fclose(file);
}

// - function -----------------------------------------------------------------
void save_bin(const graph_t * const graph, const char *fname) {
   FILE *file = fopen(fname, "wb");
   if (file == NULL) {
      fprintf(stderr, "Failed to open file %s\n", fname);
      exit(-1);
   }

   fwrite(graph->edges, sizeof(edge_t), graph->num_of_edges, file);

   fclose(file);
}
