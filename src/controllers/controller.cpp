#include "src/controllers/controller.hpp"

Controller::Controller(const std::string &name) : name_{name}
{
}

void Controller::HandleKeyPressed(sf::Keyboard::Key key)
{
    auto it_key_act = GetKeyboardPressAction(key);
    if (it_key_act != get_kb_press_actions().end())
    {
        it_key_act->second->Execute();
    }
}

void Controller::HandleKeyReleased(sf::Keyboard::Key key)
{
    auto it_key_act = GetKeyboardReleaseAction(key);
    if (it_key_act != get_kb_release_actions().end())
    {
        it_key_act->second->Execute();
    }
}

void Controller::HandleEvent(const sf::Event &evt)
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
