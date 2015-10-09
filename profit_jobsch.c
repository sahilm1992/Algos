//WEIGHTED JOB SCHEDULING

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


int main()
{
	int size =15;
	job *jobArray = createJobs(size);
	printf("\n JOBS :");
	printJobs(jobArray,size);
	compare comp = compfinish;
	quickSort(jobArray, 0, size-1, comp);
	printf("\n SORTED ACC TO dead TIME (INC)");
	printJobs(jobArray,size);


}
