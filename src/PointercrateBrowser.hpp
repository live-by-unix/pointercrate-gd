#pragma once

#include <Geode/Geode.hpp>
#include <string>

#if defined(__APPLE__)
#include <TargetConditionals.h>
#endif

namespace pointercrate {

enum class DemonlistType {
    Pointercrate,
    Pemonlist,
    AREDL
};

class PointercrateBrowser {
public:
    static PointercrateBrowser& get();

    void openBrowser(DemonlistType type = DemonlistType::Pointercrate);
    void closeBrowser();

    std::string getURL(DemonlistType type) const;

private:
    PointercrateBrowser() = default;
    ~PointercrateBrowser() = default;

    void openURL(const std::string& url);

#if defined(_WIN32) || defined(_WIN64)
    void openBrowserWindows(const std::string& url);
#elif defined(__APPLE__) && TARGET_OS_MAC
    void openBrowserMacOS(const std::string& url);
#elif defined(__APPLE__) && TARGET_OS_IPHONE
    void openBrowserIOS(const std::string& url);
#elif defined(__ANDROID__)
    void openBrowserAndroid(const std::string& url);
#endif
};

} // namespace pointercrate
