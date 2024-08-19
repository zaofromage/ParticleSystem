#include <ctime>
#include <vector>
#include "Timer.h"

class ParticleSystem {
private:
   float size;
   int spawnSpeed;
   float speed;
   int nb;
   std::vector<Particle> ps;
   Timer timer;
   std::thread* gen;
public:
   ParticleSystem(int nb, float size, int spawnSpeed, float speed)
   : size(size),
   nb(nb),
   spawnSpeed(spawnSpeed),
   speed(speed) {
      srand(time(NULL));
      gen = timer.interval([&]() {
         //Vector d((float) ((rand()%200) - 100)/100.0f, (float) ((rand()%200) - 100) /100.0f);
         Vector d(-1, -1);
         ps.push_back(Particle(0, d, speed));
      }, spawnSpeed);
      timer.delay([&]() {
         timer.stop(gen);
      }, spawnSpeed * nb);
   }

   ~ParticleSystem() {
   }

   void update(sf::RenderWindow& window, int x, int y) {
      for (Particle& p : ps) {
         if (p.isDead()) {
            Vector d((float) (rand()%200 - 100)/100.0f, (float) (rand()%200 - 100)/100.0f);
            p.reset(size, d, x, y);
         }
         p.update(window);
      }
   }
};
