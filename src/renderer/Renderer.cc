module;

#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>

export module eden:renderer;

namespace eden {

export class Renderer {
public:
  Renderer(MTL::Device *pDevice) : _pDevice(pDevice->retain()) {
    _pCommandQueue = _pDevice->newCommandQueue();
  }

  ~Renderer() {
    _pCommandQueue->release();
    _pDevice->release();
  }

  void draw(MTK::View *pView) {
    NS::AutoreleasePool *pPool = NS::AutoreleasePool::alloc()->init();

    MTL::CommandBuffer *pCmd = _pCommandQueue->commandBuffer();
    MTL::RenderPassDescriptor *pRpd = pView->currentRenderPassDescriptor();
    MTL::RenderCommandEncoder *pEnc = pCmd->renderCommandEncoder(pRpd);
    pEnc->endEncoding();
    pCmd->presentDrawable(pView->currentDrawable());
    pCmd->commit();

    pPool->release();
  }

private:
  MTL::Device *_pDevice;
  MTL::CommandQueue *_pCommandQueue;
};

} // namespace eden