#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glu.h>

class Shader
{
    GLuint id;

public:
    Shader ();
    Shader (const GLchar* src, GLsizei length, GLenum type);
    ~Shader ();

    void compile (void);
    GLuint getId ();

    static Shader* load_from_file (const GLchar* file_name, GLenum type);
    static Shader* load_from_file_with_extension (const GLchar* file_name);
};

#endif
