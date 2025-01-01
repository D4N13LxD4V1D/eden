#import <Window/Window.hh>

#import <Window/MacOS/AppDelegate.h>

#import <AppKit/AppKit.h>
#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>

RawWindow::RawWindow(const char *title, int width, int height) {
  auto delegate = [[AppDelegate alloc] init];
  delegate.title = [NSString stringWithUTF8String:title];
  delegate.width = width;
  delegate.height = height;

  auto app = [NSApplication sharedApplication];
  [app setDelegate:delegate];
}

RawWindow::~RawWindow() {
  auto app = [NSApplication sharedApplication];
  [app terminate:nil];
}

auto RawWindow::show() -> void {
  auto app = [NSApplication sharedApplication];
  [app run];
}

// @interface WindowImpl : NSObject

// @property(nonatomic, assign) NSApplication *app;
// @property(nonatomic, assign) NSWindow *window;
// @property(nonatomic, assign) AppDelegate *delegate;

// @end

// @implementation WindowImpl
// - (instancetype)initWithTitle:(const char *)title
//                         width:(int)width
//                        height:(int)height {
//   self = [super init];
//   if (self) {
//     self.delegate = [[AppDelegate alloc] init];
//     self.delegate.title = [NSString stringWithUTF8String:title];
//     self.delegate.width = width;
//     self.delegate.height = height;

//     self.app = [NSApplication sharedApplication];
//     [self.app setDelegate:self.delegate];
//   }
//   return self;
// }

// - (void)show {
//   [self.app run];
// }

// - (void)terminate {
//   [self.app terminate:nil];
// }

// @end