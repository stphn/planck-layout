# Keyboard Layout Diagrams

This directory contains tools and generated diagrams for visualizing the Planck keyboard layout.

## Tools Used

- **[keymap-drawer](https://github.com/caksoylar/keymap-drawer)** - Professional keyboard layout visualization tool
- Inspired by [urob's ZMK config](https://github.com/urob/zmk-config/tree/main/draw)

## Setup

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

## Usage

Generate layout diagrams:

```bash
# From project root
./draw/generate.sh

# Or use the Makefile target
make draw
```

This will create:
- `keymap.yaml` - Parsed keymap representation
- `planck.svg` - Vector diagram (recommended)
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
