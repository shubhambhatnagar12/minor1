#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<stdbool.h>
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

int noVer;                                  //declaration of global variables
struct listofvertex * graph;
struct nodeForAStar * final,*formoving;
int size=1;
int destination;
struct nodeForAStar *PQ;


// edge creation function
void createEdge(int i)
{
    int j,iteration,x,w;
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
	printf("vertex %d is connected to ",i);
	while(k!=NULL)
	{
		printf("%d (Weight= %d ) ",k->vertex,k->weight);

		k=k->next;
	}
    printf("\n");
	
}



                                    /*  DIJKSTRA FUNCTIONS */

// SETISEMPTY FUNCTION TO CHECK WHETHER THE SET IS EMPTY OR NOT.
// IT RETURNS A BOOLEAN VALUE ACCORDING TO THE SITUATION OF SET. IF SET IS EMPTY IT WILL RETURN TRUE 

bool setisempty(int set[]){

	  int counter=0;
	  for(int i=0;i<noVer;i++){
	  	if(set[i]!=0)
		  counter++;
	  }
	  if(counter==noVer)
	  return false;
	  else
	  return true;
}

// MIN FUNCTION WHICH RETURNS THE VERTEX IN THE WEIGHT ARRAY HAVING MINIMUM VALUE


int min(int weights[],int set[]){
	
	int initial=0;
	int counter=0;
	int temp[noVer]; 
	
	//COPYING THE WEIGHT ARRAY IN TEMP
	
	for(int i=0;i<noVer;i++){
		temp[i]=weights[i];
	}
	
	// NOW WE REMOVE THOSE VERTEX TO BE CHOSEN BY OUR FUNCTION WHICH HAVE BEEN ALREADY CHOSEN BEFORE AND SENT TO SET
	
	for(int i=0;i<noVer;i++){
		if(set[i]!=0)
			temp[set[i]-1]=INF;
	}
	
	for(int i=0;i<noVer;i++){
		if(temp[i]==INF)
		counter++;
	}
	if(counter!=noVer){
	
	// SELECTING THE MIN. VERTEX
	
	for(int i=1;i<noVer;i++){
		if(temp[i]<temp[initial])
		initial=i;
	}
	
	return(initial+1);
	}
	else
	return 0;
}

// NOADJVERTICES FUNCTION TO FIND THE NUMBER OF VERTEX ADJACENT TO THE MIN. VERTEX
//IT RETURNS TOTAL NUMBER OF ADJACENT VERTICES
// THE FUNCTION IS SIMILAR TO DISPLAY DUNCTION

