#ifndef CPPDIEP_BASIC_TANK_H
#define CPPDIEP_BASIC_TANK_H

/// @file
/// Definition of the BasicTank class.

#include <SFML/Graphics/RenderTarget.hpp>

#include "tank.h"

namespace cppdiep {

/// A tank with a single cannon.
class BasicTank : public Tank {
public:
  using Tank::Tank;

protected:
  void fire() override;

private:
  void drawCannons(sf::RenderTarget &target) const override;
  float getMoveForce() const override { return 15.f * getRadius(); }
};

} // namespace cppdiep

#endif // CPPDIEP_BASIC_TANK_H
