/* Copyright 2015-2023 Jack Humbert
 * GPL-2.0-or-later
 *
 * SMART COMBOS - UROB'S POSITIONAL SYSTEM
 * Based on urob's ZMK config using physical positions instead of letters
 */

#pragma once

#include QMK_KEYBOARD_H
#include "bilateral_mods.h"

/* ╔═══════════════════════════════════════════════════════════════════════════════════════════════════╗
 * ║  SMART COMBOS - UROB'S POSITIONAL SYSTEM                                                          ║
 * ║  Based on urob's ZMK config using physical positions instead of letters                           ║
 * ║  Layout reference:                                                                                ║
 * ║  LT3=Q, LT2=W, LT1=F, LT0=P | RT0=J, RT1=L, RT2=U, RT3=Y                                          ║
 * ║  LM3=A, LM2=R, LM1=S, LM0=T | RM0=N, RM1=E, RM2=I, RM3=O                                          ║
 * ║  LB3=Z, LB2=X, LB1=C, LB0=D | RB0=K, RB1=H, RB2=,, RB3=.                                          ║
 * ╚═══════════════════════════════════════════════════════════════════════════════════════════════════╝ */

enum combo_events {
    // Navigation combos (existing)
    ESC_COMBO,       // W+F = Escape
    BSPC_COMBO,      // L+U = Backspace
    LEADER_COMBO,    // S+T = Leader key

    // urob's horizontal combos (left hand)
    TAB_COMBO,       // A+R = Tab
    CUT_COMBO,       // Z+C = Cut
    COPY_COMBO,      // Z+X = Copy
    PASTE_COMBO,     // X+C = Paste

    // urob's horizontal combos (right hand)
    DEL_COMBO,       // U+Y = Delete
    LPRN_COMBO,      // E+I = (
    RPRN_COMBO,      // I+O = )
    LBRC_COMBO,      // H+, = [
    RBRC_COMBO,      // ,+. = ]

    // urob's vertical symbol combos (left hand)
    AT_COMBO,        // Q+A = @
    HASH_COMBO,      // W+R = #
    DOLLAR_COMBO,    // F+S = $
    PERCENT_COMBO,   // P+T = %
    GRAVE_COMBO,     // A+Z = `
    BACKSLASH_COMBO, // R+X = backslash
    EQUALS_COMBO,    // S+C = =
    TILDE_COMBO,     // T+D = ~

    // urob's vertical symbol combos (right hand)
    CARET_COMBO,     // J+M = ^
    PLUS_COMBO,      // L+N = +
    STAR_COMBO,      // U+E = *
    AMPER_COMBO,     // Y+I = &
    UNDERSCORE_COMBO,// M+K = _
    MINUS_COMBO,     // N+H = -
    SLASH_COMBO,     // E+, = /
    PIPE_COMBO,      // I+. = |

};

// Navigation combos
extern const uint16_t PROGMEM esc_combo[];
extern const uint16_t PROGMEM bspc_combo[];
extern const uint16_t PROGMEM leader_combo[];

// urob's horizontal combos (left hand)
extern const uint16_t PROGMEM tab_combo[];
extern const uint16_t PROGMEM cut_combo[];
extern const uint16_t PROGMEM copy_combo[];
extern const uint16_t PROGMEM paste_combo[];

// urob's horizontal combos (right hand)
extern const uint16_t PROGMEM del_combo[];
extern const uint16_t PROGMEM lprn_combo[];
extern const uint16_t PROGMEM rprn_combo[];
extern const uint16_t PROGMEM lbrc_combo[];
extern const uint16_t PROGMEM rbrc_combo[];

// urob's vertical symbol combos (left hand)
extern const uint16_t PROGMEM at_combo[];
extern const uint16_t PROGMEM hash_combo[];
extern const uint16_t PROGMEM dollar_combo[];
extern const uint16_t PROGMEM percent_combo[];
extern const uint16_t PROGMEM grave_combo[];
extern const uint16_t PROGMEM backslash_combo[];
extern const uint16_t PROGMEM equals_combo[];
extern const uint16_t PROGMEM tilde_combo[];

