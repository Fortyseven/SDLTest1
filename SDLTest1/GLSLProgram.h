#pragma once

#include <GL/glew.h>
#include <string>

class GLSLProgram
{
public:
    GLSLProgram();
    ~GLSLProgram();

    void compileShaders( const std::string& vertex_shader_path, const std::string& fragment_shader_path );
    void linkShaders();
    void addAttribute( const std::string& name );
    void use();
    void remove();

private:
    GLuint _program_id;
    GLuint _vertex_shader_id;
    GLuint _frag_shader_id;
    int _num_attributes;

    void compileShader( const std::string& path, GLuint id );

};

