#include "core/GameLoop.h"
#include "scene/Background.h"
#include "const/Constants.h"
#include <SFML/Graphics.hpp>
#include "core/ScoreManager.h"
#include <iostream>

using namespace AnimationFrame;


GameLoop::GameLoop(sf::RenderWindow& window, sf::Sprite& player, EnemyManager& enemies) 
    : m_window(window), m_player(player), m_kirby(MyKirby(player)), m_enemyManager(enemies), m_enemies(enemies.getEnemies()) {
    // 保存原始窗口尺寸
    m_originalSize = window.getSize();
    m_gameView.setSize(m_originalSize.x,m_originalSize.y);
    //加载纹理
    loadTexture();
    //加载历史记录
    m_bestRecord = ScoreManager::loadHighScore();
    //初始化状态栈
    m_stateStack.push(STATE_MENU);
    //初始化苹果
    spawnApples(4);
    //初始化分数、生命值
    initScoreHealth();
    //初始化动画帧
    initAnimation();
}

void GameLoop::loadTexture(){
    //初始化背景
    m_background.loadTextures("assets/back_top.png","assets/back_bottom.png");
    if (!m_endingTexture.loadFromFile("assets/winScreen.png")) {
        throw std::runtime_error("无法加载通关图片");
    }
    if (!m_appleTexture.loadFromFile("assets/apple.png")) {
        throw std::runtime_error("无法加载苹果图片");
    }
    if (!m_gameOverTexture.loadFromFile("assets/loseScreen.png")) {
        throw std::runtime_error("无法加载失败图片");
    }
    if (!m_mainMenuTexture.loadFromFile("assets/menubackround.png")) {
        throw std::runtime_error("无法加载主菜单图片");
    }
    if (!m_newGameBtnTexture.loadFromFile("assets/Menu_play2.png")) {
        throw std::runtime_error("无法加载主菜单图片");
    }
    if (!m_helpBtnTexture.loadFromFile("assets/Menu_Help2.png")) {
        throw std::runtime_error("无法加载主菜单图片");
    }
    if (!m_exitBtnTexture.loadFromFile("assets/Menu_EXIT2.png")) {
        throw std::runtime_error("无法加载主菜单图片");
    }
    if (!m_helpMenuTexture.loadFromFile("assets/helpMenu.png")) {
        throw std::runtime_error("无法加载主菜单图片");
    }
    if (!m_returnBtnTexture.loadFromFile("assets/Menu_Back.png")) {
        throw std::runtime_error("无法加载主菜单图片");
    }
    m_helpMenu.setTexture(m_helpMenuTexture);
    m_returnBtn.setTexture(m_returnBtnTexture);
    m_mainMenu.setTexture(m_mainMenuTexture);
    m_newGameBtn.setTexture(m_newGameBtnTexture);
    m_helpBtn.setTexture(m_helpBtnTexture);
    m_exitBtn.setTexture(m_exitBtnTexture);
    m_endingSprite.setTexture(m_endingTexture);
    m_gameOverSprite.setTexture(m_gameOverTexture);
    //调整按钮位置
    m_newGameBtn.setPosition(190,100);
    m_helpBtn.setPosition(190,140);
    m_exitBtn.setPosition(190,180);
    m_returnBtn.setPosition(5,5);
    //调整图片大小为窗口大小
    sf::Vector2u windowSize = m_window.getSize();
    m_endingSprite.setScale(
        windowSize.x / m_endingSprite.getLocalBounds().width,
        windowSize.y / m_endingSprite.getLocalBounds().height
    );
    m_gameOverSprite.setScale(
        windowSize.x / m_gameOverSprite.getLocalBounds().width,
        windowSize.y / m_gameOverSprite.getLocalBounds().height
    );
}

