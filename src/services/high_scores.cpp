#include "services/high_scores.h"
#include <fstream>
#include <sstream>
#include <algorithm>

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
        size_t firstQuote = content.find('"', colon+1);
        size_t secondQuote = content.find('"', firstQuote+1);
        if (colon==std::string::npos || firstQuote==std::string::npos || secondQuote==std::string::npos) break;
        std::string name = content.substr(firstQuote+1, secondQuote-firstQuote-1);

        size_t scoreKey = content.find("\"score\"", secondQuote);
        if (scoreKey == std::string::npos) break;
        size_t colon2 = content.find(':', scoreKey);
        size_t endNum = content.find_first_of(",}\n\r\t ", colon2+1);
        std::string numStr = content.substr(colon2+1, (endNum==std::string::npos?content.size():endNum)-(colon2+1));
        int sc = 0; try { sc = std::stoi(numStr); } catch(...) { sc = 0; }
        if (!name.empty()) scores.emplace_back(name, sc);
        pos = scoreKey + 7;
    }
}

void HighScoreService::save() {
    std::sort(scores.begin(), scores.end(), [](auto&a, auto&b){return a.second > b.second;});
    if (scores.size() > 10) scores.resize(10);
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
        if (scores.size() > 10) scores.resize(10);
    }
}

int HighScoreService::best() const {
    int best = 0;
    for (auto &p : scores) best = std::max(best, p.second);
    return best;
}
