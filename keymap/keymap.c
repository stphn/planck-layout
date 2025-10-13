/* Copyright 2015-2023 Jack Humbert
 * GPL-2.0-or-later
 *
 * EXPERIMENTAL VERSION with Bilateral Homerow Mods
 * Based on urob's timeless homerow mod concepts
 */

#include QMK_KEYBOARD_H
#include "user_song_list.h"
#include "../password.h"

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

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
// LED groups (left→right)
static const uint8_t LED_TOP[]    = {6, 5, 4, 3};
static const uint8_t LED_MID[]    = {0};
static const uint8_t LED_BOTTOM[] = {7, 8, 1, 2};
static const uint8_t LED_ALL[]    = {0, 1, 2, 3, 4, 5, 6, 7, 8};
static const uint8_t LED_LEFT[]   = {6, 7};
static const uint8_t LED_RIGHT[]  = {3, 2};

static inline void set_group_color(const uint8_t *grp, uint8_t cnt, uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t i = 0; i < cnt; i++) rgb_matrix_set_color(grp[i], r, g, b);
}
#endif

extern keymap_config_t keymap_config;

/* ═══════════════════════════════════════════════════════════════════════════════════════════════════
 * UROB'S SMART BEHAVIORS - Variable declarations
 * ═══════════════════════════════════════════════════════════════════════════════════════════════════ */

static bool num_word_active = false;
static uint16_t magic_shift_timer = 0;
static uint16_t last_keycode = KC_NO;
static bool last_key_was_alpha = false;
static uint16_t magic_shift_tap_timer = 0;
static bool caps_word_active = false;
static uint16_t smart_num_tap_timer = 0;
static bool sticky_num_active = false;
static bool leader_active = false;
static uint16_t leader_timer = 0;


/* ═══════════════════════════════════════════════════════════════════════════════════════════════════
 * BILATERAL HOMEROW MODS CONFIGURATION
 * Based on urob's timeless homerow mods - uses opposite hands to eliminate timing issues
 * ═══════════════════════════════════════════════════════════════════════════════════════════════════ */

// Timing settings for bilateral homerow mods
#define TAPPING_TERM 280        // Longer than usual for reliability
#define TAPPING_TERM_PER_KEY    // Enable per-key tapping terms
#define PERMISSIVE_HOLD         // Aggressive hold behavior
#define HOLD_ON_OTHER_KEY_PRESS // Immediate hold when other key pressed

// Left hand homerow mods (A, R, S, T)
#define HRM_A LGUI_T(KC_A)
#define HRM_R LALT_T(KC_R)
#define HRM_S LCTL_T(KC_S)
#define HRM_T LSFT_T(KC_T)

// Right hand homerow mods (N, E, I, O)
#define HRM_N RSFT_T(KC_N)
#define HRM_E RCTL_T(KC_E)
#define HRM_I RALT_T(KC_I)
#define HRM_O RGUI_T(KC_O)

// QWERTY homerow mods (bilateral - same mod philosophy, different keys)
#define HRM_A_Q LGUI_T(KC_A)  // A = Cmd (same as Colemak A)
#define HRM_S_Q LALT_T(KC_S)  // S = Alt
#define HRM_D_Q LCTL_T(KC_D)  // D = Ctrl
#define HRM_F_Q LSFT_T(KC_F)  // F = Shift
#define HRM_J_Q RSFT_T(KC_J)  // J = Shift
#define HRM_K_Q RCTL_T(KC_K)  // K = Ctrl
#define HRM_L_Q RALT_T(KC_L)  // L = Alt
#define HRM_SCLN_Q RGUI_T(KC_SCLN) // ; = Cmd

/* Layers - urob's naming convention */
enum planck_layers {
    _DEF,      // Default layer (Colemak)
    _QWERTY,   // Alternative base layer
    _NUM,      // Numeric layer
    _SYM,      // Symbol layer (keep for now)
    _FN,       // Function layer
    _SYS,      // System layer (was ADJUST)
    _NAV,      // Navigation layer
    _MIDI      // MIDI layer (keep as is)
};

