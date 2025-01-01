import eden;

auto main() -> int {
  eden::EventQueue eventQueue;
  eden::Window window{"Hello, World!", 800, 600, &eventQueue};

  window.show();

  while (!eventQueue.empty()) {
    auto event = eventQueue.pop();
  }

  return 0;
}