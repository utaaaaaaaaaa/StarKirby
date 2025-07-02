#ifndef MY_KIRBY_H
#define MY_KIRBY_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <scene/Background.h>
#include <scene/Barrier.h>
#include <entity/Enemy/Enemy.h>

class MyKirby {
public: 
    MyKirby(sf::Sprite& player);
    MyKirby(sf::Sprite& player, sf::Vector2f speed);
    virtual ~MyKirby() = default;
    void update(float deltaTime, Background& bg);
    void walk(Background& bg);
    void fall(float deltatime, Background& bg);
    void jump();
    void checkGroundCollision(Background& bg);
    void checkBarrierCollision(Barrier& barrier);
    void checkEnemyCollision(std::vector<std::shared_ptr<Enemy>>& enemies);
    void updateInvincibility();
    sf::Vector2f getSpeed(){return m_speed;};
    bool getIsGround(){return m_isGround;};
    void setSprite(sf::Sprite& player);
    void setSpeed(sf::Vector2f speed);
private:
    sf::Sprite& m_kirby;
    sf::Vector2f m_speed = {0.25,0.15};
    int m_health;
    int m_attack;
    bool m_isGround = false;
    bool m_isNoHarm = false;
    sf::Clock m_invincibilityClock; //无敌时间计时器
    float m_invincibilityDuration = 2.0f; //无敌状态持续时间
    const float m_gravity = 0.8f;
};

#endif