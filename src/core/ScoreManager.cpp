#include "ScoreManager.h"
#include <iostream>
#include <filesystem>

const std::string ScoreManager::SCORE_FILE = "D:\\_Code\\c++\\StarKirby\\assets\\highscore.txt";

void ScoreManager::saveHighScore(int score) {
    std::ofstream file(SCORE_FILE);
    if (file) file << score;
}

int ScoreManager::loadHighScore() {
    if (!std::filesystem::exists(SCORE_FILE)) {
        std::cout<<"找不到文件"<<std::endl;
        return 0;
    }
    
    std::ifstream file(SCORE_FILE);
    int score = 0;
    if (file) file >> score;
    return score;
}