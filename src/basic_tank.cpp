// SPDX-FileCopyrightText: 2022 Alexander Zhang <alex@alexyzhang.dev>
//
// SPDX-License-Identifier: AGPL-3.0-or-later

#include "basic_tank.h"

#include <cmath>

#include <SFML/Graphics/RenderTarget.hpp>
#include <box2d/b2_math.h>

#include "arena.h"
#include "bullet.h"

namespace cppdiep {

void BasicTank::drawCannons(sf::RenderTarget &target) const {
  drawCannon(target, 2 * getRadius(), getRadius(), getTargetAngle());
}

void BasicTank::fire() {
  if (getArena().getTime() < reload_complete_time) {
    return;
  }
  const auto reload_time = std::round(1.f / getArena().getTimeStep());
  reload_complete_time = getArena().getTime() + reload_time;
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
