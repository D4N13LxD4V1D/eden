#import <Window/MacOS/ViewDelegate.h>

@implementation ViewDelegate

- (instancetype)initWithDevice:(id<MTLDevice>)device {
  self = [super init];
  if (self) {
    _renderer = [[Renderer alloc] initWithDevice:device];
  }
  return self;
}

- (void)drawInMTKView:(MTKView *)view {
  [_renderer drawInMTKView:view];
}

- (void)mtkView:(MTKView *)view drawableSizeWillChange:(CGSize)size {
  NSLog(@"drawableSizeWillChange");
}

- (BOOL)acceptsFirstResponder {
  return YES;
}

- (void)keyDown:(NSEvent *)event {
  NSLog(@"keyDown %d", event.keyCode);
}

- (void)keyUp:(NSEvent *)event {
  NSLog(@"keyUp %d", event.keyCode);
}

@end