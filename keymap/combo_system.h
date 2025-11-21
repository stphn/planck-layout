/* Copyright 2015-2023 Jack Humbert
 * GPL-2.0-or-later
 *
 * SMART COMBOS - UROB'S POSITIONAL SYSTEM
 * Based on urob's ZMK config using physical positions instead of letters
 */

#pragma once

#include QMK_KEYBOARD_H
#include "bilateral_mods.h"
#include "custom_keycodes.h"  // For U_NAV_* keycodes

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
    LEADER_COMBO,    // S+T = Leader key (urob's LM2+LM1)
    LEADER_SFT_COMBO, // R+S+T = Shifted leader (urob's LM3+LM2+LM1)

    // urob's mouse layer activation
    MOUSE_COMBO,     // F+P = Smart Mouse toggle (urob's LT2+LT1)

    // urob's horizontal combos (left hand)
    TAB_COMBO,       // R+S = Tab (urob's LM3+LM2)
    CUT_COMBO,       // X+D = Cut (urob's LB3+LB1)
    COPY_COMBO,      // X+C = Copy (urob's LB3+LB2)
    PASTE_COMBO,     // C+D = Paste (urob's LB2+LB1)

    // urob's horizontal combos (right hand)
    DEL_COMBO,       // U+Y = Delete
    LPRN_LT_COMBO,   // N+E = ( or < (RM1+RM2, shift-modified, like urob's lpar_lt)
    RPRN_GT_COMBO,   // E+I = ) or > (RM2+RM3, shift-modified, like urob's rpar_gt)
    LBKT_LBRC_COMBO, // H+, = [ on DEF/NUM, { on NAV (layer-specific)
    RBKT_RBRC_COMBO, // ,+. = ] on DEF/NUM, } on NAV (layer-specific)

    // NAV layer versions (same physical positions, different keycodes)
    BSPC_COMBO_NAV,  // U_NAV_BS+U_NAV_U = Backspace (same as L+U on base layer)
    DEL_COMBO_NAV,   // U_NAV_U+U_NAV_DEL = Delete (same as U+Y on base layer)

    // urob's vertical symbol combos (left hand)
    AT_COMBO,        // W+R = @ (urob's LT3+LM3)
    HASH_COMBO,      // F+S = # (urob's LT2+LM2)
    DOLLAR_COMBO,    // P+T = $ (urob's LT1+LM1)
    PERCENT_COMBO,   // B+G = % (urob's LT0+LM0)
    GRAVE_COMBO,     // R+X = ` (urob's LM3+LB3)
    BACKSLASH_COMBO, // S+C = \ (urob's LM2+LB2)
    EQUALS_COMBO,    // T+D = = (urob's LM1+LB1)
    TILDE_COMBO,     // G+V = ~ (urob's LM0+LB0)

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

