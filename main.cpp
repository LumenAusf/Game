#include <cstdlib>
#include <iostream>
#include <SDL2/SDL_version.h>

std::ostream& operator<<(std::ostream& out, const SDL_version& v) {
  out << static_cast<int>(v.major) << '.';
  out << static_cast<int>(v.minor) << '.';
  out << static_cast<int>(v.patch);
  return out;
}

int main()
{
    SDL_version compiled = {0, 0, 0};
    SDL_version linked = {0, 0, 0};

    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);

    std::cout << "compiled: " << compiled << '\n';
    std::cout << "linked: " << linked << std::endl;
    std::clog << "I`m okay lumenausf" << std::endl;
    return 0;
}