// urob's vertical symbol combos (right hand)
extern const uint16_t PROGMEM caret_combo[];
extern const uint16_t PROGMEM plus_combo[];
extern const uint16_t PROGMEM star_combo[];
extern const uint16_t PROGMEM amper_combo[];
extern const uint16_t PROGMEM underscore_combo[];
extern const uint16_t PROGMEM minus_combo[];
extern const uint16_t PROGMEM slash_combo[];
extern const uint16_t PROGMEM pipe_combo[];

// Combo array declaration
extern combo_t key_combos[];

/* ╔════════════════════════════════════════════════════════════════════════════════════════════════════╗
 * ║  COMBO ARRAY IMPLEMENTATIONS                                                                       ║
 * ║  Physical key combinations for urob's smart combo system                                           ║
 * ╚════════════════════════════════════════════════════════════════════════════════════════════════════╝ */

// Navigation combos
const uint16_t PROGMEM esc_combo[] = {KC_W, KC_F, COMBO_END};         // W+F = Escape
const uint16_t PROGMEM bspc_combo[] = {KC_L, KC_U, COMBO_END};        // L+U = Backspace
const uint16_t PROGMEM leader_combo[] = {HRM_S, HRM_T, COMBO_END};    // S+T = Leader key

// urob's horizontal combos (left hand)
const uint16_t PROGMEM tab_combo[] = {HRM_A, HRM_R, COMBO_END};       // A+R = Tab
const uint16_t PROGMEM cut_combo[] = {KC_Z, KC_C, COMBO_END};         // Z+C = Cut
const uint16_t PROGMEM copy_combo[] = {KC_Z, KC_X, COMBO_END};        // Z+X = Copy
const uint16_t PROGMEM paste_combo[] = {KC_X, KC_C, COMBO_END};       // X+C = Paste

// urob's horizontal combos (right hand)
const uint16_t PROGMEM del_combo[] = {KC_U, KC_Y, COMBO_END};         // U+Y = Delete
const uint16_t PROGMEM lprn_combo[] = {HRM_E, HRM_I, COMBO_END};      // E+I = (
const uint16_t PROGMEM rprn_combo[] = {HRM_I, HRM_O, COMBO_END};      // I+O = )
const uint16_t PROGMEM lbrc_combo[] = {KC_H, KC_COMM, COMBO_END};     // H+, = [
const uint16_t PROGMEM rbrc_combo[] = {KC_COMM, KC_DOT, COMBO_END};   // ,+. = ]

// urob's vertical symbol combos (left hand) - using homerow mod keycodes
const uint16_t PROGMEM at_combo[] = {KC_Q, HRM_A, COMBO_END};         // Q+A = @
const uint16_t PROGMEM hash_combo[] = {KC_W, HRM_R, COMBO_END};       // W+R = #
const uint16_t PROGMEM dollar_combo[] = {KC_F, HRM_S, COMBO_END};     // F+S = $
const uint16_t PROGMEM percent_combo[] = {KC_P, HRM_T, COMBO_END};    // P+T = %
const uint16_t PROGMEM grave_combo[] = {HRM_A, KC_Z, COMBO_END};      // A+Z = `
const uint16_t PROGMEM backslash_combo[] = {HRM_R, KC_X, COMBO_END};  // R+X = backslash
const uint16_t PROGMEM equals_combo[] = {HRM_S, KC_C, COMBO_END};     // S+C = =
const uint16_t PROGMEM tilde_combo[] = {HRM_T, KC_D, COMBO_END};      // T+D = ~

// urob's vertical symbol combos (right hand) - using homerow mod keycodes
const uint16_t PROGMEM caret_combo[] = {KC_J, KC_M, COMBO_END};       // J+M = ^
const uint16_t PROGMEM plus_combo[] = {KC_L, HRM_N, COMBO_END};       // L+N = +
const uint16_t PROGMEM star_combo[] = {KC_U, HRM_E, COMBO_END};       // U+E = *
const uint16_t PROGMEM amper_combo[] = {KC_Y, HRM_I, COMBO_END};      // Y+I = &
const uint16_t PROGMEM underscore_combo[] = {KC_M, KC_K, COMBO_END};  // M+K = _
const uint16_t PROGMEM minus_combo[] = {HRM_N, KC_H, COMBO_END};      // N+H = -
const uint16_t PROGMEM slash_combo[] = {HRM_E, KC_COMM, COMBO_END};   // E+, = /
const uint16_t PROGMEM pipe_combo[] = {HRM_I, KC_DOT, COMBO_END};     // I+. = |

