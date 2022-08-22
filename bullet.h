#ifndef CPPDIEP_BULLET_H
#define CPPDIEP_BULLET_H

#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2World.h>
#include <SFML/Graphics/RenderTarget.hpp>

#include "arena.fwd.h"
#include "object.h"
#include "render_utils.h"
#include "time.h"

namespace cppdiep {

/// A bullet fired from a cannon. Bullets disappear after three seconds.
class Bullet : public Object {
public:
  /// Get the radius of the bullet.
  /// @return The radius of the bullet.
  float getRadius() const {
    return getB2Body().GetFixtureList()->GetShape()->m_radius;
  }

  void draw(sf::RenderTarget &target) const override;

protected:
  /// Construct a bullet.
  /// @param arena the arena that contains the bullet.
  /// @param b2_world the Box2D world where the b2Body of the bullet will be
  /// created.
  /// @param position the initial position of the bullet.
  /// @param velocity the initial velocity of the bullet.
  /// @param impulse the impulse applied to the bullet on top of the initial
  /// velocity.
  /// @param radius the radius of the bullet.
  /// @param color the color of the bullet.
  Bullet(Arena &arena, b2World &b2_world, const b2Vec2 &position,
         const b2Vec2 &velocity, const b2Vec2 &impulse, float radius,
         const sf::Color &color);

private:
  friend Arena;

  bool shouldDestroy() const override;

  /// The color of the bullet.
  sf::Color color;

  /// The time when the bullet should be destroyed.
  Time destroy_time;
};

} // namespace cppdiep

#endif // CPPDIEP_BULLET_H
