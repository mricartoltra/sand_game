#ifndef PARTICLE_H
#define PARTICLE_H

#include <SDL2/SDL.h>
#include "World.h"

class World;

enum class ParticleType {
    SAND,
    WATER
};

class Particle {
public:
    Particle(int x, int y, ParticleType type, World* world);
    virtual ~Particle() = default;

    virtual void update() = 0;
    virtual Uint32 getColor() const = 0;

    int getX() const { return x; }
    int getY() const { return y; }
    void setPosition(int newX, int newY);
    ParticleType getType() const { return type; }

protected:
    int x, y;
    ParticleType type;
    World* world;
};

class Sand : public Particle {
public:
    Sand(int x, int y, World* world);
    void update() override;
    Uint32 getColor() const override;
};

class Water : public Particle {
public:
    Water(int x, int y, World* world);
    void update() override;
    Uint32 getColor() const override;
};

#endif // PARTICLE_H