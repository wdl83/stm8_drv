#include "tim2.h"

tim_ctl_t tim2_ctl_;

void tim2_cb(timer_cb_t cb, uintptr_t user_data)
{
    tim2_ctl_.cb = cb;
    tim2_ctl_.user_data = user_data;
}

void tim2_irq(void) __interrupt(IRQ_NO_TIM2)
{
    if(!tim2_ctl_.cb) return;
    (*tim2_ctl_.cb)(tim2_ctl_.user_data);
}
