module;

#include <bitset>
#include <typeinfo>
#include <unordered_map>
#include <vector>

export module eden:system;

import :entity;

namespace eden {

export struct System {
  System(size_t size) : size(size) { data = new char[size * MAX_ENTITIES]; }
  ~System() { delete[] data; }

  inline auto get(Entity *entity) -> void * { return data + entity->id * size; }

  char *data{nullptr};
  size_t size{0};
};

export class Systems {
public:
  template <typename T> auto get(Entity *entity) -> T * {
    auto id = hash<T>();

    if (!entity->mask.test(id))
      return nullptr;

    return static_cast<T *>(systems[id]->get(entity));
  }

  template <typename T> auto set(Entity *entity, T &system) -> T * {
    auto id = hash<T>();

    if (systems.size() <= id)
      systems.resize(id + 1, nullptr);

    if (systems[id] == nullptr)
      systems[id] = new System(sizeof(T));

    auto pSystem = new (systems[id]->get(entity)) T();
    *pSystem = system;

    entity->mask.set(id);

    return pSystem;
  }

  template <typename T> auto hash() -> int {
    static std::unordered_map<std::size_t, std::size_t> systemMap;
    auto id = typeid(T).hash_code();
    if (systemMap.find(id) == systemMap.end()) {
      systemMap[id] = systems.size();
    }
    return systemMap[id];
  }

private:
  std::vector<System *> systems;
};

}; // namespace eden