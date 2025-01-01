import eden;

struct Position {
  int x;
  int y;
};

auto main() -> int {
  auto world = eden::World{};

  world.spawn(Position{24, 20});
  world.spawn(Position{30, 40});

  for (auto entity : eden::World::View<Position>{&world}) {
    auto position = world.components.get<Position>(entity);
    eden::log("Entity: {}\nPosition: {}, {}", entity->id, position->x,
              position->y);
  }

  return 0;
}