#include <src/controllers/actions/vehicle/stop-shoot.hpp>
#include <spdlog/spdlog.h>

namespace actions::vehicle
{
    StopShootAction::StopShootAction(std::shared_ptr<Vehicle> vehicle) : vehicle_{vehicle}
    {
    }

    void StopShootAction::Execute()
    {
        // spdlog::debug("executing stop shoot action");
        vehicle_->StopShoot();
    }
}
