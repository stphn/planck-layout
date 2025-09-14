# ⌨️ Planck Rev7 — stphn Layout (Detailed)

This firmware defines multiple layers and a few custom behaviors on top of QMK defaults.  
Below is a breakdown of how each part works.

---

## 🎛 Layers
---

### Colemak DH  
Includes bracket/Hyper/Num/Sym/Nav keys for consistency.  
Tap-dances: `;/:`, `'/"`, `C/⌘C`, `V/⌘V`, `/ ?`.
Hyper Key

![Colemak Layer](images/colemak-layer.png)

---

### QWERTY
Alternative base using QWERTY.  
Same layer access and tap-dances as Colemak DH.  

![QWERTY Layer](images/qwerty-layer.png)


### NUM (Numbers + F-keys)
Second layer with numbers, function keys, and extra symbols.

![Number Layer](images/num-layer.png)

---

### SYM (Symbols + shifted F-keys)  
Third layer providing shifted symbols (`!@#$%^&*()` etc.) and F11–F20.  
Includes an extended F-key range for potential system shortcuts or custom bindings.

![Symbols Layer](images/sym-layer.png)

---

### NAV (Navigation, media, mouse — Vim-style NEIO consistency)
Navigation + system control:  
- Arrows, PgUp/PgDn, Home/End  
- Volume, mute, brightness  
- Alt+Tab, Ctrl+Arrow  
- Optional mouse movement + buttons

![Nav Layer](images/nav-layer.png)

---

### ADJUST (RGB, Audio, Boot, Layer toggles)
Tri-layer (_NUM + _SYM).  
Controls bootloader, debug, RGB Matrix, audio, and default layers.

![Adjust Layer](images/adjust-layer.png)

---

### Plover (Steno)
Stenography input for Plover software.  
Activates NKRO automatically.

![Plover Layer](images/plover-layer.png)

---

## 🩰 Tap-Dance Keys

- `;` → `;` (tap) / `:` (double-tap)  
- `'` → `'` (tap) / `"` (double-tap)  
- `/` → `/` (tap) / `?` (double-tap)  
- `C` → `C` (tap) / ⌘C (double-tap)  
- `V` → `V` (tap) / ⌘V (double-tap)  

![Tap Dance](images/tap-dance.png)

---

## 🅥 Vim Integration

Using four Colemak keys (`N/E/I/O`) acted as:  
- Tap → letter (`n/e/i/o`)  
- Hold → arrow (`← ↓ ↑ →`)  

Mimics Vim’s `hjkl` but adapted to Colemak home row.  
In QWERTY cleanup, `H J K L` remain plain letters.

---

## 🔑 Special Behaviors

- **CTRL_ESC** → Esc (tap) / Ctrl (hold)  
- **Space / Enter dual roles**:  
  - `SFT_T(SPC)` = Space (tap) / Shift (hold)  
  - `LT(0, ENT)` = Enter (tap) / Backspace (hold)  
- **Brackets `[ ]`** → quick outer pinky access  
- **Hyper key** → Ctrl+Alt+Shift+GUI  
- **RGB indicators** → layer-specific LED feedback

---

## 📖 Usage Summary

- **Typing** → QWERTY or Colemak  
- **Symbols/Numbers** → NUM/SYM  
- **System/media/nav** → NAV  
- **Config/RGB/boot/audio** → ADJUST  
- **Steno** → Plover  
- **Editing speedups** → tap-dance + Vim features
