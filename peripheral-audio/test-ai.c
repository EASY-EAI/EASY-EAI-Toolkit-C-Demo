#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include <audio.h>

static int g_run = 0;
static void sigterm_handler(int sig) {
	fprintf(stderr, "signal %d\n", sig);
	g_run = 0;
}

int main(int argc, char *argv[])
{
	signal(SIGINT, sigterm_handler);

	ai_init(RK_SAMPLE_FMT_S16, 16000, 2, 100);
	if(argc == 2){
		ai_start(argv[1]);
	}

	g_run++;
	while(g_run) {
		usleep(100000);
	}

	//结束录制
	ai_stop();
	printf("ai_stop\n");

	ai_exit();

	return 0;
}

