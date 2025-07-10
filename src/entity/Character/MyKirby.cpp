#include "MyKirby.h"
#include <iostream>
#include "entity/Enemy/Enemy.h"

MyKirby::MyKirby(sf::Sprite& player) 
    : m_kirby(player) {
        this->m_health = 5;
        loadTexture();
    }

MyKirby::MyKirby(sf::Sprite& player, sf::Vector2f speed) 
    : m_kirby(player), m_speed(speed) {
        this->m_health = 5;
        loadTexture();
    }

void MyKirby::loadTexture(){
    // 加载卡比精灵纹理
    if (!m_normalKirbyTexture.loadFromFile("assets/Kirby_Normal.png")) {
        throw std::runtime_error("没有找到卡比素材，角色创建失败");
    }
    // 飞行攻击精灵纹理
    if (!m_attackFlyParticlesTexture.loadFromFile("assets/kirbySpit.png")) {
        throw std::runtime_error("没有找到卡比素材，角色创建失败");
    }
    // 吞噬精灵纹理
    if (!m_devourParticlesTexture.loadFromFile("assets/AirSuck2.png")) {
        throw std::runtime_error("没有找到卡比素材，角色创建失败");
    }
    // 闪电卡比精灵纹理
    if (!m_sparkKirbyTexture.loadFromFile("assets/sparkKirby.png")) {
        throw std::runtime_error("没有找到卡比素材，角色创建失败");
    }
    m_devourParticles.setTexture(m_devourParticlesTexture);
    m_attackFlyParticles.setTexture(m_attackFlyParticlesTexture);
}

void MyKirby::update(float deltaTime, Background& bg) {
    //障碍物碰撞检测
    checkBarrierCollision(bg.getBarrier());
    //卡比水平方向移动
    m_kirby.move(m_speed.x,0);
    //根据速度方向改变卡比朝向
    m_faceRight = m_speed.x >=0 ? true : false;
}

void MyKirby::reset(){
    m_health = 5; 
    m_score = 0;
    m_attackDamage = 1;   //攻击伤害
    m_attackFlyDamage = 3;   //飞行攻击伤害
    m_isDying = false;
    m_shouldDestroy = false; 
    m_faceRight = true;
    m_isFlying = false;
    m_startFly = false;
    m_isGround = false;
    m_isNoHarm = false;
    m_gravity = 0.8f;
    m_isAttacking = false;
    m_canDoDamge = false;
    m_isDevouring = false;
    m_isDefault = true;
    m_isChangable = false;
    m_changeType = 0;
    //重置贴图
    m_kirby.setTexture(m_normalKirbyTexture);
    //初始化贴图区域
    m_kirby.setTextureRect(sf::IntRect(2, 98, 25, 20)); 
    m_kirby.setPosition(30, 90); //初始位置
}

void MyKirby::walk(Background& bg) {

}

//不由按键驱动的一直执行的重力掉落
void MyKirby::fall(float deltatime, Background& bg) {
    //必须先检查是否在地面上，不然直接掉出屏幕！！
    checkGroundCollision(bg);
    checkBarrierCollision(bg.getBarrier());
    if(!m_isGround || (m_isGround && m_speed.y < 0)) {
        m_speed.y += m_gravity * deltatime; 
        m_kirby.move(0,m_speed.y);
    } 
}

void MyKirby::jump() {

}

void MyKirby::devour(){
    m_isDevouring = true;
}

void MyKirby::startFly(float deltatime, Background& bg){
    if(!m_startFly){
        //必须先检查是否在地面上，不然直接掉出屏幕！！
        checkGroundCollision(bg);
        checkBarrierCollision(bg.getBarrier());
        m_startFly = true;
        m_gravity = 0.15f;
        m_speed.y = -0.12f;
        m_startFlyClock.restart();
    }
}

void MyKirby::enterFlyModel(){
    m_startFly = false;
    m_isFlying = true;
    m_speed.y = 0;
    std::cout<<"进入飞行模式!-------"<<std::endl;
} 

void MyKirby::fly(float deltatime, Background& bg){
    if(m_isFlying){
        //地面和障碍物碰撞检测
        checkGroundCollision(bg);
        checkBarrierCollision(bg.getBarrier());
        //卡比水平方向移动
        m_kirby.move(m_speed.x,0);
        //根据速度方向改变卡比朝向
        m_faceRight = m_speed.x >=0 ? true : false;
    }
}

void MyKirby::endFly(){
    m_startFly = false; //防止bug
    m_isFlying = false;
    m_gravity = 0.8f;
    m_speed.y = 0;
    std::cout<<"结束飞行模式!-------"<<std::endl;
}

void MyKirby::attack(){
    if(!m_isAttacking){
        m_isAttacking = true;
        m_canDoDamge = true;
        m_attackClock.restart();
        //如果闪电卡比攻击，记录相关参数
        if(m_changeType==1){
            m_bounds = m_kirby.getGlobalBounds();
            m_pos = {m_kirby.getPosition().x, m_kirby.getPosition().y};
        }
    }
}

