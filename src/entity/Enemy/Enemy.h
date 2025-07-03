#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <scene/Background.h>
#include <animation/Animation.h>
#include <const/Constants.h>

class Enemy {
public:
    Enemy(sf::Sprite& sprite, float gravity = 0.8f);
    virtual ~Enemy() = default;
    
    virtual void update(float deltaTime, Background& bg) = 0;
    
    void takeDamage(int amount){
        m_health -= amount;
        std::cout<<"Enemy-HP: "<<m_health<<std::endl;
        if (m_health<=0){
            die();
            std::cout<<"die--------"<<std::endl;
        }       
    };
    
    //复用卡比的检测方法，并且地面和障碍物一起检测
    //实战结果复用方法会出循环引用的问题，单独实现
    void checkCollisions(Background& bg);
    
    // 公共属性
    void setSpeed(sf::Vector2f speed){m_speed = speed;}
    void setHealth(int health){m_health = health;}
    void setAttack(int attack){m_attack = attack;}
    void setShouldDestroy(bool shouldDestroy){m_shouldDestroy = shouldDestroy;}
    void setShouldChangeTexture(bool shouldChange){m_shouldChangeTexture = shouldChange;}
    sf::Vector2f getSpeed(){return m_speed;}
    sf::Sprite& getSprite() { return m_sprite; }
    int getAttack(){return m_attack;}
    sf::Clock getClock(){return m_deathClock;}
    float getDeathDuration(){return m_deathDuration;}
    bool isAlive() { return m_health > 0; }
    bool isDying(){return m_isDying;}
    bool shouldDestroy(){return m_shouldDestroy;}
    bool shouldChangeTexture(){return m_shouldChangeTexture;}

protected:
    void die(){
        m_isDying = true;
        m_shouldChangeTexture = true;
        std::cout<<"m_isDying: "<<m_isDying<<std::endl;
        m_deathClock.restart();
    }

    sf::Sprite& m_sprite;
    sf::Vector2f m_speed;
    int m_health;
    bool m_shouldDestroy = false; //是否要被销毁
    bool m_isDying = false;    //是否正在播放死亡动画
    bool m_shouldChangeTexture = true; //是否更换为死亡动画纹理
    sf::Clock m_deathClock;    //死亡动画计时器
    float m_deathDuration = 0.8f; //死亡动画持续时间
    int m_attack;
    float m_gravity;
    bool m_isGround;
    bool m_isBlock = false;

// private:
//     MyKirby temp_enemy;
};

#endif