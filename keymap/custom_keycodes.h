/* Copyright 2015-2023 Jack Humbert
 * GPL-2.0-or-later
 *
 * CUSTOM KEYCODES AND LAYER DEFINITIONS
 * Central location for all custom keycode and layer management
 */

#pragma once

#include QMK_KEYBOARD_H

/* ╔════════════════════════════════════════════════════════════╗
 * ║  LAYER DEFINITIONS - UROB'S NAMING CONVENTION              ║
 * ╚════════════════════════════════════════════════════════════╝ */

/* Layers - urob's naming convention */
enum planck_layers {
    _DEF,      // Default layer (Colemak)
    _NUM,      // Numeric layer
    _GAMING,   // Gaming layer (no combos/mods)
    _FN,       // Function layer
    _SYS,      // System layer (was ADJUST)
    _NAV,      // Navigation layer
    _MOUSE,    // Mouse layer (urob-style)
    _MIDI      // MIDI layer (keep as is)
};

/* ╔════════════════════════════════════════════════════════════╗
 * ║  CUSTOM KEYCODES                                           ║
 * ╚════════════════════════════════════════════════════════════╝ */

/* Custom keycodes */
enum planck_keycodes {
    DEF = SAFE_RANGE,
    GAMING,
    BACKLIT,
    PSWD,
    SMART_NUM,    // urob's smart num behavior
    MAGIC_SHIFT,  // urob's magic shift behavior
    SMART_SPC,    // urob's smart space behavior (lt_spc)
    NAV_BSPC,     // urob's smart backspace
    NAV_DEL,      // urob's smart delete
    SMART_MOUSE,  // urob's smart mouse toggle
    LEADER,       // Leader key for umlauts and special chars
    LEADER_SFT,   // Leader with sticky shift (urob's leader_sft)
    ALT_TAB_FWD,  // Alt+Tab swapper (forward)
    ALT_TAB_REV,  // Alt+Shift+Tab swapper (reverse)
    DSK_PREV,     // Previous desktop
    DSK_NEXT,     // Next desktop
    PIN_WIN,      // Pin window across desktops
    PIN_APP,      // Pin application across desktops
    DSK_MGR,      // Desktop manager
};

/* ╔══════════════════════════════════════════════════════════╗
 * ║  TAP DANCE DEFINITIONS                                   ║
 * ╚══════════════════════════════════════════════════════════╝ */

enum {
    TD_PRINT,   // Tap: Print Screen | Double-tap: Shift+Print Screen
};

/* ╔══════════════════════════════════════════════════════════╗
 * ║  KEYCODE ALIASES AND CONVENIENCE MACROS                  ║
 * ╚══════════════════════════════════════════════════════════╝ */

#define NUM      MO(_NUM)
#define SYM      MO(_GAMING)  // SYM key now accesses gaming layer
#define FN       MO(_FN)
#define NAV      MO(_NAV)
#define MOUSE    TG(_MOUSE)   // Mouse layer toggle
#define MIDI     TG(_MIDI)
#define CTRL_ESC LCTL_T(KC_ESC)
#define GAME_ESC LT(_SYS, KC_ESC)  // Gaming layer escape with system access
#define PRINT TD(TD_PRINT)   // Tap: Print Screen | Double-tap: Shift+Print Screen

/* ╔══════════════════════════════════════════════════════════════════════╗
 * ║  MOD-MORPH - UROB'S LINGUISTIC ?/! APPROACH                          ║
 * ║  Tap = ?, Shift+Tap = ! (linguistic grouping for sentence endings)   ║
 * ╚══════════════════════════════════════════════════════════════════════╝ */

// Urob's ?/! mod-morph (more linguistic than /?)
extern const key_override_t qexcl_override;
extern const key_override_t *key_overrides[];
