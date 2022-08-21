#include "basic_tank.h"

#include <cmath>

#include <Box2D/Common/b2Math.h>
#include <SFML/Graphics/RenderTarget.hpp>

#include "arena.h"
#include "bullet.h"

namespace cppdiep {

void BasicTank::drawCannons(sf::RenderTarget &target) const {
  float radius = getRadius();
  drawCannon(target, 2 * radius, radius, getTargetAngle());
}

void BasicTank::fire() {
  b2Vec2 target_vec = getTarget();
  target_vec.Normalize();
  float bullet_radius = getRadius() / 2.f;
  float impulse_magnitude = 10.f * getRadius();
  getArena().spawnBullet(
      getPosition() + (getRadius() + bullet_radius) * target_vec, getVelocity(),
      impulse_magnitude * target_vec, bullet_radius, getColor());
  getB2Body().ApplyLinearImpulse(-impulse_magnitude * target_vec,
                                 getB2Body().GetWorldCenter(), true);
}

} // namespace cppdiep
