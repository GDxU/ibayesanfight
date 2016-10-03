//
//  touch.h
//  baye-ios
//
//  Created by loong on 16/10/3.
//
//

#ifndef touch_h
#define touch_h

#include <stdio.h>
#include "inc/dictsys.h"
#include "baye/comm.h"

typedef struct {
    I16 left;
    I16 top;
    I16 right;
    I16 bottom;
} Rect;

typedef struct {
    U8 touched;
    U8 moved;
    I16 startX;
    I16 startY;
    I16 currentX;
    I16 currentY;
} Touch;

U8 touchIsPointInRect(I16 x, I16 y, Rect r);
I16 touchListViewItemIndexAtPoint(I16 x, I16 y, Rect listRect, U16 itemStart, U16 itemCount, U16 itemHeight);
void touchSendTouchEvent(U16 event, I16 x, I16 y);
I8 touchUpdate(Touch *touch, MsgType msg);

#endif /* touch_h */
