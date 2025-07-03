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
    void attack();
    void checkGroundCollision(Background& bg);
    void checkBarrierCollision(Barrier& barrier);
    void checkEnemyCollision(std::vector<std::shared_ptr<Enemy>>& enemies);
    void checkAttackHit(std::vector<std::shared_ptr<Enemy>>& enemies);
    void updateInvincibility();
    void updateAttackState();
    sf::Vector2f getSpeed(){return m_speed;};
    bool getIsGround(){return m_isGround;};
    bool getIsAttacking(){return m_isAttacking;};
    bool getCanDoDamage(){return m_canDoDamge;};
    void setSprite(sf::Sprite& player);
    void setSpeed(sf::Vector2f speed);
private:
    sf::Sprite& m_kirby;
    sf::Vector2f m_speed = {0.25,0.15};
    int m_health;
    bool m_faceRight = true;
    bool m_isGround = false;
    bool m_isNoHarm = false;
    sf::Clock m_invincibilityClock; //无敌时间计时器
    float m_invincibilityDuration = 2.0f; //无敌状态持续时间
    const float m_gravity = 0.8f;
    //攻击相关属性
    bool m_isAttacking = false;
    bool m_canDoDamge = false;
    sf::Clock m_attackClock;
    float m_attackDuration = 0.3f; //攻击动画持续时间
    float m_attackRange = 10.0f; //攻击范围
    int m_attackDamage = 1;   //攻击伤害
};

#endif