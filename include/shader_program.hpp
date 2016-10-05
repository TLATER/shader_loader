#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <GL/glu.h>
#include "shader.hpp"

class ShaderProgram
{
    GLuint id;

public:
    ShaderProgram (Shader** shaders, GLuint num);
    ~ShaderProgram ();
    void use ();
    GLuint getId ();
};

#endif
