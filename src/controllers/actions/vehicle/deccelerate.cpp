#include "src/controllers/actions/vehicle/deccelerate.hpp"
#include <spdlog/spdlog.h>
namespace actions::vehicle
{
    DeccelerateAction::DeccelerateAction(std::shared_ptr<Vehicle> vehicle) : vehicle_{vehicle}
    {
    }

    void DeccelerateAction::Execute()
    {
        // spdlog::debug("executing deccelerate action");
        vehicle_->Deccelerate();
    }
}
