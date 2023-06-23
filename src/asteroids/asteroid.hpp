#ifndef ASTEROID_H
#define ASTEROID_H

#include <SFML/Graphics/ConvexShape.hpp>
#include <src/game/game-object.hpp>
#include <src/asteroids/generator.hpp>

class Asteroid : public GameObject, public std::enable_shared_from_this<Asteroid>
{
public:
    explicit Asteroid(std::shared_ptr<Generator> gen, const sf::Vector2f &initial_pos, float speed, float angle, unsigned int life);
    ~Asteroid() final = default;

    unsigned int get_life() const { return life_; }
    float get_speed() const { return speed_; }
    float get_angle() const { return angle_; }

    void Update(float elapsed_time) override;
    void CollideWith(std::shared_ptr<GameObject>) override;
    void UpdateConvexShapePoints(const std::vector<sf::Vector2f> &rand_points) const;
    void Init();

private:
    std::shared_ptr<sf::ConvexShape> shape_{nullptr};
    std::shared_ptr<Generator> gen_{nullptr};
    sf::Vector2f initial_pos_;
    float angle_;
    float speed_;
    unsigned int life_;
};

#endif
