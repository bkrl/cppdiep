// SPDX-FileCopyrightText: 2022 Alexander Zhang <alex@alexyzhang.dev>
//
// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef CPPDIEP_OBJECT_H
#define CPPDIEP_OBJECT_H

/// @file
/// Definition of the Object class.

#include <SFML/Graphics/RenderTarget.hpp>
#include <box2d/b2_body.h>
#include <box2d/b2_math.h>
#include <box2d/b2_world.h>

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
  b2Vec2 getPosition() const noexcept { return getB2Body().GetPosition(); }

  /// Get the current velocity of the object.
  /// @return The current velocity of the object.
  b2Vec2 getVelocity() const noexcept {
    return getB2Body().GetLinearVelocity();
  }

  /// Get the maximum possible health of the object.
  /// @return The maximum possible health of the object.
  float getMaxHealth() const noexcept { return max_health; }

  /// Get the current health of the object.
  /// @return The current health of the object.
  float getHealth() const noexcept { return health; }

  /// Draw the object to an SFML render target.
  /// @param target the SFML render target to draw to.
  virtual void draw(sf::RenderTarget &target) const = 0;

  /// Decrease the object's health.
  /// @param damage_amount the amount of damage inflicted.
  void damage(const float damage_amount) { health -= damage_amount; }

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
  Arena &getArena() const noexcept { return arena; }

  /// Get a reference to the Box2D body of the object.
  /// @return A reference to the Box2D body of the object.
  b2Body &getB2Body() noexcept { return b2_body; }

  /// @copydoc getB2Body()
  const b2Body &getB2Body() const noexcept { return b2_body; }

  /// Draw the object's health bar.
  /// @param target the SFML render target to draw to.
  /// @param width the width of the health bar.
  /// @param distance the distance from the origin of the object to the health
  /// bar.
  void drawHealthBar(sf::RenderTarget &target, float width,
                     float distance) const;

private:
  friend Arena;

  /// The arena that contains the object.
  Arena &arena;

  /// The Box2D body of the object.
  b2Body &b2_body;

  /// The maximum amount of health that the object can have.
  float max_health;

  /// The amount of health that the object has.
  float health;
};

} // namespace cppdiep

#endif // CPPDIEP_OBJECT_H