/* Custom keycodes */
enum planck_keycodes {
    QWERTY = SAFE_RANGE,
    DEF,
    BACKLIT,
    SAM,
    PSWD,
    SMART_NUM,    // urob's smart num behavior
    MAGIC_SHIFT,  // urob's magic shift behavior
    NAV_BSPC,     // urob's smart backspace
    NAV_DEL,      // urob's smart delete
    LEADER,       // Leader key for umlauts and special chars
    DSK_PREV,     // Previous desktop
    DSK_NEXT,     // Next desktop
    PIN_WIN,      // Pin window across desktops
    PIN_APP,      // Pin application across desktops
    DSK_MGR,      // Desktop manager
};

#define NUM      MO(_NUM)
#define SYM      MO(_SYM)
#define FN       MO(_FN)
#define NAV      MO(_NAV)
#define MIDI     TG(_MIDI)
#define CTRL_ESC LCTL_T(KC_ESC)

/* ───────────────────────────── Tap Dance ──────────────────────────────── */
enum {
    TD_SCLN_COLN,
    TD_QUOT_DQUOT,
    TD_SLSH_QUES,
    TD_C_COPY,
    TD_V_PASTE,
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_SCLN_COLN]  = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
    [TD_QUOT_DQUOT] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQUO),
    [TD_SLSH_QUES]  = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_QUES),
    [TD_C_COPY]     = ACTION_TAP_DANCE_DOUBLE(KC_C, LGUI(KC_C)),
    [TD_V_PASTE]    = ACTION_TAP_DANCE_DOUBLE(KC_V, LGUI(KC_V)),
};

/* ═══════════════════════════════════════════════════════════════════════════════════════════════════
 * SMART COMBOS - UROB'S POSITIONAL SYSTEM
 * Based on urob's ZMK config using physical positions instead of letters
 * Layout reference: LT3=Q, LT2=W, LT1=F, LT0=P | RT0=J, RT1=L, RT2=U, RT3=Y
 *                   LM3=A, LM2=R, LM1=S, LM0=T | RM0=N, RM1=E, RM2=I, RM3=O
 *                   LB3=Z, LB2=X, LB1=C, LB0=D | RB0=K, RB1=H, RB2=,, RB3=.
 * ═══════════════════════════════════════════════════════════════════════════════════════════════════ */

enum combo_events {
    // Navigation combos (existing)
    ESC_COMBO,      // W+F = Escape
    BSPC_COMBO,     // L+U = Backspace
    LEADER_COMBO,   // S+T = Leader key

    // urob's horizontal combos (left hand)
    TAB_COMBO,      // A+R = Tab
    CUT_COMBO,      // Z+C = Cut
    COPY_COMBO,     // Z+X = Copy
    PASTE_COMBO,    // X+C = Paste

    // urob's horizontal combos (right hand)
    DEL_COMBO,      // U+Y = Delete
    LPRN_COMBO,     // E+I = (
    RPRN_COMBO,     // I+O = )
    LBRC_COMBO,     // H+, = [
    RBRC_COMBO,     // ,+. = ]

    // urob's vertical symbol combos (left hand)
    AT_COMBO,       // Q+A = @
    HASH_COMBO,     // W+R = #
    DOLLAR_COMBO,   // F+S = $
    PERCENT_COMBO,  // P+T = %
    GRAVE_COMBO,    // A+Z = `
    BACKSLASH_COMBO,// R+X = backslash
    EQUALS_COMBO,   // S+C = =
    TILDE_COMBO,    // T+D = ~

    // urob's vertical symbol combos (right hand)
    CARET_COMBO,    // J+M = ^
    PLUS_COMBO,     // L+N = +
    STAR_COMBO,     // U+E = *
    AMPER_COMBO,    // Y+I = &
    UNDERSCORE_COMBO,// M+K = _
    MINUS_COMBO,    // N+H = -
    SLASH_COMBO,    // E+, = /
    PIPE_COMBO,     // I+. = |
};

// Navigation combos
const uint16_t PROGMEM esc_combo[] = {KC_W, KC_F, COMBO_END};    // W+F = Escape
const uint16_t PROGMEM bspc_combo[] = {KC_L, KC_U, COMBO_END};   // L+U = Backspace
const uint16_t PROGMEM leader_combo[] = {HRM_S, HRM_T, COMBO_END}; // S+T = Leader key

