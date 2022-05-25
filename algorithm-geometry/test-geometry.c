#include <sys/time.h>

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "geometry.h"

int main(void)
{
	double ratio = 0.0;
	// 矩形A 和 矩形B 矩形C
	s32Rect_t RectA = {50, 50, 70, 120};
	s32Rect_t RectB = {50, 100, 100, 200};
	s32Rect_t RectC = {300, 300, 450, 500};
	
	printf(">>>>>>>>\n");
	// 两两判断矩形是否相交(切)
	if(rect_is_intersect(RectA, RectB)){
		printf("RectA and RectB is intersect\n");
	}else{
		printf("RectA and RectB is not intersect\n");
	}
	
	if(rect_is_intersect(RectB, RectC)){
		printf("RectB and RectC is intersect\n");
	}else{
		printf("RectB and RectC is not intersect\n");
	}
	
	printf(">>>>>>>>\n");
	// 计算[矩形A]和[矩形B]相交部分面积
	printf("RectA and RectB intersect square is %d\n", calc_rect_intersect_square(RectA, RectB));
	// 计算[矩形B]和[矩形C]相交部分面积
	printf("RectB and RectC intersect square is %d\n", calc_rect_intersect_square(RectB, RectC));

	printf(">>>>>>>>\n");
	// 计算[两矩形相交部分面积]与[小矩形面积]之比
	ratio = calc_intersect_of_min_rect(RectA, RectB);
	printf("[RectA & RectB] intersect square of min rect square is :%lf\n", ratio);
	ratio = calc_intersect_of_min_rect(RectB, RectC);
	printf("[RectB & RectC] intersect square of min rect square is :%lf\n", ratio);

	printf(">>>>>>>>\n");
	// 计算两矩形的交并比
	ratio = calc_intersect_of_union(RectA, RectB);
	printf("[RectA & RectB] IoU is :%lf\n", ratio);
	ratio = calc_intersect_of_union(RectB, RectC);
	printf("[RectB & RectC] IoU is :%lf\n", ratio);
	
	return 0;
}
