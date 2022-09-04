#include <memory>

#include <Box2D/Common/b2Math.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "arena.h"
#include "basic_tank.h"
#include "external_control_tank.h"
#include "render_utils.h"
#include "simple_ai_tank.h"

int main() {
  // Set up the window.
  sf::ContextSettings settings;
  settings.antialiasingLevel = 4;
  sf::RenderWindow window(sf::VideoMode(800, 800), "CppDiep",
                          sf::Style::Titlebar | sf::Style::Close, settings);
  constexpr auto frame_rate = 60;
  window.setFramerateLimit(frame_rate);
  constexpr auto arena_size = 20.f;
  // The Y size of the view is negative to flip things vertically since SFML
  // uses a downwards vertical axis while the arena uses an upwards vertical
  // axis.
  const sf::View view(sf::Vector2f(0.f, 0.f),
                      sf::Vector2f(arena_size, -arena_size));
  window.setView(view);

  // Create the arena and spawn two tanks for testing.
  cppdiep::Arena arena(arena_size, 1.f / frame_rate);
  const auto player_tank =
      arena.spawn<cppdiep::ExternalControlTank<cppdiep::BasicTank>>(
          b2Vec2(7.5f, 7.5f), 1.f, cppdiep::colors::BLUE);
  const auto enemy_tank =
      arena.spawn<cppdiep::SimpleAITank<cppdiep::BasicTank>>(
          b2Vec2(-7.5f, -7.5f), 1.f, cppdiep::colors::RED);
  if (auto locked_enemy_tank = enemy_tank.lock()) {
    locked_enemy_tank->setTargetObject(player_tank);
  }

  auto auto_firing = false;

  while (window.isOpen()) {
    const auto locked_player_tank = player_tank.lock();

    // Make the tank cannon point towards the mouse.
    if (locked_player_tank) {
      const b2Vec2 mouse_position = cppdiep::toB2Vec2(
          window.mapPixelToCoords(sf::Mouse::getPosition(window)));
      locked_player_tank->setTarget(mouse_position -
                                    locked_player_tank->getPosition());
    }

    // Process events.
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
      case sf::Event::Closed:
        window.close();
        break;
      case sf::Event::MouseButtonPressed:
        if (event.mouseButton.button == sf::Mouse::Left && locked_player_tank) {
          locked_player_tank->fire();
        }
        break;
      case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::E) {
          auto_firing = !auto_firing;
        }
        break;
      default:;
      }
    }

    if (locked_player_tank) {
      if (auto_firing) {
        locked_player_tank->fire();
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        locked_player_tank->move(b2Vec2(0.f, 1.f));
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        locked_player_tank->move(b2Vec2(-1.f, 0.f));
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        locked_player_tank->move(b2Vec2(0.f, -1.f));
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        locked_player_tank->move(b2Vec2(1.f, 0.f));
      }
    }

    arena.step();
    arena.draw(window);
    window.display();
  }
}
