#ifndef CPPDIEP_BASIC_TANK_H
#define CPPDIEP_BASIC_TANK_H

#include <SFML/Graphics/RenderTarget.hpp>

#include "tank.h"

namespace cppdiep {

class BasicTank : public Tank {
protected:
  using Tank::Tank;
  void fire();

private:
  void drawCannons(sf::RenderTarget &target) const override;
  constexpr float getMoveForce() const override { return 15.f; }
};

} // namespace cppdiep

#endif // CPPDIEP_BASIC_TANK_H
