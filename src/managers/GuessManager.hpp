#pragma once

#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>

using namespace geode::prelude;

struct LevelDate {
    int year;
    int month;
    int day;
};

struct LeaderboardEntry {
    int account_id;
    std::string username;
    int total_score;
    int icon_id;
};

// gets and stores the current level,
// as well as handles the game state.
class GuessManager: public CCObject, public LevelDownloadDelegate {
protected:
    GuessManager() {}

    EventListener<web::WebTask> m_listener;

    // DashAuth token
    std::string m_daToken;

    void levelDownloadFinished(GJGameLevel* level) override;
    void levelDownloadFailed(int x) override;
public:
    GJGameLevel* currentLevel;

    int totalScore = 0;

    void startNewGame();
    void endGame();
    void submitGuess(LevelDate date, std::function<void(int score)> callback);

    void getLeaderboard(std::function<void(std::vector<LeaderboardEntry>)> callback);
    const std::string getServerUrl();

    static GuessManager& get() {
        static GuessManager instance;
        return instance; 
    }
};
