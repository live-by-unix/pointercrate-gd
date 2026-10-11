#include "DemonlistMenu.hpp"
#include "PointercrateBrowser.hpp"

using namespace geode::prelude;

namespace pointercrate {

DemonlistMenu* DemonlistMenu::create() {
    auto ret = new DemonlistMenu();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool DemonlistMenu::init() {
    if (!FLAlertLayer::init(nullptr, "Demonlist Browser", "Select a demonlist to browse:", "Cancel", nullptr, 400.0f, false, 0.0f, 1.0f)) {
        return false;
    }

    // Remove default button and add custom menu
    m_buttonMenu->removeAllChildren();

    // Create Pointercrate button using game button sprite
    auto pointercrateBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_starBtn_001.png"),
        this,
        menu_selector(DemonlistMenu::onPointercrate)
    );
    pointercrateBtn->setID("pointercrate-btn"_spr);
    m_buttonMenu->addChild(pointercrateBtn);

    // Create Pemonlist button
    auto pemonlistBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_starBtn_001.png"),
        this,
        menu_selector(DemonlistMenu::onPemonlist)
    );
    pemonlistBtn->setID("pemonlist-btn"_spr);
    m_buttonMenu->addChild(pemonlistBtn);

    // Create AREDL button
    auto aredlBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_starBtn_001.png"),
        this,
        menu_selector(DemonlistMenu::onAredl)
    );
    aredlBtn->setID("aredl-btn"_spr);
    m_buttonMenu->addChild(aredlBtn);

    m_buttonMenu->setLayout(
        RowLayout::create()
            ->setGap(10.0f)
            ->setAutoScale(false)
    );

    return true;
}

void DemonlistMenu::onPointercrate(CCObject* sender) {
    log::info("Opening Pointercrate");
    PointercrateBrowser::get().openBrowser(DemonlistType::Pointercrate);
    removeFromParent();
}

void DemonlistMenu::onPemonlist(CCObject* sender) {
    log::info("Opening Pemonlist");
    PointercrateBrowser::get().openBrowser(DemonlistType::Pemonlist);
    removeFromParent();
}

void DemonlistMenu::onAredl(CCObject* sender) {
    log::info("Opening AREDL");
    PointercrateBrowser::get().openBrowser(DemonlistType::AREDL);
    removeFromParent();
}

} // namespace pointercrate
