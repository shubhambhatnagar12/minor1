#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<stdbool.h>
#include <time.h> 
#define INF 99999
                                  /* common declarations in all 3 algos*/

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

int noVer, algorithm, destination, size=1, knowhere=0;                                  //declaration of global variables
struct listofvertex * graph;
struct nodeForAStar * final,*formoving;
struct nodeForAStar *PQ;



void traverse(int,int[]);							//declaration of all the functions
void get_heuristic(int);
void createEdge(int);
void updateEdge(int);
void changeweight(int,int,int);
void displayConnection(int);
void addnodes();
void weightupdate();
void Dynamicchange();
bool setisempty(int[]);
int min(int[],int[]);
int noadjvertices(int);
int adjvertices(int,int);
int adjverticesweight(int,int);
int path(int,int[],int);
void dijkstra(int);
void BellmanFord(int);
void deleteFromHeap();
void createHeap(int);
void createArrayForPQ(struct listofvertex,int);
void AstarMain(int);
void Astar(int);
void fillgraph();
void height(int);
void distance(int);
void delay(int);
void frontend();
void rectangle(int, int);


// delay function
void delay(int time) 
{ 
    // Converting time into milli_seconds 
    int ms = 1000 * time; 
  
    // Storing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < start_time + ms) 
        ; 
} 

// edge creation function
void createEdge(int i)
{
    int j,iteration,x,w;
	struct node* k=NULL,*L=NULL;

	system("cls");  					// clear screen
	height(3);
	distance(30);

    printf("Total Number Of Vertices Connected To Vertex %d ? \n",i);
	distance(30);
    printf("-> ");
	scanf("%d",&j);
	printf("\n");
    graph[i-1].noOfNodeConnected=j;

    for (iteration=0; iteration<j; iteration++)
    {   
        if(iteration==0)
		{
			graph[i-1].edges=(struct node*)malloc(sizeof(struct node));

			distance(30);
			//added vertex in node
			printf("HEYY the vertex %d is connected to which vertex = ",i);
			scanf("%d",&x);
            graph[i-1].edges->vertex=x;

			distance(30);
            //added weight
            printf("weight of edge = ");
			scanf("%d",&w);
			printf("\n");
            graph[i-1].edges->weight=w;
            
            graph[i-1].edges->next=NULL;
			L=graph[i-1].edges;
		}
		else
        {
			
			L->next=(struct node*)malloc(sizeof(struct node));

            distance(30);
			//added vertex in node
			printf("HEYY the vertex %d is connected to which vertex = ",i);
			scanf("%d",&x);
            L->next->vertex=x;

			distance(30);
            //added weight
            printf("weight of edge = ");
			scanf("%d",&w);
			printf("\n");
            L->next->weight=w;

            L->next->next=NULL;
            L=L->next;

		}
    }
}



void updateEdge(int i)
{
    int j,x,w;
	struct node *L=NULL;

    if(graph[i-1].edges==NULL)
	{
    	createEdge(i);
	}
	else
	{
		distance(30);
		printf("Total no. of new edges for vertex %d ? \n",i);
		distance(30);
		printf("-> ");
    	scanf("%d",&j);
    	graph[i-1].noOfNodeConnected = graph[i-1].noOfNodeConnected+j;
    
		for(int h=0;h<j;h++)
		{
    		L=(struct node*)malloc(sizeof(struct node));
			distance(30);
    		printf("the vertex %d is connected to which vertex\n",i);
			distance(30);
			printf("-> ");
			scanf("%d",&x);
            L->vertex=x;

            //added weight
			distance(30);
            printf("weight of edge = ");
			scanf("%d",&w);
            L->weight=w;
            L->next=graph[i-1].edges;
            graph[i-1].edges=L;
    			
		}
	}
}

void changeweight(int x, int y, int w)
{
	struct node *K=NULL;
	K=graph[x-1].edges;
		
	while(K->vertex!=y)
	{
		K=K->next;	
	}
		
	K->weight=w;
	printf("Edge weight Updated");
}

