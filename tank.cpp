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
#include "render_utils.h"

namespace dieprl {

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
  getB2Body().CreateFixture(&fixture_def);
}

void Tank::draw(sf::RenderTarget &target) const {
  drawBarrels(target);
  drawCircle(target, getPosition(), getRadius(), getColor());
}

void Tank::drawBarrel(sf::RenderTarget &target, float length, float width,
                      float angle) const {
  sf::RectangleShape barrel_shape(sf::Vector2f(length, width));
  barrel_shape.setOrigin(0.f, width / 2.f);
  barrel_shape.setPosition(convertVector(getPosition()));
  barrel_shape.setFillColor(colors::BARREL);
  barrel_shape.setOutlineThickness(OUTLINE_THICKNESS);
  barrel_shape.setOutlineColor(darken(colors::BARREL));
  barrel_shape.setRotation(radiansToDegrees(angle));
  target.draw(barrel_shape);
}

} // namespace dieprl
