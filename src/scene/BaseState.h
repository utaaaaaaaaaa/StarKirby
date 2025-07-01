#ifndef BASE_STATE_H
#define BASE_STATE_H

#include <SFML/Graphics.hpp>

//场景基类
class BaseState {
public:
    sf::View& GetView(){ return m_view; }

protected:
    sf::View m_view;
};

#endif