#include "bullet.h"

#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>
#include <SFML/Graphics/RenderTarget.hpp>

#include "arena.h"
#include "box2d_categories.h"
#include "render_utils.h"

namespace cppdiep {

namespace {
b2BodyDef makeB2BodyDef(const b2Vec2 &position, const b2Vec2 &velocity) {
  b2BodyDef body_def;
  body_def.type = b2_dynamicBody;
  body_def.position = position;
  body_def.linearVelocity = velocity;
  body_def.linearDamping = 0.5f;
  body_def.angularDamping = 0.5f;
  body_def.bullet = true;
  return body_def;
}
} // namespace

Bullet::Bullet(Arena &arena, const b2Vec2 &position, const b2Vec2 &velocity,
               const b2Vec2 &impulse, float radius, const sf::Color &color)
    : Object(arena, makeB2BodyDef(position, velocity)), color(color),
      destroy_time(arena.getTime() + 3.f / arena.getTimeStep()) {
  b2CircleShape body_shape;
  body_shape.m_radius = radius;
  b2FixtureDef fixture_def;
  fixture_def.shape = &body_shape;
  fixture_def.density = 1.f;
  fixture_def.restitution = 0.25f;
  fixture_def.filter.categoryBits = box2d_categories::BULLET;
  fixture_def.filter.maskBits =
      box2d_categories::BULLET | box2d_categories::TANK;
  getB2Body().CreateFixture(&fixture_def);
  getB2Body().ApplyLinearImpulse(impulse, getB2Body().GetWorldCenter(), true);
}

void Bullet::draw(sf::RenderTarget &target) const {
  drawCircle(target, getPosition(), getRadius(), color);
}

bool Bullet::step() {
  if (Object::step()) {
    return true;
  }
  return getArena().getTime() >= destroy_time;
}

} // namespace cppdiep
