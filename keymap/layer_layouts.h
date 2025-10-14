/* Copyright 2015-2023 Jack Humbert
 * GPL-2.0-or-later
 *
 * LAYER LAYOUT DIAGRAMS AND DOCUMENTATION
 * Beautiful visual representations of all keyboard layers
 */

#pragma once

/* ╔════════════════════════════════════════════════════════════════════════════════╗
 * ║  COLEMAK DH with BILATERAL HOMEROW MODS (EXPERIMENTAL)                         ║
 * ╠════════════════════════════════════════════════════════════════════════════════╣
 * ║  Key Innovation: Homerow mods use bilateral combinations (opposite hands)      ║
 * ║  Left hand:  A=Cmd  R=Alt  S=Ctrl  T=Shift                                     ║
 * ║  Right hand: N=Shift E=Ctrl I=Alt   O=Cmd                                      ║
 * ║  This eliminates timing issues - when you press A+N it triggers immediately    ║
 * ╚════════════════════════════════════════════════════════════════════════════════╝
 *
 * ╭────────────────────────────────────────────────────────────────────────────────╮
 * │                                    PLANCK LAYOUT                               │
 * ╞═════╤═════╤═════╤═════╤═════════╤════════╦══════╤══════╤═════╤═════╤═════╤═════╡
 * │ Tab │  Q  │  W  │  F  │    P    │  B     ║   J  │  L   │  U  │  Y  │  ;: │Bksp │
 * ╞═════╪═════╪═════╪═════╪═════════╪════════╬══════╪══════╪═════╪═════╪═════╪═════╡
 * │ Esc │A/Cmd│R/Alt│S/Ctl│  T/Sft  │  G     ║   M  │N/Sft │E/Ctl│I/Alt│O/Cmd│ '"  │
 * ╞═════╪═════╪═════╪═════╪═════════╪════════╬══════╪══════╪═════╪═════╪═════╪═════╡
 * │Shift│  Z  │  X  │  C  │    D    │  V     ║   K  │  H   │ ,<  │ .>  │ ?/  │Shift│
 * ╞═════╪═════╪═════╪═════╪═════════╪════════╬══════╪══════╪═════╪═════╪═════╪═════╡
 * │PSWD │ Alt │HYPR │ NUM │ SPC/NAV │ ENT/FN ║SmartN│MagicS│ F18 │GAME │ Alt │  ]  │
 * ╰─────┴─────┴─────┴─────┴─────────┴────────┴──────┴──────┴─────┴─────┴─────┴─────╯
 */

/* ╔═══════════════════════════════════════════════════════════════════════════════╗
 * ║  GAMING LAYER - PURE PERFORMANCE MODE                                         ║
 * ╠═══════════════════════════════════════════════════════════════════════════════╣
 * ║  No combos, no homerow mods - zero input lag for competitive gaming           ║
 * ║  WASD movement cluster optimized with PlayStation face button mapping         ║
 * ║  SOCD cleaning enabled (Last Input Priority) for precise directional input    ║
 * ╚═══════════════════════════════════════════════════════════════════════════════╝
 *
 * ╭───────────────────────────────────────────────────────────────────────╮
 * │                                 GAMING MODE QWERTY                    │
 * ╞═════╤═════╤═════╤═════╤═════╤═════╦═════╤═════╤═════╤═════╤═════╤═════╡
 * │ Tab │  Q  │  W* │  E  │  R  │  T  ║  Y  │  U  │  I  │  O  │  P  │Bksp │
 * ╞═════╪═════╪═════╪═════╪═════╪═════╬═════╪═════╪═════╪═════╪═════╪═════╡
 * │ Esc │ A*  │ S*  │ D*  │  F  │  G  ║  H  │  J  │  K  │  L  │  ;  │  '  │
 * ╞═════╪═════╪═════╪═════╪═════╪═════╬═════╪═════╪═════╪═════╪═════╪═════╡
 * │Shift│  Z  │  X  │  C  │  V  │  B  ║  N  │  M  │  ,  │  .  │  /  │Shift│
 * ╞═════╪═════╪═════╪═════╪═════╪═════╬═════╪═════╪═════╪═════╪═════╪═════╡
 * │Ctrl │ Alt │ Win │ NUM │Space│Enter║Space│ NUM │ SYS │ DEF │ Alt │Ctrl │
 * ╰─────┴─────┴─────┴─────┴─────┴─────┺─────┴─────┴─────┴─────┴─────┴─────╯
 *
 * Legend: *=SOCD Cleaned Keys (W/S and A/D pairs)
 *         H/J/K/L=PlayStation face buttons (Square/Triangle/X/Circle)
 *         DEF=Return to Default Layer
 */

