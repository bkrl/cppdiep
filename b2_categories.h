#ifndef CPPDIEP_B2_CATEGORIES_H
#define CPPDIEP_B2_CATEGORIES_H

#include <Box2D/Common/b2Settings.h>

namespace cppdiep {

namespace b2_categories {
inline constexpr uint16 BORDER = 1u << 0;
inline constexpr uint16 TANK = 1u << 1;
inline constexpr uint16 BULLET = 1u << 2;
} // namespace b2_categories

} // namespace cppdiep

#endif // CPPDIEP_B2_CATEGORIES_H
