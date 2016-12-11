#ifndef SHADER_ERROR_HPP
#define SHADER_ERROR_HPP

#include <string>
#include <stdexcept>

class ShaderError: public std::runtime_error
{
public:
    ShaderError(std::string message): ShaderError(message.c_str()) {};
    ShaderError(const char* message): std::runtime_error(message) {};
};

#endif
