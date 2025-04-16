#include "StartPopup.hpp"
#include <managers/GuessManager.hpp>
#include <ui/layers/LeaderboardLayer.hpp>

StartPopup* StartPopup::create() {
    auto ret = new StartPopup;
    if (ret->initAnchored(300.f, 250.f)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool StartPopup::setup() {
    this->setTitle("GDGuesser");

    auto btn = CCMenuItemExt::createSpriteExtra(ButtonSprite::create("Start!"), [this](CCObject*) {
        auto& gm = GuessManager::get();        
        gm.startNewGame();
    });
    auto menu = CCMenu::create();
    menu->addChild(btn);
    m_mainLayer->addChildAtPosition(menu, Anchor::Center);

    auto lbBtn = CCMenuItemExt::createSpriteExtraWithFrameName("GJ_levelLeaderboardBtn_001.png", 1.f, [](CCObject*) {
        auto layer = GDGLeaderboardLayer::create();
        auto scene = CCScene::create();
        scene->addChild(layer);
        CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(.5f, scene));
    });
    auto lbMenu = CCMenu::create();
    lbMenu->addChild(lbBtn);
    m_mainLayer->addChildAtPosition(lbMenu, Anchor::TopRight, ccp(-30.f, -30.f));

    return true;
}
