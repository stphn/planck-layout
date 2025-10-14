/* Enhanced MIDI Layout for Furnace Tracker
 * GPL-2.0-or-later
 * 
 * Advanced MIDI implementation with Furnace-specific features:
 * - Real-time pattern editing
 * - Instrument and channel control
 * - Effect parameter manipulation
 * - Advanced octave and velocity management
 * - Furnace workflow optimization
 */

#pragma once

#include QMK_KEYBOARD_H
#include "custom_keycodes.h"

/* ═══════════════════════════════════════════════════════════════════════════
 * MIDI STATE MANAGEMENT
 * ═══════════════════════════════════════════════════════════════════════════ */

typedef struct {
    uint8_t current_octave;      // Current octave offset (-2 to +2)
    uint8_t velocity_level;      // Current velocity (0-127)
    uint8_t instrument_id;       // Current instrument (0-255)
    uint8_t channel_focus;       // Focused channel (0-15)
    bool sustain_active;         // Sustain pedal state
    bool chord_mode;             // Chord input mode
    bool record_mode;            // Pattern recording mode
    uint8_t effect_param;        // Current effect parameter value
    uint8_t transpose_offset;    // Global transpose offset
} midi_state_t;

extern midi_state_t midi_state;

/* ═══════════════════════════════════════════════════════════════════════════
 * FURNACE-SPECIFIC MIDI KEYCODES
 * ═══════════════════════════════════════════════════════════════════════════ */

// Octave control
#define MIDI_OCT_DN2    (SAFE_RANGE + 0x100)  // -2 octaves
#define MIDI_OCT_DN1    (SAFE_RANGE + 0x101)  // -1 octave  
#define MIDI_OCT_UP1    (SAFE_RANGE + 0x102)  // +1 octave
#define MIDI_OCT_UP2    (SAFE_RANGE + 0x103)  // +2 octaves
#define MIDI_OCT_RESET  (SAFE_RANGE + 0x104)  // Reset to 0

// Velocity control
#define MIDI_VEL_DN     (SAFE_RANGE + 0x110)  // Decrease velocity
#define MIDI_VEL_UP     (SAFE_RANGE + 0x111)  // Increase velocity
#define MIDI_VEL_1      (SAFE_RANGE + 0x112)  // Velocity 32 (ppp)
#define MIDI_VEL_2      (SAFE_RANGE + 0x113)  // Velocity 48 (pp)
#define MIDI_VEL_3      (SAFE_RANGE + 0x114)  // Velocity 64 (p)
#define MIDI_VEL_4      (SAFE_RANGE + 0x115)  // Velocity 80 (mp)
#define MIDI_VEL_5      (SAFE_RANGE + 0x116)  // Velocity 96 (mf)
#define MIDI_VEL_6      (SAFE_RANGE + 0x117)  // Velocity 112 (f)
#define MIDI_VEL_7      (SAFE_RANGE + 0x118)  // Velocity 127 (ff)

// Transpose control
#define MIDI_TRNS_DN    (SAFE_RANGE + 0x120)  // Transpose down
#define MIDI_TRNS_UP    (SAFE_RANGE + 0x121)  // Transpose up
#define MIDI_TRNS_RST   (SAFE_RANGE + 0x122)  // Reset transpose

// Furnace workflow controls
#define MIDI_INST_PREV  (SAFE_RANGE + 0x130)  // Previous instrument
#define MIDI_INST_NEXT  (SAFE_RANGE + 0x131)  // Next instrument
#define MIDI_CHAN_PREV  (SAFE_RANGE + 0x132)  // Previous channel
#define MIDI_CHAN_NEXT  (SAFE_RANGE + 0x133)  // Next channel
#define MIDI_REC_TOGGLE (SAFE_RANGE + 0x134)  // Toggle record mode
#define MIDI_PLAY_PAUSE (SAFE_RANGE + 0x135)  // Play/pause
#define MIDI_TRANSPORT_STOP (SAFE_RANGE + 0x136)  // Stop playback

// Pattern editing
#define MIDI_PAT_PREV   (SAFE_RANGE + 0x140)  // Previous pattern
#define MIDI_PAT_NEXT   (SAFE_RANGE + 0x141)  // Next pattern
#define MIDI_ROW_PREV   (SAFE_RANGE + 0x142)  // Previous row
#define MIDI_ROW_NEXT   (SAFE_RANGE + 0x143)  // Next row
#define MIDI_NOTE_OFF   (SAFE_RANGE + 0x144)  // Insert note off
#define MIDI_NOTE_REL   (SAFE_RANGE + 0x145)  // Insert note release

