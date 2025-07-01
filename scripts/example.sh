#!/bin/bash

# File-Scrapper Example Usage Script
# This script demonstrates how to use File-Scrapper in different scenarios

echo "📚 File-Scrapper Usage Examples"
echo "==============================="
echo ""

# Navigate to project root
cd "$(dirname "$0")/.."

# Check if executable exists
if [ ! -f "./Sea" ]; then
    echo "❌ Error: Sea executable not found!"
    echo "🔧 Please run './scripts/build.sh' first to build the project"
    exit 1
fi

echo "🎯 Available usage modes:"
echo ""
echo "1. GUI Mode (with file dialogs):"
echo "   ./Sea"
echo "   ./scripts/start.sh"
echo ""
echo "2. Command-line Mode:"
echo "   ./Sea <input_folder> <output.json>"
echo "   ./scripts/start.sh <input_folder> <output.json>"
echo ""

# Create example directories and files
echo "📁 Creating example files for demonstration..."
mkdir -p /tmp/example_apps
touch /tmp/example_apps/calculator.py
touch /tmp/example_apps/text_editor.sh
touch /tmp/example_apps/game.bin
chmod +x /tmp/example_apps/text_editor.sh
chmod +x /tmp/example_apps/game.bin

echo "✅ Created example executable files in /tmp/example_apps/"
echo ""

echo "🚀 Example command-line usage:"
echo "==============================="
echo ""

# Run example
echo "Running: ./Sea /tmp/example_apps example_output.json"
echo ""
./Sea /tmp/example_apps example_output.json

echo ""
echo "📄 Generated output (example_output.json):"
echo "=========================================="
if [ -f "example_output.json" ]; then
    cat example_output.json | jq . 2>/dev/null || cat example_output.json
else
    echo "❌ Output file not found"
fi

echo ""
echo "🧹 Cleaning up example files..."
rm -rf /tmp/example_apps
rm -f example_output.json

echo ""
echo "✅ Example completed!"
echo ""
echo "💡 Tips:"
echo "   - On Linux, the app searches for executable files (with execute permission)"
echo "   - Output includes full paths and generates icon paths for each found executable"
echo "   - Use GUI mode for interactive selection, command-line mode for automation"
