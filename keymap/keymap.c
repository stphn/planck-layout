/* Copyright 2015-2023 Jack Humbert
 * GPL-2.0-or-later
 */

#include QMK_KEYBOARD_H
#include "user_song_list.h"

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

/* Layers */
enum planck_layers {
    _QWERTY,
    _COLEMAK,
    _NUM,
    _SYM,
    _PLOVER,
    _ADJUST,
    _NAV
};

/* Custom keycodes */
enum planck_keycodes {
    QWERTY = SAFE_RANGE,
    COLEMAK,
    PLOVER,
    BACKLIT,
    EXT_PLV,
    SAM,
    /* Vim-style tap-hold: tap = letter, hold = arrow */
    N_VIM, E_VIM, I_VIM, O_VIM,
};

#define NUM      MO(_NUM)
#define SYM      MO(_SYM)
#define NAV      MO(_NAV)
#define CTRL_ESC LCTL_T(KC_ESC)

/* ───────────────── Vim tap-hold state ───────────────── */
typedef struct {
    uint16_t tap_code;   // letter
    uint16_t hold_code;  // arrow
    uint16_t timer;
    bool deciding;       // within TAPPING_TERM window
    bool held;           // hold has been registered
} vim_th_t;

static vim_th_t vim[4] = {0};

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

/* ============================== Keymaps ================================ */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY 
 * ,-----------------------------------------------------------------------------------------------------------------------.
 * |   Tab   |    Q    |    W    |    E    |    R    |    T    |    Y    |    U    |    I    |    O    |    P    |  Bksp   |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * | Ctr/Esc |    A    |    S    |    D    |    F    |    G    |    H    |    J    |    K    |    L    |    ;    |   '     |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * | Shift/( |    Z    |    X    |   C/⎘   |    C    |   V/⎘   |    V    |    B    |    ,    |    .    |   / ?   | Shift/) |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |    [    |   Alt   |   HYPR  |   NUM   |   LGUI  |   Space |  Ent/⌫  |   NAV   |   SYM   |   RGUI  |   Alt   |    ]    |
 * `-----------------------------------------------------------------------------------------------------------------------'
 * Notes:
 *  - Tap-dance:
 *      ; → ; / :      ' → ' / "
 *      C → C / ⌘C     V → V / ⌘V
 *      / → / / ?
 *  - Outer brackets [ ] mirror Colemak layer for symmetry.
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,     KC_Q,   KC_W,       KC_E,          KC_R,   KC_T,           KC_Y,          KC_U,   KC_I,    KC_O      , KC_P            , KC_BSPC,
    CTRL_ESC,   KC_A,   KC_S,       KC_D,          KC_F,   KC_G,           KC_H,          KC_J,   KC_K,    KC_L,     KC_SCLN          , TD(TD_QUOT_DQUOT),
    SC_LSPO,    KC_Z,   KC_X,       TD(TD_C_COPY), KC_C,   TD(TD_V_PASTE), KC_V,          KC_B,   KC_COMM, KC_DOT    , TD(TD_SLSH_QUES), SC_RSPC,
    KC_LBRC,    KC_LALT,HYPR(KC_NO),NUM,           KC_LGUI,SFT_T(KC_SPC),  LT(0, KC_ENT), NAV,    SYM,     KC_RGUI   , KC_RALT         , KC_RBRC
),

/* Colemak (base)
 * ,-----------------------------------------------------------------------------------------------------------------------.
 * |   Tab   |    Q    |    W    |    F    |    P    |    B    |    J    |    L    |    U    |    Y    |    ;    |  Bksp   |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * | Ctr/Esc |    A    |    R    |    S    |    T    |    G    |    M    |    N    |    E    |    I    |    O    | Ctrl/'  |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * | Shift/( |    Z    |    X    |    C    |    D    |    V    |    K    |    H    |    ,    |    .    |    /    | Shift/) |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |    [    |   Alt   |   HYPR  |   NUM   |   LGUI  |    󱁐    |  󰿄 :󰁮   |   SYM   |   NAV   |   RGUI  |   Alt   |    ]    |
 * `-----------------------------------------------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_grid(
    KC_TAB,     KC_Q,   KC_W,       KC_F,   KC_P,   KC_B,           KC_J,          KC_L,  KC_U,    KC_Y      , TD(TD_SCLN_COLN), KC_BSPC,
    CTRL_ESC,   KC_A,   KC_R,       KC_S,   KC_T,   KC_G,           KC_M,          KC_N,  KC_E ,   KC_I      , KC_O            , TD(TD_QUOT_DQUOT),
    SC_LSPO,    KC_Z,   KC_X,       KC_C,   KC_D,   TD(TD_V_PASTE), KC_K,          KC_H,  KC_COMM, KC_DOT    , TD(TD_SLSH_QUES), SC_RSPC,
    KC_LBRC,    KC_LALT,HYPR(KC_NO),NUM,    KC_LGUI,LALT_T(KC_SPC), HYPR_T(KC_ENT),NAV,   SYM,     KC_RGUI   , KC_RALT         , KC_RBRC
),
/* Number
 * ,-----------------------------------------------------------------------------------.
 * |       |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |       |
 * |-------+------+------+------+------+------+------+------+------+------+------+-------|
 * |       |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  0   |       |
 * |-------+------+------+------+------+------+------+------+------+------+------+-------|
 * |       |  -   |  =   |  `   |  \   |      |      |      |      |      |      |       |
 * |-------+------+------+------+------+------+------+------+------+------+------+-------|
 * |       |      |      |      |      |      |      |      |      |      |      |       |
 * `-----------------------------------------------------------------------------------'
 */
