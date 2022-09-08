#include "arena.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <concepts>
#include <memory>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

#include <SFML/Graphics/RenderTarget.hpp>
#include <box2d/b2_body.h>
#include <box2d/b2_chain_shape.h>
#include <box2d/b2_contact.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_math.h>
#include <box2d/b2_world.h>
#include <box2d/b2_world_callbacks.h>

#include "box2d_categories.h"
#include "bullet.h"
#include "render_utils.h"
#include "tank.h"
#include "time.h"

namespace cppdiep {

void Arena::ContactListener::PostSolve(b2Contact *const contact,
                                       const b2ContactImpulse *const impulse) {
  const auto object_a = reinterpret_cast<Object *>(
      contact->GetFixtureA()->GetBody()->GetUserData().pointer);
  const auto object_b = reinterpret_cast<Object *>(
      contact->GetFixtureB()->GetBody()->GetUserData().pointer);
  if (!object_a || !object_b) {
    return;
  }
  const auto impulse_magnitude = std::hypot(
      std::accumulate(impulse->normalImpulses,
                      impulse->normalImpulses + impulse->count, 0.f),
      std::accumulate(impulse->tangentImpulses,
                      impulse->tangentImpulses + impulse->count, 0.f));
  // Box2D sometimes reports contacts with zero impulse and damage animations
  // might be added in the future so we don't want to call Object::damage() if
  // the impulse is zero.
  if (impulse_magnitude > 0.f) {
    object_a->damage(impulse_magnitude);
    object_b->damage(impulse_magnitude);
  }
}

Arena::Arena(const float size, const float time_step) : time_step(time_step) {
  b2_world.SetContactListener(&contact_listener);
  b2BodyDef border_body_def;
  b2Body &border_body = *b2_world.CreateBody(&border_body_def);
  std::array border_vertices = {
      b2Vec2(size / 2.f, size / 2.f), b2Vec2(size / 2.f, -size / 2.f),
      b2Vec2(-size / 2.f, -size / 2.f), b2Vec2(-size / 2.f, size / 2.f)};
  b2ChainShape border_chain;
  border_chain.CreateLoop(border_vertices.data(), border_vertices.size());
  b2FixtureDef border_fixture_def;
  border_fixture_def.shape = &border_chain;
  border_fixture_def.restitution = 0.25f;
  border_fixture_def.filter.categoryBits = box2d_categories::BORDER;
  border_fixture_def.filter.maskBits = box2d_categories::TANK;
  border_body.CreateFixture(&border_fixture_def);
}

void Arena::draw(sf::RenderTarget &target) const {
  target.clear(colors::BACKGROUND);
  for (const auto &object : objects) {
    object->draw(target);
  }
  // Tanks are drawn last so that their barrels are on top of other objects.
  for (const auto &tank : tanks) {
    tank->draw(target);
  }
}

void Arena::step() {
  b2_world.Step(time_step, 8, 3);
  // Remove objects that need to be destroyed without preserving order.
  objects.erase(
      std::partition(objects.begin(), objects.end(),
                     [](const auto &object) { return !object->step(); }),
      objects.end());
  std::erase_if(tanks, [](const auto &tank) { return tank->step(); });
  ++time;
}

} // namespace cppdiep
