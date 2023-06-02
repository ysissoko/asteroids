#include <src/vehicle/vehicle.hpp>
#include <src/vehicle/bullet.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <spdlog/spdlog.h>

Vehicle::Vehicle(const std::string_view &name, std::shared_ptr<GameState> gs, std::shared_ptr<SoundPlayer> sp) : GameObject(name), gs_{gs}, sp_{sp}
{
    ctx_ = std::make_shared<fsm::vehicle::states::VehicleContext>();

    ctx_->TransitionTo(std::make_shared<fsm::vehicle::states::VehicleState>());
    InitDrawable();
}

void Vehicle::InitDrawable()
{
    vehicle_shape_ = std::make_shared<sf::CircleShape>(16, 3);
    spdlog::debug("shape radius {}", vehicle_shape_->getRadius());
    vehicle_shape_->setOrigin(12, 12);
    vehicle_shape_->setPosition(sf::Vector2f(400, 400));
    vehicle_shape_->setFillColor(sf::Color::Transparent);
    vehicle_shape_->setOutlineColor(sf::Color::White);
    vehicle_shape_->setOutlineThickness(2.0f);

    set_drawable(vehicle_shape_);
}

void Vehicle::UpdatePosition(float elapsed_time)
{
    speed_ += kMaxSpeed * kAcceleration * this->ctx_->get_accel_dir();
    vehicle_shape_->move(-sf::Vector2f(speed_ * elapsed_time * std::cos(this->heading_angle_), speed_ * elapsed_time * std::sin(heading_angle_)));

    if (speed_ < 0)
        speed_ = 0;

    if (speed_ > kMaxSpeed)
        speed_ = kMaxSpeed;
}

void Vehicle::UpdateRotation(float elapsed_time)
{
    // Rotate the vehicle
    vehicle_shape_->rotate(kRotateSpeed * this->ctx_->get_rotate_dir() * elapsed_time);

    this->heading_angle_ = deg2rad((vehicle_shape_->getRotation() + 90));
}

void Vehicle::UpdateShooting(float elapsed_time)
{
    if (this->ctx_->get_is_shooting() && reload_time_ >= kReloadTimeMs)
    {
        sp_->PlaySound("shoot");
        gs_->AddObject(std::make_shared<Bullet>(shared_from_this()));
        reload_time_ = 0;
    }

    reload_time_ += elapsed_time;
}

void Vehicle::Update(float elapsed_time)
{
    UpdatePosition(elapsed_time);
    UpdateRotation(elapsed_time);
    UpdateShooting(elapsed_time);

    sf::Vector2f pos = vehicle_shape_->getPosition();

    if (pos.x >= 800)
        pos.x = 0;
    if (pos.x <= -16)
        pos.x = 800;
    if (pos.y <= 0)
        pos.y = 600;
    if (pos.y >= 600)
        pos.y = 0;

    vehicle_shape_->setPosition(pos);
}
