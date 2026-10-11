# Embedded Browser Implementation Roadmap

## Current Implementation

The current implementation uses the platform's default external browser as a fallback. When the user clicks the Pointercrate button, it opens the Pointercrate website in their system browser (Chrome, Safari, Edge, etc.).

This approach:
- ✅ Works reliably on all platforms
- ✅ Requires no additional dependencies
- ✅ Is simple to maintain
- ❌ Does not provide an in-game embedded experience
- ❌ Switches context away from Geometry Dash

## Future Embedded Rendering Implementation

To achieve true embedded browser rendering within the Geometry Dash game window, the following implementation path is recommended:

### Research Findings

Based on research into embedded browser rendering in game engines:

1. **Cocos2d-x WebView**: The built-in WebView in Cocos2d-x (which Geometry Dash uses) is a system overlay that renders above all game content, not truly embedded within the scene.

2. **Chromium Embedded Framework (CEF)**: CEF supports off-screen rendering (OSR) which can render web content to textures that can be displayed in-game. This is the most viable path for true embedded rendering.

3. **CEG with GPU Acceleration**: Modern CEF supports GPU-accelerated off-screen rendering using shared textures on Windows (D3D11) and OpenGL on other platforms.

### Recommended Implementation Path

#### Phase 1: CEF Integration

1. **Add CEF as a dependency**
   - Integrate CEF binaries into the mod
   - Package CEF runtime with the .geode file
   - Handle platform-specific CEF distributions

2. **Implement Off-Screen Rendering Handler**
   - Create a CEF render handler that receives frame callbacks
   - Implement `OnPaint` (software) or `OnAcceleratedPaint` (GPU) callbacks
   - Convert CEF frames to Cocos2d-x textures

3. **Texture Integration**
   - Create a Cocos2d-x custom node that displays the browser texture
   - Handle texture updates on the game thread
   - Manage texture lifecycle and memory

#### Phase 2: Input Handling

1. **Mouse/Touch Forwarding**
   - Capture input events on the browser node
   - Forward coordinates to CEF browser instance
   - Handle clicks, scrolling, and keyboard input

2. **Focus Management**
   - Handle focus acquisition/loss
   - Manage keyboard text input
   - Handle shortcuts and special keys

#### Phase 3: Platform-Specific Optimizations

**Windows**:
- Use D3D11 shared textures for zero-copy rendering
- Leverage WebView2 runtime if available as an alternative

**macOS**:
- Use Metal or OpenGL for texture sharing
- Support both Apple Silicon and Intel architectures

**Android**:
- Use Android WebView with GL texture rendering
- Implement JNI bridge for native WebView integration
- Handle touch events and gestures correctly

**iOS**:
- Use WKWebView with OpenGL texture rendering
- Implement Objective-C++ bridge
- Handle iOS-specific touch and lifecycle events

#### Phase 4: Lifecycle Management

1. **Browser Initialization**
   - Initialize CEF subprocess
   - Handle async initialization
   - Show loading state during startup

2. **Resource Cleanup**
   - Properly shutdown CEF browser
   - Release textures and GPU resources
   - Handle game shutdown gracefully

3. **Error Handling**
   - Handle CEF initialization failures
   - Provide fallback to external browser
   - Show user-friendly error messages

### Technical Challenges

1. **Dependency Size**: CEF adds significant binary size (~50-100MB)
2. **Thread Safety**: CEF runs on multiple threads; synchronization with game thread is critical
3. **Graphics Context**: Must properly integrate with Geometry Dash's graphics context
4. **Platform Variations**: Each platform has different GPU APIs and texture sharing mechanisms
5. **Memory Usage**: Browser engines are memory-intensive; must monitor and limit usage

### Reference Projects

- [godot-cef](https://github.com/dsh0416/godot-cef): CEF integration for Godot with texture rendering
- [cef-mixer](https://github.com/mediabuff/cef-mixer): CEF off-screen rendering demo
- [cocos2dx-cef-wrapper](https://github.com/woody006/cocos2dx-cef-wrapper): CEF wrapper for Cocos2d-x

### Implementation Priority

1. **High Priority**: Windows CEF integration (largest user base)
2. **Medium Priority**: macOS CEF integration
3. **Lower Priority**: Android/iOS WebView integration (more complex, smaller user base)

### Timeline Estimate

- Research and prototyping: 2-3 weeks
- Windows implementation: 3-4 weeks
- macOS implementation: 2-3 weeks
- Android/iOS implementation: 4-6 weeks
- Testing and optimization: 2-3 weeks

**Total**: 13-19 weeks for full embedded rendering implementation

## Conclusion

The current external browser implementation provides immediate functionality while the embedded rendering path is being developed. The roadmap above provides a clear path to achieving the goal of true in-game embedded browser rendering.
