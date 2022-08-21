#include "tank.h"

#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2World.h>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "arena.h"
#include "b2_categories.h"
#include "render_utils.h"

namespace cppdiep {

namespace {
b2BodyDef makeB2BodyDef(const b2Vec2 &position) {
  b2BodyDef body_def;
  body_def.type = b2_dynamicBody;
  body_def.position = position;
  body_def.fixedRotation = true;
  body_def.linearDamping = 1.f;
  return body_def;
}
} // namespace

Tank::Tank(Arena &arena, b2World &b2_world, const b2Vec2 &position,
           float radius, const sf::Color &color)
    : Object(arena, b2_world, makeB2BodyDef(position)), color(color) {
  b2CircleShape body_shape;
  body_shape.m_radius = radius;
  b2FixtureDef fixture_def;
  fixture_def.shape = &body_shape;
  fixture_def.density = 1.f;
  fixture_def.friction = 0.3f;
  fixture_def.restitution = 0.25f;
  fixture_def.filter.categoryBits = b2_categories::TANK;
  fixture_def.filter.maskBits =
      b2_categories::TANK | b2_categories::BORDER | b2_categories::BULLET;
  getB2Body().CreateFixture(&fixture_def);
}

void Tank::draw(sf::RenderTarget &target) const {
  drawCannons(target);
  drawCircle(target, getPosition(), getRadius(), getColor());
}

void Tank::drawCannon(sf::RenderTarget &target, float length, float width,
                      float angle) const {
  sf::RectangleShape cannon_shape(sf::Vector2f(length, width));
  cannon_shape.setOrigin(0.f, width / 2.f);
  cannon_shape.setPosition(convertVector(getPosition()));
  cannon_shape.setFillColor(colors::CANNON);
  cannon_shape.setOutlineThickness(OUTLINE_THICKNESS);
  cannon_shape.setOutlineColor(darken(colors::CANNON));
  cannon_shape.setRotation(radiansToDegrees(angle));
  target.draw(cannon_shape);
}

} // namespace cppdiep