// urob's horizontal combos (left hand)
const uint16_t PROGMEM tab_combo[] = {HRM_A, HRM_R, COMBO_END};       // A+R = Tab
const uint16_t PROGMEM cut_combo[] = {KC_Z, KC_C, COMBO_END};         // Z+C = Cut
const uint16_t PROGMEM copy_combo[] = {KC_Z, KC_X, COMBO_END};        // Z+X = Copy
const uint16_t PROGMEM paste_combo[] = {KC_X, KC_C, COMBO_END};       // X+C = Paste

// urob's horizontal combos (right hand)
const uint16_t PROGMEM del_combo[] = {KC_U, KC_Y, COMBO_END};         // U+Y = Delete
const uint16_t PROGMEM lprn_combo[] = {HRM_E, HRM_I, COMBO_END};      // E+I = (
const uint16_t PROGMEM rprn_combo[] = {HRM_I, HRM_O, COMBO_END};      // I+O = )
const uint16_t PROGMEM lbrc_combo[] = {KC_H, KC_COMM, COMBO_END};     // H+, = [
const uint16_t PROGMEM rbrc_combo[] = {KC_COMM, KC_DOT, COMBO_END};   // ,+. = ]

// urob's vertical symbol combos (left hand) - using homerow mod keycodes
const uint16_t PROGMEM at_combo[] = {KC_Q, HRM_A, COMBO_END};         // Q+A = @
const uint16_t PROGMEM hash_combo[] = {KC_W, HRM_R, COMBO_END};       // W+R = #
const uint16_t PROGMEM dollar_combo[] = {KC_F, HRM_S, COMBO_END};     // F+S = $
const uint16_t PROGMEM percent_combo[] = {KC_P, HRM_T, COMBO_END};    // P+T = %
const uint16_t PROGMEM grave_combo[] = {HRM_A, KC_Z, COMBO_END};      // A+Z = `
const uint16_t PROGMEM backslash_combo[] = {HRM_R, KC_X, COMBO_END};  // R+X = backslash
const uint16_t PROGMEM equals_combo[] = {HRM_S, KC_C, COMBO_END};     // S+C = =
const uint16_t PROGMEM tilde_combo[] = {HRM_T, KC_D, COMBO_END};      // T+D = ~

// urob's vertical symbol combos (right hand) - using homerow mod keycodes
const uint16_t PROGMEM caret_combo[] = {KC_J, KC_M, COMBO_END};        // J+M = ^
const uint16_t PROGMEM plus_combo[] = {KC_L, HRM_N, COMBO_END};       // L+N = +
const uint16_t PROGMEM star_combo[] = {KC_U, HRM_E, COMBO_END};       // U+E = *
const uint16_t PROGMEM amper_combo[] = {KC_Y, HRM_I, COMBO_END};      // Y+I = &
const uint16_t PROGMEM underscore_combo[] = {KC_M, KC_K, COMBO_END};   // M+K = _
const uint16_t PROGMEM minus_combo[] = {HRM_N, KC_H, COMBO_END};     // N+H = -
const uint16_t PROGMEM slash_combo[] = {HRM_E, KC_COMM, COMBO_END};   // E+, = /
const uint16_t PROGMEM pipe_combo[] = {HRM_I, KC_DOT, COMBO_END};     // I+. = |


