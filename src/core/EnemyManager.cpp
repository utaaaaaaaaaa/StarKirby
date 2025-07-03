#include "EnemyManager.h"
#include "const/Constants.h"

using namespace AnimationFrame;

EnemyManager::EnemyManager()
    :m_sparkEnemy(m_sprite) {
    //加载精灵纹理
    if (!m_texture.loadFromFile("assets/sparkEnemy.png")) {
        throw std::runtime_error("没有找到sparkEnemy素材，敌人创建失败");
    }
    //加载死亡动画纹理
    if (!m_deathTexture.loadFromFile("assets/deadAnimation.png")) {
        throw std::runtime_error("没有找到deadAnimation素材，敌人创建失败");
    }
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sparkEnemyAnimationRects[0]);
    m_sprite.setPosition(250, 150 + 56 - 25); 
    //设置动画参数
    sparkEnemyAnimation.setFrames(sparkEnemyAnimationRects);
    sparkEnemyAnimation.play(0.12f);
    enemyDeadAnimation.setFrames(enemyDeadAnimationRects);
    enemyDeadAnimation.play(0.1f,false);
    //添加所有敌人到统一容器
    addEnemy(m_sparkEnemy);
}


void EnemyManager::addEnemy(SparkEnemy& enemy){
    m_enemies.push_back(std::make_shared<SparkEnemy>(enemy));
};

void EnemyManager::updateAll(float deltaTime, Background& bg){
    //移除标记为销毁的敌人（先将应该被销毁的敌人移到末尾，拿到尾部迭代器后删除
    auto it = std::remove_if(
        m_enemies.begin(), 
        m_enemies.end(),
        [](const std::shared_ptr<Enemy>& enemy) {
            return enemy->shouldDestroy();
        }
    );
    m_enemies.erase(it, m_enemies.end());
    //更新存活的敌人
    for(auto& enemy : m_enemies){
        updateAnimation(deltaTime,enemy);
        enemy->update(deltaTime,bg);
    }
};

void EnemyManager::updateAnimation(float deltaTime,std::shared_ptr<Enemy> enemy){
    if(enemy->isAlive()){
        enemy->getSprite().setTextureRect(sparkEnemyAnimation.update(deltaTime));
    }else {
        //切换死亡纹理
        if(enemy->shouldChangeTexture()){
            enemy->getSprite().setTexture(m_deathTexture);
            enemy->setShouldChangeTexture(false);
        }
        enemy->setAttack(0);
        //播放死亡动画
        enemy->getSprite().setTextureRect(enemyDeadAnimation.update(deltaTime));
        if (enemy->getClock().getElapsedTime().asSeconds() > enemy->getDeathDuration()) {
            enemy->setShouldDestroy(true); //动画结束后，标记为可销毁
        }
    }
}

void EnemyManager::drawAll(sf::RenderWindow& window){
    window.draw(m_sparkEnemy.getSprite());
};

void EnemyManager::clear(){
};