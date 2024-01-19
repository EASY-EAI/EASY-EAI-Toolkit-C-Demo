#include "stdio.h"
#include "gpio.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
static const GPIOCfg_t gpioCfg_tab[] = {
	{
		.pinName   = "GPIO3_B2",
		.direction = DIR_OUTPUT,
		.val       = 0,
	}, {
		.pinName   = "GPIO3_B3",
		.direction = DIR_OUTPUT,
		.val       = 0,
	}, {
		.pinName   = "GPIO3_C4",
		.direction = DIR_INPUT,
		.val       = 0,
	}
};

int main(int argc, char **argv)
{
    gpio_init(gpioCfg_tab, ARRAY_SIZE(gpioCfg_tab));
    
    pin_out_val("GPIO3_B2", 0);
    pin_out_val("GPIO3_B3", 1);
    
    int val = read_pin_val("GPIO3_C4");
    printf("GPIO3_C4 val : %d\n", val);

	return 0;
}
