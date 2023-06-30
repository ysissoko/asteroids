#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>
#include <src/controllers/controller.hpp>

namespace renderer::screen {
    class ScreenManager;
    
    class Screen {
        public:
            Screen(std::shared_ptr<ScreenManager> scr_mgr) : scr_mgr_(scr_mgr) { }
            virtual ~Screen() = default;
            virtual void Update(float) = 0;

            void HandleEvent(const sf::Event &evt) { 
                if (controller_) controller_->HandleEvent(evt); 
            };

            virtual void OnExit() = 0;
            virtual void OnEnter() = 0;

            void set_event_handler(std::shared_ptr<Controller> controller) { controller_ = controller; }
        private:
            std::shared_ptr<Controller> controller_;
        protected:
            std::shared_ptr<ScreenManager> scr_mgr_{nullptr};
    };
}

#endif
