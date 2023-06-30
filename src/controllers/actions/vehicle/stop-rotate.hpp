#ifndef STOP_ROT_ACT_H
#define STOP_ROT_ACT_H

#include "src/controllers/actions/action.hpp"
#include "src/vehicle/vehicle.hpp"

namespace actions::vehicle
{
    class StopRotateAction : public Action
    {
    public:
        explicit StopRotateAction(std::shared_ptr<Vehicle>);
        void Execute() override;

    private:
        std::shared_ptr<Vehicle> vehicle_;
    };
}

#endif
