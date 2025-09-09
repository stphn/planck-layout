/* Copyright 2015-2023 Jack Humbert
 * GPL-2.0-or-later
*/

#include QMK_KEYBOARD_H
#include "user_song_list.h"

// ---------- RGB keycode fallbacks (safe without RGB hardware) ----------
#if !defined(RGBLIGHT_ENABLE) && !defined(RGB_MATRIX_ENABLE)
#define RGB_TOG KC_NO
#define RGB_MOD KC_NO
#define RGB_HUI KC_NO
#define RGB_HUD KC_NO
#define RGB_SAI KC_NO
#define RGB_SAD KC_NO
#define RGB_VAI KC_NO
#define RGB_VAD KC_NO
#endif

#ifndef RGB_TOG
#define RGB_TOG KC_NO
#endif
#ifndef RGB_MOD
#define RGB_MOD KC_NO
#endif
#ifndef RGB_HUI
#define RGB_HUI KC_NO
#endif
#ifndef RGB_HUD
#define RGB_HUD KC_NO
#endif
#ifndef RGB_SAI
#define RGB_SAI KC_NO
#endif
#ifndef RGB_SAD
#define RGB_SAD KC_NO
#endif
#ifndef RGB_VAI
#define RGB_VAI KC_NO
#endif
#ifndef RGB_VAD
#define RGB_VAD KC_NO
#endif
// ----------------------------------------------------------------------

extern keymap_config_t keymap_config;

// Layers
enum planck_layers { _QWERTY, _COLEMAK, _NUM, _SYM, _PLOVER, _ADJUST, _NAV };

// Custom keycodes
enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  PLOVER,
  BACKLIT,
  EXT_PLV,
  SAM,
  TTHEME, // Play a short Tetris motif
};

#define NUM MO(_NUM)
#define SYM MO(_SYM)
#define NAV MO(_NAV)
#define CTRL_ESC LCTL_T(KC_ESC)

// Tap Dance declarations
enum {
  TD_SCLN_COLN,
  TD_QUOT_DQUOT,
  TD_SLSH_QUES,
  TD_C_COPY,
  TD_V_PASTE,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_SCLN_COLN] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
    [TD_QUOT_DQUOT] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQUO),
    [TD_SLSH_QUES] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_QUES),
    [TD_C_COPY] = ACTION_TAP_DANCE_DOUBLE(KC_C, LGUI(KC_C)),
    [TD_V_PASTE] = ACTION_TAP_DANCE_DOUBLE(KC_V, LGUI(KC_V)),
};