// graph display function
void displayConnection(int i)
{	
	struct node* k=NULL,*L=NULL;
	k=graph[i-1].edges;
	printf("Vertex %d is connected to --> ",i);
	if (k==NULL)
	{
		printf("NULL");
	}
	
	while(k!=NULL)
	{
		printf("%d [ Weight= %d ]   ",k->vertex,k->weight);
		k=k->next;
	}
    printf("\n");
}

void addnodes()
{
	int n,e;
	height(2);
	distance(30);
	printf("How Many nodes you want to add ? \n");
	distance(30);
	printf("-> ");
	scanf("%d",&n);

	noVer=noVer+n;
	
	graph=(struct listofvertex *)realloc(graph,noVer*sizeof(struct listofvertex));
	
	for(int i=1;i<=n;i++)
	{
		createEdge((noVer-n)+i);
	}
	
	for(int i=1;i<=n;i++)
	{
		get_heuristic((noVer-n)+i);
	}
	 
	
	distance(30);
	printf("How Many vertex are affected by this addition ? \n");
	distance(30);
	printf("-> ");
	scanf("%d",&e);
	
	for(int j=0;j<e;j++)
	{
		int x;
		distance(30);
		printf("Which vertex is affected? \n");
		distance(30);
		printf("-> ");
		scanf("%d",&x);
		updateEdge(x);
	}
	
}


void weightupdate()
{
	int n;
	height(2);
	distance(30);
	printf("How many edge has to be updated? \n");
	distance(30);
	printf("-> ");
	scanf("%d",&n);
	height(2);
	for(int i=0;i<n;i++)
	{
		int y,x,w;
		distance(30);
		printf("Enter the source vertex \n");
		distance(30);
		printf("-> ");
		scanf("%d \n",&x);
		distance(30);
		printf("Enter the destination vertex \n ");
		distance(30);
		printf("-> ");
		scanf("%d \n",&y);
		distance(30);
		printf("Enter the updated weight for edge %d to %d",x,y);
		distance(30);
		printf("-> ");
		scanf("%d",&w);
		 
		changeweight(x,y,w);
	}
}

void Dynamicchange()
{
	int R3;
	system("cls");
	height(2);
	distance(30);
	printf("Choose among the Given Dynamic scenarios you want to update: \n");
	distance(30);
	printf("(0) Add Nodes \n");
	distance(30);
	printf("(1) Change Weight of Edges \n");
	distance(30);
	printf("-> ");
	scanf("%d",&R3);
	
	if(R3==0)
	{
		knowhere++;
		addnodes();
		height(2);
		for(int i=1;i<=noVer;i++)
		{
			distance(30);
			displayConnection(i);
			printf("\n");
		}
	}
	if(R3==1)
	{
		weightupdate();
		height(2);
		for(int i=1;i<=noVer;i++)
		{
			distance(30);
			displayConnection(i);
			printf("\n");
		}
	}
	
} 


void traverse(int source,int parent[])
{
	int M=destination, L=noVer, temp[noVer];

	height(2);
	
	
	for(int i=0;i<noVer;i++)
	{
		temp[i]=0;
	}
	while(M!=source)
	{
		temp[L-1]=M;
		M=parent[M-1];
		L--;
	}
	
	if(M==source)
	{
		temp[L-1]=M;
	}
	
	int R2=1, R1, counter=0;
	while(R2==1)
	{
		if(counter<noVer-1)
		{
	
			if( temp[counter]!= 0)
			{
				distance(30);
				printf("You are currently at node %d \n",temp[counter]);
				distance(30);
				printf("Next node in the shortest path is %d .\n",temp[counter+1]);
				distance(30);
				printf("You want to keep traversing { PRESS 1 } or bring some Dynamic change ? { PRESS 0 } \n");
				distance(30);
				printf("-> ");
				scanf("%d",&R2);
				if(R2==1)
				{	
					height(2);
					counter++;
				}
				
			}
			if( temp[counter]==0)
			{
				counter++;
			}
		
		}
		else
		{
			distance(30);
			printf("The last node in the path is %d ",temp[counter]);
			exit(0);
		}
	}
	
	if(R2==0)
	{
		Dynamicchange();
		//printf("in after dynamic change source is at %d \n",temp[counter]);
        delay(10);
		if(algorithm==1)
		dijkstra(temp[counter]);
		else if(algorithm==3)
		AstarMain(temp[counter]);
		else if(algorithm==2)
		BellmanFord(temp[counter]);
	}
}


                                    /*  DIJKSTRA FUNCTIONS */

