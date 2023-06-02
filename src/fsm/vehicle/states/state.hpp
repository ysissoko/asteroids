#ifndef STATE_H
#define STATE_H

#include <memory>

namespace fsm::vehicle::states
{
    class VehicleContext;

    class State
    {
    protected:
        std::shared_ptr<VehicleContext> ctx_{nullptr};

    public:
        virtual ~State() = default;

        void set_context(std::shared_ptr<VehicleContext> ctx)
        {
            ctx_ = ctx;
        }

        virtual void HandleIdle() = 0;
        virtual void HandleAccelerate() = 0;
        virtual void HandleDeccelerate() = 0;
        virtual void HandleRotateCW() = 0;
        virtual void HandleRotateCCW() = 0;
        virtual void HandleShoot() = 0;
        virtual void HandleStopShoot() = 0;
        virtual void HandleRotateStop() = 0;
    };
};

#endif
