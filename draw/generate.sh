#!/bin/bash
# Generate keyboard layout diagrams using keymap-drawer
# Based on urob's setup: https://github.com/caksoylar/keymap-drawer

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
KEYMAP_FILE="../keymap/keymap.c"

echo "🎨 Generating keyboard layout diagrams..."

# Check if keymap-drawer is installed
if ! command -v keymap &> /dev/null; then
    echo "❌ keymap-drawer not found. Installing..."
    echo "Run: pip install keymap-drawer"
    exit 1
fi

# Parse QMK keymap and generate YAML representation
echo "📝 Parsing keymap..."
keymap parse -c "$SCRIPT_DIR/config.yaml" -q "$KEYMAP_FILE" > "$SCRIPT_DIR/keymap.yaml"

# Generate SVG diagram
echo "🖼️  Generating SVG..."
keymap draw "$SCRIPT_DIR/keymap.yaml" -c "$SCRIPT_DIR/config.yaml" > "$SCRIPT_DIR/planck.svg"

# Generate PNG (requires cairosvg or inkscape)
if command -v cairosvg &> /dev/null; then
    echo "📸 Generating PNG..."
    cairosvg "$SCRIPT_DIR/planck.svg" -o "$SCRIPT_DIR/planck.png" -W 2000
elif command -v inkscape &> /dev/null; then
    echo "📸 Generating PNG (using inkscape)..."
    inkscape "$SCRIPT_DIR/planck.svg" -o "$SCRIPT_DIR/planck.png" -w 2000
else
    echo "⚠️  PNG generation skipped (install cairosvg or inkscape)"
fi

echo "✅ Done! Generated files:"
echo "   - keymap.yaml   (parsed keymap)"
echo "   - planck.svg    (vector diagram)"
[ -f "$SCRIPT_DIR/planck.png" ] && echo "   - planck.png    (raster image)"

echo ""
echo "View the SVG: open draw/planck.svg"
