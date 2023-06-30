#ifndef GAME_H
#define GAME_H

#include <vector>
#include <sstream>
#include <memory>

#include <src/simulator/simulator.hpp>
#include <src/renderer/renderer.hpp>
#include <src/vehicle/vehicle.hpp>
#include <src/controllers/ievent-handler.hpp>
#include <src/controllers/pc-controller.hpp>
#include <src/renderer/soundplayer.hpp>
#include <src/asteroids/generator.hpp>
#include <src/renderer/screens/screen-manager.hpp>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Game
{
private:
    std::shared_ptr<GameState> gs_{nullptr};
    std::shared_ptr<Renderer> renderer_{nullptr};
    std::shared_ptr<SoundPlayer> sp_{nullptr};
    std::shared_ptr<renderer::screen::ScreenManager> scr_manager_{nullptr};
    sf::RenderWindow window_;

    void Init();

public:
    explicit Game();
    void Run();

    static json config;
};

#endif
