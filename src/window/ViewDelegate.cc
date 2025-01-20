module;

#include <MetalKit/MetalKit.hpp>

export module eden:view_delegate;

import :renderer;

namespace eden {

export class ViewDelegate : public MTK::ViewDelegate {
public:
  ViewDelegate(MTL::Device *pDevice)
      : MTK::ViewDelegate(), _pRenderer(new Renderer(pDevice)) {}

  virtual ~ViewDelegate() override { delete _pRenderer; }

  virtual void drawInMTKView(MTK::View *pView) override {
    _pRenderer->draw(pView);
  }

private:
  Renderer *_pRenderer;
};

} // namespace eden