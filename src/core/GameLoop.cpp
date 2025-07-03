#include "core/GameLoop.h"
#include "scene/Background.h"
#include "const/Constants.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace AnimationFrame;


GameLoop::GameLoop(sf::RenderWindow& window, sf::Sprite& player, EnemyManager& enemies) 
    : m_window(window), m_player(player), m_kirby(MyKirby(player)), m_enemyManager(enemies), m_enemies(enemies.getEnemies()) {
    // 保存原始窗口尺寸
    m_originalSize = window.getSize();
    //初始化背景
    m_background.loadTextures("assets/back_top.png","assets/back_bottom.png");
    //初始化动画帧
    initAnimation();
}

void GameLoop::run() {
    while (m_window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void GameLoop::processEvents() {
    // SFML的事件处理是同步但非阻塞的
    // pollEvent()会从事件队列中取出一个事件处理
    // 如果没有事件会立即返回false，不会阻塞
    sf::Event event;
    while (m_window.pollEvent(event)) {
        // 处理窗口关闭事件
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }
        // 处理窗口大小变化事件
        else if (event.type == sf::Event::Resized) {
            // 计算保持原始宽高比的视图
            float windowRatio = (float)event.size.width / (float)event.size.height;
            float gameRatio = (float)m_originalSize.x / (float)m_originalSize.y;
            
            float viewWidth = 1.0f;
            float viewHeight = 1.0f;
            float viewX = 0.0f;
            float viewY = 0.0f;

            if (windowRatio > gameRatio) {
                // 窗口更宽，左右加黑边
                viewWidth = gameRatio / windowRatio;
                viewX = (1.0f - viewWidth) / 2.0f;
            } else {
                // 窗口更高，上下加黑边
                viewHeight = windowRatio / gameRatio;
                viewY = (1.0f - viewHeight) / 2.0f;
            }

            // 设置视图
            sf::View view(sf::FloatRect(0, 0, m_originalSize.x, m_originalSize.y));
            view.setViewport(sf::FloatRect(viewX, viewY, viewWidth, viewHeight));
            m_window.setView(view);
        }
        // ...
    }
}

void GameLoop::initEnemy(){

}

void GameLoop::initAnimation(){
    // 站立动画
    standAnimation.addFrame(standAnimationRect);
    // 行走动画
    for (int i = 0; i < 10; i++) {
        walkAnimation.addFrame(sf::IntRect(
            walkAnimationRect.left + i * walkAnimationRect.width, walkAnimationRect.top, walkAnimationRect.width, walkAnimationRect.height
        ));
    }
    // 跳跃动画
    for (int i=0;i<7 ;i++){
        jumpAnimation.addFrame(sf::IntRect(
            jumpAnimationRect.left + i * (jumpAnimationRect.width + 5),//多右移5个固定像素
            jumpAnimationRect.top, jumpAnimationRect.width, jumpAnimationRect.height
        ));
        //跳跃动画不循环，每帧设置0.2s
        jumpAnimation.play(0.1f,false);
    }
    // 降落动画
    for (int i=0;i<2;i++){
        fallAnimation.addFrame(sf::IntRect(
            fallAnimationRect.left + i * (fallAnimationRect.width + 5),//多右移5个固定像素
            fallAnimationRect.top, fallAnimationRect.width, fallAnimationRect.height
        ));
        //降落动画不循环，每帧设置0.2s
        fallAnimation.play(0.1f,false);
    }
    // 攻击动画
    attackAnimation.setFrames(attackAnimationRect);
    attackAnimation.play(0.05f,false);
    // ...
}

void GameLoop::updateAnimation(float deltaTime){
    switch (currentState)
    {
    case AnimationState::Standing:
        m_player.setTextureRect(standAnimation.update(deltaTime));
        break;
    case AnimationState::Walking:
        m_player.setTextureRect(walkAnimation.update(deltaTime));
        break;
    case AnimationState::Jumping:
        m_player.setTextureRect(jumpAnimation.update(deltaTime));
        if (jumpAnimation.isFinished()) {
            currentState = m_kirby.getIsGround() ? AnimationState::Standing : AnimationState::Falling;
        }
        break;
    case AnimationState::Falling:
        m_player.setTextureRect(fallAnimation.update(deltaTime));
        if (m_kirby.getIsGround()){
            currentState = AnimationState::Standing;
        }
        break;
    case AnimationState::Attacking:
        m_player.setTextureRect(attackAnimation.update(deltaTime));
        break;
    default:
        break;
    }
}

void GameLoop::update() {
    //计算帧时间
    float deltaTime = clock.restart().asSeconds();
    // elapsedTime += deltaTime;
    //处理键盘输入
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if (m_player.getPosition().x > 0)
            // m_player.move(-m_speed, 0);
            m_kirby.setSpeed({-m_speed.x,m_kirby.getSpeed().y});
            m_kirby.update(deltaTime, m_background);
            if(m_kirby.getIsGround()){
                currentState = AnimationState::Walking;
            }
    }
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if (m_player.getPosition().x < m_originalSize.x - m_player.getGlobalBounds().width)
            // m_player.move({m_speed.x, 0});
            m_kirby.setSpeed({m_speed.x,m_kirby.getSpeed().y});
            m_kirby.update(deltaTime, m_background);
            if(m_kirby.getIsGround()){
                currentState = AnimationState::Walking;
            }
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && m_kirby.getIsGround()) {
        if (m_player.getPosition().y > 0)
            // m_player.move({0, -m_speed.y});
            m_kirby.setSpeed({0, -m_speed.y});
            m_kirby.update(deltaTime, m_background);
            currentState = AnimationState::Jumping;
            jumpAnimation.play(0.1f, false); //重置跳跃动画
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !m_kirby.getIsAttacking()) {
        // m_kirby.update(deltaTime, m_background);
        m_kirby.attack();
        currentState = AnimationState::Attacking;
        attackAnimation.play(0.05f,false);
    }
    //检测是否没有水平输入、不是原地起跳、没有在攻击
    bool noHorizontalInput = !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && 
                         !sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
                         !sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
                         !sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
    if (noHorizontalInput && m_kirby.getIsGround() && !m_kirby.getIsAttacking()) {
        currentState = AnimationState::Standing;
    }
    //处理帧动画
    updateAnimation(deltaTime);
    //每帧更新敌人列表，确保enemyManager已经回收的死亡敌人不被访问（内存安全）
    m_enemies = m_enemyManager.getEnemies();
    //不由按键驱动的一直执行的重力掉落、无敌状态检测、敌人碰撞检测
    m_kirby.fall(deltaTime, m_background);
    m_kirby.updateInvincibility();
    m_kirby.updateAttackState();
    m_kirby.checkAttackHit(m_enemies);
    m_kirby.checkEnemyCollision(m_enemies);
    //敌人运动
    m_enemyManager.updateAll(deltaTime,m_background);
}

void GameLoop::render() {
    m_window.clear();
    m_background.draw(m_window);
    m_enemyManager.drawAll(m_window);
    m_window.draw(m_player);
    m_window.display();
}


