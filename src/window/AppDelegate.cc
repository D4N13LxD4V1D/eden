module;

#include <AppKit/AppKit.hpp>
#include <MetalKit/MetalKit.hpp>

export module eden:app_delegate;

import :view_delegate;

namespace eden {

export class AppDelegate : public NS::ApplicationDelegate {
public:
  ~AppDelegate() {
    _pMtkView->release();
    _pWindow->release();
    _pDevice->release();
    delete _pViewDelegate;
  }

  virtual void
  applicationWillFinishLaunching(NS::Notification *pNotification) override {
    NS::Application *pApp =
        reinterpret_cast<NS::Application *>(pNotification->object());
    pApp->setActivationPolicy(NS::ActivationPolicy::ActivationPolicyRegular);
  }

  virtual void
  applicationDidFinishLaunching(NS::Notification *pNotification) override {
    CGRect frame = (CGRect){{100.0, 100.0}, {512.0, 512.0}};

    _pWindow = NS::Window::alloc()->init(
        frame, NS::WindowStyleMaskClosable | NS::WindowStyleMaskTitled,
        NS::BackingStoreBuffered, false);

    _pDevice = MTL::CreateSystemDefaultDevice();

    _pMtkView = MTK::View::alloc()->init(frame, _pDevice);
    _pMtkView->setColorPixelFormat(
        MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);
    _pMtkView->setClearColor(MTL::ClearColor::Make(1.0, 0.0, 0.0, 1.0));

    _pViewDelegate = new ViewDelegate(_pDevice);
    _pMtkView->setDelegate(_pViewDelegate);

    _pWindow->setContentView(_pMtkView);
    _pWindow->setTitle(NS::String::string(
        "00 - Window", NS::StringEncoding::UTF8StringEncoding));

    _pWindow->makeKeyAndOrderFront(nullptr);

    NS::Application *pApp =
        reinterpret_cast<NS::Application *>(pNotification->object());
    pApp->activateIgnoringOtherApps(true);
  }

  virtual bool applicationShouldTerminateAfterLastWindowClosed(
      NS::Application *pSender) override {
    return true;
  }

private:
  NS::Window *_pWindow;
  MTK::View *_pMtkView;
  MTL::Device *_pDevice;
  ViewDelegate *_pViewDelegate = nullptr;
};

} // namespace eden