void GameLoop::spawnApples(int count) {
    std::uniform_int_distribution<> xDist(50, m_originalSize.x * 3 - 50);
    std::uniform_int_distribution<> yDist(40, 150);
    
    for (int i = 0; i < count; ++i) {
        Apple apple;
        apple.sprite.setTexture(m_appleTexture);
        apple.sprite.setPosition(xDist(m_gen), yDist(m_gen));
        m_apples.push_back(apple);
    }
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

        GameState current = getCurrentState();

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
        switch (current) {
            case STATE_MENU:
                if (event.key.code == sf::Keyboard::Enter || (event.mouseButton.button == sf::Mouse::Left && isSpriteClicked(m_newGameBtn,event.mouseButton, m_window))) {
                    pushState(STATE_PLAYING); // 进入游戏
                }
                if(event.mouseButton.button == sf::Mouse::Left && isSpriteClicked(m_helpBtn,event.mouseButton, m_window)){
                    pushTempState(STATE_HELP); //进入帮助界面
                }
                if(event.mouseButton.button == sf::Mouse::Left && isSpriteClicked(m_exitBtn,event.mouseButton, m_window)){
                    m_window.close(); //游戏结束
                }
                break;
                
            case STATE_PLAYING:
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    pushTempState(STATE_PAUSED); //临时暂停
                }
                //处理按下空格执行吞噬动画
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && m_kirby.isAlive() && !isSpacePressed && !m_kirby.isFlying()) {
                    //闪电卡比按下空格恢复状态
                    if(m_kirby.getChangeType()==1){
                        m_kirby.setMyChangetype(0);
                        m_kirby.change();
                        m_currentAnimation = &m_normalAnimation;
                    }else {
                        m_kirby.devour();
                        isRenderParticles = true;
                        isSpacePressed = true;
                        m_particles = m_kirby.getDevourParticle();
                        currentState = AnimationState::Devour;
                        m_currentAnimation->devourAnimation.play(0.05f, false);  //重置并播放（不循环）
                        m_currentAnimation->devourParticlesAnimation.play(0.1f, false);
                    }
                }
                //空格释放
                else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space){
                    isSpacePressed = false;
                    isRenderParticles = false;
                    m_kirby.setIsDevouring(false);
                }
                //H进入帮助页面
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::H) {
                    pushTempState(STATE_HELP); 
                }
                break;
                
            case STATE_PAUSED:
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    popTempState(); //取消暂停
                }
                //H进入帮助页面
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::H) {
                    pushTempState(STATE_HELP); 
                }
                break;
                
            case STATE_HELP:
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape || (event.mouseButton.button == sf::Mouse::Left && isSpriteClicked(m_returnBtn,event.mouseButton, m_window))) {
                    popTempState(); 
                }
                break;
                
            case STATE_GAME_OVER:
                //通关或死亡后按任意键退出
                if (event.type == sf::Event::KeyPressed) {
                    // m_window.close();
                    clearState();
                    render();
                }
                break;
            //...
        }
        // ...
    }
}

bool GameLoop::isSpriteClicked(sf::Sprite& sprite, sf::Event::MouseButtonEvent& mouseEvent, sf::RenderWindow& window) {
    //将鼠标像素坐标转换为世界坐标
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(mouseEvent.x, mouseEvent.y));
    //获取精灵的全局边界框
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    //检查是否在边界框内
    return spriteBounds.contains(mousePos);
}

void GameLoop::initScoreHealth(){
    //初始化计分文本
    m_font.loadFromFile("assets/fonts/font.ttf");
    m_scoreText.setFont(m_font);
    m_scoreText.setString("Score: " + std::to_string(0)+ "\n" + "Best: " + std::to_string(m_bestRecord));
    m_scoreText.setCharacterSize(16);
    m_scoreText.setFillColor(sf::Color::Red);
    m_scoreText.setPosition(m_window.getSize().x - 120, 10); //右上角
    //初始化生命值
    m_healthText.setFont(m_font);
    m_healthText.setString("HP: 5");
    m_healthText.setCharacterSize(16);
    m_healthText.setFillColor(sf::Color::Red);
    m_healthText.setPosition(10, 10); //左上角
    //初始化等级
    m_levelText.setFont(m_font);
    m_levelText.setString("Level: 1");
    m_levelText.setCharacterSize(16);
    m_levelText.setFillColor(sf::Color::Red);
    m_levelText.setPosition(10, 28); //左上角
}

