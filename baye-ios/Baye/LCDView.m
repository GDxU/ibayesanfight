//
//  LCDView.m
//  baye-ios
//
//  Created by loong on 15/8/15.
//
//

#import "LCDView.h"

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
    
    for (y = 0; y < 96; y++) {
        for (x = 0; x < 160; x++) {
            ind = 160*y + x;
            int pixel = self.buffer[ind];
            
            if (pixel) {
                color = [NSColor blackColor];
            }
            else {
                color = [NSColor whiteColor];
            }
            [color drawSwatchInRect:NSMakeRect(x*ratio, (95-y)*ratio, ratio, ratio)];
        }
    }
}

@end
