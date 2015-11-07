#pragma once
#include <GL/glew.h>

struct Vertex
{
    struct Position
    {
        float x, y;
    } position;

    struct Color
    {
        GLubyte r, g, b, a;
    } color;
};