#include <sys/time.h>

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "geometry.h"

int main(void)
{
	s32Rect_t Rect = {0};
	
	// 矩形A 和 矩形B
	s32Rect_t RectA = {50, 100, 70, 120};
	s32Rect_t RectB = {50, 100, 100, 200};

	// 分别计算两矩形面积
	int32_t Sa = calc_rect_square(RectA);
	printf("RectA square = %d\n", Sa);
	int32_t Sb = calc_rect_square(RectB);
	printf("RectB square = %d\n", Sb);
	
	// 比较两矩形框面积大小
	Rect = min_rect(RectA, RectB);
	printf("the min Rect is {%d, %d, %d, %d}\n", Rect.left, Rect.top, Rect.right, Rect.bottom);
	Rect = max_rect(RectA, RectB);
	printf("the max Rect is {%d, %d, %d, %d}\n", Rect.left, Rect.top, Rect.right, Rect.bottom);

	return 0;
}
