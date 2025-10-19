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
#include "midi_enhanced.h"

#ifdef MIDI_ENABLE
    #include "process_midi.h"
    extern MidiDevice midi_device;
    extern midi_config_t midi_config;
#endif

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

extern keymap_config_t keymap_config;

// Urob's morphs - modifier-dependent key behaviors
// ?/! morph (more linguistic than /?)
const key_override_t qexcl_override = ko_make_basic(MOD_MASK_SHIFT, KC_QUES, KC_EXLM);

// Comma morph: , -> Shift: ; -> Shift+Ctrl: <
// NOTE: Inner morph MUST come before basic morph in array for proper priority
const key_override_t comma_inner_morph = ko_make_with_layers_and_negmods(
    MOD_MASK_CS, KC_COMM, KC_LT, ~0, MOD_MASK_ALT | MOD_MASK_GUI
);
const key_override_t comma_morph = ko_make_with_layers_and_negmods(
    MOD_MASK_SHIFT, KC_COMM, KC_SCLN, ~0, MOD_MASK_CTRL | MOD_MASK_ALT | MOD_MASK_GUI
);

// Dot morph: . -> Shift: : -> Shift+Ctrl: >
// NOTE: Inner morph MUST come before basic morph in array for proper priority
const key_override_t dot_inner_morph = ko_make_with_layers_and_negmods(
    MOD_MASK_CS, KC_DOT, KC_GT, ~0, MOD_MASK_ALT | MOD_MASK_GUI
);
const key_override_t dot_morph = ko_make_with_layers_and_negmods(
    MOD_MASK_SHIFT, KC_DOT, KC_COLN, ~0, MOD_MASK_CTRL | MOD_MASK_ALT | MOD_MASK_GUI
);

// Backspace/Delete morph: BSPC -> Shift: DEL -> RShift: Shift+DEL
const key_override_t bs_del_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

const key_override_t *key_overrides[] = {
    &qexcl_override,
    // NOTE: More specific overrides (Ctrl+Shift) MUST come before less specific ones (Shift only)
    &comma_inner_morph,     // Shift+Ctrl+, → <  (MUST be first)
    &comma_morph,           // Shift+, → ;
    &dot_inner_morph,       // Shift+Ctrl+. → >  (MUST be first)
    &dot_morph,             // Shift+. → :
    &bs_del_override,
    NULL // Terminate the array
};

/* ═══════════════════════════════════════════════════════════════════════════════════════════════════
 * TAP DANCE ACTIONS
 * Based on urob's copy/cut tap-dance behavior
 * ═══════════════════════════════════════════════════════════════════════════════════════════════════ */

// Tap: copy (Cmd+C) | Double-tap: cut (Cmd+X) - Mac shortcuts
tap_dance_action_t tap_dance_actions[] = {
    [TD_COPY_CUT] = ACTION_TAP_DANCE_DOUBLE(LGUI(KC_C), LGUI(KC_X)),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_DEF] = LAYOUT_planck_grid(
    KC_Q,  KC_W,   KC_F,    KC_P,   KC_B,    COPY_CUT,       KC_BSPC,           KC_J, KC_L,    KC_U,    KC_Y,    KC_SCLN,
    HRM_A, HRM_R,  HRM_S,   HRM_T,  KC_G,    LGUI(KC_Z),     SGUI(KC_Z),        KC_M, HRM_N,   HRM_E,   HRM_I,   HRM_O,
    KC_Z,  KC_X,   KC_C,    KC_D,   KC_V,    LGUI(KC_S),     LGUI(KC_F),        KC_K, KC_H,    KC_COMM, KC_DOT,  KC_QUES,
    PSWD,  HYPR(KC_NO), _______, KC_LGUI, SMART_SPC, LT(_FN, KC_ENT), SMART_NUM, MAGIC_SHIFT, SMART_MOUSE, _______, MIDI, GAMING
),

[_NUM] = LAYOUT_planck_grid(
    _______ , KC_7    , KC_8    , KC_9    , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______,
    NUM_0   , NUM_4   , NUM_5   , NUM_6   , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______,
    _______ , KC_1    , KC_2    , KC_3    , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______,
    _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
),

[_GAMING] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    GAME_ESC,KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL, KC_LALT, KC_LGUI, NUM,     KC_SPC,  KC_ENT,  KC_SPC,  NUM,     MO(_SYS),_______, _______, DEF
),

[_FN] = LAYOUT_planck_grid(
    KC_F12        , KC_F7        , KC_F8        , KC_F9        , _______ , _______ , _______ , _______ , KC_MPRV , KC_VOLU        , KC_MNXT , _______,
    LGUI_T(KC_F11), LALT_T(KC_F4), LSFT_T(KC_F5), LCTL_T(KC_F6), _______ , _______ , _______ , _______ , DSK_PREV, RSFT_T(KC_VOLD), DSK_NEXT, _______,
    KC_F10        , KC_F1        , KC_F2        , KC_F3        , _______ , _______ , _______ , _______ , PIN_APP , PIN_WIN        , DSK_MGR , _______,
    _______       , _______      , _______      , _______      , _______ , _______ , KC_MUTE , KC_MPLY , _______ , _______        , _______ , _______
),

