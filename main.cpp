// main.cpp
#include "Game.h"
#include <iostream>

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 540;

int main(int argc, char* args[]) {
    Game game(SCREEN_WIDTH, SCREEN_HEIGHT);
    std::cout << "Here!\n";
    if (!game.initialize()){
    }
    game.run();
    return 0;
}