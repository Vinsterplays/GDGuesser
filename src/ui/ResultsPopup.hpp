#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class ResultsPopup : public geode::Popup<int> {
protected:
    bool setup(int score) override;

    void onClose(cocos2d::CCObject *) override;
public:
    static ResultsPopup* create(int score);
};
