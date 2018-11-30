#include <stdio.h>
#include <stdlib.h>   
#define SIZE 30                 // How many vertices do we have?

int Array[SIZE][SIZE];          // Graph matrix array.
int distance[SIZE];             // Min. distances array.
int vertex[SIZE];               // Vertices array.

void zeroArray()
{
    for(int i = 0; i < SIZE; i++)
        for(int j=0; j<SIZE; j++)
           Array[i][j]=0;
}

// Entering edges into the matrix.
void enterEdges()
{
    printf("Enter edges:\n");
    int r, c, n;
    for(int i = 0; i < 49; i++)
    {
        scanf("%d %d %d", &r, &c, &n);
        Array[r-1][c-1]=n;
        Array[c-1][r-1]=n;
    }
}

// Output
void printArray()  
{
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            printf("%d ", Array[i][j]);
        }
        printf("\n");
    }
} 

// Array initialization.
void initArray()
{
    for(int i = 0; i < SIZE; i++)
    {
        distance[i] = 10000;       // All distances are currently unknown, so we use a big-big number.
        vertex[i] =1;              // No vertix has been indixed yet.
    }
    distance[0] = 0;               // Distance to vertix 0.
}

// Output of smallest distances.
void printDistance()
{
    printf("\nShortest path to every vertex(1-30): \n");
        for(int i = 0; i < SIZE; i++)
        {
            printf("%d) %d;  ", i + 1, distance[i]);
            if((i + 1) % 5 == 0 && i != 0)
            	printf("\n");
        }
}

int main(void)
{                                
    int temp;
    int minindex;
    int min;
  
    zeroArray();

    enterEdges();
  
    printArray();
    
    initArray();
  
    do 
    {
        minindex=10000;
        min=10000;
        for(int i = 0; i < SIZE; i++)
        { 
            if((vertex[i] == 1) && (distance[i] < min))      // If vertix hasn't been used yet and weight < min.
            { 
                min=distance[i];
                minindex=i;
            }
        }

        if(min != 10000)
        {
            for(int i = 0; i <SIZE; i++)
            {
                if(Array[minindex][i]>0)
                {
                    temp = min + Array[minindex][i];
                    if(temp < distance[i])
                    {
                        distance[i] = temp;                           // Put down the distance into our distances array.
                    }
                }
            }
            vertex[minindex] = 0;                               // Vertix is used, mark it.
        }
    } 
    while(minindex < 10000);
      
    printDistance();
     
    // Gathering the min path.
    int ver[SIZE];
    int end = SIZE - 1; 		// Last vertix index(since we begin count from 0)
    ver[0] = end + 1; 			// First element - last vertix.
    int k = 1;
    int weight = distance[end];

    while (end > 0)
    {
        for(int i = 0; i < SIZE; i++)
            if (Array[end][i] != 0)
            {
                int temp = weight - Array[end][i];
                if (temp == distance[i])
                {
                    weight = temp;
                    end = i;
                    ver[k] = i + 1;
                    k++;
                }
            }
    }

    printf("\nOutput of the shortest path:\n");
    for(int i = k-1; i >= 0; i--)
    {
        printf("%3d ", ver[i]);
    }
}