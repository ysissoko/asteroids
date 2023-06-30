#ifndef SIM_H
#define SIM_H

class Simulator;

#include <string>
#include <memory>

namespace actions
{
    class Action
    {
    public:
        virtual ~Action() = default;
        virtual void Execute() = 0;
    };
};

#endif
