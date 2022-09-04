#ifndef CPPDIEP_SIMPLE_AI_TANK_H
#define CPPDIEP_SIMPLE_AI_TANK_H

/// @file
/// Definition of the SimpleAITank class template.

#include <concepts>
#include <memory>

#include <Box2D/Common/b2Math.h>

#include "object.h"
#include "tank.fwd.h"

namespace cppdiep {

/// A tank that always moves and fires towards a target object.
/// @tparam BaseTank the type of the tank to be controlled by the simple AI.
template <std::derived_from<Tank> BaseTank>
class SimpleAITank final : public BaseTank {
public:
  using BaseTank::BaseTank;

  void setTargetObject(std::weak_ptr<Object> target_object) {
    this->target_object = std::move(target_object);
  }

  b2Vec2 getTarget() const override {
    if (auto locked_target_object = target_object.lock()) {
      return locked_target_object->getPosition() - this->getPosition();
    } else {
      return b2Vec2(0.f, 0.f);
    }
  }

protected:
  bool step() override {
    if (BaseTank::step()) {
      return true;
    }
    if (auto locked_target_object = target_object.lock()) {
      this->fire();
      auto target_vec =
          locked_target_object->getPosition() - this->getPosition();
      target_vec.Normalize();
      this->move(target_vec);
    }
    return false;
  }

private:
  std::weak_ptr<Object> target_object;
};

} // namespace cppdiep

#endif // CPPDIEP_SIMPLE_AI_TANK_H
