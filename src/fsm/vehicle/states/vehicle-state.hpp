#ifndef VEH_STATE_H
#define VEH_STATE_H

#include <src/fsm/vehicle/states/state.hpp>

namespace fsm::vehicle::states
{
    class VehicleState : public State
    {
    public:
        void HandleIdle() override;
        void HandleAccelerate() override;
        void HandleDeccelerate() override;
        void HandleRotateCW() override;
        void HandleRotateCCW() override;
        void HandleRotateStop() override;
        void HandleShoot() override;
        void HandleStopShoot() override;
    };
};

#endif
