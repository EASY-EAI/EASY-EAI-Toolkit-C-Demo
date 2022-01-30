#include <stdio.h>

#include <string.h>
#include "base64.h"



int main(void)
{
	char *cStr = "my name is hao";
	char base64_data[1024] = {0};
	char src_string[1024] = {0};
	
	memset(base64_data, 0, sizeof(base64_data));
	base64_encode(base64_data, cStr, strlen(cStr));
	printf("encode data : %s\n", base64_data);	
	base64_decode(src_string, sizeof(src_string), base64_data);
	printf("source string : %s\n", src_string);

	//用于验证即便数据中间有0x00，还原出来的数据也不会从0x00处断掉
	char num_data[8] = {0x67, 0x88, 0x70, '\0', '\r', '\n', 0x73, 0x73};
	char decode_data[8] = {0};
	memset(base64_data, 0, sizeof(base64_data));
	base64_encode(base64_data, num_data, sizeof(num_data));
	printf("encode data : %s\n", base64_data);
	base64_decode(decode_data, sizeof(decode_data), base64_data);
	printf("source string : 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n", 
			decode_data[0], decode_data[1], decode_data[2], decode_data[3], decode_data[4], decode_data[5], decode_data[6], decode_data[7]);

	return 0;
}
