#include "HookedPauseLayer.hpp"
#include <managers/GuessManager.hpp>
#include <ui/layers/LevelLayer.hpp>

void HookedPauseLayer::tryQuit(CCObject* sender) {
    if (!GuessManager::get().currentLevel) {
        PauseLayer::tryQuit(sender);
        return;
    }
    
    auto layer = LevelLayer::create();
    auto scene = CCScene::create();
    scene->addChild(layer);
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(.5f, scene));
}

void HookedPauseLayer::customSetup() {
    PauseLayer::customSetup();

    if (!GuessManager::get().currentLevel) return;

    if (auto titleLabel = typeinfo_cast<CCLabelBMFont*>(this->getChildByIDRecursive("level-name"))) {
        titleLabel->setString("????????");
    }
}
