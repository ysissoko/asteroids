#ifndef CURSOR_H
#define CURSOR_H

#include "src/renderer/screens/screen-manager.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <spdlog/spdlog.h>

class Cursor : public sf::RectangleShape {
    public:
        Cursor(const sf::Vector2f& confirm_pos, const sf::Vector2f& deny_pos,  std::shared_ptr<renderer::screen::ScreenManager> scr_manager) : RectangleShape(), confirm_pos_{confirm_pos}, deny_pos_{deny_pos}, scr_manager_{scr_manager}
        {
            setSize(sf::Vector2f(20, 20));
            setFillColor(sf::Color::White);
            Move();
        }

        void Move() { 
            spdlog::debug("move cursor: {}", confirm_);
            confirm_ = !confirm_;
            setPosition((confirm_) ? confirm_pos_ : deny_pos_);
        }

        void Confirm() {
            if (confirm_)
                scr_manager_->SwitchScreen("game-screen");
        }
    private:
        bool confirm_{false};
        sf::Vector2f confirm_pos_;
        sf::Vector2f deny_pos_;
        std::shared_ptr<renderer::screen::ScreenManager> scr_manager_;
};

#endif
