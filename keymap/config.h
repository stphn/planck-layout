/*
 * EXPERIMENTAL CONFIG for Bilateral Homerow Mods
 * Based on urob's timeless homerow mod concepts
 */

#pragma once

/* ═══════════════════════════════════════════════════════════════════════════════════════════════════
 * BILATERAL HOMEROW MODS CONFIGURATION
 * Key insight: Use opposite hands to eliminate timing conflicts
 * ═══════════════════════════════════════════════════════════════════════════════════════════════════ */

// Urob's timing approach - 280ms base, same as ZMK config
#define TAPPING_TERM 280

// Enable per-key configuration
#define TAPPING_TERM_PER_KEY

// Aggressive hold behavior for bilateral combinations
#define PERMISSIVE_HOLD
#define PERMISSIVE_HOLD_PER_KEY

// Immediate hold when another key is pressed (crucial for bilateral mods)
#define HOLD_ON_OTHER_KEY_PRESS
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

// Quick tap term matching urob's 175ms
#define QUICK_TAP_TERM 175
#define QUICK_TAP_TERM_PER_KEY

/* ═══════════════════════════════════════════════════════════════════════════════════════════════════
 * ADDITIONAL QMK FEATURES
 * ═══════════════════════════════════════════════════════════════════════════════════════════════════ */

// Tap dance settings
#define TAPPING_TOGGLE 2

// Smart Combos - urob's symbol system (16 combos) - using urob's fast timing
#define COMBO_COUNT 27
#define COMBO_TERM 18           // 18ms like urob's fast combos
#define COMBO_MUST_HOLD_MODS    // Don't interfere with homerow mods
#define COMBO_HOLD_TERM 150     // Hold time for combo holds
#define COMBO_STRICT_TIMER      // More precise timing - start timer on first key
#define COMBO_TERM_PER_COMBO    // Allow per-combo timing configuration

// One shot settings
#define ONESHOT_TAP_TOGGLE 2
#define ONESHOT_TIMEOUT 3000


// Mouse key settings (if using)
#ifdef MOUSEKEY_ENABLE
    #define MOUSEKEY_DELAY 0
    #define MOUSEKEY_INTERVAL 16
    #define MOUSEKEY_WHEEL_DELAY 0
    #define MOUSEKEY_MAX_SPEED 6
    #define MOUSEKEY_TIME_TO_MAX 64
#endif

/* ═══════════════════════════════════════════════════════════════════════════════════════════════════
 * PERFORMANCE AND DEBUGGING
 * ═══════════════════════════════════════════════════════════════════════════════════════════════════ */

// Debug options (comment out for production)
// #define DEBUG_MATRIX_SCAN_RATE

// Memory optimization - 8 layers (COLEMAK, QWERTY, NUM, SYM, FN, ADJUST, NAV, MIDI)
#define LAYER_STATE_8BIT  // Use 8-bit layer state for <=8 layers

// Firmware size optimization
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

/* ═══════════════════════════════════════════════════════════════════════════════════════════════════
 * EXPERIMENTAL FEATURES
 * ═══════════════════════════════════════════════════════════════════════════════════════════════════ */

// Enable advanced features that make bilateral homerow mods work
// IGNORE_MOD_TAP_INTERRUPT is now default behavior in QMK and should not be defined
#define RETRO_TAPPING            // Tap on release if no other key pressed

// RGB Matrix integration for homerow mod feedback
#ifdef RGB_MATRIX_ENABLE
    #define RGB_MATRIX_KEYPRESSES
    #define RGB_MATRIX_KEYRELEASES
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#endif