[_SYS] = LAYOUT_planck_grid(
    AU_ON  , AU_OFF , _______ , _______ , _______ , RM_TOGG , _______ , _______ , RM_NEXT , RM_HUEU , RM_SATU , RM_VALU,
    MU_ON  , MU_OFF , _______ , _______ , _______ , QK_BOOT , QK_BOOT , _______ , RM_PREV , RM_HUED , RM_SATD , RM_VALD,
    MI_ON  , MI_OFF , _______ , _______ , _______ , EE_CLR  , EE_CLR  , _______ , _______ , _______ , _______ , _______,
    AU_PREV, AU_NEXT, _______ , _______ , _______ , DEF     , GAMING  , MIDI    , _______ , _______ , _______ , DB_TOGG
),

[_NAV] = LAYOUT_planck_grid(
    LALT(KC_F4)  , _______      , ALT_TAB_REV  , ALT_TAB_FWD  , _______ , _______ , _______ , KC_PGUP , NAV_BSPC, KC_UP   , NAV_DEL , _______,
    OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LSFT), OSM(MOD_LCTL), _______ , _______ , _______ , KC_PGDN , KC_LEFT , KC_DOWN , KC_RGHT , KC_ENT,
    _______      , _______      , _______      , _______      , _______ , _______ , _______ , KC_INS  , KC_TAB  , _______ , _______ , _______,
    _______      , _______      , _______      , _______      , _______ , _______ , KC_CNCL , _______ , _______ , _______ , _______ , _______
),

[_MOUSE] = LAYOUT_planck_grid(
    // Mouse layer - urob-style with movement, scrolling, and buttons
    _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP, MS_UP,   KC_PGDN, _______,
    _______, MS_BTN1, MS_BTN3, MS_BTN2, _______, _______, _______, MS_WHLL, MS_LEFT, MS_DOWN, MS_RGHT, MS_WHLR,
    _______, _______, _______, _______, _______, _______, _______, _______, MS_BTN1, MS_BTN3, MS_BTN2, _______,
    _______, _______, _______, _______, _______, _______, MS_WHLU, MS_WHLD, _______, _______, _______, _______
),

