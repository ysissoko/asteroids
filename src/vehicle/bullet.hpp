#ifndef BULLET_H
#define BULLET_H

#include "src/game/game-object.hpp"
#include "src/vehicle/vehicle.hpp"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Bullet : public GameObject
{
private:
    void InitDrawable(std::shared_ptr<Vehicle> veh);

    std::shared_ptr<sf::CircleShape> bullet_shape_;
    float bullet_heading_{0};
    float max_duration_{1.0};
    float speed_{280};

public:
    explicit Bullet(std::shared_ptr<Vehicle> veh);
    ~Bullet() final = default;

    void Update(float elapsed_time) override;
    void CollideWith(std::shared_ptr<GameObject>) override;

    float get_max_duration() const { return max_duration_; }
};

#endif
