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
    void reset();
    void walk(Background& bg);
    void fall(float deltatime, Background& bg);
    void jump();
    void startFly(float deltatime, Background& bg);
    void enterFlyModel();
    void fly(float deltatime, Background& bg);
    void endFly();
    void attack();
    void attackFly();
    void reborn();
    void devour();
    void change();
    void addScore(int points);
    void minusScore(int points);
    void loadTexture();
    void checkGroundCollision(Background& bg);
    void checkBarrierCollision(Barrier& barrier);
    void checkAppleCollision(std::vector<Apple>& m_apples);
    void checkEnemyCollision(std::vector<std::shared_ptr<Enemy>>& enemies);
    void checkAttackHit(std::vector<std::shared_ptr<Enemy>>& enemies);
    void checkDevourHit(std::vector<std::shared_ptr<Enemy>>& enemies);
    void updateInvincibility();
    void updateAttackState();
    sf::Vector2f getSpeed(){return m_speed;};
    bool getIsGround(){return m_isGround;};
    bool getIsAttacking(){return m_isAttacking;};
    bool getCanDoDamage(){return m_canDoDamge;};
    bool getIsDevouring(){return m_isDevouring;}
    sf::Sprite getAttackFlyParticle(){return m_attackFlyParticles;}
    sf::Sprite getDevourParticle(){return m_devourParticles;}
    sf::Clock getClock(){return m_deathClock;}
    sf::Clock getStartFlyClock(){return m_startFlyClock;}
    sf::Clock getAttackClock(){return m_attackClock;}
    float getStartFlyCD(){return m_startFlyCD;}
    float getStartFlyDuration(){return m_startFlyDuration;}
    float getAttackDuration(){return m_attackDuration;}
    float getDeathDuration(){return m_deathDuration;}
    sf::Vector2f getPos(){return m_pos;}
    sf::FloatRect getBounds(){return m_bounds;}
    bool getStartFly(){return m_startFly;}
    bool getChangable(){return m_isChangable;}
    int getScore(){return m_score;}
    int getHP(){return m_health;}
    int getChangeType(){return m_changeType;}
    bool isFlying(){return m_isFlying;}
    bool isAlive(){return m_health>0;};
    bool isDying(){return m_isDying;}
    bool isDefault(){return m_isDefault;}
    void setSprite(sf::Sprite& player);
    void setSpeed(sf::Vector2f speed);
    void setIsDying(bool isDying){m_isDying = isDying;}
    void setIsFlying(bool isFlying){m_isFlying = isFlying;}
    void setStartFly(bool startFly){m_startFly = startFly;}
    void setStartFlyCD(float cd){m_startFlyCD = cd;}
    void setIsDevouring(bool isDevouring){m_isDevouring = isDevouring;}
    void setMyChangetype(int type){m_changeType = type;}

    void die(){
        // m_isDying = true;
        // std::cout<<"m_isDying: "<<m_isDying<<std::endl;
        m_deathClock.restart();
    }
private:
    sf::Sprite& m_kirby;
    sf::Texture m_normalKirbyTexture;
    //变身贴图
    sf::Texture m_sparkKirbyTexture;
    //粒子
    sf::Sprite m_attackFlyParticles; //飞行攻击粒子
    sf::Texture m_attackFlyParticlesTexture;
    
    sf::Sprite m_devourParticles; //吞噬粒子
    sf::Texture m_devourParticlesTexture;

    sf::Vector2f m_speed = {0.25,0.15};
    int m_health;
    int m_score = 0;
    //死亡相关参数
    bool m_shouldDestroy = false; //是否要被销毁
    bool m_isDying = false;    //是否正在播放死亡动画
    sf::Clock m_deathClock;    //死亡动画计时器
    float m_deathDuration = 0.7f; //死亡动画持续时间

    bool m_faceRight = true;
    //起飞相关参数
    bool m_isFlying = false;
    bool m_startFly = false;
    sf::Clock m_startFlyClock;
    float m_startFlyCD = 0.0f;
    float m_startFlyDuration = 0.3f;

    bool m_isGround = false;
    bool m_isNoHarm = false;
    sf::Clock m_invincibilityClock; //无敌时间计时器
    float m_invincibilityDuration = 2.0f; //无敌状态持续时间
    float m_gravity = 0.8f;
    //攻击相关属性
    bool m_isAttacking = false;
    bool m_canDoDamge = false;
    sf::Clock m_attackClock;
    float m_attackDuration = 0.3f; //攻击动画持续时间
    float m_attackRange = 10.0f; //攻击范围
    int m_attackDamage = 1;   //攻击伤害
    int m_attackFlyDamage = 3;   //飞行攻击伤害
    sf::FloatRect m_bounds;
    sf::Vector2f m_pos;
    //吞噬相关属性
    bool m_isDevouring = false;
    bool m_isDefault = true;
    bool m_isChangable = false;
    int m_changeType;

};

#endif