#include <unistd.h>
#include <stdio.h>

#include "audio.h"
#include "wavHeader.h"

// 根据[常见]采样格式转换为WAV文件格式
static uint16_t wavFmt(snd_pcm_format_t fmt)
{
    uint16_t wavFmt;
    switch (fmt){
        case SND_PCM_FORMAT_UNKNOWN:
            wavFmt = WAV_FMT_UNKNOW;  break;
        case SND_PCM_FORMAT_S8:
        case SND_PCM_FORMAT_U8:
        case SND_PCM_FORMAT_S16:
        case SND_PCM_FORMAT_U16:
        case SND_PCM_FORMAT_S24:
        case SND_PCM_FORMAT_U24:
        case SND_PCM_FORMAT_S32:
        case SND_PCM_FORMAT_U32:
            wavFmt = WAV_FMT_PCM; break;
        case SND_PCM_FORMAT_FLOAT:
        case SND_PCM_FORMAT_FLOAT64:
            wavFmt = WAV_FMT_FLOAT; break;
        default: 
            wavFmt = WAV_FMT_UNKNOW; break;
    }
    return wavFmt;
}
static wav_format *create_wavInfo(uint32_t sampleRate, uint16_t channels, snd_pcm_format_t fmt, int32_t recTimes)
{
    wav_format *pWavIno = calloc(1, sizeof(wav_format));
    if(NULL == pWavIno){
        printf("create wavInfo faild!\n");
        return NULL;
    }
    
    size_t bitDepth = snd_pcm_format_physical_width(fmt);
    uint16_t frameSize = channels * (bitDepth>>3); //一帧音频数据所占的内存大小
    uint32_t pcm1sSize = sampleRate * frameSize;   //一秒音频数据所占的内存大小
    pWavIno->format.fmt_id   = FMT;
    pWavIno->format.fmt_size = LE_INT(16);
    pWavIno->format.fmt      = LE_SHORT(wavFmt(fmt));
    pWavIno->format.channels = LE_SHORT(channels);
    pWavIno->format.sample_rate     = LE_INT(sampleRate);
    pWavIno->format.byte_rate       = LE_INT(pcm1sSize);
    pWavIno->format.block_align     = LE_SHORT(frameSize);
    pWavIno->format.bits_per_sample = LE_SHORT(bitDepth);

    uint32_t dataSize = recTimes * pcm1sSize;
    pWavIno->data.data_id   = DATA;
    pWavIno->data.data_size = LE_INT(dataSize);
    
    pWavIno->head.id     = RIFF;
    pWavIno->head.size   = LE_INT(36 + dataSize);
    pWavIno->head.format = WAVE;

    return pWavIno;
}


// ============================== 以上代码与声卡采集无关 ==============================
// ====================================================================================
// ============================ 以下代码为声卡采集调用逻辑 ============================

int main(int argc, char *argv[])
{
    if(argc != 2) {
        printf("Usage: %s <wav-file>\n", argv[0]);
        exit(1);
    }

    // PCM音频3大关键参数：
    snd_pcm_format_t format = SND_PCM_FORMAT_FLOAT_LE;   //采样格式
    uint32_t sampleRate = 44100;    //采样率
    uint16_t channels   = 1;        //通道数

    // 1: 打开WAV格式文件
    int fd = open(argv[1], O_CREAT|O_WRONLY|O_TRUNC, 0777);
    if(-1 == fd) {
        perror("open() error");
        exit(1);
    }

    // 2: 写WAV格式的文件头
    wav_format *wav = create_wavInfo(sampleRate, channels, format, 10);
    if(NULL == wav){
        perror("create_wavInfo() error");
        exit(1);
    }
    write(fd, &wav->head, sizeof(wav->head));
    write(fd, &wav->format, sizeof(wav->format));
    write(fd, &wav->data, sizeof(wav->data));

    // 3: 初始化声卡
	ai_init(0, sampleRate, channels, format);   //帧率参数填0，pcm采样周期以最大周期的1/4作为标准

    // 4: 读取声卡数据并写入wav文件。
    uint32_t total_bytes = wav->data.data_size;
    uint32_t nwrite = 0;
    while(0 < total_bytes) {
        uint32_t n = MIN(total_bytes, ai_pcmPeriodSize());
        uint32_t readSize = ai_readpcmData(n);
    
        nwrite = write(fd, ai_pcmBufptr(), readSize);
        total_bytes -= readSize;
    }

	ai_exit();
    free(wav);

	return 0;
}

