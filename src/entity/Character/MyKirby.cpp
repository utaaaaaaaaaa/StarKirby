#include "MyKirby.h"
#include <iostream>
#include "entity/Enemy/Enemy.h"

MyKirby::MyKirby(sf::Sprite& player) 
    : m_kirby(player) {
        this->m_health = 5;
        this->m_attack = 3;
    }

MyKirby::MyKirby(sf::Sprite& player, sf::Vector2f speed) 
    : m_kirby(player), m_speed(speed) {
        this->m_health = 5;
        this->m_attack = 3;
    }

void MyKirby::update(float deltaTime, Background& bg) {
    //障碍物碰撞检测
    checkBarrierCollision(bg.getBarrier());
    //卡比水平方向移动
    m_kirby.move(m_speed.x,0);
}

void MyKirby::walk(Background& bg) {

}

//不由按键驱动的一直执行的重力掉落
void MyKirby::fall(float deltatime, Background& bg) {
    //必须先检查是否在地面上，不然直接掉出屏幕！！
    checkGroundCollision(bg);
    checkBarrierCollision(bg.getBarrier());
    if(!m_isGround) {
        m_speed.y += m_gravity * deltatime; 
        m_kirby.move(0,m_speed.y);
    } 
}

void MyKirby::jump() {

}

void MyKirby::checkGroundCollision(Background& bg) {
    m_isGround = false;
    // m_speed.y = 0.5;
    //获取地面矩形和角色矩形
    std::vector<sf::FloatRect> groundRect =  bg.getGroundRects();
    sf::FloatRect kirbyBounds = m_kirby.getGlobalBounds();
    //添加1像素防止卡入地面
    kirbyBounds.top += 1;

    //遍历地面矩形容器，处理逻辑（核心使用intersects函数检查两个矩形是否相交）
    for(const auto& ground : groundRect) {
        //如果角色和地面接触
        if(kirbyBounds.intersects(ground)){
            //卡比竖直速度为0，坐标设置在地面上
            m_isGround = true;
            m_speed.y = 0.0;
            m_kirby.setPosition(m_kirby.getPosition().x, ground.top - kirbyBounds.height - 1);
            break;
        }
    }
}

void MyKirby::checkBarrierCollision(Barrier& barrier){
    sf::FloatRect kirbyRect = m_kirby.getGlobalBounds();
    int collisionDir = barrier.checkCollisionDirection(kirbyRect, m_speed);
    sf::FloatRect theOneBarrier = barrier.getTheOneBarrier();
    switch (collisionDir) {
        case 0:
            break;
        case 1: //站在障碍物上
            m_speed.y = 0;
            m_isGround = true;
            //将角色精确放置在障碍物顶部
            m_kirby.setPosition(m_kirby.getPosition().x, 
                               theOneBarrier.top - kirbyRect.height);
            break;
            
        case 2: //卡比左面碰撞(由于帧动画左边多出2像素，减去两像素重新检查一次碰撞)
            //kirbyRect.left += 4;
            //if(barrier.checkCollisionDirection(kirbyRect,m_speed)!=2)break;
            if(m_speed.x < 0){
                m_speed.x = 0;
            }
            break;
        case 3: //顶部碰撞
            m_speed.y = -m_speed.y;
            break;
        case 4: //卡比右面碰撞
            if(m_speed.x > 0){
                m_speed.x = 0;
            }
            break;
    }
}

void MyKirby::checkEnemyCollision(std::vector<std::shared_ptr<Enemy>>& enemies){
    sf::FloatRect kirbyBounds = m_kirby.getGlobalBounds();
    for(auto& enemy : enemies){
        sf::FloatRect enemyBounds = enemy->getSprite().getGlobalBounds();
        if (kirbyBounds.intersects(enemyBounds)) {
            //普通碰撞(如果没有无敌状态)
            if(!m_isNoHarm){
                m_health -= enemy->getAttack();
                std::cout<<"HP: "<<m_health<<std::endl;
                //设置为无敌并重置计时器
                m_isNoHarm = true;
                m_invincibilityClock.restart();
                break;
            }
        }
    }
}

void MyKirby::updateInvincibility(){
    if (m_isNoHarm) {
        if (m_invincibilityClock.getElapsedTime().asSeconds() >= m_invincibilityDuration) {
            m_isNoHarm = false;
        }
    }
}

void MyKirby::setSprite(sf::Sprite& player) {
    m_kirby = player;
}

void MyKirby::setSpeed(sf::Vector2f speed) {
    m_speed = speed;
}