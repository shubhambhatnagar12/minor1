#include<stdio.h>
#include<stdlib.h>

struct node              //structure to represent edge in a graph
{
    int vertex;
    int weight;
    struct node *next;
};

struct nodeForAStar            //structure to represent Priority queue and Final linked list
{
    int vertex;
    int distance;
    int via;
    int Hfunc;
    struct nodeForAStar *next,*prev;
};

struct listofvertex             //structure to represent vertices in a graph
{
    int heuristic;
    int noOfNodeConnected;
    struct node *edges;
};


int noVer;                                  //declaration of global variables
struct listofvertex * graph;
int destination;





// edge creation function
void createEdge(int i)
{
	int j,iteration,x,w,a;
	struct node* k=NULL,*L=NULL;

    printf("total no. of vertices connected to vertex %d ? ",i);
    scanf("%d",&j);
    graph[i-1].noOfNodeConnected=j;


    for (iteration=0; iteration<j; iteration++)
    {   
        if(iteration==0)
		{
			graph[i-1].edges=(struct node*)malloc(sizeof(struct node));

            //added vertex in node
			printf("HEYY the vertex %d is connected to which vertex\n",i);
			scanf("%d",&x);
            graph[i-1].edges->vertex=x;

            //added weight
            printf("weight of edge = ");
			scanf("%d",&w);
            graph[i-1].edges->weight=w;
            
            graph[i-1].edges->next=NULL;
			L=graph[i-1].edges;
		}
		else
        {
			
			L->next=(struct node*)malloc(sizeof(struct node));

            //added vertex in node
			printf("the vertex %d is connected to which vertex\n",i);
			scanf("%d",&x);
            L->next->vertex=x;

            //added weight
            printf("weight of edge = ");
			scanf("%d",&w);
            L->next->weight=w;

            L->next->next=NULL;
            L=L->next;

		}
    }

}


// graph display function
void displayConnection(int i){
	struct node* k=NULL,*L=NULL;
	k=graph[i-1].edges;
	printf("vertex %d is connected to vertex ",i);
	while(k!=NULL)
	{
		printf("%d (Weight= %d ) ",k->vertex,k->weight);

		k=k->next;
	}
    printf("\n");
	
}


int main()
{
    int i;
	printf("no. of vertex in graph = ");
	scanf("%d",&noVer);
	printf("no. of vertex=%d\n",noVer);

    //created listofvertex array of size noVer
    graph=(struct listofvertex *)calloc(noVer,sizeof(struct listofvertex));

    //entering info in the listofvertex and adding edges
    for(i=1;i<=noVer;i++)
	{
         createEdge(i);
	}

    //printing graph
    for(i=1;i<=noVer;i++)
	{
		displayConnection(i);
	}


    return 0;
}