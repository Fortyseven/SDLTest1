#include "Sprite.h"



Sprite::Sprite()
{
    _vbo_id = 0;
}


Sprite::~Sprite()
{
    if ( _vbo_id != 0 ) {
        glDeleteBuffers( 1, &_vbo_id );
    }
}


void Sprite::init( float x, float y, float width, float height )
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;

    if ( _vbo_id == 0 ) {
        glGenBuffers( 1, &_vbo_id );
    }

    float vertexData[ 6 * 2 ];

    vertexData[ 0 ] = x + width;
    vertexData[ 1 ] = y + height;

    vertexData[ 2 ] = x;
    vertexData[ 3 ] = y + height;

    vertexData[ 4 ] = x;
    vertexData[ 5 ] = y;

    // Second Triangle
    vertexData[ 6 ] = x;
    vertexData[ 7 ] = y;

    vertexData[ 8 ] = x + width;
    vertexData[ 9 ] = y;

    vertexData[ 10 ] = x + width;
    vertexData[ 11 ] = y + height;

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_id );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertexData ), vertexData, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}


void Sprite::draw()
{
    glBindBuffer( GL_ARRAY_BUFFER, _vbo_id );

    glEnableVertexAttribArray( 0 );

    glVertexAttribPointer( 0, 2, GL_FLOAT, false, 0, 0 );

    glDrawArrays( GL_TRIANGLES, 0, 6 );

    glDisableVertexAttribArray( 0 );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}
