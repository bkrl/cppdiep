#ifndef CPPDIEP_RENDER_UTILS_H
#define CPPDIEP_RENDER_UTILS_H

/// @file
/// Constants and helper functions used for rendering.

#include <numbers>

#include <Box2D/Common/b2Math.h>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

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

} // namespace colors

/// The thickness of the outlines around the objects. This is negative to make
/// the outline inside the edge of the object.
inline constexpr float OUTLINE_THICKNESS = -0.125f;

/// Darken a color to get the color of the outline.
/// @param color the color to darken.
/// @return The darkened color.
inline sf::Color darken(const sf::Color &color) {
  return sf::Color(color.r * 0.75, color.g * 0.75, color.b * 0.75, color.a);
}

/// Draw a circle.
/// @param target the SFML render target to draw to.
/// @param position the position of the center of the circle.
/// @param radius the radius of the circle.
/// @param color the color of the circle.
void drawCircle(sf::RenderTarget &target, const b2Vec2 &position, float radius,
                const sf::Color &color);

/// Convert radians to degrees.
/// @param radians an angle in radians.
/// @return The angle in degrees.
inline float radiansToDegrees(float radians) {
  return radians * 180.f / std::numbers::pi_v<float>;
}

/// Convert a Box2D vector to an SFML vector.
/// @param b2_vec a Box2D vector.
/// @return The SFML vector.
inline sf::Vector2f convertVector(const b2Vec2 &b2_vec) {
  return sf::Vector2f(b2_vec.x, b2_vec.y);
}

/// Convert an SFML vector to a Box2D vector.
/// @param sf_vec an SFML vector.
/// @return The Box2D vector.
inline b2Vec2 convertVector(const sf::Vector2f &sf_vec) {
  return b2Vec2(sf_vec.x, sf_vec.y);
}

} // namespace cppdiep

#endif // CPPDIEP_RENDER_UTILS_H
