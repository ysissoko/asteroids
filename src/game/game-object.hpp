#ifndef GAME_OBJ_H
#define GAME_OBJ_H

#include <string>
#include <memory>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>

class GameObject
{
public:
    explicit GameObject(const std::string_view &);
    sf::Vector2<float> get_position() const { return position_; };

    void set_mass(float mass) { mass_ = mass; }
    void set_position(const sf::Vector2<float> &position) { position_ = position; };
    void set_drawable(std::shared_ptr<sf::Drawable> drawable_obj) { drawable_obj_ = drawable_obj; }
    std::shared_ptr<sf::Drawable> get_drawable() { return drawable_obj_; }

    float get_mass() const { return mass_; };
    uint64_t get_id() const { return id_; };
    std::shared_ptr<sf::Drawable> get_drawable() const { return drawable_obj_; }

    virtual std::string_view to_string() const { return name_; }
    std::shared_ptr<sf::Drawable> Render() const { return drawable_obj_; };

    virtual void Update(float elapsed_time) = 0;

private:
    static uint64_t current_id_;
    uint64_t id_;
    float mass_{0};
    sf::Vector2<float> position_{0, 0};
    std::string_view name_;
    std::shared_ptr<sf::Drawable> drawable_obj_{nullptr};
};

#endif
