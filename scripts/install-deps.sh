#!/bin/bash

# File-Scrapper Linux Dependencies Installation Script
# This script installs the required dependencies for building File-Scrapper on Linux

set -e  # Exit on any error

echo "🔧 Installing File-Scrapper dependencies for Linux..."

# Detect the Linux distribution
if [ -f /etc/os-release ]; then
    . /etc/os-release
    OS=$NAME
else
    echo "❌ Cannot detect Linux distribution"
    exit 1
fi

echo "📋 Detected OS: $OS"

# Install dependencies based on the distribution
case "$OS" in
    *"Ubuntu"*|*"Debian"*)
        echo "📦 Installing dependencies for Ubuntu/Debian..."
        sudo apt update
        sudo apt install -y cmake build-essential libgtk-3-dev pkg-config
        ;;
    *"Fedora"*|*"Red Hat"*|*"CentOS"*)
        echo "📦 Installing dependencies for Fedora/RHEL/CentOS..."
        if command -v dnf &> /dev/null; then
            sudo dnf install -y cmake gcc-c++ gtk3-devel pkgconfig
        else
            sudo yum install -y cmake gcc-c++ gtk3-devel pkgconfig
        fi
        ;;
    *"Arch"*)
        echo "📦 Installing dependencies for Arch Linux..."
        sudo pacman -S --noconfirm cmake gcc gtk3 pkgconf
        ;;
    *"openSUSE"*)
        echo "📦 Installing dependencies for openSUSE..."
        sudo zypper install -y cmake gcc-c++ gtk3-devel pkg-config
        ;;
    *)
        echo "⚠️  Unknown distribution: $OS"
        echo "📋 Please install the following dependencies manually:"
        echo "   - cmake (version 3.10 or higher)"
        echo "   - gcc/g++ compiler"
        echo "   - GTK3 development libraries"
        echo "   - pkg-config"
        echo ""
        echo "🔍 Common package names:"
        echo "   - cmake build-essential libgtk-3-dev pkg-config (Ubuntu/Debian)"
        echo "   - cmake gcc-c++ gtk3-devel pkgconfig (Fedora/RHEL)"
        echo "   - cmake gcc gtk3 pkgconf (Arch)"
        exit 1
        ;;
esac

echo "✅ Dependencies installed successfully!"
echo "🚀 You can now run './scripts/build.sh' to build the project"
