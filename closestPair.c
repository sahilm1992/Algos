//
// To get closest pair of points in a 2 Dimensional Plane in O(nlogn ) time complexity
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<limits.h>


struct Point{
int x;
int y;
};
typedef struct Point point;

point  createPoint(int x , int y)
{
	point *pt= (point*)malloc(sizeof(point));
	pt->x=x;
	pt->y=y;
	return *pt;
}
typedef int (*compare)(point , point);


point * createPoints(int num , point *pArray)
{
	
	srand(time(NULL));
	int i = 0  ; 
	while(i<num)
		{
		int x = rand()%100;
		int y = rand()%100;
		pArray[i++] = createPoint(x,y);
		}

}



void printPoints(point *pArray  , int size)
{
	printf("\n\n");
	int i =0 ; 
	while(i<size)
	{
	printf(" ( %d ,%d ) , ", pArray[i].x, pArray[i].y);
	i++;
	}


}

int compX(point a,point b)
{
if((a.x <= b.x))
	return 0;
else
return 2;

}

int compY(point a,point b)
{
if((a.y <= b.y))
	return 0;
else
return 2;

}

int partition(point *pArray , int beg , int end,  compare comp)
	{
		int j = beg;
		int i = j-1;

		while(j<end)
			{
				if(comp(pArray[j],pArray[end])<1)	
					{	
						i++;
						point p = pArray[j];		
						pArray[j] = pArray[i];
						pArray[i] = p;

					}
				j++;

			}

		point p = pArray[i+1];	
		pArray[i+1] = pArray[end];
		pArray[end] = p;

		return (i+1);
	}

void quickSort( point *pArray , int begin , int end, compare comp )
{

if(begin<end)
	{
	int part = partition(pArray, begin , end,comp);
	quickSort(pArray, begin , part-1,comp);
	quickSort(pArray, part+1, end,comp);
	}

}

float distance( point a , point b)
{
return 	sqrt((a.x-b.x)*(a.x-b.x) +(a.y-b.y)*(a.y-b.y));

}

point * brute(point *pArray, int beg , int end)
{
point*closestPoints = (point*)malloc(sizeof(point)*2);
int i = 0; 
float min=100000;

for(i=beg;i<end;i++)
	{
		int j = i+1;

		for(;j<=end;j++)
			{	float dist =distance(pArray[i], pArray[j]);
				if(dist <min)	
					{	min = dist ;
						closestPoints[0].x= pArray[i].x;closestPoints[0].y= pArray[i].y;
		
						closestPoints[1].x= pArray[j].x;closestPoints[1].y= pArray[j].y;
		
					}
			}
	}
return closestPoints;
}


int getStripMin(point *strip, int size , float dMin)
{
point*closestPoints = (point*)malloc(sizeof(point)*2);
closestPoints[0].x= -INT_MAX/100;
closestPoints[0].y= -INT_MAX/100;
		
closestPoints[1].x= INT_MAX/100;
closestPoints[1].y= INT_MAX/100;
int i= 0 ; 
for(i=0;i<=size-1;i++)
	{
		int j =i+1;	
		for(j=i+1;j<size && (strip[j].y - strip[i].y)< dMin;j++)
			{
				float dist =distance(strip[i],strip[j]);
					if(dist<dMin)
				{
					dMin = dist;
					closestPoints[0].x= strip[i].x;
					closestPoints[0].y= strip[i].y;
		
					closestPoints[1].x= strip[j].x;
					closestPoints[1].y= strip[j].y;
			

				}
			}

	}

return closestPoints;
}



point *closestPointsosestPair( point *pXSort,point *pYSort, int l , int r   )
{

	
	if((r-l)<=3)
		{
			point *bruteclosestPoints = brute(pXSort,l,r);			
			return bruteclosestPoints;
		}

	int midIndex = (l) +(r-l)/2;
	point midP = pXSort[midIndex];

	point* leftclosestPoints = closestPointsosestPair(pXSort,pYSort, l , midIndex);

	point *rightclosestPoints= closestPointsosestPair(pXSort,pYSort, midIndex+1,r);

	int leftDistance = distance(leftclosestPoints[0],leftclosestPoints[1]);
	int rightDistance = distance(rightclosestPoints[0],rightclosestPoints[1]);
	point *finalMinclosestPoints;
	float dmin = (leftDistance<=rightDistance)?leftDistance:rightDistance;

	if(dmin==leftDistance)
		finalMinclosestPoints = leftclosestPoints;
	else
		finalMinclosestPoints = rightclosestPoints;

	point *strip = (point*) malloc(sizeof(point)*(r-l+1));

	int i= l;
	int stripSize=0;
	while(i<=r)
		{
			if((	midP.x -pYSort[i].x)<dmin)
					strip[stripSize++]= pYSort[i];

			i++;
		}

	point * stripclosestPoints =getStripMin(strip,stripSize,dmin);

	float stripDist = distance(stripclosestPoints[0],stripclosestPoints[1]);

	if(stripDist<dmin)
		finalMinclosestPoints = stripclosestPoints;


	return finalMinclosestPoints;
}

/*
void initPoints(point *pArray)
{
	pArray[0].x=1;
	pArray[0].y=2;

	pArray[1].x=5;
	pArray[1].y=4;

	pArray[2].x=1;
	pArray[2].y=1;

	pArray[3].x=2;
	pArray[3].y=2;

	pArray[4].x=1;
	pArray[4].y=3;

	pArray[5].x=5;
	pArray[5].y=6;

}
*/

int main()

{
	int size =100	;
	point *pArray = (point*)malloc(sizeof(point)* size);

	//initPoints(pArray);
	createPoints(size,pArray);		
	printPoints(pArray,size);

	point *pXSort = (point*)malloc(sizeof(point)* size);
	point *pYSort = (point*)malloc(sizeof(point)* size);


	memcpy(pXSort, pArray,sizeof(point)*size);
	memcpy(pYSort, pArray,sizeof(point)*size);
	free(pArray);
	compare comp = compX;
	quickSort(pXSort,0,size-1,comp);
	comp = compY;
	quickSort(pYSort,0,size-1,comp);

	printPoints(pXSort,size);
	printPoints(pYSort,size);

	point *closestPoints =closestPointsosestPair(pXSort,pYSort,0,size-1);
	printf("\n  \n\n\n %f (%d %d)   : ( %d ,%d) ",distance(closestPoints[0],closestPoints[1])  , closestPoints[0].x ,closestPoints[0].y , closestPoints[1].x ,closestPoints[1].y);

	point *VclosestPoints=brute(pXSort,0,size-1);
	printf("\n  \n\n\n %f (%d %d)   : ( %d ,%d) ",distance(VclosestPoints[0],VclosestPoints[1])  , VclosestPoints[0].x ,VclosestPoints[0].y , VclosestPoints[1].x ,VclosestPoints[1].y);


	return 0 ; 
}

