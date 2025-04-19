#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class ResultsPopup : public geode::Popup<int, std::string> {
protected:
    bool setup(int score, std::string correctDate) override;

    void onClose(cocos2d::CCObject *) override;
public:
    static ResultsPopup* create(int score, std::string correctDate);
};
