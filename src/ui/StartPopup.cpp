#include "StartPopup.hpp"
#include <ui/layers/LeaderboardLayer.hpp>
#include <ui/layers/LoadingOverlayLayer.hpp>

class DifficultySelectionPopup : public geode::Popup<GameOptions> {
protected:
    bool setup(GameOptions options) {
        this->setTitle("Select your difficulty!");

        auto startGame = [this, options](GameMode mode) {
            auto& gm = GuessManager::get();
            gm.startNewGame({
                .mode = mode,
                .versions = options.versions
            });
            this->onClose(nullptr);
        };

        auto normalBtn = CCMenuItemExt::createSpriteExtra(ButtonSprite::create("Normal"), [startGame](CCObject*) {
            startGame(GameMode::Normal);
        });

        auto hardBtn = CCMenuItemExt::createSpriteExtra(ButtonSprite::create("Hardcore"), [startGame](CCObject*) {
            startGame(GameMode::Hardcore);
        });

        auto menu = CCMenu::create();
        menu->setLayout(
            ColumnLayout::create()
                ->setAxisReverse(true)
        );

        menu->addChild(normalBtn);
        menu->addChild(hardBtn);

        menu->updateLayout();

        m_mainLayer->addChildAtPosition(menu, Anchor::Center);

        auto infoBtn = InfoAlertButton::create("Info", "<cg>Normal mode</c> is the regular version of the game. You can see the level name, author, and difficulty. Scores submitted in this mode are out of 500.\n<cr>Hardcore mode</c> gives you nothing but the song name and level to go by. Scores submitted in this mode are out of 600.", 1.f);
        auto topRightMenu = CCMenu::create();
        topRightMenu->addChild(infoBtn);

        m_mainLayer->addChildAtPosition(topRightMenu, Anchor::TopRight);

        return true;
    }
public:
    static DifficultySelectionPopup* create(GameOptions options) {
        auto ret = new DifficultySelectionPopup;
        if (ret->initAnchored(280.f, 230.f, options)) {
            ret->autorelease();
            return ret;
        }
        delete ret;
        return nullptr;
    }
};

StartPopup* StartPopup::create() {
    auto ret = new StartPopup;
    if (ret->initAnchored(300.f, 200.f)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool StartPopup::setup() {
    this->setTitle("GDGuesser");

    auto btn = CCMenuItemExt::createSpriteExtra(ButtonSprite::create("Start!"), [this](CCObject*) {
        DifficultySelectionPopup::create(options)->show();
    });
    auto startMenu = CCMenu::create();
    startMenu->addChild(btn);
    m_mainLayer->addChildAtPosition(startMenu, Anchor::Center, ccp(0.f, 30.f));

    auto lbBtn = CCMenuItemExt::createSpriteExtraWithFrameName("GJ_levelLeaderboardBtn_001.png", .85f, [](CCObject*) {
        auto layer = GDGLeaderboardLayer::create();
        auto scene = CCScene::create();
        scene->addChild(layer);
        CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(.5f, scene));
    });
    auto lbMenu = CCMenu::create();
    lbMenu->addChild(lbBtn);
    m_mainLayer->addChildAtPosition(lbMenu, Anchor::TopRight, ccp(-30.f, -30.f));

    auto versionsMenu = CCMenu::create();

    #define VERSION_BTN(version_name) \
        { \
            auto versionTextOff = CCLabelBMFont::create(version_name, "bigFont.fnt"); \
            versionTextOff->setOpacity(255 * 0.5); \
            auto versionBtn = CCMenuItemExt::createToggler(CCLabelBMFont::create(version_name, "bigFont.fnt"), versionTextOff, [this](CCMenuItemToggler* toggler) { \
                if (!toggler->isOn()) { \
                    if (std::find(options.versions.begin(), options.versions.end(), version_name) == options.versions.end()) { \
                        options.versions.push_back(version_name); \
                    } \
                } else { \
                    auto searchResult = std::find(options.versions.begin(), options.versions.end(), version_name); \
                    if (searchResult != options.versions.end()) { \
                        options.versions.erase(searchResult); \
                    } \
                } \
            }); \
            versionsMenu->addChild(versionBtn); \
        }

    VERSION_BTN("1.0")
    VERSION_BTN("1.1")
    VERSION_BTN("1.2")
    VERSION_BTN("1.3")
    VERSION_BTN("1.4")
    VERSION_BTN("1.5")
    VERSION_BTN("1.6")
    VERSION_BTN("1.7")
    VERSION_BTN("1.8")
    VERSION_BTN("1.9")
    VERSION_BTN("2.0")
    VERSION_BTN("2.1")
    VERSION_BTN("2.2")

    #undef VERSION_BTN

    versionsMenu->setLayout(
        RowLayout::create()
            ->setGrowCrossAxis(true)
            ->setGap(8.f)
    );
    versionsMenu->setScale(0.5f);
    versionsMenu->setContentWidth(380.f);
    versionsMenu->updateLayout();

    auto versionsContainer = CCScale9Sprite::create("square02b_001.png");
    versionsContainer->setContentSize({
        275.f,
        versionsMenu->getContentHeight() - 10.f
    });
    versionsContainer->setColor(ccc3(0,0,0));
    versionsContainer->setOpacity(75);

    versionsMenu->setPosition(
        {
            275.f / 2.f,
            versionsContainer->getContentHeight() / 2.f
        }
    );
    versionsContainer->addChild(versionsMenu);

    m_mainLayer->addChildAtPosition(versionsContainer, Anchor::Bottom, ccp(0.f, 45.f));

    auto versionsText = CCLabelBMFont::create("Versions", "bigFont.fnt");
    versionsText->setScale(0.5f);
    m_mainLayer->addChildAtPosition(versionsText, Anchor::Bottom, ccp(0.f, 45.f + versionsContainer->getContentHeight() - 20.f));
    return true;
}
