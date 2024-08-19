#include "Vector.h"

class Particle {
private:
   sf::CircleShape shape;
   int x, y;
   float speed;
   float radius;
   Vector dir;
   float offsetX, offsetY;
public:
   Particle(float radius, Vector dir, float speed)
      : shape(radius),
      radius(radius),
      dir(dir),
      offsetX(0),
      offsetY(0),
      speed(speed) {
      shape.setFillColor(sf::Color::White);
   }

   void update(sf::RenderWindow& window) {
      disapear();
      move();
      shape.setPosition(x + offsetX, y + offsetY);
      shape.setRadius(radius);
      window.draw(shape);
   }

   void disapear() {
      radius -= 0.2f;
      if (radius <= 0.1f) {
         radius = 0;
      }
   }

   bool isDead() {
      return radius <= 0;
   }

   void move() {
      Vector v = dir * speed;
      offsetX += dir.x;
      offsetY += dir.y;
   }

   void reset(float r, Vector newDir, int x, int y) {
      this->x = x;
      this->y = y;
      radius = r;
      dir = newDir;
      offsetX = 0;
      offsetY = 0;
      shape.setRadius(r);
   }

   float getRadius() {
      return radius;
   }
};
