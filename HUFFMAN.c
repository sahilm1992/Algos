//huffman

#include<stdlib.h>
#include<time.h>
struct chars{
char val;
int freq;
struct chars *left;
struct chars *right;
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
	p[1].freq=41;


	p[2].val='c';
	p[2].freq=19;


	p[3].val='d';
	p[3].freq=28;

	int i =0; 
	while(i<size)
		{
			p[i].left=NULL;
			p[i].right=NULL;
			i++;

		}

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

letter *extractMin(letter **Array,int *size)
{

	if(*size==0)
		{
		printf("\nHEAP UNDERFLOW");
		return NULL;
		}
	letter *min = (letter*)malloc(sizeof(letter));
	min->freq = Array[0][0].freq;
	min->val = Array[0][0].val;
	min->left = Array[0][0].left;
	min->right=Array[0][0].right;
	
	Array[0][0] =Array[0][*size-1];

	*size = *size -1;
	heapify(Array[0],0,*size);

	*Array = (letter*)realloc(*Array, sizeof(letter)*(*size));	

	return min;
}


letter *createNode(int freq, char val)
{
	letter *node = (letter*)malloc(sizeof(letter));
	node->freq=freq;
	node->val=val;
	node->left=NULL;
	node->right=NULL;
	return node;

}

void printTree(letter *tree)
{

if(tree)
	{
		printTree(tree->left);
		printf("(%c %d) ,  " ,tree->val  , tree->freq);
		printTree(tree->right);
	}


}


void printHuffmanCodes(letter *tree, int level, int arr[])
{
	if(tree==NULL)
		return;

	if(!(tree->left || tree->right))
		{

			int i=0;
			printf("\n %c ", tree->val);
			while(tree->val!='*' && i<level )
			{			//LEAF print it
				printf( " %d ",arr[i]);
				i++;			
			}
			
		}

	if(tree->left )
		{
			arr[level]=0;
			printHuffmanCodes(tree->left,level+1,arr);				
		}



	if((tree->right))
		{
			arr[level]=1;
			printHuffmanCodes(tree->right,level+1,arr);		
		}

}

void createHuffManCode(letter *letterArray , int size)
{

	int *arr =(int*)malloc(sizeof(int)*size);
int i = 0 ;
while(1)
	{
		if(size == 1)
			break ;

		letter *min1 = extractMin(&letterArray,&size);
		letter *min2= extractMin(&letterArray,&size);
		letter *newNode = createNode(min1->freq+min2->freq,'*');
		newNode->left= min1;
		newNode->right = min2;
		letterArray = insertInHeap(letterArray,newNode[0],&size);
	}
	printf("\nTREE  INORDER\n");
	letter *root = extractMin(&letterArray, &size);
	printTree(root);
	printf("\nCODES\n");
	printHuffmanCodes(root,0,arr);
}



int main()
{
	int numChar =4;
	letter *letterArray  = (letter*)malloc(sizeof(letter)*numChar);
	initLetters(letterArray,numChar);
	printArray(letterArray,numChar);
	buildMinHeap(letterArray,numChar);
	printArray(letterArray,numChar);
	/*letter object ={'h',10};
	letterArray=insertInHeap(letterArray,object,&numChar);

	 letter object2 ={'m',14};
	letterArray=insertInHeap(letterArray,object2,&numChar);


	letter object3 ={'n',100};
	letterArray=insertInHeap(letterArray,object3,&numChar);

	letter *min = extractMin(&letterArray,&numChar);
	printf("\nMIN : %c %d  ... \n" ,min->val,min->freq);	 
		printArray(letterArray,numChar);

	min = extractMin(&letterArray,&numChar);
	printf("\nMIN : %c %d  ... \n" ,min->val,min->freq);	 

	printArray(letterArray,numChar);

	min = extractMin(&letterArray,&numChar);
	printf("\nMIN : %c %d  ... \n" ,min->val,min->freq);	 
	printArray(letterArray,numChar);

	min = extractMin(&letterArray,&numChar);
	if (min!=NULL)
		printf("\nMIN : %c %d  ... \n" ,min->val,min->freq);	 

	printArray(letterArray,numChar);

	min = extractMin(&letterArray,&numChar);
	if (min!=NULL)
		printf("\nMIN : %c %d  ... \n" ,min->val,min->freq);	 
	

	*/

	printArray(letterArray,numChar);
	
	createHuffManCode(letterArray,numChar);
}