/* ╔═══════════════════════════════════════════════════════════════════════╗
 * ║  NUMBER LAYER - UROB'S OPTIMIZED NUMERIC INPUT                        ║
 * ╠═══════════════════════════════════════════════════════════════════════╣
 * ║  Calculator layout with numpad-style arrangement on left hand         ║
 * ║  Auto-activates on number input, double-tap SMART_NUM for sticky mode ║
 * ║  Colemak home positions preserved for hybrid typing                   ║
 * ╚═══════════════════════════════════════════════════════════════════════╝
 *
 * ╭───────────────────────────────────────────────────────────────────────╮
 * │                                NUMBER ENTRY MODE                      │
 * ╞═════╤═════╤═════╤═════╤═════╤═════╦═════╤═════╤═════╤═════╤═════╤═════╡
 * │     │     │  7  │  8  │  9  │     ║     │     │     │     │     │     │
 * ╞═════╪═════╪═════╪═════╪═════╪═════╬═════╪═════╪═════╪═════╪═════╪═════╡
 * │     │  0  │  4  │  5  │  6  │     ║     │     │     │     │     │     │
 * ╞═════╪═════╪═════╪═════╪═════╪═════╬═════╪═════╪═════╪═════╪═════╪═════╡
 * │     │     │  1  │  2  │  3  │     ║     │     │     │     │     │     │
 * ╞═════╪═════╪═════╪═════╪═════╪═════╬═════╪═════╪═════╪═════╪═════╪═════╡
 * │     │     │     │     │     │     ║     │     │     │     │     │     │
 * ╰─────┴─────┴─────┴─────┴─────┴─────┺─────┴─────┴─────┴─────┴─────┴─────╯
 *
 * Legend: Numpad layout on left hand, auto-deactivates on non-numeric input
 */

/* ╔════════════════════════════════════════════════════════════════════════════╗
 * ║  FUNCTION LAYER - MEDIA & DESKTOP CONTROL                                  ║
 * ╠════════════════════════════════════════════════════════════════════════════╣
 * ║  Media controls with desktop management integration                        ║
 * ║  Desktop switching, window management, and app pinning                     ║
 * ║  Function keys with homerow mod integration for advanced workflows         ║
 * ╚════════════════════════════════════════════════════════════════════════════╝
 *
 * ╭────────────────────────────────────────────────────────────────────────────╮
 * │                           FUNCTION & MEDIA CONTROL                         │
 * ╞═════╤══════╤══════╤═════╤═════╤═════╦═════╤══════╤══════╤══════╤═════╤═════╡
 * │     │ F12  │  F7  │  F8 │  F9 │     ║     │Prev  │Vol+  │Next  │     │     │
 * ╞═════╪══════╪══════╪═════╪═════╪═════╬═════╪══════╪══════╪══════╪═════╪═════╡
 * │     │F11Cmd│F4Alt │F5Sft│F6Ctl│     ║     │Desk< │Vol-S │Desk> │     │     │
 * ╞═════╪══════╪══════╪═════╪═════╪═════╬═════╪══════╪══════╪══════╪═════╪═════╡
 * │     │ F10  │  F1  │  F2 │  F3 │     ║     │PinApp│PinWin│DskMgr│     │     │
 * ╞═════╪══════╪══════╪═════╪═════╪═════╬═════╪══════╪══════╪══════╪═════╪═════╡
 * │     │      │      │     │     │     ║     │Play  │      │      │     │     │
 * ╰─────┴──────┴──────┴─────┴─────┴─────┺─────┴──────┴──────┴──────┴─────┴─────╯
 *
 * Legend: Prev/Next=Media Track, Vol+/Vol-=Volume, Desk</>=Desktop Switch
 *         PinApp=Pin Application, PinWin=Pin Window, DskMgr=Desktop Manager
 */

/* ╔═══════════════════════════════════════════════════════════════════════╗
 * ║  SYSTEM LAYER - FIRMWARE & RGB CONTROL                                ║
 * ╠═══════════════════════════════════════════════════════════════════════╣
 * ║  Complete RGB Matrix control with audio system management             ║
 * ║  Bootloader access, EEPROM clearing, and debug toggles                ║
 * ║  Audio and MIDI system controls for creative workflows                ║
 * ╚═══════════════════════════════════════════════════════════════════════╝
 *
 * ╭───────────────────────────────────────────────────────────────────────╮
 * │                            SYSTEM & RGB CONTROL                       │
 * ╞═════╤═════╤═════╤═════╤═════╤═════╦═════╤═════╤═════╤═════╤═════╤═════╡
 * │ DEF │AudON│AudOF│     │     │RGBTg║     │RGB> │ H+  │ S+  │ B+  │     │
 * ╞═════╪═════╪═════╪═════╪═════╪═════╬═════╪═════╪═════╪═════╪═════╪═════╡
 * │     │MusON│MusOF│     │     │BOOT ║BOOT │RGB< │ H-  │ S-  │ B-  │     │
 * ╞═════╪═════╪═════╪═════╪═════╪═════╬═════╪═════╪═════╪═════╪═════╪═════╡
 * │MIDI │MidON│MidOF│     │     │EECLR║EECLR│     │     │     │     │     │
 * ╞═════╪═════╪═════╪═════╪═════╪═════╬═════╪═════╪═════╪═════╪═════╪═════╡
 * │GAME │Aud< │Aud> │     │     │     ║     │     │     │     │     │Debug│
 * ╰─────┴─────┴─────┴─────┴─────┴─────┺─────┴─────┴─────┴─────┴─────┴─────╯
 *
 * Legend: RGB>/<=RGB Mode Forward/Back, H/S/B=Hue/Saturation/Brightness
 *         BOOT=Bootloader, EECLR=EEPROM Clear, Debug=Debug Toggle
 */

