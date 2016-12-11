#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <GL/glu.h>
#include <tuple>

#ifndef SHADER_HPP
#include "shader.hpp"
#endif

class ShaderProgram
{
    GLuint id;

public:
    ShaderProgram ();
    ShaderProgram (Shader** shaders, GLuint num);
    ~ShaderProgram ();

    void link ();
    void use ();
    GLuint getId ();

    static ShaderProgram*
        load_from_files (std::tuple<const GLchar*, GLenum>* shaders, GLint num);

    static ShaderProgram*
        load_from_files_with_extension (const GLchar** shaders, GLint num);
};

#endif
