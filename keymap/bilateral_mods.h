/* Copyright 2015-2023 Jack Humbert
 * GPL-2.0-or-later
 *
 * BILATERAL HOMEROW MODS CONFIGURATION
 * Based on urob's timeless homerow mod concepts
 */

#pragma once

#include QMK_KEYBOARD_H

/* ╔═══════════════════════════════════════════════════════════════════════════════════════════════════╗
 * ║  BILATERAL HOMEROW MODS CONFIGURATION                                                             ║
 * ║  Based on urob's timeless homerow mods - uses opposite hands to eliminate timing issues           ║
 * ╚═══════════════════════════════════════════════════════════════════════════════════════════════════╝ */

// Timing settings defined in config.h

// Left hand homerow mods (A, R, S, T)
#define HRM_A LGUI_T(KC_A)
#define HRM_R LALT_T(KC_R)
#define HRM_S LSFT_T(KC_S)
#define HRM_T LCTL_T(KC_T)

// Right hand homerow mods (N, E, I, O)
#define HRM_N RCTL_T(KC_N)
#define HRM_E RSFT_T(KC_E)
#define HRM_I RALT_T(KC_I)
#define HRM_O RGUI_T(KC_O)

// Number layer homerow mods (0, 4, 5, 6) - urob's layout
#define NUM_0 LGUI_T(KC_0)
#define NUM_4 LALT_T(KC_4)
#define NUM_5 LSFT_T(KC_5)
#define NUM_6 LCTL_T(KC_6)

/* ╔═════════════════════════════════════════════════════════════════════════════════════════════════════╗
 * ║  BILATERAL HOMEROW MODS CONFIGURATION FUNCTIONS                                                     ║
 * ╚═════════════════════════════════════════════════════════════════════════════════════════════════════╝ */

// Per-key tapping term - urob's approach uses consistent 280ms
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Homerow mods - base layer
        case HRM_A:
        case HRM_R:
        case HRM_S:
        case HRM_T:
        case HRM_N:
        case HRM_E:
        case HRM_I:
        case HRM_O:
        // Number layer homerow mods
        case NUM_0:
        case NUM_4:
        case NUM_5:
        case NUM_6:
            return TAPPING_TERM;  // Same 280ms as urob
        default:
            return TAPPING_TERM;
    }
}

// Bilateral combinations - only apply permissive hold to opposite hand combinations
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Apply permissive hold to all homerow mods for bilateral combinations
        // Base layer homerow mods
        case HRM_A:
        case HRM_R:
        case HRM_S:
        case HRM_T:
        case HRM_N:
        case HRM_E:
        case HRM_I:
        case HRM_O:
        // Number layer homerow mods
        case NUM_0:
        case NUM_4:
        case NUM_5:
        case NUM_6:
            return true;
        default:
            return false;
    }
}
