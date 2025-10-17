#!/bin/bash
# Generate keyboard layout diagrams using keymap-drawer
# Based on urob's setup: https://github.com/caksoylar/keymap-drawer

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo "🎨 Generating keyboard layout diagrams..."

# Check if keymap-drawer is installed
if ! command -v keymap &> /dev/null; then
    echo "❌ keymap-drawer not found."
    echo "Install with: pip install keymap-drawer"
    exit 1
fi

cd "$SCRIPT_DIR"

# Generate global SVG with all layers
echo "🖼️  Generating global planck.svg (all layers)..."
keymap draw keymap.yaml > planck.svg

# Generate individual layer SVGs
echo "🖼️  Generating individual layer SVGs..."

for layer in DEF NUM GAMING FN SYS NAV MOUSE MIDI; do
    layer_lower=$(echo "$layer" | tr '[:upper:]' '[:lower:]')
    echo "   - ${layer_lower}-layer.svg"
    keymap draw keymap.yaml -s $layer > ${layer_lower}-layer.svg
done

# Generate PNG if cairosvg or inkscape available
if command -v cairosvg &> /dev/null; then
    echo "📸 Generating PNGs with cairosvg..."
    for svg in *.svg; do
        png="${svg%.svg}.png"
        cairosvg "$svg" -o "$png" -W 2000
    done
elif command -v inkscape &> /dev/null; then
    echo "📸 Generating PNGs with inkscape..."
    for svg in *.svg; do
        png="${svg%.svg}.png"
        inkscape "$svg" -o "$png" -w 2000
    done
else
    echo "⚠️  PNG generation skipped (install cairosvg or inkscape)"
fi

echo ""
echo "✅ Done! Generated files:"
echo "   - planck.svg (all layers)"
for layer in DEF NUM GAMING FN SYS NAV MOUSE MIDI; do
    layer_lower=$(echo "$layer" | tr '[:upper:]' '[:lower:]')
    echo "   - ${layer_lower}-layer.svg"
done
[ -f "planck.png" ] && echo "   + PNGs generated"

echo ""
echo "View: open draw/planck.svg"
