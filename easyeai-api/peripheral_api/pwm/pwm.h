#ifndef     PWM_H
#define    PWM_H



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