// Define what each combo does - urob's complete symbol system
combo_t key_combos[] = {
    // Navigation combos
    [ESC_COMBO] = COMBO(esc_combo, KC_ESC),      // W+F = Escape
    [BSPC_COMBO] = COMBO(bspc_combo, KC_BSPC),   // L+U = Backspace
    [LEADER_COMBO] = COMBO(leader_combo, LEADER), // S+T = Leader key

    // urob's horizontal combos (left hand)
    [TAB_COMBO] = COMBO(tab_combo, KC_TAB),      // A+R = Tab
    [CUT_COMBO] = COMBO(cut_combo, LGUI(KC_X)), // Z+C = Cut
    [COPY_COMBO] = COMBO(copy_combo, LGUI(KC_C)), // Z+X = Copy
    [PASTE_COMBO] = COMBO(paste_combo, LGUI(KC_V)), // X+C = Paste

    // urob's horizontal combos (right hand)
    [DEL_COMBO] = COMBO(del_combo, KC_DEL),      // U+Y = Delete
    [LPRN_COMBO] = COMBO(lprn_combo, KC_LPRN),  // E+I = (
    [RPRN_COMBO] = COMBO(rprn_combo, KC_RPRN),  // I+O = )
    [LBRC_COMBO] = COMBO(lbrc_combo, KC_LBRC),  // H+, = [
    [RBRC_COMBO] = COMBO(rbrc_combo, KC_RBRC),  // ,+. = ]

    // urob's vertical symbol combos (left hand)
    [AT_COMBO] = COMBO(at_combo, KC_AT),         // Q+A = @
    [HASH_COMBO] = COMBO(hash_combo, KC_HASH),   // W+R = #
    [DOLLAR_COMBO] = COMBO(dollar_combo, KC_DLR), // F+S = $
    [PERCENT_COMBO] = COMBO(percent_combo, KC_PERC), // P+T = %
    [GRAVE_COMBO] = COMBO(grave_combo, KC_GRV),  // A+Z = `
    [BACKSLASH_COMBO] = COMBO(backslash_combo, KC_BSLS), // R+X = backslash
    [EQUALS_COMBO] = COMBO(equals_combo, KC_EQL), // S+C = =
    [TILDE_COMBO] = COMBO(tilde_combo, KC_TILD), // T+D = ~

    // urob's vertical symbol combos (right hand)
    [CARET_COMBO] = COMBO(caret_combo, KC_CIRC), // J+N = ^
    [PLUS_COMBO] = COMBO(plus_combo, KC_PLUS),   // L+E = +
    [STAR_COMBO] = COMBO(star_combo, KC_ASTR),   // U+I = *
    [AMPER_COMBO] = COMBO(amper_combo, KC_AMPR), // Y+O = &
    [UNDERSCORE_COMBO] = COMBO(underscore_combo, KC_UNDS), // N+K = _
    [MINUS_COMBO] = COMBO(minus_combo, KC_MINS), // E+H = -
    [SLASH_COMBO] = COMBO(slash_combo, KC_SLSH), // I+, = /
    [PIPE_COMBO] = COMBO(pipe_combo, KC_PIPE),   // O+. = |
};

/* ═══════════════════════════════════════════════════════════════════════════════════════════════════
 * COMBO TIMING CONFIGURATION
 * Make leader combo fire before homerow mods activate
 * ═══════════════════════════════════════════════════════════════════════════════════════════════════ */

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch (index) {
        case ESC_COMBO:
        case BSPC_COMBO:
            return 15;  // Fast navigation combos

        // Combos involving homerow mods need longer timing
        case HASH_COMBO:     // W+R = #
        case DOLLAR_COMBO:   // F+S = $
        case PERCENT_COMBO:  // P+T = %
        case CARET_COMBO:    // J+N = ^
        case PLUS_COMBO:     // L+E = +
        case STAR_COMBO:     // U+I = *
        case AMPER_COMBO:    // Y+O = &
            return 30;  // Longer timing for homerow conflicts

        default:
            return COMBO_TERM;  // Default 18ms for safe combos
    }
}



/* ══════════════════════════════════════════════════════════════════════════════════════════════════════
 * KEYMAPS - EXPERIMENTAL WITH BILATERAL HOMEROW MODS
 * ══════════════════════════════════════════════════════════════════════════════════════════════════════ */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak with Bilateral Homerow Mods (EXPERIMENTAL)
 * ┌────────────────────────────────────────────────────────────────────────────────────────────────────┐
 * │ Key Innovation: Homerow mods use bilateral combinations (opposite hands)                           │
 * │ Left hand: A=Cmd, R=Alt, S=Ctrl, T=Shift                                                          │
 * │ Right hand: N=Shift, E=Ctrl, I=Alt, O=Cmd                                                         │
 * │ This eliminates timing issues - when you press A+N it triggers immediately                        │
 * └────────────────────────────────────────────────────────────────────────────────────────────────────┘
 *
 * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
 * │ Tab │  Q  │  W  │  F  │  P  │  B  │  J  │  L  │  U  │  Y  │ ;:  │Bksp │
 * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │Esc  │A/Cmd│R/Alt│S/Ctl│T/Sft│  G  │  M  │N/Sft│E/Ctl│I/Alt│O/Cmd│ '"  │
 * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │ ⇧   │  Z  │  X  │  C  │  D  │V/⌘V │  K  │  H  │  ,  │  .  │ /?  │ ⇧   │
 * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │  [  │ Alt │HYPR │ NUM │⌘/Spc│⌥/Spc│⇧/Ent│NAV/E│ SYM │ F18 │ Alt │  ]  │
 * └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
 */
