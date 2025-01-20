module;

#include <bitset>

export module eden:query;

import :ecs;
import :entity;

namespace eden {

export template <typename... Ts> struct Query {
  Query(ECS *ecs) : ecs(ecs) {
    if (sizeof...(Ts) == 0) {
      all = true;
    } else {
      int componentIds[] = {0, ecs->hash<Ts>()...};
      for (int i = 1; i < sizeof...(Ts) + 1; ++i) {
        mask.set(componentIds[i]);
      }
    }
  }

  struct Iterator {
    Iterator(ECS *ecs, std::size_t index, std::bitset<MAX_COMPONENTS> mask,
             bool all)
        : ecs(ecs), index(index), mask(mask), all(all) {}

    auto operator*() -> Entity * { return ecs->entities[index]; }

    auto operator==(const Iterator &other) const -> bool {
      return index == other.index || index == ecs->entities.size();
    }

    auto operator!=(const Iterator &other) const -> bool {
      return index != other.index && index != ecs->entities.size();
    }

    auto operator++() -> Iterator & {
      do {
        ++index;
      } while (index < ecs->entities.size() &&
               !(all || (ecs->entities[index]->mask & mask) == mask));
      return *this;
    }

  private:
    ECS *ecs;
    std::size_t index;
    std::bitset<MAX_COMPONENTS> mask;
    bool all;
  };

  auto begin() const -> const Iterator {
    std::size_t index = 0;
    while (index < ecs->entities.size() &&
           (ecs->entities[index]->mask & mask) != mask)
      ++index;

    return Iterator(ecs, index, mask, all);
  }

  auto end() const -> const Iterator {
    return Iterator(ecs, ecs->entities.size(), mask, all);
  }

  ECS *ecs{nullptr};
  std::bitset<MAX_COMPONENTS> mask;
  bool all{false};
};

} // namespace eden