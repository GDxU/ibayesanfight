//
//  GamLCDView.m
//  baye-ios
//
//  Created by loong on 15/8/16.
//
//

#import "GamLCDView.h"

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 96

@implementation GamLCDView

// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
    if (!self.buffer) {
        return;
    }
    CGContextRef ctx = UIGraphicsGetCurrentContext();
    int ind = 0;
    int x, y;
    float ratio = self.frame.size.width / SCREEN_WIDTH;
    
    for (y = 0; y < SCREEN_HEIGHT; y++) {
        for (x = 0; x < SCREEN_WIDTH; x++) {
            ind = SCREEN_WIDTH*y + x;
            int pixel = self.buffer[ind];
            
            if (pixel) {
                CGContextSetRGBFillColor(ctx, 0, 0, 0, 1);
            }
            else {
                CGContextSetRGBFillColor(ctx, 0.8, 0.85, 0.8, 1);
            }
            CGContextFillRect(ctx, CGRectMake(x*ratio, (y)*ratio, ratio, ratio));
        }
    }
}

@end
