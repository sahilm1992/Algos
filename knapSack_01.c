//

// Program to solve 0-1 Knapsack problem using Dynamic Programming
#include<stdlib.h>
#include<time.h>

struct Object{
int profit;
int weight;
int id;
};

typedef struct Object object;

object createObject(int profit,int weight, int id)
{

	object *obj = (object*)malloc(sizeof(object));
	obj->profit=profit;
	obj->weight=weight;
	obj->id=id;

	return *obj;

}


void printObjects(object *array, int size)
{
	printf("\n");
	printf ("\n ID \tPROFIT \t\tWEIGHT");
	int i=0 ; 
	for(i=0;i<size;i++)
		printf ("\n%d\t%d\t\t%d",array[i].id,array[i].profit ,array[i].weight );


}


object *createObjects(int num)
{
	object *ptr = (object*) malloc(sizeof(object)*num);

	srand(time(NULL));
	int i =0 ; 
	while(i<num)
	{

		int p = (rand()%10)+1;
		int weight = (rand()%7)+1 ;

		ptr[i]=createObject(p,weight,i);
		i++;

	}
return ptr;
}


int max(int a , int b)
{
return (a>b)?a:b;
}

struct Point{
	int n ;
	int W
	};
typedef struct Point point;



int get01KnapSack(object *items, int i , int W, int **DP )

{

	if(i==0 || W==0)
		{
			DP[i][W]=0;
			
			return DP[i][W];
		}
	if(DP[i][W]!=-1000)
		{
	
			return DP[i][W];	
		}
	else
		{
			
			if(items[i-1].weight <=W)		
			{
			
			DP[i][W]=max(items[i-1].profit + get01KnapSack(items,i-1,W-items[i-1].weight ,DP),get01KnapSack(items,i-1,W,DP ));
			
			
	
			}
			else
				DP[i][W] =get01KnapSack(items,i-1,W,DP);


			return DP[i][W];
		}
	
}


void printSolKnapSack(object  *items,int**DP,int n, int W)
{
printf("\n SOLUTION ids: \n");
int i = n;
int j = W;
while(i>0)
	{

		if(DP[i][j] ==(DP[i-1][j-items[i-1].weight] + items[i-1].profit))
			{
				printf(" %d ",items[i-1].id);
				j = j - items[i-1].weight;
			}

	i--;
	}


}

int main()
{
	srand(time(NULL));

	int numItems = rand()%5+2;
	int knapSackSize = rand()%14;
	object *items = createObjects(numItems);
	printf("\n KNAPSACK SIZE %d " ,knapSackSize);
	printObjects(items,numItems);
	int **DPmatrix = (int**)malloc(sizeof(int*)*(numItems+1));

	int i =0 ;
	while(i<=numItems)
		{
			DPmatrix[i] = (int*)malloc(sizeof(int)*(1+knapSackSize));
					
			int j=0;
			while(j<=knapSackSize)
				{

				DPmatrix[i][j]=-1000; 
				j++;
				}
			i++;
		
		}
	int knapVal = get01KnapSack(items, numItems, knapSackSize, DPmatrix);

	printf ( "\n\n MAX = %d" ,knapVal);
	printSolKnapSack(items,DPmatrix,numItems,knapSackSize);

}	
