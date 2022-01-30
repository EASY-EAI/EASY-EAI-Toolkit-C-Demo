#include <unistd.h>
#include <stdio.h>

#include <string.h>
#include "data_check.h"



int main(void)
{
	char md5[40];
	char CSC_Data[8] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
	char BCC_Data[8] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
	char CRC_Data[8] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
	//char BCC_Data[8] = {0x18, 0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11};
	
	memset(md5, 0, sizeof(md5));
	if(NULL != create_md5_code("file", "/userdata/Demo/Demo")){
		memcpy(md5, create_md5_code("file", "/userdata/Demo/Demo"), sizeof(md5));
		printf("file md5: %s\n",md5);
	}
	
	memset(md5, 0, sizeof(md5));	
	if(NULL != create_md5_code("string", "/userdata/Demo/Demo")){
		memcpy(md5, create_md5_code("string", "/userdata/Demo/Demo"), sizeof(md5));
		printf("string md5: %s\n",md5);
	}
	
	printf("csc : 0x%02x\n", check_sum_check((uint8_t *)CSC_Data, sizeof(CSC_Data)));
	printf("bcc : 0x%02x\n", block_check_character((uint8_t *)BCC_Data, sizeof(BCC_Data)));	
	printf("crc : 0x%02x\n", CRC_8((uint8_t *)CRC_Data, sizeof(CRC_Data)));
	return 0;
}
