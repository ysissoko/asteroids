#include "src/renderer/screens/game-over-screen.hpp"
#include "src/controllers/menu-controller.hpp"
namespace renderer::screen
{
    GameOverScreen::GameOverScreen(std::shared_ptr<renderer::screen::ScreenManager> scr_mgr) : Screen(scr_mgr)
    {
    }

    void GameOverScreen::OnExit()
    {
        spdlog::debug("on exit game over screen");
        scr_mgr_->get_game_state()->Reset();
    }

    void GameOverScreen::OnEnter()
    {
        spdlog::debug("on enter game over screen");
        menu_ = std::make_shared<Menu>(scr_mgr_);

        scr_mgr_->get_game_state()->AddUiObject(menu_);

        set_event_handler(std::make_shared<MenuController>(menu_->get_cursor()));
    }

    void GameOverScreen::Update(float elapsed) {

    }

    GameOverScreen::~GameOverScreen()
    {
    }
}
