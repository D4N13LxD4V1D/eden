#import "Renderer/Renderer.hh"

@implementation Renderer : NSObject

- (nonnull instancetype)initWithDevice:(id<MTLDevice>)device {
  self = [super init];
  if (self) {
    _device = [device retain];
    _commandQueue = [_device newCommandQueue];
    [self buildShaders];
    [self buildBuffers];
  }
  return self;
}

- (void)dealloc {
  [_vertexPositionsBuffer release];
  [_vertexColorsBuffer release];
  [_renderPipelineState release];
  [_commandQueue release];
  [_device release];
  [super dealloc];
}

- (void)buildShaders {
  const char *shaderSource = R"(
        #include <metal_stdlib>
        using namespace metal;

        struct v2f
        {
            float4 position [[position]];
            half3 color;
        };

        v2f vertex vertexMain( uint vertexId [[vertex_id]],
                               device const float3* positions [[buffer(0)]],
                               device const float3* colors [[buffer(1)]] )
        {
            v2f o;
            o.position = float4( positions[ vertexId ], 1.0 );
            o.color = half3 ( colors[ vertexId ] );
            return o;
        }

        half4 fragment fragmentMain( v2f in [[stage_in]] )
        {
            return half4( in.color, 1.0 );
        }
    )";

  NSError *error = nil;
  id<MTLLibrary> library =
      [_device newLibraryWithSource:[NSString stringWithUTF8String:shaderSource]
                            options:nil
                              error:&error];
  if (!library) {
    NSLog(@"Error when creating library: %@", error);
    return;
  }

  id<MTLFunction> vertexFunction = [library newFunctionWithName:@"vertexMain"];
  id<MTLFunction> fragmentFunction =
      [library newFunctionWithName:@"fragmentMain"];

  MTLRenderPipelineDescriptor *pipelineDescriptor =
      [[MTLRenderPipelineDescriptor alloc] init];
  pipelineDescriptor.vertexFunction = vertexFunction;
  pipelineDescriptor.fragmentFunction = fragmentFunction;
  pipelineDescriptor.colorAttachments[0].pixelFormat =
      MTLPixelFormatBGRA8Unorm_sRGB;

  _renderPipelineState =
      [_device newRenderPipelineStateWithDescriptor:pipelineDescriptor
                                              error:&error];
  if (!_renderPipelineState) {
    NSLog(@"Error when creating render pipeline state: %@", error);
    return;
  }

  [pipelineDescriptor release];
  [vertexFunction release];
  [fragmentFunction release];
  [library release];
}

- (void)buildBuffers {
  const size_t vertexCount = 3;

  simd::float3 vertexPositions[vertexCount] = {
      {-0.8f, 0.8f, 0.0f}, {0.0f, -0.8f, 0.0f}, {+0.8f, 0.8f, 0.0f}};

  simd::float3 vertexColors[vertexCount] = {
      {1.0, 0.3f, 0.2f}, {0.8f, 1.0, 0.0f}, {0.8f, 0.0f, 1.0}};

  const size_t positionDataSize = vertexCount * sizeof(simd::float3);
  const size_t colorDataSize = vertexCount * sizeof(simd::float3);

  _vertexPositionsBuffer =
      [_device newBufferWithBytes:vertexPositions
                           length:positionDataSize
                          options:MTLResourceStorageModeShared];

  _vertexColorsBuffer =
      [_device newBufferWithBytes:vertexColors
                           length:colorDataSize
                          options:MTLResourceStorageModeShared];

  memcpy([_vertexPositionsBuffer contents], vertexPositions, positionDataSize);
  memcpy([_vertexColorsBuffer contents], vertexColors, colorDataSize);

  [_vertexPositionsBuffer
      didModifyRange:NSMakeRange(0, [_vertexPositionsBuffer length])];
  [_vertexColorsBuffer
      didModifyRange:NSMakeRange(0, [_vertexColorsBuffer length])];
}

- (void)drawInMTKView:(MTKView *)view {
  auto pool = [[NSAutoreleasePool alloc] init];

  auto commandBuffer = [_commandQueue commandBuffer];
  auto renderPassDescriptor = [view currentRenderPassDescriptor];
  auto renderEncoder =
      [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];

  [renderEncoder setRenderPipelineState:_renderPipelineState];
  [renderEncoder setVertexBuffer:_vertexPositionsBuffer offset:0 atIndex:0];
  [renderEncoder setVertexBuffer:_vertexColorsBuffer offset:0 atIndex:1];
  [renderEncoder drawPrimitives:MTLPrimitiveTypeTriangle
                    vertexStart:0
                    vertexCount:3];

  [renderEncoder endEncoding];
  [commandBuffer presentDrawable:view.currentDrawable];
  [commandBuffer commit];

  [pool release];
}

@end