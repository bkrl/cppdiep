#ifndef CPPDIEP_OBJECT_H
#define CPPDIEP_OBJECT_H

/// @file
/// Definition of the Object class.

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

  /// Destruct an object and destroy the object's Box2D body.
  virtual ~Object();

  /// Get the current position of the object.
  /// @return The current position of the object.
  b2Vec2 getPosition() const { return getB2Body().GetPosition(); }

  /// Get the current velocity of the object.
  /// @return The current velocity of the object.
  b2Vec2 getVelocity() const { return getB2Body().GetLinearVelocity(); }

  /// Get the current health of the object.
  /// @return The current health of the object.
  float getHealth() const { return health; }

  /// Draw the object to an SFML render target.
  /// @param target the SFML render target to draw to.
  virtual void draw(sf::RenderTarget &target) const = 0;

  /// Decrease the object's health.
  /// @param damage_amount the amount of damage inflicted.
  void damage(float damage_amount) { health -= damage_amount; }

protected:
  /// Construct an object. Objects should only be created by calling
  /// Arena::spawn().
  /// @param arena the arena that contains the object. The object will keep a
  /// reference to the arena.
  /// @param b2_body_def the Box2D body definition that will be used to create
  /// the object's body.
  /// @param max_health the maximum amount of health that the object can have.
  Object(Arena &arena, const b2BodyDef &b2_body_def, float max_health);

  /// Advance the state of the object by one time step and return whether the
  /// object should be destroyed now.
  /// @return Whether the object should be destroyed now.
  virtual bool step() { return getHealth() <= 0.f; }

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

  /// The arena that contains the object.
  Arena &arena;

  /// The Box2D body of the object.
  b2Body &b2_body;

  /// The amount of health that the object has.
  float health;
};

} // namespace cppdiep

#endif // CPPDIEP_OBJECT_H
