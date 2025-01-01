module;

#include <Window/Window.hh>

export module eden:window;
import :event_queue;

namespace eden {

export class Window : public RawWindow {
public:
  Window(const char *title, int width, int height, EventQueue *eventQueue)
      : RawWindow(title, width, height) {
    this->eventQueue = eventQueue;
  };

private:
  void *eventQueue;
  void *window;
};

} // namespace eden