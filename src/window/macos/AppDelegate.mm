#import <Window/MacOS/AppDelegate.h>

@implementation AppDelegate

- (void)applicationWillFinishLaunching:(NSNotification *)notification {
  [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
  _window = [[NSWindow alloc]
      initWithContentRect:NSMakeRect(0, 0, _width, _height)
                styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable |
                           NSWindowStyleMaskResizable |
                           NSWindowStyleMaskMiniaturizable)
                  backing:NSBackingStoreBuffered
                    defer:NO];

  _device = MTLCreateSystemDefaultDevice();

  _view = [[MTKView alloc] initWithFrame:_window.contentView.frame
                                  device:_device];
  _view.colorPixelFormat = MTLPixelFormatBGRA8Unorm;
  _view.depthStencilPixelFormat = MTLPixelFormatDepth32Float;
  _view.clearColor = MTLClearColorMake(0.0, 0.0, 0.0, 1.0);

  _viewDelegate = [[ViewDelegate alloc] initWithDevice:_device];
  _view.delegate = _viewDelegate;

  [_window.contentView addSubview:_view];
  [_window setTitle:_title];

  [_window makeKeyAndOrderFront:nil];

  [NSApp activateIgnoringOtherApps:YES];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)app {
  return YES;
}

@end