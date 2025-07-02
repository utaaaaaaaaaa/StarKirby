#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <entity/Character/MyKirby.h>

class Enemy {
public:
    Enemy(sf::Sprite& sprite, float gravity = 0.8f);
    virtual ~Enemy() = default;
    
    virtual void update(float deltaTime, Background& bg) = 0;
    virtual void takeDamage(int amount) = 0;
    
    //复用卡比的检测方法，并且地面和障碍物一起检测
    void checkCollisions(Background& bg);
    
    // 公共属性
    void setSpeed(sf::Vector2f speed){
        m_speed = speed;
        temp_enemy.setSpeed(speed);
    }
    void setHealth(int health){m_health = health;}
    sf::Vector2f getSpeed(){return m_speed;}
    sf::Sprite& getSprite() { return m_sprite; }
    bool isAlive() { return m_health > 0; }

protected:
    sf::Sprite& m_sprite;
    sf::Vector2f m_speed;
    int m_health;
    float m_gravity;
    bool m_isGround;
    bool m_isBlock = false;

private:
    MyKirby temp_enemy;
};

#endif