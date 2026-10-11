# Security Policy

## Supported Versions

Currently supported versions with security updates:

| Version | Supported          |
| ------- | ------------------ |
| 1.0.x   | :white_check_mark: |

## Reporting a Vulnerability

If you discover a security vulnerability, please report it responsibly.

### How to Report

1. **Do not** create a public issue
2. Send an email to the maintainers (via GitHub private issue if available)
3. Include:
   - A description of the vulnerability
   - Steps to reproduce
   - Potential impact
   - Suggested fix (if known)

### What to Expect

- We will acknowledge receipt within 48 hours
- We will provide a detailed response within 7 days
- We will work with you to understand and fix the issue
- We will coordinate release of the fix

### Security Best Practices

- Never commit secrets or API keys
- Use environment variables for sensitive configuration
- Validate all user input
- Keep dependencies updated
- Follow the principle of least privilege

## Known Security Considerations

### External Browser Integration

The current implementation opens the Pointercrate website in the system's default browser. This is a standard practice and considered safe. However:

- The website content is controlled by Pointercrate, not this mod
- Users should ensure they trust the Pointercrate website
- The mod does not expose any native APIs to the website

### Future Embedded Browser Implementation

When implementing embedded browser rendering (CEF integration):

- Implement proper navigation restrictions
- Validate and sanitize all content
- Do not expose unrestricted native bindings
- Implement same-origin policy where applicable
- Keep the browser engine updated

## Dependency Security

This mod depends on:
- Geode SDK
- Cocos2d-x (via Geometry Dash)
- Standard C++ libraries

We will:
- Monitor Geode SDK security advisories
- Update dependencies promptly when vulnerabilities are disclosed
- Document any security-related changes in the changelog

## Receiving Security Updates

Users should:
- Keep the mod updated to the latest version
- Monitor the repository for security advisories
- Report any suspicious behavior

## Disclaimer

This mod is provided as-is without warranty. Users are responsible for:
- Understanding the risks of using third-party mods
- Keeping their game and system secure
- Backing up their data before installing mods
