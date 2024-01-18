#include <unistd.h>
#include <stdio.h>

#include "audio.h"
#include "wavHeader.h"

static int get_wavHeader_info(int fd, wav_format *wav)
{
    int n1 = read(fd, &wav->head, sizeof(wav->head));
    int n2 = read(fd, &wav->format, sizeof(wav->format));
    int n3 = read(fd, &wav->data, sizeof(wav->data));

    if(n1 != sizeof(wav->head) ||
       n2 != sizeof(wav->format) ||
       n3 != sizeof(wav->data))
    {
        fprintf(stderr, "get_wav_header_info() failed\n");
        return -1;
    }

    return 0;
}

// ============================== 以上代码与声卡播放无关 ==============================
// ====================================================================================
// ============================ 以下代码为声卡播放调用逻辑 ============================
static snd_pcm_format_t get_pcmFormat(wav_format *pWavInfo)
{
    snd_pcm_format_t snd_format = SND_PCM_FORMAT_UNKNOWN;
    
    if((LE_SHORT(pWavInfo->format.fmt) != WAV_FMT_PCM) &&
       (LE_SHORT(pWavInfo->format.fmt) != WAV_FMT_FLOAT))
        return snd_format;

    switch(LE_SHORT(pWavInfo->format.bits_per_sample))
    {
        case 64:
            snd_format = SND_PCM_FORMAT_FLOAT64; break;
        case 32:    //同是32位还有: SND_PCM_FORMAT_U32、SND_PCM_FORMAT_S32
            snd_format = SND_PCM_FORMAT_FLOAT; break;
        case 24:    //同是24位还有: SND_PCM_FORMAT_U24
            snd_format = SND_PCM_FORMAT_S24; break;
        case 16:    //同是24位还有: SND_PCM_FORMAT_U16
            snd_format = SND_PCM_FORMAT_S16; break;
        case 8:
            snd_format = SND_PCM_FORMAT_U8; break;
        default:
            snd_format = SND_PCM_FORMAT_UNKNOWN; break;
    }
    return snd_format;
}


int main(int argc, char *argv[])
{
    if(argc != 2) {
        printf("Usage: %s <wav-file>\n", argv[0]);
        return -1;
    }

    // 1: 打开WAV格式文件
    int fd = open(argv[1], O_RDONLY);
    if(-1 == fd) {
        perror("open() error");
        return -1;
    }

    // 2:读取wav头并，从中提取描述该wav数据的信息，用于声卡初始化
    wav_format *wav = (wav_format *)calloc(1, sizeof(wav_format));
    get_wavHeader_info(fd, wav);    
    snd_pcm_format_t format = get_pcmFormat(wav);

    // 3: 声卡初始化
    ao_init(0, wav->format.sample_rate, wav->format.channels, format);   //帧率参数填0，pcm采样周期以最大周期的1/4作为标准

    // 4: 读取文件数据，并送入声卡
    uint32_t written = 0;
    uint32_t total_bytes = LE_INT(wav->data.data_size);
    uint32_t period_bytes = LE_SHORT(wav->format.channels) * (LE_SHORT(wav->format.bits_per_sample)/8) * LE_INT(wav->format.sample_rate);
    uint8_t *buf = malloc(period_bytes);
    if(NULL == buf){
        printf("create buffer faild\n");
        return -1;
    }

    bool bEOS = false;
    ssize_t rBytes, wBytes;
    while(written < total_bytes){
        memset(buf, 0, period_bytes);
        if(0 == (rBytes = read(fd, buf, period_bytes)))
            break;

        if(rBytes < 0){
            printf("read file(%s) err !\n", argv[1]);
            break;
        }

        if(rBytes < period_bytes)
            bEOS = true;
            
        wBytes = ao_writepcmBuf(buf, rBytes, bEOS);
        if(0 < wBytes){
            written += wBytes;
        }
    }

    // 5: 销毁资源，释放声卡
    free(buf);
    free(wav);
    
    ao_exit();
    close(fd);
    
	return 0;
}
