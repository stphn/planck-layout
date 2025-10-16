/* Copyright 2015-2023 Jack Humbert
 * GPL-2.0-or-later
 *
 * UROB'S SMART BEHAVIORS - Advanced Intelligence System
 * Based on urob's timeless homerow mod concepts
 */

#pragma once

#include QMK_KEYBOARD_H
#include "bilateral_mods.h"

/* ╔════════════════════════════════════════════════════════════════════════════════════════════════════╗
 * ║  SMART BEHAVIOR STATE VARIABLES                                                                    ║
 * ║  Implementation of state tracking for intelligent behaviors                                        ║
 * ╚════════════════════════════════════════════════════════════════════════════════════════════════════╝ */

// Smart behavior state variables
bool num_word_active = false;
uint16_t magic_shift_timer = 0;
uint16_t last_keycode = KC_NO;
bool last_key_was_alpha = false;
uint16_t magic_shift_tap_timer = 0;
bool caps_word_active = false;
uint16_t smart_num_tap_timer = 0;
bool sticky_num_active = false;
bool leader_active = false;
uint16_t leader_timer = 0;
bool smart_mouse_active = false;
uint16_t smart_mouse_tap_timer = 0;

// SOCD cleaning variables for gaming layer
bool socd_w_pressed = false;
bool socd_s_pressed = false;
bool socd_a_pressed = false;
bool socd_d_pressed = false;
uint16_t socd_last_horizontal = KC_NO;  // Last pressed: A or D
uint16_t socd_last_vertical = KC_NO;    // Last pressed: W or S

/* ╔════════════════════════════════════════════════════════════════════════════════════════════════════╗
 * ║  SMART NUM-WORD BEHAVIOR                                                                           ║
 * ║  Auto-exits from NUM layer on non-number key                                                       ║
 * ╚════════════════════════════════════════════════════════════════════════════════════════════════════╝ */

static void handle_num_word_logic(uint16_t keycode, keyrecord_t *record) {
    // Auto-activate num-word when typing numbers on base layer
    if (record->event.pressed && !num_word_active && !sticky_num_active &&
        keycode >= KC_1 && keycode <= KC_0 && get_highest_layer(layer_state) == 0) {
        num_word_active = true;
        layer_on(_NUM);
    }

    // Auto-exit num-word/sticky on non-number key
    if ((num_word_active || sticky_num_active) && record->event.pressed) {
        if (!(keycode >= KC_1 && keycode <= KC_0) && keycode != KC_BSPC && keycode != KC_DEL) {
            if (num_word_active) {
                num_word_active = false;
                layer_off(_NUM);
            }
            // Sticky num stays active until manually cancelled with SMART_NUM tap
        }
    }

    // Cancel sticky num on SMART_NUM tap (not hold)
    if (sticky_num_active && record->event.pressed && keycode == SMART_NUM) {
        sticky_num_active = false;
        if (!num_word_active) {
            layer_off(_NUM);
        }
    }
}

/* ╔════════════════════════════════════════════════════════════════════════════════════════════════════╗
 * ║  KEYCODE TRACKING AND CAPS-WORD LOGIC                                                              ║
 * ║  Smart context awareness for intelligent behaviors                                                 ║
 * ╚════════════════════════════════════════════════════════════════════════════════════════════════════╝ */

