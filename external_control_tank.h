#ifndef CPPDIEP_EXTERNAL_CONTROL_TANK_H
#define CPPDIEP_EXTERNAL_CONTROL_TANK_H

#include <concepts>

#include <Box2D/Common/b2Math.h>

#include "tank.h"

namespace cppdiep {

template <std::derived_from<Tank> BaseTank>
class ExternalControlTank final : public BaseTank {
public:
  using BaseTank::BaseTank;
  void move(const b2Vec2 &vec) { BaseTank::move(vec); }
  b2Vec2 getTarget() const override { return target; }
  void setTarget(const b2Vec2 &target) { this->target = target; }
  void fire() { BaseTank::fire(); }

private:
  b2Vec2 target{0.f, 0.f};
};

} // namespace cppdiep

#endif // CPPDIEP_EXTERNAL_CONTROL_TANK_H
