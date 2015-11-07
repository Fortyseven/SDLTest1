#pragma once
#include <SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <string>
#include "Sprite.h"
#include "GLSLProgram.h"

enum class GameState { PLAY, EXIT };

class MainGame
{
public:
    MainGame();
    ~MainGame();

    void run();

private:
    void initSystems();
    void initShaders();
    void gameLoop();
    void processInput();
    void drawGame();

    SDL_Window* _window;
    int _screen_width;
    int _screen_height;
    GameState _currentGameState;

    Sprite _sprite;

    GLSLProgram _color_program;
};

