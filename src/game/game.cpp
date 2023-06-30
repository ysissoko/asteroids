#include "src/game/game.hpp"
#include "src/controllers/pc-controller.hpp"
#include "src/ui/hud.hpp"
#include "src/renderer/screens/game-screen.hpp"
#include "src/renderer/screens/game-over-screen.hpp"
#include "config.h"

#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <fstream>

json Game::config = {};

Game::Game()
{
    Init();
}

void Game::Init()
{
    std::ifstream json_file("config.json", std::ifstream::in);
    if (!json_file.is_open())
        throw std::runtime_error("config file not found");
    else
        spdlog::debug("Config file is opened!");

    config = json::parse(json_file);
    json_file.close();

    // create the window
    window_.create(sf::VideoMode(config["window"]["width"].get<unsigned int>(), config["window"]["height"].get<unsigned int>()), config["window"]["title"].get<std::string>(), sf::Style::Titlebar);
    sp_ = std::make_shared<SoundPlayer>();

    for (auto& el: config["assets"]["sounds"].items())
        sp_->LoadSound(el.key(), std::filesystem::path(el.value().get<std::string>()));

    gs_ = std::make_shared<GameState>();
    renderer_ = std::make_shared<Renderer>(gs_);
    scr_manager_ = std::make_shared<renderer::screen::ScreenManager>(gs_, sp_);

    scr_manager_->AddScreen("game-screen", std::make_shared<renderer::screen::GameScreen>(scr_manager_));
    scr_manager_->AddScreen("game-over-screen", std::make_shared<renderer::screen::GameOverScreen>(scr_manager_));

    scr_manager_->SwitchScreen("game-screen");
}

void Game::Run()
{
    // Game clock to synchronize actions and updates
    sf::Clock clock;

    // on fait tourner le programme jusqu'à ce que la fenêtre soit fermée
    while (window_.isOpen())
    {
        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        sf::Event event;
        auto screen = scr_manager_->get_current_screen();

        while (window_.pollEvent(event))
        {
            // évènement "fermeture demandée" : on ferme la fenêtre
            if (event.type == sf::Event::Closed)
                window_.close();
            
            if(screen) screen->HandleEvent(event);
        }

        auto elapsed = clock.restart().asSeconds();

        if(screen) screen->Update(elapsed);

        renderer_->Render(window_);
    }
}
