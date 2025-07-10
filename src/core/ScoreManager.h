#pragma once
#include <string>
#include <fstream>

class ScoreManager {
public:
    static void saveHighScore(int score);
    static int loadHighScore();
    static const std::string SCORE_FILE;
};