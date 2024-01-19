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

// ai: audioIn
extern int32_t  ai_init(uint32_t fps, uint32_t sampleRate, uint16_t channels, snd_pcm_format_t fmt);
extern int32_t  ai_exit(void);
extern uint32_t ai_pcmPeriodSize(void);
extern uint32_t ai_readpcmData(uint32_t dataLen);
extern uint8_t *ai_pcmBufptr(void);
    
// ao: audioOut
extern int32_t  ao_init(uint32_t fps, uint32_t sampleRate, uint16_t channels, snd_pcm_format_t fmt);
extern int32_t  ao_exit(void);
extern int32_t  ao_writepcmBuf(uint8_t *pData, uint32_t dataLen, bool bEOS);


#ifdef __cplusplus
}
#endif
#endif


