#include <stdio.h>
#include<stdlib.h>
struct graph
{
	int vertex;
	struct graph* next;
};

void createEdge(struct graph** arrofLL, int i)
{
	int j=0;
	int a;
	struct graph* k=NULL,*L=NULL;
	printf("Is there vertex connected to %d 1/0\n",i);
	scanf("%d",&a);

	while(a!=0)
	{
		int x;

		if(j==0)
		{
			arrofLL[i-1]=(struct graph*)malloc(sizeof(struct graph));
			printf("HEYY the vertex %d is connected to which vertex\n",i);
			scanf("%d",&x);

			arrofLL[i-1]->vertex=x;
			arrofLL[i-1]->next=NULL;
			L=arrofLL[i-1];
			j++;
		}
		else{
			
			L->next=(struct graph*)malloc(sizeof(struct graph));
			printf("the vertex %d is connected to which vertex\n",i);
			scanf("%d",&x);

            L->next->vertex=x;
            L->next->next=NULL;
            L=L->next;
// 			k->vertex=x;
// 			k->next=NULL;

// 			L->next=k;
// 			L=k;
// 			free(k);
 			j++;
		}

		printf("Is there more vertex connected to %d 1/0\n",i);
		scanf("%d",&a);
	}
}

void displayConnection(struct graph** arrofLL, int i){
	struct graph* k=NULL,*L=NULL;
	k=arrofLL[i-1];
	printf("vertex %d is connected to \n",i);
	while(k!=NULL)
	{
		printf("%d, ",k->vertex);

		L=k->next;
		k=NULL;
		k=L;
	}
	
}

int main( ){
	int noVer,i;
	printf("no. of vertex=?\n");
	scanf("%d",&noVer);
	printf("no. of vertex=%d",noVer);
	struct graph* arrofLL[noVer];

	for(i=1;i<=noVer;i++)
	{
		arrofLL[i]=NULL;
	}

	for(i=1;i<=noVer;i++)
	{
		createEdge(arrofLL,i);
	}

	for(i=1;i<=noVer;i++)
	{
		displayConnection(arrofLL,i);
	}

	return 0;
}
