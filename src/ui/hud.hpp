#ifndef HUD_H
#define HUD_H

#include <src/ui/gui-element.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window.hpp>

class HUD : public GuiElement {
    public:
        HUD();
        ~HUD() = default;

        void Init();
        void UpdateScore(unsigned long score);
        void UpdateLife(unsigned long);
        void IncreaseScore();
    private:
        std::shared_ptr<sf::Text> score_txt_;
        std::shared_ptr<sf::Text> life_txt_;

        unsigned long score_;
        uint8_t life_;

        sf::Font font_;
};

#endif
