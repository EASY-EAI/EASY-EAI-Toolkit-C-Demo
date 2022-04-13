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

	ao_init(RK_SAMPLE_FMT_S16, 16000, 2, 100);
	if(argc == 2){
		ao_start(argv[1]);
	}

	g_run++;
	while(g_run) {
		usleep(100000);
	}
	//播放结束前按CTRL+C执行ao_stop()打断当前播放
	ao_stop();
	printf("ao_stop\n");

	//重新播放
	if(argc == 2){
		ao_start(argv[1]);
	}

	g_run++;
	while(g_run) {
		usleep(100000);
	}

	ao_exit();

	return 0;
}
