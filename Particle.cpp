#include "Particle.h"
#include "World.h"
#include <random>
#include <iostream>

Particle::Particle(int x, int y, ParticleType type, World* world) : x(x), y(y), type(type), world(world) {}

void Particle::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

Sand::Sand(int x, int y, World* world) : Particle(x, y, ParticleType::SAND, world) {}

void Sand::update() {
    if (y < world->getHeight()-1){
        if (world->getPixel(x,y+1)!=0){
            if (world->getPixel(x+1,y+1)!=0){
                if (world->getPixel(x-1,y+1)!=0){
                    //4294956800 sand
                    //4278190335 water
                } else if (x > 1){
                    x--;
                    y++;
                }
            } else if (x < world->getWidth()-1){
                x++;
                y++;
            }
        } else {
            y++; // Simple gravity
        }
    }
}

Uint32 Sand::getColor() const {
    return 0xFFFFD700; // Gold color
}

Water::Water(int x, int y, World* world) : Particle(x, y, ParticleType::WATER, world) {}

void Water::update() {
    //static std::random_device rd;
    //static std::mt19937 gen(rd());
    //static std::uniform_int_distribution<> dis(-1, 1);

    //y++; // Gravity
    //x += dis(gen); // Random horizontal movement
    if (y < world->getHeight()-5){
        if (world->getPixel(x,y+1)!=0){
            if (world->getPixel(x+1,y+1)!=0){
                if (world->getPixel(x-1,y+1)!=0){
                    //4294956800 sand
                    //4278190335 water
                } else {
                    x--;
                    y++;
                }
            } else {
                x++;
                y++;
            }
        } else {
            y++; // Simple gravity
        }
    }
}

Uint32 Water::getColor() const {
    return 0xFF0000FF; // Blue color
}