static void handle_keycode_tracking(uint16_t keycode, keyrecord_t *record) {
    // Track last keycode for MAGIC_SHIFT repeat behavior
    if (record->event.pressed && keycode != MAGIC_SHIFT) {
        // Check if it's an alpha key (A-Z or homerow mods)
        bool is_alpha = (keycode >= KC_A && keycode <= KC_Z) ||
                       (keycode == HRM_A) || (keycode == HRM_R) || (keycode == HRM_S) || (keycode == HRM_T) ||
                       (keycode == HRM_N) || (keycode == HRM_E) || (keycode == HRM_I) || (keycode == HRM_O);

        if (is_alpha) {
            // For homerow mods, store the base keycode for repeat
            if (keycode == HRM_A) last_keycode = KC_A;
            else if (keycode == HRM_R) last_keycode = KC_R;
            else if (keycode == HRM_S) last_keycode = KC_S;
            else if (keycode == HRM_T) last_keycode = KC_T;
            else if (keycode == HRM_N) last_keycode = KC_N;
            else if (keycode == HRM_E) last_keycode = KC_E;
            else if (keycode == HRM_I) last_keycode = KC_I;
            else if (keycode == HRM_O) last_keycode = KC_O;
            else last_keycode = keycode; // Regular alpha key

            last_key_was_alpha = true;
        } else {
            last_key_was_alpha = false;
        }

        // Handle caps-word mode
        if (caps_word_active) {
            if (is_alpha) {
                // Capitalize alpha keys (including homerow mods)
                add_oneshot_mods(MOD_BIT(KC_LSFT));
            } else if (keycode == KC_MINS || keycode == KC_UNDS) {
                // Allow minus/underscore in caps-word
                // Do nothing, let it pass through
            } else if (keycode == KC_BSPC || keycode == KC_DEL) {
                // Allow backspace/delete in caps-word
                // Do nothing, let it pass through
            } else {
                // Any other key cancels caps-word
                caps_word_active = false;
            }
        }
    }
}

/* ╔════════════════════════════════════════════════════════════════════════════════════════════════════╗
 * ║  SMART_NUM KEY BEHAVIOR                                                                            ║
 * ║  Single tap = num-word, Double tap = sticky num, Hold = momentary NUM                              ║
 * ╚════════════════════════════════════════════════════════════════════════════════════════════════════╝ */

static bool handle_smart_num_key(uint16_t keycode, keyrecord_t *record) {
    if (keycode == SMART_NUM) {
        if (record->event.pressed) {
            magic_shift_timer = timer_read();
            layer_on(_NUM);
        } else {
            layer_off(_NUM);
            if (timer_elapsed(magic_shift_timer) < TAPPING_TERM) {
                // Check for double-tap (sticky NUM layer)
                if (timer_elapsed(smart_num_tap_timer) < TAPPING_TERM) {
                    sticky_num_active = true;
                    layer_on(_NUM);
                    smart_num_tap_timer = 0; // Reset timer
                } else {
                    // Single tap: activate num-word mode
                    num_word_active = true;
                    layer_on(_NUM);
                    smart_num_tap_timer = timer_read(); // Start double-tap timer
                }
            }
        }
        return false;
    }
    return true;
}

/* ╔═══════════════════════════════════════════════════════════════════════════════════════════════════╗
 * ║  MAGIC_SHIFT KEY BEHAVIOR                                                                         ║
 * ║  Single tap = repeat last alpha or sticky shift, Double tap = caps-word, Hold = shift             ║
 * ╚═══════════════════════════════════════════════════════════════════════════════════════════════════╝ */

static bool handle_magic_shift_key(uint16_t keycode, keyrecord_t *record) {
    if (keycode == MAGIC_SHIFT) {
        if (record->event.pressed) {
            magic_shift_timer = timer_read();
            register_mods(MOD_BIT(KC_LSFT));
        } else {
            unregister_mods(MOD_BIT(KC_LSFT));
            if (timer_elapsed(magic_shift_timer) < TAPPING_TERM) {
                // Check for double-tap (caps-word)
                if (timer_elapsed(magic_shift_tap_timer) < TAPPING_TERM) {
                    caps_word_active = true;
                    magic_shift_tap_timer = 0; // Reset timer
                } else {
                    // Single tap: context-sensitive behavior
                    if (last_key_was_alpha && last_keycode != KC_NO) {
                        // Repeat last alpha character
                        tap_code(last_keycode);
                    } else {
                        // Sticky shift for next character
                        set_oneshot_mods(MOD_BIT(KC_LSFT));
                    }
                    magic_shift_tap_timer = timer_read(); // Start double-tap timer
                }
            }
        }
        return false;
    }
    return true;
}

/* ╔════════════════════════════════════════════════════════════════════════════════════════════════════╗
 * ║  LEADER KEY SEQUENCES                                                                              ║
 * ║  International character input via leader + key combinations                                       ║
 * ╚════════════════════════════════════════════════════════════════════════════════════════════════════╝ */

