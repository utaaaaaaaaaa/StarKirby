#ifndef MY_KIRBY_H
#define MY_KIRBY_H

#include <SFML/Graphics.hpp>
#include <scene/Background.h>
#include <scene/Barrier.h>

class MyKirby {
public: 
    MyKirby(sf::Sprite& player);
    MyKirby(sf::Sprite& player, sf::Vector2f speed);
    virtual ~MyKirby() = default;
    void update(Background& bg);
    void walk(Background& bg);
    void fall(float deltatime, Background& bg);
    void jump();
    void checkGroundCollision(Background& bg);
    void checkBarrierCollision(Barrier& barrier);
    sf::Vector2f getSpeed(){return m_speed;};
    bool getIsGround(){return m_isGround;};
    void setSprite(sf::Sprite& player);
    void setSpeed(sf::Vector2f speed);
private:
    sf::Sprite& m_kirby;
    sf::Vector2f m_speed = {0.25,0.15};
    bool m_isGround = false;
    const float m_gravity = 0.8f;
};

#endif