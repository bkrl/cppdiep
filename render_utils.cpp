#include "render_utils.h"

#include <Box2D/Common/b2Math.h>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace dieprl {

void drawCircle(sf::RenderTarget &target, const b2Vec2 &position, float radius,
                const sf::Color &color) {
  sf::CircleShape shape(radius);
  shape.setOrigin(radius, radius);
  shape.setPosition(position.x, position.y);
  shape.setFillColor(color);
  shape.setOutlineThickness(OUTLINE_THICKNESS);
  shape.setOutlineColor(darken(color));
  target.draw(shape);
}

} // namespace dieprl
