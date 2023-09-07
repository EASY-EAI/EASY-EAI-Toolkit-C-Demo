#include <unistd.h>
#include <stdio.h>

#include "audio.h"
#include "wavHeader.h"

// 根据[常见]采样格式计算位深度
static uint16_t bitDepth(snd_pcm_format_t fmt)
{
    uint16_t depth;
    switch (fmt){
        case SND_PCM_FORMAT_UNKNOWN:
            depth = 0;  break;
        case SND_PCM_FORMAT_S8:
        case SND_PCM_FORMAT_U8:
            depth = 8;  break;
        case SND_PCM_FORMAT_S16_LE:
        case SND_PCM_FORMAT_S16_BE:
        case SND_PCM_FORMAT_U16_LE:
        case SND_PCM_FORMAT_U16_BE:
            depth = 16;  break;
        case SND_PCM_FORMAT_S24_LE:
        case SND_PCM_FORMAT_S24_BE:
        case SND_PCM_FORMAT_U24_LE:
        case SND_PCM_FORMAT_U24_BE:
            depth = 24;  break;
        case SND_PCM_FORMAT_S32_LE:
        case SND_PCM_FORMAT_S32_BE:
        case SND_PCM_FORMAT_U32_LE:
        case SND_PCM_FORMAT_U32_BE:
        case SND_PCM_FORMAT_FLOAT_LE:
        case SND_PCM_FORMAT_FLOAT_BE:
            depth = 32;  break;
        case SND_PCM_FORMAT_FLOAT64_LE:
        case SND_PCM_FORMAT_FLOAT64_BE:
            depth = 64;  break;
        default: 
            depth = 0; break;
    }
    return depth;
}

// 根据[常见]采样格式转换为WAV文件格式
static uint16_t wavFmt(snd_pcm_format_t fmt)
{
    uint16_t wavFmt;
    switch (fmt){
        case SND_PCM_FORMAT_UNKNOWN:
            wavFmt = WAV_FMT_UNKNOW;  break;
        case SND_PCM_FORMAT_S8:
        case SND_PCM_FORMAT_U8:
        case SND_PCM_FORMAT_S16_LE:
        case SND_PCM_FORMAT_S16_BE:
        case SND_PCM_FORMAT_U16_LE:
        case SND_PCM_FORMAT_U16_BE:
        case SND_PCM_FORMAT_S24_LE:
        case SND_PCM_FORMAT_S24_BE:
        case SND_PCM_FORMAT_U24_LE:
        case SND_PCM_FORMAT_U24_BE:
        case SND_PCM_FORMAT_S32_LE:
        case SND_PCM_FORMAT_S32_BE:
        case SND_PCM_FORMAT_U32_LE:
        case SND_PCM_FORMAT_U32_BE:
            wavFmt = WAV_FMT_PCM; break;
        case SND_PCM_FORMAT_FLOAT_LE:
        case SND_PCM_FORMAT_FLOAT_BE:
        case SND_PCM_FORMAT_FLOAT64_LE:
        case SND_PCM_FORMAT_FLOAT64_BE:
            wavFmt = WAV_FMT_FLOAT; break;
        default: 
            wavFmt = WAV_FMT_UNKNOW; break;
    }
    return wavFmt;
}

// 准备WAV格式参数
#define DURATION_TIME 5
void prepare_wav_params(wav_format *wav, uint32_t sampleRate, uint16_t channels, snd_pcm_format_t fmt)
{
    uint16_t frameSize = channels * (bitDepth(fmt)>>3); //一帧音频数据所占的内存大小
    uint32_t pcm1sSize = sampleRate * frameSize;   //一秒音频数据所占的内存大小
    wav->format.fmt_id   = FMT;
    wav->format.fmt_size = LE_INT(16);
    wav->format.fmt      = LE_SHORT(wavFmt(fmt));
    wav->format.channels = LE_SHORT(channels);
    wav->format.sample_rate     = LE_INT(sampleRate);
    wav->format.byte_rate       = LE_INT(pcm1sSize);
    wav->format.block_align     = LE_SHORT(frameSize);
    wav->format.bits_per_sample = LE_SHORT(bitDepth(fmt));

    uint32_t dataSize = DURATION_TIME * pcm1sSize;
    wav->data.data_id   = DATA;
    wav->data.data_size = LE_INT(dataSize);
    
    wav->head.id     = RIFF;
    wav->head.size   = LE_INT(36 + dataSize);
    wav->head.format = WAVE;
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
    uint16_t channels   = 2;        //通道数

    // 1: 打开WAV格式文件
    int fd = open(argv[1], O_CREAT|O_WRONLY|O_TRUNC, 0777);
    if(-1 == fd) {
        perror("open() error");
        exit(1);
    }

    // 2: 写WAV格式的文件头
    wav_format *wav = calloc(1, sizeof(wav_format));
    prepare_wav_params(wav, sampleRate, channels, format);
    write(fd, &wav->head, sizeof(wav->head));
    write(fd, &wav->format, sizeof(wav->format));
    write(fd, &wav->data, sizeof(wav->data));

    // 3: 初始化声卡
	ai_init(sampleRate, channels, format);

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

	return 0;
}

