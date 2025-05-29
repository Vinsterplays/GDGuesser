#include "AccountPopup.hpp"
#include <managers/GuessManager.hpp>

AccountPopup* AccountPopup::create(int accountID) {
    auto ret = new AccountPopup;
    if (ret->initAnchored(350.f, 270.f, accountID)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool AccountPopup::setup(int accountID) {
    auto& gm = GuessManager::get();

    gm.getAccount(accountID, [this](LeaderboardEntry user) {
        auto theB = CCLabelBMFont::create(user.username.c_str(), "bigFont.fnt");
        m_mainLayer->addChildAtPosition(theB, Anchor::Top, ccp(0.f, -30.f));

        auto separator = CCSprite::createWithSpriteFrameName("floorLine_001.png");
        separator->setScaleX(0.75f);
        separator->setScaleY(1);
        separator->setOpacity(100);

        m_mainLayer->addChildAtPosition(separator, Anchor::Top, ccp(0.f, -50.f));
    });

    return true;
}
