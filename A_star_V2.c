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
struct nodeForAStar * final,*formoving;
int size=0;
int destination;
struct nodeForAStar *PQ;


// edge creation function
void createEdge(int i)
{
	int j=0;
	int a;
	struct node* k=NULL,*L=NULL;

	printf("Is there vertex connected to %d 1/0\n",i);
	scanf("%d",&a);

	while(a!=0)
	{
		int x,w;

		if(j==0)
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
			j++;
		}
		else{
			
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

 			j++;
		}

		printf("Is there more vertex connected to %d 1/0\n",i);
		scanf("%d",&a);
	}
    graph[i-1].noOfNodeConnected=j;

}


// graph display function
void displayConnection(int i){
	struct node* k=NULL,*L=NULL;
	k=graph[i-1].edges;
	printf("vertex %d is connected to ",i);
	while(k!=NULL)
	{
		printf("%d, ",k->vertex);

		k=k->next;
	}
    printf("\n");
	
}

void deleteFromHeap()
{
    int i,j;
    struct nodeForAStar *temp1=(struct nodeForAStar *)malloc(1*sizeof(struct nodeForAStar));
    struct nodeForAStar temp2;

    // copying !st element from PQ to TEMP1
    temp1->vertex=PQ[0].vertex;
    temp1->distance=PQ[0].distance;
    temp1->via=PQ[0].via;
    temp1->Hfunc=PQ[0].Hfunc;

    // now atttaching  temp1 to final linked list
    formoving->next=temp1;
    formoving->next->prev=formoving;
    formoving=formoving->next;

    // now keeping last element in PQ at the first position
    PQ[0].vertex=PQ[size-1].vertex;
    PQ[0].distance=PQ[size-1].distance;
    PQ[0].via=PQ[size-1].via;
    PQ[0].Hfunc=PQ[size-1].Hfunc;

    size=size-1;
    // reallocating PQ
    PQ=(struct nodeForAStar *)realloc(PQ,size*sizeof(struct nodeForAStar));
    i=0;
    j=2*i+1;

    // copying PQ[0] to temp2
    temp2.vertex=PQ[0].vertex;
    temp2.distance=PQ[0].distance;
    temp2.via=PQ[0].via;
    temp2.Hfunc=PQ[0].Hfunc;

    //correcting the heap
    while(j<size)    
    {    
        if(size>2)
        {
            if(PQ[j+1].Hfunc<PQ[j].Hfunc)
            {
                j=j+1;
            }

            if(temp2.Hfunc>PQ[j].Hfunc)
            {
                PQ[i].vertex=PQ[j].vertex;
                PQ[i].distance=PQ[j].distance;
                PQ[i].via=PQ[j].via;
                PQ[i].Hfunc=PQ[j].Hfunc;

                i=j;
                j=2*j+1;
            }
            else
            {
                PQ[i].vertex=temp2.vertex;
                PQ[i].distance=temp2.distance;
                PQ[i].via=temp2.via;
                PQ[i].Hfunc=temp2.Hfunc;
                return;
            }
        }

        else
        {
            if(temp2.Hfunc>PQ[j].Hfunc)
            {
                PQ[i].vertex=PQ[j].vertex;
                PQ[i].distance=PQ[j].distance;
                PQ[i].via=PQ[j].via;
                PQ[i].Hfunc=PQ[j].Hfunc;

                i=j;
                j=2*j+1;
            }
            else
            {
                PQ[i].vertex=temp2.vertex;
                PQ[i].distance=temp2.distance;
                PQ[i].via=temp2.via;
                PQ[i].Hfunc=temp2.Hfunc;
                return;
            }
        }
        
    }
    
}


