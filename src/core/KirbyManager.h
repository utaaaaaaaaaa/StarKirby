#ifndef Kirby_Manage_H
#define Kirby_Manage_H

#include <SFML/Graphics.hpp>
#include <stdexcept>

class KirbyManager {
public:
    KirbyManager();
    sf::Sprite& getKirby();

private:
    sf::Texture m_kirbyTexture;
    sf::Sprite m_kirby;
};

#endif