#include "GLSLProgram.h"
#include "Errors.h"
#include <fstream>
#include <vector>

GLSLProgram::GLSLProgram() : _num_attributes( 0 ), _program_id( 0 ), _vertex_shader_id( 0 ), _frag_shader_id( 0 )
{
}


GLSLProgram::~GLSLProgram()
{
}


void GLSLProgram::compileShaders( const std::string& vertex_shader_path, const std::string& fragment_shader_path )
{
    _program_id = glCreateProgram();

    if ( ( _vertex_shader_id = glCreateShader( GL_VERTEX_SHADER ) ) == 0 ) {
        fatalError( "Could not create vertex shader" );
    }

    if ( ( _frag_shader_id = glCreateShader( GL_FRAGMENT_SHADER ) ) == 0 ) {
        fatalError( "Could not create fragment shader" );
    }

    compileShader( vertex_shader_path, _vertex_shader_id );
    compileShader( fragment_shader_path, _frag_shader_id );


}

void GLSLProgram::compileShader( const std::string& path, GLuint id )
{
    std::ifstream shaderFile( path );
    if ( shaderFile.fail() ) {
        perror( path.c_str() );
        fatalError( "Failed to open " + path );
    }

    std::string file_contents = "";
    std::string line;

    while ( std::getline( shaderFile, line ) ) {
        file_contents += line + "\n";
    }

    shaderFile.close();

    const char* content_ptr = file_contents.c_str(); // hack
    glShaderSource( id, 1, &content_ptr, nullptr );
    glCompileShader( id );

    GLint success = 0;
    glGetShaderiv( id, GL_COMPILE_STATUS, &success );

    if ( success == GL_FALSE ) {
        GLint max_length = 0;
        glGetShaderiv( id, GL_INFO_LOG_LENGTH, &max_length );

        std::vector<char> errorLog( max_length );
        glGetShaderInfoLog( id, max_length, &max_length, &errorLog[ 0 ] );

        glDeleteShader( id );

        std::printf( "%s\n", &( errorLog[ 0 ] ) );
        fatalError( "Shader compilation error: " + path );
    }

}

void GLSLProgram::addAttribute( const std::string& name )
{
    glBindAttribLocation( _program_id, _num_attributes++, name.c_str() );
}

void GLSLProgram::linkShaders()
{
    glAttachShader( _program_id, _vertex_shader_id );
    glAttachShader( _program_id, _frag_shader_id );

    glLinkProgram( _program_id );

    GLint is_linked = 0;
    glGetProgramiv( _program_id, GL_LINK_STATUS, (int*) &is_linked );
    if ( is_linked == GL_FALSE ) {
        GLint max_length = 0;
        glGetProgramiv( _program_id, GL_INFO_LOG_LENGTH, &max_length );

        std::vector<char> error_log( max_length );
        glGetProgramInfoLog( _program_id, max_length, &max_length, &error_log[ 0 ] );

        glDeleteProgram( _program_id );
        glDeleteShader( _vertex_shader_id );
        glDeleteShader( _frag_shader_id );

        std::printf( "%s\n", &( error_log[ 0 ] ) );
        fatalError( "Shader link error" );
        return;
    }
    glDetachShader( _program_id, _vertex_shader_id );
    glDetachShader( _program_id, _frag_shader_id );

    glDeleteShader( _vertex_shader_id );
    glDeleteShader( _frag_shader_id );
}

void GLSLProgram::use()
{
    glUseProgram( _program_id );
    for ( int i = 0; i < _num_attributes; i++ ) {
        glEnableVertexAttribArray( i );
    }
}

void GLSLProgram::remove()
{
    glUseProgram( 0 );
    for ( int i = 0; i < _num_attributes; i++ ) {
        glDisableVertexAttribArray( i );
    }
}
