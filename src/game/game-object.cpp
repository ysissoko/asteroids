#include <src/game/game-object.hpp>

uint64_t GameObject::current_id_ = 1;

GameObject::GameObject(const std::string_view &name) : name_{name}
{
    id_ = current_id_++;
}
