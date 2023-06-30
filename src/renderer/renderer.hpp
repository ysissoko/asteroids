#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include <src/game/game-state.hpp>
class Renderer
{
public:
    explicit Renderer(std::shared_ptr<GameState>);
    void Render(sf::RenderWindow &);

private:
    std::shared_ptr<GameState> gs_{nullptr};
};

#endif
