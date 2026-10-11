#include <Geode/Geode.hpp>
#include "PointercrateBrowser.hpp"

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>

class $modify(PointercrateMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		log::debug("Pointercrate mod loaded - adding button to main menu");

		// Create a button with a demon-like icon
		auto pointercrateButton = CCMenuItemSpriteExtra::create(
			CCSprite::createWithSpriteFrameName("GJ_demonBtn_001.png"),
			this,
			menu_selector(PointercrateMenuLayer::onPointercrateButton)
		);

		// Add button to bottom menu
		auto menu = this->getChildByID("bottom-menu");
		if (menu) {
			menu->addChild(pointercrateButton);
			pointercrateButton->setID("pointercrate-button"_spr);
			menu->updateLayout();
		} else {
			log::warn("Failed to find bottom-menu node");
		}

		return true;
	}

	void onPointercrateButton(CCObject*) {
		log::info("Pointercrate button clicked");
		pointercrate::PointercrateBrowser::get().openBrowser();
	}
};
