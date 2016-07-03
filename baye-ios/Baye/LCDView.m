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

#define SCR_W SCR_WID
#define SCR_H SCR_HGT
#define BYTES_PERLINE (SCR_LINE * 8)

@implementation LCDView

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    if (!self.buffer) {
        return;
    }
    int ind = 0;
    int x, y;
    float ratio = 2;
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
            [color drawSwatchInRect:NSMakeRect(x*ratio, (SCR_HGT-1-y)*ratio, ratio, ratio)];
        }
    }
}

@end
