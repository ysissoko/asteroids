#include "src/controllers/actions/vehicle/rotate-cw.hpp"

#include <spdlog/spdlog.h>

namespace actions::vehicle
{
    RotateCWAction::RotateCWAction(std::shared_ptr<Vehicle> vehicle) : vehicle_{vehicle}
    {
    }

    void RotateCWAction::Execute()
    {
        // spdlog::debug("executing rotate cw action");
        vehicle_->RotateCW();
    }
};
