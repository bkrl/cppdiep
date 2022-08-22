#ifndef CPPDIEP_RENDER_UTILS_H
#define CPPDIEP_RENDER_UTILS_H

#include <numbers>

#include <Box2D/Common/b2Math.h>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

namespace cppdiep {

namespace colors {
inline const sf::Color BLUE(0, 178, 225);
inline const sf::Color RED(241, 78, 84);
inline const sf::Color CANNON(153, 153, 153);
inline const sf::Color BACKGROUND(205, 205, 205);
} // namespace colors

inline constexpr float OUTLINE_THICKNESS = -0.125f;

inline sf::Color darken(const sf::Color &color) {
  return sf::Color(color.r * 0.75, color.g * 0.75, color.b * 0.75, color.a);
}

void drawCircle(sf::RenderTarget &target, const b2Vec2 &position, float radius,
                const sf::Color &color);

inline float radiansToDegrees(float radians) {
  return radians * 180.f / std::numbers::pi_v<float>;
}

inline sf::Vector2f convertVector(const b2Vec2 &b2_vec) {
  return sf::Vector2f(b2_vec.x, b2_vec.y);
}

inline b2Vec2 convertVector(const sf::Vector2f &sf_vec) {
  return b2Vec2(sf_vec.x, sf_vec.y);
}

} // namespace cppdiep

#endif // CPPDIEP_RENDER_UTILS_H