// NAV layer versions
extern const uint16_t PROGMEM bspc_combo_nav[];
extern const uint16_t PROGMEM del_combo_nav[];

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
const uint16_t PROGMEM esc_combo[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM bspc_combo[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM leader_combo[] = {HRM_S, HRM_T, COMBO_END};
const uint16_t PROGMEM leader_sft_combo[] = {HRM_R, HRM_S, HRM_T, COMBO_END};
const uint16_t PROGMEM mouse_combo[] = {KC_F, KC_P, COMBO_END};

// urob's horizontal combos (left hand)
const uint16_t PROGMEM tab_combo[] = {HRM_R, HRM_S, COMBO_END};
const uint16_t PROGMEM cut_combo[] = {KC_X, KC_D, COMBO_END};
const uint16_t PROGMEM copy_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_C, KC_D, COMBO_END};

// urob's horizontal combos (right hand)
const uint16_t PROGMEM del_combo[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM lprn_lt_combo[] = {HRM_N, HRM_E, COMBO_END};
const uint16_t PROGMEM rprn_gt_combo[] = {HRM_E, HRM_I, COMBO_END};
const uint16_t PROGMEM lbkt_lbrc_combo[] = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM rbkt_rbrc_combo[] = {KC_COMM, KC_DOT, COMBO_END};

// NAV layer versions (same physical positions, U_NAV_* keycodes)
const uint16_t PROGMEM bspc_combo_nav[] = {U_NAV_BS, U_NAV_U, COMBO_END};
const uint16_t PROGMEM del_combo_nav[] = {U_NAV_U, U_NAV_DEL, COMBO_END};

// urob's vertical symbol combos (left hand)
const uint16_t PROGMEM at_combo[] = {KC_W, HRM_R, COMBO_END};
const uint16_t PROGMEM hash_combo[] = {KC_F, HRM_S, COMBO_END};
const uint16_t PROGMEM dollar_combo[] = {KC_P, HRM_T, COMBO_END};
const uint16_t PROGMEM percent_combo[] = {KC_B, KC_G, COMBO_END};
const uint16_t PROGMEM grave_combo[] = {HRM_R, KC_X, COMBO_END};
const uint16_t PROGMEM backslash_combo[] = {HRM_S, KC_C, COMBO_END};
const uint16_t PROGMEM equals_combo[] = {HRM_T, KC_D, COMBO_END};
const uint16_t PROGMEM tilde_combo[] = {KC_G, KC_V, COMBO_END};

// urob's vertical symbol combos (right hand)
const uint16_t PROGMEM caret_combo[] = {KC_J, KC_M, COMBO_END};
const uint16_t PROGMEM plus_combo[] = {KC_L, HRM_N, COMBO_END};
const uint16_t PROGMEM star_combo[] = {KC_U, HRM_E, COMBO_END};
const uint16_t PROGMEM amper_combo[] = {KC_Y, HRM_I, COMBO_END};
const uint16_t PROGMEM underscore_combo[] = {KC_M, KC_K, COMBO_END};
const uint16_t PROGMEM minus_combo[] = {HRM_N, KC_H, COMBO_END};
const uint16_t PROGMEM slash_combo[] = {HRM_E, KC_COMM, COMBO_END};
const uint16_t PROGMEM pipe_combo[] = {HRM_I, KC_DOT, COMBO_END};

combo_t key_combos[] = {
    [ESC_COMBO] = COMBO(esc_combo, KC_ESC),
    [BSPC_COMBO] = COMBO(bspc_combo, KC_BSPC),
    [LEADER_COMBO] = COMBO(leader_combo, LEADER),
    [LEADER_SFT_COMBO] = COMBO(leader_sft_combo, LEADER_SFT),
    [MOUSE_COMBO] = COMBO(mouse_combo, SMART_MOUSE),

    [TAB_COMBO] = COMBO(tab_combo, KC_TAB),
    [CUT_COMBO] = COMBO(cut_combo, LGUI(KC_X)),
    [COPY_COMBO] = COMBO(copy_combo, LGUI(KC_C)),
    [PASTE_COMBO] = COMBO(paste_combo, LGUI(KC_V)),

    [DEL_COMBO] = COMBO(del_combo, KC_DEL),
    [LPRN_LT_COMBO] = COMBO_ACTION(lprn_lt_combo),
    [RPRN_GT_COMBO] = COMBO_ACTION(rprn_gt_combo),
    [LBKT_LBRC_COMBO] = COMBO_ACTION(lbkt_lbrc_combo),
    [RBKT_RBRC_COMBO] = COMBO_ACTION(rbkt_rbrc_combo),

    // NAV layer versions (trigger combos even when hold-tap keys are in those positions)
    [BSPC_COMBO_NAV] = COMBO(bspc_combo_nav, KC_BSPC),
    [DEL_COMBO_NAV] = COMBO(del_combo_nav, KC_DEL),

    [AT_COMBO] = COMBO(at_combo, KC_AT),
    [HASH_COMBO] = COMBO(hash_combo, KC_HASH),
    [DOLLAR_COMBO] = COMBO(dollar_combo, KC_DLR),
    [PERCENT_COMBO] = COMBO(percent_combo, KC_PERC),
    [GRAVE_COMBO] = COMBO(grave_combo, KC_GRV),
    [BACKSLASH_COMBO] = COMBO(backslash_combo, KC_BSLS),
    [EQUALS_COMBO] = COMBO(equals_combo, KC_EQL),
    [TILDE_COMBO] = COMBO(tilde_combo, KC_TILD),

    [CARET_COMBO] = COMBO(caret_combo, KC_CIRC),
    [PLUS_COMBO] = COMBO(plus_combo, KC_PLUS),
    [STAR_COMBO] = COMBO(star_combo, KC_ASTR),
    [AMPER_COMBO] = COMBO(amper_combo, KC_AMPR),
    [UNDERSCORE_COMBO] = COMBO(underscore_combo, KC_UNDS),
    [MINUS_COMBO] = COMBO(minus_combo, KC_MINS),
    [SLASH_COMBO] = COMBO(slash_combo, KC_SLSH),
    [PIPE_COMBO] = COMBO(pipe_combo, KC_PIPE),
};

/* ╔═════════════════════════════════════════════════════════════════════════════╗
 * ║  COMBO TIMING AND CONTROL FUNCTIONS                                         ║
 * ║  Smart timing to work with bilateral homerow mods                           ║
 * ╚═════════════════════════════════════════════════════════════════════════════╝ */

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch (index) {
        case ESC_COMBO:
        case BSPC_COMBO:
        case BSPC_COMBO_NAV:  // NAV layer version needs same fast timing
        case MOUSE_COMBO:
            return 15;

        case LEADER_SFT_COMBO:
            return 25;

        case HASH_COMBO:
        case DOLLAR_COMBO:
        case PERCENT_COMBO:
        case PLUS_COMBO:
        case STAR_COMBO:
        case AMPER_COMBO:
            return 30;

        default:
            return COMBO_TERM;  // DEL_COMBO_NAV uses default 18ms
    }
}

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    uint8_t current_layer = get_highest_layer(layer_state);

    if (get_highest_layer(default_layer_state) == _GAMING) {
        return false;
    }

    switch (combo_index) {
        // Base layer combos - don't trigger on NAV layer (NAV versions will handle it)
        case BSPC_COMBO:
        case DEL_COMBO:
            return current_layer != _NAV;

        // NAV layer combos - only trigger on NAV layer
        case BSPC_COMBO_NAV:
        case DEL_COMBO_NAV:
            return current_layer == _NAV;

        case LBKT_LBRC_COMBO:
        case RBKT_RBRC_COMBO:
            return (current_layer == _DEF || current_layer == _NUM || current_layer == _NAV);

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
    uint8_t saved_mods = get_mods();
    uint8_t oneshot_mods = get_oneshot_mods();
    bool shift_held = (saved_mods | oneshot_mods) & MOD_MASK_SHIFT;

    switch (combo_index) {
        case LPRN_LT_COMBO:
            if (pressed) {
                if (current_layer == _NAV) {
                    tap_code16(KC_LT);
                } else {
                    clear_mods();
                    clear_oneshot_mods();
                    if (shift_held) {
                        tap_code16(KC_LT);
                    } else {
                        tap_code16(KC_LPRN);
                    }
                    set_mods(saved_mods);
                    set_oneshot_mods(oneshot_mods);
                }
            }
            break;

        case RPRN_GT_COMBO:
            if (pressed) {
                if (current_layer == _NAV) {
                    tap_code16(KC_GT);
                } else {
                    clear_mods();
                    clear_oneshot_mods();
                    if (shift_held) {
                        tap_code16(KC_GT);
                    } else {
                        tap_code16(KC_RPRN);
                    }
                    set_mods(saved_mods);
                    set_oneshot_mods(oneshot_mods);
                }
            }
            break;

        case LBKT_LBRC_COMBO:
            if (pressed) {
                if (current_layer == _NAV) {
                    tap_code16(KC_LCBR);
                } else {
                    tap_code16(KC_LBRC);
                }
            }
            break;

        case RBKT_RBRC_COMBO:
            if (pressed) {
                if (current_layer == _NAV) {
                    tap_code16(KC_RCBR);
                } else {
                    tap_code16(KC_RBRC);
                }
            }
            break;
    }
}