[_MIDI] = LAYOUT_planck_grid(
    // Tracker Power User Layout - see layer_layouts.h for visual documentation
    MIDI_PANIC,     MIDI_PLAY_PAUSE, MIDI_TRANSPORT_STOP, MIDI_REC_TOGGLE, MIDI_PAT_PREV, MIDI_PAT_NEXT, MIDI_OCT_DN2, MIDI_OCT_DN1, MIDI_OCT_UP1, MIDI_OCT_UP2, MIDI_OCT_RESET, MIDI,
    MIDI_VEL_1,     MI_Cs,           MI_Ds,               _______,         MI_Fs,         MI_Gs,         MI_As,        _______,      MI_Cs,        MIDI_INST_PREV, MIDI_INST_NEXT, MIDI_VEL_7,
    MIDI_SUST_TOG,  MI_C,            MI_D,                MI_E,            MI_F,          MI_G,          MI_A,         MI_B,         MI_C,         MIDI_NOTE_OFF,  MIDI_NOTE_REL,  MIDI_CHORD_TOG,
    MIDI_CHAN_PREV, MIDI_CHAN_NEXT,  MIDI_EFF_ARPEG,      MIDI_EFF_PITCH,  MIDI_EFF_PAN,  MIDI_EFF_VIBR, MIDI_EFF_TREM,MIDI_EFF_VOL, MIDI_TRNS_DN, MIDI_TRNS_UP,   MIDI_VEL_DN,    MIDI_VEL_UP
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
            midi_state_init();  // Initialize enhanced MIDI state
        #endif
        #ifdef AUDIO_ENABLE
            PLAY_SONG(midi_layer_on);
        #endif
    } else if (!midi_is_on && midi_was_on) {
        // Exiting MIDI layer - disable MIDI
        #ifdef MIDI_ENABLE
            midi_panic_all_notes_off();  // Clean exit with panic
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

        // Handle enhanced MIDI keycodes
    if (keycode >= MIDI_OCT_DN2 && keycode <= MIDI_CONFIG) {
        if (!record->event.pressed) return false;  // Only process on press
        
        switch (keycode) {
            // Octave controls
            case MIDI_OCT_DN2: midi_update_octave(-2); return false;
            case MIDI_OCT_DN1: midi_update_octave(-1); return false;
            case MIDI_OCT_UP1: midi_update_octave(1); return false;
            case MIDI_OCT_UP2: midi_update_octave(2); return false;
            case MIDI_OCT_RESET: 
                midi_state.current_octave = MIDI_OCT_DEFAULT; 
                return false;
                
            // Velocity controls
            case MIDI_VEL_DN: midi_update_velocity(-1); return false;
            case MIDI_VEL_UP: midi_update_velocity(1); return false;
            case MIDI_VEL_1: midi_set_velocity_level(MIDI_VEL_PPP); return false;
            case MIDI_VEL_2: midi_set_velocity_level(MIDI_VEL_PP); return false;
            case MIDI_VEL_3: midi_set_velocity_level(MIDI_VEL_P); return false;
            case MIDI_VEL_4: midi_set_velocity_level(MIDI_VEL_MP); return false;
            case MIDI_VEL_5: midi_set_velocity_level(MIDI_VEL_MF); return false;
            case MIDI_VEL_6: midi_set_velocity_level(MIDI_VEL_F); return false;
            case MIDI_VEL_7: midi_set_velocity_level(MIDI_VEL_FF); return false;
            
            // Transpose controls
            case MIDI_TRNS_DN: 
                if (midi_state.transpose_offset > -12) midi_state.transpose_offset--;
                return false;
            case MIDI_TRNS_UP: 
                if (midi_state.transpose_offset < 12) midi_state.transpose_offset++;
                return false;
            case MIDI_TRNS_RST: 
                midi_state.transpose_offset = 0;
                return false;
                
            // Instrument controls
            case MIDI_INST_PREV:
                if (midi_state.instrument_id > 0) {
                    midi_send_instrument_change(midi_state.instrument_id - 1);
                }
                return false;
            case MIDI_INST_NEXT:
                if (midi_state.instrument_id < MIDI_MAX_INSTRUMENTS - 1) {
                    midi_send_instrument_change(midi_state.instrument_id + 1);
                }
                return false;
                
            // Channel controls
            case MIDI_CHAN_PREV:
                if (midi_state.channel_focus > 0) {
                    midi_send_channel_focus(midi_state.channel_focus - 1);
                }
                return false;
            case MIDI_CHAN_NEXT:
                if (midi_state.channel_focus < MIDI_MAX_CHANNELS - 1) {
                    midi_send_channel_focus(midi_state.channel_focus + 1);
                }
                return false;
                
            // Transport controls
            case MIDI_REC_TOGGLE: midi_transport_record_toggle(); return false;
            case MIDI_PLAY_PAUSE: midi_transport_play_pause(); return false;
            case MIDI_TRANSPORT_STOP: midi_transport_stop(); return false;
            
            // Pattern controls
            case MIDI_PAT_PREV: 
                #ifdef MIDI_ENABLE
                    midi_send_cc(&midi_device, midi_config.channel, 0x79, 0);
                #endif
                return false;
            case MIDI_PAT_NEXT: 
                #ifdef MIDI_ENABLE
                    midi_send_cc(&midi_device, midi_config.channel, 0x79, 1);
                #endif
                return false;
            case MIDI_NOTE_OFF: midi_pattern_insert_note_off(); return false;
            case MIDI_NOTE_REL: midi_pattern_insert_note_release(); return false;
            
            // Effect controls
            case MIDI_EFF_VOL: midi_send_effect(0, midi_state.effect_param); return false;
            case MIDI_EFF_PAN: midi_send_effect(1, midi_state.effect_param); return false;
            case MIDI_EFF_PITCH: midi_send_effect(2, midi_state.effect_param); return false;
            case MIDI_EFF_ARPEG: midi_send_effect(3, midi_state.effect_param); return false;
            case MIDI_EFF_VIBR: midi_send_effect(4, midi_state.effect_param); return false;
            case MIDI_EFF_TREM: midi_send_effect(5, midi_state.effect_param); return false;
            
            // Mode toggles
            case MIDI_CHORD_TOG: 
                midi_state.chord_mode = !midi_state.chord_mode;
                return false;
            case MIDI_SUST_TOG: 
                midi_state.sustain_active = !midi_state.sustain_active;
                #ifdef MIDI_ENABLE
                    midi_send_cc(&midi_device, midi_config.channel, 0x40, 
                                midi_state.sustain_active ? 127 : 0);
                #endif
                #ifdef CONSOLE_ENABLE
                    uprintf("MIDI Sustain: %s\n", midi_state.sustain_active ? "ON" : "OFF");
                #endif
                return false;
                
            // Utility
            case MIDI_PANIC: midi_panic_all_notes_off(); return false;
            case MIDI_LEARN: midi_enter_learn_mode(); return false;
            case MIDI_CONFIG: 
                #ifdef CONSOLE_ENABLE
                    uprintf("MIDI Config requested\n");
                #endif
                return false;
        }
    }

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
