#include "arena.h"

#include <array>
#include <concepts>
#include <memory>
#include <utility>

#include <Box2D/Collision/Shapes/b2ChainShape.h>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2World.h>
#include <SFML/Graphics/RenderTarget.hpp>

#include "b2_categories.h"
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
  border_fixture_def.filter.categoryBits = b2_categories::BORDER;
  border_fixture_def.filter.maskBits = b2_categories::TANK;
  border_body.CreateFixture(&border_fixture_def);
}

void Arena::draw(sf::RenderTarget &target) const {
  target.clear(colors::BACKGROUND);
  // Bullets are drawn first so that they are underneath the tank barrels.
  for (const ObjectPtr<Bullet> &bullet : bullets) {
    bullet->draw(target);
  }
  for (const ObjectPtr<Tank> &tank : tanks) {
    tank->draw(target);
  }
}

template <std::derived_from<Object> ObjectType>
void Arena::cleanObjects(ObjectContainer<ObjectType> &objects) {
  // Replace objects that need to be destroyed with objects moved from the end
  // of the vector. Iterating in reverse simplifies things since we don't have
  // to worry about skipping over objects when removing an object.
  auto new_end = objects.end();
  for (auto it = objects.rbegin(); it != objects.rend(); ++it) {
    if ((*it)->shouldDestroy()) {
      b2_world.DestroyBody(&(*it)->getB2Body());
      *it = std::move(*--new_end);
    }
  }
  objects.erase(new_end, objects.end());
}

void Arena::step() {
  cleanObjects(bullets);
  cleanObjects(tanks);
  for (const ObjectPtr<Tank> &tank : tanks) {
    tank->step();
  }
  for (const ObjectPtr<Bullet> &bullet : bullets) {
    bullet->step();
  }
  b2_world.Step(time_step, 8, 3);
  ++time;
}

} // namespace cppdiep
