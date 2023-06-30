#ifndef GAME_OVER_SCREEN
#define GAME_OVER_SCREEN

#include <src/renderer/screens/screen.hpp>
#include <src/game/game-state.hpp>
#include <src/renderer/soundplayer.hpp>
#include <src/ui/menu.hpp>


namespace renderer::screen
{
    class GameOverScreen : public Screen
    {
    public:
        GameOverScreen(std::shared_ptr<renderer::screen::ScreenManager> scr_mgr);
        ~GameOverScreen();

        void OnExit() override;
        void OnEnter() override;

        void Update(float) override;

    private:
        std::shared_ptr<Menu> menu_{nullptr};
    };

}

#endif
