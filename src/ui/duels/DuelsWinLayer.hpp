#pragma once

#include <Geode/Geode.hpp>
#include <managers/types.hpp>

using namespace geode::prelude;

class DuelsWinLayer : public CCLayer {
public:
    static DuelsWinLayer* create(LeaderboardEntry winner, LeaderboardEntry loser);
    static CCScene* scene(LeaderboardEntry winner, LeaderboardEntry loser);
protected:
    LeaderboardEntry winner;
    LeaderboardEntry loser;

    bool init(LeaderboardEntry winner, LeaderboardEntry loser);
};
