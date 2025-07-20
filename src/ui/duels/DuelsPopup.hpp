#pragma once

#include <Geode/Geode.hpp>
using namespace geode::prelude;

#include <managers/types.hpp>

class DuelsPopup : public geode::Popup<> {
public:
    static DuelsPopup* create();
protected:
    CCMenuItemSpriteExtra* readyBtn;
    
    CCNode* myNode;
    CCNode* oppNode;

    bool setup() override;
    void updatePlayers(Duel duel);

    void onClose(CCObject*) override;
};
