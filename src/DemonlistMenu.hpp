#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

namespace pointercrate {

class DemonlistMenu : public FLAlertLayer {
public:
    static DemonlistMenu* create();

    void onPointercrate(CCObject* sender);
    void onPemonlist(CCObject* sender);
    void onAredl(CCObject* sender);

private:
    bool init() override;
};

} // namespace pointercrate
