#ifndef ROT_CW_ACT_H
#define ROT_CW_ACT_H

#include <src/controllers/actions/action.hpp>
#include <src/vehicle/vehicle.hpp>

namespace actions::vehicle
{
    class RotateCWAction : public Action
    {
    public:
        explicit RotateCWAction(std::shared_ptr<Vehicle>);
        void Execute() override;

    private:
        std::shared_ptr<Vehicle> vehicle_;
    };
};

#endif
