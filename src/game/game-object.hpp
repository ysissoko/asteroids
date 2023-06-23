#ifndef GAME_OBJ_H
#define GAME_OBJ_H

#include <string>
#include <memory>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Shape.hpp>
#include "object-type.hpp"

class GameObject
{
public:
    explicit GameObject(ObjectType, const std::string_view &);
    virtual ~GameObject() = default;

    sf::Vector2<float> get_position() const { return shape_->getPosition(); };

    void set_position(const sf::Vector2<float> &position) const { shape_->setPosition(position); };
    void set_shape(std::shared_ptr<sf::Shape> shape) { shape_ = shape; }
    std::shared_ptr<sf::Shape> get_shape() const { return shape_; }

    uint64_t get_id() const { return id_; };
    ObjectType get_type() const { return type_; }
    std::shared_ptr<sf::Shape> get_drawable() const { return shape_; }

    virtual std::string_view ToString() const { return name_; }

    virtual void Update(float elapsed_time) = 0;
    virtual void CollideWith(std::shared_ptr<GameObject>) = 0;

private:
    static uint64_t current_id_;
    uint64_t id_;
    std::string_view name_;
    std::shared_ptr<sf::Shape> shape_{nullptr};
    ObjectType type_;
};

#endif
