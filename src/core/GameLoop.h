#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>
#include <scene/Background.h>
#include <entity/Character/MyKirby.h>
#include <animation/Animation.h>
#include "core/EnemyManager.h"
#include <entity/Enemy/SparkEnemy.h>

//动画帧(一种形态一套动作动画)
struct KirbyAnimations {
    Animation standAnimation;
    Animation deathAnimation;
    Animation walkAnimation;
    Animation jumpAnimation;
    Animation fallAnimation;
    Animation attackAnimation;
    Animation attackFlyAnimation;
    Animation attackFlyParticleAnimation;
    Animation flyingAnimation;
    Animation flyPreAnimation;
    //吞噬动画
    Animation devourAnimation;
    Animation devourParticlesAnimation;
    //吞噬闪电怪物相关动画
    //... 
};

class GameLoop {
public:
    GameLoop(sf::RenderWindow& window, sf::Sprite& player, EnemyManager& sparkEnemy);
    void run();

private:
    //同步非阻塞处理事件（关闭窗口事件
    void processEvents();
    //鼠标点击事件
    bool isSpriteClicked(sf::Sprite& sprite, sf::Event::MouseButtonEvent& mouseEvent, sf::RenderWindow& window);
    //初始化动画
    void initAnimation();
    void initNormalKirbyAnimation();
    void initSparkKirbyAnimation();
    //加载纹理
    void loadTexture();
    //初始化游戏显示数据
    void initScoreHealth();
    //更新关卡
    void loadNextLevel();
    //重置
    void resetGameData();
    //更新动画
    void updateAnimation(float deltaTime);
    //更新粒子效果（位置）
    void updateParticles();
    //结束游戏
    void end();
    //处理键盘输入
    void update();
    //渲染画面
    void render();
    void renderMainMenu();
    void renderGameWorld();
    void renderPauseMenu();
    void renderHelpMeau();
    void renderGameOver();

    sf::RenderWindow& m_window;
    sf::Sprite& m_player;
    sf::Sprite m_particles;
    MyKirby m_kirby; // 成员变量生命周期与GameLoop相同，不会频繁复制
    EnemyManager m_enemyManager;
    std::vector<std::shared_ptr<Enemy>>& m_enemies;

    Background m_background = Background();
    sf::Vector2f m_speed = {0.25,0.25};
    sf::Vector2u m_originalSize; // 原始窗口尺寸

    //得分相关
    int m_score = 0;
    int m_bestRecord;
    sf::Text m_scoreText;
    sf::Text m_healthText;
    sf::Text m_levelText;
    sf::Font m_font;

    //关卡相关
    int m_currentLevel = 1;
    int m_currentScene = 1;
    float m_levelWidth = 510.f;  //关卡宽度
    bool m_isLoadingNextLevel = false;
    sf::View m_gameView; //可移动的视图
    sf::RectangleShape m_fadeOverlay;
    float m_fadeAlpha = 0;

    //游戏结束
    sf::Texture m_endingTexture;
    sf::Texture m_gameOverTexture;
    sf::Sprite m_gameOverSprite;
    sf::Sprite m_endingSprite;
    bool m_win = false;
    bool m_isGameCompleted = false;

    //存储所有帧区域
    std::vector<sf::IntRect> frames;
    int currentFrame = 0;
    float frameTime = 0.1f; // 每帧持续时间（秒）
    float elapsedTime = 0.0f; // 积累的时间
    sf::Clock clock;

    bool isRenderParticles = false; //是否渲染粒子
    bool isSpacePressed = false; //是否按住空格

    
    KirbyAnimations m_normalAnimation;    //普通形态动画组
    KirbyAnimations m_sparkAnimation; //变身形态动画组
    KirbyAnimations* m_currentAnimation;  //指向当前动画组
    
    AnimationState currentState = AnimationState::Standing;

    //游戏状态相关
    enum GameState {
        STATE_MENU,
        STATE_HELP,
        STATE_PLAYING,
        STATE_PAUSED,
        STATE_GAME_OVER
    };

    //主菜单
    sf::Sprite m_mainMenu; //背景
    sf::Texture m_mainMenuTexture;
    sf::Sprite m_newGameBtn; //新游戏按钮
    sf::Texture m_newGameBtnTexture;
    sf::Sprite m_helpBtn; //帮助按钮
    sf::Texture m_helpBtnTexture;
    sf::Sprite m_exitBtn; //退出按钮
    sf::Texture m_exitBtnTexture;

    //帮助菜单
    sf::Sprite m_helpMenu;
    sf::Texture m_helpMenuTexture;
    sf::Sprite m_returnBtn;
    sf::Texture m_returnBtnTexture;

    //双栈系统：一个用于常规状态，一个用于临时/覆盖状态
    std::stack<GameState> m_stateStack;      //主状态栈
    std::stack<GameState> m_tempStateStack;  //临时状态栈 

    void pushState(GameState state) {
        m_stateStack.push(state);
    }
    void popState() {
        if (!m_stateStack.empty()) {m_stateStack.pop();}
    }
    void pushTempState(GameState state) {
        m_tempStateStack.push(state);
    }
    void popTempState() {
        if (!m_tempStateStack.empty()) {m_tempStateStack.pop();}
    }
    void clearState(){
        while(!m_stateStack.empty()){m_stateStack.pop();}
        while(!m_tempStateStack.empty()){m_tempStateStack.pop();}
        //重置游戏数据
        resetGameData();
        pushState(STATE_MENU);
    }
    GameState getCurrentState() const {
        if (!m_tempStateStack.empty()) {
            return m_tempStateStack.top();
        }
        return m_stateStack.empty() ? STATE_MENU : m_stateStack.top();
    }
    
};

#endif 
