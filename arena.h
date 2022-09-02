#ifndef CPPDIEP_ARENA_H
#define CPPDIEP_ARENA_H

/// @file
/// Definition of the Arena class.

#include "arena.fwd.h"

#include <concepts>
#include <cstdint>
#include <memory>
#include <set>
#include <utility>
#include <vector>

#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2World.h>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "bullet.h"
#include "tank.h"
#include "time.h"

namespace cppdiep {

/// The Arena class manages all of the objects in the game.
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

  /// Spawn an object in the arena.
  /// @tparam ObjectType the type of the object to spawn.
  /// @tparam Args the type of the arguments forwarded to the object's
  /// constructor.
  /// @param args the arguments to be forwarded to the object's constructor.
  /// @return A reference to the new object.
  template <std::derived_from<Object> ObjectType, typename... Args>
  ObjectType &spawn(Args &&...args) {
    ObjectType *object = new ObjectType(*this, std::forward<Args>(args)...);
    if constexpr (std::derived_from<ObjectType, Tank>) {
      tanks.emplace(object);
    } else {
      objects.emplace_back(object);
    }
    return *object;
  }

  /// Get the time step size.
  /// @return The time step size.
  float getTimeStep() const { return time_step; }

  /// Get the current time.
  /// @return The current time in steps.
  Time getTime() const { return time; }

private:
  friend Object;

  /// Alias for the type of the smart pointers used to store the polymorphic
  /// objects.
  /// @tparam ObjectType the type of the object that the pointer points to.
  template <std::derived_from<Object> ObjectType>
  using ObjectPtr = std::unique_ptr<ObjectType>;

  /// Get the arena's Box2D world.
  /// @return A reference to the arena's Box2D world.
  b2World &getB2World() { return b2_world; }

  /// @copydoc getB2World()
  const b2World &getB2World() const { return b2_world; }

  /// The Box2D world of the arena. The gravity vector is zero since the world
  /// is horizontal. This has to be destructed after all of the objects have
  /// been destructed since the destructors of the objects will access the world
  /// to destroy their bodies.
  b2World b2_world{b2Vec2(0.f, 0.f)};

  /// Container of all of the objects in the arena except for tanks.
  std::vector<ObjectPtr<Object>> objects;

  /// Tank radius comparison functor passed to the multiset that stores tanks.
  struct TankRadiusCompare {
    bool operator()(const ObjectPtr<Tank> &a, const ObjectPtr<Tank> &b) const {
      return a->getRadius() < b->getRadius();
    }
  };

  /// Container of all of the tanks in the arena. Tank barrels can overlap with
  /// other objects, so they have to be drawn after other objects from smallest
  /// to biggest.
  std::multiset<ObjectPtr<Tank>, TankRadiusCompare> tanks;

  /// The number of seconds in each time step.
  const float time_step;

  /// The current time as the number of time steps since the arena was created.
  Time time = 0;
};

} // namespace cppdiep

#endif // CPPDIEP_ARENA_H
