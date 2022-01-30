#include <sys/time.h>

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "rtsp.h"

FILE *g_RecordFp = NULL;
int g_IFrame_cout = 0;
void open_record_file(char *fileName)
{
	if(g_RecordFp)
		return ;
	
	g_RecordFp = fopen(fileName, "w");
	printf("==== Start Recode file[%s] ====\n", fileName);
}

int write_frame_to_file(VideoNodeDesc *pNodeDesc, uint8_t *pData)
{
	int ret = 0;
	if(NULL == g_RecordFp)
		return -1;
	
	ret = fwrite(pData, 1, pNodeDesc->dwDataLen, g_RecordFp);
	
	return ret;
}

void close_record_file()
{
	if(NULL == g_RecordFp)
		return ;
	
	fclose(g_RecordFp);
	g_RecordFp = NULL;
	
	printf("========== End Recode ==========\n");
}

uint64_t get_time_stamp()
{
    struct timeval tv;	
	gettimeofday(&tv, NULL);	
	return (uint64_t)tv.tv_sec;
}
void open_record_file_by_time(uint64_t time_stamp)
{
	char fileName[128] = {0};
	sprintf(fileName, "%llu.264",time_stamp);
	open_record_file(fileName);
}

//  ==============================  以上是rtsp非必要代码  ==============================
//  ===============================  以下是rtsp必要代码  ===============================
void myPrintFunction(const char *strMsg)
{
	printf("[myPrintFunction]----%s", strMsg);
}

int32_t VideoHandle(void *pCapturer, VideoNodeDesc *pNodeDesc, uint8_t *pData)
{	
	if(1 == pNodeDesc->bySubType){	
		if(0 == g_IFrame_cout){
			open_record_file_by_time(get_time_stamp());
		}
		printf("--- [%d] Iframe --- Width = %u, Height = %u\n", g_IFrame_cout, pNodeDesc->dwWidth, pNodeDesc->dwHeight);
		g_IFrame_cout++;
	}
	
	write_frame_to_file(pNodeDesc, pData);
	
	if(5 == g_IFrame_cout){
		g_IFrame_cout = 0;
		close_record_file();
	}
	
	return 0;
}

int main(void)
{
	const char *testProgName = "myRtsp";
	const char *testRtspUrl = "rtsp://192.168.1.65";
	const char *testRtspUserName = "admin";
	const char *testRtspPassword = "a12345678";
	
	RTSP_Chn_t rtspChn;
	memset(&rtspChn, 0, sizeof(RTSP_Chn_t));
	
	rtspChn.uDecChn = 0;
	
	memset(rtspChn.progName, 0, sizeof(rtspChn.progName));
	memcpy(rtspChn.progName, testProgName, strlen(testProgName));
	
	memset(rtspChn.rtspUrl, 0, sizeof(rtspChn.rtspUrl));
	memcpy(rtspChn.rtspUrl, testRtspUrl, strlen(testRtspUrl));
	
	memset(rtspChn.userName, 0, sizeof(rtspChn.userName));
	memcpy(rtspChn.userName, testRtspUserName, strlen(testRtspUserName));
	
	memset(rtspChn.password, 0, sizeof(rtspChn.password));
	memcpy(rtspChn.password, testRtspPassword, strlen(testRtspPassword));
	
	set_rtsp_client_printf(myPrintFunction);
	
	set_rtsp_client_video_callback(VideoHandle, NULL);
	
	create_rtsp_client_channel(&rtspChn);

	return 0;
}
