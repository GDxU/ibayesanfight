//
//  timer.c
//  baye-ios
//
//  Created by loong on 15/8/15.
//
//
#include <emscripten.h>

#define NULL ((void*)0)
#define ratio 10.0

typedef void(*timer_cb)(void);

typedef struct {
    int started;
    int active;
    int interval;
    timer_cb cb;
} timer_t;

static timer_t timer1 = {
    0, 0, 1, NULL
};

static void schedule_timer(timer_t* timer);

void _timer_cb(void*t) {
    timer_t* timer = (timer_t*)t;
    if (timer->active && timer->cb) {
        timer->cb();
    }
    schedule_timer(timer);
}

static void schedule_timer(timer_t* timer) {
    emscripten_async_call(_timer_cb, timer, timer->interval * ratio);
}

int gam_timer_interval()
{
    return timer1.interval;
}

void gam_timer_init()
{
}

void gam_timer_set_callback(void(*cb)(void))
{
    timer1.cb = cb;
}

void gam_timer_open(int interval)
{
    timer1.interval = interval;
    timer1.active = 1;
    if (!timer1.started) {
        timer1.started = 1;
        schedule_timer(&timer1);
    }
}

void gam_timer_close()
{
    timer1.active = 0;
}


static timer_t timer2 = {
    0, 0, 1, NULL
};

void gam_timer2_open(int interval, void(*callback))
{
    timer2.interval = interval;
    timer2.cb = callback;
    schedule_timer(&timer2);
}