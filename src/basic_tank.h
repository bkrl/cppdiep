// SPDX-FileCopyrightText: 2022 Alexander Zhang <alex@alexyzhang.dev>
//
// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef CPPDIEP_BASIC_TANK_H
#define CPPDIEP_BASIC_TANK_H

/// @file
/// Definition of the BasicTank class.

#include <SFML/Graphics/RenderTarget.hpp>

#include "tank.h"
#include "time.h"

namespace cppdiep {

/// A tank with a single cannon.
class BasicTank : public Tank {
public:
  /// Construct a basic tank.
  /// @param arena the arena that the tank belongs to.
  /// @param position the initial position of the tank.
  /// @param radius the radius of the tank.
  /// @param color the color of the tank.
  BasicTank(Arena &arena, const b2Vec2 &position, const float radius,
            const sf::Color &color)
      : Tank(arena, position, radius, 100.f * radius * radius, color) {}

protected:
  void fire() override;

private:
  void drawCannons(sf::RenderTarget &target) const override;
  float getMoveForce() const noexcept override { return 15.f * getRadius(); }

  /// Time when the tank can fire again.
  Time reload_complete_time = 0;
};

} // namespace cppdiep

#endif // CPPDIEP_BASIC_TANK_H
