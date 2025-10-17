#!/bin/bash
# Generate keyboard layout diagrams using keymap-drawer
# Based on urob's setup: https://github.com/caksoylar/keymap-drawer

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

echo "🎨 Generating keyboard layout diagrams..."

# Check if keymap-drawer is installed
if ! command -v keymap &> /dev/null; then
    echo "❌ keymap-drawer not found."
    echo "Install with: pip install keymap-drawer"
    exit 1
fi

# Check if qmk CLI is available
if ! command -v qmk &> /dev/null; then
    echo "❌ qmk CLI not found."
    echo "Install with: brew install qmk/qmk/qmk"
    exit 1
fi

# Generate keymap.json from QMK
echo "📝 Generating keymap.json from QMK..."
cd "$PROJECT_ROOT"
QMK_HOME="$PROJECT_ROOT/qmk" qmk c2json -km stphn -kb planck/rev7 keymap/keymap.c > "$SCRIPT_DIR/keymap.json"

# Parse QMK keymap.json and generate YAML representation
echo "📝 Parsing keymap..."
keymap parse -q "$SCRIPT_DIR/keymap.json" -c 12 > "$SCRIPT_DIR/keymap.yaml"

# Generate SVG diagram
echo "🖼️  Generating SVG..."
cat "$SCRIPT_DIR/config.yaml" "$SCRIPT_DIR/keymap.yaml" | keymap draw - > "$SCRIPT_DIR/planck.svg"

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
