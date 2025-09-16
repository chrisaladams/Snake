#pragma once
#include <string>
#include <vector>
#include <utility>

class HighScoreService {
public:
    explicit HighScoreService(std::string path = "highscores.json");

    void load();
    void save();

    void submit(const std::string& name, int score);

    int best() const; // highest score

    const std::vector<std::pair<std::string,int>>& list() const { return scores; }

private:
    std::string filePath;
    std::vector<std::pair<std::string,int>> scores; // name, score
};