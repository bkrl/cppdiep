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

#include <Box2D/Collision/Shapes/b2ChainShape.h>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <SFML/Graphics/RenderTarget.hpp>

#include "box2d_categories.h"
#include "bullet.h"
#include "render_utils.h"
#include "tank.h"
#include "time.h"

namespace cppdiep {

void Arena::ContactListener::PostSolve(b2Contact *contact,
                                       const b2ContactImpulse *impulse) {
  auto user_data_a =
      static_cast<Object *>(contact->GetFixtureA()->GetBody()->GetUserData());
  auto user_data_b =
      static_cast<Object *>(contact->GetFixtureB()->GetBody()->GetUserData());
  if (!user_data_a || !user_data_b) {
    return;
  }
  float impulse_magnitude = std::hypot(
      std::accumulate(impulse->normalImpulses,
                      impulse->normalImpulses + impulse->count, 0.f),
      std::accumulate(impulse->tangentImpulses,
                      impulse->tangentImpulses + impulse->count, 0.f));
  if (impulse_magnitude > 0.f) {
    user_data_a->damage(impulse_magnitude);
    user_data_b->damage(impulse_magnitude);
  }
}

Arena::Arena(float size, float time_step) : time_step(time_step) {
  b2_world.SetContactListener(&contact_listener);
  b2BodyDef border_body_def;
  b2Body &border_body = *b2_world.CreateBody(&border_body_def);
  std::array border_vertices = {
      b2Vec2(size / 2.f, size / 2.f), b2Vec2(-size / 2.f, size / 2.f),
      b2Vec2(-size / 2.f, -size / 2.f), b2Vec2(size / 2.f, -size / 2.f)};
  b2ChainShape border_chain;
  border_chain.CreateLoop(border_vertices.data(), border_vertices.size());
  b2FixtureDef border_fixture_def;
  border_fixture_def.shape = &border_chain;
  border_fixture_def.friction = 0.25f;
  border_fixture_def.restitution = 0.25f;
  border_fixture_def.filter.categoryBits = box2d_categories::BORDER;
  border_fixture_def.filter.maskBits = box2d_categories::TANK;
  border_body.CreateFixture(&border_fixture_def);
}

void Arena::draw(sf::RenderTarget &target) const {
  target.clear(colors::BACKGROUND);
  for (const std::shared_ptr<Object> &object : objects) {
    object->draw(target);
  }
  // Tanks are drawn last so that their barrels are on top of other objects.
  for (const std::shared_ptr<Tank> &tank : tanks) {
    tank->draw(target);
  }
}

void Arena::step() {
  b2_world.Step(time_step, 8, 3);
  // Remove objects that need to be destroyed without preserving order.
  objects.erase(std::partition(objects.begin(), objects.end(),
                               [](const std::shared_ptr<Object> &object) {
                                 return !object->step();
                               }),
                objects.end());
  std::erase_if(tanks,
                [](const std::shared_ptr<Tank> &tank) { return tank->step(); });
  ++time;
}

} // namespace cppdiep
