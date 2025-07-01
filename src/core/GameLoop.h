#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <SFML/Graphics.hpp>
#include <scene/Background.h>
#include <entity/Character/MyKirby.h>
#include <animation/Animation.h>

class GameLoop {
public:
    GameLoop(sf::RenderWindow& window, sf::Sprite& player);
    void run();

private:
    //同步非阻塞处理事件（关闭窗口事件
    void processEvents();
    //初始化动画
    void initAnimation();
    //更新动画
    void updateAnimation(float deltaTime);
    //处理键盘输入
    void update();
    //渲染画面
    void render();

    sf::RenderWindow& m_window;
    sf::Sprite& m_player;
    MyKirby m_kirby; // 成员变量生命周期与GameLoop相同，不会频繁复制

    Background m_background = Background();
    sf::Vector2f m_speed = {0.25,0.25};
    sf::Vector2u m_originalSize; // 原始窗口尺寸

    // 存储所有帧区域
    std::vector<sf::IntRect> frames;
    int currentFrame = 0;
    float frameTime = 0.1f; // 每帧持续时间（秒）
    float elapsedTime = 0.0f; // 积累的时间
    sf::Clock clock;

    //动画帧
    Animation standAnimation;
    Animation walkAnimation;
    Animation jumpAnimation;
    Animation attackAnimation;
    AnimationState currentState = AnimationState::Walking;
};

#endif // GAME_LOOP_H
