#include <SFML/Graphics.hpp>
#include "core/GameLoop.h"
#include "core/KirbyManager.h"
#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
    #ifdef _WIN32
    // 设置控制台和窗口为 UTF-8 模式
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    #endif

    // 创建游戏窗口
    sf::RenderWindow window(sf::VideoMode(512, 256), sf::String("星之卡比"));

    //创建卡比精灵
    KirbyManager kirbyManager;
    sf::Sprite& kirby = kirbyManager.getKirby();

    // 创建并运行游戏循环
    GameLoop gameLoop(window, kirby);
    gameLoop.run();

    return 0;
}
