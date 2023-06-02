#ifndef BULLET_H_
#define BULLET_H_

#include <src/game/game-object.hpp>
#include <src/vehicle/vehicle.hpp>

constexpr unsigned char kSpeed{200};

class Bullet : public GameObject
{
private:
    void InitDrawable(std::shared_ptr<Vehicle> veh);

    std::shared_ptr<sf::CircleShape> bullet_shape_;
    float bullet_heading_{0};

public:
    explicit Bullet(std::shared_ptr<Vehicle> veh);
    virtual ~Bullet() = default;

    void Update(float elapsed_time) override;
};

#endif
