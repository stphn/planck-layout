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
 * ║  Layout reference (urob has 5 columns per hand):                                                  ║
 * ║  LT4=Q, LT3=W, LT2=F, LT1=P, LT0=B | RT0=J, RT1=L, RT2=U, RT3=Y, RT4=;                            ║
 * ║  LM4=A, LM3=R, LM2=S, LM1=T, LM0=G | RM0=M, RM1=N, RM2=E, RM3=I, RM4=O                            ║
 * ║  LB4=Z, LB3=X, LB2=C, LB1=D, LB0=V | RB0=K, RB1=H, RB2=,, RB3=., RB4=/                            ║
 * ╚═══════════════════════════════════════════════════════════════════════════════════════════════════╝ */

enum combo_events {
    // Navigation combos (existing)
    ESC_COMBO,       // W+F = Escape
    BSPC_COMBO,      // L+U = Backspace
    LEADER_COMBO,    // S+T = Leader key (urob's position)
    LEADER_SFT_COMBO, // R+S+T = Shifted leader (Shift+Ctrl+Alt mod)

    // urob's mouse layer activation
    MOUSE_COMBO,     // F+P = Smart Mouse toggle (LT1+LT0 in urob's notation)

    // urob's horizontal combos (left hand)
    TAB_COMBO,       // A+R = Tab
    CUT_COMBO,       // Z+C = Cut
    COPY_COMBO,      // Z+X = Copy
    PASTE_COMBO,     // X+C = Paste

    // urob's horizontal combos (right hand)
    DEL_COMBO,       // U+Y = Delete
    LPRN_LT_COMBO,   // N+E = ( or < (RM1+RM2, shift-modified, like urob's lpar_lt)
    RPRN_GT_COMBO,   // E+I = ) or > (RM2+RM3, shift-modified, like urob's rpar_gt)
    LBKT_LBRC_COMBO, // H+, = [ on DEF/NUM, { on NAV (layer-specific)
    RBKT_RBRC_COMBO, // ,+. = ] on DEF/NUM, } on NAV (layer-specific)

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
    CARET_COMBO,     // J+M = ^ (RT0+RM0)
    PLUS_COMBO,      // L+N = + (RT1+RM1)
    STAR_COMBO,      // U+E = * (RT2+RM2)
    AMPER_COMBO,     // Y+I = & (RT3+RM3)
    UNDERSCORE_COMBO,// M+K = _ (RM0+RB0)
    MINUS_COMBO,     // N+H = - (RM1+RB1)
    SLASH_COMBO,     // E+, = / (RM2+RB2)
    PIPE_COMBO,      // I+. = | (RM3+RB3)

};

// Navigation combos
extern const uint16_t PROGMEM esc_combo[];
extern const uint16_t PROGMEM bspc_combo[];
extern const uint16_t PROGMEM leader_combo[];
extern const uint16_t PROGMEM leader_sft_combo[];
extern const uint16_t PROGMEM mouse_combo[];

// urob's horizontal combos (left hand)
extern const uint16_t PROGMEM tab_combo[];
extern const uint16_t PROGMEM cut_combo[];
extern const uint16_t PROGMEM copy_combo[];
extern const uint16_t PROGMEM paste_combo[];

// urob's horizontal combos (right hand)
extern const uint16_t PROGMEM del_combo[];
extern const uint16_t PROGMEM lprn_lt_combo[];
extern const uint16_t PROGMEM rprn_gt_combo[];
extern const uint16_t PROGMEM lbkt_lbrc_combo[];
extern const uint16_t PROGMEM rbkt_rbrc_combo[];

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
const uint16_t PROGMEM esc_combo[] = {KC_W, KC_F, COMBO_END};                    // W+F = Escape
const uint16_t PROGMEM bspc_combo[] = {KC_L, KC_U, COMBO_END};                   // L+U = Backspace
const uint16_t PROGMEM leader_combo[] = {HRM_S, HRM_T, COMBO_END};               // S+T = Leader key (urob)
const uint16_t PROGMEM leader_sft_combo[] = {HRM_R, HRM_S, HRM_T, COMBO_END};    // R+S+T = Shifted leader
const uint16_t PROGMEM mouse_combo[] = {KC_F, KC_P, COMBO_END};                  // F+P = Smart Mouse toggle

// urob's horizontal combos (left hand)
const uint16_t PROGMEM tab_combo[] = {HRM_A, HRM_R, COMBO_END};       // A+R = Tab
const uint16_t PROGMEM cut_combo[] = {KC_Z, KC_C, COMBO_END};         // Z+C = Cut
const uint16_t PROGMEM copy_combo[] = {KC_Z, KC_X, COMBO_END};        // Z+X = Copy
const uint16_t PROGMEM paste_combo[] = {KC_X, KC_C, COMBO_END};       // X+C = Paste

