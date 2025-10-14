/* Enhanced MIDI Implementation for Furnace Tracker
 * GPL-2.0-or-later
 * 
 * Implementation of advanced MIDI features with Furnace-specific optimizations
 */

#include <math.h>
#include "midi_enhanced.h"
#include "process_midi.h"

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

// External references to QMK MIDI system
extern MidiDevice midi_device;

#ifdef MIDI_ENABLE
extern MidiDevice midi_device;
extern midi_config_t midi_config;
#endif

/* ═══════════════════════════════════════════════════════════════════════════
 * GLOBAL MIDI STATE
 * ═══════════════════════════════════════════════════════════════════════════ */

midi_state_t midi_state;

/* ═══════════════════════════════════════════════════════════════════════════
 * STATE MANAGEMENT FUNCTIONS
 * ═══════════════════════════════════════════════════════════════════════════ */

void midi_state_init(void) {
    midi_state.current_octave = MIDI_OCT_DEFAULT;
    midi_state.velocity_level = MIDI_VEL_DEFAULT;
    midi_state.instrument_id = 0;
    midi_state.channel_focus = 0;
    midi_state.sustain_active = false;
    midi_state.chord_mode = false;
    midi_state.record_mode = false;
    midi_state.effect_param = 0;
    midi_state.transpose_offset = 0;
    
    #ifdef CONSOLE_ENABLE
        uprintf("MIDI state initialized - Oct:%d Vel:%d\n", 
                midi_state.current_octave, midi_state.velocity_level);
    #endif
}

void midi_state_reset(void) {
    #ifdef MIDI_ENABLE
        // Send all notes off
        for (uint8_t i = 0; i < 16; i++) {
            midi_send_cc(&midi_device, i, 0x7B, 0);  // All notes off
        }
    #endif
    
    midi_state_init();
    
    #ifdef AUDIO_ENABLE
        midi_play_mode_change_sound();
    #endif
}

void midi_update_octave(int8_t delta) {
    int8_t new_octave = midi_state.current_octave + delta;
    
    if (new_octave >= MIDI_OCT_MIN && new_octave <= MIDI_OCT_MAX) {
        midi_state.current_octave = new_octave;
        
        #ifdef CONSOLE_ENABLE
            uprintf("MIDI octave changed to: %d\n", midi_state.current_octave);
        #endif
        
        #ifdef AUDIO_ENABLE
            midi_play_feedback_tone(60 + (midi_state.current_octave * 12));
        #endif
    }
}

void midi_update_velocity(int8_t delta) {
    int16_t new_velocity = midi_state.velocity_level + (delta * MIDI_VEL_STEP);
    
    if (new_velocity < 1) new_velocity = 1;
    if (new_velocity > 127) new_velocity = 127;
    
    midi_state.velocity_level = (uint8_t)new_velocity;
    
    #ifdef CONSOLE_ENABLE
        uprintf("MIDI velocity changed to: %d\n", midi_state.velocity_level);
    #endif
}

void midi_set_velocity_level(uint8_t level) {
    if (level >= 1 && level <= 127) {
        midi_state.velocity_level = level;
        
        #ifdef CONSOLE_ENABLE
            uprintf("MIDI velocity set to: %d\n", midi_state.velocity_level);
        #endif
    }
}

/* ═══════════════════════════════════════════════════════════════════════════
 * FURNACE INTEGRATION FUNCTIONS
 * ═══════════════════════════════════════════════════════════════════════════ */

void midi_send_note_to_furnace(uint8_t note, uint8_t velocity) {
    uint8_t final_note = midi_calculate_final_note(note);
    uint8_t final_velocity = midi_calculate_final_velocity(velocity);
    
    #ifdef MIDI_ENABLE
        // Send to MIDI output for Furnace
        midi_send_noteon(&midi_device, midi_config.channel, final_note, final_velocity);
        
        // If in record mode, also add to pattern
        if (midi_state.record_mode) {
            midi_pattern_record_note(final_note, final_velocity);
        }
    #endif
    
    #ifdef CONSOLE_ENABLE
        uprintf("MIDI Note: %d Vel: %d (Final: %d/%d)\n", 
                note, velocity, final_note, final_velocity);
    #endif
}

void midi_send_instrument_change(uint8_t instrument) {
    midi_state.instrument_id = instrument;
    
    #ifdef MIDI_ENABLE
        // Send program change to Furnace
        midi_send_programchange(&midi_device, midi_config.channel, instrument);
    #endif
    
    #ifdef CONSOLE_ENABLE
        uprintf("MIDI Instrument changed to: %d\n", instrument);
    #endif
}

void midi_send_channel_focus(uint8_t channel) {
    if (channel < MIDI_MAX_CHANNELS) {
        midi_state.channel_focus = channel;
        
        #ifdef MIDI_ENABLE
            // Send CC to change focused channel in Furnace
            midi_send_cc(&midi_device, midi_config.channel, 0x78, channel);
        #endif
        
        #ifdef CONSOLE_ENABLE
            uprintf("MIDI Channel focus: %d\n", channel);
        #endif
    }
}

void midi_send_effect(uint8_t effect_type, uint8_t value) {
    midi_state.effect_param = value;
    
    #ifdef MIDI_ENABLE
        // Send CC for effect parameter (Furnace-specific CCs)
        midi_send_cc(&midi_device, midi_config.channel, 0x10 + effect_type, value);
    #endif
    
    #ifdef CONSOLE_ENABLE
        uprintf("MIDI Effect: Type %d Value %d\n", effect_type, value);
    #endif
}

