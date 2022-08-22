#ifndef CPPDIEP_OBJECT_H
#define CPPDIEP_OBJECT_H

#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>
#include <SFML/Graphics/RenderTarget.hpp>

#include "arena.fwd.h"

namespace cppdiep {

/// A game object, such as a tank, a bullet, or a polygon.
class Object {
public:
  Object(const Object &) = delete;

  /// Get the current position of the object.
  /// @return The current position of the object.
  b2Vec2 getPosition() const { return getB2Body().GetPosition(); }

  /// Get the current velocity of the object.
  /// @return The current velocity of the object.
  b2Vec2 getVelocity() const { return getB2Body().GetLinearVelocity(); }

  /// Draw the object to an SFML render target.
  /// @param target the SFML render target to draw to.
  virtual void draw(sf::RenderTarget &target) const = 0;

protected:
  /// Construct an object.
  /// @param arena the arena that contains the object. The object will keep a
  /// reference to the arena so the
  /// @param b2_body_def the Box2D body definition that will be used to create
  /// the object's body.
  Object(Arena &arena, const b2BodyDef &b2_body_def);

  /// Destruct an object.
  virtual ~Object();

  /// Advance the state of the object by one time step and return whether the
  /// object should be destroyed now.
  /// @return Whether the object should be destroyed now.
  virtual bool step() {
    // Health and damage haven't been implemented yet so this just returns
    // false.
    return false;
  }

  /// Get a reference to the arena that contains the object.
  /// @return A reference to the arena that contains the object.
  Arena &getArena() const { return arena; }

  /// Get a reference to the Box2D body of the object.
  /// @return A reference to the Box2D body of the object.
  b2Body &getB2Body() { return b2_body; }

  /// @copydoc getB2Body()
  const b2Body &getB2Body() const { return b2_body; }

private:
  friend Arena;

  /// A deleter that the arena passes to the smart pointer. This is necessary
  /// since the destructor is not public.
  struct Deleter {
    void operator()(Object *object) const { delete object; }
  };

  /// The arena that contains the object.
  Arena &arena;

  /// The Box2D body of the object.
  b2Body &b2_body;
};

} // namespace cppdiep

#endif // CPPDIEP_OBJECT_H
