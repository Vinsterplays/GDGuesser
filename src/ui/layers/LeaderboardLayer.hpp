#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class GDGLeaderboardLayer : public CCLayer {
protected:
    bool init();
    void keyBackClicked();
public:
    static GDGLeaderboardLayer* create();
};