bool setisempty(int set[])
{
	int counter=0;
	for(int i=0;i<noVer;i++)
	{
	  	if(set[i]!=0)
		{
			counter++;
		}
	}
	if(counter==noVer)
	{
		return false;
	}
	else
	{
		return true;
	}
	  
}

// MIN FUNCTION WHICH RETURNS THE VERTEX IN THE WEIGHT ARRAY HAVING MINIMUM VALUE

int min(int weights[],int set[]){
	
	int initial=0, counter=0, wtemp[noVer];
	 
	//COPYING THE WEIGHT ARRAY IN TEMP
	for(int i=0;i<noVer;i++)
	{
		wtemp[i]=weights[i];
	}
	
	// NOW WE REMOVE THOSE VERTEX TO BE CHOSEN BY OUR FUNCTION WHICH HAVE BEEN ALREADY CHOSEN BEFORE AND SENT TO SET
	
	for(int i=0;i<noVer;i++)
	{
		if(set[i]!=0)
		{
			wtemp[set[i]-1]=INF;
		}
			
	}
	
	for(int i=0;i<noVer;i++)
	{
		if(wtemp[i]==INF)
		{
			counter++;
		}
		
	}
	if(counter!=noVer){
		// SELECTING THE MIN. VERTEX
		for(int i=1;i<noVer;i++)
		{
			if(wtemp[i]<wtemp[initial])
			{
				initial=i;
			}
		}
		return(initial+1);
	}
	else
	{
		return 0;
	}
	
}

// NOADJVERTICES FUNCTION TO FIND THE NUMBER OF VERTEX ADJACENT TO THE MIN. VERTEX
//IT RETURNS TOTAL NUMBER OF ADJACENT VERTICES
// THE FUNCTION IS SIMILAR TO DISPLAY DUNCTION

int noadjvertices(int u)
{
	struct node* k=NULL;
	k=graph[u-1].edges;
	int counter=0;
	
	while(k!=NULL)
	{
		counter++;
		k=k->next;
	}
	
	return(counter);
}

// ADJVERTICES FUNCTION TO RETURN ALL THE ADJACENT VERTICES TO THE MIN VERTEX

int adjvertices(int u, int j)
{
	struct node* k=NULL;
	k=graph[u-1].edges;
	for(int i=0;i<j;i++)
	{
		k=k->next;
	}
	
	return(k->vertex);
}

// ADJVERTICESWEIGHT FUNCTION TO RETURN THE WEIGHTS OF ALL THE ADJACENT VERTICES OF MIN. VERTEX

int adjverticesweight(int u, int j)
{
	struct node* k=NULL;
	k=graph[u-1].edges;
	
	for(int i=0;i<j;i++)
	{
		k=k->next;
	}
	
	return(k->weight);
}

// PATH VERTEX TO SHOW THE MINIMUM WEIGHT PATH FROM SOURCE TO DESTINATION VERTEX

int  path(int destination, int parent[], int source)
{
	int counter=0;
	
	if(destination==source)
	{	
		printf("%d <-- \n",destination);
		return 0;
	}
	
	if(destination!=source)
	{
		printf("%d <-- ",destination);
		return(path(parent[destination-1],parent,source));
	}
	
}



//DIJKSTRA FUNCTION CONTAINING RELAX FUNCTION OF ALGO AND INITIALISING ALL WEIGHT AND SET TO INFINITE AND ZERO


