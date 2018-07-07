#include <timer.h>
#include <windows.h>

#define IDT_TIMER 100
#define IDT_TIMER2 101

#define ratio 10

static void(*timer_callback)();
static int timer_interval = 0;

void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
    if (timer_callback) {
        timer_callback();
    }
}

void gam_timer_init() {
}

void gam_timer_set_callback(void(*cb)()) {
    timer_callback = cb;
}

void gam_timer_open(int interval) {
    timer_interval = interval;
    SetTimer(NULL, IDT_TIMER, interval * ratio, (TIMERPROC)TimerProc);
}

void gam_timer_close() {
    KillTimer(NULL, IDT_TIMER);
}

int gam_timer_interval() {
    return timer_interval;
}


static void(*timer2_callback)();

void CALLBACK Timer2Proc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
    timer2_callback();
}

void gam_timer2_open(int interval, void(*callback)())
{
    timer2_callback = callback;
    SetTimer(NULL, IDT_TIMER2, interval * ratio, (TIMERPROC)Timer2Proc);
}
