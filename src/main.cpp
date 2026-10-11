#include <Geode/Geode.hpp>
#include "PointercrateBrowser.hpp"
#include "DemonlistMenu.hpp"

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>

class $modify(PointercrateMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		log::debug("Demonlist Browser mod loaded - adding button to main menu");

		// Add single button to bottom menu
		auto menu = this->getChildByID("bottom-menu");
		if (menu) {
			// Demonlist Browser button - use the working star button
			auto demonlistButton = CCMenuItemSpriteExtra::create(
				CCSprite::createWithSpriteFrameName("GJ_starBtn_001.png"),
				this,
				menu_selector(PointercrateMenuLayer::onDemonlistButton)
			);
			demonlistButton->setID("demonlist-button"_spr);
			menu->addChild(demonlistButton);

			menu->updateLayout();
		} else {
			log::warn("Failed to find bottom-menu node");
		}

		return true;
	}

	void onDemonlistButton(CCObject*) {
		log::info("Demonlist Browser button clicked");
		pointercrate::DemonlistMenu::create()->show();
	}
};
