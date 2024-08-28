#ifndef WORLD_H
#define WORLD_H

#include "Particle.h"
#include <iostream>
#include <vector>

class World{
    public:
        World();
        void addParticle(Particle* particle, int x, int y);
        void update();
        void draw();

        ~World();
    private:
        std::vector<std::vector<int>> grid;
    
};

#endif // WORLD_H