/* ======================= Keymaps ======================= */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
     * ,-----------------------------------------------------------------------------------.
     * | Tab  |  Q   |  W   |  E   |  R   |  T   |  Y   |  U   |  I   |  O   |
     * P   | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Esc  |  A   |  S   |  D   |  F   |  G   |  H   |  J   |  K   |  L   |
     * ;   |  '   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Shift|  Z   |  X   |  C   |  V   |  B   |  N   |  M   |  ,   |  .   |
     * /   |Enter |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |
     * Up  |Right |
     * `-----------------------------------------------------------------------------------'
     */
    [_QWERTY] = LAYOUT_planck_grid(
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P,
        KC_BSPC, KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,
        KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M,
        KC_COMM, KC_DOT, KC_SLSH, KC_ENT, BACKLIT, KC_LCTL, KC_LALT, KC_LGUI,
        NUM, KC_RSFT, KC_SPC, SYM, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT),

    /* Colemak */
    [_COLEMAK] = LAYOUT_planck_grid(
        KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y,
        TD(TD_SCLN_COLN), KC_BSPC, CTRL_ESC, KC_A, KC_R, KC_S, KC_T, KC_G, KC_M,
        KC_N, KC_E, KC_I, KC_O, TD(TD_QUOT_DQUOT), SC_LSPO, KC_Z, KC_X,
        TD(TD_C_COPY), KC_D, TD(TD_V_PASTE), KC_K, KC_H, KC_COMM, KC_DOT,
        TD(TD_SLSH_QUES), SC_RSPC, KC_LBRC, KC_LALT, KC_LGUI, NAV, NUM, _______,
        MT(MOD_HYPR, KC_SPC), SYM, NAV, KC_RGUI, KC_ENT, KC_RBRC),

    /* Number */
    [_NUM] = LAYOUT_planck_grid(
        _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9,
        KC_F10, _______, _______, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7,
        KC_8, KC_9, KC_0, _______, _______, KC_MINS, KC_EQL, KC_GRV, KC_BSLS,
        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______),

    /* Symbol */
    [_SYM] = LAYOUT_planck_grid(
        _______, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18,
        KC_F19, KC_F20, _______, _______, KC_EXLM, KC_AT, KC_HASH, KC_DLR,
        KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, _______,
        KC_UNDS, KC_PLUS, KC_TILD, KC_PIPE, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______),

    /* Plover */
    [_PLOVER] = LAYOUT_planck_grid(
        KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1,
        _______, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P,
        KC_LBRC, _______, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,
        KC_SCLN, KC_QUOT, EXT_PLV, _______, _______, KC_C, KC_V, _______,
        _______, KC_N, KC_M, _______, _______, _______),

    /* Adjust (includes RGB keys that safely no-op without RGB) */
    [_ADJUST] = LAYOUT_planck_grid(
        _______, QK_BOOT, DB_TOGG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI,
        RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, EE_CLR, MU_NEXT, AU_ON,
        AU_OFF, AG_NORM, AG_SWAP, _______, _______, _______, QWERTY, COLEMAK,
        _______, AU_PREV, AU_NEXT, MU_ON, MU_OFF, MI_ON, MI_OFF, _______,
        _______, _______, _______, TTHEME, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______),

    /* Navigate */
    [_NAV] = LAYOUT_planck_grid(
        _______, _______, KC_BRID, KC_BRIU, _______, _______, _______, KC_HOME,
        KC_PGDN, KC_PGUP, KC_END, _______, _______, SAM, LCTL(KC_DOWN),
        LCTL(KC_UP), _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,
        KC_RGHT, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,
        _______, LGUI(KC_LBRC), _______, _______, LGUI(KC_RBRC), _______,
        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______)};
/* ===================== End Keymaps ===================== */

#ifdef AUDIO_ENABLE
float plover_song[][2] = SONG(PLOVER_SOUND);
float plover_gb_song[][2] = SONG(PLOVER_GOODBYE_SOUND);
float coin_up[][2] = SONG(AUDIO_ON_SOUND);
float coin_down[][2] = SONG(AUDIO_OFF_SOUND);
float tetris_song[][2] = SONG(TETRIS_THEME_A);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  // Tri-layer: NUM + SYM => ADJUST
  return update_tri_layer_state(state, _NUM, _SYM, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case SAM:
    if (record->event.pressed) {
      register_code(KC_LSFT);
      register_code(KC_LALT);
      register_code(KC_M);
#ifdef AUDIO_ENABLE
      PLAY_SONG(coin_up);
#endif
    } else {
      unregister_code(KC_LSFT);
      unregister_code(KC_LALT);
      unregister_code(KC_M);
    }
    return false;

  case TTHEME:
#ifdef AUDIO_ENABLE
    if (record->event.pressed) {
      stop_all_notes(); // reset any previous tune
      PLAY_SONG(tetris_song);
    }
#endif
    return false;

  case QWERTY:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_QWERTY);
    }
    return false;

  case COLEMAK:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_COLEMAK);
    }
    return false;

  case BACKLIT:
    if (record->event.pressed) {
      register_code(KC_RSFT);
    } else {
      unregister_code(KC_RSFT);
    }
    return false;

  case PLOVER:
    if (record->event.pressed) {
#ifdef AUDIO_ENABLE
      stop_all_notes();
      PLAY_SONG(plover_song);
#endif
      layer_off(_SYM);
      layer_off(_NUM);
      layer_off(_NAV);
      layer_off(_ADJUST);
      layer_on(_PLOVER);
      if (!eeconfig_is_enabled()) {
        eeconfig_init();
      }
      eeconfig_read_keymap(&keymap_config);
      keymap_config.nkro = 1;
      eeconfig_update_keymap(&keymap_config);
    }
    return false;

  case EXT_PLV:
    if (record->event.pressed) {
#ifdef AUDIO_ENABLE
      PLAY_SONG(plover_gb_song);
#endif
      layer_off(_PLOVER);
    }
    return false;
  }
  return true;
}

/* ===== Extra fun: encoder melody toy (unchanged) ===== */
deferred_token tokens[8];

uint32_t reset_note(uint32_t trigger_time, void *note) {
  *(float *)note = 440.0f;
  return 0;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
#ifdef AUDIO_ENABLE
  static float melody[2][2] = {{440.0f, 8}, {440.0f, 24}};
  cancel_deferred_exec(tokens[index]);
  if (clockwise) {
    melody[1][0] *= 1.059463f; // +1 semitone
    melody[0][0] =
        melody[1][0] / 1.498307f; // -7 semitones (approx perfect fifth below)
  } else {
    melody[1][0] /= 1.059463f;               // -1 semitone
    melody[0][0] = melody[1][0] * 1.414214f; // tritone above
  }
  audio_play_melody(&melody, 2, false);
  tokens[index] = defer_exec(1000, reset_note, &melody[1][0]);
#endif
  return false;
}

bool dip_switch_update_user(uint8_t index, bool active) {
  switch (index) {
  case 0: {
#ifdef AUDIO_ENABLE
    static bool play_sound = false;
#endif
    if (active) {
#ifdef AUDIO_ENABLE
      if (play_sound)
        PLAY_SONG(plover_song);
#endif
      layer_on(_ADJUST);
    } else {
#ifdef AUDIO_ENABLE
      if (play_sound)
        PLAY_SONG(plover_gb_song);
#endif
      layer_off(_ADJUST);
    }
#ifdef AUDIO_ENABLE
    play_sound = true;
#endif
    break;
  }
  }
  return true;
}
