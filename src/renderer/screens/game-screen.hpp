#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <src/renderer/screens/screen.hpp>
#include <src/game/game-state.hpp>
#include <src/renderer/soundplayer.hpp>
#include <src/vehicle/vehicle.hpp>
#include <src/controllers/pc-controller.hpp>
#include <src/asteroids/generator.hpp>
#include <src/ui/hud.hpp>

#include <memory>

#include <SFML/Window/Window.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace renderer::screen {
    class GameScreen : public Screen {
        public:
            GameScreen(std::shared_ptr<renderer::screen::ScreenManager> scr_mgr);
            ~GameScreen() = default;

            void Update(float) override;
            void OnEnter() override;
            void OnExit() override;

            void Init() const;

        private:
            std::shared_ptr<Vehicle> vehicle_{nullptr};
            std::shared_ptr<PcController> pc_controller_{nullptr};
            std::shared_ptr<Simulator> sim_{nullptr};
            std::shared_ptr<Generator> gen_{nullptr};
            std::shared_ptr<Generator> gen2_{nullptr};
            std::shared_ptr<HUD> hud_{nullptr};
    };
}

#endif
