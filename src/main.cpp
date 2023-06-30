#include "src/game/game.hpp"

#include <spdlog/spdlog.h>

#include <iostream>

int main(int argc, char **argv)
{
#if BUILD_TYPE == Debug
    spdlog::set_level(spdlog::level::debug);
#else
    spdlog::set_level(spdlog::level::info);
#endif
    Game app;

    app.Run();
    return 0;
}
