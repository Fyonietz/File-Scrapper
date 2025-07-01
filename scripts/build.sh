#!/bin/bash

# File-Scrapper Linux Build Script
# This script builds the project using CMake and Make

set -e  # Exit on any error

echo "🔧 Building File-Scrapper for Linux..."

# Navigate to project root
cd "$(dirname "$0")/.."

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
    mkdir build
fi

# Configure with CMake
echo "📋 Configuring with CMake..."
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

# Build the project
echo "🔨 Building project..."
cd build
make -j$(nproc)

# Go back to project root
cd ..

echo "✅ Build completed successfully!"
echo "📁 Executable location: ./Sea"
echo "🚀 Run './scripts/start.sh' to start the application"
