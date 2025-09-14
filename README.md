# ⌨️ Planck Rev7 — Personal Layout (Detailed)

This firmware defines multiple layers and a few custom behaviors on top of QMK defaults.  
Below is a breakdown of how each part works.

## 🎛 Layers

### Colemak DH  

Includes bracket/Hyper/Num/Sym/Nav keys.  
Tap-dances: `;/:`, `'/"`, `C/⌘C`, `V/⌘V`, `/ ?`.

![Colemak Layer](images/colemak-layer.png)

### QWERTY
Alternative base using QWERTY.  
Same layer access and tap-dances as Colemak DH.  

![QWERTY Layer](images/qwerty-layer.png)

### NUM (Numbers + F-keys)

Layer for numbers, F1–F10, and basic symbols like `- = \``.  
Designed for quick numeric input and function key access.

![Number Layer](images/num-layer.png)

### SYM (Symbols + shifted F-keys)  

Third layer providing shifted symbols (`!@#$%^&*()` etc.) and F11–F20.  
Includes an extended F-key range for potential system shortcuts or custom bindings.

![Symbols Layer](images/sym-layer.png)

### NAV (Navigation, media, mouse — Vim-style NEIO consistency)

Navigation + system control:  
- Arrows, PgUp/PgDn, Home/End  
- Volume, mute, brightness  
- Alt+Tab, Ctrl+Arrow  
- Optional mouse movement + buttons

![Nav Layer](images/nav-layer.png)

### ADJUST (RGB, Audio, Boot, Layer toggles)

Tri-layer (_NUM + _SYM).  
Controls bootloader, debug, RGB Matrix, audio, and default layers.

![Adjust Layer](images/adjust-layer.png)

### Plover (Steno)
Stenography input for Plover software.  
Activates NKRO automatically.

## 🩰 Tap-Dance Keys

- `;` → `;` (tap) / `:` (double-tap)  
- `'` → `'` (tap) / `"` (double-tap)  
- `/` → `/` (tap) / `?` (double-tap)  
- `C` → `C` (tap) / ⌘C (double-tap)  
- `V` → `V` (tap) / ⌘V (double-tap)  

## 🅥 Vim Integration

Using four Colemak keys (`N/E/I/O`) acted as:  
- Tap → letter (`n/e/i/o`)  
- Hold → arrow (`← ↓ ↑ →`)  

Mimics Vim’s `hjkl` but adapted to Colemak home row.  

## 🔑 Special Behaviors

- **CTRL_ESC** → Esc (tap) / Ctrl (hold)  
- **Space / Enter dual roles**:  
  - `SFT_T(SPC)` = Space (tap) / Shift (hold)  
  - `LT(0, ENT)` = Enter (tap) / Backspace (hold)  
- **Brackets `[ ]`** → quick outer pinky access  
- **Hyper key** → Ctrl+Alt+Shift+GUI  
- **RGB indicators** → layer-specific LED feedback

## ⚙️ Build Commands

### `make build`
Compiles the firmware and outputs a `.bin` file into QMK’s build directory:
qmk/.build/planck_rev7_stphn.bin

Use this if you only want to check that the firmware compiles successfully.

### `make flash`
Compiles the firmware and flashes it directly to the Planck Rev7.  
Requires putting the board into bootloader mode first:
- Press the physical **RESET** or **BOOT** button on the PCB  
- Or press the `QK_BOOT` key if you have it mapped

### `make save`
Compiles the firmware and saves a copy into the `firmware/` folder with a timestamped filename.  

Example:
firmware/planck_rev7_stphn-20240909-212055.bin

Useful for archiving known-good builds.

### `make clean`
Removes the cached build artifacts inside `qmk/.build/`.  
Forces the next build to compile everything fresh.  
Run this if you encounter strange build errors or after major QMK updates.

Thanks for reading 
