#include "src/game/game-object.hpp"

uint64_t GameObject::current_id_ = 1;

GameObject::GameObject(ObjectType type, const std::string_view &name) : name_{name}, type_{type}
{
    id_ = current_id_++;
}
