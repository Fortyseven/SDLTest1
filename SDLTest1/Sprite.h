#pragma once

#include <GL/glew.h>
#include "GLSLProgram.h"

class Sprite
{
public:
    Sprite();
    ~Sprite();

    void init( float x, float y, float width, float height );
    void draw();

private:
    float _x, _y;
    float _width, _height;

    GLuint _vbo_id;
};

