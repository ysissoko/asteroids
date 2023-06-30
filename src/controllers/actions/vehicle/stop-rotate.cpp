#include "src/controllers/actions/vehicle/stop-rotate.hpp"
#include <spdlog/spdlog.h>

namespace actions::vehicle
{
    StopRotateAction::StopRotateAction(std::shared_ptr<Vehicle> vehicle) : vehicle_{vehicle}
    {
    }

    void StopRotateAction::Execute()
    {
        // spdlog::debug("executing stop rotate action");
        vehicle_->RotateStop();
    }
};
