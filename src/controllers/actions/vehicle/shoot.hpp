#ifndef SHOOT_ACT_H
#define SHOOT_ACT_H

#include <src/controllers/actions/action.hpp>
#include <src/vehicle/vehicle.hpp>

namespace actions::vehicle
{
    class ShootAction : public Action
    {
    public:
        ShootAction(std::shared_ptr<Vehicle>);
        void Execute() override;

    private:
        std::shared_ptr<Vehicle> vehicle_;
    };
}

#endif
