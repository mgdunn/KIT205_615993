#define _CRT_SECURE_NO_WARNINGS  // Disable unsafe function warnings
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

// Function to add an edge at the front of the edge list
void insert_at_front(EdgeList* list, int to, int weight) {
    EdgeNodePtr newNode = (EdgeNodePtr)malloc(sizeof(struct edgeNode));
    newNode->edge.to_vertex = to;
    newNode->edge.weight = weight;
    newNode->next = list->head;
    list->head = newNode;
}

// Function to add an edge to the graph
void add_edge(Graph* self, int from, int to, int w) {
    insert_at_front(&self->edges[from], to, w);
}

int main() {
    Graph G;

    FILE* file = fopen("soc-academia.txt", "r");
    if (file == NULL) {
        return 1;
    }

    fscanf(file, "%d", &G.V);
    // Initialise edge lists for each vertex
    G.edges = (EdgeList*)malloc(G.V * sizeof(EdgeList));
    for (int i = 0; i < G.V; i++) {
        G.edges[i].head = NULL;
    }

    // Read edges and add to the graph
    int from;
    int to;
    int weight;

    while (fscanf(file, "%d %d", &from, &to) == 2) {
        add_edge(&G, from - 1, to - 1, 0);
    }

    fclose(file);

    int* in_degrees = (int*)malloc(G.V * sizeof(int));

    for (int i = 0; i < G.V; i++) {
        in_degrees[i] = 0;
    }

    for (int i = 0; i < G.V; i++) {
        EdgeNodePtr current = G.edges[i].head;
        while (current != NULL) {
            in_degrees[current->edge.to_vertex]++;

            current = current->next;
        }
    }

    // Print the in-degrees
    printf("In-degrees of all vertices:\n");
    for (int i = 0; i < G.V; i++) {
        printf("Vertex %d: %d\n", i + 1, in_degrees[i]);
    }

    free(in_degrees);
    free(G.edges);

    return 0;
}
