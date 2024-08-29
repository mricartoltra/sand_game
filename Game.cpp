#include "Game.h"
#include "Particle.h"
#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <cmath>
#include <random>

Game::Game(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight), 
      window(nullptr), renderer(nullptr), texture(nullptr),
      world(screenWidth, screenHeight), quit(false) {}

Game::~Game() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Game::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    window = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                              screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 
                                screenWidth, screenHeight);
    
    return true;
}

void Game::run() {
    while (!quit) {
        handleEvents();
        update();
        render();
        //std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

struct Point {
    int x;
    int y;
};

std::vector<Point> generateFilledCirclePoints(int radius, int numPoints) {
    std::vector<Point> points;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-radius, radius);

    while (points.size() < numPoints) {
        int x = dis(gen);
        int y = dis(gen);
        if (x*x + y*y <= radius*radius) {
            points.push_back({x, y});
        }
    }

    return points;
}



void Game::handleEvents() {
    SDL_Event e;
    int mouseX, mouseY;
    uint32_t mouseState = SDL_GetMouseState(&mouseX, &mouseY);

    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
    }

    // Check if left mouse button is held down
    if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        static std::vector<Point> filledCirclePoints = generateFilledCirclePoints(20, 1000);
        
        // Add particles at the current mouse position
        for (const auto& point : filledCirclePoints) {
            int particleX = mouseX + point.x;
            int particleY = mouseY + point.y;
            world.addParticle(std::make_unique<Sand>(particleX, particleY, &world));
        }
    }
    if (mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
        static std::vector<Point> filledCirclePoints = generateFilledCirclePoints(20, 1000);
        
        // Add particles at the current mouse position
        for (const auto& point : filledCirclePoints) {
            int particleX = mouseX + point.x;
            int particleY = mouseY + point.y;
            world.addParticle(std::make_unique<Water>(particleX, particleY, &world));
        }
    }
}

void Game::update() {
    world.update();
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    const auto& pixels = world.getPixels();
    
    // Create a flat vector to hold the pixel data
    std::vector<Uint32> flatPixels;
    flatPixels.reserve(screenWidth * screenHeight);

    // Flatten the 2D vector into a 1D vector
    for (const auto& row : pixels) {
        flatPixels.insert(flatPixels.end(), row.begin(), row.end());
    }

    // Update the texture with the flattened pixel data
    SDL_UpdateTexture(texture, nullptr, flatPixels.data(), screenWidth * sizeof(Uint32));
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}