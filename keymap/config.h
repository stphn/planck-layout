/* Copyright 2015-2023 Jack Humbert
 * GPL-2.0-or-later
 */
#pragma once

/* ---------------- Audio ---------------- */
#ifdef AUDIO_ENABLE
#    define STARTUP_SONG SONG(PLANCK_SOUND)
// #define STARTUP_SONG SONG(NO_SOUND)
#    define DEFAULT_LAYER_SONGS { SONG(COLEMAK_SOUND), SONG(QWERTY_SOUND), SONG(DVORAK_SOUND) }
#endif

/* ---------------- MIDI ----------------- */
/* Basic MIDI (Music mode notes) */
#define MIDI_BASIC
#define MUSIC_MAP
/* Advanced MIDI features (octave/transpose/etc.) */
// #define MIDI_ADVANCED

/* -------------- Unicode ---------------- */
#define UNICODE_SELECTED_MODES UNICODE_MODE_MACOS

/* ------------- Tap Dance --------------- */
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY
// Auto Shift example:
// #define AUTO_SHIFT_TIMEOUT 200

/* ------------- RGB MATRIX -------------- */
/* Planck Rev7 uses RGB_MATRIX (per-key), not RGBLIGHT. */
#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 120
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true
#    define RGB_MATRIX_KEYPRESSES          // react to keypresses
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS // fancy effects buffer
#    define RGB_MATRIX_DEFAULT_HUE 128     // cyan-ish; set 0..255
#    define RGB_MATRIX_DEFAULT_SAT 255     // full saturation
#    define RGB_MATRIX_DEFAULT_VAL 180     // brightness cap (0..255)
/* Enable a curated set of effects (add/remove to taste) */
#    define ENABLE_RGB_MATRIX_ALPHAS_MODS
#    define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#    define ENABLE_RGB_MATRIX_BREATHING
#    define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#    define ENABLE_RGB_MATRIX_CYCLE_ALL
#    define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#    define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
// Pick your preferred default effect:
#    define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#endif