// urob's horizontal combos (right hand)
const uint16_t PROGMEM del_combo[] = {KC_U, KC_Y, COMBO_END};              // U+Y = Delete
const uint16_t PROGMEM lprn_lt_combo[] = {HRM_N, HRM_E, COMBO_END};        // N+E = ( or < (RM1+RM2, urob's lpar_lt)
const uint16_t PROGMEM rprn_gt_combo[] = {HRM_E, HRM_I, COMBO_END};        // E+I = ) or > (RM2+RM3, urob's rpar_gt)
const uint16_t PROGMEM lbkt_lbrc_combo[] = {KC_H, KC_COMM, COMBO_END};     // H+, = [ or { (layer-specific)
const uint16_t PROGMEM rbkt_rbrc_combo[] = {KC_COMM, KC_DOT, COMBO_END};   // ,+. = ] or } (layer-specific)

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
const uint16_t PROGMEM caret_combo[] = {KC_J, KC_M, COMBO_END};       // J+M = ^ (RT0+RM0)
const uint16_t PROGMEM plus_combo[] = {KC_L, HRM_N, COMBO_END};       // L+N = + (RT1+RM1)
const uint16_t PROGMEM star_combo[] = {KC_U, HRM_E, COMBO_END};       // U+E = * (RT2+RM2)
const uint16_t PROGMEM amper_combo[] = {KC_Y, HRM_I, COMBO_END};      // Y+I = & (RT3+RM3)
const uint16_t PROGMEM underscore_combo[] = {KC_M, KC_K, COMBO_END};  // M+K = _ (RM0+RB0)
const uint16_t PROGMEM minus_combo[] = {HRM_N, KC_H, COMBO_END};      // N+H = - (RM1+RB1)
const uint16_t PROGMEM slash_combo[] = {HRM_E, KC_COMM, COMBO_END};   // E+, = / (RM2+RB2)
const uint16_t PROGMEM pipe_combo[] = {HRM_I, KC_DOT, COMBO_END};     // I+. = | (RM3+RB3)

// Define what each combo does - urob's complete symbol system
combo_t key_combos[] = {
    // Navigation combos
    [ESC_COMBO] = COMBO(esc_combo, KC_ESC),                         // W+F = Escape
    [BSPC_COMBO] = COMBO(bspc_combo, KC_BSPC),                      // L+U = Backspace
    [LEADER_COMBO] = COMBO(leader_combo, LEADER),                   // R+S = Leader key
    [LEADER_SFT_COMBO] = COMBO(leader_sft_combo, LSA(KC_NO)),       // A+R+S = Shift+Ctrl+Alt modifier
    [MOUSE_COMBO] = COMBO(mouse_combo, SMART_MOUSE),                // F+P = Smart Mouse toggle

    // urob's horizontal combos (left hand)
    [TAB_COMBO] = COMBO(tab_combo, KC_TAB),                // A+R = Tab
    [CUT_COMBO] = COMBO(cut_combo, LGUI(KC_X)),            // Z+C = Cut
    [COPY_COMBO] = COMBO(copy_combo, LGUI(KC_C)),          // Z+X = Copy
    [PASTE_COMBO] = COMBO(paste_combo, LGUI(KC_V)),        // X+C = Paste

    // urob's horizontal combos (right hand) - layer-specific variants
    [DEL_COMBO] = COMBO(del_combo, KC_DEL),                // U+Y = Delete
    [LPRN_LT_COMBO] = COMBO_ACTION(lprn_lt_combo),         // N+E = ( or < (shift-modified)
    [RPRN_GT_COMBO] = COMBO_ACTION(rprn_gt_combo),         // E+I = ) or > (shift-modified)
    [LBKT_LBRC_COMBO] = COMBO_ACTION(lbkt_lbrc_combo),     // H+, = [ on DEF/NUM, { on NAV
    [RBKT_RBRC_COMBO] = COMBO_ACTION(rbkt_rbrc_combo),     // ,+. = ] on DEF/NUM, } on NAV

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
    [CARET_COMBO] = COMBO(caret_combo, KC_CIRC),           // J+M = ^
    [PLUS_COMBO] = COMBO(plus_combo, KC_PLUS),             // L+N = +
    [STAR_COMBO] = COMBO(star_combo, KC_ASTR),             // U+E = *
    [AMPER_COMBO] = COMBO(amper_combo, KC_AMPR),           // Y+I = &
    [UNDERSCORE_COMBO] = COMBO(underscore_combo, KC_UNDS), // M+K = _
    [MINUS_COMBO] = COMBO(minus_combo, KC_MINS),           // N+H = -
    [SLASH_COMBO] = COMBO(slash_combo, KC_SLSH),           // E+, = /
    [PIPE_COMBO] = COMBO(pipe_combo, KC_PIPE),             // I+. = |

};

