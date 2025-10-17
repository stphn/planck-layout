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

## Professional Diagrams (WIP)

**Note:** SVG/PNG generation using keymap-drawer is currently a work in progress due to QMK's complex keymap structure. The terminal visualization above is fully functional.

### Future Setup

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

### Future Usage

```bash
# From project root
./draw/generate.sh

# Or use the Makefile target
make draw
```

This will create:
- `keymap.json` - QMK JSON representation
- `keymap.yaml` - Parsed keymap representation
- `planck.svg` - Vector diagram
- `planck.png` - Raster image (if cairosvg/inkscape installed)

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
- `keymap.yaml` - Generated parsed keymap (git-ignored)
- `planck.svg` - Generated SVG diagram (git-ignored)
- `planck.png` - Generated PNG diagram (git-ignored)

## Tips

- SVG files are vector graphics that scale perfectly
- View SVG in browser or graphics app
- PNG is good for sharing/embedding in docs
- Regenerate after keymap changes
