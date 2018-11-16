#include <stdio.h>
#include <stdlib.h>

//maximum vertices in the graph
#define N 31

//big number for int
#define INTBIG 0x7FFFFFFF

#define false 0
#define true 1

//create bidirectional edges since we have undirected graph
#define bidirect(graph, src, dest, w) \
    addEdge(graph, src, dest, w); \
    addEdge(graph, dest, src, w);

struct Graph{
    //array of pointers to Node. V is size of vertices set
    //cost is sum of all edges weight
    int V, cost;
    struct Node* head[N];
};

struct Node{
    //represents node, its destination edge and weight
    int weight, destination;
    struct Node* next;
};

struct Node* newNode(int name, int weight){
    //makes new node
    struct Node* node = (struct Node*)malloc(
        sizeof(struct Node)
    );

    node->destination = name;
    node->weight = weight;

    return node;
};

void addEdge(struct Graph* graph,
    int source, int destination, int weight){

    //add edge from source to destination
    struct Node* node = newNode(destination, weight);
    graph->cost += weight;
    node->next = graph->head[source];
    graph->head[source] = node;
}

struct Graph* initializeGraph(int V){
    //allocate memory for graph data structure size of V
    struct Graph* graph = (struct Graph*)malloc(
        sizeof(struct Graph)
    );

    graph->cost = 0;
    graph->V = V;

    //add head pointer for all vertices
    for(int i=0; i<N; i++)
        graph->head[i] = NULL;

    return graph;
};

void addVertex(struct Graph* graph, int V){
    //adds vertex to graph
    graph->head[V] = NULL;
    graph->V++;
}

int min(int* array, int* avoid, int arrsize){
    //returns index of minimum element of array, except
    //those which is in 'avoid'. returns -1 if not found.

    int minel = INTBIG,
        minindex = -1;
    for(int i=0; i<arrsize; i++){
        if(
            !*(avoid+i) &&
            *(array+i)<minel
        ){
            minel = *(array+i);
            minindex = i;
        }
    }

    return minindex;
}

int full(int *array, int arrsize){
    //returns 'true' if array do not contain 'false'
    for(int i=0; i<arrsize; i++)
        if( *(array+i) == false )
            return false;
    return true;
}

int* dijkstra(struct Graph* graph, int start){
    /*returns array tree where the index represents vertex and value is
    * parent of it. the start point will be marked as 0.
    * i.e if we have array [1:0 | 2:1 | 3:4 | 4:1 | 5:3] (where the
    * first number is index and second one is vertex), the path from 1
    * to 5 vertex will be 5<-3<-4<-1.
    * this path must be printed reversely.
    */

    //allocate memory for array of shortest distances
    int *tree = (int*)malloc(
        sizeof(int) * graph->V
    );

    //allocate memory for shortest paths tree (SPT)
    int *spt = (int*)malloc(
        sizeof(int) * graph->V
    );

    //allocate memory for marking visited vertices
    int *visited = (int*)malloc(
        sizeof(int) * graph->V
    );

    //now distances to all vertex is a INTBIG and no
    //vertices have been visited yet
    for(int i=0; i<graph->V; i++){
        *(tree+i) = INTBIG;
        *(visited+i) = false;
        *(spt+i) = -1;
    }

    //select first vertex. use start-1 to count from 0, while the graph
    //vertices will be enumerated from 1
    *(tree+start-1) = 0;
    *(visited+start-1) = 0;

    //check wether there are still unvisited vertices
    while( !full(visited, graph->V) ){
        //find minimum edge to unvisited vertices
        int minel = min(tree, visited, graph->V);
        //min returns -1 when no elements found
        if(minel == -1)
            break;
        struct Node *node = graph->head[minel+1];
        //l variable will be used to hold previous weight
        int l = *(tree+minel);
        //while next node is not equal to NULL
        while(node){
            int dest = node->destination;
            if( node->weight+l < *(tree+dest) ){
                *(tree+dest) = node->weight+l;
                *(spt+dest-1) = minel+1;
            }
            //go to the next node
            node = node->next;
        }
        *(visited+minel) = 1;
    }
    *(spt+29) = 29;

    for(int i=0; i<graph->V; i++)
        printf("[V%d]: %d\n", i, *(tree+i));

    free(tree);
    free(visited);
    return spt;
};