void GameLoop::initAnimation(){
    //初始化普通形态动画
    initNormalKirbyAnimation();
    //初始化闪电形态动画
    initSparkKirbyAnimation();
    //默认使用普通动画
    m_currentAnimation = &m_normalAnimation;
}

void GameLoop::initNormalKirbyAnimation(){
    // 站立动画
    m_normalAnimation.standAnimation.addFrame(standAnimationRect);
    //死亡动画
    m_normalAnimation.deathAnimation.setFrames(deathAnimationRect);
    m_normalAnimation.deathAnimation.play(0.1f,false);
    //飞行动画
    m_normalAnimation.flyingAnimation.setFrames(flyingAnimationRect);
    //准备飞行（起飞）动画
    m_normalAnimation.flyPreAnimation.setFrames(flyPrepareAnimationRect);
    m_normalAnimation.flyPreAnimation.play(0.05f,false);
    // 行走动画
    m_normalAnimation.walkAnimation.setFrames(walkAnimationRect);
    // 跳跃动画
    m_normalAnimation.jumpAnimation.setFrames(jumpAnimationRect);
    m_normalAnimation.jumpAnimation.play(0.1f,false);
    // 降落动画
    m_normalAnimation.fallAnimation.setFrames(fallAnimationRect);
    m_normalAnimation.fallAnimation.play(0.1f,false);
    // 攻击动画
    m_normalAnimation.attackAnimation.setFrames(attackAnimationRect);
    m_normalAnimation.attackAnimation.play(0.05f,false);
    //飞行状态下攻击动画
    m_normalAnimation.attackFlyAnimation.setFrames(attackFlyAnimationRect);
    m_normalAnimation.attackFlyAnimation.play(0.05f,false);
    //飞行状态下攻击粒子
    m_normalAnimation.attackFlyParticleAnimation.setFrames(attackFlyParticlesAnimationRect);
    m_normalAnimation.attackFlyParticleAnimation.play(0.05f,false);
    //吞噬动画
    m_normalAnimation.devourAnimation.setFrames(devourAnimationRect);
    m_normalAnimation.devourAnimation.play(0.1f,false);
    //吞噬动画粒子
    m_normalAnimation.devourParticlesAnimation.setFrames(devourParticlesAnimationRect);
    m_normalAnimation.devourParticlesAnimation.play(0.1f,false);
    // ...
}

void GameLoop::initSparkKirbyAnimation(){
    // 站立动画
    m_sparkAnimation.standAnimation.setFrames(standSparkAnimationRect);
    //死亡动画
    m_sparkAnimation.deathAnimation.setFrames(deathAnimationRect);
    m_sparkAnimation.deathAnimation.play(0.1f,false);
    //飞行动画
    m_sparkAnimation.flyingAnimation.setFrames(flyingSparkAnimationRect);
    //准备飞行（起飞）动画
    m_sparkAnimation.flyPreAnimation.setFrames(flyPrepareSparkAnimationRect);
    m_sparkAnimation.flyPreAnimation.play(0.05f,false);
    // 行走动画
    m_sparkAnimation.walkAnimation.setFrames(walkSparkAnimationRect);
    // 跳跃动画
    m_sparkAnimation.jumpAnimation.setFrames(jumpSparkAnimationRect);
    m_sparkAnimation.jumpAnimation.play(0.1f,false);
    // 降落动画
    m_sparkAnimation.fallAnimation.setFrames(fallSparkAnimationRect);
    m_sparkAnimation.fallAnimation.play(0.1f,false);
    // 攻击动画
    m_sparkAnimation.attackAnimation.setFrames(attackASparkAnimationRect);
    m_sparkAnimation.attackAnimation.play(0.05f,false);
    //飞行状态下攻击动画
    m_sparkAnimation.attackFlyAnimation.setFrames(attackFlyAnimationRect);
    m_sparkAnimation.attackFlyAnimation.play(0.05f,false);
    //飞行状态下攻击粒子
    m_sparkAnimation.attackFlyParticleAnimation.setFrames(attackFlyParticlesAnimationRect);
    m_sparkAnimation.attackFlyParticleAnimation.play(0.05f,false);
    //吞噬动画
    m_sparkAnimation.devourAnimation.setFrames(devourSparkAnimationRect);
    m_sparkAnimation.devourAnimation.play(0.1f,false);
    //吞噬动画粒子
    m_sparkAnimation.devourParticlesAnimation.setFrames(devourParticlesAnimationRect);
    m_sparkAnimation.devourParticlesAnimation.play(0.1f,false);
    // ...
}