void dijkstra(int source)
{
	int R1, weights[noVer], parent[noVer], set[noVer], u, check=0;
	struct timespec start, end;         // for calculating time using gettime function

// INITIALISING SINGLE SOURCE BY ADDING INFINITE IN ALL THE OTHER VERTICES IN WEIGHT ARRAY
	for(int i=0;i<noVer;i++)
	{
		weights[i]=INF;
		set[i]=0;
	}

	weights[source-1]=0;
	parent[source-1]=0;

	// MAIN ITERATING LOOP
	//starting time
	clock_gettime(CLOCK_MONOTONIC, &start); 

	while(setisempty(set))
	{
		u=min(weights,set);
		
		if(u!=0)
		{
		
			set[u-1]=u;
	
			// FINDING ADJACENT VERTICES TO U
			int noadj = noadjvertices(u);
		
			if(noadj!=0)
			{
				int adjvert[noadj];
				int adjvertweight[noadj];
				for(int j=0;j<noadj;j++)
				{
					adjvert[j]=adjvertices(u,j);
					adjvertweight[j]=adjverticesweight(u,j);
				}
			
				// RELAX ITERATION
	
				for(int c=0;c<noadj;c++)
				{
					//relax(u,adjvert[c],adjvertweight[c]);
					if(weights[adjvert[c]-1]>(weights[u-1]+adjvertweight[c]))
					{
						weights[adjvert[c]-1]=weights[u-1]+adjvertweight[c];
						parent[adjvert[c]-1]=u;
					}
				}
			}

		}
		else
		{
			break;
		}
	}
	
	 
    //stopping time
	clock_gettime(CLOCK_MONOTONIC, &end);
    //calculating time in nano seconds
	double time_taken; 
	time_taken = (end.tv_sec - start.tv_sec) * 1e9; 
	time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) ;

	int parenttemp[noVer];
	for(int i=0;i<noVer;i++)
	{
		parenttemp[i]=parent[i];
	}
	if (algorithm==1)
	{
		system("cls");
	}
	
	printf("\n");
	distance(30);
	printf("DISPLAYING PATH CALCULATED BY Dijkstra ALGORITHM \n");
	printf("\n");
	distance(30);
	printf("Path is : ");
	path(destination,parent,source);

	distance(30);
    printf("Dijkstra took %lf nano seconds to execute ", time_taken); 
	height(3);

	if (algorithm==1)
	{
		BellmanFord(source);
		if (knowhere==0)
		{
			Astar(source);
		}
		else
		{
			AstarMain(source);
		}
		
		

	
		height(2);
		distance(30);
		printf("Do you want to start traversing your shortest path? (1/0) \n");
		distance(30);
		printf("-->");
		scanf("%d",&R1);
	
		if(R1==1)
		{
			system("cls");
			traverse(source,parent);
		}
		else
		{
			exit(0);
		}
	}
	
	
	
}




//___________________________________________  /*  BELLMAN FORD functions  */

void BellmanFord(int source)
{
	int R1=0, weights[noVer], parent[noVer];
	struct timespec start, end;  // for calculating time using gttime function
  	// OVER ESTIMATION
    for (int i = 0; i < noVer; i++)
	{ 	//initialise all dist to INT_MAX
    	weights[i]  = INF;
      	parent[i] = 0;
    }
    weights[source-1] = 0;
    
//starting time
   clock_gettime(CLOCK_MONOTONIC, &start);
  // RELAXATION 
    for (int r = 0; r < noVer-1; r++)
    {
        for (int u = 1; u <= noVer; u++)
        {
            // FINDING ADJACENT VERTICES TO U		
		
			int noadj = noadjvertices(u);
		
			if(noadj!=0)
			{
				int adjvert[noadj];
				int adjvertweight[noadj];
			
				for(int j=0;j<noadj;j++)
				{
					adjvert[j]=adjvertices(u,j);
					adjvertweight[j]=adjverticesweight(u,j);
				}	
		
				// RELAX ITERATION
				for(int c=0;c<noadj;c++)
				{
					//relax(u,adjvert[c],adjvertweight[c]);
					if(weights[adjvert[c]-1]>(weights[u-1]+adjvertweight[c]))
					{
						weights[adjvert[c]-1]=weights[u-1]+adjvertweight[c];
						parent[adjvert[c]-1]=u;
					}
				}
			}
    	}
	}
  
  	// NEGATIVE CYCLE CHECK
	for (int u = 1; u <= noVer; u++)
	{
        // FINDING ADJACENT VERTICES TO U	
		int noadj = noadjvertices(u);
		
		if(noadj!=0)
		{
			int adjvert[noadj];
			int adjvertweight[noadj];
			
			for(int j=0;j<noadj;j++)
			{
				adjvert[j]=adjvertices(u,j);
				adjvertweight[j]=adjverticesweight(u,j);
			}
		
			// NEGATIVE CYCLE CHECK
			for(int c=0;c<noadj;c++)
			{
				if(weights[adjvert[c]-1]>(weights[u-1]+adjvertweight[c]))
				{
					height(2);
					distance(30);
					printf("Graph contains negative weight cycle");
				}
			}
		}
	} 
	
    //stopping time
	clock_gettime(CLOCK_MONOTONIC, &end); 
    //calculating time in nano seconds
    double time_taken; 
	time_taken = (end.tv_sec - start.tv_sec) * 1e9; 
	time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) ; 
	if (algorithm==2)
	{
		system("cls");
	}
	printf("\n");
	distance(30);
	printf("DISPLAYING PATH CALCULATED BY BellmanFord ALGORITHM \n");
	printf("\n");
	distance(30);
	printf("Path is : ");
	path(destination,parent,source);

	distance(30);
    printf("Bellman Ford took %lf nano seconds to execute ", time_taken);
	height(3);
	distance(30);

	if (algorithm==2)
	{
		dijkstra(source);
		if (knowhere==0)
		{
			Astar(source);
		}
		else
		{
			AstarMain(source);
		}

		height(2);
		distance(30);
    	printf("Do you want to start traversing your shortest path? (1/0) \n");
    	distance(30);
    	printf("-->");
		scanf("%d",&R1);
	
		if(R1==1)
		{
			system("cls");
			traverse(source,parent);
		}
		else
		{
			exit(0);
		}	
	}
	
	
	
}


