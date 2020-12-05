#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 99999

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
	printf("vertex %d is connected to ",i);
	while(k!=NULL)
	{
		printf("%d, ",k->vertex);
		printf("(with weight %d), ",k->weight);
		k=k->next;
	}
    printf("\n");
	
}





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




//BELLMAN FORD ALGORITHM

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


int main()
{
  
 	int i,source;
	printf("no. of vertex in graph = ");
	scanf("%d",&noVer);
	printf("no. of vertex=%d\n",noVer);

	//created listofvertex array of size noVer
    graph=(struct listofvertex *)calloc(noVer,sizeof(struct listofvertex)); 
	
	fillgraph(); // CALL THE FILL GRAPH FUNCTION TO ENTER NODES AND WEIGHTS BETWEEN THEM
	
	printf("Please Enter the source vertex among the %d vertex of Graph",noVer);
	scanf("%d",&source); // ENTER THE SOURCE VERTEX OF YOUR GRAPH
	printf("source = %d \n", source);
    
    //getting destination vertex
    printf("enter destination vertex");
    scanf("%d",&destination);
    
    BellmanFord(source); // 0 is the source node
    return 0;
}

