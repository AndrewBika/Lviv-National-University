#include <stdio.h>
#include <stdlib.h>

// Maximum vertices in the graph
#define MAX_VERT 12

#define SENTINEL 2147483647
#define INT_MAX 2147483646

#define FALSE 0
#define TRUE 1

//create bidirectional edges since we have undirected graph
#define bidirect(graph, src, dest, weight) \
    addEdge(graph, src, dest, weight); \
    addEdge(graph, dest, src, weight);

void lazy_list_init(int* array, int lenght)
{
    for(int i = 0; i < lenght; i++)
    {
        array[i] = SENTINEL;
    }
}

int get_len(int* array)
{
    int len = 0;
    while(TRUE)
    {
        if(array[len] == SENTINEL)
        {
            return len;
        }
        len++;
    }
}

int is_in_list(int* array, int el)
{
    for(int i = 0, len = get_len(array); i < len; i++)
    {
        if(array[i] == el)
        {
            return TRUE;
        }
    }
    return FALSE;
}

void add_to_set(int* array, int el)
{
    if(!is_in_list(array, el))
    {
        array[get_len(array)] = el;
    }
}

typedef struct Graph{
    // Array of node pointers.
    struct Node* heads[MAX_VERT];
    int edge_amount;
} Graph;

typedef struct Node
{
    int source, destination, weight;
    struct Node* next;    
} Node;

void bubble_sort(Node**, int);

void addEdge(Graph* graph, int source, int destination, int weight)
{
    Node* newNode = (Node*) malloc(sizeof(Node));

    newNode->source = source;
    newNode->destination = destination;
    newNode->weight = weight;
    newNode->next = graph->heads[source];
    graph->heads[source] = newNode;
    graph->edge_amount++;
}

Graph* initializeGraph()
{
    Graph* graph = (Graph*) malloc(sizeof(Graph));

    for(int i = 0; i < MAX_VERT; i++)
        graph->heads[i] = NULL;

    graph->edge_amount = 0;

    return graph;
}

void recursive_destination_gathering(Graph* graph, int source, int* to_return)
{
    // Gathers all destinations source can get into.
    add_to_set(to_return, source);

    Node* ptr = graph->heads[source];
    while(ptr != NULL)
    {
        /*printf("Visited: ");
        for(int i = 0, len = get_len(to_return); i < len; i++)
        {
            printf("%d ", to_return[i]);
        }
        printf("\nMy source is = %d, dest is = %d\n", source, ptr->destination);*/
        if(!is_in_list(to_return, ptr->destination))
        { 
            recursive_destination_gathering(graph, ptr->destination, to_return);
        }
        ptr = ptr->next;
    }
}

int cycle_check(Graph* graph, int source, int destination)
{
    // Checks if we already have a way from source to destination.
    // Returns TRUE if cycle is found, FALSE otherways.
    int* checked_vertixes = malloc(sizeof(int) * MAX_VERT);
    lazy_list_init(checked_vertixes, MAX_VERT);

    recursive_destination_gathering(graph, destination, checked_vertixes);
    if(is_in_list(checked_vertixes, source))
    {
        free(checked_vertixes);
        return TRUE;
    }
    else
    {
        free(checked_vertixes);
        return FALSE;
    }
}

Graph* KrusMST(Graph* graph)
{
    // MST will have same amount of Vertices. But they are the same for all the graphs in this programm,
    // so I digress.
    Graph* mst = initializeGraph();

    // Counting all the possible edges to then sort them.
    int edge_count = 0;
    for(int i = 0; i < MAX_VERT; i++)
    {
        Node* ptr = graph->heads[i];
        while(ptr != NULL)
        {
            edge_count++;
            ptr = ptr->next;
        }
    }

    // Initiating an array of all edges, and sorting it by weight.
    Node* sorted_edges[edge_count];
    int edge_pos = 0;
    for(int i = 0; i < MAX_VERT; i++)
    {
        Node* ptr = graph->heads[i];
        while(ptr != NULL)
        {
            sorted_edges[edge_pos] = ptr;
            edge_pos++;
            ptr = ptr->next;
        }
    }
    bubble_sort(&sorted_edges[0], edge_count);

    for(int i = 0; i < edge_count; i++)
    {
        Node* edge = sorted_edges[i];
        if(!cycle_check(mst, edge->source, edge->destination))
        {
            addEdge(mst, edge->source, edge->destination, edge->weight);
        }
    }
    return mst;
}

void printBidirectGraph(struct Graph* graph){
    for(int i = 0; i < MAX_VERT; i++)
    {
        // Printing current vertix, and all it's edges.
        struct Node* ptr = graph->heads[i];
        int printed = FALSE;

        while(ptr != NULL)
        {
            printf("%d <-> %d (%d)\t", i, ptr->destination, ptr->weight);
            ptr = ptr->next;

            printed = TRUE;
        }
        //break to next line if something was printed
        if(printed)
        {
            printf("\n");
        }
    }
}

int main(){
    struct Graph* graph = initializeGraph();

    bidirect(graph, 1, 2, 7);
    bidirect(graph, 1, 3, 3);
    bidirect(graph, 1, 4, 2);
    bidirect(graph, 2, 5, 7);
    bidirect(graph, 2, 7, 1);
    bidirect(graph, 3, 5, 7);
    bidirect(graph, 3, 6, 4);
    bidirect(graph, 4, 6, 5);
    bidirect(graph, 4, 7, 5);
    bidirect(graph, 5, 8, 2);
    bidirect(graph, 5, 9, 4);
    bidirect(graph, 6, 8, 4);
    bidirect(graph, 6, 10, 2);
    bidirect(graph, 7, 9, 3);
    bidirect(graph, 7, 10, 4);
    bidirect(graph, 8, 11, 3);
    bidirect(graph, 9, 11, 1);
    bidirect(graph, 10, 11, 6);

    printf("The given graph is:\n");
    printBidirectGraph(graph);

    printf("\nThe MST for this graph is:\n");
    printBidirectGraph(KrusMST(graph));
}

void bubble_sort(Node** array, int lenght)
{
    for(int i = 0; i < lenght; i++)
    {
        for(int j = 0; j < lenght - i - 1; j++)
        {
            if(array[j]->weight > array[j + 1]->weight)
            {
                Node* temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}