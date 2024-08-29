#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include "Particle.h"

class Particle;

class World {
public:
    World(int width, int height);
    void addParticle(std::unique_ptr<Particle> particle);
    void update();
    const std::vector<std::vector<Uint32>>& getPixels() const;
    int getWidth();
    int getHeight();
    Uint32 getPixel(int x, int y);

private:
    int width;
    int height;
    std::vector<std::unique_ptr<Particle>> particles;
    std::vector<std::vector<Uint32>> pixels;  // For rendering
};

#endif // WORLD_H