[_NUM] = LAYOUT_planck_grid(
    _______ , KC_F1    , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6  , KC_F7   , KC_F8   , KC_F9   , KC_F10  , _______,
    _______ , KC_1     , KC_2    , KC_3    , KC_4    , KC_5    , KC_6   , KC_7    , KC_8    , KC_9    , KC_0    , _______,
    _______ , KC_MINS  , KC_EQL  , KC_GRV  , KC_BSLS , _______ , _______, _______ , _______ , _______ , _______ , _______,
    _______ , _______  , _______ , _______ , _______ , _______ , _______, _______ , _______ , _______ , _______ , _______
),
/* Symbol
 * ,-----------------------------------------------------------------------------------.
 * |       | F11  | F12  | F13  | F14  | F15  | F16  | F17  | F18  | F19  | F20  |       |
 * |-------+------+------+------+------+------+------+------+------+------+------+-------|
 * |       |  !   |  @   |  #   |  $   |  %   |  ^   |  &   |  *   |  (   |  )   |       |
 * |-------+------+------+------+------+------+------+------+------+------+------+-------|
 * |       |  _   |  +   |  ~   |  |   |      |      |      |      |      |      |       |
 * |-------+------+------+------+------+------+------+------+------+------+------+-------|
 * |       |      |      |      |      |      |      |      |      |      |      |       |
 * `-----------------------------------------------------------------------------------'
 */
[_SYM] = LAYOUT_planck_grid(
    _______ , KC_F11  , KC_F12  , KC_F13  , KC_F14  , KC_F15  , KC_F16  , KC_F17  , KC_F18  , KC_F19  , KC_F20  , _______,
    _______ , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , _______,
    _______ , KC_UNDS , KC_PLUS , KC_TILD , KC_PIPE , _______ , _______ , _______ , _______ , _______ , _______ , _______,
    _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
),
/* Adjust (RGB, Boot, Audio, Default layers)
 * ,-----------------------------------------------------------------------------------.
 * |       | Boot | Debug| RMtog| RMnext| Hue+ | Hue- | Sat+ | Sat- | Val+ | Val- |       |
 * |-------+------+------+------+------+------+------+------+------+------+------+-------|
 * |       | EECL | MuNx | AudOn| AudOff| AG N | AG Sw|      |      |      | QWRT | COLM  |
 * |-------+------+------+------+------+------+------+------+------+------+------+-------|
 * |       | MuPr | MuNx | MusOn| MusOff| MidiOn|MidiOff|    |      |      |      |       |
 * |-------+------+------+------+------+------+------+------+------+------+------+-------|
 * |       |      |      |      |      |      |      |      |      |      |      |       |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, QK_BOOT, DB_TOGG, RM_TOGG, RM_NEXT, RM_HUEU, RM_HUED, RM_SATU, RM_SATD, RM_VALU, RM_VALD, _______,
    _______, EE_CLR,  MU_NEXT, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______, _______, QWERTY,  COLEMAK,
    _______, AU_PREV, AU_NEXT, MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
/* Navigate (arrows, media, brightness, app switch, mouse)
 * ,------------------------------------------------------------------------------------.
 * | Mute  | Vol- | Vol+ |  ☼-  |  ☼+  |      |      | Home | PgDn | PgUp | End   |     |
 * |-------+------+------+------+------+------+------+------+------+------+-------+-----|
 * |       | Alt↹ | C-↓  | C-↑  |  SAM |      |      |  ←   |  ↓   |  ↑   |  →    |     |
 * |-------+------+------+------+------+------+------+------+------+------+-------+-----|
 * |       |      | M1   | M2   |  M3  |      |      | MS←  | MS↓  | MS↑  | MS→   |     |
 * |-------+------+------+------+------+------+------+------+------+------+-------+-----|
 * |       |      |      |      |      |      |      |      |      |      |       |     |
 * `------------------------------------------------------------------------------------'
 * Legend: Alt↹ = LALT+Tab, C-↓/C-↑ = Ctrl+arrow, M1/M2/M3 = Mouse buttons, MS = mouse move
 */
