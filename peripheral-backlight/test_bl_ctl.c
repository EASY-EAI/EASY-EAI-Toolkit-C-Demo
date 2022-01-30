#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "backlight.h"

#define	BACKLIGHT	"/sys/class/backlight/backlight/brightness"
#define	LOW_LEVEL	30
int main(int argc, char *argv[])
{
	int c = 100;
	static uint16_t level = LOW_LEVEL;

	while(c--) {
		level += 10;
		if (level >= 255) {
			level = LOW_LEVEL;
		}
		printf("setting bl level:%d\n", level);
		set_backlight(BACKLIGHT, level);
		usleep(100*1000);
	}

	return 0;
}
