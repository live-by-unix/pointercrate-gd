# Contributing to pointercrate-gd

Thank you for your interest in contributing to pointercrate-gd! This document provides guidelines and instructions for contributing to the project.

## Code of Conduct

- Be respectful and inclusive
- Provide constructive feedback
- Focus on what is best for the community
- Show empathy towards other community members

## How to Contribute

### Reporting Bugs

Before creating bug reports, please check the existing issues to avoid duplicates. When creating a bug report, include:

- A clear and descriptive title
- Steps to reproduce the issue
- Expected behavior
- Actual behavior
- Screenshots or logs if applicable
- Your platform (Windows/macOS/Android) and Geometry Dash version
- Geode version

### Suggesting Enhancements

Enhancement suggestions are welcome! Please include:

- A clear and descriptive title
- A detailed description of the enhancement
- Explain why this enhancement would be useful
- Provide examples if applicable

### Pull Requests

1. Fork the repository
2. Create a branch for your feature or bugfix
3. Make your changes following the code style guidelines
4. Test your changes thoroughly
5. Commit your changes with clear messages
6. Push to your fork and submit a pull request

#### Branch Naming

- Use `feature/` for new features: `feature/embedded-browser`
- Use `fix/` for bug fixes: `fix/crash-on-startup`
- Use `docs/` for documentation: `docs/update-readme`

#### Commit Messages

Follow conventional commits format:
- `feat: add embedded browser support`
- `fix: resolve crash when clicking button`
- `docs: update installation instructions`
- `refactor: simplify browser initialization`

## Development Setup

### Prerequisites

- Geode CLI installed
- Geode SDK installed
- CMake 3.21+
- C++23 compatible compiler
- Android NDK (for Android builds)

### Building

```bash
# Clone the repository
git clone https://github.com/live-by-unix/pointercrate-gd.git
cd pointercrate-gd

# Build for current platform
./scripts/build-all.sh

# Or use geode CLI directly
geode build
```

### Testing

Test your changes on:
- Multiple platforms if possible
- Different Geometry Dash versions if applicable
- Various screen sizes and resolutions

## Code Style

- Use C++23 features where appropriate
- Follow existing code formatting
- Use meaningful variable and function names
- Add comments for complex logic
- Keep functions focused and concise

## Project Structure

```
pointercrate-gd/
├── src/                      # Source code
│   ├── main.cpp             # Main mod entry point
│   ├── PointercrateBrowser.hpp/cpp  # Browser abstraction
│   └── platform/            # Platform-specific code
├── scripts/                 # Build and utility scripts
├── .github/workflows/        # CI/CD workflows
└── assets/                  # Mod assets
```

## What We're Looking For

### High Priority

- Embedded browser rendering implementation (CEF integration)
- Android JNI implementation for browser opening
- iOS Objective-C++ implementation for browser opening
- Bug fixes and stability improvements

### Medium Priority

- UI improvements and polish
- Additional features (navigation controls, history, etc.)
- Performance optimizations
- Better error handling

### Low Priority

- Documentation improvements
- Code refactoring
- Minor UI tweaks

## Getting Help

If you need help contributing:
- Open an issue with the question label
- Join the Geode Discord: https://discord.gg/9e43WMKzhp
- Check the Geode documentation: https://docs.geode-sdk.org/

## License

By contributing, you agree that your contributions will be licensed under the MIT License.
