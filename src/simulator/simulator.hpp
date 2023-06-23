#ifndef SIMU_H
#define SIMU_H

#include <queue>
#include <memory>
#include <src/game/game-state.hpp>

class Simulator : public std::enable_shared_from_this<Simulator>
{
private:
    std::shared_ptr<GameState> gs_;

public:
    explicit Simulator(std::shared_ptr<GameState>);
    void Update(float);

    std::shared_ptr<GameState> get_game_state() const { return gs_; }
    void CheckCollision(std::shared_ptr<GameObject>);
};

#endif
