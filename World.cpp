#include "World.h"
#include <vector>
#include <iostream>

World::World(int width, int height) : width(width), height(height) {
    pixels = std::vector<std::vector<Uint32>>(height, std::vector<Uint32>(width, 0));
}

int World::getWidth() {
    return width;
}

int World::getHeight() {
    return height;
}

Uint32 World::getPixel(int x, int y) {
    return pixels[y][x];
}

void World::addParticle(std::unique_ptr<Particle> particle) {
    particles.push_back(std::move(particle));
}

void World::update() {
    // Clear pixels
    for (auto& row : pixels) {
        std::fill(row.begin(), row.end(), 0);
    }

    // Update and draw particles
    for (const auto& particlePtr : particles) {
        particlePtr->update();
        int x = particlePtr->getX();
        int y = particlePtr->getY();
        if (x >= 0 && x < width && y >= 0 && y < height) {
            pixels[y][x] = particlePtr->getColor();
        }
    }
}

const std::vector<std::vector<Uint32>>& World::getPixels() const {
    std::vector<std::vector<Uint32>> prixels(height, std::vector<Uint32>(width, 0));
    return pixels;
}