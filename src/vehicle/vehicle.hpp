#ifndef VEH_H
#define VEH_H

#include <cmath>

#include <src/game/game-object.hpp>
#include <src/game/game-state.hpp>
#include <src/simulator/simulator.hpp>
#include <src/renderer/soundplayer.hpp>
#include <src/fsm/vehicle/states/vehicle-context.hpp>
#include <src/ui/hud.hpp>

#include <SFML/Graphics/CircleShape.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Vehicle : public GameObject, public std::enable_shared_from_this<Vehicle>
{
private:
    std::shared_ptr<fsm::vehicle::states::VehicleContext> ctx_{nullptr};
    float heading_angle_{0};
    float speed_{0};
    float reload_time_{0};
    std::shared_ptr<GameState> gs_{nullptr};
    std::shared_ptr<SoundPlayer> sp_{nullptr};

    float acceleration_{0.004f};
    float decceleration_{0.0001};
    float reload_time_ms_{0.3f};
    float rotate_speed_{90.0f};
    unsigned int max_speed_{300};
    uint8_t life_;
    sf::Vector2f initial_position_;
    float invincible_duration_;
    float invincible_max_duration_;
    float blink_duration_{0};
    float blink_max_duration_;
    float bullet_speed_{280};
    std::shared_ptr<HUD> hud_;
public:
    Vehicle(const std::string_view &name, std::shared_ptr<GameState> gs, std::shared_ptr<SoundPlayer> sp, std::shared_ptr<HUD> hud);
    ~Vehicle() final = default;

    void InitDrawable();
    void Shoot() const { ctx_->RequestShoot(); }
    void StopShoot() const { ctx_->RequestStopShoot(); }
    void RotateCCW() const { ctx_->RequestRotateCCW(); }
    void RotateCW() const { ctx_->RequestRotateCW(); }
    void RotateStop() const { ctx_->RequestRotateStop(); }
    void Accelerate() const { ctx_->RequestAccelerate(); }
    void Deccelerate() const { ctx_->RequestDeccelerate(); }
    void RequestIdle() const { ctx_->RequestIdle(); }
    void Respawn();

    void Update(float elapsed_time) override;
    void UpdatePosition(float elapsed_time);
    void UpdateRotation(float elapsed_time);
    void UpdateShooting(float elapsed_time);
    void UpdateInvincible(float elapsed_time);

    void CollideWith(std::shared_ptr<GameObject>) override;

    float get_heading_angle() const { return heading_angle_; }
    float get_bullet_speed() const { return bullet_speed_; }

private:
    std::shared_ptr<sf::CircleShape> vehicle_shape_;
};

#endif
