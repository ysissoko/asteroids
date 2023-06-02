#ifndef DECC_ACT_H
#define DECC_ACT_H

#include <src/controllers/actions/action.hpp>
#include <src/vehicle/vehicle.hpp>

namespace actions::vehicle
{
    class DeccelerateAction : public Action
    {
    public:
        explicit DeccelerateAction(std::shared_ptr<Vehicle>);
        void Execute() override;

    private:
        std::shared_ptr<Vehicle> vehicle_;
    };
}

#endif
