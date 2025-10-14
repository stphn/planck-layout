/* Copyright 2015-2023 Jack Humbert
 * GPL-2.0-or-later
 *
 * EXPERIMENTAL VERSION with Bilateral Homerow Mods
 * Based on urob's timeless homerow mod concepts
 */

#include QMK_KEYBOARD_H
#include "user_song_list.h"
#include "../password.h"

// Include our modular components
#include "custom_keycodes.h"
#include "bilateral_mods.h"
#include "smart_behaviors.h"
#include "combo_system.h"
#include "rgb_effects.h"
#include "layer_layouts.h"

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

extern keymap_config_t keymap_config;

// Urob's ?/! mod-morph (more linguistic than /?)
const key_override_t qexcl_override = ko_make_basic(MOD_MASK_SHIFT, KC_QUES, KC_EXLM);
const key_override_t *key_overrides[] = {
    &qexcl_override,
    NULL // Terminate the array
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_DEF] = LAYOUT_planck_grid(
    KC_TAB,        KC_Q,  KC_W,       KC_F,   KC_P,    KC_B,            KC_J,           KC_L,  KC_U,    KC_Y,         KC_SCLN,          KC_BSPC,
    KC_ESC,        HRM_A, HRM_R,      HRM_S,  HRM_T,   KC_G,            KC_M,           HRM_N, HRM_E,   HRM_I,        HRM_O,            KC_QUOT,
    OSM(MOD_LSFT), KC_Z,  KC_X,       KC_C,   KC_D,    KC_V,            KC_K,           KC_H,  KC_COMM, KC_DOT,       KC_QUES,          OSM(MOD_RSFT),
    PSWD, KC_LALT, HYPR(KC_NO), NUM, LT(_NAV, KC_SPC), LT(_FN, KC_ENT), SMART_NUM, MAGIC_SHIFT, KC_F18, GAMING, KC_RALT, KC_RBRC
),

[_NUM] = LAYOUT_planck_grid(
    _______ , _______ , KC_7    , KC_8    , KC_9    , _______ , _______ , _______ , _______ , _______ , _______ , _______,
    _______ , KC_0    , KC_4    , KC_5    , KC_6    , _______ , _______ , _______ , _______ , _______ , _______ , _______,
    _______ , _______ , KC_1    , KC_2    , KC_3    , _______ , _______ , _______ , _______ , _______ , _______ , _______,
    _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
),

[_GAMING] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    GAME_ESC,KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL, KC_LALT, KC_LGUI, NUM,     KC_SPC,  KC_ENT,  KC_SPC,  NUM,     MO(_SYS),DEF,     KC_RALT, KC_RCTL
),

[_FN] = LAYOUT_planck_grid(
    _______ , KC_F12  , KC_F7   , KC_F8   , KC_F9   , _______ , _______ , KC_MPRV , KC_VOLU , KC_MNXT , _______ , _______,
    _______ , LGUI_T(KC_F11), LALT_T(KC_F4), LSFT_T(KC_F5), LCTL_T(KC_F6), _______ , _______ , DSK_PREV, RSFT_T(KC_VOLD), DSK_NEXT, _______ , _______,
    _______ , KC_F10  , KC_F1   , KC_F2   , KC_F3   , _______ , _______ , PIN_APP , PIN_WIN , DSK_MGR , _______ , _______,
    _______ , _______ , _______ , _______ , _______ , _______ , _______ ,  KC_MPLY ,_______, _______ , _______ , _______
),

[_SYS] = LAYOUT_planck_grid(
    DEF    , AU_ON  , AU_OFF , _______, _______, RM_TOGG, _______, RM_NEXT, RM_HUEU, RM_SATU, RM_VALU, _______,
    _______ , MU_ON  , MU_OFF , _______, _______, QK_BOOT, QK_BOOT, RM_PREV, RM_HUED, RM_SATD, RM_VALD, _______,
    MIDI   , MI_ON  , MI_OFF , _______, _______, EE_CLR , EE_CLR , _______, _______, _______, _______, _______,
    GAMING , AU_PREV, AU_NEXT, _______, _______, _______, _______, _______, _______, _______, _______, DB_TOGG
),

[_NAV] = LAYOUT_planck_grid(
    _______ , LALT(KC_F4), _______ , LSFT(KC_TAB), LALT(KC_TAB), _______ , KC_PGUP, NAV_BSPC, KC_UP   , NAV_DEL , _______ , _______,
    _______ , OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LSFT), OSM(MOD_LCTL), _______ , KC_PGDN, KC_LEFT , KC_DOWN , KC_RGHT , KC_ENT  , _______,
    _______ , _______, _______, _______, _______, _______ , KC_INS , KC_TAB  , _______ , _______ , _______ , _______,
    _______ , _______, _______, _______, _______, _______ , KC_CNCL, _______ , _______ , _______ , _______ , _______
),

