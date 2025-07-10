#include "EnemyManager.h"
#include "const/Constants.h"

using namespace AnimationFrame;

EnemyManager::EnemyManager(){
    loadTextures();
    //加载死亡动画纹理
    if (!m_deathTexture.loadFromFile("assets/deadAnimation.png")) {
        throw std::runtime_error("没有找到deadAnimation素材，敌人创建失败");
    }
    initEnemy();
    //设置动画参数
    enemyDeadAnimation.setFrames(enemyDeadAnimationRects);
    enemyDeadAnimation.play(0.1f,false);
}

void EnemyManager::initEnemy(){
    spawnEnemy("spark",250, 150 + 56 - 25);
    spawnEnemy("spark",620, 150 + 56 - 25);
    spawnEnemy("spark",1130, 130 + 56 - 25);
    spawnEnemy("fly",780, 15 + 56 - 25);
    spawnEnemy("fly",1342, 35 + 56 - 25);
    spawnEnemy("plant",1394, 133 + 56 - 25);
    spawnEnemy("plant",832, 85 + 56 - 25);
}

void EnemyManager::spawnEnemy(const std::string& type, float x, float y) {
    auto sprite = std::make_shared<sf::Sprite>();
    sprite->setTexture(m_textures[type]);
    sprite->setPosition(x, y);

    if (type == "spark") {
        auto enemy = std::make_shared<SparkEnemy>(sprite);
        m_enemies.push_back(enemy);
    } 
    else if(type == "fly") {
        auto enemy = std::make_shared<FlyEnemy>(sprite);
        m_enemies.push_back(enemy);
    }
    else if(type == "plant"){
        auto enemy = std::make_shared<PlantEnemy>(sprite);
        m_enemies.push_back(enemy);
    }
    //...
}

void EnemyManager::loadTextures() {
    if (!m_textures["spark"].loadFromFile("assets/sparkEnemy.png")) {
        throw std::runtime_error("没有找到sparkEnemy素材，敌人创建失败");
    }
    if (!m_textures["fly"].loadFromFile("assets/flyingEnemy.png")) {
        throw std::runtime_error("没有找到flyingEnemy素材，敌人创建失败");
    }
    if (!m_textures["plant"].loadFromFile("assets/plantEnemy.png")) {
        throw std::runtime_error("没有找到plantEnemy素材，敌人创建失败");
    }
    plantEnemyAnimation.setFrames(plantEnemyAnimationRects);
    plantEnemyAnimation.play(0.2f);
    flyEnemyAnimation.setFrames(flyEnemyAnimationRects);
    flyEnemyAnimation.play(0.12f);
    sparkEnemyAnimation.setFrames(sparkEnemyAnimationRects);
    sparkEnemyAnimation.play(0.12f);
}

void EnemyManager::addEnemy(SparkEnemy& enemy){
    
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
        switch (enemy->getMyType()) 
        {
        case 1: //sparkenemy
            enemy->getSprite().setTextureRect(sparkEnemyAnimation.update(deltaTime));
            break;
        case 2: //flyenemy
            enemy->getSprite().setTextureRect(flyEnemyAnimation.update(deltaTime));
            break;
        case 3: //plantenemy
            enemy->getSprite().setTextureRect(plantEnemyAnimation.update(deltaTime));
            break;
        default:
            break;
        }
    }else {
        //切换死亡纹理
        if(enemy->shouldChangeTexture()){
            //设置死亡动画起始位置
            enemy->setDeathCenter(sf::Vector2f(enemy->getSprite().getPosition()));
            //设置纹理
            enemy->getSprite().setTexture(m_deathTexture);
            enemy->setShouldChangeTexture(false);
        }
        enemy->setAttack(0);
        //播放死亡动画（根据中心点偏移）
        sf::IntRect& currentRect = enemyDeadAnimation.update(deltaTime);
        sf::FloatRect bounds = enemy->getBeforeDeathBounds();
        sf::Vector2f pos = enemy->getDeathCenter();
        float deltaX = (currentRect.width - bounds.width) / 2.0;
        float deltaY = (currentRect.height - bounds.height) / 2.0; 
        enemy->getSprite().setTextureRect(currentRect);
        enemy->getSprite().setPosition(pos.x - deltaX, pos.y - deltaY);
        //如果动画播放完成，标记为可以销毁敌人
        if (enemy->getClock().getElapsedTime().asSeconds() > enemy->getDeathDuration()) {
            enemy->setShouldDestroy(true); 
        }
    }
}

void EnemyManager::drawAll(sf::RenderWindow& window){
    for(auto& enemy : m_enemies){
        window.draw(enemy->getSprite());
    }
};

void EnemyManager::clear(){
    //清空敌人容器
    m_enemies.clear();

    //重新生成初始敌人
    initEnemy();
};