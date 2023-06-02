#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <unordered_map>
#include <memory>
#include <src/game/game-object.hpp>

class GameState
{
public:
    GameState();
    void AddObject(std::shared_ptr<GameObject> obj) { objects_.emplace(std::make_pair(obj->get_id(), obj)); };
    void RemoveObject(std::shared_ptr<GameObject> obj) { objects_.erase(obj->get_id()); };
    std::shared_ptr<GameObject> get_object(uint64_t id) const { return objects_.at(id); };
    std::unordered_map<uint64_t, std::shared_ptr<GameObject>> get_objects() const { return objects_; };
    void set_player(std::shared_ptr<GameObject> go) { go_ = go; };
    std::shared_ptr<GameObject> get_player() const { return go_; };

private:
    std::shared_ptr<GameObject> go_;
    std::unordered_map<uint64_t, std::shared_ptr<GameObject>> objects_;
};

#endif
