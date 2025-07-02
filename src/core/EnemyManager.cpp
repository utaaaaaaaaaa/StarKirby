#include "EnemyManager.h"

EnemyManager::EnemyManager()
    :m_sparkEnemy(m_sprite) {
    //加载精灵纹理
    if (!m_texture.loadFromFile("assets/sparkEnemy1.png")) {
        throw std::runtime_error("没有找到sparkEnemy素材，敌人创建失败");
    }
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(290, 150 + 56 - 25); 
}

SparkEnemy& EnemyManager::getSparkEnemy(){
    return m_sparkEnemy;
}

void EnemyManager::addEnemy(const Enemy& enemy){
};

void EnemyManager::updateAll(float deltaTime, Background& bg){
    m_sparkEnemy.update(deltaTime,bg);
};

void EnemyManager::drawAll(sf::RenderWindow& window){
    window.draw(m_sparkEnemy.getSprite());
};

void EnemyManager::clear(){
};