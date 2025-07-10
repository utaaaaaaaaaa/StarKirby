#include "Enemy.h"
#include <iostream>

Enemy::Enemy(sf::Sprite& sprite, float gravity) 
    : m_sprite(sprite), m_gravity(gravity) {
    }

void Enemy::checkCollisions(Background& bg){
    //===============checkGroundCollision==========================
    m_isGround = false;
    // m_speed.y = 0.5;
    //获取地面矩形和角色矩形
    std::vector<sf::FloatRect> groundRect =  bg.getGroundRects();
    sf::FloatRect EnemyBounds = m_sprite.getGlobalBounds();
    //添加1像素防止卡入地面
    EnemyBounds.top += 1;

    //遍历地面矩形容器，处理逻辑（核心使用intersects函数检查两个矩形是否相交）
    for(const auto& ground : groundRect) {
        //如果角色和地面接触
        if(EnemyBounds.intersects(ground)){
            //卡比竖直速度为0，坐标设置在地面上
            m_isGround = true;
            m_speed.y = 0.0;
            m_sprite.setPosition(m_sprite.getPosition().x, ground.top - EnemyBounds.height - 1);
            break;
        }
    }
    //================checkBarrierCollision=========================
    Barrier& barrier = bg.getBarrier();
    int collisionDir = barrier.checkCollisionDirection(EnemyBounds, m_speed);
    sf::FloatRect theOneBarrier = barrier.getTheOneBarrier();
    switch (collisionDir) {
        case 2: 
        case 4:
            m_isBlock = true;
            break;
        default:
            break;
    }
}

void Enemy::startBeingDevoured(){
    std::cout<<"==== Enemy start being devoured ===="<<std::endl;
    m_isBeingDevoured = true;
    m_devourClock.restart();
    m_speed = {m_speed.x/4,m_speed.y/4}; //被吞噬时速度变为原速度1/4
}

void Enemy::resetDevour(){
    std::cout<<"==== Enemy reset devour ===="<<std::endl;
    m_isBeingDevoured = false;
    m_speed = {m_speed.x*4,m_speed.y*4}; 
}

void Enemy::takeDevour(){
    std::cout<<"Enemy is being devoured "<<std::endl;
    
}

void Enemy::endBeingDevoured(){
    std::cout<<"==== Enemy end being devoured ===="<<std::endl;
    m_isBeingDevoured = false;
    m_health = 0;
    die(); //暂时用die函数替代

}