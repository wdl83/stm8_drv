#include "tim4.h"

tim_ctl_t tim4_ctl_;

void tim4_cb(timer_cb_t cb, uintptr_t user_data)
{
    tim4_ctl_.cb = cb;
    tim4_ctl_.user_data = user_data;
}

void tim4_irq(void) __interrupt(IRQ_NO_TIM4)
{
    if(!tim4_ctl_.cb) return;
    (*tim4_ctl_.cb)(tim4_ctl_.user_data);
}