static bool handle_leader_key(uint16_t keycode, keyrecord_t *record) {
    if (keycode == LEADER) {
        if (record->event.pressed) {
            leader_active = true;
            leader_timer = timer_read();
        }
        return false;
    }
    return true;
}

static bool handle_leader_sequences(uint16_t keycode, keyrecord_t *record) {
    if (leader_active && record->event.pressed) {
        if (timer_elapsed(leader_timer) > 3000) {
            // Leader timeout
            leader_active = false;
            return true;
        }

        // Check for shift state for uppercase variants (including one-shot mods)
        bool shift_held = (get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT;

        switch (keycode) {
            // A-umlaut: ä/Ä
            case KC_A:
            case HRM_A:     // Colemak A
                if (shift_held) {
                    del_mods(MOD_MASK_SHIFT);
                    del_oneshot_mods(MOD_MASK_SHIFT);
                    send_unicode_string("Ä");
                    add_mods(get_mods() & MOD_MASK_SHIFT);  // Restore only if it was a held mod
                } else {
                    send_unicode_string("ä");
                }
                leader_active = false;
                return false;

            // O-umlaut: ö/Ö
            case KC_O:
            case HRM_O:     // Colemak O
                if (shift_held) {
                    del_mods(MOD_MASK_SHIFT);
                    del_oneshot_mods(MOD_MASK_SHIFT);
                    send_unicode_string("Ö");
                    add_mods(get_mods() & MOD_MASK_SHIFT);  // Restore only if it was a held mod
                } else {
                    send_unicode_string("ö");
                }
                leader_active = false;
                return false;

            // U-umlaut: ü/Ü
            case KC_U:
                if (shift_held) {
                    del_mods(MOD_MASK_SHIFT);
                    del_oneshot_mods(MOD_MASK_SHIFT);
                    send_unicode_string("Ü");
                    add_mods(get_mods() & MOD_MASK_SHIFT);  // Restore only if it was a held mod
                } else {
                    send_unicode_string("ü");
                }
                leader_active = false;
                return false;

            // S-eszett: ß
            case KC_S:
            case HRM_S:     // Colemak S
                send_unicode_string("ß");
                leader_active = false;
                return false;

            // E-acute: é/É
            case KC_E:
            case HRM_E:     // Colemak E
                if (shift_held) {
                    del_mods(MOD_MASK_SHIFT);
                    del_oneshot_mods(MOD_MASK_SHIFT);
                    send_unicode_string("É");
                    add_mods(get_mods() & MOD_MASK_SHIFT);  // Restore only if it was a held mod
                } else {
                    send_unicode_string("é");
                }
                leader_active = false;
                return false;

            // C-cedilla: ç
            case KC_C:
                send_unicode_string("ç");
                leader_active = false;
                return false;

            // N-tilde: ñ
            case KC_N:
            case HRM_N:     // Colemak N
                send_unicode_string("ñ");
                leader_active = false;
                return false;

            // Grave accents: à/À (G for "grave")
            case KC_G:
                if (shift_held) {
                    del_mods(MOD_MASK_SHIFT);
                    del_oneshot_mods(MOD_MASK_SHIFT);
                    send_unicode_string("À");  // A-grave
                    add_mods(get_mods() & MOD_MASK_SHIFT);  // Restore only if it was a held mod
                } else {
                    send_unicode_string("à");  // a-grave
                }
                leader_active = false;
                return false;

            // Circumflex accents: â/Â (T for "tilde/circumflex")
            case KC_T:
            case HRM_T:     // Colemak T
                if (shift_held) {
                    del_mods(MOD_MASK_SHIFT);
                    del_oneshot_mods(MOD_MASK_SHIFT);
                    send_unicode_string("Â");  // A-circumflex
                    add_mods(get_mods() & MOD_MASK_SHIFT);  // Restore only if it was a held mod
                } else {
                    send_unicode_string("â");  // a-circumflex
                }
                leader_active = false;
                return false;

            // Euro symbol (4 key, like $)
            case KC_4:
                send_unicode_string("€");
                leader_active = false;
                return false;

            // British Pound (3 key, like #)
            case KC_3:
                send_unicode_string("£");
                leader_active = false;
                return false;

            default:
                // Cancel leader on any other key
                leader_active = false;
                break;
        }
    }
    return true;
}

/* ╔════════════════════════════════════════════════════════════════════════════════════════════════════╗
 * ║  SMART_MOUSE KEY BEHAVIOR (UROB-STYLE)                                                            ║
 * ║  Activates mouse layer with auto-exit on key press outside ignored positions                       ║
 * ╚════════════════════════════════════════════════════════════════════════════════════════════════════╝ */

static bool handle_smart_mouse_key(uint16_t keycode, keyrecord_t *record) {
    if (keycode == SMART_MOUSE) {
        if (record->event.pressed) {
            if (smart_mouse_active) {
                // Already active, turn it off
                smart_mouse_active = false;
                layer_off(_MOUSE);
            } else {
                // Activate mouse layer
                smart_mouse_active = true;
                layer_on(_MOUSE);
            }
        }
        return false;
    }

    // Auto-exit mouse layer on key press (except movement/scroll/button keys and modifiers)
    if (smart_mouse_active && record->event.pressed) {
        bool is_mouse_key = (keycode >= MS_UP && keycode <= MS_RGHT) ||
                           (keycode >= MS_BTN1 && keycode <= MS_BTN8) ||
                           (keycode >= MS_WHLU && keycode <= MS_WHLR) ||
                           (keycode == KC_PGUP || keycode == KC_PGDN) ||
                           (keycode == KC_LGUI || keycode == KC_LALT ||
                            keycode == KC_LSFT || keycode == KC_LCTL ||
                            keycode == SMART_MOUSE || keycode == MOUSE);

        if (!is_mouse_key) {
            smart_mouse_active = false;
            layer_off(_MOUSE);
        }
    }

    return true;
}

/* ╔════════════════════════════════════════════════════════════════════════════════════════════════════╗
 * ║  DESKTOP MANAGEMENT KEYS                                                                           ║
 * ║  macOS desktop switching and window pinning functions                                              ║
 * ╚════════════════════════════════════════════════════════════════════════════════════════════════════╝ */

static bool handle_desktop_keys(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DSK_PREV:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI));
                tap_code(KC_LEFT);
                unregister_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI));
            }
            return false;

        case DSK_NEXT:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI));
                tap_code(KC_RIGHT);
                unregister_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI));
            }
            return false;

        case PIN_WIN:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI) | MOD_BIT(KC_LSFT));
                tap_code(KC_Q);
                unregister_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI) | MOD_BIT(KC_LSFT));
            }
            return false;

        case PIN_APP:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI) | MOD_BIT(KC_LSFT));
                tap_code(KC_A);
                unregister_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI) | MOD_BIT(KC_LSFT));
            }
            return false;

        case DSK_MGR:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LALT));
                tap_code(KC_GRAVE);
                unregister_mods(MOD_BIT(KC_LALT));
            }
            return false;
    }
    return true;
}

/* ╔════════════════════════════════════════════════════════════════════════════════════════════════════╗
 * ║  MAIN SMART BEHAVIOR PROCESSOR                                                                     ║
 * ║  Central dispatch function for all intelligent behaviors                                           ║
 * ╚════════════════════════════════════════════════════════════════════════════════════════════════════╝ */

bool process_smart_behaviors(uint16_t keycode, keyrecord_t *record) {
    // Handle smart mouse first (may affect layer state)
    if (!handle_smart_mouse_key(keycode, record)) return false;

    // Handle num-word logic first (affects layer state)
    handle_num_word_logic(keycode, record);

    // Handle keycode tracking and caps-word
    handle_keycode_tracking(keycode, record);

    // Handle specific smart keys
    if (!handle_smart_num_key(keycode, record)) return false;
    if (!handle_magic_shift_key(keycode, record)) return false;
    if (!handle_leader_key(keycode, record)) return false;
    if (!handle_desktop_keys(keycode, record)) return false;

    // Handle leader sequences
    if (!handle_leader_sequences(keycode, record)) return false;

    return true;
}
