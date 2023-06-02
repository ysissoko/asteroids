#include <src/controllers/actions/vehicle/rotate-ccw.hpp>
#include <spdlog/spdlog.h>

namespace actions::vehicle
{
    RotateCCWAction::RotateCCWAction(std::shared_ptr<Vehicle> vehicle) : vehicle_{vehicle}
    {
    }

    void RotateCCWAction::Execute()
    {
        spdlog::debug("executing rotate ccw action");
        vehicle_->RotateCCW();
    }
};
