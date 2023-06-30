#include <src/renderer/renderer.hpp>

Renderer::Renderer(std::shared_ptr<GameState> gs) : gs_{gs}
{
}

void Renderer::Render(sf::RenderWindow &window)
{
    window.clear();

    for (auto drawable_obj : gs_->get_objects())
    {
        auto drawing = drawable_obj.second->get_shape();
        if (drawing)
            window.draw(*drawing);
    }

    for (auto ui_object : gs_->get_ui_objects())
    {
        for (auto drawing : ui_object->get_drawings())
        {
            if (drawing)
                window.draw(*drawing);
        }

        for (auto child : ui_object->get_childs())
        {
            for (auto drawing : child->get_drawings())
            {
                if (drawing)
                    window.draw(*drawing);
            }
        }
    }

    window.display();
}
