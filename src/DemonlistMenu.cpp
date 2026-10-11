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
    if (!FLAlertLayer::init(nullptr, "Demonlist Browser", "Select a demonlist to browse:", "Cancel", nullptr, 500.0f, false, 0.0f, 1.0f)) {
        return false;
    }

    // Remove default button and add custom menu
    m_buttonMenu->removeAllChildren();

    // Create Pointercrate button with label
    auto pointercrateNode = CCNode::create();
    auto pointercrateSprite = CCSprite::createWithSpriteFrameName("GJ_starBtn_001.png");
    pointercrateSprite->setPosition(CCPoint(0, 10));
    pointercrateNode->addChild(pointercrateSprite);
    
    auto pointercrateLabel = CCLabelTTF::create("Pointercrate", "Arial", 12);
    pointercrateLabel->setPosition(CCPoint(0, -10));
    pointercrateLabel->setColor(ccWHITE);
    pointercrateNode->addChild(pointercrateLabel);
    
    auto pointercrateBtn = CCMenuItemSpriteExtra::create(
        pointercrateNode,
        this,
        menu_selector(DemonlistMenu::onPointercrate)
    );
    pointercrateBtn->setID("pointercrate-btn"_spr);
    m_buttonMenu->addChild(pointercrateBtn);

    // Create Pemonlist button with label
    auto pemonlistNode = CCNode::create();
    auto pemonlistSprite = CCSprite::createWithSpriteFrameName("GJ_starBtn_001.png");
    pemonlistSprite->setPosition(CCPoint(0, 10));
    pemonlistNode->addChild(pemonlistSprite);
    
    auto pemonlistLabel = CCLabelTTF::create("Pemonlist", "Arial", 12);
    pemonlistLabel->setPosition(CCPoint(0, -10));
    pemonlistLabel->setColor(ccWHITE);
    pemonlistNode->addChild(pemonlistLabel);
    
    auto pemonlistBtn = CCMenuItemSpriteExtra::create(
        pemonlistNode,
        this,
        menu_selector(DemonlistMenu::onPemonlist)
    );
    pemonlistBtn->setID("pemonlist-btn"_spr);
    m_buttonMenu->addChild(pemonlistBtn);

    // Create AREDL button with label
    auto aredlNode = CCNode::create();
    auto aredlSprite = CCSprite::createWithSpriteFrameName("GJ_starBtn_001.png");
    aredlSprite->setPosition(CCPoint(0, 10));
    aredlNode->addChild(aredlSprite);
    
    auto aredlLabel = CCLabelTTF::create("AREDL", "Arial", 12);
    aredlLabel->setPosition(CCPoint(0, -10));
    aredlLabel->setColor(ccWHITE);
    aredlNode->addChild(aredlLabel);
    
    auto aredlBtn = CCMenuItemSpriteExtra::create(
        aredlNode,
        this,
        menu_selector(DemonlistMenu::onAredl)
    );
    aredlBtn->setID("aredl-btn"_spr);
    m_buttonMenu->addChild(aredlBtn);

    m_buttonMenu->setLayout(
        RowLayout::create()
            ->setGap(30.0f)
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
