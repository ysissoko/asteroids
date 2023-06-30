#include <src/ui/menu.hpp>
#include <spdlog/spdlog.h>

Menu::Menu(std::shared_ptr<renderer::screen::ScreenManager> scr_mgr): GuiElement() {
    Init(scr_mgr);
}

void Menu::Init(std::shared_ptr<renderer::screen::ScreenManager> scr_mgr) {
    if (!font_.loadFromFile("./assets/space_invaders.ttf")) {
        spdlog::error("Error loading font");
    }

    game_over_txt_ = std::make_shared<sf::Text>();
    play_txt_ = std::make_shared<sf::Text>();
    exit_txt_ = std::make_shared<sf::Text>();

    game_over_txt_->setFont(font_);
    play_txt_->setFont(font_);
    exit_txt_->setFont(font_);

    game_over_txt_->setPosition(200, 200);
    game_over_txt_->setFillColor(sf::Color::White);
    game_over_txt_->setStyle(sf::Text::Bold);
    game_over_txt_->setCharacterSize(64); // in pixels, not points!
    game_over_txt_->setString("GAME OVER");
    
    play_txt_->setPosition(200, 350);
    play_txt_->setFillColor(sf::Color::White);
    play_txt_->setStyle(sf::Text::Bold);
    play_txt_->setCharacterSize(20); // in pixels, not points!
    play_txt_->setString("Restart");

    exit_txt_->setPosition(200, 450);
    exit_txt_->setFillColor(sf::Color::White);
    exit_txt_->setStyle(sf::Text::Bold);
    exit_txt_->setCharacterSize(20); // in pixels, not points!
    exit_txt_->setString("Quit");

    add_drawing(game_over_txt_);
    add_drawing(play_txt_);
    add_drawing(exit_txt_);

    auto confirm_pos = play_txt_->getPosition();
    auto deny_pos = exit_txt_->getPosition();

    cursor_ = std::make_shared<Cursor>(sf::Vector2f(170, 350), sf::Vector2f(170 ,450), scr_mgr);
    
    add_drawing(cursor_);
}
