// Game.h
#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "World.h"

class Game {
public:
    Game(int screenWidth, int screenHeight);
    ~Game();
    bool initialize();
    void run();

private:
    void handleEvents();
    void update();
    void render();

    int screenWidth;
    int screenHeight;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    World world;
    bool quit;
};

#endif // GAME_H