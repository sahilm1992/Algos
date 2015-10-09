//huffman

#include<stdlib.h>
#include<time.h>
struct chars{
char val;
int freq;
};

typedef struct chars letter;

void heapify(letter *arr ,int i ,int size)
{

	int left = 2*i+1;
	int right = 2*i+2;
	int min=i;
	if(left<size)
		{
			if(arr[left].freq<arr[i].freq)
				{
					min = left;
				}

		}
	if(right<size)
			{
			if(arr[right].freq<arr[min].freq)
					min = right;
			}

	if(i!=min)
		{
			letter temp = arr[i];
			arr[i]=arr[min];
			arr[min]=temp;
			heapify(arr,min,size);
		}


}

void buildMinHeap(letter* arr, int size)
{
int i = (size-1)/2;
while(i>=0)
	{
		heapify(arr,i,size);
		i--;
	}


}

void initLetters(letter *p,int size)
{
	p[0].val='a';
	p[0].freq=12;


	p[1].val='b';
	p[1].freq=30;


	p[2].val='c';
	p[2].freq=20;


	p[3].val='d';
	p[3].freq=8;

	//p[4].val='i';
	//p[4].freq=16;

	//p[5].val='g';
	//p[5].freq=14;


}

void printArray(letter *Array  , int size)
{
	printf("\n");

	int i =0 ; 
	while(i<size)
	{
		printf(" %c %d ...  " , Array[i].val ,  Array[i].freq);
		i++;
	}


}

letter* insertInHeap(letter *Array,letter object,int *size)
{
Array =(letter*) realloc(Array,sizeof(letter)*(*size+1));
*size= *size+1;
Array[*size-1]=object;

int i = (*size-1);
int parent = (i-1)/2;

while(parent>=0)
	{
		if(Array[i].freq< Array[parent].freq)
			{
				letter temp = Array[i];
				Array[i] = Array[parent];
				Array[parent]=temp;

				i = parent;
				parent = (parent-1)/2;
			}
		else 
			break;

	}


return Array;
}



int main()
{
	int numChar =4;
	letter *letterArray  = (letter*)malloc(sizeof(letter)*numChar);
	initLetters(letterArray,numChar);
	printArray(letterArray,numChar);
	buildMinHeap(letterArray,numChar);
	printArray(letterArray,numChar);
	letter object ={'h',10};
	letterArray=insertInHeap(letterArray,object,&numChar);

	 letter object2 ={'m',14};
	letterArray=insertInHeap(letterArray,object2,&numChar);


	letter object3 ={'n',100};
	letterArray=insertInHeap(letterArray,object3,&numChar);
	printArray(letterArray,numChar);
	
}