/* ╔═══════════════════════════════════════════════════════════════════════╗
 * ║  NAVIGATION LAYER - CURSOR & WINDOW MANAGEMENT                        ║
 * ╠═══════════════════════════════════════════════════════════════════════╣
 * ║  Arrow keys, page navigation, and smart text editing controls         ║
 * ║  One-shot modifiers for advanced key combinations                     ║
 * ║  Window switching and application navigation shortcuts                ║
 * ╚═══════════════════════════════════════════════════════════════════════╝
 *
 * ╭───────────────────────────────────────────────────────────────────────╮
 * │                           NAVIGATION & EDITING                        │
 * ╞═════╤═════╤═════╤═════╤═════╤═════╦═════╤═════╤═════╤═════╤═════╤═════╡
 * │     │AltF4│     │S-Tab│A-Tab│     ║PgUp │SmBsp│ Up  │SmDel│     │     │
 * ╞═════╪═════╪═════╪═════╪═════╪═════╬═════╪═════╪═════╪═════╪═════╪═════╡
 * │     │OSCmd│OSAlt│OSSft│OSCtl│     ║PgDn │Left │Down │Right│Enter│     │
 * ╞═════╪═════╪═════╪═════╪═════╪═════╬═════╪═════╪═════╪═════╪═════╪═════╡
 * │     │     │     │     │     │     ║Ins  │Tab  │     │     │     │     │
 * ╞═════╪═════╪═════╪═════╪═════╪═════╬═════╪═════╪═════╪═════╪═════╪═════╡
 * │     │     │     │     │     │     ║Cncl │     │     │     │     │     │
 * ╰─────┴─────┴─────┴─────┴─────┴─────┺─────┴─────┴─────┴─────┴─────┴─────╯
 *
 * Legend: OS=One-Shot Modifier, SmBsp/SmDel=Smart Backspace/Delete (word-aware)
 *         S-Tab=Shift+Tab, A-Tab=Alt+Tab for window switching
 */

/* ╔═══════════════════════════════════════════════════════════════════════╗
 * ║  MIDI LAYER - MUSICAL KEYBOARD INTERFACE                              ║
 * ╠═══════════════════════════════════════════════════════════════════════╣
 * ║  Two-octave piano layout with musical controls                        ║
 * ║  Velocity, transpose, sustain, and octave controls                    ║
 * ║  RGB lighting shows creative musical mode is active                   ║
 * ╚═══════════════════════════════════════════════════════════════════════╝
 *
 * ╭───────────────────────────────────────────────────────────────────────╮
 * │                         MUSICAL KEYBOARD MODE                         │
 * ╞═════╤═════╤═════╤═════╤═════╤═════╦═════╤═════╤═════╤═════╤═════╤═════╡
 * │Oct-2│Oct-1│Oct+1│Oct+2│Vel- │Vel+ │Trns-│Trns+│Sust │Soft │AllOf│EXIT │
 * ╞═════╪═════╪═════╪═════╪═════╪═════╬═════╪═════╪═════╪═════╪═════╪═════╡
 * │ C#  │ D#  │     │ F#  │ G#  │ A#  ║     │ C#  │ D#  │     │ F#  │ G#  │
 * ╞═════╪═════╪═════╪═════╪═════╪═════╬═════╪═════╪═════╪═════╪═════╪═════╡
 * │ C   │ D   │ E   │ F   │ G   │ A   ║ B   │ C   │ D   │ E   │ F   │ G   │
 * ╞═════╪═════╪═════╪═════╪═════╪═════╬═════╪═════╪═════╪═════╪═════╪═════╡
 * │EXIT │     │     │     │     │     ║     │     │     │     │     │     │
 * ╰─────┴─────┴─────┴─────┴─────┴─────┺─────┴─────┴─────┴─────┴─────┴─────╯
 *
 * Legend: Natural notes C-G, Sharp notes C#/D#/F#/G#/A#
 *         Oct=Octave shift, Vel=Velocity, Trns=Transpose, Sust=Sustain pedal
 */