void GameLoop::loadNextLevel(){
    m_currentLevel++;
    m_isLoadingNextLevel = true;

    //重置卡比位置到左侧
    m_player.setPosition( (m_window.getSize().x + 25)* m_currentScene, 80);
    currentState = AnimationState::Falling;
    
    // 根据关卡编号加载不同地图
    switch (m_currentLevel) {
        case 2:
            m_levelWidth = 1600.f;
            m_gameView.setCenter(m_player.getPosition().x +m_originalSize.x/2 ,
                m_originalSize.y/2);
            m_window.setView(m_gameView);
            m_background.setBottomPos((m_window.getSize().x + 25)* m_currentScene);
            m_background.setBottomRect(sf::IntRect(1,196,512,193));
            //设置面板位置
            m_scoreText.setPosition((m_window.getSize().x + 25)* m_currentScene + m_window.getSize().x - 120, 10); //右上角
            m_healthText.setPosition((m_window.getSize().x + 25)* m_currentScene+10,10);
            m_levelText.setPosition((m_window.getSize().x + 25)* m_currentScene+10,28);
            m_helpMenu.setPosition((m_window.getSize().x + 25)* m_currentScene,0);
            m_currentScene++;
            break;
        case 3:
            //...
            end();
            break;
    }
    // m_isLoadingNextLevel = false;
}

void GameLoop::resetGameData(){
    //重置卡比状态
    m_kirby.reset();
    m_currentAnimation = &m_normalAnimation;
    currentState = AnimationState::Falling;
    m_player.setPosition(30, 90); //初始位置

    //重置关卡数据
    m_currentLevel = 1;
    m_currentScene = 0;
    m_isGameCompleted = false;
    m_levelWidth = 510.f;  //关卡宽度
    m_win = false;
    
    //重置敌人
    m_enemyManager.clear();

    //重新生成苹果
    m_apples.clear();
    spawnApples(4);
    
    //重置视图
    m_helpMenu.setPosition(0,0);
    m_gameView.setCenter(m_originalSize.x/2, m_originalSize.y/2);
    m_window.setView(m_gameView);
    
    //重置背景位置
    m_background.resetPosition();
}

void GameLoop::end(){
    std::cout<<"end-------------"<<m_isGameCompleted<<" "<<m_currentLevel <<std::endl;
    m_gameOverSprite.setPosition((m_window.getSize().x + 25)* (m_currentScene-1),0);
    m_endingSprite.setPosition((m_window.getSize().x + 25)* (m_currentScene-1),0);
    if(m_kirby.isAlive()){
        m_win = true;
    }
    m_score = m_kirby.getScore();
    if (m_score > m_bestRecord) {
        m_bestRecord = m_score;
        ScoreManager::saveHighScore(m_bestRecord);
    }
    pushState(STATE_GAME_OVER);
    m_isGameCompleted = true;
}

