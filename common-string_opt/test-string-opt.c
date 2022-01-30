#include <stdio.h>

#include "string_opt.h"


int main(void)
{

	char strHex[8] = "FFFc";
    uint32_t val1 = hexToi(strHex);
	printf("hexStr : %s  transform to value,  value :  %d(0x%04x) \n", strHex, val1, val1);

	char hexNum[16] = {0};
	uint32_t val2 = 65532;
    val_to_hexStr(hexNum, val2, 10);
	printf("value  : %d transform to hexStr, hexStr : %s \n", val2, hexNum);

	char sentence[128]="temperature:37, height:177cm, weight:70kg";
	uint32_t temperature = read_val_from_str(sentence, "temperature:");
	uint32_t height      = read_val_from_str(sentence, "height:");
	uint32_t weight      = read_val_from_str(sentence, "weight:");
	printf("your temperature = %d, height = %d, weight = %d\n", temperature, height, weight);

	return 0;
}
