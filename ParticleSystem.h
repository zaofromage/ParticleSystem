#include <ctime>
#include <vector>
#include "Timer.h"

class ParticleSystem {
private:
   Particle particleTemplate;
   int spawnSpeed;
   int nb;
   std::vector<Particle> ps;
   Timer timer;
   std::thread* gen;
public:
   ParticleSystem(int nb, int spawnSpeed, Particle& p)
      : nb(nb),
        spawnSpeed(spawnSpeed),
        particleTemplate(p) {
      srand(time(NULL));
      gen = timer.interval([&]() {
         ps.push_back(Particle(particleTemplate));
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
            if (p.isCircle())
               p.reset(particleTemplate.getRadius(), d, x, y);
            else if (p.isRect())
               p.reset(particleTemplate.getSide(), d, x, y);
         }
         p.update(window);
      }
   }
};

