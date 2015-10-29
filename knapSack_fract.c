//Program : knapsack Fractional 

#include<stdlib.h>
#include<time.h>

struct Object{
float profit;
float weight;
int id;
};
typedef struct Object object;



int partition(object *array, int beg , int end)
{

int j = beg;
int i = j-1;

while(j<end)
	{

		if(array[j].profit/array[j].weight>array[end].profit/array[end].weight)
			{
				i++;
				object temp = array[j];
				array[j] = array[i];
				array[i] = temp;

			}
	j++;

	}

	object temp = array[i+1];
	array[i+1] = array[end];
	array[end] = temp;



return (i+1);

}

void quickSort(object* array,int beg , int end)
{
if(beg<end)
	{
		int part = partition(array, beg, end);
		quickSort(array,beg, part-1);
		quickSort(array, part+1, end);

	}

}



void printObjects(object *array, int size)
{
	printf("\n");
	printf ("\n ID \tPROFIT \t\tWEIGHT\t \tP/W");
	int i=0 ; 
	for(i=0;i<size;i++)
		printf ("\n%d\t%f\t%f\t%f",array[i].id,array[i].profit ,array[i].weight , (float)(array[i].profit)/(array[i].weight));


}


object* getKnapSackObjects(object *inArray, int len, int knapSize, int *numReturn)
{
quickSort(inArray,0,len-1);
printObjects(inArray,len);

int i =0 ; 
object *resultArray = (object*)malloc(sizeof(object)*len);
int count = 0 ; 

for (i=0;i<len;i++)
	{
		if(knapSize==0)
			break;
		else
		{
			float PperW= (float)inArray[i].profit/inArray[i].weight;
			float wtUsed =0;
			if(inArray[i].weight<=knapSize)
				{
					wtUsed = inArray[i].weight;
				}
			else
				{
					//fractional
					wtUsed = knapSize ;		
				}

			resultArray[count].weight = wtUsed;
			resultArray[count].id  =  inArray[i].id;
			resultArray[count].profit = PperW*wtUsed;
			knapSize = knapSize - wtUsed;
			count++;
		}
	}
*numReturn =count;
return resultArray;

}

object createObject(float profit,float weight, int id)
{

	object *obj = (object*)malloc(sizeof(object));
	obj->profit=profit;
	obj->weight=weight;
	obj->id=id;

	return *obj;

}



object *createObjects(int num)
{
	object *ptr = (object*) malloc(sizeof(object)*num);

	srand(time(NULL));
	int i =0 ; 
	while(i<num)
	{

		float p = (rand()%10)+1;
		float weight = (float)(rand()%7)+1 ;

		ptr[i]=createObject(p,weight,i);
		i++;

	}
return ptr;
}

void printResult(object *array, int size)
{
	printf("\n Solution");
	int i=0 ; 
	float profit =0 ; 
	printf ("\n ID \tPROFIT/WEIGHT \t WEIGHT");

	for(i=0;i<size;i++)
		{
			printf ("\n%d \t%f\t %f",array[i].id,array[i].profit/array[i].weight,array[i].weight );
			profit+= array[i].profit;

		}
	printf ("\n\n NET PROFIT %f \n"  , profit);
	

}



int main()

{
	int num =20;
	srand(time(NULL));
	int knapSize=rand()%100;
 	object *items = createObjects(num);
	printf(" \n  KNAPSACK SIZE ::: %d ", knapSize);
	printObjects(items,num);
	int numEleminSack = 0 ; 
	object *result = getKnapSackObjects(items,num,knapSize,&numEleminSack);
	printResult(result,numEleminSack);
}	
