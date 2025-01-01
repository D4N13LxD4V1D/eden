module;

#include <bitset>
#include <vector>

export module eden:entity;

namespace eden {

export const int MAX_ENTITIES = 5000;
export const int MAX_COMPONENTS = 32;

export struct Entity {
  std::size_t id;
  std::bitset<MAX_COMPONENTS> mask;
};

export class Entities {
public:
  auto create() -> Entity * {
    if (!availableEntities.empty()) {
      auto entity = availableEntities.back();
      availableEntities.pop_back();

      entities.push_back(entity);
      return &entities.back();
    }

    entities.push_back(Entity{});
    return &entities.back();
  }

  auto destroy(Entity *entity) -> void {
    entity->mask.reset();
    availableEntities.push_back(*entity);
  }

  inline auto operator[](int entity) -> Entity * { return &entities[entity]; }

  inline auto size() -> std::size_t { return entities.size(); }

private:
  std::vector<Entity> entities;
  std::vector<Entity> availableEntities;
};

}; // namespace eden