#include <Geode/Geode.hpp>
#include <Geode/modify/CreatorLayer.hpp>

#include "ui/StartPopup.hpp"

using namespace geode::prelude;

class $modify(MyCL, CreatorLayer) {
    struct Fields {
    };

    bool init() {
        if (!CreatorLayer::init()) return false;

        auto btn = CCMenuItemExt::createSpriteExtra(CircleButtonSprite::create(CCLabelBMFont::create("GDG", "goldFont.fnt")), [this](CCObject*) {
            StartPopup::create()->show();
        });

        if (auto menu = this->getChildByIDRecursive("bottom-right-menu")) {
            menu->addChild(btn);
            menu->updateLayout();
        }

        return true;
    }
};
