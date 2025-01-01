#import <AppKit/AppKit.h>
#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>

@interface Renderer : NSObject

@property(nonatomic, strong) id<MTLDevice> device;
@property(nonatomic, strong) id<MTLCommandQueue> commandQueue;
@property(nonatomic, strong) id<MTLRenderPipelineState> renderPipelineState;
@property(nonatomic, strong) id<MTLBuffer> vertexPositionsBuffer;
@property(nonatomic, strong) id<MTLBuffer> vertexColorsBuffer;

- (instancetype)initWithDevice:(id<MTLDevice>)device;

- (void)drawInMTKView:(MTKView *)view;

@end
