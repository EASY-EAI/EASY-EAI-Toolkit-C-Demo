#include <sys/time.h>

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "geometry.h"

int main(void)
{
	s32Point_t pointA = {2,7};
	s32Point_t pointB = {61, 1126};
	
	s32Rect_t Rect = {3, 8, 1080, 1920};
	
	if(point_in_rect(pointA, Rect)){
		printf("point A(%d, %d) is in Rect\n", pointA.x, pointA.y);
	}else{
		printf("point A(%d, %d) is not in Rect\n", pointA.x, pointA.y);		
	}
	
	if(point_in_rect(pointB, Rect)){
		printf("point B(%d, %d) is in Rect\n", pointB.x, pointB.y);
	}else{
		printf("point B(%d, %d) is not in Rect\n", pointB.x, pointB.y);		
	}

	return 0;
}
