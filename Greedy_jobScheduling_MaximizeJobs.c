
#include<time.h>
#include<stdlib.h>
struct JOB
{

	int id;
	int start;
	int finish;

};
typedef struct JOB job;

job *createJobs(int num)

{
job *jobArray = (job*)malloc(sizeof(job)*num);
srand(time(NULL));

int i =0 ; 
while(i<num)
	{
		jobArray[i].start=rand()%100;
		jobArray[i].finish =  jobArray[i].start + rand()%100+1;		
		jobArray[i].id = i;
		i++;
	}

return jobArray;
}

int partition(job *array, int beg , int end)
{

int j = beg;
int i = j-1;

while(j<end)
	{

		if(array[j].finish<=array[end].finish)
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

void quickSort(job* array,int beg , int end)
{
if(beg<end)
	{
		int part = partition(array, beg, end);
		quickSort(array,beg, part-1);
		quickSort(array, part+1, end);

	}

}


job *getMaximumCardinalityJobs(job *jobs , int size)
{
if(size==0)
	return NULL;
job *maxCardinalityArray = (job*)malloc(sizeof(job)*size);


// insert first job  always
int i = 0 ; 
maxCardinalityArray[0] = jobs[0];	
int latFinish = jobs[0].finish;
i++;
int count =1;

while(i<size)
	{
		if(jobs[i].start>=latFinish)
			{
				maxCardinalityArray[count]= jobs[i];
				latFinish = jobs[i].finish;			
				count++;
			}



		i++;
	}


return maxCardinalityArray;
}

void printJobs(job *array,int size)
{
if(array==NULL)
	return;
int i =0 ; 

		printf("\n\n\tID:\tSTART,\tFINISH");
while(i<size)
	{
		printf(" \n\t(%d:\t%d,\t%d)" , array[i].id,array[i].start,array[i].finish);
		i++;
	}

}

int main()
{
	int size =10;
	job *jobArray = createJobs(size);
	printf("\n JOBS :");
	printJobs(jobArray,size);
	quickSort(jobArray, 0, size-1);
	printf("\n SORTED ACC TO FINISH TIME (INC)");
	printJobs(jobArray,size);

	job *maxCardinalityArray =getMaximumCardinalityJobs(jobArray,size);
	
	printf("\n MAX CARDINALITY");
	printJobs(maxCardinalityArray,size);


}		
