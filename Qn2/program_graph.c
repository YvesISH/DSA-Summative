#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Graph {
    Node* adjLists[MAX_NODES];
    int numNodes;
} Graph;

void initGraph(Graph* graph) {
    graph->numNodes = 0;
    for (int i = 0; i < MAX_NODES; i++) {
        graph->adjLists[i] = NULL;
    }
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = dest;
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

void DFS(Graph* graph, int startNode, int visited[]) {
    visited[startNode] = 1;
    printf("%d ", startNode);

    Node* temp = graph->adjLists[startNode];
    while (temp != NULL) {
        int adjNode = temp->data;
        if (!visited[adjNode]) {
            DFS(graph, adjNode, visited);
        }
        temp = temp->next;
    }
}

int main() {
    Graph graph;
    initGraph(&graph);

    // Represent the program as a graph
    // Assume line numbers start from 1
    addEdge(&graph, 1, 2); // Start of program
    addEdge(&graph, 2, 3); // User input
    addEdge(&graph, 3, 4); // Allocate memory
    addEdge(&graph, 4, 5); // Get student details
    addEdge(&graph, 5, 6); // Loop start
    addEdge(&graph, 6, 7); // Get name
    addEdge(&graph, 7, 8); // Get grade
    addEdge(&graph, 8, 6); // Loop end
    addEdge(&graph, 6, 9); // Loop end
    addEdge(&graph, 9, 10); // Sort students
    addEdge(&graph, 10, 11); // Print student details
    addEdge(&graph, 11, 12); // Free memory
    addEdge(&graph, 12, 13); // End of program

    int visited[MAX_NODES] = {0};
    printf("DFS traversal of the program graph:\n");
    DFS(&graph, 1, visited);

    return 0;
}