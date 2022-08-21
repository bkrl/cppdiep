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

int main() {
  sf::ContextSettings settings;
  settings.antialiasingLevel = 4;
  sf::RenderWindow window(sf::VideoMode(800, 800), "DiepRL",
                          sf::Style::Titlebar | sf::Style::Close, settings);
  constexpr int frame_rate = 60;
  window.setFramerateLimit(frame_rate);
  constexpr float arena_size = 20.f;
  sf::View view(sf::Vector2f(0.f, 0.f), sf::Vector2f(arena_size, -arena_size));
  window.setView(view);

  dieprl::Arena arena(arena_size, 1.f / frame_rate);
  auto &tank = arena.spawnTank<dieprl::ExternalControlTank<dieprl::BasicTank>>(
      b2Vec2(0.f, 0.f), 1.f, dieprl::colors::BLUE);
  arena.spawnTank<dieprl::ExternalControlTank<dieprl::BasicTank>>(
      b2Vec2(0.f, 5.f), 1.f, dieprl::colors::RED);

  while (window.isOpen()) {
    b2Vec2 mouse_position = dieprl::convertVector(
        window.mapPixelToCoords(sf::Mouse::getPosition(window)));
    tank.setTarget(mouse_position - tank.getPosition());
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::MouseButtonPressed &&
                 event.mouseButton.button == sf::Mouse::Left) {
        tank.fire();
      }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      tank.move(b2Vec2(0.f, 1.f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      tank.move(b2Vec2(-1.f, 0.f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
      tank.move(b2Vec2(0.f, -1.f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      tank.move(b2Vec2(1.f, 0.f));
    }
    arena.step();
    arena.draw(window);
    window.display();
  }
}
