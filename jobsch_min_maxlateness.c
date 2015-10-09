
#include<time.h>
#include<stdlib.h>
struct JOB
{

	int id;
	int dur;
	int dead;

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
			jobArray[i].dur=rand()%100;
			jobArray[i].dead =  jobArray[i].dur + rand()%100+1;		
			jobArray[i].id = i;
			i++;
		}

	return jobArray;
}

int compDead( job a ,  job b)
{
if(a.dead<=b.dead)
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


job *getMaximumCardinalityJobs(job *jobs , int size)
{
if(size==0)
	return NULL;
job *maxCardinalityArray = (job*)malloc(sizeof(job)*size);


// insert first job  always
int i = 0 ; 
maxCardinalityArray[0] = jobs[0];	
int latest = jobs[0].dur;
i++;
int count =1;

while(i<size)
	{
		//if(jobs[i].dur>=latdead)
		//	{
				maxCardinalityArray[count]= jobs[i];
				//latdead =latdead jobs[i].dead;			
				count++;
		//	}



		i++;
	}


return maxCardinalityArray;
}

void printJobs(job *array,int size)
{
if(array==NULL)
	return;
int i =0 ; 

		printf("\n\n\tID:\tdur,\tdead");
while(i<size)
	{
		printf(" \n\t(%d:\t%d,\t%d)" , array[i].id,array[i].dur,array[i].dead);
		i++;
	}

}

int main()
{
	int size =10;
	job *jobArray = createJobs(size);
	printf("\n JOBS :");
	printJobs(jobArray,size);
	compare comp = compDead;
	quickSort(jobArray, 0, size-1, comp);
	printf("\n SORTED ACC TO dead TIME (INC)");
	printJobs(jobArray,size);

	job *maxCardinalityArray =getMaximumCardinalityJobs(jobArray,size);
	
	printf("\n MAX CARDINALITY");
	printJobs(maxCardinalityArray,size);
	
	free(jobArray);
	free(maxCardinalityArray);


}		
