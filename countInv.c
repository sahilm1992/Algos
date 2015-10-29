//
// to count number of inversions in a 1 D Array.
// i, j is in an inversion if A[i] >A[j] for i<j.

// ARRAY 8 2 1 4 5 
/*
ELEMENT 8 ,2 is an inversion.
similary 2,1
and 8,5 also etc

*/

#include<stdlib.h>
int merge(int *arr,int beg , int  mid , int end)
{
int *temp = (int*)calloc((end-mid+1),sizeof(int));

int i =beg ; 
int j =mid+1;
int count=0;

int inver=0;
while(i<=mid && j<=end)
	{
		if(arr[i]<=arr[j])
			{
			temp[count]=arr[i];
			i++;count++;
			}



		else if(arr[i]>arr[j])
			{inver+=mid-i+1;
			temp[count]=arr[j];
			j++;count++;
			}

	}

while(i<=mid)
		temp[count++]=arr[i++];


while(j<=end)
	{
		temp[count++]=arr[j++];
	}

i =beg;
count=0;
while(i<=end)
	arr[i++]=temp[count++];

return inver;

}
/*
2463		 1832

24     63		18 	32
 


 1	 0	 0	 1 
2 4 	6 3 	1 8 	3 2

0   0	0 0	0 0	0 0 
*/

int  mergeSort(int *arr, int beg , int end)
{
int inv = 0 ; 
if(beg<end)
	{
		int mid = (beg+end)/2;
		inv +=mergeSort(arr, beg,	mid);
		inv +mergeSort(arr,mid+1,end);
		inv+=merge(arr,beg,mid,end);	

	}

return inv;
}

void printArray(int *arr, int size)
{
printf("\n");
int i =0 ; 
while(i<size)
	{
		printf (" %d ", arr[i]);
		i++;
	}

}

int main()

{

int arr[]={6,5,1,2,9};
printArray(arr,sizeof(arr)/sizeof(arr[0]));


printf("\n %d Number of Inversion\n\n " ,mergeSort(arr,0,sizeof(arr)/sizeof(arr[0]) -1));
printArray(arr,sizeof(arr)/sizeof(arr[0]));


}
