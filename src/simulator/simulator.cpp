#include <src/simulator/simulator.hpp>
#include <src/controllers/actions/action.hpp>

Simulator::Simulator(std::shared_ptr<GameState> gs)
{
    gs_ = gs;
}

void Simulator::Update(float elapsed_time_in_sec)
{
    for (const auto obj : gs_->get_objects())
    {
        // for (const auto coll_obj : gs_->get_objects())
        // {
        //     if (coll_obj.first == obj.first)
        //         continue;
        //     else
        //         obj.second->get_drawable()->getGlobalBounds()
        // }
        obj.second->Update(elapsed_time_in_sec);
    }
}
