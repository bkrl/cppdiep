#ifndef CPPDIEP_RENDER_UTILS_H
#define CPPDIEP_RENDER_UTILS_H

/// @file
/// Constants and helper functions used for rendering.

#include <numbers>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <box2d/b2_math.h>

namespace cppdiep {

/// Colors used for rendering.
namespace colors {

/// Color for blue tanks and bullets.
inline const sf::Color BLUE(0, 178, 225);

/// Color for red tanks and bullets.
inline const sf::Color RED(241, 78, 84);

/// Color for tank cannons.
inline const sf::Color CANNON(153, 153, 153);

/// Background color of the arena.
inline const sf::Color BACKGROUND(205, 205, 205);

/// Background color of health bars.
inline const sf::Color HEALTH_BAR_BG(85, 85, 85);

/// Foreground color of the health bars.
inline const sf::Color HEALTH_BAR_FG(133, 227, 125);

} // namespace colors

/// The thickness of the outlines around the objects.
inline constexpr float OUTLINE_THICKNESS = 0.125f;

/// Darken a color to get the color of the outline.
/// @param color the color to darken.
/// @return The darkened color.
inline sf::Color darken(const sf::Color &color) noexcept {
  return sf::Color(color.r * 0.75, color.g * 0.75, color.b * 0.75, color.a);
}

/// Draw a circle.
/// @param target the SFML render target to draw to.
/// @param position the position of the center of the circle.
/// @param radius the radius of the circle.
/// @param color the color of the circle.
inline void drawCircle(sf::RenderTarget &target, const b2Vec2 &position,
                       const float radius, const sf::Color &color) {
  sf::CircleShape shape(radius);
  shape.setOrigin(radius, radius);
  shape.setPosition(position.x, position.y);
  shape.setFillColor(color);
  shape.setOutlineThickness(-OUTLINE_THICKNESS);
  shape.setOutlineColor(darken(color));
  target.draw(shape);
}

/// Convert radians to degrees.
/// @param radians an angle in radians.
/// @return The angle in degrees.
inline float radiansToDegrees(const float radians) noexcept {
  return radians * 180.f / std::numbers::pi_v<float>;
}

/// Convert a Box2D vector to an SFML vector.
/// @param b2_vec a Box2D vector.
/// @return The SFML vector.
inline sf::Vector2f toSfVector2f(const b2Vec2 &b2_vec) noexcept {
  return sf::Vector2f(b2_vec.x, b2_vec.y);
}

/// Convert an SFML vector to a Box2D vector.
/// @param sf_vec an SFML vector.
/// @return The Box2D vector.
inline b2Vec2 toB2Vec2(const sf::Vector2f &sf_vec) noexcept {
  return b2Vec2(sf_vec.x, sf_vec.y);
}

} // namespace cppdiep

#endif // CPPDIEP_RENDER_UTILS_H
