#include <fstream>
#include <string.h>

#include <GL/glew.h>

#include "shader_error.hpp"
#include "shader.hpp"

using namespace std;

Shader::Shader (const GLchar* src, GLsizei length, GLenum type)
{
    id = glCreateShader(type);
    glShaderSource(id, 1, &src, &length);
}

Shader::~Shader ()
{
    glDeleteShader(id);
}

void Shader::compile ()
{
    glCompileShader(id);

    GLint log_length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_length);

    if (log_length > 1) {
        char* error_log = new char[log_length];
        glGetShaderInfoLog(id, log_length, NULL, error_log);
        throw ShaderError(error_log);
    }
}

GLuint Shader::getId ()
{
    return id;
}

Shader* Shader::load_from_file (const GLchar* file_name, GLenum type)
{
    ifstream file;
    char* src;
    GLsizei length;

    file.open(file_name);

    // Find the length
    file.seekg(0, ios::end);
    length = file.tellg();

    // Read the file
    src = new char[length];
    file.seekg(0, ios::beg);
    file.read(src, length);
    file.close();

    return new Shader(src, length, type);
}

Shader* Shader::load_from_file_with_extension (const GLchar* file_name)
{
    const GLchar* extension = &(file_name[strlen(file_name) - 5]);
    GLenum type;

    if (strcmp(extension, ".vert"))
        type = GL_VERTEX_SHADER;
    else if (strcmp(extension, ".tesc"))
        type = GL_TESS_CONTROL_SHADER;
    else if (strcmp(extension, ".tese"))
        type = GL_TESS_EVALUATION_SHADER;
    else if (strcmp(extension, ".geom"))
        type = GL_GEOMETRY_SHADER;
    else if (strcmp(extension, ".frag"))
        type = GL_FRAGMENT_SHADER;
    else if (strcmp(extension, ".comp"))
        type = GL_COMPUTE_SHADER;

    return load_from_file(file_name, type);
}
