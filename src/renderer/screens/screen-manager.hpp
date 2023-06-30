#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include <src/renderer/screens/screen.hpp>
#include <src/game/game-state.hpp>
#include <src/renderer/soundplayer.hpp>

#include <unordered_map>
#include <string_view>
#include <memory>
#include <sstream>

namespace renderer::screen {

    class ScreenNotFoundException : public std::exception {
        public:
        ScreenNotFoundException(const std::string_view& screen_name) : std::exception() { 
            std::stringstream ss;
            ss << "Screen not found. name: " << screen_name << "\n";
            msg_ = ss.str();
        }

        const char* what() const noexcept override {
            return "Screen not found";
        }

        private:
            std::string_view msg_;
    };

    class ScreenManager : public std::enable_shared_from_this<ScreenManager> {
        public:
            ScreenManager(std::shared_ptr<GameState> gs, std::shared_ptr<SoundPlayer> sp) :  gs_{gs}, sp_{sp} {}
            ~ScreenManager() = default;

            void AddScreen(std::string_view name, std::shared_ptr<Screen> screen) {
                screens_.try_emplace(name, screen); 
            }

            void SwitchScreen(const std::string_view& screen_name) {
                auto it = screens_.find(screen_name);
                if (current_screen_) current_screen_->OnExit();

                if (it != screens_.end()) current_screen_ = it->second;
                else throw ScreenNotFoundException(it->first);

                current_screen_->OnEnter();
            }

            std::shared_ptr<Screen> get_current_screen() { return current_screen_; }
            std::shared_ptr<GameState> get_game_state() { return gs_; }
            std::shared_ptr<SoundPlayer> get_sound_player() { return sp_; }
        private:
            std::unordered_map<std::string_view, std::shared_ptr<Screen>> screens_;
            std::shared_ptr<Screen> current_screen_{nullptr};

            std::shared_ptr<GameState> gs_{nullptr};
            std::shared_ptr<SoundPlayer> sp_{nullptr};
    };
}

#endif
