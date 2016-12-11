#include <stdexcept>
#include <tuple>

#include <GL/glew.h>

#include "shader.hpp"
#include "shader_error.hpp"
#include "shader_program.hpp"

using namespace std;

ShaderProgram::ShaderProgram (Shader** shaders, GLuint num)
{
    id = glCreateProgram();

    for (GLuint i = 0; i < num; i++)
        glAttachShader(id, shaders[i]->getId());
}

ShaderProgram::~ShaderProgram ()
{
    glDeleteProgram(id);
}

void ShaderProgram::link ()
{
    glLinkProgram(id);

    GLint log_length;
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &log_length);

    if (log_length > 1) {
        char* error_log = new char[log_length];
        glGetProgramInfoLog(id, log_length, NULL, error_log);
        throw ShaderError(error_log);
    }
}

void ShaderProgram::use ()
{
    glUseProgram(id);
}

GLuint ShaderProgram::getId ()
{
    return id;
}

ShaderProgram* ShaderProgram::
    load_from_files (std::tuple<const GLchar*, GLenum>* shaders, GLint num)
{
    Shader** compiled = new Shader*[num];

    for (int i = 0; i < num; i++) {
        compiled[i] = Shader::load_from_file(std::get<0>(shaders[i]),
                                             std::get<1>(shaders[i]));
        compiled[i]->compile();
    }

    ShaderProgram* program = new ShaderProgram(compiled, num);
    delete compiled;

    return program;
}

ShaderProgram* ShaderProgram::
    load_from_files_with_extension (const GLchar** shaders, GLint num)
{
    Shader** compiled = new Shader*[num];

    for (int i = 0; i < num; i++) {
        compiled[i] = Shader::load_from_file_with_extension(shaders[i]);
        compiled[i]->compile();
    }

    ShaderProgram* program = new ShaderProgram(compiled, num);
    delete compiled;

    return program;
}
