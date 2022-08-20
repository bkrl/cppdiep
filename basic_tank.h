#ifndef DIEPRL_BASIC_TANK_H
#define DIEPRL_BASIC_TANK_H

#include <SFML/Graphics/RenderTarget.hpp>

#include "tank.h"

namespace dieprl {

class BasicTank : public Tank {
protected:
  using Tank::Tank;
  void fire();

private:
  void drawBarrels(sf::RenderTarget &target) const override;
  constexpr float getMoveForce() const override { return 15.f; }
};

} // namespace dieprl

#endif // DIEPRL_BASIC_TANK_H
