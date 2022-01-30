#include <unistd.h>
#include <stdio.h>

#include <string.h>
#include "file_opt.h"



int main(void)
{	
	char dirPath[256] = "/userdata/Demo/testDir/myDir";
	printf("before add '/' : %s\n", dirPath);
    bool add_succ = add_bias_for_dirpath(dirPath);
	if(add_succ){
		printf("after  add '/' : %s\n", dirPath);
	}else{
		printf("after  add '/' : %s\n", dirPath);	
	}
	
	bool mk_succ = make_directory(dirPath);
	if(mk_succ){
		printf("create dir succ\n");
	}else{
		printf("create dir faild\n");		
	}
	
	return 0;
}