void GameLoop::updateAnimation(float deltaTime){
    switch (currentState)
    {
    case AnimationState::Standing:
        m_player.setTextureRect(m_currentAnimation->standAnimation.update(deltaTime));
        break;
    case AnimationState::Walking:
        m_player.setTextureRect(m_currentAnimation->walkAnimation.update(deltaTime));
        break;
    case AnimationState::Jumping:
        m_player.setTextureRect(m_currentAnimation->jumpAnimation.update(deltaTime));
        if (m_currentAnimation->jumpAnimation.isFinished()) {
            currentState = m_kirby.getIsGround() ? AnimationState::Standing : AnimationState::Falling;
        }
        break;
    case AnimationState::Falling:
        m_player.setTextureRect(m_currentAnimation->fallAnimation.update(deltaTime));
        if (m_kirby.getIsGround()){
            currentState = AnimationState::Standing;
        }
        break;
    case AnimationState::Attacking:
        m_player.setTextureRect(m_currentAnimation->attackAnimation.update(deltaTime));
        //如果是闪电卡比普通攻击动画需要从中心点播放
        if(m_kirby.getChangeType()==1){
            sf::IntRect& currentRect = m_currentAnimation->attackAnimation.update(deltaTime);
            sf::FloatRect bounds = m_kirby.getBounds();
            sf::Vector2f pos = m_kirby.getPos();
            float deltaX = (currentRect.width - bounds.width) / 2.0;
            float deltaY = (currentRect.height - bounds.height) / 2.0; 
            m_player.setTextureRect(currentRect);
            m_player.setPosition(pos.x - deltaX, pos.y - deltaY + 7);
        }
        break;
    case AnimationState::AttackFly:
        m_player.setTextureRect(m_currentAnimation->attackFlyAnimation.update(deltaTime));
        m_particles.setTextureRect(m_currentAnimation->attackFlyParticleAnimation.update(deltaTime));
        updateParticles();
        if(m_kirby.getAttackClock().getElapsedTime().asSeconds()>m_kirby.getAttackDuration()){
            //飞行结束
            m_kirby.endFly();
            isRenderParticles = false;
            currentState = AnimationState::Falling;
        }
        break;
    case AnimationState::Death:
        m_player.setTextureRect(m_currentAnimation->deathAnimation.update(deltaTime));
        //如果动画播放完...
        if(m_kirby.getClock().getElapsedTime().asSeconds()>m_kirby.getDeathDuration()){
            //重新复活或者游戏结束
            // m_kirby.reborn();
            // currentState = AnimationState::Falling;
            end();
        }
        break;
    case AnimationState::FlyPre:
        m_player.setTextureRect(m_currentAnimation->flyPreAnimation.update(deltaTime));
        m_kirby.setStartFlyCD(m_kirby.getStartFlyClock().getElapsedTime().asSeconds()>=1 ? 0 : m_kirby.getStartFlyClock().getElapsedTime().asSeconds());
        if(m_kirby.getStartFlyClock().getElapsedTime().asSeconds()>m_kirby.getStartFlyDuration()){
            //起飞完成进入飞行模式
            m_kirby.enterFlyModel();
            currentState = AnimationState::Flying;
        }
        break;
    case AnimationState::Flying:
        m_player.setTextureRect(m_currentAnimation->flyingAnimation.update(deltaTime));
        if(m_kirby.getIsGround()){
            m_kirby.endFly();
            currentState = AnimationState::Standing;
        }  
        break;  
    case AnimationState::Devour:
        m_player.setTextureRect(m_currentAnimation->devourAnimation.update(deltaTime));
        m_particles.setTextureRect(m_currentAnimation->devourParticlesAnimation.update(deltaTime));
        updateParticles();
        break;
    default:
        break;
    }
}

void GameLoop::updateParticles(){
    sf::Vector2f pos = m_player.getPosition();
    sf::FloatRect bounds = m_player.getGlobalBounds();
    m_particles.setPosition(pos.x + bounds.width + 5, pos.y);
}