/* ═══════════════════════════════════════════════════════════════════════════
 * PATTERN CONTROL FUNCTIONS
 * ═══════════════════════════════════════════════════════════════════════════ */

void midi_pattern_record_note(uint8_t note, uint8_t velocity) {
    // This would integrate with Furnace's pattern recording
    // For now, we'll send appropriate MIDI commands
    
    #ifdef MIDI_ENABLE
        // Send note with timing information
        midi_send_noteon(&midi_device, midi_state.channel_focus, note, velocity);
    #endif
    
    midi_pattern_advance_cursor();
}

void midi_pattern_insert_note_off(void) {
    #ifdef MIDI_ENABLE
        // Send note off command (Furnace CC for note off)
        midi_send_cc(&midi_device, midi_config.channel, 0x7C, 0);
    #endif
    
    midi_pattern_advance_cursor();
}

void midi_pattern_insert_note_release(void) {
    #ifdef MIDI_ENABLE
        // Send note release command (Furnace CC for note release)
        midi_send_cc(&midi_device, midi_config.channel, 0x7D, 0);
    #endif
    
    midi_pattern_advance_cursor();
}

void midi_pattern_advance_cursor(void) {
    #ifdef MIDI_ENABLE
        // Send CC to advance cursor in Furnace
        midi_send_cc(&midi_device, midi_config.channel, 0x7E, 1);
    #endif
}

/* ═══════════════════════════════════════════════════════════════════════════
 * TRANSPORT CONTROL FUNCTIONS
 * ═══════════════════════════════════════════════════════════════════════════ */

void midi_transport_play_pause(void) {
    #ifdef MIDI_ENABLE
        // Send MIDI Clock Start/Continue/Stop
        // Note: This is simplified - full implementation would track play state
        midi_send_cc(&midi_device, midi_config.channel, 0x7A, 127);
    #endif
    
    #ifdef CONSOLE_ENABLE
        uprintf("MIDI Transport: Play/Pause\n");
    #endif
}

void midi_transport_stop(void) {
    #ifdef MIDI_ENABLE
        // Send MIDI Clock Stop
        midi_send_cc(&midi_device, midi_config.channel, 0x7B, 0);  // All notes off
    #endif
    
    #ifdef CONSOLE_ENABLE
        uprintf("MIDI Transport: Stop\n");
    #endif
}

void midi_transport_record_toggle(void) {
    midi_state.record_mode = !midi_state.record_mode;
    
    #ifdef MIDI_ENABLE
        // Send CC to toggle record mode in Furnace
        midi_send_cc(&midi_device, midi_config.channel, 0x7F, midi_state.record_mode ? 127 : 0);
    #endif
    
    #ifdef CONSOLE_ENABLE
        uprintf("MIDI Record mode: %s\n", midi_state.record_mode ? "ON" : "OFF");
    #endif
}

/* ═══════════════════════════════════════════════════════════════════════════
 * UTILITY FUNCTIONS
 * ═══════════════════════════════════════════════════════════════════════════ */

void midi_panic_all_notes_off(void) {
    #ifdef MIDI_ENABLE
        // Send all notes off on all channels
        for (uint8_t i = 0; i < 16; i++) {
            midi_send_cc(&midi_device, i, 0x7B, 0);    // All notes off
            midi_send_cc(&midi_device, i, 0x78, 0);    // All sound off
        }
    #endif
    
    midi_state_reset();
    
    #ifdef CONSOLE_ENABLE
        uprintf("MIDI PANIC: All notes off\n");
    #endif
}

void midi_enter_learn_mode(void) {
    // Placeholder for MIDI learn functionality
    #ifdef CONSOLE_ENABLE
        uprintf("MIDI Learn mode activated\n");
    #endif
    
    #ifdef AUDIO_ENABLE
        midi_play_mode_change_sound();
    #endif
}

uint8_t midi_calculate_final_velocity(uint8_t base_velocity) {
    // Apply velocity scaling based on current velocity level
    uint16_t scaled = (uint16_t)base_velocity * midi_state.velocity_level / 127;
    return (uint8_t)(scaled > 127 ? 127 : scaled);
}

uint8_t midi_calculate_final_note(uint8_t base_note) {
    // Apply octave and transpose offsets
    int16_t final_note = base_note + (midi_state.current_octave * 12) + midi_state.transpose_offset;
    
    // Clamp to valid MIDI range
    if (final_note < 0) final_note = 0;
    if (final_note > 127) final_note = 127;
    
    return (uint8_t)final_note;
}

/* ═══════════════════════════════════════════════════════════════════════════
 * AUDIO FEEDBACK FUNCTIONS
 * ═══════════════════════════════════════════════════════════════════════════ */

#ifdef AUDIO_ENABLE
void midi_play_feedback_tone(uint8_t note) {
    // Convert MIDI note to frequency and play short tone
    (void)note; // Suppress unused parameter warning
    // float freq = 440.0f * pow(2.0f, (note - 69) / 12.0f);
    // Note: QMK might not have audio_play_tone, this is a placeholder
    // audio_play_tone(freq);
}

void midi_play_mode_change_sound(void) {
    // Play ascending/descending arpeggio for mode changes
    static float mode_change_melody[][2] = {
        {NOTE_C5, 8}, {NOTE_E5, 8}, {NOTE_G5, 8}
    };
    audio_play_melody(&mode_change_melody, 3, false);
}
#endif