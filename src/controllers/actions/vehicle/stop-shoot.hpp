#ifndef STOP_SHOOT_ACT_H
#define STOP_SHOOT_ACT_H

#include <src/controllers/actions/action.hpp>
#include <src/vehicle/vehicle.hpp>

namespace actions::vehicle
{
    class StopShootAction : public Action
    {
    public:
        StopShootAction(std::shared_ptr<Vehicle>);
        void Execute() override;

    private:
        std::shared_ptr<Vehicle> vehicle_;
    };
}

#endif
