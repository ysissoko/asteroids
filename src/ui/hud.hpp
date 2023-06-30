#ifndef HUD_H
#define HUD_H

#include "src/ui/gui-element.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window.hpp>

class HUD : public GuiElement {
    public:
        HUD();
        ~HUD() = default;

        void Init();
        void UpdateScore(unsigned long score);
        void IncreaseScore();
    private:
        std::shared_ptr<sf::Text> score_txt_;
        unsigned long score_;
        sf::Font font_;
};

#endif
