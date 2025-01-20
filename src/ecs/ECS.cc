export module eden:ecs;

import :entity;
import :component;
import :system;

namespace eden {

export struct ECS {
  template <typename... Ts> auto spawn(Ts... component) -> Entity * {
    auto entity = entities.create();
    (components.set<Ts>(entity, component), ...);
    return entity;
  }

  template <typename... Ts> auto add_systems(Ts... system) -> void {}

  template <typename T> auto hash() -> int { return components.hash<T>(); }

  Entities entities;
  Components components;
  Systems systems;
};

}; // namespace eden