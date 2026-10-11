# Demonlist Browser for Geometry Dash

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Geode](https://img.shields.io/badge/Geode-5.9.0-blue)](https://geode-sdk.org/)

A Geometry Dash mod that adds three buttons to the main menu for quick access to the most popular demonlists:

- **Pointercrate**: The original Geometry Dash Demonlist
- **Pemonlist**: The Platformer Demonlist
- **AREDL**: All Rated Extreme Demons List

## Features

- **Multiple Demonlists**: Access Pointercrate, Pemonlist, and AREDL from the main menu
- **Quick Access**: Three icon buttons in the bottom menu for instant demonlist access
- **Cross-Platform**: Supports Windows, macOS (Apple Silicon and Intel), and Android
- **Real Websites**: Uses the live demonlist websites, not static mockups
- **CEF Foundation**: Includes structure for future embedded browser rendering

## Current Implementation

**Note**: The current implementation opens demonlist websites in your system's default browser (Chrome, Safari, Edge, etc.) rather than rendering them embedded within the game. This provides reliable functionality across all platforms while work continues on true embedded browser rendering.

See [EMBEDDED_BROWSER_IMPLEMENTATION.md](EMBEDDED_BROWSER_IMPLEMENTATION.md) for details on the roadmap for embedded browser rendering using CEF (Chromium Embedded Framework).

## Supported Platforms

- **Windows**: x86_64
- **macOS**: Universal binary (Apple Silicon and Intel)
- **Android**: arm64-v8a and armeabi-v7a (with NDK)

*Note: Windows x86 (Win32) is not supported by the current Geode SDK.*

## Installation

### Via Geode

1. Ensure you have Geode installed for Geometry Dash
2. Download the appropriate `.geode` file for your platform from the [Releases](https://github.com/live-by-unix/pointercrate-gd/releases) page
3. Place the `.geode` file in your Geode mods folder

### Available Artifacts

- **macOS ARM64**: `pointercrate-gd-macos-arm64.geode` (Available in v1.1.0)
- **Windows x86_64**: Build via CI or on Windows (not in v1.1.0)
- **Android**: Build via CI with Android NDK (not in v1.1.0)

*Note: v1.1.0 includes only the macOS ARM64 artifact. Other platforms will be added in future releases via CI builds.*

### Manual Installation

1. Download the `.geode` file for your platform
2. Copy it to:
   - **Windows**: `Geometry Dash/geode/mods/`
   - **macOS**: `~/Library/Application Support/Geometry Dash/geode/mods/`
   - **Android**: `/storage/emulated/0/Android/media/com.geode.launcher/game/geode/mods/`

## Building from Source

### Prerequisites

- Geode CLI: https://github.com/geode-sdk/cli
- Geode SDK: https://github.com/geode-sdk/geode
- CMake 3.21+
- C++23 compatible compiler
- Android NDK (for Android builds)

### Setup

1. Install Geode CLI and SDK:
   ```bash
   brew install geode-sdk/geode/geode-cli  # macOS
   geode sdk install
   ```

2. Clone the repository:
   ```bash
   git clone https://github.com/live-by-unix/pointercrate-gd.git
   cd pointercrate-gd
   ```

### Building

Build for your current platform:
```bash
geode build
```

Build for specific platforms:
```bash
geode build -p windows64    # Windows x86_64
geode build -p windows32    # Windows x86
geode build -p macos64      # macOS ARM64/x86_64 universal
geode build -p android64    # Android arm64-v8a
geode build -p android32    # Android armeabi-v7a
```

Or use the unified build script:
```bash
./scripts/build-all.sh --target all
```

## Development

This mod uses the official Geode SDK. See the [Geode Documentation](https://docs.geode-sdk.org/) for more information on mod development.

### Project Structure

```
pointercrate-gd/
├── src/                    # Source code
│   ├── main.cpp           # Main mod entry point
│   ├── MenuButton.hpp/cpp # Menu button implementation
│   ├── PointercrateBrowser.hpp/cpp # Browser abstraction
│   ├── BrowserPanel.hpp/cpp # Browser UI panel
│   └── platform/          # Platform-specific implementations
│       ├── windows/
│       ├── macos/
│       └── android/
├── assets/                # Mod assets
├── scripts/               # Build and utility scripts
└── .github/workflows/     # CI/CD workflows
```

## Contributing

Contributions are welcome! Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on our code of conduct and the process for submitting pull requests.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- [Geode SDK](https://github.com/geode-sdk/geode) - The mod loader and SDK
- [Pointercrate](https://pointercrate.com/) - The Demonlist website
- The Geometry Dash modding community

## Disclaimer

This mod is not affiliated with RobTop Games or Pointercrate. Use at your own risk.
