#ifndef __WAV_HEADDER_H__
#define __WAV_HEADDER_H__

#define WAV_FMT_UNKNOW 0x0000
#define WAV_FMT_PCM    0x0001
#define WAV_FMT_FLOAT  0x0003

#define MIN(a, b) \
    ({ \
        typeof(a) _a = a; \
        typeof(b) _b = b; \
        (void)(_a == _b); \
        _a < _b ? _a : _b; \
    })

// 根据本系统的具体字节序处理的存放格式
#if __BYTE_ORDER == __LITTLE_ENDIAN

    #define RIFF ('F'<<24|'F'<<16|'I'<<8|'R'<<0)
    #define WAVE ('E'<<24|'V'<<16|'A'<<8|'W'<<0)
    #define FMT  (' '<<24|'t'<<16|'m'<<8|'f'<<0)
    #define DATA ('a'<<24|'t'<<16|'a'<<8|'d'<<0)
    
    #define LE_SHORT(val) (val)
    #define LE_INT(val)   (val)
    
#elif __BYTE_ORDER == __BIG_ENDIAN

    #define RIFF ('R'<<24|'I'<<16|'F'<<8|'F'<<0)
    #define WAVE ('W'<<24|'A'<<16|'V'<<8|'E'<<0)
    #define FMT  ('f'<<24|'m'<<16|'t'<<8|' '<<0)
    #define DATA ('d'<<24|'a'<<16|'t'<<8|'a'<<0)

    #define LE_SHORT(val) bswap_16(val)
    #define LE_INT(val)   bswap_32(val)
    
#endif

// 1:RIFF块
struct wav_header
{
    uint32_t id; //固定位'RIFF'
    uint32_t size; //除了id和size之外，整个WAV文件的大小
    uint32_t format; //fm chunk的格式，此处为'WAVE'
};
// 2:fmt块
struct wav_fmt
{
    uint32_t fmt_id; //固定为'fmmt'
    uint32_t fmt_size; //在fmt块的大小，固定位16字节
    uint16_t fmt; //data块中数据的格式代码
    uint16_t channels;    //音轨数目：1为单音轨，2为立体声
    uint32_t sample_rate; //采样频率
    uint32_t byte_rate;   //码率 = 采样率 * 帧大小
    uint16_t block_align; //帧大小 = 音轨数 * 量化级/8
    uint16_t bits_per_sample; //量化位数：典型值是8、16、24
};
// 3: the data chunk
struct wav_data
{
    uint32_t data_id; //固定为 'data'
    uint32_t data_size;//除了WAV格式头之外的音频数据大小
};
typedef struct
{
    struct wav_header head;
    struct wav_fmt format;
    struct wav_data data;

}wav_format;


#endif
