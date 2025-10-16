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

/* ╔═══════════════════════════════════════════════════════════════════════════════╗
 * ║  MIDI LAYER - TRACKER POWER USER LAYOUT                                       ║
 * ╠═══════════════════════════════════════════════════════════════════════════════╣
 * ║  Optimized for tracker workflow (Furnace, Renoise, etc.)                      ║
 * ║  Chromatic octave + comprehensive tracker controls                            ║
 * ║  Quick access to transport, effects, and pattern navigation                   ║
 * ║  Balanced layout for fast note entry and powerful editing features            ║
 * ╚═══════════════════════════════════════════════════════════════════════════════╝
 *
 * ╭────────────────────────────────────────────────────────────────────────────────╮
 * │                         TRACKER POWER USER MODE                                │
 * ╞══════╤══════╤══════╤══════╤══════╤══════╦══════╤══════╤══════╤══════╤══════╤══════╡
 * │Panic │ Play │ Stop │ Rec  │ Pat- │ Pat+ ║Oct-2 │Oct-1 │Oct+1 │Oct+2 │OctRst│ Exit │
 * │Reset │Pause │      │ Tog  │ Prev │ Next ║      │      │      │      │  0   │      │
 * ╞══════╪══════╪══════╪══════╪══════╪══════╬══════╪══════╪══════╪══════╪══════╪══════╡
 * │Vol 1 │  C#  │  D#  │      │  F#  │  G#  ║  A#  │      │  C#  │Inst- │Inst+ │Vol 7 │
 * │ ppp  │      │      │      │      │      ║      │      │      │ Prev │ Next │  ff  │
 * ╞══════╪══════╪══════╪══════╪══════╪══════╬══════╪══════╪══════╪══════╪══════╪══════╡
 * │Sust  │  C   │  D   │  E   │  F   │  G   ║  A   │  B   │  C   │ ---  │ ===  │Chord │
 * │ Tog  │      │      │      │      │      ║      │      │      │ Off  │ Rel  │ Tog  │
 * ╞══════╪══════╪══════╪══════╪══════╪══════╬══════╪══════╪══════╪══════╪══════╪══════╡
 * │Chan- │Chan+ │ 0xy  │ 1xx  │ 2xx  │ 4xy  ║ 7xx  │ Cxx  │Trns- │Trns+ │ Vol- │ Vol+ │
 * │ Prev │ Next │Arpeg │Pitch │ Pan  │Vibr  ║ Trem │ Vol  │ Down │  Up  │ Down │  Up  │
 * ╰──────┴──────┴──────┴──────┴──────┴──────┺──────┴──────┴──────┴──────┴──────┴──────╯
 *
 * Legend:
 *   Notes: Chromatic octave (C C# D D# E F F# G G# A A# B C) with piano-style layout
 *   ---/Off = Note Off, ===/Rel = Note Release (tracker-specific)
 *   Oct±1/±2 = Octave shift, OctRst = Reset to octave 0
 *   Vol 1-7 = Velocity presets (ppp to ff), Vol±/Trns± = Fine adjustments
 *   Inst±/Chan± = Navigate instruments and channels
 *   Pat± = Pattern navigation, Rec Tog = Toggle pattern recording
 *   0xy-Cxx = Common tracker effect shortcuts (Arpeg, Pitch, Vibrato, etc.)
 *   Sust/Chord Tog = Toggle sustain pedal and chord mode
 *   Panic = All notes off + MIDI reset
 */
