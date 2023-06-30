#ifndef PC_CTRL_H
#define PC_CTRL_H

#include "src/controllers/controller.hpp"
#include "src/controllers/ievent-handler.hpp"
#include "src/vehicle/vehicle.hpp"

#include <SFML/Window/Event.hpp>

#include <memory>
class PcController : public Controller
{
public:
    explicit PcController(std::shared_ptr<Vehicle>);

private:
    void InitActions(std::shared_ptr<Vehicle>);
};

#endif
