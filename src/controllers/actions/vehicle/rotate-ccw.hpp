#ifndef ROT_CCW_ACT_H
#define ROT_CCW_ACT_H

#include <src/controllers/actions/action.hpp>
#include <src/vehicle/vehicle.hpp>

namespace actions::vehicle
{
    class RotateCCWAction : public Action
    {
    public:
        explicit RotateCCWAction(std::shared_ptr<Vehicle>);
        void Execute() override;

    private:
        std::shared_ptr<Vehicle> vehicle_;
    };
}

#endif
