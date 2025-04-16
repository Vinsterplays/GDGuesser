#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/EndLevelLayer.hpp>

using namespace geode::prelude;

class $modify(HookedEndLevelLayer, EndLevelLayer) {
    $override
    void onMenu(CCObject* sender);

    $override
    void onLevelLeaderboard(CCObject* sender);
};
