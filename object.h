#ifndef CPPDIEP_OBJECT_H
#define CPPDIEP_OBJECT_H

#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>
#include <SFML/Graphics/RenderTarget.hpp>

#include "arena.fwd.h"

namespace cppdiep {

class Object {
public:
  Object(const Object &) = delete;
  b2Vec2 getPosition() const { return getB2Body().GetPosition(); }
  b2Vec2 getVelocity() const { return getB2Body().GetLinearVelocity(); }
  virtual void draw(sf::RenderTarget &target) const = 0;

protected:
  Object(Arena &arena, b2World &b2_world, const b2BodyDef &b2_body_def)
      : arena(arena), b2_body(*b2_world.CreateBody(&b2_body_def)) {}
  virtual ~Object() = default;
  virtual void step() {}
  Arena &getArena() const { return arena; }
  b2Body &getB2Body() { return b2_body; }
  const b2Body &getB2Body() const { return b2_body; }

private:
  friend Arena;
  struct Deleter {
    void operator()(Object *object) const { delete object; }
  };

  virtual bool shouldDestroy() const = 0;

  Arena &arena;
  b2Body &b2_body;
};

} // namespace cppdiep

#endif // CPPDIEP_OBJECT_H
