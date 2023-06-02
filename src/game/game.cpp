#include <src/game/game.hpp>
#include <src/controllers/pc-controller.hpp>
#include "config.h"
#include <spdlog/spdlog.h>

Game::Game()
{
    Init();
}

void Game::Init()
{
    window_.create(sf::VideoMode(800, 600), "ASTEROIDS");
    sp_ = std::make_shared<SoundPlayer>();
    sp_->LoadSound("shoot", std::filesystem::path("/home/yasuke/projects/cpp/asteroids/assets/shoot.wav"));

    gs_ = std::make_shared<GameState>();
    sim_ = std::make_shared<Simulator>(gs_);
    renderer_ = std::make_shared<Renderer>(gs_);
    vehicle_ = std::make_shared<Vehicle>(std::string_view("ship"), gs_, sp_);
    pc_controller_ = std::make_shared<PcController>(vehicle_);

    gs_->AddObject(vehicle_);

    event_handlers_.push_back(pc_controller_);
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
        while (window_.pollEvent(event))
        {
            // évènement "fermeture demandée" : on ferme la fenêtre
            if (event.type == sf::Event::Closed)
                window_.close();

            for (auto event_handler : event_handlers_)
            {
                event_handler->HandleEvent(event);
            }
        }

        sim_->Update(clock.restart().asSeconds());
        renderer_->Render(window_);
    }
}
