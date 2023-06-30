#include <src/vehicle/vehicle.hpp>
#include <src/vehicle/bullet.hpp>
#include <src/game/object-type.hpp>
#include <src/common/common.hpp>
#include <src/game/game.hpp>

#include <SFML/Graphics/CircleShape.hpp>
#include <spdlog/spdlog.h>

Vehicle::Vehicle(const std::string_view &name, std::shared_ptr<GameState> gs, std::shared_ptr<SoundPlayer> sp, std::shared_ptr<HUD> hud, std::shared_ptr<renderer::screen::ScreenManager> scr_mgr) : GameObject(ObjectType::SHIP, name), gs_{gs}, sp_{sp}, hud_{hud}, scr_mgr_(scr_mgr)
{
    ctx_ = std::make_shared<fsm::vehicle::states::VehicleContext>();
    ctx_->TransitionTo(std::make_shared<fsm::vehicle::states::VehicleState>());

    acceleration_ = Game::config["vehicle"]["acceleration"].get<float>();
    decceleration_ = Game::config["vehicle"]["decceleration"].get<float>();

    reload_time_ms_ = Game::config["vehicle"]["bullet"]["reloadTimeMs"].get<float>();
    rotate_speed_ = Game::config["vehicle"]["rotateSpeed"].get<float>();
    max_speed_ = Game::config["vehicle"]["maxSpeed"].get<unsigned int>();

    life_ = Game::config["vehicle"]["life"].get<uint8_t>();
    initial_position_ = sf::Vector2f(Game::config["vehicle"]["initialPos"]["x"].get<float>(), Game::config["vehicle"]["initialPos"]["y"].get<float>());

    invincible_max_duration_ = Game::config["vehicle"]["invincibleMaxDuration"].get<float>();
    blink_max_duration_ = Game::config["vehicle"]["blinkMaxDuration"].get<float>();
    bullet_speed_ = Game::config["vehicle"]["bullet"]["speed"].get<float>();

    InitDrawable();
}

void Vehicle::InitDrawable()
{
    vehicle_shape_ = std::make_shared<sf::CircleShape>(16, 3);
    vehicle_shape_->setOrigin(12, 12);
    vehicle_shape_->setPosition(initial_position_);
    vehicle_shape_->setFillColor(sf::Color::Transparent);
    vehicle_shape_->setOutlineColor(sf::Color::White);
    vehicle_shape_->setOutlineThickness(2.0f);

    set_shape(vehicle_shape_);
}

void Vehicle::UpdatePosition(float elapsed_time)
{
    speed_ += max_speed_ * ((this->ctx_->get_accel_dir() > 0) ? acceleration_ : decceleration_) * this->ctx_->get_accel_dir();

    vehicle_shape_->move(-sf::Vector2f(speed_ * elapsed_time * std::cos(this->heading_angle_), speed_ * elapsed_time * std::sin(heading_angle_)));

    if (speed_ < 0)
        speed_ = 0;

    if (speed_ > max_speed_)
        speed_ = max_speed_;
}

void Vehicle::UpdateRotation(float elapsed_time)
{
    // Rotate the vehicle
    vehicle_shape_->rotate(rotate_speed_ * this->ctx_->get_rotate_dir() * elapsed_time);
    this->heading_angle_ = deg2rad((vehicle_shape_->getRotation() + 90));
}

void Vehicle::UpdateShooting(float elapsed_time)
{
    if (this->ctx_->get_is_shooting() && reload_time_ >= reload_time_ms_)
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
    if (invincible_duration_ <= invincible_max_duration_)
        UpdateInvincible(elapsed_time);
    else
        vehicle_shape_->setOutlineColor(sf::Color::White);

    sf::Vector2f pos = vehicle_shape_->getPosition();

    const unsigned int w_width = Game::config["window"]["width"];
    const unsigned int w_height = Game::config["window"]["height"];

    if (pos.x >= w_width)
        pos.x = 0;
    else if (pos.x <= 0)
        pos.x = w_width;
    else if (pos.y <= 0)
        pos.y = w_height;
    else if (pos.y >= w_height)
        pos.y = 0;

    //spdlog::debug("pos y: {}, window height: {}, window width: {}", pos.y, w_height, w_width);

    vehicle_shape_->setPosition(pos);
}

void Vehicle::UpdateInvincible(float elapsed_time)
{
    invincible_duration_ += elapsed_time;
    blink_duration_ += elapsed_time;

    uint8_t opacity = 255;

    if (blink_duration_ <= blink_max_duration_)
        opacity = 127;
    else if (blink_duration_ <= 2 * blink_max_duration_)
        opacity = 255;
    else
        blink_duration_ = 0;

    vehicle_shape_->setOutlineColor(sf::Color(255, 255, 255, opacity));
}

void Vehicle::Respawn()
{
    life_--;
    invincible_duration_ = 0;
    speed_ = 0;
    RequestIdle();

    auto radius = vehicle_shape_->getRadius();
    vehicle_shape_->setPosition(initial_position_);
    vehicle_shape_->move(sf::Vector2f(-radius, -radius));
}

void Vehicle::CollideWith(std::shared_ptr<GameObject> obj)
{
    if (obj->get_type() == ObjectType::ASTEROID && invincible_duration_ >= invincible_max_duration_)
    {
        scr_mgr_->SwitchScreen("game-over-screen");
    }
}
