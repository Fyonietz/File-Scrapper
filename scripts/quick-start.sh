#!/bin/bash

# File-Scrapper Linux Quick Start Script
# This script will set up, build, and run File-Scrapper on Linux

set -e

echo "🚀 File-Scrapper Linux Quick Start"
echo "================================="
echo ""

# Check if we're on Linux
if [[ "$OSTYPE" != "linux-gnu"* ]]; then
    echo "❌ This script is designed for Linux systems"
    exit 1
fi

# Navigate to project root
cd "$(dirname "$0")/.."

echo "📋 Step 1: Checking system requirements..."
if ./scripts/check-system.sh | grep -q "All requirements met"; then
    echo "✅ System requirements satisfied"
else
    echo "⚠️  Some requirements are missing"
    echo ""
    read -p "Do you want to install missing dependencies? [Y/n]: " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]] || [[ -z $REPLY ]]; then
        echo "Installing dependencies..."
        ./scripts/install-deps.sh
    else
        echo "Cannot proceed without required dependencies"
        exit 1
    fi
fi

echo ""
echo "🔨 Step 2: Building the project..."
if [[ -f "./Sea" ]]; then
    read -p "Executable already exists. Rebuild? [y/N]: " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        rm -rf build
        ./scripts/build.sh
    else
        echo "✅ Using existing executable"
    fi
else
    ./scripts/build.sh
fi

echo ""
echo "🎉 Step 3: Ready to run!"
echo "🚀 Starting File-Scrapper..."
echo ""
echo "Note: If GUI dialogs don't appear or the app hangs, press Ctrl+C and use:"
echo "      ./Sea /path/to/input/folder /path/to/output.json"
echo ""

# Give user a moment to read
sleep 3

# Run the application with a timeout to prevent hanging
timeout 30s ./scripts/start.sh || {
    echo ""
    echo "⚠️  GUI dialogs timed out or failed."
    echo "🔧 This might happen on some desktop environments (like Wayland compositors)."
    echo ""
    echo "💡 Try command-line mode instead:"
    echo "   ./Sea /path/to/input/folder /path/to/output.json"
    echo ""
    echo "📝 Example:"
    echo "   ./Sea /usr/bin output.json"
    echo "   ./Sea ~/Applications apps.json"
}
