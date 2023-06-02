#include <src/renderer/renderer.hpp>

Renderer::Renderer(std::shared_ptr<GameState> gs) : gs_{gs}
{
}

void Renderer::Render(sf::RenderWindow &window)
{
    window.clear();

    for (auto drawable_obj : gs_->get_objects())
    {
        auto drawing = drawable_obj.second->Render();
        if (drawing)
            window.draw(*drawing);
    }

    window.display();
}