[_DEF] = LAYOUT_planck_grid(
    KC_TAB,        KC_Q,  KC_W,       KC_F,   KC_P,    KC_B,            KC_J,           KC_L,  KC_U,    KC_Y,         TD(TD_SCLN_COLN), KC_BSPC,
    KC_ESC,        HRM_A, HRM_R,      HRM_S,  HRM_T,   KC_G,            KC_M,           HRM_N, HRM_E,   HRM_I,        HRM_O,            TD(TD_QUOT_DQUOT),
    OSM(MOD_LSFT), KC_Z,  KC_X,       KC_C,   KC_D,    TD(TD_V_PASTE),  KC_K,           KC_H,  KC_COMM, KC_DOT,       TD(TD_SLSH_QUES), OSM(MOD_RSFT),
    PSWD, KC_LALT, HYPR(KC_NO), NUM, LT(_NAV, KC_SPC), LT(_FN, KC_ENT), SMART_NUM, MAGIC_SHIFT, SYM, KC_F18, KC_RALT, KC_RBRC
),

/* QWERTY with urob's Bilateral Homerow Mods and Smart Behaviors
 * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
 * │ Tab │  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │Bksp │
 * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │Esc  │A/⌘  │S/⌥  │D/⌃  │F/⇧  │  G  │  H  │J/⇧  │K/⌃  │L/⌥  │;/⌘  │ '"  │
 * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │ ⇧   │  Z  │  X  │  C  │  V  │V/⌘V │  N  │  M  │  ,  │  .  │ /?  │ ⇧   │
 * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │  [  │ Alt │HYPR │ NUM │Spc/NAV│Ent/FN│SmartNUM│MagicSHFT│SYM│ F18│ Alt │  ]  │
 * └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,        KC_Q,     KC_W,       KC_E,     KC_R,    KC_T,            KC_Y,    KC_U,     KC_I,    KC_O,      KC_P,              KC_BSPC,
    KC_ESC,        HRM_A_Q,  HRM_S_Q,    HRM_D_Q,  HRM_F_Q, KC_G,            KC_H,    HRM_J_Q,  HRM_K_Q, HRM_L_Q,   HRM_SCLN_Q,        TD(TD_QUOT_DQUOT),
    OSM(MOD_LSFT), KC_Z,     KC_X,       KC_C,     KC_V,    TD(TD_V_PASTE),  KC_N,    KC_M,     KC_COMM, KC_DOT,    TD(TD_SLSH_QUES),  OSM(MOD_RSFT),
    PSWD, KC_LALT, HYPR(KC_NO), NUM, LT(_NAV, KC_SPC), LT(_FN, KC_ENT), SMART_NUM, MAGIC_SHIFT, SYM, KC_F18, KC_RALT, KC_RBRC
),

/* Number Layer - urob's exact layout with Colemak positions */
[_NUM] = LAYOUT_planck_grid(
    _______ , _______ , KC_7    , KC_8    , KC_9    , _______ , _______ , _______ , _______ , _______ , _______ , _______,
    _______ , KC_0    , KC_4    , KC_5    , KC_6    , _______ , _______ , _______ , _______ , _______ , _______ , _______,
    _______ , _______ , KC_1    , KC_2    , KC_3    , _______ , _______ , _______ , _______ , _______ , _______ , _______,
    _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
),

/* Symbol Layer - restored for reliable symbol access */
[_SYM] = LAYOUT_planck_grid(
    _______ , KC_F11  , KC_F12  , KC_F13  , KC_F14  , KC_F15  , KC_F16  , KC_F17  , KC_F18  , KC_F19  , KC_F20  , _______,
    _______ , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , _______,
    _______ , KC_UNDS , KC_PLUS , KC_TILD , KC_PIPE , _______ , _______ , _______ , _______ , _______ , _______ , _______,
    _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
),

