#import <Renderer/Renderer.hh>

#import <AppKit/AppKit.h>
#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>

@interface ViewDelegate : NSObject <MTKViewDelegate>

@property(nonatomic, assign) Renderer *renderer;

- (instancetype)initWithDevice:(id<MTLDevice>)device;

@end