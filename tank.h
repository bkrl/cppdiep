#ifndef DIEPRL_TANK_H
#define DIEPRL_TANK_H

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

namespace dieprl {

class Tank : public Object {
public:
  float getRadius() const {
    return getB2Body().GetFixtureList()->GetShape()->m_radius;
  }
  virtual b2Vec2 getTarget() const = 0;
  float getTargetAngle() const {
    b2Vec2 target = getTarget();
    return std::atan2(target.y, target.x);
  }
  sf::Color getColor() const { return color; }
  virtual void draw(sf::RenderTarget &target) const;

protected:
  Tank(Arena &arena, b2World &b2_world, const b2Vec2 &position, float radius,
       const sf::Color &color);
  void drawBarrel(sf::RenderTarget &target, float length, float width,
                  float angle) const;
  void move(const b2Vec2 &vec) {
    getB2Body().ApplyForceToCenter(getMoveForce() * vec, true);
  }

private:
  friend Arena;

  virtual void drawBarrels(sf::RenderTarget &target) const = 0;
  virtual constexpr float getMoveForce() const = 0;

  sf::Color color;
};

} // namespace dieprl

#endif // DIEPRL_TANK_H
