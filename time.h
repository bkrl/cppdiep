#ifndef CPPDIEP_TIME_H
#define CPPDIEP_TIME_H

/// @file
/// Definition of the Time type alias.

#include <cstdint>

namespace cppdiep {

/// The signed integer type that will be used to represent time in the arena as
/// a number of steps.
using Time = std::int64_t;

} // namespace cppdiep

#endif // CPPDIEP_TIME_H