/* Function Layer - urob's exact FN layer corrected */
[_FN] = LAYOUT_planck_grid(
    _______ , KC_F12  , KC_F7   , KC_F8   , KC_F9   , _______ , _______ , KC_MPRV , KC_VOLU , KC_MNXT , _______ , _______,
    _______ , LGUI_T(KC_F11), LALT_T(KC_F4), LSFT_T(KC_F5), LCTL_T(KC_F6), _______ , _______ , DSK_PREV, RSFT_T(KC_VOLD), DSK_NEXT, _______ , _______,
    _______ , KC_F10  , KC_F1   , KC_F2   , KC_F3   , _______ , _______ , PIN_APP , PIN_WIN , DSK_MGR , _______ , _______,
    _______ , _______ , _______ , _______ , _______ , _______ , _______ ,  KC_MPLY ,_______, _______ , _______ , _______
),

/* System Layer - urob's Sys layer equivalent */
[_SYS] = LAYOUT_planck_grid(
    DEF    , AU_ON  , AU_OFF , _______, _______, RM_TOGG, _______, RM_NEXT, RM_HUEU, RM_SATU, RM_VALU, _______,
    QWERTY , MU_ON  , MU_OFF , _______, _______, QK_BOOT, QK_BOOT, RM_PREV, RM_HUED, RM_SATD, RM_VALD, _______,
    MIDI   , MI_ON  , MI_OFF , _______, _______, EE_CLR , EE_CLR , _______, _______, _______, _______, _______,
    _______, AU_PREV, AU_NEXT, _______, _______, _______, _______, _______, _______, _______, _______, DB_TOGG
),
/* Navigation Layer - urob's exact layout */
[_NAV] = LAYOUT_planck_grid(
    _______ , LALT(KC_F4), _______ , LSFT(KC_TAB), LALT(KC_TAB), _______ , KC_PGUP, NAV_BSPC, KC_UP   , NAV_DEL , _______ , _______,
    _______ , OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LSFT), OSM(MOD_LCTL), _______ , KC_PGDN, KC_LEFT , KC_DOWN , KC_RGHT , KC_ENT  , _______,
    _______ , _______, _______, _______, _______, _______ , KC_INS , KC_TAB  , _______ , _______ , _______ , _______,
    _______ , _______, _______, _______, _______, _______ , KC_CNCL, _______ , _______ , _______ , _______ , _______
),

/* MIDI Layer (unchanged from original) */
[_MIDI] = LAYOUT_planck_grid(
    MI_OCN2,   MI_OCN1,   MI_OC1,  MI_OC2,   MI_VELD, MI_VELU, MI_TRSD, MI_TRSU, MI_SUST, MI_SOFT, MI_AOFF, MIDI,
    MI_Cs,     MI_Ds,     _______, MI_Fs,    MI_Gs,   MI_As,   _______, MI_Cs,   MI_Ds,   _______,  MI_Fs,   MI_Gs,
    MI_C,      MI_D,      MI_E,    MI_F,     MI_G,    MI_A,    MI_B,    MI_C,    MI_D,    MI_E,     MI_F,    MI_G,
    MIDI,      _______,   _______, _______,  _______, _______, _______, _______, _______, _______,  _______, _______
),
};

/* ═══════════════════════════════════════════════════════════════════════════════════════════════════
 * BILATERAL HOMEROW MODS CONFIGURATION FUNCTIONS
 * ═══════════════════════════════════════════════════════════════════════════════════════════════════ */

// Per-key tapping term - urob's approach uses consistent 280ms
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Homerow mods (both Colemak and QWERTY)
        case HRM_A:     // Colemak A, same as QWERTY A
        case HRM_R:     // Colemak R
        case HRM_S:     // Colemak S, same as QWERTY S
        case HRM_T:     // Colemak T
        case HRM_N:     // Colemak N
        case HRM_E:     // Colemak E
        case HRM_I:     // Colemak I
        case HRM_O:     // Colemak O
        // QWERTY-only homerow mods (different from Colemak)
        case HRM_D_Q:   // QWERTY D
        case HRM_F_Q:   // QWERTY F
        case HRM_J_Q:   // QWERTY J
        case HRM_K_Q:   // QWERTY K
        case HRM_L_Q:   // QWERTY L
        case HRM_SCLN_Q: // QWERTY ;
            return TAPPING_TERM;  // Same 280ms as urob
        default:
            return TAPPING_TERM;
    }
}

