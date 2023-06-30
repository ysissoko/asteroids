#ifndef MENU_H
#define MENU_H

#include "src/ui/gui-element.hpp"
#include "src/renderer/screens/screen-manager.hpp"
#include "src/ui/cursor.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class Menu : public GuiElement {
    public:
        Menu(std::shared_ptr<renderer::screen::ScreenManager> scr_mgr);
        ~Menu() = default;
        void Init(std::shared_ptr<renderer::screen::ScreenManager> scr_mgr);

        std::shared_ptr<Cursor> get_cursor() const  { return cursor_; }
    private:
        std::shared_ptr<sf::Text> game_over_txt_{nullptr};
        std::shared_ptr<sf::Text> play_txt_{nullptr};
        std::shared_ptr<sf::Text> exit_txt_{nullptr};
        std::shared_ptr<Cursor> cursor_{nullptr};
        sf::Font font_;
};

#endif
