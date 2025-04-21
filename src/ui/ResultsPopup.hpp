#pragma once

#include <Geode/Geode.hpp>
#include <managers/GuessManager.hpp>

using namespace geode::prelude;

class ResultsPopup : public geode::Popup<int, LevelDate, LevelDate> {
protected:
    bool setup(int score, LevelDate correctDate, LevelDate date) override;

    void onClose(cocos2d::CCObject *) override;
public:
    static ResultsPopup* create(int score, LevelDate correctDate, LevelDate date);
};
