#include <src/controllers/actions/vehicle/shoot.hpp>
#include <spdlog/spdlog.h>

namespace actions::vehicle
{
    ShootAction::ShootAction(std::shared_ptr<Vehicle> vehicle) : vehicle_{vehicle}
    {
    }

    void ShootAction::Execute()
    {
        // spdlog::debug("executing shoot action");
        vehicle_->Shoot();
    }
}
