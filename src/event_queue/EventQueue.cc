module;

#include <queue>

export module eden:event_queue;

export import :event;

namespace eden {

export class EventQueue {
public:
  auto pop() -> Event * {
    if (events.empty())
      return nullptr;

    auto event = events.front();
    events.pop();
    return event;
  }

  auto push(Event *event) -> void { events.push(event); }

  auto empty() -> bool { return events.empty(); }

private:
  std::queue<Event *> events;
};

} // namespace eden