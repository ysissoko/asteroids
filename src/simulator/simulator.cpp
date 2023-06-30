#include "src/simulator/simulator.hpp"
#include "src/controllers/actions/action.hpp"

Simulator::Simulator(std::shared_ptr<GameState> gs) : gs_{gs}
{
}

void Simulator::Update(float elapsed_time_in_sec)
{
    for (const auto obj : gs_->get_objects())
    {
        CheckCollision(obj.second);
        obj.second->Update(elapsed_time_in_sec);
    }
}

void Simulator::CheckCollision(std::shared_ptr<GameObject> current_obj)
{
    for (const auto obj : gs_->get_objects())
    {
        auto go = obj.second;
        if (current_obj->get_id() != go->get_id())
        {
            auto rectCurrentObj = current_obj->get_shape()->getGlobalBounds();
            auto rectOtherObj = go->get_shape()->getGlobalBounds();

            if (rectCurrentObj.intersects(rectOtherObj))
            {
                current_obj->CollideWith(go);
            }
        }
    }
}
