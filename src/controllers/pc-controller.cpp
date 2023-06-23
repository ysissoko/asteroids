#include <spdlog/spdlog.h>

#include <src/controllers/pc-controller.hpp>
#include <src/controllers/actions/vehicle/accelerate.hpp>
#include <src/controllers/actions/vehicle/deccelerate.hpp>
#include <src/controllers/actions/vehicle/rotate-cw.hpp>
#include <src/controllers/actions/vehicle/rotate-ccw.hpp>
#include <src/controllers/actions/vehicle/shoot.hpp>
#include <src/controllers/actions/vehicle/stop-shoot.hpp>
#include <src/controllers/actions/vehicle/stop-rotate.hpp>

using namespace actions::vehicle;

PcController::PcController(std::shared_ptr<Vehicle> vehicle) : Controller("pc-controller")
{
    InitActions(vehicle);
}

void PcController::InitActions(std::shared_ptr<Vehicle> vehicle)
{
    AddKeyPressedAction(sf::Keyboard::Key::Up, std::make_shared<AccelerateAction>(vehicle));
    // AddKeyPressedAction(sf::Keyboard::Key::Down, std::make_shared<DeccelerateAction>(vehicle));
    AddKeyPressedAction(sf::Keyboard::Key::Left, std::make_shared<RotateCCWAction>(vehicle));
    AddKeyPressedAction(sf::Keyboard::Key::Right, std::make_shared<RotateCWAction>(vehicle));
    AddKeyPressedAction(sf::Keyboard::Key::Space, std::make_shared<ShootAction>(vehicle));

    AddKeyReleasedAction(sf::Keyboard::Key::Up, std::make_shared<DeccelerateAction>(vehicle));
    AddKeyReleasedAction(sf::Keyboard::Key::Space, std::make_shared<StopShootAction>(vehicle));
    AddKeyReleasedAction(sf::Keyboard::Key::Left, std::make_shared<StopRotateAction>(vehicle));
    AddKeyReleasedAction(sf::Keyboard::Key::Right, std::make_shared<StopRotateAction>(vehicle));
}

void PcController::HandleKeyPressed(sf::Keyboard::Key key)
{
    auto it_key_act = GetKeyboardPressAction(key);
    if (it_key_act != get_kb_press_actions().end())
    {
        it_key_act->second->Execute();
    }
}

void PcController::HandleKeyReleased(sf::Keyboard::Key key)
{
    auto it_key_act = GetKeyboardReleaseAction(key);
    if (it_key_act != get_kb_release_actions().end())
    {
        it_key_act->second->Execute();
    }
}

void PcController::HandleEvent(sf::Event &evt)
{
    if (evt.type == sf::Event::KeyPressed)
    {
        HandleKeyPressed(evt.key.code);
    }
    else if (evt.type == sf::Event::KeyReleased)
    {
        HandleKeyReleased(evt.key.code);
    }
}
