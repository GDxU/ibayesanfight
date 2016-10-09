//
//  main.c
//  baye-ios
//
//  Created by loong on 16/6/29.
//
//

#include	"inc/dictsys.h"
#include	"baye/comm.h"
#include	"baye/bind-objects.h"
#include	"baye/data-bind.h"
#include	"baye/script.h"
#include    "touch.h"

#include <emscripten.h>

FAR U8 GamConInit(void);
FAR void GamBaYeEng(void);

void GamSetLcdFlushCallback(void(*lcd_fluch_cb)(char*buffer));

static void _lcd_flush_cb(char*buffer) {
    EM_ASM_INT ({
        lcdFlushBuffer($0);
    }, buffer);
}

EMSCRIPTEN_KEEPALIVE
void sendKey(int key)
{
    MsgType msg;
    msg.type = VM_CHAR_FUN;
    msg.param = key;
    GuiPushMsg(&msg);
}

EMSCRIPTEN_KEEPALIVE
void sendTouchEvent(int event, int x, int y)
{
    touchSendTouchEvent((U16)event, (I16)x, (I16)y);
}

EMSCRIPTEN_KEEPALIVE
void bayeSetDebug(int debug)
{
    GamSetDebug(debug);
}

EMSCRIPTEN_KEEPALIVE
void setLCDSize(int width, int height)
{
    g_screenWidth = width;
    g_screenHeight = height;
}

int main(int argc, char*argv[])
{
    emscripten_sleep(1); // give javascript chance to run init
    GamSetResourcePath((U8*)"/rom/dat.lib", (U8*)"/rom/font.bin");
    GamSetAltLibPath((U8*)"/data/dat.lib");
    GamSetDataDir((U8*)"/data/");
    GamSetLcdFlushCallback(_lcd_flush_cb);
    GamConInit();
    script_init();
    GamBaYeEng();

    EM_ASM({
        goHome();
    });
    return 0;
}
