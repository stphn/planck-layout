#!/usr/bin/env python3
"""
Planck Keyboard Layout Visualizer
Generates ASCII art representations of keyboard layers
"""

import sys
from typing import List, Dict

# Color codes for terminal output
class Colors:
    HEADER = '\033[95m'
    BLUE = '\033[94m'
    CYAN = '\033[96m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    RED = '\033[91m'
    END = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

# Layer definitions matching your keymap
LAYERS = {
    '_DEF': {
        'name': 'Default (Colemak DH)',
        'keys': [
            ['Q', 'W', 'F', 'P', 'B', 'COPY', 'BSPC', 'J', 'L', 'U', 'Y', ';'],
            ['A', 'R', 'S', 'T', 'G', 'UNDO', 'REDO', 'M', 'N', 'E', 'I', 'O'],
            ['Z', 'X', 'C', 'D', 'V', 'SAVE', 'FIND', 'K', 'H', ',', '.', '?'],
            ['PSWD', 'HYPR', '___', 'GUI', 'SPC', 'ENT', 'NUM', 'SHFT', 'MOUS', '___', 'MIDI', 'GAME']
        ],
        'mods': {
            'A': 'GUI', 'R': 'ALT', 'S': 'SFT', 'T': 'CTL',
            'N': 'CTL', 'E': 'SFT', 'I': 'ALT', 'O': 'GUI',
            'SPC': 'NAV', 'ENT': 'FN', 'NUM': 'NUM', 'SHFT': 'MAGIC'
        },
        'special': {
            'COPY': 'Tap:Copy\nDbl:Cut',
            'BSPC': 'Tap:Bspc\nSft:Del',
            'UNDO': 'Cmd+Z',
            'REDO': 'Cmd+Sft+Z',
            'SAVE': 'Cmd+S',
            'FIND': 'Cmd+F',
        }
    },
    '_NUM': {
        'name': 'Numbers (urob-style with homerow mods)',
        'keys': [
            ['___', '7', '8', '9', '___', '___', '___', '___', '___', '___', '___', '___'],
            ['0', '4', '5', '6', '___', '___', '___', '___', '___', '___', '___', '___'],
            ['___', '1', '2', '3', '___', '___', '___', '___', '___', '___', '___', '___'],
            ['___', '___', '___', '___', '___', '___', '___', '___', '___', '___', '___', '___']
        ],
        'mods': {
            '0': 'GUI', '4': 'ALT', '5': 'SFT', '6': 'CTL'
        }
    },
    '_FN': {
        'name': 'Function Keys',
        'keys': [
            ['F12', 'F7', 'F8', 'F9', '___', '___', '___', '___', 'PREV', 'VOL+', 'NEXT', '___'],
            ['F11', 'F4', 'F5', 'F6', '___', '___', '___', '___', 'DSK◄', 'VOL-', 'DSK►', '___'],
            ['F10', 'F1', 'F2', 'F3', '___', '___', '___', '___', 'PIN', 'PIN', 'DSKM', '___'],
            ['___', '___', '___', '___', '___', '___', 'MUTE', 'PLAY', '___', '___', '___', '___']
        ],
        'mods': {
            'F11': 'GUI', 'F4': 'ALT', 'F5': 'SFT', 'F6': 'CTL',
            'VOL-': 'SFT'
        }
    },
    '_SYS': {
        'name': 'System (FN + NUM)',
        'keys': [
            ['AU_ON', 'AU_OF', '___', '___', '___', 'RGB', '___', '___', 'NEXT', 'HUE+', 'SAT+', 'VAL+'],
            ['MU_ON', 'MU_OF', '___', '___', '___', 'BOOT', 'BOOT', '___', 'PREV', 'HUE-', 'SAT-', 'VAL-'],
            ['MI_ON', 'MI_OF', '___', '___', '___', 'ECLR', 'ECLR', '___', '___', '___', '___', '___'],
            ['AU_PR', 'AU_NX', '___', '___', '___', 'DEF', 'GAME', 'MIDI', '___', '___', '___', 'DBUG']
        ]
    },
    '_NAV': {
        'name': 'Navigation',
        'keys': [
            ['ALT4', '___', 'TAB◄', 'TAB►', '___', '___', '___', 'PGUP', 'BSPC', '↑', 'DEL', '___'],
            ['oGUI', 'oALT', 'oSFT', 'oCTL', '___', '___', '___', 'PGDN', '←', '↓', '→', 'ENT'],
            ['___', '___', '___', '___', '___', '___', '___', 'INS', 'TAB', '___', '___', '___'],
            ['___', '___', '___', '___', '___', '___', 'CNCL', '___', '___', '___', '___', '___']
        ]
    },
    '_MOUSE': {
        'name': 'Mouse',
        'keys': [
            ['___', '___', '___', '___', '___', '___', '___', '___', 'PGUP', 'M↑', 'PGDN', '___'],
            ['___', '___', '___', '___', '___', '___', '___', 'WHL◄', 'M←', 'M↓', 'M→', 'WHL►'],
            ['___', '___', '___', '___', '___', '___', '___', '___', 'BTN1', 'BTN3', 'BTN2', '___'],
            ['___', '___', '___', '___', '___', '___', 'WHL↑', 'WHL↓', '___', '___', '___', '___']
        ]
    }
}

def draw_key(key: str, width: int = 6, mod: str = None, special: str = None) -> List[str]:
    """Draw a single key as a box with optional modifier or special notation"""
    lines = []

    # Top border
    lines.append('┌' + '─' * width + '┐')

    # Modifier line (if present)
    if mod:
        mod_text = f"{mod}".center(width)
        lines.append(f'│{Colors.YELLOW}{mod_text}{Colors.END}│')
    elif special:
        # For multi-line special text, split it
        special_lines = special.split('\n')
        for sp_line in special_lines[:1]:  # Only first line for now
            sp_text = sp_line[:width].center(width)
            lines.append(f'│{Colors.CYAN}{sp_text}{Colors.END}│')
    else:
        lines.append('│' + ' ' * width + '│')

    # Key text
    key_text = key[:width].center(width)
    if key == '___':
        lines.append(f'│{Colors.END}{key_text}{Colors.END}│')
    else:
        lines.append(f'│{Colors.GREEN}{key_text}{Colors.END}│')

    # Bottom border
    lines.append('└' + '─' * width + '┘')

    return lines

def draw_row(keys: List[str], mods: Dict = None, special: Dict = None) -> str:
    """Draw a complete row of keys"""
    mods = mods or {}
    special = special or {}

    key_boxes = [draw_key(k, mod=mods.get(k), special=special.get(k)) for k in keys]

    # Combine horizontally
    result = []
    for line_idx in range(len(key_boxes[0])):
        line = ' '.join(box[line_idx] for box in key_boxes)
        result.append(line)

    return '\n'.join(result)

def draw_layer(layer_name: str, layer_data: Dict) -> str:
    """Draw a complete layer"""
    output = []

    # Header
    output.append(f"\n{Colors.BOLD}{Colors.BLUE}{'='*100}{Colors.END}")
    output.append(f"{Colors.BOLD}{Colors.BLUE}{layer_data['name'].center(100)}{Colors.END}")
    output.append(f"{Colors.BOLD}{Colors.BLUE}{'='*100}{Colors.END}\n")

    # Draw each row
    for row_idx, row in enumerate(layer_data['keys']):
        mods = layer_data.get('mods', {})
        special = layer_data.get('special', {})
        output.append(draw_row(row, mods, special))
        if row_idx < len(layer_data['keys']) - 1:
            output.append('')  # Space between rows

    # Legend
    if layer_data.get('mods') or layer_data.get('special'):
        output.append(f"\n{Colors.CYAN}Legend:{Colors.END}")
        if layer_data.get('mods'):
            output.append(f"  {Colors.YELLOW}Yellow text{Colors.END} = Hold modifier (homerow mods, layer-taps)")
        if layer_data.get('special'):
            output.append(f"  {Colors.CYAN}Cyan text{Colors.END} = Special behavior (tap-dance, morphs)")

    return '\n'.join(output)

def main():
    """Main function to draw all layers or specific ones"""
    if len(sys.argv) > 1:
        # Draw specific layers
        layers_to_draw = [arg.upper() if not arg.startswith('_') else arg for arg in sys.argv[1:]]
        layers_to_draw = [f"_{name}" if not name.startswith('_') else name for name in layers_to_draw]
    else:
        # Draw all layers
        layers_to_draw = list(LAYERS.keys())

    for layer_name in layers_to_draw:
        if layer_name in LAYERS:
            print(draw_layer(layer_name, LAYERS[layer_name]))
        else:
            print(f"{Colors.RED}Error: Layer '{layer_name}' not found{Colors.END}")
            print(f"Available layers: {', '.join(LAYERS.keys())}")

if __name__ == '__main__':
    main()
