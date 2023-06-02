#ifndef SIM_H
#define SIM_H

#include <string>
#include <memory>
class Simulator;

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
