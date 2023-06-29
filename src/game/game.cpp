#include <fstream>

#include <src/game/game.hpp>
#include <src/controllers/pc-controller.hpp>
#include <src/ui/hud.hpp>
#include <config.h>

#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

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

    auto hud = std::make_shared<HUD>();

    gs_ = std::make_shared<GameState>();
    sim_ = std::make_shared<Simulator>(gs_);
    renderer_ = std::make_shared<Renderer>(gs_);
    vehicle_ = std::make_shared<Vehicle>(std::string_view("ship"), gs_, sp_, hud);
    pc_controller_ = std::make_shared<PcController>(vehicle_);

    gen_ = std::make_shared<Generator>(gs_, config["generators"][0], hud, sp_);
    gen2_ = std::make_shared<Generator>(gs_, config["generators"][1], hud, sp_);

    gs_->AddObject(vehicle_);
    gs_->AddUiObject(hud);

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

        auto elapsed = clock.restart().asSeconds();
        sim_->Update(elapsed);
        gen_->Update(elapsed);
        gen2_->Update(elapsed);

        renderer_->Render(window_);
    }
}
