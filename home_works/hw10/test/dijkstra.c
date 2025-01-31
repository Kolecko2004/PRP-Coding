#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "dijkstra.h"
#include "graph.h"
#include "graph_utils.h"
#include "my_malloc.h"
#include "pq_heap.h"
#include "load_simple.h"

typedef struct {
   int edge_start;
   int edge_count;
   int parent;
   int cost;
} node_t;

typedef struct {
   graph_t *graph;
   node_t *nodes;
   int num_nodes;
   int start_node;
} dijkstra_t;

// - function ----------------------------------------------------------------
void* dijkstra_init(void)
{
   dijkstra_t *dij = myMalloc(sizeof(dijkstra_t));
   dij->nodes = NULL;
   dij->num_nodes = 0;
   dij->start_node = -1;
   dij->graph = allocate_graph();

   if (!dij->graph) {
      free(dij); 
      dij = NULL;
   }

   return dij;
}

// - function ----------------------------------------------------------------
_Bool dijkstra_load_graph(const char *filename, void *dijkstra)
{
   _Bool ret = false;
   dijkstra_t *dij = (dijkstra_t*)dijkstra;

   if (
        dij && dij->graph &&
        load_graph_simple(filename, dij->graph)
      ) {
      int m = -1;

      for (int i = 0; i < dij->graph->num_edges; ++i) {
         const edge_t *const e = &(dij->graph->edges[i]);
         m = m < e->from ? e->from : m;
         m = m < e->to ? e->to : m;
      }

      m += 1;
      dij->nodes = myMalloc(sizeof(node_t) * m);
      dij->num_nodes = m;

      for (int i = 0; i < m; ++i) {
         dij->nodes[i].edge_start = -1;
         dij->nodes[i].edge_count = 0;
         dij->nodes[i].parent = -1;
         dij->nodes[i].cost = -1;
      }

      for (int i = 0; i < dij->graph->num_edges; ++i) {
         int cur = dij->graph->edges[i].from;
         if (dij->nodes[cur].edge_start == -1) {
            dij->nodes[cur].edge_start = i;
         }
         dij->nodes[cur].edge_count += 1;
      }

      ret = true;
   }
   return ret;
}

// - function ----------------------------------------------------------------
_Bool dijkstra_solve(void *dijkstra, int label) 
{
    dijkstra_t *dij = (dijkstra_t*)dijkstra;

    if (!dij || label < 0 || label >= dij->num_nodes) {
        return false;
    }

    dij->start_node = label;

    node_t *nodes = dij->nodes;
    edge_t *edges = dij->graph->edges;
    
    void *pq = pq_alloc(dij->num_nodes);
    if (!pq) return false;

    nodes[label].cost = 0;
    if (!pq_push(pq, label, 0)) {
        pq_free(pq);
        return false;
    }

    int cur_label, edge_index, to_label, new_cost;
    node_t *cur_node, *to_node;
    edge_t *edge;

    while (!pq_is_empty(pq) && pq_pop(pq, &cur_label)) {
        cur_node = &nodes[cur_label];
        edge_index = cur_node->edge_start + cur_node->edge_count;
        
        for (int i = cur_node->edge_start; i < edge_index; i++) {
            edge = &edges[i];
            to_label = edge->to;
            to_node = &nodes[to_label];
            new_cost = cur_node->cost + edge->cost;

            if (to_node->cost == -1) {
                to_node->cost = new_cost;
                to_node->parent = cur_label;

                if (!pq_push(pq, to_label, new_cost)) {
                    pq_free(pq);
                    return false;
                }
            } 
            
            else if (new_cost < to_node->cost) {
                to_node->cost = new_cost;
                to_node->parent = cur_label;

                if (!pq_update(pq, to_label, new_cost)) {
                    pq_free(pq);
                    return false;
                }
            }
        }
    }
    pq_free(pq);

    return true;
}

// - function ----------------------------------------------------------------
_Bool dijkstra_save_path(const void *dijkstra, const char *filename)
{
    _Bool ret = false;
    const dijkstra_t *const dij = (dijkstra_t*)dijkstra;

    if (dij) {
        FILE *f = fopen(filename, "w");

        if (f) {
            for (int i = 0; i <dij->num_nodes; ++i) {
                const node_t *const node = &(dij->nodes[i]);
                fprintf(f, "%i %i %i\n", i, node->cost, node->parent);
            }
            ret = fclose(f) == 0;
        }
    }
    return ret;
}

// - function ----------------------------------------------------------------
void dijkstra_free(void *dijkstra)
{
    dijkstra_t *dij = (dijkstra_t*)dijkstra;

    if (dij) {
        if (dij->graph) {
            free_graph(&(dij->graph));
        }
        
        if (dij->nodes) {
            free(dij->nodes);
        }
        free(dij);
    }
}

_Bool dijkstra_set_graph(int e, int edges[][3], void *dijkstra)
{
    _Bool ret = false;
    dijkstra_t *dij = (dijkstra_t*)dijkstra;
    
    if (dij && dij->graph && e > 0) {
        while (dij->graph->capacity < e) {
            if (!enlarge_graph(dij->graph)) {
                return false;
            }
        }
        
        for (int i = 0; i < e; i++) {
            dij->graph->edges[i].from = edges[i][0];
            dij->graph->edges[i].to = edges[i][1];
            dij->graph->edges[i].cost = edges[i][2];
        }

        dij->graph->num_edges = e;
        int m = -1;

        for (int i = 0; i < e; i++) {
            m = m < edges[i][0] ? edges[i][0] : m;
            m = m < edges[i][1] ? edges[i][1] : m;
        }

        m += 1;
        dij->nodes = myMalloc(sizeof(node_t) * m);

        if (!dij->nodes) {
            return false;
        }

        dij->num_nodes = m;
        
        for (int i = 0; i < m; i++) {
            dij->nodes[i].edge_start = -1;
            dij->nodes[i].edge_count = 0;
            dij->nodes[i].parent = -1;
            dij->nodes[i].cost = -1;
        }
        
        for (int i = 0; i < e; i++) {
            int cur = dij->graph->edges[i].from;
            if (dij->nodes[cur].edge_start == -1) {
                dij->nodes[cur].edge_start = i;
            }
            dij->nodes[cur].edge_count++;
        }
        
        ret = true;
    }
    return ret;
}

_Bool dijkstra_get_solution(const void *dijkstra, int n, int solution[][3])
{
    _Bool ret = false;
    const dijkstra_t *const dij = (dijkstra_t*)dijkstra;
    
    if (dij && dij->nodes && n > 0 && n <= dij->num_nodes) {
        for (int i = 0; i < n; i++) {
            solution[i][0] = i;
            solution[i][1] = dij->nodes[i].cost;
            solution[i][2] = dij->nodes[i].parent;
        }
        ret = true;
    }
    return ret;
}
