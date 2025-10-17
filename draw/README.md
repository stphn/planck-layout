# Keyboard Layout Diagrams

This directory contains tools for visualizing the Planck keyboard layout.

## Quick Terminal View

The fastest way to view your layouts:

```bash
# From project root
make layout           # View all layers
make layout _DEF      # View default layer
make layout _NUM _FN  # View multiple layers
```

Uses the `draw_layout.py` script for colored ASCII art in terminal.

## Professional Diagrams

Generate beautiful SVG diagrams of your keyboard layout:

### Setup

Install keymap-drawer:

```bash
pip install keymap-drawer
```

Optional (for PNG generation):
```bash
pip install cairosvg
# or
brew install inkscape
```

### Usage

```bash
# From project root
./draw/generate.sh

# Or use the Makefile target
make draw
```

This will create:
- `planck.svg` - Complete keymap with all 8 layers
- `def-layer.svg` - Default Colemak layer
- `num-layer.svg` - Numbers with homerow mods
- `gaming-layer.svg` - QWERTY gaming layer
- `fn-layer.svg` - Function keys
- `sys-layer.svg` - System controls
- `nav-layer.svg` - Navigation
- `mouse-layer.svg` - Mouse control
- `midi-layer.svg` - MIDI controller
- `*.png` - PNG versions (if cairosvg/inkscape installed)

### Viewing

```bash
open draw/planck.svg           # View all layers
open draw/def-layer.svg        # View individual layer
```

## Configuration

Edit `config.yaml` to customize:
- Key legends and symbols
- Colors and styling
- Layer names
- Special keycode representations

## Quick Terminal View

For a quick ASCII view in terminal:

```bash
# View all layers
python3 draw_layout.py

# View specific layers
python3 draw_layout.py _DEF _NUM
```

## Files

- `config.yaml` - keymap-drawer configuration
- `generate.sh` - Script to generate diagrams
- `keymap.yaml` - Manual keymap definition (committed)
- `*.svg` - Generated SVG diagrams (git-ignored)
- `*.png` - Generated PNG diagrams (git-ignored)

## Tips

- SVG files are vector graphics that scale perfectly
- View SVG in browser or graphics app
- PNG is good for sharing/embedding in docs
- Regenerate after keymap changes
