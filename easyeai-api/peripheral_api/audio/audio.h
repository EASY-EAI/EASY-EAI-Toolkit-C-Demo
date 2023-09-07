/**
 *
 * Copyright 2021 by Guangzhou Easy EAI Technologny Co.,Ltd.
 * website: www.easy-eai.com
 *
 * Author: CHM <chenhaiman@easy-eai.com>
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * License file for more details.
 * 
 */

#ifndef AUDIO_H
#define AUDIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include <alsa/asoundlib.h>

#if __BYTE_ORDER == __LITTLE_ENDIAN
    #define SND_PCM_FORMAT_FLOAT64 SND_PCM_FORMAT_FLOAT64_LE
    #define SND_PCM_FORMAT_FLOAT   SND_PCM_FORMAT_FLOAT_LE
    #define SND_PCM_FORMAT_U32     SND_PCM_FORMAT_U32_LE
    #define SND_PCM_FORMAT_S32     SND_PCM_FORMAT_S32_LE
    #define SND_PCM_FORMAT_U24     SND_PCM_FORMAT_U24_LE
    #define SND_PCM_FORMAT_S24     SND_PCM_FORMAT_S24_LE
    #define SND_PCM_FORMAT_U16     SND_PCM_FORMAT_U16_LE
    #define SND_PCM_FORMAT_S16     SND_PCM_FORMAT_S16_LE

#elif __BYTE_ORDER == __BIG_ENDIAN
    #define SND_PCM_FORMAT_FLOAT64 SND_PCM_FORMAT_FLOAT64_BE
    #define SND_PCM_FORMAT_FLOAT   SND_PCM_FORMAT_FLOAT_BE
    #define SND_PCM_FORMAT_U32     SND_PCM_FORMAT_U32_BE
    #define SND_PCM_FORMAT_S32     SND_PCM_FORMAT_S32_BE
    #define SND_PCM_FORMAT_U24     SND_PCM_FORMAT_U24_BE
    #define SND_PCM_FORMAT_S24     SND_PCM_FORMAT_S24_BE
    #define SND_PCM_FORMAT_U16     SND_PCM_FORMAT_U16_BE
    #define SND_PCM_FORMAT_S16     SND_PCM_FORMAT_S16_BE

#endif

// ai: audioIn
extern int32_t  ai_init(uint32_t sampleRate, uint16_t channels, snd_pcm_format_t fmt);
extern int32_t  ai_exit(void);
extern uint32_t ai_pcmPeriodSize(void);
extern uint32_t ai_readpcmData(uint32_t dataLen);
extern uint8_t *ai_pcmBufptr(void);
    
// ao: audioOut
extern int32_t  ao_init(uint32_t sampleRate, uint16_t channels, snd_pcm_format_t fmt);
extern int32_t  ao_exit(void);
extern int32_t  ao_writepcmBuf(uint8_t *pData, uint32_t dataLen, bool bEOS);


#ifdef __cplusplus
}
#endif
#endif


