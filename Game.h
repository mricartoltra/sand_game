#ifndef GAME_H
#define GAME_H

#include "Particle.h"
#include "World.h"
#include <iostream>
#include <vector>

class Game{
    public:
        void run();
    private:
        World world;
    
};

#endif // GAME_H