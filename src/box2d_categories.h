// SPDX-FileCopyrightText: 2022 Alexander Zhang <alex@alexyzhang.dev>
//
// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef CPPDIEP_B2_CATEGORIES_H
#define CPPDIEP_B2_CATEGORIES_H

/// @file
/// Box2D collision category constants.

#include <box2d/b2_types.h>

namespace cppdiep {

/// Box2D collision category bitmasks.
namespace box2d_categories {

/// Box2D collision category bitmask for the arena border.
inline constexpr uint16 BORDER = 1u << 0;

/// Box2D collision category bitmask for tanks.
inline constexpr uint16 TANK = 1u << 1;

/// Box2D collision category bitmask for bullets.
inline constexpr uint16 BULLET = 1u << 2;

} // namespace box2d_categories

} // namespace cppdiep

#endif // CPPDIEP_B2_CATEGORIES_H
