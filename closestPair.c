//OM
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct Point{
int x;
int y;
};
typedef struct Point point;

int qSort();

point  createPoint(int x , int y)
{
point *pt= (point*)malloc(sizeof(point));
pt->x=x;
pt->y=y;
return *pt;
}

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
	int i =0 ; 
	while(i<size)
	{
	printf(" ( %d ,%d ) , ", pArray[i].x, pArray[i].y);
	i++;
	}


}

int main()

{
int size =10;
point *pArray = (point*)malloc(sizeof(size));
createPoints(size,pArray);

printPoints(pArray,size);

return 0 ; 
}
