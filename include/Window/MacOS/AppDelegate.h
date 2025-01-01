#import <Window/MacOS/ViewDelegate.h>

#import <AppKit/AppKit.h>
#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>

@property(nonatomic, assign) int width;
@property(nonatomic, assign) int height;

@property(nonatomic, strong) NSString *title;
@property(nonatomic, strong) NSWindow *window;
@property(nonatomic, strong) MTKView *view;
@property(nonatomic, strong) ViewDelegate *viewDelegate;

@property(nonatomic, strong) id<MTLDevice> device;

@end
