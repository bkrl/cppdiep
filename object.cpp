#include "object.h"

#include "arena.h"

namespace cppdiep {

Object::Object(Arena &arena, const b2BodyDef &b2_body_def)
    : arena(arena), b2_body(*arena.getB2World().CreateBody(&b2_body_def)) {}

Object::~Object() { arena.getB2World().DestroyBody(&b2_body); }

} // namespace cppdiep
