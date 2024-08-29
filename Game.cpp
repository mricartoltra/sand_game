#include "Game.h"
#include "Particle.h"
#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

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
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

void Game::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            if (e.button.button == SDL_BUTTON_LEFT) {
                world.addParticle(std::make_unique<Sand>(mouseX, mouseY, &world));
            } else if (e.button.button == SDL_BUTTON_RIGHT) {
                world.addParticle(std::make_unique<Water>(mouseX, mouseY, &world));
            }
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