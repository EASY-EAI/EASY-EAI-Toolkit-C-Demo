/**
 *
 * Copyright 2022 by Guangzhou Easy EAI Technologny Co.,Ltd.
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

#ifndef PWM_H
#define PWM_H


#if defined(__cplusplus)
extern "C"{
#endif

extern int pwm_init(const char  *path);
extern int pwm_set_period(const char* chipid, const char* period);
extern int pwm_set_duty_cycle(const char* chipid, const char* duty_cycle);
extern int pwm_set_enable(const char* chipid, const char* enable);
extern int pwm_release(const char* path);

#if defined(__cplusplus)
}
#endif

#endif
