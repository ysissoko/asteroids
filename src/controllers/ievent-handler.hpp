#ifndef EVT_HDL_H
#define EVT_HDL_H

#include <SFML/Window/Event.hpp>

class IEventHandler
{
public:
    virtual void HandleEvent(const sf::Event &) = 0;
};

#endif
