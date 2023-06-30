#ifndef ACC_ACT_H
#define ACC_ACT_H

#include "src/controllers/actions/action.hpp"
#include "src/vehicle/vehicle.hpp"

namespace actions::vehicle
{
    class AccelerateAction : public Action
    {
    public:
        explicit AccelerateAction(std::shared_ptr<Vehicle>);
        void Execute() override;

    private:
        std::shared_ptr<Vehicle> vehicle_;
    };
}

#endif