//________________________________________________/*  A-STAR FUNCTIONS */

void deleteFromHeap()
{
    int i,j;
    struct nodeForAStar *temp1=(struct nodeForAStar *)malloc(1*sizeof(struct nodeForAStar));
    struct nodeForAStar temp2;

    // copying !st element from PQ to TEMP1
    temp1->vertex=PQ[1].vertex;
    temp1->distance=PQ[1].distance;
    temp1->via=PQ[1].via;
    temp1->Hfunc=PQ[1].Hfunc;

    // now atttaching  temp1 to final linked list
    formoving->next=temp1;
    formoving->next->prev=formoving;
    formoving=formoving->next;

    // now keeping last element in PQ at the first position
    PQ[1].vertex=PQ[size-1].vertex;
    PQ[1].distance=PQ[size-1].distance;
    PQ[1].via=PQ[size-1].via;
    PQ[1].Hfunc=PQ[size-1].Hfunc;

    size=size-1;
    // reallocating PQ
    PQ=(struct nodeForAStar *)realloc(PQ,size*sizeof(struct nodeForAStar));
    i=1;
    j=2*i;

    // copying PQ[1] to temp2
    temp2.vertex=PQ[1].vertex;
    temp2.distance=PQ[1].distance;
    temp2.via=PQ[1].via;
    temp2.Hfunc=PQ[1].Hfunc;

    //correcting the heap
    while(j<size)    
    {    
        if(size>3)
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
                j=2*j;

                PQ[i].vertex=temp2.vertex;
                PQ[i].distance=temp2.distance;
                PQ[i].via=temp2.via;
                PQ[i].Hfunc=temp2.Hfunc;
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
                j=2*j;

                PQ[i].vertex=temp2.vertex;
                PQ[i].distance=temp2.distance;
                PQ[i].via=temp2.via;
                PQ[i].Hfunc=temp2.Hfunc;
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

    while (i>1 && temp.Hfunc<PQ[i/2].Hfunc)
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
void AstarMain(int source2)
{   
    int src,des;
    int R1=0;
	struct timespec start, end;  //for calculating time using gettime function

    //adding source to final list
    final=(struct nodeForAStar *)malloc(1*sizeof(struct nodeForAStar));
    formoving=final;
    
    final->prev=NULL;
    final->next=NULL;
    final->vertex=source2;
    final->distance=0;
    final->via=source2;
    final->Hfunc=final->distance+graph[source2-1].heuristic;

    //initialising PQ
    size=1;
    PQ=(struct nodeForAStar *)malloc(1*sizeof(struct nodeForAStar));

    // calling function to create PQ using heap
    createArrayForPQ(graph[source2-1],graph[source2-1].noOfNodeConnected);
    // now initial PQ is ready, now we need to add more nodes to PQ and extract elements until destination node is reached
    //starting time
    clock_gettime(CLOCK_MONOTONIC, &start); 

    while (!(PQ[1].vertex==destination))
    {
        deleteFromHeap();
        createArrayForPQ(graph[(formoving->vertex)-1],graph[(formoving->vertex)-1].noOfNodeConnected);
    }
     
    //stopping time
	clock_gettime(CLOCK_MONOTONIC, &end); 
    //calculating time in nano seconds
	double time_taken; 
	time_taken = (end.tv_sec - start.tv_sec) * 1e9; 
	time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) ; 

    //adding last node to final linked list
    struct nodeForAStar *temp=(struct nodeForAStar *)malloc(1*sizeof(struct nodeForAStar));
    temp->vertex=PQ[1].vertex;
    temp->distance=PQ[1].distance;
    temp->via=PQ[1].via;
    temp->Hfunc=PQ[1].Hfunc;
    temp->next=NULL;
    temp->prev=formoving;

    formoving->next=temp;
    formoving=formoving->next;


    // checking if the path is correct or not
    src=source2;
    struct nodeForAStar * temp2;
    des=destination;
    temp2=formoving;
    while(des!=src)
    {
        if(temp2->via==temp2->prev->vertex)
        {
            temp2=temp2->prev;
            des=temp2->vertex;
        }
        else
        {
            temp2->prev=temp2->prev->prev;
            temp2->prev->next=temp2;    
        }
        
    }
    
    // printing the path and weight
	if (algorithm==3)
	{
		system("cls");
		height(3);
		distance(30);
	}
	
	height(3);
	distance(30);
	
	printf("DISPLAYING PATH CALCULATED BY A-STAR ALGORITHM");
	height(2);
	distance(30);

    printf("Path is : ");
    struct nodeForAStar * show;
    show=final;
    while(show!=NULL)
    {
        printf("%d --> ",show->vertex);
        show=show->next;
    }
    printf("\n");
	distance(30);
    printf("Path length = %d",formoving->distance);
    printf("\n");
	distance(30);
    printf("A-Star took %lf nano seconds to execute ", time_taken); 
	height(3);

	if (algorithm==3)
	{
		dijkstra(source2);
		BellmanFord(source2);
    	//PARENT array 
    	int parent[noVer];
    	temp2=formoving;

    	for (int i = 0; i < noVer; i++)
    	{
        	parent[i]=0;
    	}

    	while (temp2->prev!=NULL)
    	{
        	parent[temp2->vertex-1]=temp2->prev->vertex;
        	temp2=temp2->prev;
    	}
    
    	height(2);
		distance(30);
    	printf("Do you want to start traversing your shortest path? (1/0) \n");
    	distance(30);
    	printf("-->");
		scanf("%d",&R1);
	
		if(R1==1)
		{
			system("cls");
			traverse(source2,parent);
		}
		else
		{
			exit(0);
		}
	}
	

	
    
}


void get_heuristic(int i)
{
	//getting heuristic for vertices
    if (algorithm==3)
	{
		system("cls");
    	height(3);
	}
	
	printf("\n");
    for(;i<=noVer;i++)
	{	
        distance(30);
        printf("Enter hueristic from %d to destination = ",i);
        scanf("%d",&graph[i-1].heuristic);
	}
}



void Astar(int source1)
{
	get_heuristic(1);
    //Calling astarmain function
    AstarMain(source1);

}

//fillgraph function
void fillgraph()
{
	int i;
	
    //entering info in the listofvertex and adding edges
	for(i=1;i<=noVer;i++)
	{
		createEdge(i);
	}

	system("cls");  					// clear screen
	height(3);
	distance(72);
	
	printf(" Displaying Graph ");
	height(3);
	
    //printing graph
	for(i=1;i<=noVer;i++)
	{
		distance(30);
		displayConnection(i);
	}
}

// display formatting functions
void height(int h)
{
	for (int i = 0; i <h; i++)
	{
		printf("\n");
	}
}


void distance(int d)
{
	for (int i = 0; i <d ; i++)
	{
		printf(" ");
	}
}

void rectangle(int n, int m) 
{ 
    int i, j; 
    for (i = 1; i <= n; i++) 
    { 
        for (j = 1; j <= m; j++) 
        { 
            if (i==1 || i==n || j==1 || (j==m && i!=4 && i!=5))             
                printf("*");
            else if (i==4 && j==(m-44))
                printf("*");      
            else if (i==5 && j==(m-29))
                printf("*");                       
            else if (i==4 && j==50)
                printf("Modified Shortestpath algorithms for multiple");
            else if (i==5 && j==59)
                printf("dynamically changing scenerios");
            else
                printf(" ");             
        } 
        printf("\n"); 
    }   
} 
    
void frontend()
{
	int rows = 9, columns = 155,i=0; 
    printf("\t\t\t\t\t\t\t            MINOR 1 \n");
    printf("\n"); 
    rectangle(rows, columns); 
    printf("\n"); 
    printf("APPROVED BY:   \t\t\t\t\t\t\t\t\t                                             SUBMITTED BY:\n" );
    printf("Mr. Amrendra Tripathi [MENTOR]  \t\t\t\t\t\t                                             Shubham Bhatnagar [151]\n" );
    printf("Dr. Deepshikha Bhargava [HOD]    \t\t\t\t\t\t                                             Yashvardhan Singh Nathawat [192]\n" );
    printf("  \t\t\t\t\t\t\t\t\t\t                                             Harsh Upparwal [198]" );
	height(2);
	printf("Press 1 to continue ");
	scanf("%d",&i);
	while (1)
	{
		if(i==1)
		{
			break;
		}
		else
		{
			height(1);
			printf("Press 1 to continue ");
			scanf("%d",&i);
		}
		
	}
	
}




//______________________________________________________MAIN FUNCTION___________________________________________________________
int main()
{	
	system("cls");   // clearing screen.
	frontend();
	system("cls");   // clearing screen.

    int source,i=0;
    
	height(2);
	distance(72);
	
	printf("Please Enter The Graph !!! \n");

	height(3);
	distance(30);
	
	printf("Number Of Vertex In The Graph = ?\n");
	distance(30);
	scanf("%d",&noVer);
	
	height(1);
	distance(30);
	printf("Total Number Of Vertices In The Graph = %d\n",noVer);
	delay(2);

	system("cls");   // clearing screen.
	

    //created listofvertex array of size noVer
    graph=(struct listofvertex *)calloc(noVer,sizeof(struct listofvertex));

    //entering graph CALL THE FILL GRAPH FUNCTION TO ENTER NODES AND WEIGHTS BETWEEN THEM
    fillgraph();

	delay(5);

	system("cls");
	height(3);
	distance(30);
    // ENTER THE SOURCE VERTEX OF YOUR GRAPH
    printf("Please Enter the source vertex among the %d vertices of Graph\n",noVer);
	distance(30);
	printf("--> ");
	scanf("%d",&source);

	height(1);
	distance(30);
	
	//ENTER DESTINATION VERTEX 
	printf("Please Enter the destination vertex among the %d vertex of Graph \n",noVer);
	distance(30);
	printf("--> ");
	scanf("%d",&destination);
	system("cls");


    // giving option of algos
	while (1)
	{
		height(3);
		distance(72);
		printf(" SELECT ALGORITHM TO FIND SHORTEST PATH ");
		height(2);
		distance(30);
		printf(" PRESS 1 to find shortest path using DIJKSTRA \n");
		height(2);
		distance(30);
    	printf(" PRESS 2 to find shortest path using BELLMAN FORD \n");
		height(2);
		distance(30);
    	printf(" PRESS 3 to find shortest path using A-STAR \n");
		height(2);
		distance(30);
		printf(" PRESS 4 to EXIT  \n");
		height(2);
		distance(30);
		printf(" --> ");
    	scanf("%d",&i);
    	algorithm=i;
    	//switch case
    	switch (i)
    	{
        	case 1:dijkstra(source);
					break;
        	case 2:BellmanFord(source);
                	break;
        	case 3:Astar(source);
            	    break;
					
			case 4:exit(0);
             
        	default:height(2);
					distance(30);
					printf("INVALID CHOICE");
                	break;
   		}
	}
	
    return 0;
}
