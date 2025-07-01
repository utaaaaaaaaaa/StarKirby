#include "core/GameLoop.h"
#include "scene/Background.h"
#include "const/Constants.h"
#include <SFML/Graphics.hpp>
#include <iostream>


GameLoop::GameLoop(sf::RenderWindow& window, sf::Sprite& player) 
    : m_window(window), m_player(player), m_kirby(MyKirby(player)) {
    // 保存原始窗口尺寸
    m_originalSize = window.getSize();
    //初始化卡比对象
    m_kirby.setSprite(player);
    //初始化背景
    m_background.loadTextures("assets/back_top.png","assets/back_bottom.png");
    //初始化帧vector
    for (int i = 0; i < Animation::frameCount; ++i) {
        frames.emplace_back(Animation::startX + i * Animation::frameWidth, Animation::startY, Animation::frameWidth, Animation::frameHeight);
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

void GameLoop::update() {
    //计算帧时间
    float deltaTime = clock.restart().asSeconds();
    elapsedTime += deltaTime;
    // 处理键盘输入
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if (m_player.getPosition().x > 0)
            // m_player.move(-m_speed, 0);
            m_kirby.setSpeed({-m_speed.x,m_kirby.getSpeed().y});
            m_kirby.update(m_background);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if (m_player.getPosition().x < m_originalSize.x - m_player.getGlobalBounds().width)
            // m_player.move({m_speed.x, 0});
            m_kirby.setSpeed({m_speed.x,m_kirby.getSpeed().y});
            m_kirby.update(m_background);
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && m_kirby.getIsGround()) {
        if (m_player.getPosition().y > 0)
            // m_player.move({0, -m_speed.y});
            m_kirby.setSpeed({0, -m_speed.y});
            m_kirby.update(m_background);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        if (m_player.getPosition().y < m_originalSize.y - m_player.getGlobalBounds().height)
            // m_player.move({0, m_speed.y});
            m_kirby.setSpeed({0, m_speed.y});
            m_kirby.update(m_background);
    }
    //处理帧动画
    if (elapsedTime >= frameTime) {
        currentFrame = (currentFrame + 1) % Animation::frameCount;
        m_player.setTextureRect(frames[currentFrame]);
        elapsedTime = 0.0f;
    }
    // 不由按键驱动的一直执行的重力掉落
    m_kirby.fall(deltaTime, m_background);
}

void GameLoop::render() {
    m_window.clear();
    m_background.draw(m_window);
    m_window.draw(m_player);
    m_window.display();
}


