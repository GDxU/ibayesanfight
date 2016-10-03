//
//  LCDView.m
//  baye-ios
//
//  Created by loong on 15/8/15.
//
//

#include "consdef.h"
#import "LCDView.h"

#include "consdef.h"
#include "baye-wrapper-mac.h"
#include "baye/comm.h"

#define SCR_W SCR_WID
#define SCR_H SCR_HGT
#define BYTES_PERLINE (SCR_LINE * 8)

@implementation LCDView
- (void)keyDown:(NSEvent *)theEvent {
    [self.delegate keyDown: theEvent];
    [super keyDown:theEvent];
}

- (BOOL)acceptsFirstResponder {
    return YES;
}

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    if (!self.buffer) {
        return;
    }
    int ind = 0;
    int x, y;
    NSColor *color;
    
    for (y = 0; y < SCR_H; y++) {
        for (x = 0; x < SCR_W; x++) {
            ind = BYTES_PERLINE*y + x;
            int pixel = self.buffer[ind];
            
            if (pixel) {
                color = [NSColor blackColor];
            }
            else {
                color = [NSColor whiteColor];
            }
            CGFloat vw = self.frame.size.width;
            CGFloat vh = self.frame.size.height;

            CGFloat pw = vw / SCR_W;
            CGFloat ph = vh / SCR_H;
            CGFloat px = x * vw / SCR_W;
            CGFloat py = (SCR_H - 1 - y) * vh / SCR_H;

            [color drawSwatchInRect:NSMakeRect(px, py, pw, ph)];
        }
    }
}

- (NSPoint)pointInLCD:(NSEvent *)theEvent
{
    NSPoint pv = [self convertPoint:[theEvent locationInWindow] fromView:nil];
    return NSMakePoint(pv.x / self.frame.size.width * SCR_W, (self.frame.size.height - pv.y) / self.frame.size.height * SCR_H);
}

- (void)mouseDown:(NSEvent *)theEvent
{
    NSPoint p = [self pointInLCD:theEvent];
    bayeTouchSendTouchEvent(VT_TOUCH_DOWN, p.x, p.y);
}

- (void)mouseDragged:(NSEvent *)theEvent
{
    NSPoint p = [self pointInLCD:theEvent];
    bayeTouchSendTouchEvent(VT_TOUCH_MOVE, p.x, p.y);
}

- (void)mouseUp:(NSEvent *)theEvent
{
    NSPoint p = [self pointInLCD:theEvent];
    bayeTouchSendTouchEvent(VT_TOUCH_UP, p.x, p.y);
}

@end
