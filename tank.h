#ifndef CPPDIEP_TANK_H
#define CPPDIEP_TANK_H

#include <Box2D/Collision/Shapes/b2Shape.h>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2World.h>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "arena.fwd.h"
#include "object.h"
#include "render_utils.h"

namespace cppdiep {

/// A generic tank.
class Tank : public Object {
public:
  /// Get the radius of the tank body.
  /// @return the radius of the tank body.
  float getRadius() const {
    return getB2Body().GetFixtureList()->GetShape()->m_radius;
  }

  /// Get the current target position of the tank.
  /// @return the target position of the tank relative to the tank's position.
  virtual b2Vec2 getTarget() const = 0;

  /// Get the direction of the tank's target relative to the tank.
  /// @return The direction of the tank's target as an angle in radians.
  float getTargetAngle() const {
    b2Vec2 target = getTarget();
    return std::atan2(target.y, target.x);
  }

  /// Get the color of the tank.
  /// @return The color of the tank.
  sf::Color getColor() const { return color; }

  void draw(sf::RenderTarget &target) const override;

protected:
  /// Construct a Tank.
  /// @param arena the arena that contains the tank.
  /// @param position the initial position of the tank.
  /// @param radius the radius of the tank's body.
  /// @param color the color of the tank.
  Tank(Arena &arena, const b2Vec2 &position, float radius,
       const sf::Color &color);

  /// Helper function for drawing cannons.
  /// @param target the SFML render target to draw to.
  /// @param length the length of the barrel. The barrel starts from the center
  /// of the tank.
  /// @param width the width of the barrel.
  /// @param angle the angle that the cannon is pointing towards in radians.
  void drawCannon(sf::RenderTarget &target, float length, float width,
                  float angle) const;

  /// Apply a force to move the tank.
  /// @param vec the direction and speed to move in. A magnitude of 1 represents
  /// full speed.
  void move(const b2Vec2 &vec) {
    getB2Body().ApplyForceToCenter(getMoveForce() * vec, true);
  }

  /// Fire the tank's cannon(s).
  virtual void fire() = 0;

private:
  friend Arena;

  /// Draw the tank's cannon(s).
  /// @param target the SFML render target to draw to.
  virtual void drawCannons(sf::RenderTarget &target) const = 0;

  /// Get the magnitude of the force used to move the tank.
  /// @param the magnitude of the force used to move the tank.
  virtual float getMoveForce() const = 0;

  /// The color of the tank.
  sf::Color color;
};

} // namespace cppdiep

#endif // CPPDIEP_TANK_H
