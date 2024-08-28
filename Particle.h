#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include "World.h"

class Particle{
    public:
        virtual void update(World& world) = 0;
        virtual void draw() = 0;
        //add common properties like position

    private:
        //Grid representation
    
};

#endif // PARTICLE_H