// Bilateral combinations - only apply permissive hold to opposite hand combinations
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Apply permissive hold to all homerow mods for bilateral combinations
        // Homerow mods (both Colemak and QWERTY)
        case HRM_A:     // Colemak A, same as QWERTY A
        case HRM_R:     // Colemak R
        case HRM_S:     // Colemak S, same as QWERTY S
        case HRM_T:     // Colemak T
        case HRM_N:     // Colemak N
        case HRM_E:     // Colemak E
        case HRM_I:     // Colemak I
        case HRM_O:     // Colemak O
        // QWERTY-only homerow mods (different from Colemak)
        case HRM_D_Q:   // QWERTY D
        case HRM_F_Q:   // QWERTY F
        case HRM_J_Q:   // QWERTY J
        case HRM_K_Q:   // QWERTY K
        case HRM_L_Q:   // QWERTY L
        case HRM_SCLN_Q: // QWERTY ;
            return true;
        default:
            return false;
    }
}

/* ═══════════════════════════════════════════════════════════════════════════════════════════════════
 * RGB MATRIX AND LAYER STATE (unchanged from original)
 * ═══════════════════════════════════════════════════════════════════════════════════════════════════ */

static inline void set_group_hsv(const uint8_t *grp, uint8_t cnt, uint8_t h, uint8_t s, uint8_t v) {
    RGB c = hsv_to_rgb((HSV){h, s, v});
    for (uint8_t i = 0; i < cnt; i++) {
        rgb_matrix_set_color(grp[i], c.r, c.g, c.b);
    }
}

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_user(void) {
    // Layer-specific lighting disabled as requested
    // RGB matrix effects (RM_NEXT, etc.) still work
    return false; // keep animations
}

// Built-in RGB matrix effects are enabled and will be accessible via RM_NEXT
// Custom effects removed due to QMK compilation complexity
#endif

