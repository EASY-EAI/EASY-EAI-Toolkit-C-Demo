#include <pwm.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, const char** argv) {
    int ret;
    ret = pwm_init("/sys/class/pwm/pwmchip1");
    printf("export_ret:%d\n",ret);
    ret = pwm_set_period("/sys/class/pwm/pwmchip1","1000000");
    printf("set_period_ret:%d\n",ret);
    ret = pwm_set_duty_cycle("/sys/class/pwm/pwmchip1","500000");
    printf("set_duty_cycle_ret:%d\n",ret);
    ret = pwm_set_enable("/sys/class/pwm/pwmchip1","1");
    printf("set_enable:%d\n",ret);
    ret = pwm_release("/sys/class/pwm/pwmchip1");
    printf("unexport_ret:%d\n",ret);

    ret = pwm_init("/sys/class/pwm/pwmchip2");
    printf("export_ret:%d\n",ret);
    ret = pwm_set_period("/sys/class/pwm/pwmchip2","1000000");
    printf("set_period_ret:%d\n",ret);
    ret = pwm_set_duty_cycle("/sys/class/pwm/pwmchip2","500000");
    printf("set_duty_cycle_ret:%d\n",ret);
    ret = pwm_set_enable("/sys/class/pwm/pwmchip2","1");
    printf("set_enable:%d\n",ret);
    ret = pwm_release("/sys/class/pwm/pwmchip2");
    printf("unexport_ret:%d\n",ret);
    return 0;
}