void GameLoop::update() {
    switch (getCurrentState()) {
        case STATE_MENU:

            break;
            
        case STATE_PLAYING: {
            if(m_isGameCompleted) return; //游戏结束
            // 检测是否到达右边界
            if (m_player.getPosition().x > m_levelWidth - 50) {
                loadNextLevel();
            }else if(m_player.getPosition().x > m_window.getSize().x * m_currentScene){
                //重置卡比位置到左侧
                m_player.setPosition( (m_window.getSize().x + 25)* m_currentScene, m_player.getPosition().y);
                m_gameView.setCenter(m_player.getPosition().x +m_originalSize.x/2 ,
                    m_originalSize.y/2);
                m_window.setView(m_gameView);
                m_background.setBottomPos((m_window.getSize().x + 25)* m_currentScene);
                //设置面板位置
                m_scoreText.setPosition((m_window.getSize().x + 25)* m_currentScene + m_window.getSize().x - 120, 10); //右上角
                m_healthText.setPosition((m_window.getSize().x + 25)* m_currentScene+10,10);
                m_levelText.setPosition((m_window.getSize().x + 25)* m_currentScene+10,28);
                m_helpMenu.setPosition((m_window.getSize().x + 25)* m_currentScene,0);
                m_currentScene++;
            }
            //更新视图中心（跟随玩家）
                // m_gameView.setCenter(m_gameView.getCenter().x + m_window.getSize().x,
                //         m_gameView.getCenter().y);
                // m_window.setView(m_gameView);
            //计算帧时间
            float deltaTime = clock.restart().asSeconds();
            //处理键盘输入
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && m_kirby.isAlive() && !m_kirby.getIsDevouring()) {
                if (m_player.getPosition().x > 0)
                    // m_player.move(-m_speed, 0);
                    m_kirby.setSpeed({-m_speed.x,m_kirby.getSpeed().y});
                    m_kirby.update(deltaTime, m_background);
                    if(m_kirby.getIsGround()){
                        currentState = AnimationState::Walking;
                    }
            }
            if ( sf::Keyboard::isKeyPressed(sf::Keyboard::D) && m_kirby.isAlive() && !m_kirby.getIsDevouring()) {
                if (m_player.getPosition().x < m_originalSize.x * m_currentScene - m_player.getGlobalBounds().width)
                    // m_player.move({m_speed.x, 0});
                    m_kirby.setSpeed({m_speed.x,m_kirby.getSpeed().y});
                    m_kirby.update(deltaTime, m_background);
                    if(m_kirby.getIsGround()){
                        currentState = AnimationState::Walking;
                    }
            }
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::K)) && m_kirby.getIsGround() && m_kirby.isAlive() && !m_kirby.getIsDevouring()) {
                if (m_player.getPosition().y > 0)
                    // m_player.move({0, -m_speed.y});
                    m_kirby.setSpeed({0, -m_speed.y});
                    m_kirby.update(deltaTime, m_background);
                    currentState = AnimationState::Jumping;
                    m_currentAnimation->jumpAnimation.play(0.1f, false); //重置跳跃动画
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && !m_kirby.getIsAttacking() && m_kirby.isAlive() && !m_kirby.getIsDevouring()) {
                if(m_kirby.getChangeType()==1 && (m_kirby.isFlying()|| m_kirby.getStartFly()||!m_kirby.getIsGround())){
                    //如果闪电卡比飞行或者起跳状态攻击，不反应
                }else {
                    // m_kirby.update(deltaTime, m_background);
                    if(m_kirby.isFlying() || m_kirby.getStartFly()){
                        m_kirby.attackFly();
                        isRenderParticles = true;
                        m_particles = m_kirby.getAttackFlyParticle();
                        currentState = AnimationState::AttackFly;
                        m_currentAnimation->attackFlyAnimation.play(0.05f,false);
                        m_currentAnimation->attackFlyParticleAnimation.play(0.05f,false);
                    }else {
                        m_kirby.attack();
                        currentState = AnimationState::Attacking;
                        m_currentAnimation->attackAnimation.play(0.05f,false);
                    }
                }  
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::I) && m_kirby.isAlive() && !m_kirby.getIsDevouring() ) {
                // m_kirby.update(deltaTime, m_background);
                m_kirby.startFly(deltaTime,m_background);
                currentState = AnimationState::FlyPre;
                m_currentAnimation->flyPreAnimation.play(0.05f,false);
                // std::cout<<"speedY: "<<m_kirby.getSpeed().y<<std::endl;
            }
            if ( sf::Keyboard::isKeyPressed(sf::Keyboard::S) && m_kirby.isAlive() && !m_kirby.getIsDevouring() && m_kirby.getChangable()) {
                m_kirby.change();
                switch (m_kirby.getChangeType())
                {       
                case 1: //闪电卡比
                    m_currentAnimation = &m_sparkAnimation;
                    break;
                default:
                    break;
                }
            }
            //检测是否没有水平输入、不是原地起跳、没有在攻击、没有在吞噬
            bool noHorizontalInput = !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && 
                                !sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
                                !sf::Keyboard::isKeyPressed(sf::Keyboard::K) &&
                                !sf::Keyboard::isKeyPressed(sf::Keyboard::J)&&
                                !sf::Keyboard::isKeyPressed(sf::Keyboard::I);
            if (noHorizontalInput && m_kirby.getIsGround() && !m_kirby.getIsAttacking() && m_kirby.isAlive() && !m_kirby.getStartFly() && !m_kirby.isFlying() && !m_kirby.getIsDevouring()) {
                currentState = AnimationState::Standing;
            }
            if (!m_kirby.isAlive() && !m_kirby.isDying()){
                currentState = AnimationState::Death;
                m_currentAnimation->deathAnimation.play(0.1f,false);
                m_kirby.setIsDying(true);
            }
            //处理帧动画
            updateAnimation(deltaTime);
            //每帧更新敌人列表，确保enemyManager已经回收的死亡敌人不被访问（内存安全）
            m_enemies = m_enemyManager.getEnemies();
            //不由按键驱动的一直执行的重力掉落、无敌状态检测、敌人碰撞检测
            m_kirby.fall(deltaTime, m_background);
            m_kirby.updateAttackState();
            m_kirby.checkAttackHit(m_enemies);
            m_kirby.checkDevourHit(m_enemies);
            m_kirby.checkEnemyCollision(m_enemies);
            m_kirby.checkAppleCollision(m_apples);
            m_kirby.updateInvincibility();
            //敌人运动
            m_enemyManager.updateAll(deltaTime,m_background);
            break;
        }
            
        case STATE_PAUSED:

            break;
            
        case STATE_HELP:

            break;
            
        case STATE_GAME_OVER:

            break;
        //...
    }
}

