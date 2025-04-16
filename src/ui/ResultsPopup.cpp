#include "ResultsPopup.hpp"
#include <managers/GuessManager.hpp>

ResultsPopup* ResultsPopup::create(int score) {
    auto ret = new ResultsPopup;
    if (ret->initAnchored(370.f, 145.f, score)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool ResultsPopup::setup(int score) {
    this->setTitle("Results");

    m_closeBtn->removeFromParent();

    auto label = CCLabelBMFont::create(fmt::format("You got a score of {}!\nYour total score is {}.", score, GuessManager::get().totalScore).c_str(), "bigFont.fnt");
    label->setScale(0.5f);
    m_mainLayer->addChildAtPosition(label, Anchor::Center, ccp(0.f, 5.f));

    auto nextRoundSpr = ButtonSprite::create("Continue");
    nextRoundSpr->setScale(0.8f);
    auto nextRoundBtn = CCMenuItemExt::createSpriteExtra(nextRoundSpr, [](CCObject*) {
        auto& gm = GuessManager::get();
        gm.startNewGame();
    });

    auto endGameSpr = ButtonSprite::create("End Game", "goldFont.fnt", "GJ_button_06.png");
    endGameSpr->setScale(0.8f);
    auto endGameBtn = CCMenuItemExt::createSpriteExtra(endGameSpr, [](CCObject*) {
        auto& gm = GuessManager::get();
        gm.endGame();
    });
    
    auto nextRoundMenu = CCMenu::create();
    nextRoundMenu->addChild(nextRoundBtn);
    nextRoundMenu->addChild(endGameBtn);

    nextRoundMenu->setLayout(
        RowLayout::create()
    );

    m_mainLayer->addChildAtPosition(nextRoundMenu, Anchor::Bottom, ccp(0.f, 25.f));

    return true;
}

void ResultsPopup::onClose(CCObject*) {}
