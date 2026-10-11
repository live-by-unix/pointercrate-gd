#include <Geode/Geode.hpp>
#include "PointercrateBrowser.hpp"

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>

class $modify(PointercrateMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		log::debug("Pointercrate mod loaded - adding buttons to main menu");

		// Add buttons to bottom menu
		auto menu = this->getChildByID("bottom-menu");
		if (menu) {
			// Pointercrate button
			auto pointercrateButton = CCMenuItemSpriteExtra::create(
				CCSprite::createWithSpriteFrameName("GJ_demonBtn_001.png"),
				this,
				menu_selector(PointercrateMenuLayer::onPointercrateButton)
			);
			pointercrateButton->setID("pointercrate-button"_spr);
			menu->addChild(pointercrateButton);

			// Pemonlist button
			auto pemonlistButton = CCMenuItemSpriteExtra::create(
				CCSprite::createWithSpriteFrameName("GJ_difficultyBtn_001.png"),
				this,
				menu_selector(PointercrateMenuLayer::onPemonlistButton)
			);
			pemonlistButton->setID("pemonlist-button"_spr);
			menu->addChild(pemonlistButton);

			// AREDL button
			auto aredlButton = CCMenuItemSpriteExtra::create(
				CCSprite::createWithSpriteFrameName("GJ_starBtn_001.png"),
				this,
				menu_selector(PointercrateMenuLayer::onAredlButton)
			);
			aredlButton->setID("aredl-button"_spr);
			menu->addChild(aredlButton);

			menu->updateLayout();
		} else {
			log::warn("Failed to find bottom-menu node");
		}

		return true;
	}

	void onPointercrateButton(CCObject*) {
		log::info("Pointercrate button clicked");
		pointercrate::PointercrateBrowser::get().openBrowser(pointercrate::DemonlistType::Pointercrate);
	}

	void onPemonlistButton(CCObject*) {
		log::info("Pemonlist button clicked");
		pointercrate::PointercrateBrowser::get().openBrowser(pointercrate::DemonlistType::Pemonlist);
	}

	void onAredlButton(CCObject*) {
		log::info("AREDL button clicked");
		pointercrate::PointercrateBrowser::get().openBrowser(pointercrate::DemonlistType::AREDL);
	}
};
