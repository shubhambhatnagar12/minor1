#include <stdio.h>
#include<stdlib.h>

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




// FILL GRAPH FUNCTION


void fillgraph(){
	
	int i;
	
	for(i=1;i<=noVer;i++)
	{
		createEdge(i);
	}

	for(i=1;i<=noVer;i++)
	{
		displayConnection(i);
		printf("\n");
	}
}



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



int main(){
	
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
	
	// APPLYING THE DIJKSTRA ON GRAPH ENTERED ABOVE
	
	dijkstra(source);

	return 0;
	
}
