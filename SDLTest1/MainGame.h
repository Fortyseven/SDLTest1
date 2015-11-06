#pragma once
#include <SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <string>

enum class GameState { PLAY, EXIT };

void fatalError( std::string error_string );

class MainGame
{
public:
    MainGame();
    ~MainGame();

    void run();

private:
    void initSystems();
    void gameLoop();
    void processInput();
    void drawGame();

    SDL_Window* _window;
    int _screen_width;
    int _screen_height;
    GameState _currentGameState;
};