void GameLoop::render() {
    m_window.clear();

    //总是渲染底层状态（暂停时仍然显示游戏画面）
    if (!m_stateStack.empty()) {
        switch (m_stateStack.top()) {
            case STATE_MENU:
                renderMainMenu();
                break;

            case STATE_PLAYING:
                renderGameWorld();
                break;

            case STATE_GAME_OVER:
                renderGameOver();
                break;
            //...
        }
    }
    
    //渲染当前顶层状态（只有临时状态栈不空时才需要额外渲染顶层状态）
    switch (getCurrentState()) {
        case STATE_PAUSED:
            renderPauseMenu();
            break;

        case STATE_HELP:
            renderHelpMeau();
            break;
            
        //...
    }

    m_window.display(); 
}

void GameLoop::renderMainMenu(){
    m_window.draw(m_mainMenu);
    m_window.draw(m_exitBtn);
    m_window.draw(m_helpBtn);
    m_window.draw(m_newGameBtn);
}

void GameLoop::renderGameWorld(){
    m_background.draw(m_window);
    m_enemyManager.drawAll(m_window);
    m_window.draw(m_player);
    if(isRenderParticles) m_window.draw(m_particles);
    //更新并渲染分数文本
    m_scoreText.setString("Score: " + std::to_string(m_kirby.getScore())+ "\n" + "Best: " + std::to_string(m_bestRecord));
    m_window.draw(m_scoreText);
    //生命值文本
    m_healthText.setString("HP: " + std::to_string(m_kirby.getHP()));
    m_window.draw(m_healthText);
    //关卡文本
    m_levelText.setString("Level: " + std::to_string(m_currentLevel));
    m_window.draw(m_levelText);
    // 关卡切换时的渐隐效果
    // if (m_isLoadingNextLevel) {
    //     m_fadeOverlay.setFillColor(sf::Color(0, 0, 0, m_fadeAlpha));
    //     m_window.draw(m_fadeOverlay);
    //     m_fadeAlpha += 1; // 调整速度
    //     if (m_fadeAlpha >= 255) {
    //         m_fadeAlpha = 0;
    //         m_isLoadingNextLevel = false;
    //     }
    // }
    //绘制苹果
    for (const auto& apple : m_apples) {
        if (!apple.collected) {
            m_window.draw(apple.sprite);
        }
    }
}

void GameLoop::renderPauseMenu(){

}

void GameLoop::renderHelpMeau(){
    m_window.draw(m_helpMenu);
    m_window.draw(m_returnBtn);
}

void GameLoop::renderGameOver(){
    if(m_win){
        m_window.draw(m_endingSprite);
    }else {
        m_window.draw(m_gameOverSprite);
    }
}


