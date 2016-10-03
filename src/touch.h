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

U8 touchIsPointInRect(I16 x, I16 y, Rect r);
I16 touchListViewItemIndexAtPoint(I16 x, I16 y, Rect listRect, U16 itemStart, U16 itemCount, U16 itemHeight);
void touchSendTouchEvent(U16 event, I16 x, I16 y);

#endif /* touch_h */
