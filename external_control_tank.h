#ifndef CPPDIEP_EXTERNAL_CONTROL_TANK_H
#define CPPDIEP_EXTERNAL_CONTROL_TANK_H

#include <concepts>

#include <Box2D/Common/b2Math.h>

#include "tank.h"

namespace cppdiep {

/// A tank controlled externally using the move() and fire() methods.
/// @tparam BaseTank the type of the tank to be controlled externally.
template <std::derived_from<Tank> BaseTank>
class ExternalControlTank final : public BaseTank {
public:
  using BaseTank::BaseTank;

  /// Apply a force to move the tank in the direction of the given vector.
  /// @param vec a vector indicating the direction and speed to move in. A
  /// magnitude of 1 indicates full speed.
  void move(const b2Vec2 &vec) { BaseTank::move(vec); }

  /// @copydoc Tank::getTarget()
  b2Vec2 getTarget() const override { return target; }

  /// Set the target point of the tank. This is the point that the tank will aim
  /// towards.
  /// @param target the target point relative to the position of the tank.
  void setTarget(const b2Vec2 &target) { this->target = target; }

  /// Fire the tank's cannon(s).
  void fire() { BaseTank::fire(); }

private:
  /// The current target point of the tank.
  b2Vec2 target{0.f, 0.f};
};

} // namespace cppdiep

#endif // CPPDIEP_EXTERNAL_CONTROL_TANK_H
