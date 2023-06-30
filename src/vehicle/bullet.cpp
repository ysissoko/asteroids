#include "src/vehicle/bullet.hpp"
#include "src/game/object-type.hpp"

Bullet::Bullet(std::shared_ptr<Vehicle> veh) : GameObject(ObjectType::BULLET, "bullet")
{
    bullet_heading_ = veh->get_heading_angle();
    InitDrawable(veh);
}

void Bullet::InitDrawable(std::shared_ptr<Vehicle> veh)
{
    bullet_shape_ = std::make_shared<sf::CircleShape>(2);
    bullet_shape_->setOrigin(bullet_shape_->getRadius() / 2, bullet_shape_->getRadius() / 2);

    bullet_shape_->setPosition(veh->get_shape()->getPosition());
    bullet_shape_->setFillColor(sf::Color::White);

    bullet_shape_->move(-sf::Vector2f(std::dynamic_pointer_cast<sf::CircleShape>(veh->get_shape())->getRadius() * std::cos(bullet_heading_), std::dynamic_pointer_cast<sf::CircleShape>(veh->get_shape())->getRadius() * std::sin(bullet_heading_)));
    speed_ = veh->get_bullet_speed();
    set_shape(bullet_shape_);
}

void Bullet::Update(float elapsed_time)
{
    bullet_shape_->move(-sf::Vector2f(speed_ * elapsed_time * std::cos(bullet_heading_), speed_ * elapsed_time * std::sin(bullet_heading_)));
}

void Bullet::CollideWith(std::shared_ptr<GameObject> obj)
{
}
