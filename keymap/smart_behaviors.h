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
bool leader_active = false;
uint16_t leader_timer = 0;
uint16_t leader_sequence[3] = {KC_NO, KC_NO, KC_NO};  // Track up to 3 keys for OS switching
uint8_t leader_sequence_count = 0;
bool smart_mouse_active = false;
uint16_t smart_mouse_tap_timer = 0;
uint16_t smart_spc_timer = 0;
bool alt_tab_active = false;

// SOCD cleaning variables for gaming layer
bool socd_w_pressed = false;
bool socd_s_pressed = false;
bool socd_a_pressed = false;
bool socd_d_pressed = false;
uint16_t socd_last_horizontal = KC_NO;  // Last pressed: A or D
uint16_t socd_last_vertical = KC_NO;    // Last pressed: W or S

/* ╔════════════════════════════════════════════════════════════════════════════════════════════════════╗
 * ║  SMART NUM-WORD BEHAVIOR (UROB'S AUTO-LAYER)                                                      ║
 * ║  Automatically deactivates NUM layer when pressing non-number keys                                 ║
 * ║  Allowed keys: 0-9, BSPC, DEL, and layer keys                                                      ║
 * ╚════════════════════════════════════════════════════════════════════════════════════════════════════╝ */

static void handle_num_word_logic(uint16_t keycode, keyrecord_t *record) {
    // Only process when Numword is active and a key is pressed
    if (!num_word_active || !record->event.pressed) {
        return;
    }

    // Check if the keycode should keep Numword active
    // Numword stays active for: numbers (0-9), homerow mod numbers, BSPC, DEL
    bool is_numword_key = (keycode >= KC_1 && keycode <= KC_0) ||  // Number keys on base layer
                          (keycode >= KC_7 && keycode <= KC_9) ||   // 7, 8, 9 on NUM layer
                          (keycode == NUM_0) ||                      // Homerow mod 0 (Cmd/0)
                          (keycode == NUM_4) ||                      // Homerow mod 4 (Alt/4)
                          (keycode == NUM_5) ||                      // Homerow mod 5 (Shift/5)
                          (keycode == NUM_6) ||                      // Homerow mod 6 (Ctrl/6)
                          (keycode == KC_BSPC) ||                    // Backspace
                          (keycode == KC_DEL) ||                     // Delete
                          (keycode == SMART_NUM) ||                  // The trigger key itself
                          (keycode == KC_NO) || (keycode == KC_TRNS);  // Layer passthroughs

    // If non-numword key pressed, deactivate Numword
    if (!is_numword_key) {
        num_word_active = false;
        layer_off(_NUM);
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
 * ║  SMART_NUM KEY BEHAVIOR (UROB'S NUMWORD)                                                          ║
 * ║  Tap = num-word (auto-exits on non-number keys), Hold = momentary NUM layer                        ║
 * ╚════════════════════════════════════════════════════════════════════════════════════════════════════╝ */

static bool handle_smart_num_key(uint16_t keycode, keyrecord_t *record) {
    if (keycode == SMART_NUM) {
        if (record->event.pressed) {
            smart_num_tap_timer = timer_read();
            layer_on(_NUM);  // Activate layer immediately for hold behavior
        } else {
            // On release, check if it was a tap or hold
            if (timer_elapsed(smart_num_tap_timer) < TAPPING_TERM) {
                // TAP: Activate Numword mode
                num_word_active = true;
                // Layer stays on via num_word_active flag
            } else {
                // HOLD: Was acting as momentary layer, now release it
                layer_off(_NUM);
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
    if (keycode == LEADER || keycode == LEADER_SFT) {
        if (record->event.pressed) {
            // If LEADER_SFT, activate one-shot shift first
            if (keycode == LEADER_SFT) {
                add_oneshot_mods(MOD_BIT(KC_LSFT));
            }
            leader_active = true;
            leader_timer = timer_read();
            leader_sequence_count = 0;
            for (int i = 0; i < 3; i++) {
                leader_sequence[i] = KC_NO;
            }
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
            leader_sequence_count = 0;
            return true;
        }

        // Add key to sequence
        if (leader_sequence_count < 3) {
            leader_sequence[leader_sequence_count++] = keycode;
        }

        // Check for shift state for uppercase variants (including one-shot mods)
        bool shift_held = (get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT;

        // Check for 3-key sequences (MAC, WIN, LIN)
        if (leader_sequence_count == 3) {
            // MAC sequence: M A C
            if (leader_sequence[0] == KC_M && leader_sequence[1] == KC_A && leader_sequence[2] == KC_C) {
                set_unicode_input_mode(UNICODE_MODE_MACOS);
                leader_active = false;
                leader_sequence_count = 0;
                return false;
            }
            // WIN sequence: W I N
            if (leader_sequence[0] == KC_W && leader_sequence[1] == HRM_I && leader_sequence[2] == HRM_N) {
                set_unicode_input_mode(UNICODE_MODE_WINCOMPOSE);
                leader_active = false;
                leader_sequence_count = 0;
                return false;
            }
            // LIN sequence: L I N
            if (leader_sequence[0] == KC_L && leader_sequence[1] == HRM_I && leader_sequence[2] == HRM_N) {
                set_unicode_input_mode(UNICODE_MODE_LINUX);
                leader_active = false;
                leader_sequence_count = 0;
                return false;
            }
            // If no match, cancel leader
            leader_active = false;
            leader_sequence_count = 0;
            return true;
        }

        // Check for 2-key sequences (French accents, ligatures)
        if (leader_sequence_count == 2) {
            uint16_t first = leader_sequence[0];
            uint16_t second = leader_sequence[1];

            // French E accents: E + modifier
            if (first == KC_E || first == HRM_E) {
                if (second == KC_G) {  // E G → è/È (grave)
                    if (shift_held) {
                        del_mods(MOD_MASK_SHIFT);
                        del_oneshot_mods(MOD_MASK_SHIFT);
                        register_unicode(0x00C8);  // È
                    } else {
                        register_unicode(0x00E8);  // è
                    }
                    leader_active = false;
                    leader_sequence_count = 0;
                    return false;
                } else if (second == KC_C) {  // E C → ê/Ê (circumflex)
                    if (shift_held) {
                        del_mods(MOD_MASK_SHIFT);
                        del_oneshot_mods(MOD_MASK_SHIFT);
                        register_unicode(0x00CA);  // Ê
                    } else {
                        register_unicode(0x00EA);  // ê
                    }
                    leader_active = false;
                    leader_sequence_count = 0;
                    return false;
                } else if (second == KC_D) {  // E D → ë/Ë (diaeresis)
                    if (shift_held) {
                        del_mods(MOD_MASK_SHIFT);
                        del_oneshot_mods(MOD_MASK_SHIFT);
                        register_unicode(0x00CB);  // Ë
                    } else {
                        register_unicode(0x00EB);  // ë
                    }
                    leader_active = false;
                    leader_sequence_count = 0;
                    return false;
                }
            }

            // French A accents: A + modifier
            if (first == KC_A || first == HRM_A) {
                if (second == KC_G) {  // A G → à/À (grave)
                    if (shift_held) {
                        del_mods(MOD_MASK_SHIFT);
                        del_oneshot_mods(MOD_MASK_SHIFT);
                        register_unicode(0x00C0);  // À
                    } else {
                        register_unicode(0x00E0);  // à
                    }
                    leader_active = false;
                    leader_sequence_count = 0;
                    return false;
                } else if (second == KC_C) {  // A C → â/Â (circumflex)
                    if (shift_held) {
                        del_mods(MOD_MASK_SHIFT);
                        del_oneshot_mods(MOD_MASK_SHIFT);
                        register_unicode(0x00C2);  // Â
                    } else {
                        register_unicode(0x00E2);  // â
                    }
                    leader_active = false;
                    leader_sequence_count = 0;
                    return false;
                } else if (second == KC_E || second == HRM_E) {  // A E → æ/Æ (ligature)
                    if (shift_held) {
                        del_mods(MOD_MASK_SHIFT);
                        del_oneshot_mods(MOD_MASK_SHIFT);
                        register_unicode(0x00C6);  // Æ
                    } else {
                        register_unicode(0x00E6);  // æ
                    }
                    leader_active = false;
                    leader_sequence_count = 0;
                    return false;
                }
            }

            // French O accents: O + modifier
            if (first == KC_O || first == HRM_O) {
                if (second == KC_C) {  // O C → ô/Ô (circumflex)
                    if (shift_held) {
                        del_mods(MOD_MASK_SHIFT);
                        del_oneshot_mods(MOD_MASK_SHIFT);
                        register_unicode(0x00D4);  // Ô
                    } else {
                        register_unicode(0x00F4);  // ô
                    }
                    leader_active = false;
                    leader_sequence_count = 0;
                    return false;
                } else if (second == KC_E || second == HRM_E) {  // O E → œ/Œ (ligature)
                    if (shift_held) {
                        del_mods(MOD_MASK_SHIFT);
                        del_oneshot_mods(MOD_MASK_SHIFT);
                        register_unicode(0x0152);  // Œ
                    } else {
                        register_unicode(0x0153);  // œ
                    }
                    leader_active = false;
                    leader_sequence_count = 0;
                    return false;
                }
            }

            // French I accents: I + modifier
            if (first == HRM_I) {
                if (second == KC_C) {  // I C → î/Î (circumflex)
                    if (shift_held) {
                        del_mods(MOD_MASK_SHIFT);
                        del_oneshot_mods(MOD_MASK_SHIFT);
                        register_unicode(0x00CE);  // Î
                    } else {
                        register_unicode(0x00EE);  // î
                    }
                    leader_active = false;
                    leader_sequence_count = 0;
                    return false;
                } else if (second == KC_D) {  // I D → ï/Ï (diaeresis)
                    if (shift_held) {
                        del_mods(MOD_MASK_SHIFT);
                        del_oneshot_mods(MOD_MASK_SHIFT);
                        register_unicode(0x00CF);  // Ï
                    } else {
                        register_unicode(0x00EF);  // ï
                    }
                    leader_active = false;
                    leader_sequence_count = 0;
                    return false;
                }
            }

            // French U accents: U + modifier
            if (first == KC_U) {
                if (second == KC_G) {  // U G → ù/Ù (grave)
                    if (shift_held) {
                        del_mods(MOD_MASK_SHIFT);
                        del_oneshot_mods(MOD_MASK_SHIFT);
                        register_unicode(0x00D9);  // Ù
                    } else {
                        register_unicode(0x00F9);  // ù
                    }
                    leader_active = false;
                    leader_sequence_count = 0;
                    return false;
                } else if (second == KC_C) {  // U C → û/Û (circumflex)
                    if (shift_held) {
                        del_mods(MOD_MASK_SHIFT);
                        del_oneshot_mods(MOD_MASK_SHIFT);
                        register_unicode(0x00DB);  // Û
                    } else {
                        register_unicode(0x00FB);  // û
                    }
                    leader_active = false;
                    leader_sequence_count = 0;
                    return false;
                } else if (second == KC_D) {  // U D → ü/Ü (diaeresis)
                    if (shift_held) {
                        del_mods(MOD_MASK_SHIFT);
                        del_oneshot_mods(MOD_MASK_SHIFT);
                        register_unicode(0x00DC);  // Ü
                    } else {
                        register_unicode(0x00FC);  // ü
                    }
                    leader_active = false;
                    leader_sequence_count = 0;
                    return false;
                }
            }

            // French Y diaeresis: Y D → ÿ/Ÿ
            if (first == KC_Y && second == KC_D) {
                if (shift_held) {
                    del_mods(MOD_MASK_SHIFT);
                    del_oneshot_mods(MOD_MASK_SHIFT);
                    register_unicode(0x0178);  // Ÿ
                } else {
                    register_unicode(0x00FF);  // ÿ
                }
                leader_active = false;
                leader_sequence_count = 0;
                return false;
            }

            // If no 2-key match, might be part of 3-key sequence
            // Don't cancel yet, wait for third key or timeout
            return true;
        }

        // Single-key sequences (German umlauts, single French accents, currency)
        if (leader_sequence_count == 1) {
            switch (keycode) {
                // German umlauts
                case KC_A:
                case HRM_A:  // A → ä/Ä
                    if (shift_held) {
                        del_mods(MOD_MASK_SHIFT);
                        del_oneshot_mods(MOD_MASK_SHIFT);
                        register_unicode(0x00C4);  // Ä
                    } else {
                        register_unicode(0x00E4);  // ä
                    }
                    leader_active = false;
                    leader_sequence_count = 0;
                    return false;

                case KC_O:
                case HRM_O:  // O → ö/Ö
                    if (shift_held) {
                        del_mods(MOD_MASK_SHIFT);
                        del_oneshot_mods(MOD_MASK_SHIFT);
                        register_unicode(0x00D6);  // Ö
                    } else {
                        register_unicode(0x00F6);  // ö
                    }
                    leader_active = false;
                    leader_sequence_count = 0;
                    return false;

                case KC_U:  // U → ü/Ü
                    if (shift_held) {
                        del_mods(MOD_MASK_SHIFT);
                        del_oneshot_mods(MOD_MASK_SHIFT);
                        register_unicode(0x00DC);  // Ü
                    } else {
                        register_unicode(0x00FC);  // ü
                    }
                    leader_active = false;
                    leader_sequence_count = 0;
                    return false;

                case KC_S:
                case HRM_S:  // S → ß
                    register_unicode(0x00DF);  // ß
                    leader_active = false;
                    leader_sequence_count = 0;
                    return false;

                // French accents (single-key)
                case KC_E:
                case HRM_E:  // E → é/É (acute)
                    if (shift_held) {
                        del_mods(MOD_MASK_SHIFT);
                        del_oneshot_mods(MOD_MASK_SHIFT);
                        register_unicode(0x00C9);  // É
                    } else {
                        register_unicode(0x00E9);  // é
                    }
                    leader_active = false;
                    leader_sequence_count = 0;
                    return false;

                case KC_C:  // C → ç/Ç (cedilla)
                    if (shift_held) {
                        del_mods(MOD_MASK_SHIFT);
                        del_oneshot_mods(MOD_MASK_SHIFT);
                        register_unicode(0x00C7);  // Ç
                    } else {
                        register_unicode(0x00E7);  // ç
                    }
                    leader_active = false;
                    leader_sequence_count = 0;
                    return false;

                // Currency symbols
                case KC_4:  // 4 → € (euro)
                    register_unicode(0x20AC);  // €
                    leader_active = false;
                    leader_sequence_count = 0;
                    return false;

                case KC_3:  // 3 → £ (pound)
                    register_unicode(0x00A3);  // £
                    leader_active = false;
                    leader_sequence_count = 0;
                    return false;

                default:
                    // Don't cancel yet, might be multi-key sequence
                    break;
            }
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
 * ║  ALT+TAB SWAPPER BEHAVIOR (UROB-STYLE)                                                            ║
 * ║  Smart Alt+Tab that keeps the switcher open until explicitly cancelled                             ║
 * ╚════════════════════════════════════════════════════════════════════════════════════════════════════╝ */

static bool handle_alt_tab_swapper(uint16_t keycode, keyrecord_t *record) {
    if (keycode == ALT_TAB_FWD || keycode == ALT_TAB_REV) {
        if (record->event.pressed) {
            if (!alt_tab_active) {
                // First press: register Alt and press Tab
                alt_tab_active = true;
                register_code(KC_LALT);
            }
            // Press Tab (with Shift for reverse)
            if (keycode == ALT_TAB_REV) {
                register_code(KC_LSFT);
            }
            tap_code(KC_TAB);
            if (keycode == ALT_TAB_REV) {
                unregister_code(KC_LSFT);
            }
        }
        return false;
    }

    // Cancel swapper on any other key press (except ignored keys)
    if (alt_tab_active && record->event.pressed) {
        bool is_ignored_key = (keycode == ALT_TAB_FWD || keycode == ALT_TAB_REV ||
                              keycode == KC_LSFT || keycode == KC_RSFT ||
                              keycode == KC_LCTL || keycode == KC_RCTL ||
                              keycode == KC_LGUI || keycode == KC_RGUI);

        if (!is_ignored_key) {
            alt_tab_active = false;
            unregister_code(KC_LALT);
        }
    }

    return true;
}

/* ╔════════════════════════════════════════════════════════════════════════════════════════════════════╗
 * ║  SMART_SPC KEY BEHAVIOR (UROB'S LT_SPC)                                                           ║
 * ║  Tap = space, Hold = NAV layer, Shift+Tap = . then space then sticky-shift                        ║
 * ╚════════════════════════════════════════════════════════════════════════════════════════════════════╝ */

static bool handle_smart_spc_key(uint16_t keycode, keyrecord_t *record) {
    if (keycode == SMART_SPC) {
        if (record->event.pressed) {
            smart_spc_timer = timer_read();
            layer_on(_NAV);  // Activate NAV layer on hold
        } else {
            layer_off(_NAV);  // Deactivate NAV layer on release

            // Check if it was a tap (not a hold)
            if (timer_elapsed(smart_spc_timer) < TAPPING_TERM) {
                // Check if shift is held
                if (get_mods() & MOD_MASK_SHIFT) {
                    // Shift + tap: output . then space then activate sticky shift
                    del_mods(MOD_MASK_SHIFT);  // Temporarily remove shift
                    tap_code(KC_DOT);          // Type dot
                    tap_code(KC_SPC);          // Type space
                    set_oneshot_mods(MOD_BIT(KC_LSFT));  // Activate sticky shift for next char
                } else {
                    // Normal tap: just space
                    tap_code(KC_SPC);
                }
            }
        }
        return false;
    }
    return true;
}

/* ╔════════════════════════════════════════════════════════════════════════════════════════════════════╗
 * ║  SOCD CLEANING (SIMULTANEOUS OPPOSITE CARDINAL DIRECTIONS)                                        ║
 * ║  Last Input Priority (LIP) for W/A/S/D - prevents impossible inputs in competitive games           ║
 * ╚════════════════════════════════════════════════════════════════════════════════════════════════════╝ */

static void handle_socd_cleaning(uint16_t keycode, keyrecord_t *record) {
    // Only apply SOCD cleaning on gaming layer
    if (get_highest_layer(default_layer_state) != _GAMING) {
        return;
    }

    // Vertical axis (W/S)
    if (keycode == KC_W) {
        if (record->event.pressed) {
            socd_w_pressed = true;
            socd_last_vertical = KC_W;
            // If S is held, release it (Last Input Priority)
            if (socd_s_pressed) {
                unregister_code(KC_S);
            }
            register_code(KC_W);
        } else {
            socd_w_pressed = false;
            unregister_code(KC_W);
            // If S was being held, re-register it
            if (socd_s_pressed) {
                register_code(KC_S);
            }
        }
    } else if (keycode == KC_S) {
        if (record->event.pressed) {
            socd_s_pressed = true;
            socd_last_vertical = KC_S;
            // If W is held, release it (Last Input Priority)
            if (socd_w_pressed) {
                unregister_code(KC_W);
            }
            register_code(KC_S);
        } else {
            socd_s_pressed = false;
            unregister_code(KC_S);
            // If W was being held, re-register it
            if (socd_w_pressed) {
                register_code(KC_W);
            }
        }
    }

    // Horizontal axis (A/D)
    if (keycode == KC_A) {
        if (record->event.pressed) {
            socd_a_pressed = true;
            socd_last_horizontal = KC_A;
            // If D is held, release it (Last Input Priority)
            if (socd_d_pressed) {
                unregister_code(KC_D);
            }
            register_code(KC_A);
        } else {
            socd_a_pressed = false;
            unregister_code(KC_A);
            // If D was being held, re-register it
            if (socd_d_pressed) {
                register_code(KC_D);
            }
        }
    } else if (keycode == KC_D) {
        if (record->event.pressed) {
            socd_d_pressed = true;
            socd_last_horizontal = KC_D;
            // If A is held, release it (Last Input Priority)
            if (socd_a_pressed) {
                unregister_code(KC_A);
            }
            register_code(KC_D);
        } else {
            socd_d_pressed = false;
            unregister_code(KC_D);
            // If A was being held, re-register it
            if (socd_a_pressed) {
                register_code(KC_A);
            }
        }
    }
}

/* ╔════════════════════════════════════════════════════════════════════════════════════════════════════╗
 * ║  MAIN SMART BEHAVIOR PROCESSOR                                                                     ║
 * ║  Central dispatch function for all intelligent behaviors                                           ║
 * ╚════════════════════════════════════════════════════════════════════════════════════════════════════╝ */

bool process_smart_behaviors(uint16_t keycode, keyrecord_t *record) {
    // Handle SOCD cleaning for gaming layer (must be first to intercept W/A/S/D)
    if (get_highest_layer(default_layer_state) == _GAMING) {
        if (keycode == KC_W || keycode == KC_A || keycode == KC_S || keycode == KC_D) {
            handle_socd_cleaning(keycode, record);
            return false;  // SOCD handler manages the keycode completely
        }
    }

    // Handle Alt+Tab swapper first (affects global modifiers)
    if (!handle_alt_tab_swapper(keycode, record)) return false;

    // Handle smart mouse first (may affect layer state)
    if (!handle_smart_mouse_key(keycode, record)) return false;

    // Handle smart space key (lt_spc behavior)
    if (!handle_smart_spc_key(keycode, record)) return false;

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
