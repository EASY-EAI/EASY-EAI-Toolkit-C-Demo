#include <stdio.h>

#include "https_request.h"

#define FILE_PATH    "/userdata/Demo/upgrade.bin"

int main(void)
{
	set_customer_crt("/userdata/customer.crt");
	
	clear_multipart();
	add_multipart_form_data("name", "gzlmo");
	add_multipart_form_data("id", "888888");
	add_multipart_form_data("pwd", "123456");
	
	char res[4096] = {0};
	printf("===================================================================== : %s\n",res);
	send_data_to_Http("192.168.3.191:50000", "/add", res, sizeof(res));
	//send_data_to_Https("192.168.3.191:50000", "/add", res, sizeof(res));
	printf("result : %s\n",res);
	
	//send_json_to_Http("192.168.3.191:50000", "/add", "{ \"name\" : \"gzlmo\" }", res, sizeof(res));
	//send_json_to_Https("192.168.3.191:50000", "/add", "{ \"name\" : \"gzlmo\" }", res, sizeof(res));
	
	//get_file_from_http("192.168.3.191:50000", "/pic", FILE_PATH);
	//get_file_from_https("192.168.3.191:50000", "/pic", FILE_PATH);
	
	return 0;
}