void MyKirby::attackFly(){
    if(!m_isAttacking){
        m_isAttacking = true;
        m_canDoDamge = true;
        m_attackClock.restart();
    }
}

void MyKirby::reborn(){
    this->m_kirby.setPosition(30,90);
    this->m_health = 5;
    m_isDying = false;
}

void MyKirby::change(){
    switch (m_changeType)
    { 
    case 0:
        m_kirby.setTexture(m_normalKirbyTexture);
        m_kirby.setTextureRect(sf::IntRect(2, 98, 25, 20)); 
        m_attackDamage = 1; //普通卡比攻击伤害为1      
        m_isDefault = true;
        m_isChangable = true;
        break;
    case 1: //闪电卡比
        m_kirby.setTexture(m_sparkKirbyTexture);
        m_kirby.setTextureRect(sf::IntRect(6,7,25,31));
        m_attackDamage = 3; //闪电卡比攻击伤害为3
        m_isDefault = false;
        m_isChangable = false;
        break;
    default:
        break;
    }
}

void MyKirby::addScore(int points){
    m_score += points;
}

void MyKirby::minusScore(int points){
    m_score -= points;
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
            m_speed.y = m_speed.y > 0 ? 0 : m_speed.y;
            //如果闪电卡比正在攻击，不需要设置位置
            if(m_changeType==1 && m_isAttacking){
                break;
            }
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
            m_speed.y = m_speed.y > 0 ? 0 : m_speed.y;
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
                minusScore(enemy->getAttack() * 5);
                std::cout<<"Kirby-HP: "<<m_health<<std::endl;
                //卡比死亡逻辑
                if(m_health <=0){
                    std::cout<<"=====Kirby Die!!! GAME OVER!!======"<<std::endl;
                    die();
                }
                //设置为无敌并重置计时器
                m_isNoHarm = true;
                m_invincibilityClock.restart();
                break;
            }
        }
    }
}

void MyKirby::checkAttackHit(std::vector<std::shared_ptr<Enemy>>& enemies){
    sf::FloatRect attackArea = m_kirby.getGlobalBounds();
    //计算攻击区域
    if(m_faceRight){
        if(m_isFlying){
            attackArea.width += m_attackFlyParticles.getGlobalBounds().width;
        }else {
            attackArea.width += m_attackRange;
        }
    }else {
        if(m_isFlying){
            attackArea.left += m_attackFlyParticles.getGlobalBounds().width;
            attackArea.width += m_attackFlyParticles.getGlobalBounds().width;
        }else {
            attackArea.left -= m_attackRange;
            attackArea.width += m_attackRange;
        }
    }
    //闪电卡比攻击时无敌
    if(m_changeType==1 && m_isAttacking){
        m_isNoHarm = true;
        m_invincibilityClock.restart();
    }
    //检测敌人是否在攻击区域
    for(auto& enemy : enemies){
        if(attackArea.intersects(enemy->getSprite().getGlobalBounds())){
            //只有在卡比可以造成伤害时敌人受伤，防止瞬间多次伤害
            if(m_canDoDamge){
                if (m_isFlying)enemy->takeDamage(m_attackFlyDamage);
                else enemy->takeDamage(m_attackDamage);
                m_canDoDamge = false;
                if(!enemy->isAlive()){
                    addScore(30); //敌人被消灭加30分
                }
            }
        }
    }
}

void MyKirby::checkDevourHit(std::vector<std::shared_ptr<Enemy>>& enemies){
    if(!m_isDevouring){
        for(auto& enemy : enemies){
            if(enemy->isBeingDevoured()){
                enemy->resetDevour();
            }
        }
        return;
    }
    sf::FloatRect devourArea = m_kirby.getGlobalBounds();
    //计算攻击区域
    if(m_faceRight){
        devourArea.width += m_devourParticles.getGlobalBounds().width;
    }else {
        devourArea.left += m_devourParticles.getGlobalBounds().width;
        devourArea.width += m_devourParticles.getGlobalBounds().width;
    }
    //检测敌人是否在吞噬区域
    for(auto& enemy : enemies){
        if(devourArea.intersects(enemy->getSprite().getGlobalBounds())){
            if(!enemy->isBeingDevoured()){
                enemy->startBeingDevoured();
            }
            else {
                //吞噬完成
                if(enemy->getDevourClock().getElapsedTime().asSeconds() > enemy->getDevourDuration()){
                    enemy->endBeingDevoured();
                    m_isChangable = true;
                    m_changeType = enemy->getMyType();
                    //吞噬敌人加10分
                    addScore(10);
                }
            }
        }
        else if(enemy->isBeingDevoured()){
            enemy->resetDevour();
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

void MyKirby::updateAttackState(){
    if(m_isAttacking){
        if(m_attackClock.getElapsedTime().asSeconds() >=
        m_attackDuration){
            m_isAttacking = false;
        }
    }
}

void MyKirby::setSprite(sf::Sprite& player) {
    m_kirby = player;
}

void MyKirby::setSpeed(sf::Vector2f speed) {
    m_speed = speed;
}