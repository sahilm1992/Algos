//WEIGHTED JOB SCHEDULING
// maximize profit -- schedule jobs to maximize net profit

#include<time.h>
#include<stdlib.h>
struct JOB
{

	int start;
	int finish;
	int id;
	int profit;

}; 
typedef struct JOB job;

typedef int (*compare)(job a , job b);

job *createJobs(int num)

{
	job *jobArray = (job*)malloc(sizeof(job)*num);
	srand(time(NULL));

	int i =0 ; 
	while(i<num)
		{
			jobArray[i].start=rand()%100;
			jobArray[i].finish =  jobArray[i].start + rand()%100+1;		
			jobArray[i].profit = rand()%20;			
			jobArray[i].id = i;
			i++;
		}

	return jobArray;
}

int compfinish( job a ,  job b)
{
if(a.finish<=b.finish)
	return 0;
else 
	return 1;
}

int partition(job *array, int beg , int end, compare comp)
{

int j = beg;
int i = j-1;

while(j<end)
	{

		if(comp(array[j],array[end])==0)
			{
				i++;
				job temp = array[j];
				array[j] = array[i];
				array[i] = temp;

			}
	j++;

	}

	job temp = array[i+1];
	array[i+1] = array[end];
	array[end] = temp;



return (i+1);

}

void quickSort(job* array,int beg , int end, compare comp)
{
if(beg<end)
	{
		int part = partition(array, beg, end,comp);
		quickSort(array,beg, part-1,comp);
		quickSort(array, part+1, end,comp);

	}

}


void printJobs(job *array,int size)
{
if(array==NULL)
	return;
int i =0 ; 

		printf("\n\n\tID:\tstart,\tfinish");
while(i<size)
	{
		printf(" \n\t(%d:\t%d,\t%d, \t{P%d })" , array[i].id,array[i].start,array[i].finish ,array[i].profit);
		i++;
	}

}


int getRecentNonOverlappingIndex(job *array,int curIndex)
{
int i = curIndex -1;
while(i>=0)
	{
		if(array[i].finish<=array[curIndex].start)
			return i;
		i--;
	}
return -1;
}

int max(int a , int b)
{
return (a>b)?a:b;
}

int profitScheduling(job *array  ,int right , int *DP)
{
if(DP[right]!=-1000)
	return DP[right];
else
   {
	int nonOverlapIndex =getRecentNonOverlappingIndex(array,right);
	if(nonOverlapIndex!=-1)
		DP[right]= max(array[right].profit + profitScheduling(array,nonOverlapIndex,DP) , profitScheduling( array, right-1,DP)) ;
	else
		DP[right]= max(array[right].profit, profitScheduling( array, right-1,DP)) ;
	
	return DP[right];		
   }
}

int profit_Sch_iter(job*array,int len, int *DP)
{

int i =1;
for(i=1;i<=len;i++)
	{
		int nonOverlapIndex =getRecentNonOverlappingIndex(array,i);
			if(nonOverlapIndex!=-1)
				DP[i]= max( array[i].profit + DP[nonOverlapIndex] , DP[i-1]);
			else
				DP[i] =max(array[i].profit ,DP[i-1]);

	}


return DP[len];
}



int main()
{
	int size =4;
	job *jobArray = createJobs(size);
	printf("\n JOBS :");
	printJobs(jobArray,size);
	
	int *DP =(int*)malloc(sizeof(int)*size);
//	memset(DP,-1,sizeof(int)*size);
	int i =0 ; 
	while(i<size)
	{
		DP[i] = -1000;
		i++;	
	}compare comp = compfinish;
	quickSort(jobArray, 0, size-1, comp);

	printf("\n SORTED ACC TO dead TIME (INC)");
	printJobs(jobArray,size);

	
	DP[0]=jobArray[0].profit;
	printf("\n \n REC %d ", profitScheduling(jobArray,size-1,DP));

	i =0 ; 
	while(i<size)
	{
		DP[i] = -1000;
		i++;	
	}

	DP[0]=jobArray[0].profit;
	printf("\n ITER %d \n", profit_Sch_iter(jobArray,size-1, DP));
	
}
