module;

#include <bitset>

export module eden:world;
import :entity;
import :component;

namespace eden {

export class World {
public:
  template <typename... Ts> auto spawn(Ts... component) -> Entity * {
    auto entity = entities.create();

    (components.set<Ts>(entity, component), ...);

    return entity;
  }

  template <typename... Ts> struct View {
    View(World *world) : world(world) {
      if (sizeof...(Ts) == 0) {
        all = true;
      } else {
        int componentIds[] = {0, world->hash<Ts>()...};
        for (int i = 1; i < sizeof...(Ts) + 1; ++i) {
          mask.set(componentIds[i]);
        }
      }
    }
    struct Iterator {
      Iterator(World *world, std::size_t index,
               std::bitset<MAX_COMPONENTS> mask, bool all)
          : world(world), index(index), mask(mask), all(all) {}

      auto operator*() -> Entity * { return world->entities[index]; }
      auto operator==(const Iterator &other) const -> bool {
        return index == other.index || index == world->entities.size();
      }
      auto operator!=(const Iterator &other) const -> bool {
        return index != other.index && index != world->entities.size();
      }

      auto operator++() -> Iterator & {
        do {
          ++index;
        } while (index < world->entities.size() &&
                 !(all || (world->entities[index]->mask & mask) == mask));
        return *this;
      }

    private:
      World *world;
      std::size_t index;
      std::bitset<MAX_COMPONENTS> mask;
      bool all;
    };

    auto begin() const -> const Iterator {
      std::size_t index = 0;
      while (index < world->entities.size() &&
             (world->entities[index]->mask & mask) != mask)
        ++index;

      return Iterator(world, index, mask, all);
    }

    auto end() const -> const Iterator {
      return Iterator(world, world->entities.size(), mask, all);
    }

    World *world{nullptr};
    std::bitset<MAX_COMPONENTS> mask;
    bool all{false};
  };

  template <typename T> auto hash() -> int { return components.hash<T>(); }

  Entities entities;
  Components components;
};

}; // namespace eden