export module eden:event;

namespace eden {

export struct WindowEvent {
  enum class Type { Close, Resize } type;
};

export struct Event {
  enum class Type { WindowEvent } type;

  union {
    WindowEvent window;
  };
};

} // namespace eden