#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

#define WHITE 0
#define YELLOW 1
#define RED 2

typedef int bool;
typedef int WEIGHT_TYPE;

typedef int KEY_TYPE;

typedef struct {
    KEY_TYPE key;
} REGISTRY;

typedef struct temp {
    REGISTRY registry;
    struct temp *next;
} ELEMENT, *NODE;

typedef struct {
    NODE start;
    NODE end;
} QUEUE;

typedef struct ADJACENCY {
    int vertex;
    WEIGHT_TYPE weight;
    struct ADJACENCY *next;
} ADJACENCY;

typedef struct VERTEX {
    ADJACENCY *head;
} VERTEX;

typedef struct GRAPH {
    int vertices_number;
    int edges_number;
    VERTEX *adjacency;
} GRAPH;

GRAPH *create_graph(int vertices_number) {
    GRAPH *graph = (GRAPH*)malloc(sizeof(GRAPH));
    graph->vertices_number = vertices_number;
    graph->edges_number = 0;
    graph->adjacency = (VERTEX *)malloc(vertices_number * sizeof(VERTEX));

    for (int i = 0; i < vertices_number; i++)
        graph->adjacency[i].head = NULL;
    return(graph);
}

ADJACENCY *create_adjacency(int vertex, int weight) {
    ADJACENCY *temp = (ADJACENCY *)malloc(sizeof(ADJACENCY));
    temp->vertex = vertex;
    temp->weight = weight;
    temp->next = NULL;
    return(temp);
}

bool create_edge(GRAPH *graph, int initial_vertex, int final_vertex,
                 WEIGHT_TYPE weight) {
    if (!graph)
        return(false);

    if ((final_vertex < 0) || (final_vertex >= graph->vertices_number))
        return(false);

    if ((initial_vertex < 0) || (initial_vertex >= graph->vertices_number))
        return(false);

    ADJACENCY *new = create_adjacency(final_vertex, weight);
    new->next = graph->adjacency[initial_vertex].head;
    graph->adjacency[initial_vertex].head = new;
    graph->edges_number++;
    return(true);
}

void print_graph(GRAPH *graph) {
    printf("Printing graph...\n");
    printf("vertices: %d, edges: %d.\n", graph->vertices_number,
            graph->edges_number);
    for (int i = 0; i < graph->vertices_number; i++) {
        printf("v%d: ", i);
        ADJACENCY *adjacency = graph->adjacency[i].head;
        while (adjacency) {
            printf("v%d(%d) ", adjacency->vertex, adjacency->weight);
            adjacency = adjacency->next;
        }
        printf("\n");
    }
    printf("\n");
}

void depth_visit(GRAPH *graph, int u, int *color) {
    printf("Visiting %d...\n", u);
    color[u] = YELLOW;
    ADJACENCY *adjacency = graph->adjacency[u].head;
    while (adjacency) {
        if (color[adjacency->vertex] == WHITE)
            depth_visit(graph, adjacency->vertex, color);
        adjacency = adjacency->next;
    }
    color[u] == RED;
}

int depth_firsth_search(GRAPH *graph) {
    int color[graph->vertices_number];
    printf("Depth first search...\n");

    for (int u = 0; u < graph->vertices_number; u++) {
        color[u] = WHITE;
    }
    for (int u = 0; u < graph->vertices_number; u++) {
        if (color[u] == WHITE)
            depth_visit(graph, u, color);
    }

    printf("\n");
}

void initialize_queue(QUEUE *queue) {
    queue->start = NULL;
    queue->end = NULL;
}

bool queue_insert(QUEUE *queue, REGISTRY registry) {
    NODE new = (NODE)malloc(sizeof(ELEMENT));
    new->registry = registry;
    new->next = NULL;
    if (queue->start == NULL)
        queue->start = new;
    else
        queue->end->next = new;
    queue->end = new;
    return true;
}

bool queue_remove(QUEUE *queue, REGISTRY *registry) {
    NODE temp;

    if (queue->start == NULL)
        return false;

    temp = queue->start;
    temp = queue->end;
    *registry = queue->start->registry;
    NODE node_to_remove = queue->start;
    queue->start = queue->start->next;
    free(node_to_remove);
    if (queue->start == NULL)
        queue->end = NULL;
}

void breadth_visit(GRAPH *graph, int start_vertex, bool *explored_vertices) {
    QUEUE queue;

    initialize_queue(&queue);
    explored_vertices[start_vertex] = true;
    REGISTRY *u = (REGISTRY *)malloc(sizeof(REGISTRY));
    u->key = start_vertex;
    queue_insert(&queue, *u);

    while (queue.start) {
        queue_remove(&queue, u);
        ADJACENCY *adjacency = graph->adjacency[u->key].head;
        while (adjacency) {
            if (!explored_vertices[adjacency->vertex]) {
                explored_vertices[adjacency->vertex] = true;
                u->key = adjacency->vertex;
                printf("Visiting %d...\n", u->key);
                queue_insert(&queue, *u);
            }
            adjacency = adjacency->next;
        }
    }
    free(u);
}

int breadth_first_search(GRAPH *graph) {
    bool explored_vertices[graph->vertices_number];

    printf("Breadth first search...\n");

    for (int u = 0; u < graph->vertices_number; u++)
        explored_vertices[u] = false;

    for (int u = 0; u < graph->vertices_number; u++)
        if (!explored_vertices[u]) {
            printf("Visiting %d...\n", u);
            breadth_visit(graph, u, explored_vertices);
        }
}

int main() {
    GRAPH *graph = create_graph(6);

    create_edge(graph, 0, 1, 2);
    create_edge(graph, 1, 2, 4);
    create_edge(graph, 2, 3, 12);
    create_edge(graph, 0, 5, 40);
    create_edge(graph, 5, 4, 3);
    create_edge(graph, 4, 3, 8);

    print_graph(graph);

    depth_firsth_search(graph);
    breadth_first_search(graph);

    return 0;
}
