#include <stdexcept>

class SDL_exception : public std::runtime_error {
public:
	SDL_exception(const std::string& err) : runtime_error(err.c_str()) {}
};