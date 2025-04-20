#include "HookedEndLevelLayer.hpp"
#include <managers/GuessManager.hpp>
#include <ui/layers/LevelLayer.hpp>

void HookedEndLevelLayer::onMenu(CCObject* sender) {
    auto& gm = GuessManager::get();
    if (!gm.currentLevel) {
        EndLevelLayer::onMenu(sender);
        return;
    }
    
    gm.syncScores();

    auto layer = LevelLayer::create();
    auto scene = CCScene::create();
    scene->addChild(layer);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(.5f, scene));

    m_playLayer->resetAudio();
    FMODAudioEngine::get()->unloadAllEffects();

    FMODAudioEngine::get()->playEffect("quitSound_01.ogg", 1.f, 0.f, 0.7f);

    GameManager::get()->fadeInMenuMusic();
}

void HookedEndLevelLayer::onLevelLeaderboard(CCObject* sender) {
    if (!GuessManager::get().currentLevel) {
        EndLevelLayer::onLevelLeaderboard(sender);
    }

    return;
}
