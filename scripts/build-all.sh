#!/bin/bash

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
DIST_DIR="$PROJECT_ROOT/dist"

# Parse arguments
TARGET=""
CLEAN_BUILD=false

while [[ $# -gt 0 ]]; do
    case $1 in
        --target)
            TARGET="$2"
            shift 2
            ;;
        --clean)
            CLEAN_BUILD=true
            shift
            ;;
        -h|--help)
            echo "Usage: $0 [--target TARGET] [--clean]"
            echo ""
            echo "Targets:"
            echo "  all          Build all supported platforms for current OS"
            echo "  macos-arm64  Build for macOS ARM64"
            echo "  macos-x86_64 Build for macOS x86_64"
            echo "  macos        Build universal macOS binary"
            echo "  windows-x86_64  Build for Windows x86_64 (requires cross-compilation)"
            echo "  windows-x86     Build for Windows x86 (requires cross-compilation)"
            echo "  android-arm64-v8a  Build for Android ARM64 (requires Android NDK)"
            echo "  android-armeabi-v7a Build for Android ARMv7 (requires Android NDK)"
            echo ""
            echo "Options:"
            echo "  --clean    Clean build directories before building"
            echo "  --help     Show this help message"
            exit 0
            ;;
        *)
            echo -e "${RED}Unknown option: $1${NC}"
            exit 1
            ;;
    esac
done

# Detect current platform
detect_platform() {
    case "$(uname -s)" in
        Darwin)
            if [[ "$(uname -m)" == "arm64" ]]; then
                echo "macos-arm64"
            else
                echo "macos-x86_64"
            fi
            ;;
        Linux*)
            echo "linux"
            ;;
        MINGW*|MSYS*|CYGWIN*)
            echo "windows"
            ;;
        *)
            echo "unknown"
            ;;
    esac
}

CURRENT_PLATFORM=$(detect_platform)

# Clean build directories if requested
if [ "$CLEAN_BUILD" = true ]; then
    echo -e "${BLUE}Cleaning build directories...${NC}"
    rm -rf "$PROJECT_ROOT/build"
    rm -rf "$PROJECT_ROOT/build-"*
fi

# Create dist directory
mkdir -p "$DIST_DIR"

# Build function
build_platform() {
    local platform=$1
    local geode_platform=$2

    echo -e "${BLUE}Building for $platform...${NC}"

    # Clean previous build for this platform
    rm -rf "$PROJECT_ROOT/build"
    rm -rf "$PROJECT_ROOT/build-"*

    # Build using geode CLI
    if [ -n "$geode_platform" ]; then
        cd "$PROJECT_ROOT"
        cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo || {
            echo -e "${RED}Failed to configure for $platform${NC}"
            return 1
        }
        cmake --build build --config RelWithDebInfo || {
            echo -e "${RED}Failed to build for $platform${NC}"
            return 1
        }
    else
        cd "$PROJECT_ROOT"
        cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo || {
            echo -e "${RED}Failed to configure for current platform${NC}"
            return 1
        }
        cmake --build build --config RelWithDebInfo || {
            echo -e "${RED}Failed to build for current platform${NC}"
            return 1
        }
    fi

    # Find the generated .geode file
    local geode_file
    geode_file=$(find "$PROJECT_ROOT/build" -name "*.geode" 2>/dev/null | head -n 1)

    if [ -z "$geode_file" ]; then
        # Try build directories with platform suffix
        geode_file=$(find "$PROJECT_ROOT/build-"* -name "*.geode" 2>/dev/null | head -n 1)
    fi

    if [ -z "$geode_file" ]; then
        echo -e "${RED}No .geode file found for $platform${NC}"
        return 1
    fi

    # Copy to dist with proper name
    local target_name="pointercrate-gd-$platform.geode"
    cp "$geode_file" "$DIST_DIR/$target_name"

    # Verify file exists and is not empty
    if [ ! -s "$DIST_DIR/$target_name" ]; then
        echo -e "${RED}Artifact $target_name is empty or does not exist${NC}"
        return 1
    fi

    echo -e "${GREEN}✓ Built $platform: $target_name${NC}"
    return 0
}