[_NAV] = LAYOUT_planck_grid(
    KC_MUTE , KC_VOLD,      KC_VOLU,        KC_BRID,    KC_BRIU,    _______ , _______ , KC_HOME, KC_PGDN , KC_PGUP , KC_END,  _______ ,
    _______ , LALT(KC_SPC), LCTL(KC_DOWN) , LCTL(KC_UP),LALT(KC_M), _______ , _______ , KC_LEFT, KC_DOWN , KC_UP ,   KC_RGHT, _______ ,
    _______ , _______,      MS_BTN1       , MS_BTN2,    MS_BTN3,    _______ , _______ , MS_LEFT, MS_DOWN , MS_UP ,   MS_RGHT, _______ ,
    _______ , _______,      _______       , _______,    _______,    _______ , _______ , _______, _______ , _______ , _______, _______
),
/* Plover (steno) */
[_PLOVER] = LAYOUT_planck_grid(
    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   ,
    _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
    _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    EXT_PLV, _______, _______, KC_C,    KC_V,    _______, _______, KC_N,    KC_M,    _______, _______, _______
),
};
/* ============================ End Keymaps ============================== */
// HSV helper defined once (above rgb_matrix_indicators_user)
static inline void set_group_hsv(const uint8_t *grp, uint8_t cnt, uint8_t h, uint8_t s, uint8_t v) {
    RGB c = hsv_to_rgb((HSV){h, s, v});
    for (uint8_t i = 0; i < cnt; i++) {
        rgb_matrix_set_color(grp[i], c.r, c.g, c.b);
    }
}
#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_user(void) {
    uint8_t n = RGB_MATRIX_LED_COUNT;
    uint8_t mods = get_mods() | get_oneshot_mods();
    if (!n) return false;

    if (layer_state_is(_NUM)) set_group_hsv(LED_LEFT,  sizeof LED_LEFT,  213, 180, 220);
    if (layer_state_is(_SYM)) set_group_hsv(LED_RIGHT, sizeof LED_RIGHT,   0, 200, 200);
    if (layer_state_is(_NAV)) set_group_hsv(LED_TOP,   sizeof LED_TOP,    85, 130, 255);

    if ( (mods & MOD_MASK_GUI) &&
         (mods & MOD_MASK_CTRL) &&
         (mods & MOD_MASK_ALT)  &&
         (mods & MOD_MASK_SHIFT) ) {
        set_group_hsv(LED_MID, sizeof LED_MID, 200, 255, 255);   // Hyper
    } else if ( (mods & MOD_MASK_GUI) &&
               !(mods & (MOD_MASK_CTRL | MOD_MASK_ALT | MOD_MASK_SHIFT)) ) {
        set_group_hsv(LED_MID, sizeof LED_MID,   4, 138, 250);   // GUI only
    }

    return false; // keep animations
}
#endif

#ifdef AUDIO_ENABLE
float plover_song[][2]    = SONG(PLOVER_SOUND);
float plover_gb_song[][2] = SONG(PLOVER_GOODBYE_SOUND);
float coin_up[][2]        = SONG(AUDIO_ON_SOUND);
float mario_game_over[][2] = SONG(MARIO_GAMEOVER);
#endif

// Keep animations dynamic: only tri-layer logic here.
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _NUM, _SYM, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
    /* Vim tap-hold handling */
    vim_th_t *st = NULL;
    switch (keycode) {
        case N_VIM: st = &vim[0]; st->tap_code = KC_N; st->hold_code = KC_LEFT;  break;
        case E_VIM: st = &vim[1]; st->tap_code = KC_E; st->hold_code = KC_DOWN;  break;
        case I_VIM: st = &vim[2]; st->tap_code = KC_I; st->hold_code = KC_UP;    break;
        case O_VIM: st = &vim[3]; st->tap_code = KC_O; st->hold_code = KC_RIGHT; break;
    }
    if (st) {
        if (record->event.pressed) {
            st->timer    = timer_read();
            st->deciding = true;
            st->held     = false;
        } else {
            if (st->held) {
                unregister_code16(st->hold_code);
            } else if (timer_elapsed(st->timer) < TAPPING_TERM) {
                tap_code16(st->tap_code);
            }
            st->deciding = false;
        }
        return false;
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

        case COLEMAK:
            if (record->event.pressed) set_single_persistent_default_layer(_COLEMAK);
            return false;

        case BACKLIT:
            if (record->event.pressed) register_code(KC_RSFT);
            else                        unregister_code(KC_RSFT);
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
                if (!eeconfig_is_enabled()) eeconfig_init();
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

/* Re-register holds after TAPPING_TERM for auto-repeat */
void matrix_scan_user(void) {
    for (int i = 0; i < 4; i++) {
        vim_th_t *st = &vim[i];
        if (st->deciding && !st->held && timer_elapsed(st->timer) >= TAPPING_TERM) {
            register_code16(st->hold_code);
            st->held = true;
            st->deciding = false; // decision made
        }
    }
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
                layer_on(_ADJUST);
            } else {
                #ifdef AUDIO_ENABLE
                if (play_sound) PLAY_SONG(plover_gb_song);
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
