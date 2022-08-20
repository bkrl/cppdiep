#ifndef DIEPRL_B2_CATEGORIES_H
#define DIEPRL_B2_CATEGORIES_H

#include <Box2D/Common/b2Settings.h>

namespace dieprl {

namespace b2_categories {
inline constexpr uint16 BORDER = 1u << 0;
inline constexpr uint16 TANK = 1u << 1;
inline constexpr uint16 BULLET = 1u << 2;
} // namespace b2_categories

} // namespace dieprl

#endif // DIEPRL_B2_CATEGORIES_H
