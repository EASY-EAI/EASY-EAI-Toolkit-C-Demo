#include <stdio.h>

#include <string.h>
#include "json_parser.h"


int main(void)
{
	int ret = -1;
	char *strJson = "\
{\
\"ProtocolVer\" : 1,\
\"EquipmentID\" : \"LMOA-01-0000D19FEA9242F65C12\",\
\"NewVer\" : \"1.0.007\",\
\"FileType\" : \"update Packet\",\
\"TotalFiles\" : 3,\
\"FileList\": [\
{\
\"url\": \"http://update.com/packet/file1\",\
\"md5\": \"3d621eee986b543d50953eca35f19a55\",\
\"number\" : 1\
},\
{\
\"url\": \"http://update.com/packet/file2\",\
\"md5\": \"12345678901234567890123456789012\",\
\"number\" : 2\
},\
{\
\"url\": \"http://update.com/packet/file3\",\
\"md5\": \"12345678901234567890123456789012\",\
\"number\" : 3\
}\
],\
\"user_data\":\
{\
\"id\" : 47,\
\"name\": \"gzlmo\"\
}\
}";
	
	
	printf("======================================= json string ================================\n");
	printf("%s\n", strJson);
	printf("======================================= json string ================================\n");
	
	int protocolVer = get_int32_from_json(strJson, "ProtocolVer");
	printf("read protocolVer = %d\n", protocolVer);
	
	char equipmentID[256] = {0};
	ret = get_string_from_json(strJson, "EquipmentID", equipmentID, sizeof(equipmentID));
	if((0 < ret)&&(ret <= sizeof(equipmentID))){
		printf("read equipmentID = %s\n", equipmentID);
	}
	
	char user_data[1024] = {0};
	char user_id = 0;
	char user_name[64] = {0};
	ret = get_object_from_json(strJson, "user_data", user_data, sizeof(user_data));
	if((0 < ret)&&(ret <= sizeof(user_data))){
		printf("\n===== >> get user_data succ << =====\n");
		user_id = get_int32_from_json(user_data, "id");
		printf("===== >> read id   = %d\n", user_id);
		ret = get_string_from_json(user_data, "name", user_name, sizeof(user_name));
		printf("===== >> read name = %s\n", user_name);
	}
	
	int listSize = get_list_size_from_json(strJson, "FileList");
	printf("\nread FileListSize = %d\n", listSize);
	int i;
	int number = 0;
	char url[256] = {0};
	char md5[256] = {0};
	for(i = 0; i < listSize; i++)
	{
		number = get_int32_from_list(strJson, "FileList", i, "number");
		printf("=== number :%d\n", number);
		ret = get_string_from_list(strJson, "FileList", i, "url", url, sizeof(url));
		if((0 < ret)&&(ret <= sizeof(url))){
			printf("=== url: %s\n", url);
		}
		ret = get_string_from_list(strJson, "FileList", i, "md5", md5, sizeof(md5));
		if((0 < ret)&&(ret <= sizeof(md5))){
			printf("=== md5: %s\n", md5);
		}
	}
	
	printf("\n\n===========  start to create json string ==================\n");	
	add_json_cache("name","string","gzlmo");	//正常使用
	add_json_cache("id","number","0");			//正常使用
	add_json_cache("version","number","");		//非正常使用，value为0
	add_json_cache("","string","66667");		//非正常使用，该条json不会被加入缓存
	add_json_cache("pwd","","787729");			//非正常使用，type默认为string
	char newJsonStr[2048] = {0};
	create_json_string(newJsonStr, sizeof(newJsonStr));
	printf("newJsonStr = %s\n",newJsonStr);
	
	return 0;
}
