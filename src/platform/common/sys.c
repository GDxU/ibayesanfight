//
//  sys.c
//  baye-ios
//
//  Created by loong on 15/8/15.
//
//

#include <stdio.h>
#include "baye/compa.h"
#include "baye/comm.h"
#include "timer.h"

void gam_timer_init();
void gam_timer2_open(int interval, void(*callback));
static void(*_lcd_fluch_cb)(char*buffer);

#define SCR_W SCR_WID
#define SCR_H SCR_HGT
#define BYTES_PERLINE (SCR_LINE * 8)

#define DOT 1
#define CLR 0
static char static_buffer[WK_BLEN_MAX];
static char backup_buffer[WK_BLEN_MAX];
static char isLcdDirty = 0;
static char *buffer = static_buffer;
static char *scr_buffer = static_buffer;
static size_t buffer_size = sizeof(static_buffer);

static U8 _insideScreen(PT x, PT y) {
    return x >= 0 && y >= 0 && x < g_screenWidth && y < g_screenHeight;
}

void GamSetLcdFlushCallback(void(*lcd_fluch_cb)(char*buffer))
{
    _lcd_fluch_cb = lcd_fluch_cb;
}

static void timed_flush_lcd()
{
    if (isLcdDirty && _lcd_fluch_cb) {
        _lcd_fluch_cb(scr_buffer);
        isLcdDirty = 0;
    }
}

FAR void logLcd()
{
    int x, y;
    int perLine = BYTES_PERLINE;
    for (y = 0; y < SCR_H; y++) {
        printf("%03d ", y);
        for (x = 0; x < SCR_W; x++) {
            bool pixel = buffer[perLine*y + x];
            printf("%s ", pixel ? "." : "#");
        }
        printf("\n");
    }
    printf("\n");
    printf("---------------%dx%d-------------------\n", SCR_W, SCR_H);
    printf("\n");
}

FAR void flushLcd()
{
    if (_lcd_fluch_cb && buffer == scr_buffer) {
        isLcdDirty = 1;
    }
}

FAR void logPicture(U8 wid, U8 hgt, U8* pic)
{
    int x, y;
    {
        int perLine = (wid + 7) / 8;
        for (y = 0; y < hgt; y++) {
            for (x = 0; x < wid; x++) {
                if (pic) {
                    bool pixel = pic[perLine*y + x/8] & (128 >> (x%8));
                    printf("%s", pixel ? "  " : "##");
                } else {
                    printf("@");
                }
            }
            printf("\n");
        }
        printf("\n");
        printf("----------------------------------\n");
        printf("\n");
    }
}


FAR void SysAscii(PT x,PT y,U8 asc)
{
}

FAR U8 SysGetKey(void)
{
    MsgType msg;
    GuiGetMsg(&msg);
    return msg.param;
}

FAR U8   SysGetKeySound(void)
{
    return 0;
}

FAR	U8 SysGetTimer1Number(void)
{
    return (U8)gam_timer_interval();
}

FAR	void SysIconAllClear(void)						/*清除所有icon显示,系统的除外 */
{
}

FAR void SysIconBattery(U8 data)
{
}

FAR	void SysLCDVoltage(U8 voltage)		/*voltage: 0 - 63 */
{
}

FAR void SysLcdPartClear(PT x1,PT y1,PT x2,PT y2)
{
    PT x, y;
    for (y = y1; y <= y2; y++) {
        for (x = x1; x <= x2; x++) {
            if (!_insideScreen(x, y)) continue;

            int ind = BYTES_PERLINE * y + x;
            buffer[ind] = CLR;
        }
    }
    flushLcd();
}

FAR void SysLcdReverse(PT x1,PT y1,PT x2,PT y2)
{
    PT x, y;
    for (y = y1; y <= y2; y++) {
        for (x = x1; x <= x2; x++) {
            if (!_insideScreen(x, y)) continue;

            int ind = BYTES_PERLINE * y + x;
            buffer[ind] = !buffer[ind];
        }
    }
    flushLcd();
}

