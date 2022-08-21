#ifndef CPPDIEP_ARENA_H
#define CPPDIEP_ARENA_H

#include "arena.fwd.h"

#include <concepts>
#include <cstdint>
#include <memory>
#include <vector>

#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2World.h>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "bullet.h"
#include "tank.h"
#include "time.h"

namespace cppdiep {

class Arena {
public:
  Arena(float size, float time_step);
  void draw(sf::RenderTarget &target) const;
  void step();
  template <std::derived_from<Tank> TankType>
  TankType &spawnTank(const b2Vec2 &position, float radius,
                      const sf::Color &color) {
    TankType *tank = new TankType(*this, b2_world, position, radius, color);
    tanks.emplace_back(tank);
    return *tank;
  }
  Bullet &spawnBullet(const b2Vec2 &position, const b2Vec2 &velocity,
                      const b2Vec2 &impulse, float radius,
                      const sf::Color &color) {
    Bullet *bullet =
        new Bullet(*this, b2_world, position, velocity, impulse, radius, color);
    bullets.emplace_back(bullet);
    return *bullet;
  }
  float getTimeStep() const { return time_step; }
  Time getTime() const { return time; }

private:
  template <std::derived_from<Object> ObjectType>
  using ObjectPtr = std::unique_ptr<ObjectType, typename ObjectType::Deleter>;
  template <std::derived_from<Object> ObjectType>
  using ObjectContainer = std::vector<ObjectPtr<ObjectType>>;

  template <std::derived_from<Object> ObjectType>
  static void cleanObjects(ObjectContainer<ObjectType> &objects);

  ObjectContainer<Tank> tanks;
  ObjectContainer<Bullet> bullets;
  b2World b2_world{b2Vec2(0.f, 0.f)};
  const float time_step;
  Time time = 0;
};

} // namespace cppdiep

#endif // CPPDIEP_ARENA_H