#ifdef AUDIO_ENABLE
float plover_song[][2]    = SONG(PLOVER_SOUND);
float plover_gb_song[][2] = SONG(PLOVER_GOODBYE_SOUND);
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
    // urob's auto-activation: Start numword when typing any number
    if (record->event.pressed && !num_word_active && !sticky_num_active &&
        (keycode >= KC_1 && keycode <= KC_0)) {
        num_word_active = true;
        layer_on(_NUM);
    }

    // Handle num-word and sticky-num cancellation FIRST, before other processing
    if ((num_word_active || sticky_num_active) && record->event.pressed) {
        if (!(keycode >= KC_1 && keycode <= KC_0) &&
            keycode != KC_BSPC && keycode != KC_DEL) {
            if (num_word_active) {
                num_word_active = false;
                layer_off(_NUM);
            }
            // Sticky num stays active until manually cancelled with SMART_NUM tap
        }
    }

    // Manual cancellation of sticky num layer
    if (sticky_num_active && record->event.pressed && keycode == SMART_NUM) {
        sticky_num_active = false;
        if (!num_word_active) {
            layer_off(_NUM);
        }
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

    // Track last keycode for MAGIC_SHIFT repeat behavior
    if (record->event.pressed && keycode != MAGIC_SHIFT) {
        // Check if it's an alpha key (A-Z or homerow mods)
        bool is_alpha = (keycode >= KC_A && keycode <= KC_Z) ||
                       (keycode == HRM_A) || (keycode == HRM_R) || (keycode == HRM_S) || (keycode == HRM_T) ||
                       (keycode == HRM_N) || (keycode == HRM_E) || (keycode == HRM_I) || (keycode == HRM_O) ||
                       (keycode == HRM_A_Q) || (keycode == HRM_S_Q) || (keycode == HRM_D_Q) || (keycode == HRM_F_Q) ||
                       (keycode == HRM_J_Q) || (keycode == HRM_K_Q) || (keycode == HRM_L_Q) || (keycode == HRM_SCLN_Q);

        if (is_alpha) {
            // For homerow mods, store the base keycode for repeat
            if (keycode == HRM_A || keycode == HRM_A_Q) last_keycode = KC_A;
            else if (keycode == HRM_R) last_keycode = KC_R;
            else if (keycode == HRM_S || keycode == HRM_S_Q) last_keycode = KC_S;
            else if (keycode == HRM_T) last_keycode = KC_T;
            else if (keycode == HRM_N) last_keycode = KC_N;
            else if (keycode == HRM_E) last_keycode = KC_E;
            else if (keycode == HRM_I) last_keycode = KC_I;
            else if (keycode == HRM_O) last_keycode = KC_O;
            else if (keycode == HRM_D_Q) last_keycode = KC_D;
            else if (keycode == HRM_F_Q) last_keycode = KC_F;
            else if (keycode == HRM_J_Q) last_keycode = KC_J;
            else if (keycode == HRM_K_Q) last_keycode = KC_K;
            else if (keycode == HRM_L_Q) last_keycode = KC_L;
            else if (keycode == HRM_SCLN_Q) last_keycode = KC_SCLN;
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

    switch (keycode) {
        case SAM:
            if (record->event.pressed) {
                register_code(KC_LSFT);
                register_code(KC_LALT);
                register_code(KC_M);
            } else {
                unregister_code(KC_LSFT);
                unregister_code(KC_LALT);
                unregister_code(KC_M);
            }
            return false;

        case LT(0, KC_ENT):
            if (record->tap.count && record->event.pressed) {
                tap_code(KC_ENT);  // Tap: Enter
            } else if (record->event.pressed) {
                register_code(KC_LALT);  // Hold: Backspace
            } else if (!record->tap.count) {
                unregister_code(KC_LALT);  // Release hold
            }
            return false;

        case QWERTY:
            if (record->event.pressed) set_single_persistent_default_layer(_QWERTY);
            return false;

        case DEF:
            if (record->event.pressed) set_single_persistent_default_layer(_DEF);
            return false;

        case BACKLIT:
            if (record->event.pressed) register_code(KC_RSFT);
            else                        unregister_code(KC_RSFT);
            return false;

        case NAV_BSPC:
            if (record->event.pressed) {
                magic_shift_timer = timer_read();
                register_code(KC_BSPC);
            } else {
                unregister_code(KC_BSPC);
                if (timer_elapsed(magic_shift_timer) > 500) {
                    // Long press: delete previous word
                    register_mods(MOD_BIT(KC_LALT));
                    tap_code(KC_BSPC);
                    unregister_mods(MOD_BIT(KC_LALT));
                }
            }
            return false;

        case NAV_DEL:
            if (record->event.pressed) {
                magic_shift_timer = timer_read();
                register_code(KC_DEL);
            } else {
                unregister_code(KC_DEL);
                if (timer_elapsed(magic_shift_timer) > 500) {
                    // Long press: delete next word
                    register_mods(MOD_BIT(KC_LALT));
                    tap_code(KC_DEL);
                    unregister_mods(MOD_BIT(KC_LALT));
                }
            }
            return false;

        case PSWD:
            if (record->event.pressed) {
                SEND_STRING(PASSWORD_STRING);
            }
            return false;

        case SMART_NUM:
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

        case MAGIC_SHIFT:
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

        case LEADER:
            if (record->event.pressed) {
                leader_active = true;
                leader_timer = timer_read();
            }
            return false;

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

    // Handle leader key sequences
    if (leader_active && record->event.pressed) {
        if (timer_elapsed(leader_timer) > 3000) {
            // Leader timeout
            leader_active = false;
            return true;
        }

        switch (keycode) {
            case KC_A:  // ä
            case HRM_A: // ä (homerow mod)
                send_unicode_string("ä");
                leader_active = false;
                return false;
            case KC_O:  // ö
            case HRM_O: // ö (homerow mod)
                send_unicode_string("ö");
                leader_active = false;
                return false;
            case KC_U:  // ü
                send_unicode_string("ü");
                leader_active = false;
                return false;
            case KC_S:  // ß
            case HRM_S: // ß (homerow mod)
                send_unicode_string("ß");
                leader_active = false;
                return false;
            case KC_E:  // é
            case HRM_E: // é (homerow mod)
                send_unicode_string("é");
                leader_active = false;
                return false;
            case KC_C:  // ç
                send_unicode_string("ç");
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
            #ifdef AUDIO_ENABLE
            static bool play_sound = false;
            #endif
            if (active) {
                #ifdef AUDIO_ENABLE
                if (play_sound) PLAY_SONG(plover_song);
                #endif
                layer_on(_SYS);
            } else {
                #ifdef AUDIO_ENABLE
                if (play_sound) PLAY_SONG(plover_gb_song);
                #endif
                layer_off(_SYS);
            }
            #ifdef AUDIO_ENABLE
            play_sound = true;
            #endif

            break;
        }
    }
    return true;
}