FAR void SysLine(PT x1,PT y1,PT x2,PT y2)
{
}

static void _timercb()
{
    MsgType msg;
    msg.type = VM_TIMER;
    GuiPushMsg(&msg);
}

FAR	void	SysMemInit(U16 start,U16 len)
{
    gam_timer_init();
    gam_timer_set_callback(_timercb);
    gam_timer2_open(3, timed_flush_lcd);
}

FAR void SysPicture(PT sX, PT sY, PT eX, PT eY, U8*pic , U8 flag)
{
    int wid = eX - sX + 1;
    int hgt = eY - sY + 1;
    int x, y, X, Y;
    int scrPerLine = BYTES_PERLINE;

    {
        int picPerLine = (wid + 7) / 8;
        for (y = 0; y < hgt; y++) {
            Y = sY + y;
            for (x = 0; x < wid; x++) {
                X = sX + x;
                unsigned char pixel0, pixel1;
                int ind = scrPerLine * Y + X;
                if (!_insideScreen(X, Y)) {
                    continue;
                }

                if (flag == 4) {
                    pixel1 = 0;
                }
                else {
                    
                    if (pic) {
                        pixel0 = pic[picPerLine*y + x/8] & (128 >> (x%8));
                    }
                    else {
                        pixel0 = 0;
                    }
                    
                    {
                        pixel1 = buffer[ind];
                        
                        switch (flag) {
                            case 0: // Normal
                                pixel1 = pixel0;
                                break;
                            case 1: // &
                                pixel1 = pixel0 && pixel1;
                                break;
                            case 2: // |
                                pixel1 = pixel0 || pixel1;
                                break;
                            case 4: // clear
                                break;
                            default:
                                break;
                        }
                    }
                }
                buffer[ind] = !!pixel1;
            }
        }
    }
    flushLcd();
}

static inline void _pixel(PT x,PT y,U8 data)
{
    if (!_insideScreen(x, y)) return;

    int ind = BYTES_PERLINE * y + x;
    buffer[ind] = data;
}

FAR void SysPutPixel(PT x,PT y,U8 data)
{
    _pixel(x, y, data);
    flushLcd();
}

FAR void SysRect(PT x1,PT y1,PT x2,PT y2)
{
    int x, y;
    y = y1;
    for (x = x1; x <= x2; x++) {
        _pixel(x, y, DOT);
    }
    y = y2;
    for (x = x1; x <= x2; x++) {
        _pixel(x, y, DOT);
    }
    x = x1;
    for (y = y1; y <= y2; y++) {
        _pixel(x, y, DOT);
    }
    x = x2;
    for (y = y1; y <= y2; y++) {
        _pixel(x, y, DOT);
    }
    flushLcd();
}

FAR void SysRectClear(PT x1,PT y1,PT x2,PT y2)
{
    SysLcdPartClear(x1, y1, x2, y2);
    flushLcd();
}

FAR void SysSetKeySound(U8 keySoundFlag)
{
}

FAR void SysTimer1Close(void)
{
    gam_timer_close();
}

FAR void SysTimer1Open(U8 times)
{
    gam_timer_open(times);
}

FAR void SysSaveScreen()
{
    memcpy(backup_buffer, scr_buffer, buffer_size);
}

FAR void SysRestoreScreen()
{
    memcpy(scr_buffer, backup_buffer, buffer_size);
}

FAR void SysAdjustLCDBuffer(int wid, int height)
{
    size_t sz = wid * height;

    if (sz <= buffer_size) {
        memset(scr_buffer, 0, sz);
        return;
    }

    if (scr_buffer && scr_buffer != static_buffer) {
        free(scr_buffer);
    }

    scr_buffer = malloc(sz);
    memset(scr_buffer, 0, sz);
    buffer_size = sz;
}

FAR void SysSelectScreen(U8*scr)
{
    buffer = scr ? (char*)scr : scr_buffer;
}

FAR void SysCopyScreen(U8*scr)
{
    memcpy(scr_buffer, scr, buffer_size);
    flushLcd();
}
