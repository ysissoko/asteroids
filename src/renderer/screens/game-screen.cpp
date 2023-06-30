#include <src/renderer/screens/game-screen.hpp>
#include <src/game/game.hpp>
namespace renderer::screen
{
    GameScreen::GameScreen(std::shared_ptr<renderer::screen::ScreenManager> scr_mgr) : Screen(scr_mgr)
    {
    }

    void GameScreen::OnEnter() {
        spdlog::debug("on enter game screen");
        hud_ = std::make_shared<HUD>();

        sim_ = std::make_shared<Simulator>(scr_mgr_->get_game_state());

        vehicle_ = std::make_shared<Vehicle>(std::string_view("ship"), scr_mgr_->get_game_state(), scr_mgr_->get_sound_player(), hud_, scr_mgr_);
        pc_controller_ = std::make_shared<PcController>(vehicle_);

        gen_ = std::make_shared<Generator>(scr_mgr_->get_game_state(), Game::config["generators"][0], hud_, scr_mgr_->get_sound_player());
        gen2_ = std::make_shared<Generator>(scr_mgr_->get_game_state(), Game::config["generators"][1], hud_, scr_mgr_->get_sound_player());

        scr_mgr_->get_game_state()->AddObject(vehicle_);
        scr_mgr_->get_game_state()->AddUiObject(hud_);

        set_event_handler(pc_controller_);
    }

    void GameScreen::OnExit() {
        spdlog::debug("on exit game screen");
        scr_mgr_->get_game_state()->Reset();
    }

    void GameScreen::Update(float elapsed) {
        sim_->Update(elapsed);
        gen_->Update(elapsed);
        gen2_->Update(elapsed);
    }
}
