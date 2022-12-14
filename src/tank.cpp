// SPDX-FileCopyrightText: 2022 Alexander Zhang <alex@alexyzhang.dev>
//
// SPDX-License-Identifier: AGPL-3.0-or-later

#include "tank.h"

#include <cstdint>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <box2d/b2_body.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_math.h>
#include <box2d/b2_world.h>

#include "arena.h"
#include "box2d_categories.h"
#include "render_utils.h"

namespace cppdiep {

b2BodyDef Tank::makeB2BodyDef(const b2Vec2 &position) {
  b2BodyDef body_def;
  body_def.type = b2_dynamicBody;
  body_def.position = position;
  body_def.fixedRotation = true;
  body_def.linearDamping = 1.f;
  body_def.userData.pointer = reinterpret_cast<std::uintptr_t>(this);
  return body_def;
}

Tank::Tank(Arena &arena, const b2Vec2 &position, const float radius,
           const float max_health, const sf::Color &color)
    : Object(arena, makeB2BodyDef(position), max_health), color(color) {
  b2CircleShape body_shape;
  body_shape.m_radius = radius;
  b2FixtureDef fixture_def;
  fixture_def.shape = &body_shape;
  fixture_def.density = 1.f;
  fixture_def.restitution = 0.25f;
  fixture_def.filter.categoryBits = box2d_categories::TANK;
  fixture_def.filter.maskBits = box2d_categories::TANK |
                                box2d_categories::BORDER |
                                box2d_categories::BULLET;
  getB2Body().CreateFixture(&fixture_def);
}

void Tank::draw(sf::RenderTarget &target) const {
  drawCannons(target);
  drawCircle(target, getPosition(), getRadius(), getColor());
  if (getHealth() < getMaxHealth()) {
    drawHealthBar(target, getRadius() * 2.f, getRadius() * 1.25f);
  }
}

void Tank::drawCannon(sf::RenderTarget &target, const float length,
                      const float width, const float angle) const {
  sf::RectangleShape cannon_shape(sf::Vector2f(length, width));
  cannon_shape.setOrigin(0.f, width / 2.f);
  cannon_shape.setPosition(toSfVector2f(getPosition()));
  cannon_shape.setFillColor(colors::CANNON);
  cannon_shape.setOutlineThickness(-OUTLINE_THICKNESS);
  cannon_shape.setOutlineColor(darken(colors::CANNON));
  cannon_shape.setRotation(radiansToDegrees(angle));
  target.draw(cannon_shape);
}

} // namespace cppdiep
