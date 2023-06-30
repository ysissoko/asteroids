#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "src/game/game-object.hpp"
#include "src/ui/gui-element.hpp"

#include <spdlog/spdlog.h>

#include <algorithm>
#include <unordered_map>
#include <memory>

class GameState
{
public:
    GameState() = default;

    void AddObject(std::shared_ptr<GameObject> obj) { objects_.try_emplace(obj->get_id(), obj); };
    void AddUiObject(std::shared_ptr<GuiElement> obj) { ui_objects_.push_back(obj); };
    void Reset() { 
        ui_objects_.clear(); 
        objects_.clear(); 
    }

    void RemoveObject(std::shared_ptr<GameObject> obj)
    {
        if (objects_.count(obj->get_id()))
            objects_.erase(obj->get_id());
    };

    void RemoveObject(uint64_t id)
    {
        spdlog::debug("objects_size before {}", objects_.size());
        spdlog::debug("erase object id {}", id);
        objects_.erase(id);
        spdlog::debug("objects_size after {}", objects_.size());
    };
    
    std::shared_ptr<GameObject> get_object(uint64_t id) const { return objects_.at(id); };
    std::unordered_map<uint64_t, std::shared_ptr<GameObject>> get_objects() const { return objects_; };
    std::vector<std::shared_ptr<GuiElement>> get_ui_objects() const { return ui_objects_; };
    void set_player(std::shared_ptr<GameObject> go) { go_ = go; };
    std::shared_ptr<GameObject> get_player() const { return go_; };

    long GetObjectCount(ObjectType type)
    {
        return std::count_if(objects_.begin(), objects_.end(), [&type](std::pair<uint64_t, std::shared_ptr<GameObject>> obj)
                             { return obj.second->get_type() == type; });
    }

private:
    std::shared_ptr<GameObject> go_;
    std::unordered_map<uint64_t, std::shared_ptr<GameObject>> objects_;
    std::vector<std::shared_ptr<GuiElement>> ui_objects_;
};

#endif
