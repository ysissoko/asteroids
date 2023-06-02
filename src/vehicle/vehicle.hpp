#ifndef VEH_H
#define VEH_H

#include <SFML/Graphics/CircleShape.hpp>

#include <src/game/game-object.hpp>
#include <src/game/game-state.hpp>
#include <src/simulator/simulator.hpp>
#include <src/renderer/soundplayer.hpp>

// States
#include <src/fsm/vehicle/states/vehicle-context.hpp>

#include <cmath>

constexpr float kAcceleration = 0.001f;
constexpr float kReloadTimeMs = 0.8f;
constexpr const float kRotateSpeed{45.0f};
constexpr const uint8_t kMaxSpeed{150};

constexpr double deg2rad(float angle) { return angle * M_PI / 180; }

class Vehicle : public GameObject, public std::enable_shared_from_this<Vehicle>
{
private:
    std::shared_ptr<fsm::vehicle::states::VehicleContext> ctx_{nullptr};
    float heading_angle_{0};
    float speed_{0};
    float reload_time_{kReloadTimeMs};
    std::shared_ptr<GameState> gs_{nullptr};
    std::shared_ptr<SoundPlayer> sp_{nullptr};

public:
    Vehicle(const std::string_view &name, std::shared_ptr<GameState> gs, std::shared_ptr<SoundPlayer> sp);
    virtual ~Vehicle() = default;

    void InitDrawable();
    void Shoot() const { ctx_->RequestShoot(); }
    void StopShoot() const { ctx_->RequestStopShoot(); }
    void RotateCCW() const { ctx_->RequestRotateCCW(); }
    void RotateCW() const { ctx_->RequestRotateCW(); }
    void RotateStop() const { ctx_->RequestRotateStop(); }
    void Accelerate() const { ctx_->RequestAccelerate(); }
    void Deccelerate() const { ctx_->RequestDeccelerate(); }

    void Update(float elapsed_time) override;
    void UpdatePosition(float elapsed_time);
    void UpdateRotation(float elapsed_time);
    void UpdateShooting(float elapsed_time);

    float get_heading_angle() const { return heading_angle_; }
    std::shared_ptr<sf::CircleShape> get_shape() const { return vehicle_shape_; }

private:
    std::shared_ptr<sf::CircleShape> vehicle_shape_;
};

#endif
