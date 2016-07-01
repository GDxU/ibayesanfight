//
//  main.c
//  baye-ios
//
//  Created by loong on 16/6/29.
//
//

#include	"inc/dictsys.h"
#include	"baye/comm.h"

FAR void GamBaYeEng(void);

int main(int argc, char*argv[])
{
    GamSetResourcePath((U8*)"/rom/dat.lib", (U8*)"/rom/font.bin");
    GamSetDataDir((U8*)"/data/");
//    GamSetLcdFlushCallback(_lcd_flush_cb);
    GamBaYeEng();
}
