#include "object.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

#include "arena.h"
#include "render_utils.h"

namespace cppdiep {

Object::Object(Arena &arena, const b2BodyDef &b2_body_def,
               const float max_health)
    : arena(arena), b2_body(*arena.getB2World().CreateBody(&b2_body_def)),
      max_health(max_health), health(max_health) {}

Object::~Object() { arena.getB2World().DestroyBody(&b2_body); }

void Object::drawHealthBar(sf::RenderTarget &target, const float width,
                           const float distance) const {
  constexpr auto height = 0.25f;
  sf::RectangleShape background(sf::Vector2f(width, height));
  background.setOrigin(width / 2.f, height + OUTLINE_THICKNESS);
  background.setPosition(getPosition().x, getPosition().y - distance);
  background.setFillColor(colors::HEALTH_BAR_BG);
  background.setOutlineThickness(OUTLINE_THICKNESS);
  background.setOutlineColor(colors::HEALTH_BAR_BG);
  target.draw(background);
  sf::RectangleShape foreground(
      sf::Vector2f(width * (getHealth() / getMaxHealth()), height));
  foreground.setOrigin(width / 2.f, height + OUTLINE_THICKNESS);
  foreground.setPosition(getPosition().x, getPosition().y - distance);
  foreground.setFillColor(colors::HEALTH_BAR_FG);
  target.draw(foreground);
}

} // namespace cppdiep
