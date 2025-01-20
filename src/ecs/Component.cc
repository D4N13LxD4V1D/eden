module;

#include <bitset>
#include <typeinfo>
#include <unordered_map>
#include <vector>

export module eden:component;

import :entity;

namespace eden {

export struct Component {
  Component(size_t size) : size(size) { data = new char[size * MAX_ENTITIES]; }
  ~Component() { delete[] data; }

  inline auto get(Entity *entity) -> void * { return data + entity->id * size; }

  char *data{nullptr};
  size_t size{0};
};

export class Components {
public:
  template <typename T> auto get(Entity *entity) -> T * {
    auto id = hash<T>();

    if (!entity->mask.test(id))
      return nullptr;

    return static_cast<T *>(components[id]->get(entity));
  }

  template <typename T> auto set(Entity *entity, T &component) -> T * {
    auto id = hash<T>();

    if (components.size() <= id)
      components.resize(id + 1, nullptr);

    if (components[id] == nullptr)
      components[id] = new Component(sizeof(T));

    auto pComponent = new (components[id]->get(entity)) T();
    *pComponent = component;

    entity->mask.set(id);

    return pComponent;
  }

  template <typename T> auto hash() -> int {
    static std::unordered_map<std::size_t, std::size_t> componentMap;
    auto id = typeid(T).hash_code();
    if (componentMap.find(id) == componentMap.end()) {
      componentMap[id] = components.size();
    }
    return componentMap[id];
  }

private:
  std::vector<Component *> components;
};

}; // namespace eden