[_MIDI] = LAYOUT_planck_grid(
    MI_OCN2,   MI_OCN1,   MI_OC1,  MI_OC2,   MI_VELD, MI_VELU, MI_TRSD, MI_TRSU, MI_SUST, MI_SOFT, MI_AOFF, MIDI,
    MI_Cs,     MI_Ds,     _______, MI_Fs,    MI_Gs,   MI_As,   _______, MI_Cs,   MI_Ds,   _______,  MI_Fs,   MI_Gs,
    MI_C,      MI_D,      MI_E,    MI_F,     MI_G,    MI_A,    MI_B,    MI_C,    MI_D,    MI_E,     MI_F,    MI_G,
    MIDI,      _______,   _______, _______,  _______, _______, _______, _______, _______, _______,  _______, _______
),
};


#ifdef AUDIO_ENABLE
float gaming_on_song[][2] = SONG(STARTUP_SOUND);
float gaming_off_song[][2] = SONG(GOODBYE_SOUND);
float coin_up[][2]        = SONG(AUDIO_ON_SOUND);
float mario_game_over[][2] = SONG(MARIO_GAMEOVER);
float midi_layer_on[][2]  = SONG(MIDI_ON_SOUND);
float midi_layer_off[][2] = SONG(MIDI_OFF_SOUND);
#endif

// Keep animations dynamic: only tri-layer logic here.
layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _FN, _NUM, _SYS);

    static bool midi_was_on = false;
    bool midi_is_on = layer_state_cmp(state, _MIDI);

    if (midi_is_on && !midi_was_on) {
        // Entering MIDI layer - enable MIDI
        #ifdef MIDI_ENABLE
            midi_on();
        #endif
        #ifdef AUDIO_ENABLE
            PLAY_SONG(midi_layer_on);
        #endif
    } else if (!midi_is_on && midi_was_on) {
        // Exiting MIDI layer - disable MIDI
        #ifdef MIDI_ENABLE
            midi_off();
        #endif
        #ifdef AUDIO_ENABLE
            PLAY_SONG(midi_layer_off);
        #endif
    }
    midi_was_on = midi_is_on;

    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Handle smart behaviors first
    if (!process_smart_behaviors(keycode, record)) {
        return false;
    }

    #ifdef CONSOLE_ENABLE
        if (record->event.pressed) {
            uint8_t r = record->event.key.row;
            uint8_t c = record->event.key.col;

        if (r < MATRIX_ROWS && c < MATRIX_COLS) {
            uint8_t led = g_led_config.matrix_co[r][c];   // key -> LED index
            if (led != NO_LED) {
                uprintf("Key r=%u c=%u -> led=%u\n", r, c, led);
            } else {
                uprintf("Key r=%u c=%u -> led=NO_LED\n", r, c);
            }
        } else {
            uprintf("Key r=%u c=%u out of range\n", r, c);
        }
    }
    #endif

    switch (keycode) {
        case LT(0, KC_ENT):
            if (record->tap.count && record->event.pressed) {
                tap_code(KC_ENT);  // Tap: Enter
            } else if (record->event.pressed) {
                register_code(KC_LALT);  // Hold: Alt
            } else if (!record->tap.count) {
                unregister_code(KC_LALT);  // Release hold
            }
            return false;

        case DEF:
            if (record->event.pressed) set_single_persistent_default_layer(_DEF);
            return false;

        case GAMING:
            if (record->event.pressed) {
                if (get_highest_layer(default_layer_state) == _GAMING) {
                    // Currently in gaming mode, switch back to DEF
                    set_single_persistent_default_layer(_DEF);
                    #ifdef AUDIO_ENABLE
                    PLAY_SONG(gaming_off_song);
                    #endif
                } else {
                    // Not in gaming mode, switch to gaming
                    set_single_persistent_default_layer(_GAMING);
                    #ifdef AUDIO_ENABLE
                    PLAY_SONG(gaming_on_song);
                    #endif
                }
            }
            return false;

        case BACKLIT:
            if (record->event.pressed) register_code(KC_RSFT);
            else                        unregister_code(KC_RSFT);
            return false;

        case NAV_BSPC:
            if (record->event.pressed) {
                register_code(KC_BSPC);
            } else {
                unregister_code(KC_BSPC);
            }
            return false;

        case NAV_DEL:
            if (record->event.pressed) {
                register_code(KC_DEL);
            } else {
                unregister_code(KC_DEL);
            }
            return false;

        case PSWD:
            if (record->event.pressed) {
                SEND_STRING(PASSWORD_STRING);
            }
            return false;
    }

    return true;
}

/* ───────────────────────── Encoder fun (optional) ─────────────────────── */
deferred_token tokens[8];

uint32_t reset_note(uint32_t trigger_time, void *note) {
    *(float *)note = 440.0f;
    return 0;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    #ifdef AUDIO_ENABLE
        static float melody[2][2] = { {440.0f, 8}, {440.0f, 24} };
        cancel_deferred_exec(tokens[index]);
        if (clockwise) {
            melody[1][0] *= 1.059463f;        // +1 semitone
            melody[0][0]  = melody[1][0] / 1.498307f;
        } else {
            melody[1][0] /= 1.059463f;        // -1 semitone
            melody[0][0]  = melody[1][0] * 1.414214f;
        }
        audio_play_melody(&melody, 2, false);
        tokens[index] = defer_exec(1000, reset_note, &melody[1][0]);
    #endif
    return false;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
            if (active) {
                layer_on(_SYS);
            } else {
                layer_off(_SYS);
            }

            break;
        }
    }
    return true;
}
