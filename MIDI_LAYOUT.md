# 🎹 Enhanced MIDI Layer - Furnace Tracker Optimized

> **Advanced MIDI implementation for Planck keyboard with Furnace Tracker integration**

## 📋 Table of Contents

- [Overview](#overview)
- [Layout Diagram](#layout-diagram)
- [Feature Highlights](#feature-highlights)
- [Control Zones](#control-zones)
- [Velocity & Dynamics](#velocity--dynamics)
- [Furnace Integration](#furnace-integration)
- [Activation & Usage](#activation--usage)
- [Advanced Features](#advanced-features)
- [Troubleshooting](#troubleshooting)
- [Technical Implementation](#technical-implementation)

## Overview

The Enhanced MIDI Layer transforms your Planck keyboard into a professional MIDI controller optimized for Furnace Tracker workflow. It provides two full octaves of piano keys, real-time parameter control, and advanced pattern editing capabilities.

### Key Features

- 🎹 **Two-octave piano layout** with proper black/white key positioning
- 🎛️ **Real-time controls** for instruments, channels, and effects
- 🎵 **Pattern recording** with note-off and release insertion
- 🔊 **Audio confirmation** for mode changes
- 🚨 **PANIC mode** for emergency note-off

## Layout Diagram

```
┌─────────────┬─────────────┬─────────────┬─────────────┬─────────────┬─────────────┬─────────────┬─────────────┬─────────────┬─────────────┬─────────────┬─────────────┐
│    PANIC    │   Oct-2     │   Oct-1     │   Oct+1     │   Oct+2     │   Record    │  Play/Pause │  Inst Prev  │  Inst Next  │  Chan Prev  │  Chan Next  │    EXIT     │
│  All Notes  │             │             │             │             │   Toggle    │             │             │             │             │             │             │
│     Off     │             │             │             │             │             │             │             │             │             │             │             │
├─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┤
│    Vel 1    │     C#      │     D#      │   Arpeggio  │     F#      │     G#      │     A#      │     C#      │     D#      │   Vibrato   │     F#      │    Vel 7    │
│   (ppp)     │             │             │   Effect    │             │             │             │  (Oct +1)   │  (Oct +1)   │   Effect    │  (Oct +1)   │    (ff)     │
├─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┤
│  Sustain    │      C      │      D      │      E      │      F      │      G      │      A      │      B      │      C      │      D      │      E      │    Chord    │
│   Toggle    │             │             │             │             │             │             │             │  (Oct +1)   │  (Oct +1)   │  (Oct +1)   │    Mode     │
├─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┤
│ Oct Reset   │  Effect:    │  Effect:    │  Note Off   │ Note Release│  Transpose  │  Transpose  │  Velocity   │  Velocity   │  Pattern    │  Pattern    │ MIDI Learn  │
│     (0)     │   Volume    │    Pan      │             │             │    Down     │     Up      │    Down     │     Up      │   Previous  │    Next     │             │
└─────────────┴─────────────┴─────────────┴─────────────┴─────────────┴─────────────┴─────────────┴─────────────┴─────────────┴─────────────┴─────────────┴─────────────┘
```

## Feature Highlights

### 🎹 Advanced Piano Interface

- **Two full octaves** (C to C) with logical black/white key arrangement
- **Octave shifting** from -2 to +2 (5 octave range total)
- **Real-time transpose** (±12 semitones)
- **Velocity-sensitive** input with 7 dynamic levels

### 🎛️ Real-Time Control

- **Instrument switching** with prev/next navigation
- **Channel focus** for multi-channel editing
- **Transport controls** (play/pause, record toggle)
- **Pattern navigation** between sequences

### 🎵 Furnace-Specific Features

- **Pattern recording mode** with automatic note entry
- **Note-off/release** insertion for precise editing
- **Effect parameter control** (volume, pan, arpeggio, vibrato)
- **Sustain pedal** simulation
- **Chord mode** for harmonic input

## Control Zones

### Top Row - System & Transport

```
PANIC | Oct-2 | Oct-1 | Oct+1 | Oct+2 | Record | Play/Pause | Inst± | Chan± | EXIT
```

- **PANIC**: Emergency all-notes-off + state reset
- **Octave controls**: Shift playing range ±2 octaves
- **Transport**: Record toggle and playback control
- **Navigation**: Instrument and channel switching
- **EXIT**: Single exit point (top-right corner)

### Middle Rows - Piano Interface

```
Vel1-7 |  Black Keys (C# D# F# G# A# + Effects)  | Vel7
Sustain|  White Keys (C D E F G A B C D E)      | Chord
```

- **Velocity controls**: Set dynamic level (ppp to ff)
- **Piano keys**: Two-octave chromatic range
- **Effects**: Arpeggio and vibrato on black key positions
- **Modes**: Sustain and chord input toggles

### Bottom Row - Pattern & Effects

```
Oct Reset | Vol | Pan | Note- | Note= | Trans- | Trans+ | Vel± | Pattern± | Learn
```

- **Effects**: Volume and pan parameter control
- **Note editing**: Insert note-off and note-release
- **Transpose**: Pitch shifting controls
- **Velocity**: Fine adjustment (±8 steps)
- **Pattern**: Navigate between sequences
- **Learn**: MIDI learn mode for custom mappings

## Velocity & Dynamics

The MIDI layer provides seven velocity levels corresponding to musical dynamics:

| Level     | Velocity | Dynamic | Description                             |
| --------- | -------- | ------- | --------------------------------------- |
| Vel 1     | 32       | ppp     | Pianississimo - Very very soft          |
| Vel 2     | 48       | pp      | Pianissimo - Very soft                  |
| Vel 3     | 64       | p       | Piano - Soft                            |
| Vel 4     | 80       | mp      | Mezzo-piano - Medium soft               |
| **Vel 5** | **96**   | **mf**  | **Mezzo-forte - Medium loud (DEFAULT)** |
| Vel 6     | 112      | f       | Forte - Loud                            |
| Vel 7     | 127      | ff      | Fortissimo - Very loud                  |

### Velocity Controls

- **Preset levels**: Vel 1-7 buttons for instant dynamic changes
- **Fine adjustment**: Vel+/Vel- for ±8 step increments
- **Global application**: All notes use current velocity setting

## Furnace Integration

### 🎯 Pattern Recording Workflow

1. **Enable recording**: Press "Record" to enter pattern recording mode
2. **Play notes**: Automatically entered into current pattern
3. **Precise editing**: Use Note Off/Release for exact timing
4. **Navigate**: Pattern Prev/Next between sequences
5. **Disable**: Press "Record" again to exit mode

### 🎹 Live Performance

1. **Select instrument**: Use Inst Prev/Next for real-time switching
2. **Set dynamics**: Choose appropriate velocity for instrument type
3. **Range control**: Octave shifts for full note access
4. **Sustain mode**: Toggle for sustained instruments (strings, pads)

### 🎵 Multi-Channel Composing

1. **Channel focus**: Chan Prev/Next to target different tracks
2. **Independent setup**: Each channel supports different instruments
3. **Focused recording**: Record mode respects active channel### 🎛️ Real-Time Effect Control

4. **Effect selection**: Choose effect type (Vol, Pan, Arpeggio, Vibrato)
5. **Parameter control**: Current velocity sets effect intensity
6. **Live manipulation**: Real-time changes during playback
7. **Transpose effects**: Pitch modulation via transpose controls

## Activation & Usage

### 🚀 Quick Start

1. **Access MIDI layer**:

   - Hold `NUM` + `SYM` (activates SYSTEM layer)
   - Press `MIDI` button (toggles MIDI layer)
   - Listen for confirmation sound (ascending arpeggio)

2. **Basic playing**:
   - **White keys** (row 3): Natural notes C D E F G A B C D E
   - **Black keys** (row 2): Sharps/flats C# D# F# G# A#
   - **Two octaves** available immediately
   - **Octave controls** for extended range

### 🎚️ Advanced Operation

1. **Set velocity**: Choose Vel1-Vel7 before playing
2. **Enable features**: Toggle Record, Sustain, or Chord modes
3. **Effect control**: Use effect buttons for real-time modulation
4. **Emergency**: PANIC button for stuck notes or reset

### 🔧 Configuration

- **MIDI Learn**: Map custom Control Changes to Furnace
- **Furnace settings**: Configure MIDI input behavior
- **Audio feedback**: Sound confirmation for mode changes

## Advanced Features

### 🔊 Audio Feedback

- **Layer entry**: Ascending C-E-G arpeggio
- **Layer exit**: Descending G-E-C arpeggio
- **Mode changes**: Confirmation tones
- **Octave shifts**: Reference tone at new octave level

### 📡 MIDI Implementation

- **Program Change**: Instrument switching commands
- **Control Change**: Effect parameter automation
- **Note Input**: Direct pattern recording integration
- **Transport**: Play/Pause/Record control
- **Channel Focus**: Track selection commands## Troubleshooting

### ❌ Notes Not Playing

**Symptoms**: No sound when pressing piano keys

**Solutions**:

- Verify Furnace MIDI input device settings
- Confirm MIDI layer is active
- Use PANIC button to reset all MIDI state
- Ensure Furnace application has focus
- Check MIDI cable/USB connection

### ❌ Wrong Octave Range

**Symptoms**: Notes too high/low or out of range

**Solutions**:

- Check current octave offset (should be -2 to +2)
- Use octave controls to adjust range
- Reset to center: Press Oct Reset button
- Verify transpose settings (use Trans Reset if available)

### ❌ Effects Not Responding

**Symptoms**: Effect controls don't change sound

**Solutions**:

- Ensure Furnace is in Edit mode (not Play mode)
- Verify effect parameter values in Furnace
- Check MIDI CC mapping in Furnace preferences
- Some effects require specific Furnace chip/instrument setup
- Confirm current channel has appropriate instrument loaded

### ❌ Recording Issues

**Symptoms**: Notes not entering pattern, or wrong timing

**Solutions**:

- Verify Record mode is enabled
- Check current pattern/channel focus
- Ensure Furnace pattern editor is visible
- Verify note entry settings in Furnace preferences
- Try manual note entry to test Furnace setup

## Technical Implementation

### 🔧 Code Architecture

- **Header file**: `midi_enhanced.h` - Interface definitions and constants
- **Implementation**: `midi_enhanced.c` - MIDI logic and Furnace integration
- **State management**: Global MIDI state tracking with automatic cleanup
- **QMK integration**: Full compatibility with QMK MIDI subsystem

### 📊 MIDI Specification

- **Protocol**: MIDI 1.0 compliant with Furnace extensions
- **Channels**: Support for 16 MIDI channels
- **Velocity range**: 1-127 with 7 preset levels
- **Note range**: Full 128-note MIDI range with octave shifting
- **Control Changes**: Custom CC mapping for Furnace-specific features

### ⚡ Performance Features

- **Real-time processing**: Zero-latency note input
- **State persistence**: Settings maintained across layer switches
- **Memory efficient**: Minimal RAM usage with optimized structures
- **Interrupt safe**: Proper handling of concurrent MIDI events

---

## 📄 Related Documentation

- **[Main README](README.md)** - Complete keyboard layout overview
- **[Agent Guidelines](AGENTS.md)** - Development and build instructions
- **[Layer Layouts](keymap/layer_layouts.h)** - Visual layout diagrams
- **[Custom Keycodes](keymap/custom_keycodes.h)** - Keycode definitions

---

_Generated for Planck Rev7 Enhanced MIDI Layout - Optimized for Furnace Tracker workflow_
