//
//  exportjs.c
//  baye-ios
//
//  Created by loong on 16/10/29.
//
//

#include <stdio.h>

#include	"baye/comm.h"
#include	"baye/bind-objects.h"
#include	"baye/data-bind.h"
#include	"baye/script.h"
#include	"baye/extern.h"
#include	"baye/sharefun.h"
#include    "touch.h"

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
void setLCDSize(int width, int height)
{
    g_screenWidth = width;
    g_screenHeight = height;
}

EMSCRIPTEN_KEEPALIVE
void bayeSetDebug(int debug)
{
    GamSetDebug(debug);
}

EMSCRIPTEN_KEEPALIVE
int bayeGetCurrentPeriod()
{
    return g_PIdx;
}

EMSCRIPTEN_KEEPALIVE
int bayeCityAddGoods(U8 city, U8 goods)
{
    return AddGoods(city, goods);
}

EMSCRIPTEN_KEEPALIVE
int bayeCityDelGoods(U8 city, U8 goods)
{
    return DelGoods(city, goods);
}
