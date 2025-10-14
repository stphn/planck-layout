/* Copyright 2015-2023 Jack Humbert
 * GPL-2.0-or-later
 *
 * RGB MATRIX EFFECTS AND LED CONTROL
 * Professional RGB lighting system for Planck keyboard
 */

#pragma once

#include QMK_KEYBOARD_H

/* ----- Safe RGB fallbacks so it still compiles without RGB Matrix ----- */
#if !defined(RGB_MATRIX_ENABLE)
#    define RM_TOGG KC_NO
#    define RM_NEXT KC_NO
#    define RM_HUEU KC_NO
#    define RM_HUED KC_NO
#    define RM_SATU KC_NO
#    define RM_SATD KC_NO
#    define RM_VALU KC_NO
#    define RM_VALD KC_NO
#endif

#ifdef RGB_MATRIX_ENABLE

/* ╔═══════════════════════════════════════════════════════════════════════════════════════════════════╗
 * ║  LED GROUP DEFINITIONS                                                                            ║
 * ║  Physical LED positions mapped to keyboard layout                                                 ║
 * ╚═══════════════════════════════════════════════════════════════════════════════════════════════════╝ */

// LED groups (left→right)
const uint8_t LED_TOP[]    = {6, 5, 4, 3};
const uint8_t LED_MID[]    = {0};
const uint8_t LED_BOTTOM[] = {7, 8, 1, 2};
const uint8_t LED_ALL[]    = {0, 1, 2, 3, 4, 5, 6, 7, 8};
const uint8_t LED_LEFT[]   = {6, 7};
const uint8_t LED_RIGHT[]  = {3, 2};

/* ╔═══════════════════════════════════════════════════════════════════════════════════════════════════╗
 * ║  RGB UTILITY FUNCTIONS                                                                            ║
 * ║  Helper functions for LED group control and color management                                      ║
 * ╚═══════════════════════════════════════════════════════════════════════════════════════════════════╝ */

// Set color for a group of LEDs using RGB values
static inline void set_group_color(const uint8_t *grp, uint8_t cnt, uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t i = 0; i < cnt; i++) rgb_matrix_set_color(grp[i], r, g, b);
}

// Set color for a group of LEDs using HSV values
static inline void set_group_hsv(const uint8_t *grp, uint8_t cnt, uint8_t h, uint8_t s, uint8_t v) {
    RGB c = hsv_to_rgb((HSV){h, s, v});
    for (uint8_t i = 0; i < cnt; i++) {
        rgb_matrix_set_color(grp[i], c.r, c.g, c.b);
    }
}

/* ╔════════════════════════════════════════════════════════════════════════════════════════════════════╗
 * ║  LAYER INDICATOR SYSTEM                                                                            ║
 * ║  Visual feedback for active layers and modes                                                       ║
 * ╚════════════════════════════════════════════════════════════════════════════════════════════════════╝ */
bool rgb_matrix_indicators_user(void) {
    // Gaming layer visual feedback - subtle red corner indicators only
    if (get_highest_layer(default_layer_state) == _GAMING) {
        // Red indicators in corners only, allowing RGB effects to continue
        set_group_color(LED_LEFT, ARRAY_SIZE(LED_LEFT), 255, 0, 0);   // Left corners
        set_group_color(LED_RIGHT, ARRAY_SIZE(LED_RIGHT), 255, 0, 0); // Right corners
        return false; // allow RGB effects to continue
    }

    // Layer-specific lighting disabled as requested
    // RGB matrix effects (RM_NEXT, etc.) still work
    return false; // keep animations
}

// Built-in RGB matrix effects are enabled and will be accessible via RM_NEXT
// Custom effects removed due to QMK compilation complexity

// Layer-specific lighting functions (placeholders for future use)
void indicate_gaming_layer(void);
void indicate_num_layer(void);
void indicate_function_layer(void);
void indicate_nav_layer(void);
void indicate_system_layer(void);
void indicate_midi_layer(void);

#endif // RGB_MATRIX_ENABLE
