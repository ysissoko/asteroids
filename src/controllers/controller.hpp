#ifndef CTRL_H
#define CTRL_H

#include "src/controllers/actions/action.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <unordered_map>
#include <string>
#include <memory>

class Controller
{
public:
    explicit Controller(const std::string &);
    void AddKeyPressedAction(sf::Keyboard::Key key, std::shared_ptr<actions::Action> action) { kb_press_actions_.emplace(key, action); }
    void AddKeyReleasedAction(sf::Keyboard::Key key, std::shared_ptr<actions::Action> action) { kb_release_actions_.emplace(key, action); }

    std::unordered_map<sf::Keyboard::Key, std::shared_ptr<actions::Action>>::const_iterator GetKeyboardPressAction(sf::Keyboard::Key key) const { return kb_press_actions_.find(key); }
    std::unordered_map<sf::Keyboard::Key, std::shared_ptr<actions::Action>>::const_iterator GetKeyboardReleaseAction(sf::Keyboard::Key key) const { return kb_release_actions_.find(key); }

    std::unordered_map<sf::Keyboard::Key, std::shared_ptr<actions::Action>> get_kb_press_actions() { return kb_press_actions_; }
    std::unordered_map<sf::Keyboard::Key, std::shared_ptr<actions::Action>> get_kb_release_actions() { return kb_release_actions_; }
    
    void HandleKeyPressed(sf::Keyboard::Key);
    void HandleKeyReleased(sf::Keyboard::Key);
    void HandleEvent(const sf::Event&);

private:
    std::string name_;
    std::unordered_map<sf::Keyboard::Key, std::shared_ptr<actions::Action>> kb_press_actions_;
    std::unordered_map<sf::Keyboard::Key, std::shared_ptr<actions::Action>> kb_release_actions_;
};

#endif
