#include "basic_tank.h"

#include <Box2D/Common/b2Math.h>
#include <SFML/Graphics/RenderTarget.hpp>

#include "arena.h"
#include "bullet.h"

namespace cppdiep {

void BasicTank::drawCannons(sf::RenderTarget &target) const {
  drawCannon(target, 2 * getRadius(), getRadius(), getTargetAngle());
}

void BasicTank::fire() {
  b2Vec2 target_vec = getTarget();
  target_vec.Normalize();
  const auto bullet_radius = getRadius() / 2.f;
  const auto impulse_magnitude = 10.f * getRadius();
  // The bullet is spawned in the barrel just outside of the tank body to avoid
  // teleportation due to the bullet intersecting the tank body. This causes
  // some teleportation if the spawned bullet intersects another object. In the
  // future, collisions between a bullet and the tank that fired it will be
  // disabled and the bullet will be spawned inside the tank body.
  getArena().spawn<Bullet>(
      getPosition() + (getRadius() + bullet_radius) * target_vec, getVelocity(),
      impulse_magnitude * target_vec, bullet_radius, getColor());
  // Simulate recoil by applying the same impulse in the opposite direction to
  // the tank.
  getB2Body().ApplyLinearImpulse(-impulse_magnitude * target_vec,
                                 getB2Body().GetWorldCenter(), true);
}

} // namespace cppdiep
