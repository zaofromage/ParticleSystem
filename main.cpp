#include <iostream>
#include <SFML/Graphics.hpp>

#include "Particle.h"
#include "ParticleSystem.h"

int main() {
   sf::RenderWindow window(sf::VideoMode(1080, 720), "particle system");
   window.setFramerateLimit(60);
   int mouseX = 100;
   int mouseY = 100;
   Particle p(20, 0.5, sf::Color::Red);
   ParticleSystem ps(30, 20, p);

   while(window.isOpen()) {
      sf::Event event;
      while(window.pollEvent(event)) {
         if (event.type == sf::Event::Closed) {
            window.close();
         }
         if (event.type == sf::Event::MouseMoved) {
            mouseX = event.mouseMove.x;
            mouseY = event.mouseMove.y;
         }
      }
      window.clear();
      ps.update(window, mouseX, mouseY);
      window.display();
   }
}
