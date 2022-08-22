#include "arena.h"

#include <array>
#include <concepts>
#include <memory>
#include <utility>
#include <vector>

#include <Box2D/Collision/Shapes/b2ChainShape.h>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2World.h>
#include <SFML/Graphics/RenderTarget.hpp>

#include "box2d_categories.h"
#include "bullet.h"
#include "render_utils.h"
#include "tank.h"
#include "time.h"

namespace cppdiep {

Arena::Arena(float size, float time_step) : time_step(time_step) {
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
  for (const ObjectPtr<Object> &object : objects) {
    object->draw(target);
  }
  // Tanks are drawn last so that their barrels are on top of other objects.
  for (const ObjectPtr<Tank> &tank : tanks) {
    tank->draw(target);
  }
}

void Arena::step() {
  // Replace objects that need to be destroyed with objects moved from the end
  // of the vector. Iterating in reverse simplifies things since we don't have
  // to worry about skipping over objects when removing an object.
  auto new_end = objects.end();
  for (auto it = objects.rbegin(); it != objects.rend(); ++it) {
    if ((*it)->step()) {
      *it = std::move(*--new_end);
    }
  }
  objects.erase(new_end, objects.end());
  // The tanks have to be rendered in a consistent order because their barrels
  // may overlap with other tanks.
  std::erase_if(tanks,
                [](const ObjectPtr<Tank> &tank) { return tank->step(); });
  b2_world.Step(time_step, 8, 3);
  ++time;
}

} // namespace cppdiep
