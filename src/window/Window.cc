module;

#include <AppKit/AppKit.hpp>

export module eden:window;

import :app_delegate;
import :event_queue;

namespace eden {

export class Window {
public:
  Window() {
    auto pAutoreleasePool = NS::AutoreleasePool::alloc()->init();

    AppDelegate del;

    auto pSharedApplication = NS::Application::sharedApplication();
    pSharedApplication->setDelegate(&del);
    pSharedApplication->run();

    pAutoreleasePool->release();
  };
};

} // namespace eden