#ifndef VEH_CTX_H
#define VEH_CTX_H

#include "src/fsm/vehicle/states/vehicle-state.hpp"

#include <iostream>
#include <memory>

namespace fsm::vehicle::states
{
    constexpr char ROTATE_IDLE = 0;
    constexpr char ROTATE_CCW = -1;
    constexpr char ROTATE_CW = 1;

    constexpr char DECCELERATION = -1;
    constexpr char ACCELERATION = 1;

    class VehicleContext : public std::enable_shared_from_this<VehicleContext>
    {
        /**
         * @var State A reference to the current state of the Context.
         */
    private:
        std::shared_ptr<fsm::vehicle::states::VehicleState> state_{nullptr};
        char rotate_dir_{ROTATE_IDLE};
        char accel_dir_{DECCELERATION};
        bool is_shooting_{false};

    public:
        explicit VehicleContext() = default;
        ~VehicleContext() = default;

        /**&
         * The Context allows changing the State object at runtime.
         */
        void TransitionTo(std::shared_ptr<VehicleState> state)
        {
            std::cout << "Context: Transition to " << typeid(state).name() << ".\n";
            this->state_ = state;
            this->state_->set_context(shared_from_this());
        }

        void RequestIdle() const
        {
            this->state_->HandleIdle();
        }

        void RequestAccelerate() const
        {
            this->state_->HandleAccelerate();
        }

        void RequestDeccelerate() const
        {
            this->state_->HandleDeccelerate();
        }

        void RequestRotateCCW() const
        {
            this->state_->HandleRotateCCW();
        }

        void RequestRotateCW() const
        {
            this->state_->HandleRotateCW();
        }

        void RequestRotateStop() const
        {
            this->state_->HandleRotateStop();
        }

        void RequestShoot() const
        {
            this->state_->HandleShoot();
        }

        void RequestStopShoot() const
        {
            this->state_->HandleStopShoot();
        }

        void set_rotate_dir(char rotate_dir)
        {
            rotate_dir_ = rotate_dir;
        }

        char get_rotate_dir() const
        {
            return rotate_dir_;
        }

        void set_accel_dir(char accel_dir)
        {
            accel_dir_ = accel_dir;
        }

        char get_accel_dir() const
        {
            return accel_dir_;
        }

        bool get_is_shooting() const
        {
            return is_shooting_;
        }

        void set_is_shooting(bool is_shooting)
        {
            is_shooting_ = is_shooting;
        }
    };
}

#endif