int noadjvertices(int u){
	
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

int adjvertices(int u, int j){
	struct node* k=NULL;
	k=graph[u-1].edges;
	for(int i=0;i<j;i++){
		k=k->next;
	}
	

	return(k->vertex);
}

// ADJVERTICESWEIGHT FUNCTION TO RETURN THE WEIGHTS OF ALL THE ADJACENT VERTICES OF MIN. VERTEX

int adjverticesweight(int u, int j){
	struct node* k=NULL;
	k=graph[u-1].edges;
	for(int i=0;i<j;i++){
		k=k->next;
	}
	

	return(k->weight);
}

// PATH VERTEX TO SHOW THE MINIMUM WEIGHT PATH FROM SOURCE TO DESTINATION VERTEX

int path(int destination, int parent[], int source){
	if(destination==source){
	printf("%d <-- ",destination);
	return 0;
	}
	
	if(destination!=source){
		printf("%d <-- ",destination);
		return(path(parent[destination-1],parent,source));
	}
}


//DIJKSTRA FUNCTION CONTAINING RELAX FUNCTION OF ALGO AND INITIALISING ALL WEIGHT AND SET TO INFINITE AND ZERO


void dijkstra(int source){
	
	int weights[noVer];
	int parent[noVer];
	int set[noVer];
	int u;
	int check=0;

// INITIALISING SINGLE SOURCE BY ADDING INFINITE IN ALL THE OTHER VERTICES IN WEIGHT ARRAY

	for(int i=0;i<noVer;i++){
		weights[i]=INF;
		set[i]=0;
	}

	weights[source-1]=0;
	parent[source-1]=0;

// MAIN ITERATING LOOP

	while(setisempty(set)){
	
		u=min(weights,set);
		
		if(u!=0){
		
		set[u-1]=u;
	
		
		// FINDING ADJACENT VERTICES TO U
	
	
		int noadj = noadjvertices(u);
		
		if(noadj!=0){
		
		int adjvert[noadj];
		int adjvertweight[noadj];
		for(int j=0;j<noadj;j++){
			adjvert[j]=adjvertices(u,j);
			adjvertweight[j]=adjverticesweight(u,j);
		}
		
	
		// RELAX ITERATION
	
		for(int c=0;c<noadj;c++){
			//relax(u,adjvert[c],adjvertweight[c]);
			if(weights[adjvert[c]-1]>(weights[u-1]+adjvertweight[c])){
				weights[adjvert[c]-1]=weights[u-1]+adjvertweight[c];
				parent[adjvert[c]-1]=u;
			}
		}
		
		}

	}
	else{
	break;
	}


}

	path(destination,parent,source);
	
}





                                    /*  BELLMAN FORD functions  */

void BellmanFord(int source)
{
    int weights[noVer];
    int parent[noVer];

  // OVER ESTIMATION
    for (int i = 0; i < noVer; i++){ //initialise all dist to INT_MAX
        weights[i]  = INF;
      parent[i] = 0;
    }
    weights[source-1] = 0;
    

  // RELAXATION 
    for (int r = 0; r < noVer-1; r++)
    {
        for (int u = 1; u <= noVer; u++)
        {
            	
		// FINDING ADJACENT VERTICES TO U		
		
		int noadj = noadjvertices(u);
		
		if(noadj!=0){
		
		int adjvert[noadj];
		int adjvertweight[noadj];
		for(int j=0;j<noadj;j++){
			adjvert[j]=adjvertices(u,j);
			adjvertweight[j]=adjverticesweight(u,j);
		}	
		
		// RELAX ITERATION
	
		for(int c=0;c<noadj;c++){
			//relax(u,adjvert[c],adjvertweight[c]);
			if(weights[adjvert[c]-1]>(weights[u-1]+adjvertweight[c])){
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
		
		if(noadj!=0){
		
		int adjvert[noadj];
		int adjvertweight[noadj];
		for(int j=0;j<noadj;j++){
			adjvert[j]=adjvertices(u,j);
			adjvertweight[j]=adjverticesweight(u,j);
		}
		
		// NEGATIVE CYCLE CHECK
	
		for(int c=0;c<noadj;c++){
			if(weights[adjvert[c]-1]>(weights[u-1]+adjvertweight[c])){
				printf("Graph contains negative weight cycle");
			}
		}
	}
} 
	path(destination,parent,source);
}




                                        /*  A-STAR FUNCTIONS */


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
void AstarMain()
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
    while (!(PQ[1].vertex==destination))
    {
        deleteFromHeap();
        createArrayForPQ(graph[(formoving->vertex)-1],graph[(formoving->vertex)-1].noOfNodeConnected);
    }

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

}




void Astar()
{
    int i,src,des;

    //getting heuristic for vertices
    for(i=1;i<=noVer;i++)
	{
        printf("enter hueristic from %d to destination ",i);
        scanf("%d",&graph[i-1].heuristic);

        printf("hueristic of %d = %d\n",i,graph[i-1].heuristic);
	}

    //Calling astar function
    AstarMain();

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
}




//fillgraph function
void fillgraph(){
	
	int i;
	
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
}





int main()
{
    int source,i=0;
    printf("Enter the graph \n");
	printf("no. of vertex in graph = ");
	scanf("%d",&noVer);
	printf("no. of vertex in the graph = %d\n",noVer);

    //created listofvertex array of size noVer
    graph=(struct listofvertex *)calloc(noVer,sizeof(struct listofvertex));

    //entering graph CALL THE FILL GRAPH FUNCTION TO ENTER NODES AND WEIGHTS BETWEEN THEM
    fillgraph();

    // ENTER THE SOURCE VERTEX OF YOUR GRAPH
    printf("Please Enter the source vertex among the %d vertex of Graph",noVer);
	scanf("%d",&source);
	printf("source = %d \n", source);
	
	//getting destination vertex
    printf("enter destination vertex");
    scanf("%d",&destination);

    // giving option of algos
    printf(" PRESS 1 to find shortest path using DIJKSTRA \n");
    printf(" PRESS 2 to find shortest path using BELLMAN FORD \n");
    printf(" PRESS 3 to find shortest path using A-STAR \n");

    scanf("%d",&i);
    //switch case
    switch (i)
    {
        case 1:dijkstra(source);
                break;
        case 2:BellmanFord(source);
                break;
        case 3:Astar();
                break;
        default:printf("INVALID CHOICE");
                break;
    }

    return 0;
}
