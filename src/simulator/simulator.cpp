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
        obj.second->Update(elapsed_time_in_sec);
    }
}
