#include <src/fsm/vehicle/states/vehicle-state.hpp>
#include <src/fsm/vehicle/states/vehicle-context.hpp>
#include <spdlog/spdlog.h>

namespace fsm::vehicle::states
{
    void VehicleState::HandleIdle()
    {
        // spdlog::debug("handling idle state request");
        this->ctx_->set_accel_dir(DECCELERATION);
        this->ctx_->set_rotate_dir(ROTATE_IDLE);
    }

    void VehicleState::HandleAccelerate()
    {
        // spdlog::debug("handling accelerate state request");
        this->ctx_->set_accel_dir(ACCELERATION);
    }

    void VehicleState::HandleDeccelerate()
    {
        // spdlog::debug("handling deccelerate state request");
        this->ctx_->set_accel_dir(DECCELERATION);
    }

    void VehicleState::HandleRotateCW()
    {
        // spdlog::debug("handling rotate cw state request");
        this->ctx_->set_rotate_dir(ROTATE_CW);
    }

    void VehicleState::HandleRotateCCW()
    {
        // spdlog::debug("handling rotate ccw state request");
        this->ctx_->set_rotate_dir(ROTATE_CCW);
    }

    void VehicleState::HandleRotateStop()
    {
        this->ctx_->set_rotate_dir(ROTATE_IDLE);
    }

    void VehicleState::HandleShoot()
    {
        // spdlog::debug("handling shoot state request");
        this->ctx_->set_is_shooting(true);
    }

    void VehicleState::HandleStopShoot()
    {
        // spdlog::debug("handling stop shoot state request");
        this->ctx_->set_is_shooting(false);
    }
};
