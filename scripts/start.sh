#!/bin/bash

# File-Scrapper Linux Start Script
# This script runs the File-Scrapper application

set -e  # Exit on any error

echo "🚀 Starting File-Scrapper..."

# Navigate to project root
cd "$(dirname "$0")/.."

# Check if executable exists
if [ ! -f "./Sea" ]; then
    echo "❌ Error: Sea executable not found!"
    echo "🔧 Please run './scripts/build.sh' first to build the project"
    exit 1
fi

# Check if executable is executable
if [ ! -x "./Sea" ]; then
    echo "🔧 Making Sea executable..."
    chmod +x ./Sea
fi

# Check if command line arguments are provided
if [ $# -eq 2 ]; then
    echo "📂 Using command-line arguments:"
    echo "   Input folder: $1"
    echo "   Output file: $2"
    ./Sea "$1" "$2"
elif [ $# -eq 0 ]; then
    echo "📂 Launching File-Scrapper with GUI dialogs..."
    echo "   (If dialogs don't appear, use: ./Sea <input_folder> <output.json>)"
    ./Sea
else
    echo "❌ Error: Invalid number of arguments"
    echo "Usage: $0 [input_folder] [output.json]"
    echo "  With no arguments: Uses GUI file dialogs"
    echo "  With 2 arguments: Uses command-line mode"
    exit 1
fi

echo "✅ File-Scrapper finished execution"