// Define what each combo does - urob's complete symbol system
combo_t key_combos[] = {
    // Navigation combos
    [ESC_COMBO] = COMBO(esc_combo, KC_ESC),                // W+F = Escape
    [BSPC_COMBO] = COMBO(bspc_combo, KC_BSPC),             // L+U = Backspace
    [LEADER_COMBO] = COMBO(leader_combo, LEADER),          // S+T = Leader key

    // urob's horizontal combos (left hand)
    [TAB_COMBO] = COMBO(tab_combo, KC_TAB),                // A+R = Tab
    [CUT_COMBO] = COMBO(cut_combo, LGUI(KC_X)),            // Z+C = Cut
    [COPY_COMBO] = COMBO(copy_combo, LGUI(KC_C)),          // Z+X = Copy
    [PASTE_COMBO] = COMBO(paste_combo, LGUI(KC_V)),        // X+C = Paste

    // urob's horizontal combos (right hand)
    [DEL_COMBO] = COMBO(del_combo, KC_DEL),                // U+Y = Delete
    [LPRN_COMBO] = COMBO(lprn_combo, KC_LPRN),             // E+I = (
    [RPRN_COMBO] = COMBO(rprn_combo, KC_RPRN),             // I+O = )
    [LBRC_COMBO] = COMBO(lbrc_combo, KC_LBRC),             // H+, = [
    [RBRC_COMBO] = COMBO(rbrc_combo, KC_RBRC),             // ,+. = ]

    // urob's vertical symbol combos (left hand)
    [AT_COMBO] = COMBO(at_combo, KC_AT),                   // Q+A = @
    [HASH_COMBO] = COMBO(hash_combo, KC_HASH),             // W+R = #
    [DOLLAR_COMBO] = COMBO(dollar_combo, KC_DLR),          // F+S = $
    [PERCENT_COMBO] = COMBO(percent_combo, KC_PERC),       // P+T = %
    [GRAVE_COMBO] = COMBO(grave_combo, KC_GRV),            // A+Z = `
    [BACKSLASH_COMBO] = COMBO(backslash_combo, KC_BSLS),   // R+X = backslash
    [EQUALS_COMBO] = COMBO(equals_combo, KC_EQL),          // S+C = =
    [TILDE_COMBO] = COMBO(tilde_combo, KC_TILD),           // T+D = ~

    // urob's vertical symbol combos (right hand)
    [CARET_COMBO] = COMBO(caret_combo, KC_CIRC),           // J+N = ^
    [PLUS_COMBO] = COMBO(plus_combo, KC_PLUS),             // L+E = +
    [STAR_COMBO] = COMBO(star_combo, KC_ASTR),             // U+I = *
    [AMPER_COMBO] = COMBO(amper_combo, KC_AMPR),           // Y+O = &
    [UNDERSCORE_COMBO] = COMBO(underscore_combo, KC_UNDS), // N+K = _
    [MINUS_COMBO] = COMBO(minus_combo, KC_MINS),           // E+H = -
    [SLASH_COMBO] = COMBO(slash_combo, KC_SLSH),           // I+, = /
    [PIPE_COMBO] = COMBO(pipe_combo, KC_PIPE),             // O+. = |

};

/* ╔═════════════════════════════════════════════════════════════════════════════╗
 * ║  COMBO TIMING AND CONTROL FUNCTIONS                                         ║
 * ║  Smart timing to work with bilateral homerow mods                           ║
 * ╚═════════════════════════════════════════════════════════════════════════════╝ */

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch (index) {
        case ESC_COMBO:
        case BSPC_COMBO:
            return 15;  // Fast navigation combos

        // Combos involving homerow mods need longer timing
        case HASH_COMBO:        // W+R = #
        case DOLLAR_COMBO:      // F+S = $
        case PERCENT_COMBO:     // P+T = %
        case CARET_COMBO:       // J+N = ^
        case PLUS_COMBO:        // L+E = +
        case STAR_COMBO:        // U+I = *
        case AMPER_COMBO:       // Y+O = &
            return 30;          // Longer timing for homerow conflicts

        default:
            return COMBO_TERM;  // Default 18ms for safe combos
    }
}

// Disable combos on gaming layer for clean gaming experience
bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    // Disable all combos on gaming layer
    if (get_highest_layer(default_layer_state) == _GAMING) {
        return false;
    }
    return true;
}
