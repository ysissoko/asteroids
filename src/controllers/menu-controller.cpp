#include <src/controllers/menu-controller.hpp>

#include <src/controllers/actions/cursor/move-action.hpp>
#include <src/controllers/actions/cursor/confirm-action.hpp>

using namespace actions::cursor;

MenuController::MenuController(std::shared_ptr<Cursor> cursor): Controller("menu-controller") {
    InitActions(cursor);
}

void MenuController::InitActions(std::shared_ptr<Cursor> cursor)
{
    AddKeyPressedAction(sf::Keyboard::Key::Up, std::make_shared<MoveAction>(cursor));
    AddKeyPressedAction(sf::Keyboard::Key::Down, std::make_shared<MoveAction>(cursor));
    AddKeyPressedAction(sf::Keyboard::Key::Space, std::make_shared<ConfirmAction>(cursor));
}
