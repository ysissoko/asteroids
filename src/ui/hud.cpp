#include <src/ui/hud.hpp>
#include <sstream>
#include <spdlog/spdlog.h>

HUD::HUD() : GuiElement() {
    Init();
}

void HUD::Init() {
    if (!font_.loadFromFile("./assets/space_invaders.ttf")) {
        spdlog::error("Error loading font");
    }

    score_txt_ = std::make_shared<sf::Text>();
    score_txt_->setFont(font_);
    score_txt_->setPosition(50, 50);
    score_txt_->setFillColor(sf::Color::White);
    score_txt_->setStyle(sf::Text::Bold);
    score_txt_->setCharacterSize(20); // in pixels, not points!

    life_txt_ = std::make_shared<sf::Text>();
    life_txt_->setFont(font_);
    life_txt_->setPosition(650, 50);
    life_txt_->setFillColor(sf::Color::White);
    life_txt_->setStyle(sf::Text::Bold);
    life_txt_->setCharacterSize(20); // in pixels, not points!

    UpdateScore(0);
    UpdateLife(3);

    add_drawing(score_txt_);
    add_drawing(life_txt_);
}

void HUD::IncreaseScore() {
    UpdateScore(score_ + 10);
}

void HUD::UpdateScore(unsigned long score) {
    std::stringstream ss;

    score_ = score;

    ss << "Score " << score_;
    score_txt_->setString(ss.str());
}

void HUD::UpdateLife(unsigned long life) {
    std::stringstream ss;

    life_ = life;

    ss << "Life " << life_;
    life_txt_->setString(ss.str());
}
