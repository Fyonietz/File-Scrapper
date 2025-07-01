#!/bin/bash

# File-Scrapper Linux System Check Script
# This script validates that the system meets all requirements for File-Scrapper

set -e

echo "🔍 File-Scrapper Linux System Check"
echo "=================================="

# Check if we're on Linux
if [[ "$OSTYPE" != "linux-gnu"* ]]; then
    echo "❌ This script is designed for Linux systems"
    exit 1
fi

echo "✅ Running on Linux"

# Check for required commands
REQUIRED_COMMANDS=("cmake" "make" "gcc" "g++" "pkg-config")
MISSING_COMMANDS=()

for cmd in "${REQUIRED_COMMANDS[@]}"; do
    if command -v "$cmd" &> /dev/null; then
        VERSION=$($cmd --version | head -n1)
        echo "✅ $cmd: $VERSION"
    else
        echo "❌ $cmd: Not found"
        MISSING_COMMANDS+=("$cmd")
    fi
done

# Check for GTK3
if pkg-config --exists gtk+-3.0; then
    GTK_VERSION=$(pkg-config --modversion gtk+-3.0)
    echo "✅ GTK3: $GTK_VERSION"
else
    echo "❌ GTK3: Not found"
    MISSING_COMMANDS+=("libgtk-3-dev")
fi

# Check CMake version
if command -v cmake &> /dev/null; then
    CMAKE_VERSION=$(cmake --version | head -n1 | grep -oP '\d+\.\d+\.\d+')
    CMAKE_MAJOR=$(echo $CMAKE_VERSION | cut -d. -f1)
    CMAKE_MINOR=$(echo $CMAKE_VERSION | cut -d. -f2)
    
    if [[ $CMAKE_MAJOR -gt 3 ]] || [[ $CMAKE_MAJOR -eq 3 && $CMAKE_MINOR -ge 10 ]]; then
        echo "✅ CMake version $CMAKE_VERSION meets requirements (>= 3.10)"
    else
        echo "❌ CMake version $CMAKE_VERSION is too old (requires >= 3.10)"
        MISSING_COMMANDS+=("cmake-newer-version")
    fi
fi

# Check if executable exists
if [[ -f "./Sea" ]]; then
    echo "✅ Sea executable exists"
    
    # Check if executable is properly linked
    if ldd ./Sea | grep -q "gtk"; then
        echo "✅ Sea executable is properly linked with GTK3"
    else
        echo "⚠️  Sea executable may not be properly linked with GTK3"
    fi
else
    echo "⚠️  Sea executable not found (run ./scripts/build.sh to build)"
fi

# Check for GUI environment
if [[ -n "$DISPLAY" ]] || [[ -n "$WAYLAND_DISPLAY" ]]; then
    echo "✅ GUI environment detected (required for file dialogs)"
else
    echo "⚠️  No GUI environment detected - file dialogs may not work"
    echo "   Make sure you're running in a desktop environment"
fi

echo ""
echo "=================================="

if [[ ${#MISSING_COMMANDS[@]} -eq 0 ]]; then
    echo "🎉 All requirements met! File-Scrapper should work correctly."
    echo "🚀 Run './scripts/build.sh' to build (if not already built)"
    echo "🚀 Run './scripts/start.sh' to start the application"
else
    echo "❌ Missing requirements:"
    for cmd in "${MISSING_COMMANDS[@]}"; do
        echo "   - $cmd"
    done
    echo ""
    echo "🔧 Run './scripts/install-deps.sh' to install missing dependencies"
fi
