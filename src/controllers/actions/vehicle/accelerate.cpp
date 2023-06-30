#include "src/controllers/actions/vehicle/accelerate.hpp"

#include <spdlog/spdlog.h>

namespace actions::vehicle
{
    AccelerateAction::AccelerateAction(std::shared_ptr<Vehicle> vehicle) : vehicle_{vehicle}
    {
    }

    void AccelerateAction::Execute()
    {
        // spdlog::debug("executing accelerate action");
        vehicle_->Accelerate();
    }
}
