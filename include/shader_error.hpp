#include <stdexcept>

class ShaderError: public std::runtime_error
{
public:
    ShaderError(const char* message): std::runtime_error(message) {};
};
