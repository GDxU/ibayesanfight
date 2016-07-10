//
//  main.c
//  baye-ios
//
//  Created by loong on 16/6/29.
//
//

#include	"inc/dictsys.h"
#include	"baye/comm.h"

#include <emscripten.h>

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

int main(int argc, char*argv[])
{
    GamSetResourcePath((U8*)"/rom/dat.lib", (U8*)"/rom/font.bin");
    GamSetAltLibPath((U8*)"/data/dat.lib");
    GamSetDataDir((U8*)"/data/");
    GamSetLcdFlushCallback(_lcd_flush_cb);
    GamBaYeEng();

    EM_ASM({
        goHome();
    });
    return 0;
}

