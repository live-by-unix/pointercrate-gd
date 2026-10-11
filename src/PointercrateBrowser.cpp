#include "PointercrateBrowser.hpp"
#include <Geode/Geode.hpp>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <shellapi.h>
#elif defined(__APPLE__)
#include <TargetConditionals.h>
#endif

using namespace geode::prelude;

namespace pointercrate {

PointercrateBrowser& PointercrateBrowser::get() {
    static PointercrateBrowser instance;
    return instance;
}

std::string PointercrateBrowser::getURL(DemonlistType type) const {
    switch (type) {
        case DemonlistType::Pointercrate:
            return "https://pointercrate.com/";
        case DemonlistType::Pemonlist:
            return "https://pemonlist.com/";
        case DemonlistType::AREDL:
            return "https://aredl.net/";
        default:
            return "https://pointercrate.com/";
    }
}

void PointercrateBrowser::openBrowser(DemonlistType type) {
    const std::string url = getURL(type);
    const std::string name = type == DemonlistType::Pointercrate ? "Pointercrate" :
                            type == DemonlistType::Pemonlist ? "Pemonlist" : "AREDL";
    log::info("Opening {} browser: {}", name, url);
    openURL(url);
}

void PointercrateBrowser::closeBrowser() {
    // For external browser, we don't need to do anything
    // The browser is managed by the OS
    log::debug("Browser close requested (external browser)");
}

void PointercrateBrowser::openURL(const std::string& url) {
#if defined(_WIN32) || defined(_WIN64)
    openBrowserWindows(url);
#elif defined(__APPLE__) && TARGET_OS_MAC
    openBrowserMacOS(url);
#elif defined(__APPLE__) && TARGET_OS_IPHONE
    openBrowserIOS(url);
#elif defined(__ANDROID__)
    openBrowserAndroid(url);
#else
    log::warn("Platform not supported for browser opening");
#endif
}

#if defined(_WIN32) || defined(_WIN64)
void PointercrateBrowser::openBrowserWindows(const std::string& url) {
    ShellExecuteA(nullptr, "open", url.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
    log::info("Opened browser on Windows");
}
#endif

#if defined(__APPLE__) && TARGET_OS_MAC
void PointercrateBrowser::openBrowserMacOS(const std::string& url) {
    std::string command = "open \"" + url + "\"";
    system(command.c_str());
    log::info("Opened browser on macOS");
}
#endif

#if defined(__APPLE__) && TARGET_OS_IPHONE
void PointercrateBrowser::openBrowserIOS(const std::string& url) {
    log::warn("iOS browser opening requires Objective-C++ implementation");
}
#endif

#if defined(__ANDROID__)
void PointercrateBrowser::openBrowserAndroid(const std::string& url) {
    log::warn("Android browser opening requires JNI implementation");
}
#endif

} // namespace pointercrate