void printShortestPath(int* spt, int start, int end, int arrsize){
    /*prints the shortest path between end and start point using
    * shortest path tree.
    * we have to print path reversely, so the best solution is to write
    * it into the array, increase 'length' on each step and process it
    * backwardly.
    */
    //allocate memory for path
    int *path = (int*)malloc( sizeof(int)*arrsize );
    if( *(spt+end-1) < 0 ){
        printf("There's no way from %d to %d.", start, end);
        return;
    }
    int length = 0;

    int cursor = end;
    while(start != cursor){
        cursor = *(spt + cursor-1);
        *(path + length++) = cursor;
    }

    while(length-- > 0)
        printf( "%d>", *(path+length) );

    printf("%d\n", end);
};

void printBidirectGraph(struct Graph* graph){
    for(int i=0; i<graph->V; i++){
        //print current vertex and all its neighbors
        struct Node* ptr = graph->head[i];
        //remember if something was printed
        int printed = false;

        while(ptr){
            printf("%d -> %d (%d)\t",
                i, ptr->destination, ptr->weight);
            ptr = ptr->next;
            if(ptr == NULL)
            printed = true;
        }
        //break to next line if something was printed
        if(printed)
            printf("\n");
    }
    printf("Cost of this graph is: %d\n", graph->cost/2);
}

int main(){
    /*there will be net-graph with 30 vertices:
    * 1   2   3   4   5   6
    * 7   8   9   10  11  12
    * 13  14  15  16  17  18
    * 19  20  21  22  23  24
    * 25  26  27  28  29  30
    */

    struct Graph* graph = initializeGraph(30);

    //1st row
    bidirect(graph, 1, 2, 6);
    bidirect(graph, 1, 7, 4);
    bidirect(graph, 2, 3, 1);
    bidirect(graph, 2, 8, 8);
    bidirect(graph, 3, 4, 1);
    bidirect(graph, 3, 9, 3);
    bidirect(graph, 4, 5, 3);
    bidirect(graph, 4, 10, 1);
    bidirect(graph, 5, 6, 3);
    bidirect(graph, 5, 11, 5);
    bidirect(graph, 6, 12, 7);

    //2nd row
    bidirect(graph, 7, 8, 2);
    bidirect(graph, 7, 13, 5);
    bidirect(graph, 8, 9, 1);
    bidirect(graph, 8, 14, 1);
    bidirect(graph, 9, 10, 4);
    bidirect(graph, 9, 15, 3);
    bidirect(graph, 10, 11, 2);
    bidirect(graph, 10, 16, 4);
    bidirect(graph, 11, 12, 4);
    bidirect(graph, 11, 17, 1);
    bidirect(graph, 12, 18, 7);

    //3rd row
    bidirect(graph, 13, 14, 7);
    bidirect(graph, 13, 19, 5);
    bidirect(graph, 14, 15, 1);
    bidirect(graph, 14, 20, 7);
    bidirect(graph, 15, 16, 2);
    bidirect(graph, 15, 21, 1);
    bidirect(graph, 16, 17, 3);
    bidirect(graph, 16, 22, 4);
    bidirect(graph, 17, 18, 7);
    bidirect(graph, 17, 23, 2);
    bidirect(graph, 18, 24, 8);

    //4th row
    bidirect(graph, 19, 20, 7);
    bidirect(graph, 19, 25, 8);
    bidirect(graph, 20, 21, 3);
    bidirect(graph, 20, 26, 2);
    bidirect(graph, 21, 22, 1);
    bidirect(graph, 21, 27, 1);
    bidirect(graph, 22, 23, 8);
    bidirect(graph, 22, 28, 3);
    bidirect(graph, 23, 24, 5);
    bidirect(graph, 23, 29, 3);
    bidirect(graph, 24, 30, 7);

    //5th row
    bidirect(graph, 25, 26, 4);
    bidirect(graph, 26, 27, 7);
    bidirect(graph, 27, 28, 3);
    bidirect(graph, 28, 29, 3);
    bidirect(graph, 29, 30, 6);

    printf("The given graph is:\n");
    printBidirectGraph(graph);

    int start = 1, end = 30;
    printf( "\nThe shortest paths tree from %d is:\n\n", end);

    int* tree = dijkstra(graph, start);

    printf("\nThe tree structure is:\n");
    for(int i=0; i<graph->V; i++)
        printf("[%d]:%d\n", i, *(tree+i));

    printf("\nThe shortest path from %d to %d is:\n", start, end);
    printShortestPath(tree, 1, 30, graph->V);

    return 0;
}