// Effect controls (for common Furnace effects)
#define MIDI_EFF_VOL    (SAFE_RANGE + 0x150)  // Volume effect
#define MIDI_EFF_PAN    (SAFE_RANGE + 0x151)  // Pan effect  
#define MIDI_EFF_PITCH  (SAFE_RANGE + 0x152)  // Pitch bend effect
#define MIDI_EFF_ARPEG  (SAFE_RANGE + 0x153)  // Arpeggio effect
#define MIDI_EFF_VIBR   (SAFE_RANGE + 0x154)  // Vibrato effect
#define MIDI_EFF_TREM   (SAFE_RANGE + 0x155)  // Tremolo effect

// Mode toggles
#define MIDI_CHORD_TOG  (SAFE_RANGE + 0x160)  // Toggle chord mode
#define MIDI_SUST_TOG   (SAFE_RANGE + 0x161)  // Toggle sustain
#define MIDI_MONO_TOG   (SAFE_RANGE + 0x162)  // Toggle mono mode

// Utility
#define MIDI_PANIC      (SAFE_RANGE + 0x170)  // All notes off + reset
#define MIDI_LEARN      (SAFE_RANGE + 0x171)  // MIDI learn mode
#define MIDI_CONFIG     (SAFE_RANGE + 0x172)  // Open MIDI config

/* ═══════════════════════════════════════════════════════════════════════════
 * VELOCITY LEVELS (Furnace-optimized)
 * ═══════════════════════════════════════════════════════════════════════════ */

#define MIDI_VEL_PPP    32   // Pianississimo
#define MIDI_VEL_PP     48   // Pianissimo  
#define MIDI_VEL_P      64   // Piano
#define MIDI_VEL_MP     80   // Mezzo-piano
#define MIDI_VEL_MF     96   // Mezzo-forte (default)
#define MIDI_VEL_F      112  // Forte
#define MIDI_VEL_FF     127  // Fortissimo

#define MIDI_VEL_DEFAULT MIDI_VEL_MF
#define MIDI_VEL_STEP    8   // Step size for vel up/down

/* ═══════════════════════════════════════════════════════════════════════════
 * OCTAVE SETTINGS
 * ═══════════════════════════════════════════════════════════════════════════ */

#define MIDI_OCT_MIN       -2
#define MIDI_OCT_MAX        2
#define MIDI_OCT_DEFAULT    0

/* ═══════════════════════════════════════════════════════════════════════════
 * FUNCTION DECLARATIONS
 * ═══════════════════════════════════════════════════════════════════════════ */

// State management
void midi_state_init(void);
void midi_state_reset(void);
void midi_update_octave(int8_t delta);
void midi_update_velocity(int8_t delta);
void midi_set_velocity_level(uint8_t level);

// Furnace integration
void midi_send_note_to_furnace(uint8_t note, uint8_t velocity);
void midi_send_instrument_change(uint8_t instrument);
void midi_send_channel_focus(uint8_t channel);
void midi_send_effect(uint8_t effect_type, uint8_t value);

// Pattern control
void midi_pattern_record_note(uint8_t note, uint8_t velocity);
void midi_pattern_insert_note_off(void);
void midi_pattern_insert_note_release(void);
void midi_pattern_advance_cursor(void);

// Transport control
void midi_transport_play_pause(void);
void midi_transport_stop(void);
void midi_transport_record_toggle(void);

// Utility functions
void midi_panic_all_notes_off(void);
void midi_enter_learn_mode(void);
uint8_t midi_calculate_final_velocity(uint8_t base_velocity);
uint8_t midi_calculate_final_note(uint8_t base_note);

// Audio feedback
#ifdef AUDIO_ENABLE
void midi_play_feedback_tone(uint8_t note);
void midi_play_mode_change_sound(void);
#endif

/* ═══════════════════════════════════════════════════════════════════════════
 * CONFIGURATION CONSTANTS
 * ═══════════════════════════════════════════════════════════════════════════ */

// Maximum instruments supported
#define MIDI_MAX_INSTRUMENTS 256

// Maximum channels supported  
#define MIDI_MAX_CHANNELS 16

// Effect parameter range
#define MIDI_EFFECT_PARAM_MAX 255

// Chord mode settings
#define MIDI_CHORD_MAX_NOTES 4
#define MIDI_CHORD_TIMEOUT_MS 50