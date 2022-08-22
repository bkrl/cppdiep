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

/// @brief The Arena class manages all of the objects in the game.
class Arena {
public:
  /// Construct an arena.
  /// @param size the side length of the arena.
  /// @param time_step the number of seconds that each time step represents.
  Arena(float size, float time_step);

  /// Draw the arena to an SFML render target.
  /// @param target the SFML render target to draw to.
  void draw(sf::RenderTarget &target) const;

  /// Advance the state of the arena by one time step.
  void step();

  /// Spawn a tank in the arena.
  /// @tparam TankType the type of the tank to spawn
  /// @param position the position where the tank is spawned.
  /// @param radius the radius of the new tank.
  /// @param color the color of the new tank.
  /// @return A reference to the new tank.
  template <std::derived_from<Tank> TankType>
  TankType &spawnTank(const b2Vec2 &position, float radius,
                      const sf::Color &color) {
    TankType *tank = new TankType(*this, b2_world, position, radius, color);
    tanks.emplace_back(tank);
    return *tank;
  }

  /// Spawn a bullet in the arena.
  /// @param position the position where the bullet is spawned.
  /// @param velocity the initial velocity of the bullet. This should be set to
  /// the velocity of the tank that fired the bullet.
  /// @param impulse the impulse applied to the bullet on top of the initial
  /// velocity.
  /// @param radius the radius of the new bullet.
  /// @param color the color of the new bullet.
  /// @return A reference to the new bullet.
  Bullet &spawnBullet(const b2Vec2 &position, const b2Vec2 &velocity,
                      const b2Vec2 &impulse, float radius,
                      const sf::Color &color) {
    Bullet *bullet =
        new Bullet(*this, b2_world, position, velocity, impulse, radius, color);
    bullets.emplace_back(bullet);
    return *bullet;
  }

  /// Get the time step size.
  /// @return The time step size.
  float getTimeStep() const { return time_step; }

  /// Get the current time.
  /// @return the current time in steps.
  Time getTime() const { return time; }

private:
  /// Alias for the type of the smart pointers used to store the polymorphic
  /// objects.
  /// @tparam ObjectType the type of the object that the pointer points to.
  template <std::derived_from<Object> ObjectType>
  using ObjectPtr = std::unique_ptr<ObjectType, typename ObjectType::Deleter>;

  /// Alias for the type of the container used to store objects.
  /// @tparam ObjectType the type of the objects stored in the container.
  template <std::derived_from<Object> ObjectType>
  using ObjectContainer = std::vector<ObjectPtr<ObjectType>>;

  /// Destroy objects whose Object::shouldDestroy() methods return true.
  /// @tparam ObjectType the type of the objects in the container to be cleaned.
  /// @param objects the container of objects to be cleaned.
  template <std::derived_from<Object> ObjectType>
  void cleanObjects(ObjectContainer<ObjectType> &objects);

  /// Container of all of the tanks in the arena.
  ObjectContainer<Tank> tanks;

  /// Container of all of the bullets in the arena. Bullets and tanks are stored
  /// separately because bullets need to be rendered before tanks.
  ObjectContainer<Bullet> bullets;

  /// The Box2D world of the arena. The gravity vector is zero since the world
  /// is horizontal.
  b2World b2_world{b2Vec2(0.f, 0.f)};

  /// The number of seconds in each time step.
  const float time_step;

  /// The current time as the number of time steps since the arena was created.
  Time time = 0;
};

} // namespace cppdiep

#endif // CPPDIEP_ARENA_H
