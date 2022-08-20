#include "arena.h"

#include <array>
#include <memory>

#include <Box2D/Collision/Shapes/b2ChainShape.h>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2World.h>
#include <SFML/Graphics/RenderTarget.hpp>

#include "bullet.h"
#include "render_utils.h"
#include "tank.h"
#include "time.h"

namespace dieprl {

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
  border_body.CreateFixture(&border_fixture_def);
}

void Arena::draw(sf::RenderTarget &target) const {
  target.clear(colors::BACKGROUND);
  for (const std::unique_ptr<Bullet, Bullet::Deleter> &bullet : bullets) {
    bullet->draw(target);
  }
  for (const std::unique_ptr<Tank, Tank::Deleter> &tank : tanks) {
    tank->draw(target);
  }
}

void Arena::step() {
  while (!bullets.empty() && bullets.front()->shouldDestroy()) {
    b2_world.DestroyBody(&bullets.front()->getB2Body());
    bullets.pop_front();
  }
  for (const std::unique_ptr<Tank, Tank::Deleter> &tank : tanks) {
    tank->step();
  }
  for (const std::unique_ptr<Bullet, Bullet::Deleter> &bullet : bullets) {
    bullet->step();
  }
  b2_world.Step(time_step, 8, 3);
  ++time;
}

} // namespace dieprl
