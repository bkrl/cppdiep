// SPDX-FileCopyrightText: 2022 Alexander Zhang <alex@alexyzhang.dev>
//
// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef CPPDIEP_BULLET_H
#define CPPDIEP_BULLET_H

/// @file
/// Definition of the Bullet class.

#include <SFML/Graphics/RenderTarget.hpp>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_math.h>
#include <box2d/b2_world.h>

#include "arena.fwd.h"
#include "object.h"
#include "render_utils.h"
#include "time.h"

namespace cppdiep {

/// A bullet fired from a cannon. Bullets disappear after three seconds.
class Bullet : public Object {
public:
  /// Construct a bullet.
  /// @param arena the arena that contains the bullet.
  /// @param position the initial position of the bullet.
  /// @param velocity the initial velocity of the bullet.
  /// @param impulse the impulse applied to the bullet on top of the initial
  /// velocity.
  /// @param radius the radius of the bullet.
  /// @param color the color of the bullet.
  Bullet(Arena &arena, const b2Vec2 &position, const b2Vec2 &velocity,
         const b2Vec2 &impulse, float radius, const sf::Color &color);

  /// Get the radius of the bullet.
  /// @return The radius of the bullet.
  float getRadius() const noexcept {
    return getB2Body().GetFixtureList()->GetShape()->m_radius;
  }

  void draw(sf::RenderTarget &target) const override;

protected:
  bool step() override;

private:
  friend Arena;

  /// Make the Box2D body definition for the bullet.
  /// @param position the initial position of the bullet.
  /// @param velocity the initial velocity of the bullet.
  /// @return The Box2D body definition for the bullet.
  b2BodyDef makeB2BodyDef(const b2Vec2 &position, const b2Vec2 &velocity);

  /// The color of the bullet.
  sf::Color color;

  /// The time when the bullet should be destroyed.
  Time destroy_time;
};

} // namespace cppdiep

#endif // CPPDIEP_BULLET_H
