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

class Bullet : public Object {
public:
  float getRadius() const {
    return getB2Body().GetFixtureList()->GetShape()->m_radius;
  }
  void draw(sf::RenderTarget &target) const override;

protected:
  Bullet(Arena &arena, b2World &b2_world, const b2Vec2 &position,
         const b2Vec2 &velocity, const b2Vec2 &impulse, float radius,
         const sf::Color &color);

private:
  friend Arena;

  bool shouldDestroy() const override;

  sf::Color color;
  Time destroy_time;
};

} // namespace cppdiep

#endif // CPPDIEP_BULLET_H
