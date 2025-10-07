#include "services/high_scores.h"
#include <fstream>
#include <sstream>
#include <algorithm>

namespace {
    constexpr size_t MAX_HIGH_SCORES = 10;
    constexpr size_t OFFSET_ONE = 1;
    constexpr int SCORE_KEY_LENGTH = 7; // length of "score" + quotes + colon pattern
    constexpr int DEFAULT_SCORE = 0;
}

HighScoreService::HighScoreService(std::string path)
: filePath(std::move(path)) {}

void HighScoreService::load() {
    scores.clear();
    std::ifstream f(filePath);
    if (!f.is_open()) return;
    std::stringstream buffer; buffer << f.rdbuf();
    std::string content = buffer.str();
    size_t pos = 0;
    while (true) {
        size_t nameKey = content.find("\"name\"", pos);
        if (nameKey == std::string::npos) break;
        size_t colon = content.find(':', nameKey);
        size_t firstQuote = content.find('"', colon + OFFSET_ONE);
        size_t secondQuote = content.find('"', firstQuote + OFFSET_ONE);
        if (colon==std::string::npos || firstQuote==std::string::npos || secondQuote==std::string::npos) break;
        std::string name = content.substr(firstQuote + OFFSET_ONE, secondQuote - firstQuote - OFFSET_ONE);

        size_t scoreKey = content.find("\"score\"", secondQuote);
        if (scoreKey == std::string::npos) break;
        size_t colon2 = content.find(':', scoreKey);
        size_t endNum = content.find_first_of(",}\n\r\t ", colon2 + OFFSET_ONE);
        std::string numStr = content.substr(colon2 + OFFSET_ONE, (endNum==std::string::npos?content.size():endNum) - (colon2 + OFFSET_ONE));
        int sc = DEFAULT_SCORE; try { sc = std::stoi(numStr); } catch(...) { sc = DEFAULT_SCORE; }
        if (!name.empty()) scores.emplace_back(name, sc);
        pos = scoreKey + SCORE_KEY_LENGTH;
    }
}

void HighScoreService::save() {
    std::sort(scores.begin(), scores.end(), [](auto&a, auto&b){return a.second > b.second;});
    if (scores.size() > MAX_HIGH_SCORES) scores.resize(MAX_HIGH_SCORES);
    std::ofstream f(filePath);
    if (!f.is_open()) return;
    f << "[\n";
    for (size_t i=0;i<scores.size();++i) {
        f << "  {\"name\":\"" << scores[i].first << "\", \"score\":" << scores[i].second << "}";
        if (i+1<scores.size()) f << ",";
        f << "\n";
    }
    f << "]\n";
}

void HighScoreService::submit(const std::string& name, const int score) {
    if (!name.empty()) {
        scores.emplace_back(name, score);
        std::sort(scores.begin(), scores.end(), [](auto&a, auto&b){return a.second > b.second;});
        if (scores.size() > MAX_HIGH_SCORES) scores.resize(MAX_HIGH_SCORES);
    }
}

int HighScoreService::best() const {
    int best = DEFAULT_SCORE;
    for (auto &p : scores) best = std::max(best, p.second);
    return best;
}
