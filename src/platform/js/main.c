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

#include	"exportjs.c"

FAR U8 GamConInit(void);
FAR void GamBaYeEng(void);

void GamSetLcdFlushCallback(void(*lcd_fluch_cb)(char*buffer));

static void _lcd_flush_cb(char*buffer) {
    EM_ASM_INT ({
        bayeFlushLcdBuffer($0);
    }, buffer);
}

int main(int argc, char*argv[])
{
    emscripten_sleep(1); // give javascript chance to run init
    GamSetResourcePath((U8*)"/rom/dat.lib", (U8*)"/rom/font.bin");
    GamSetAltLibPath((U8*)"/data/dat.lib");
    GamSetDataDir((U8*)"/data/");
    GamSetLcdFlushCallback(_lcd_flush_cb);
    GamConInit();
    GamBaYeEng();

    EM_ASM({
        bayeExit();
    });
    return 0;
}