# Build for current platform (macOS universal)
build_current_platform() {
    echo -e "${BLUE}Building for current platform...${NC}"

    # Clean previous build
    rm -rf "$PROJECT_ROOT/build"
    rm -rf "$PROJECT_ROOT/build-"*

    cd "$PROJECT_ROOT"
    cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo || {
        echo -e "${RED}Failed to configure for current platform${NC}"
        return 1
    }
    cmake --build build --config RelWithDebInfo || {
        echo -e "${RED}Failed to build for current platform${NC}"
        return 1
    }

    # Find the generated .geode file
    local geode_file
    geode_file=$(find "$PROJECT_ROOT/build" -name "*.geode" 2>/dev/null | head -n 1)

    if [ -z "$geode_file" ]; then
        echo -e "${RED}No .geode file found${NC}"
        return 1
    fi

    # Determine platform name for artifact
    local platform_name
    case "$(uname -s)" in
        Darwin)
            if [[ "$(uname -m)" == "arm64" ]]; then
                platform_name="macos-arm64"
            else
                platform_name="macos-x86_64"
            fi
            ;;
        MINGW*|MSYS*|CYGWIN*)
            platform_name="windows-x86_64"
            ;;
        *)
            platform_name="unknown"
            ;;
    esac

    # Copy to dist with proper name
    local target_name="pointercrate-gd-$platform_name.geode"
    cp "$geode_file" "$DIST_DIR/$target_name"

    # Verify file exists and is not empty
    if [ ! -s "$DIST_DIR/$target_name" ]; then
        echo -e "${RED}Artifact $target_name is empty or does not exist${NC}"
        return 1
    fi

    echo -e "${GREEN}✓ Built current platform: $target_name${NC}"
    return 0
}

# Main build logic
if [ -z "$TARGET" ] || [ "$TARGET" = "all" ]; then
    # Build for current platform only by default
    echo -e "${BLUE}Building for current platform: $CURRENT_PLATFORM${NC}"

    case "$CURRENT_PLATFORM" in
        macos-arm64|macos-x86_64|macos)
            build_current_platform
            ;;
        windows)
            echo -e "${YELLOW}Windows builds should be run on Windows${NC}"
            echo -e "${YELLOW}Use the geode CLI on Windows to build Windows targets${NC}"
            ;;
        linux)
            echo -e "${YELLOW}Linux builds are for cross-compilation to Windows${NC}"
            echo -e "${YELLOW}See Geode docs for cross-compilation setup${NC}"
            ;;
        *)
            echo -e "${RED}Unknown platform: $CURRENT_PLATFORM${NC}"
            exit 1
            ;;
    esac
else
    # Build specific target
    case "$TARGET" in
        macos-arm64|macos-x86_64|macos)
            echo -e "${YELLOW}Note: macOS builds universal binaries by default on macOS${NC}"
            echo -e "${YELLOW}Building for current macOS architecture...${NC}"
            build_current_platform
            ;;
        windows-x86_64)
            echo -e "${YELLOW}Windows x86_64 builds require cross-compilation or building on Windows${NC}"
            echo -e "${YELLOW}On Windows, run: geode build -p windows${NC}"
            echo -e "${YELLOW}On Linux with cross-compilation setup, run: geode build -p windows${NC}"
            ;;
        windows-x86)
            echo -e "${YELLOW}Windows x86 builds are not supported by current Geode${NC}"
            echo -e "${YELLOW}Use windows platform which builds for x86_64${NC}"
            ;;
        android-arm64-v8a)
            if [ -z "$ANDROID_NDK_ROOT" ]; then
                echo -e "${RED}ANDROID_NDK_ROOT environment variable not set${NC}"
                echo -e "${YELLOW}Install Android NDK and set ANDROID_NDK_ROOT${NC}"
                exit 1
            fi
            build_platform "android-arm64-v8a" "android64"
            ;;
        android-armeabi-v7a)
            if [ -z "$ANDROID_NDK_ROOT" ]; then
                echo -e "${RED}ANDROID_NDK_ROOT environment variable not set${NC}"
                echo -e "${YELLOW}Install Android NDK and set ANDROID_NDK_ROOT${NC}"
                exit 1
            fi
            build_platform "android-armeabi-v7a" "android32"
            ;;
        *)
            echo -e "${RED}Unknown target: $TARGET${NC}"
            exit 1
            ;;
    esac
fi

# Generate checksums for all artifacts
echo -e "${BLUE}Generating SHA-256 checksums...${NC}"
cd "$DIST_DIR"
if ls *.geode 1> /dev/null 2>&1; then
    sha256sum *.geode > SHA256SUMS.txt 2>/dev/null || shasum -a 256 *.geode > SHA256SUMS.txt
    echo -e "${GREEN}✓ Generated SHA256SUMS.txt${NC}"
else
    echo -e "${YELLOW}No .geode files found in dist directory${NC}"
fi

# Print summary
echo -e "${BLUE}=== Build Summary ===${NC}"
echo -e "${BLUE}Artifacts in $DIST_DIR:${NC}"
ls -lh "$DIST_DIR"/*.geode 2>/dev/null || echo -e "${YELLOW}No artifacts built${NC}"
if [ -f "$DIST_DIR/SHA256SUMS.txt" ]; then
    echo -e "${BLUE}Checksums:${NC}"
    cat "$DIST_DIR/SHA256SUMS.txt"
fi

echo -e "${GREEN}Build complete!${NC}"
