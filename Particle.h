#include <SFML/Graphics.hpp>
#include "Vector.h"

class Particle {
private:
   sf::Shape* shape;
   int x, y;
   float radius;
   float side;
   float spawnSize;
   Vector dir;
   float offsetX, offsetY;
   float lifetime;

public:
   Particle(float radius, float lifetime, sf::Color color)
      : shape(new sf::CircleShape(radius)), 
       radius(radius),
       spawnSize(radius),
       dir(0, 0),
       offsetX(0),
       offsetY(0),
       side(-1),
       x(0),
       y(0),
       lifetime(lifetime) {
      shape->setFillColor(color);
   }

   Particle(float side, float lifetime, sf::Color color, bool rect)
      : shape(new sf::RectangleShape(sf::Vector2f(side, side))),
       radius(-1),
       spawnSize(side),
       dir(0, 0),
       offsetX(0),
       offsetY(0),
       side(side),
       x(0),
       y(0),
       lifetime(lifetime) {
      shape->setFillColor(color);
   }

   Particle(const Particle& other)
      : x(other.x),
      y(other.y),
      radius(other.radius),
      dir(other.dir),
      offsetX(other.offsetX),
      offsetY(other.offsetY),
      side(other.side),
      spawnSize(other.spawnSize),
      lifetime(other.lifetime) {

      if (auto circle = dynamic_cast<sf::CircleShape*>(other.shape)) {
        shape = new sf::CircleShape(*circle);
      } else if (auto rect = dynamic_cast<sf::RectangleShape*>(other.shape)) {
        shape = new sf::RectangleShape(*rect);
      } else {
        shape = nullptr;
      }
   }

   ~Particle() {
      delete shape;
   }

   void update(sf::RenderWindow& window) {
      disapear();
      move();
      shape->setPosition(x + offsetX, y + offsetY);
      window.draw(*shape);
   }

   void disapear() {
      if (isCircle()) {
         radius -= spawnSize/(60 * lifetime); // ne fonctionne qu'a 60 fps
         if (radius <= 0.1f) {
             radius = 0;
         }
         dynamic_cast<sf::CircleShape*>(shape)->setRadius(radius);
      } else if (isRect()) {
         side -= spawnSize/(60 * lifetime);
         if (side <= 0.1f) {
            side = 0;
         }
         dynamic_cast<sf::RectangleShape*>(shape)->setSize(sf::Vector2f(side, side));
      }
   }

   bool isDead() {
      if (isCircle()) {
         return radius <= 0;
      } else if (isRect()) {
         return shape->getGlobalBounds().width <= 0 || shape->getGlobalBounds().height <= 0;
      }
      return false;
   }

   void move() {
     offsetX += dir.x;
     offsetY += dir.y;
   }

   void reset(float r, Vector newDir, int x, int y) {
      this->x = x;
      this->y = y;
      dir = newDir;
      offsetX = 0;
      offsetY = 0;
      if (isCircle()) {
         radius = r;
         dynamic_cast<sf::CircleShape*>(shape)->setRadius(r);
      } else if (isRect()) {
         side = r;
         dynamic_cast<sf::RectangleShape*>(shape)->setSize(sf::Vector2f(r, r));
      }
   }

   float getRadius() const {
     return radius;
   }

   float getSide() {
      return side;
   }

   bool isCircle() {
      return radius >= 0;
   }

   bool isRect() {
      return side >= 0;
   }
};