//createHeap function
void createHeap(int i)
{
    struct nodeForAStar temp;
    int j=0;

    temp.vertex=PQ[i].vertex;
    temp.distance=PQ[i].distance;
    temp.via=PQ[i].via;
    temp.Hfunc=PQ[i].Hfunc;

    while (i>0 && temp.Hfunc<PQ[i/2].Hfunc)
    {
        PQ[i].vertex=PQ[i/2].vertex;
        PQ[i].distance=PQ[i/2].distance;
        PQ[i].via=PQ[i/2].via;
        PQ[i].Hfunc=PQ[i/2].Hfunc;
        i=i/2;
        j=1;
    }

   if(j!=0)
   {
    PQ[i].vertex=temp.vertex;
    PQ[i].distance=temp.distance;
    PQ[i].via=temp.via;
    PQ[i].Hfunc=temp.Hfunc;
   }

    
}



// creatingArrayforPQ function
void createArrayForPQ(struct listofvertex parentnodeaddress,int numConn)
{
    struct node *address;
    int x;
    x=size;
    size=size+numConn;
    PQ=(struct nodeForAStar *)realloc(PQ,size*sizeof(struct nodeForAStar));

    // address pointing to edges of parentnode address
    address=parentnodeaddress.edges;
    // now filling PQ
    for (int i = x; i < size; i++)
    {
        PQ[i].vertex=address->vertex;
        PQ[i].distance=formoving->distance+address->weight;
        PQ[i].via=formoving->vertex;
        PQ[i].Hfunc=PQ[i].distance+graph[(address->vertex)-1].heuristic;
        PQ[i].next=NULL;
        address=address->next;
        createHeap(i);
    }
    // here the priority queue is rready to be extracted

}


// Astar function
void Astar()
{
    //adding source to final list
    final=(struct nodeForAStar *)malloc(1*sizeof(struct nodeForAStar));
    formoving=final;
    
    final->prev=NULL;
    final->next=NULL;
    final->vertex=1;
    final->distance=0;
    final->via=1;
    final->Hfunc=final->distance+graph[0].heuristic;

    //initialising PQ
    PQ=(struct nodeForAStar *)malloc(1*sizeof(struct nodeForAStar));

    // calling function to create PQ using heap
    createArrayForPQ(graph[0],graph[0].noOfNodeConnected);
    // now initial PQ is ready, now we need to add more nodes to PQ and extract elements until destination node is reached
    while (!(PQ[0].vertex==destination))
    {
        deleteFromHeap();
        createArrayForPQ(graph[(formoving->vertex)-1],graph[(formoving->vertex)-1].noOfNodeConnected);
    }

    //adding last node to final linked list
    struct nodeForAStar *temp=(struct nodeForAStar *)malloc(1*sizeof(struct nodeForAStar));
    temp->vertex=PQ[0].vertex;
    temp->distance=PQ[0].distance;
    temp->via=PQ[0].via;
    temp->Hfunc=PQ[0].Hfunc;
    temp->next=NULL;
    temp->prev=formoving;

    formoving->next=temp;
    formoving=formoving->next;

}



int main()
{
    int i,src,des;
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

    //getting destination vertex
    printf("enter destination vertex");
    scanf("%d",&destination);
    
    //getting heuristic for vertices
    for(i=1;i<=noVer;i++)
	{
        printf("enter hueristic from %d to destination ",i);
        scanf("%d",&graph[i-1].heuristic);

        printf("hueristic of %d = %d\n",i,graph[i-1].heuristic);
	}

    //Calling astar function
    Astar();

    // checking if the path is correct or not
    src=1;
    struct nodeForAStar * temp;
    des=destination;
    temp=formoving;
    while(des!=src)
    {
        if(temp->via==temp->prev->vertex)
        {
            temp=temp->prev;
            des=temp->vertex;
        }
        else
        {
            temp->prev=temp->prev->prev;
            temp->prev->next=temp;    
        }
        
    }
    
    // printing the path and weight
    printf("path is ");
    struct nodeForAStar * show;
    show=final;
    while(show!=NULL)
    {
        printf("%d --> ",show->vertex);
        show=show->next;
    }
    printf("path length = %d",formoving->distance);

    return 0;
}
