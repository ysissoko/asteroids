#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H

#include <SFML/Window.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <memory>

class GuiElement : public std::enable_shared_from_this<GuiElement> {
    public:
        GuiElement() { }
        
        void set_position(const sf::Vector2i& position) { position_ = position; }
        void set_position(int x, int y) { position_ = sf::Vector2i(x, y); }
        void set_visible(bool visible) { visible_ = visible; }
        void set_parent(std::shared_ptr<GuiElement> parent) { parent_ = parent; parent->AddChild(shared_from_this()); }
        void add_drawing(std::shared_ptr<sf::Drawable> drawing) { drawings_.push_back(drawing); }

        sf::Vector2i get_position() const { return position_; }
        bool get_visible() const { return visible_; };
        std::shared_ptr<GuiElement> get_parent() const { return parent_; }
        std::vector<std::shared_ptr<GuiElement>> get_childs() const { return childs_; }
        std::vector<std::shared_ptr<sf::Drawable>> get_drawings() { return drawings_; }

        void AddChild(std::shared_ptr<GuiElement> elem) { childs_.push_back(elem); }
    private:
        sf::Vector2i position_;
        bool visible_{true};
        std::shared_ptr<GuiElement> parent_;
        std::vector<std::shared_ptr<GuiElement>> childs_;

        std::vector<std::shared_ptr<sf::Drawable>> drawings_;
};

#endif
