#include "basic_tank.h"

#include <cmath>

#include <Box2D/Common/b2Math.h>
#include <SFML/Graphics/RenderTarget.hpp>

#include "arena.h"
#include "bullet.h"

namespace dieprl {

void BasicTank::drawBarrels(sf::RenderTarget &target) const {
  float radius = getRadius();
  drawBarrel(target, 2 * radius, radius, getTargetAngle());
}

void BasicTank::fire() {
  b2Vec2 target_vec = getTarget();
  target_vec.Normalize();
  float bullet_radius = getRadius() / 2.f;
  constexpr float impulse_magnitude = 10.f;
  getArena().spawnBullet(
      getPosition() + (getRadius() + bullet_radius) * target_vec, getVelocity(),
      impulse_magnitude * target_vec, bullet_radius, getColor());
  getB2Body().ApplyLinearImpulse(-impulse_magnitude * target_vec,
                                 getB2Body().GetWorldCenter(), true);
}

} // namespace dieprl
