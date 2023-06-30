#include "src/ui/hud.hpp"

#include <spdlog/spdlog.h>

#include <sstream>

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

    UpdateScore(0);

    add_drawing(score_txt_);
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