/* ╔═════════════════════════════════════════════════════════════════════════════╗
 * ║  COMBO TIMING AND CONTROL FUNCTIONS                                         ║
 * ║  Smart timing to work with bilateral homerow mods                           ║
 * ╚═════════════════════════════════════════════════════════════════════════════╝ */

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch (index) {
        case ESC_COMBO:
        case BSPC_COMBO:
        case MOUSE_COMBO:
            return 15;  // Fast navigation and mouse combos

        case LEADER_SFT_COMBO:
            return 25;  // Slightly longer for 3-key combo

        // Combos involving homerow mods need longer timing
        case HASH_COMBO:        // W+R = #
        case DOLLAR_COMBO:      // F+S = $
        case PERCENT_COMBO:     // P+T = %
        case PLUS_COMBO:        // L+N = +
        case STAR_COMBO:        // U+E = *
        case AMPER_COMBO:       // Y+I = &
            return 30;          // Longer timing for homerow conflicts

        default:
            return COMBO_TERM;  // Default 18ms for safe combos
    }
}

// Layer-specific combo restrictions (like urob's ZMK layer filters)
bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    uint8_t current_layer = get_highest_layer(layer_state);

    // Disable all combos on gaming layer
    if (get_highest_layer(default_layer_state) == _GAMING) {
        return false;
    }

    // Layer-specific combo restrictions to match urob's ZMK config
    switch (combo_index) {
        // Bracket combos: available on both DEF/NUM and NAV (layer-specific output)
        case LBKT_LBRC_COMBO:
        case RBKT_RBRC_COMBO:
            return (current_layer == _DEF || current_layer == _NUM || current_layer == _NAV);

        // Parenthesis/angle combos: handled in process_combo_event
        case LPRN_LT_COMBO:
        case RPRN_GT_COMBO:
            return true;

        default:
            return true;
    }
}

/* ╔═════════════════════════════════════════════════════════════════════════════╗
 * ║  UROB'S SHIFT-MODIFIED COMBO BEHAVIORS                                      ║
 * ║  Implements lpar_lt and rpar_gt mod-morph behaviors                         ║
 * ╚═════════════════════════════════════════════════════════════════════════════╝ */

void process_combo_event(uint16_t combo_index, bool pressed) {
    uint8_t current_layer = get_highest_layer(layer_state);

    // Get both regular and oneshot mods to check for shift
    uint8_t saved_mods = get_mods();
    uint8_t oneshot_mods = get_oneshot_mods();
    bool shift_held = (saved_mods | oneshot_mods) & MOD_MASK_SHIFT;

    switch (combo_index) {
        case LPRN_LT_COMBO:
            if (pressed) {
                if (current_layer == _NAV) {
                    // NAV layer: always output <
                    tap_code16(KC_LT);
                } else {
                    // DEF/NUM layer: check for real shift (not homerow mod shift)
                    // Clear all mods temporarily to prevent homerow mod interference
                    clear_mods();
                    clear_oneshot_mods();

                    if (shift_held) {
                        // With shift: output <
                        tap_code16(KC_LT);
                    } else {
                        // Without shift: output (
                        tap_code16(KC_LPRN);
                    }

                    // Restore mods
                    set_mods(saved_mods);
                    set_oneshot_mods(oneshot_mods);
                }
            }
            break;

        case RPRN_GT_COMBO:
            if (pressed) {
                if (current_layer == _NAV) {
                    // NAV layer: always output >
                    tap_code16(KC_GT);
                } else {
                    // DEF/NUM layer: check for real shift (not homerow mod shift)
                    // Clear all mods temporarily to prevent homerow mod interference
                    clear_mods();
                    clear_oneshot_mods();

                    if (shift_held) {
                        // With shift: output >
                        tap_code16(KC_GT);
                    } else {
                        // Without shift: output )
                        tap_code16(KC_RPRN);
                    }

                    // Restore mods
                    set_mods(saved_mods);
                    set_oneshot_mods(oneshot_mods);
                }
            }
            break;

        case LBKT_LBRC_COMBO:
            if (pressed) {
                if (current_layer == _NAV) {
                    // NAV layer: output {
                    tap_code16(KC_LCBR);
                } else {
                    // DEF/NUM layer: output [
                    tap_code16(KC_LBRC);
                }
            }
            break;

        case RBKT_RBRC_COMBO:
            if (pressed) {
                if (current_layer == _NAV) {
                    // NAV layer: output }
                    tap_code16(KC_RCBR);
                } else {
                    // DEF/NUM layer: output ]
                    tap_code16(KC_RBRC);
                }
            }
            break;
    }
}
