#include "core/KirbyManager.h"
#include <SFML/Graphics.hpp>
#include "core/GameLoop.h"

KirbyManager::KirbyManager() {
    // 加载卡比精灵纹理
    if (!m_kirbyTexture.loadFromFile("assets/Kirby_Normal.png")) {
        throw std::runtime_error("没有找到卡比素材，角色创建失败");
    }

    // 创建卡比精灵
    m_kirby.setTexture(m_kirbyTexture);
    // 初始化贴图区域
    m_kirby.setTextureRect(sf::IntRect(2, 98, 25, 20)); 
    m_kirby.setPosition(30, 90); // 初始位置
}

sf::Sprite& KirbyManager::getKirby() {
    return m_kirby;
}