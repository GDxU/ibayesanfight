//
//  touch.c
//  baye-ios
//
//  Created by loong on 16/10/3.
//
//

#include "touch.h"

void touchSendTouchEvent(U16 event, I16 x, I16 y)
{
    printf("touch event:%d x:%d y:%d\n", event, x, y);
    MsgType msg;
    msg.type = VM_TOUCH;
    msg.param = event;
    msg.param2.i16.p0 = x;
    msg.param2.i16.p1 = y;
    GuiPushMsg(&msg);
}

///判断一个点是否在矩形框内
U8 touchIsPointInRect(I16 x, I16 y, Rect r)
{
    return (r.left <= x && x <= r.right) && (r.top <= y && y <= r.bottom);
}

///获取触摸点在list内的item序号。
I16 touchListViewItemIndexAtPoint(I16 x, I16 y, Rect listRect, U16 itemStart, U16 itemCount, U16 itemHeight)
{
    if (!touchIsPointInRect(x, y, listRect)) {
        return -2;
    }
    U16 yOffset = y - listRect.top;
    U16 index = itemStart + yOffset / itemHeight;
    return index < itemCount ? index : -1;
}

I8 touchUpdate(Touch *touch, MsgType msg)
{
    if (msg.type != VM_TOUCH) {
        return -1;
    }

    touch->currentX = msg.param2.i16.p0;
    touch->currentY = msg.param2.i16.p1;

    switch (msg.param) {
        case VT_TOUCH_DOWN:
            touch->startX = touch->currentX;
            touch->startY = touch->currentY;
            touch->touched = 1;
            touch->moved = 0;
            break;
        case VT_TOUCH_UP:
            touch->touched = 0;
            break;
        case VT_TOUCH_MOVE:
            touch->moved = 1;
            break;
        default:
            break;
    }
    return 0;
}
