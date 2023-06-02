#ifndef PC_CTRL_H
#define PC_CTRL_H

#include <memory>

#include <SFML/Window/Event.hpp>

#include <src/controllers/controller.hpp>
#include <src/controllers/ievent-handler.hpp>
#include <src/vehicle/vehicle.hpp>

class PcController : public Controller, public IEventHandler
{
public:
    explicit PcController(std::shared_ptr<Vehicle>);
    virtual void HandleEvent(sf::Event &);

private:
    void HandleKeyPressed(sf::Keyboard::Key);
    void HandleKeyReleased(sf::Keyboard::Key);
    void InitActions(std::shared_ptr<Vehicle>);
};

#endif
