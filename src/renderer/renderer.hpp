#ifndef RENDERER_H
#define RENDERER_H

#include "src/game/game-state.hpp"

#include <SFML/Graphics.hpp>
class Renderer
{
public:
    explicit Renderer(std::shared_ptr<GameState>);
    void Render(sf::RenderWindow &);

private:
    std::shared_ptr<GameState> gs_{nullptr};
};

#endif
