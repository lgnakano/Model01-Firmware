/* -*- mode: c++ -*-
 * Basic -- A very basic Kaleidoscope example
 * Copyright (C) 2018  Keyboard.io, Inc.
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Kaleidoscope.h"

#include <Kaleidoscope-OneShot.h>

// Support for macros
#include "Kaleidoscope-Macros.h"

#include <Kaleidoscope-TopsyTurvy.h>

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Show status of mod buttons
#include <Kaleidoscope-LED-ActiveModColor.h>

// Show active layer
#include <Kaleidoscope-LED-ActiveLayerColor.h>

//#include "Kaleidoscope-LEDEffect-FunctionalColor.h"

// Support for magic combos (key chords that trigger an action)
#include "Kaleidoscope-MagicCombo.h"

// Support for USB quirks, like changing the key state report protocol
#include "Kaleidoscope-USB-Quirks.h"

// Support for keys that move the mouse
#include "Kaleidoscope-MouseKeys.h"

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif

enum { PRIMARY, NUMPAD,  FUNCTION}; // layers

enum { MACRO_VERSION_INFO,
       OSMALTCTRL,
       MACRO_USER,
       MACRO_FCDOWN,
       MACRO_FCUP,
       MACRO_ANY
     };


/* *INDENT-OFF* */
KEYMAPS(
  [PRIMARY] = KEYMAP_STACKED
  (___,       TOPSY(1),      TOPSY(2),  TOPSY(3),   TOPSY(4), TOPSY(5), Key_LEDEffectNext,
   Key_Backtick, Key_Quote,     Key_Comma, Key_Period, Key_P, Key_Y, Key_Tab,
   Key_PageUp,   Key_A,         Key_O,     Key_E,      Key_U, Key_I,
   Key_PageDown, Key_Semicolon, Key_Q,     Key_J,      Key_K, Key_X, M(MACRO_USER),
   OSM(RightControl), Key_Backspace, OSM(LeftShift), OSM(LeftGui), 
   OSL(NUMPAD),

   Key_Escape,   TOPSY(6), TOPSY(7), TOPSY(8), TOPSY(9), TOPSY(0), LockLayer(NUMPAD),
   Key_Enter,      Key_F, Key_G, Key_C, Key_R, Key_L, Key_Slash,
                   Key_D, Key_H, Key_T, Key_N, Key_S, Key_Minus,
   OSM(RightGui),   Key_B, Key_M, Key_W, Key_V, Key_Z, Key_Equals,
   OSM(LeftAlt), OSM(LeftShift), Key_Spacebar, OSM(RightControl),
   OSL(FUNCTION)),
   
  [NUMPAD] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,

   M(MACRO_VERSION_INFO),  ___, Key_7, Key_8,   Key_9,        Key_KeypadSubtract, ___,
   ___,                    ___, Key_4, Key_5,   Key_6,        Key_KeypadAdd,      ___,
                           ___, Key_1, Key_2,   Key_3,        Key_Equals,         ___,
   ___,                    ___, Key_0, Key_Period, Key_KeypadMultiply, Key_KeypadDivide,   Key_Enter,
   ___, ___, ___, ___,
   ___),

  [FUNCTION] =  KEYMAP_STACKED
  (___,      Key_F1,           Key_F2,      Key_F3,     Key_F4,        Key_F5,           Key_CapsLock,
   Key_Tab,  Key_mouseScrollUp,  Key_mouseUp, Key_mouseScrollDn,        Key_mouseBtnL, Key_mouseWarpEnd, Key_mouseWarpNE,
   Key_Home, Key_mouseL,       Key_mouseDn, Key_mouseR, Key_mouseBtnR, Key_mouseWarpNW,
   Key_End,  Key_PrintScreen,  Key_Insert,  ___,        Key_mouseBtnM, Key_mouseWarpSW,  Key_mouseWarpSE,
   ___, Key_Delete, ___, ___,
   ___,

   Consumer_ScanPreviousTrack, Key_F6,                 Key_F7,                   Key_F8,                   Key_F9,          Key_F10,          Key_F11,
   ___,    Consumer_ScanNextTrack, Key_LeftCurlyBracket,     Key_RightCurlyBracket,    Key_LeftBracket, Key_RightBracket, Key_F12,
                               Key_LeftArrow,          Key_DownArrow,            Key_UpArrow,              Key_RightArrow,  M(MACRO_FCDOWN),    M(MACRO_FCUP),
   Key_PcApplication,          Consumer_Mute,          Consumer_VolumeDecrement, Consumer_VolumeIncrement, ___,             Key_Backslash,    Key_Pipe,
   ___, ___, Consumer_PlaySlashPause, ___,
   ___)
//  [0] = KEYMAP_STACKED
//  (
//   Key_NoKey,    Key_1, Key_2, Key_3, Key_4, Key_5, Key_NoKey,
//   Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab,
//   Key_PageUp,   Key_A, Key_S, Key_D, Key_F, Key_G,
//   Key_PageDown, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,
//
//   Key_LeftControl, Key_Backspace, Key_LeftGui, Key_LeftShift,
//   Key_NoKey,
//
//   Key_skip,  Key_6, Key_7, Key_8,     Key_9,      Key_0,         Key_skip,
//   Key_Enter, Key_Y, Key_U, Key_I,     Key_O,      Key_P,         Key_Equals,
//              Key_H, Key_J, Key_K,     Key_L,      Key_Semicolon, Key_Quote,
//   Key_skip,  Key_N, Key_M, Key_Comma, Key_Period, Key_Slash,     Key_Minus,
//
//   Key_RightShift, Key_RightAlt, Key_Spacebar, Key_RightControl,
//   Key_NoKey
//  ),
)
/* *INDENT-ON* */


/** versionInfoMacro handles the 'firmware version info' macro
 *  When a key bound to the macro is pressed, this macro
 *  prints out the firmware build information as virtual keystrokes
 */

static void versionInfoMacro(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
    Macros.type(PSTR(BUILD_INFORMATION));
  }
}

static void pass(uint8_t keyState){
    Macros.type(PSTR("<cby.p21!"));
}

static void pass2(uint8_t keyState) {
  Macros.type(PSTR("Agygmb21!"));
}

static void pass3(uint8_t keyState){
  Macros.type(PSTR("Ogmm.p21!"));
}

static void user(uint8_t keyState){
  if(keyToggledOn(keyState)){
    Macros.type(PSTR("ln36873"));
  }
}

/** anyKeyMacro is used to provide the functionality of the 'Any' key.
 *
 * When the 'any key' macro is toggled on, a random alphanumeric key is
 * selected. While the key is held, the function generates a synthetic
 * keypress event repeating that randomly selected key.
 *
 */

/* static void anyKeyMacro(uint8_t keyState) {
  static Key lastKey;
  if (keyToggledOn(keyState))
    lastKey.keyCode = Key_A.keyCode + (uint8_t)(millis() % 36);

  if (keyIsPressed(keyState))
    kaleidoscope::hid::pressKey(lastKey);
} */


/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

 */

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {

  case MACRO_VERSION_INFO:
    versionInfoMacro(keyState);
    break;
  case MACRO_USER:
   user(keyState);
    break;
  case MACRO_FCUP:
//    kaleidoscope::LEDFunctionalColor::FCPlugin::brightnessUp(keyState);
    break;
   
  case MACRO_FCDOWN:
//    kaleidoscope::LEDFunctionalColor::FCPlugin::brightnessDown(keyState);
    break;
  }
  return MACRO_NONE;
}

/** A tiny wrapper, to be used by MagicCombo.
 * This simply toggles the keyboard protocol via USBQuirks, and wraps it within
 * a function with an unused argument, to match what MagicCombo expects.
 */
static void toggleKeyboardProtocol(uint8_t combo_index) {
  USBQuirks.toggleKeyboardProtocol();
}


USE_MAGIC_COMBOS({.action = toggleKeyboardProtocol,
                  // Left Fn + Esc + Shift
                  .keys = { R3C6, R2C6, R3C7 }
                 }
          ,
                {.action = pass,
                 // both function buttons and the prog key together
                 .keys = {R3C6, R3C9, R0C0}
                 }
         ,
                  {.action = pass2,
                  // both function buttons and the num key together
                  .keys = {R3C6, R3C9, R0C15}
         }
                 /*
                 ,
                 {.action = pass3,
                 // both function buttons and the any key together
                 .keys = {R3C6, R3C9,R0C9}
                 } 
                  */
                 );

// First, tell Kaleidoscope which plugins you want to use.
// The order can be important. For example, LED effects are
// added in the order they're listed here.
KALEIDOSCOPE_INIT_PLUGINS(
  // The EEPROMSettings & EEPROMKeymap plugins make it possible to have an
  // editable keymap in EEPROM.
//  EEPROMSettings,
//  EEPROMKeymap,

  // Focus allows bi-directional communication with the host, and is the
  // interface through which the keymap in EEPROM can be edited.
  //  Focus,
  // FocusSettingsCommand adds a few Focus commands, intended to aid in changing some settings of the keyboard, such as the default layer (via the `settings.defaultLayer` command)
  //  FocusSettingsCommand,

  // FocusEEPROMCommand adds a set of Focus commands, which are very helpful in
  // both debugging, and in backing up one's EEPROM contents.
  // FocusEEPROMCommand,

  // The boot greeting effect pulses the LED button for 10 seconds after the keyboard is first connected
  // BootGreetingEffect,

  // The hardware test mode, which can be invoked by tapping Prog, LED and the left Fn button at the same time.
  // TestMode,

  // LEDControl provides support for other LED modes
  LEDControl,

  // We start with the LED effect that turns off all the LEDs.
  // LEDOff,

  // IdleLayers,

  // The macros plugin adds support for macros
  Macros,
  //MacrosOnTheFly,


  // initialize oneshot
  OneShot,
  // initialize topsyturvy
  TopsyTurvy,

  // primaryLayerHighlighter,
  //secondaryLayerHighlighter,
  // functionLayerHighlighter,
  // numpadLayerHighlighter,
  // The rainbow effect changes the color of all of the keyboard's keys at the same time
  // running through all the colors of the rainbow.
  // LEDRainbowEffect,

  // The rainbow wave effect lights up your keyboard with all the colors of a rainbow
  // and slowly moves the rainbow across your keyboard
  // LEDRainbowWaveEffect,

  // The chase effect follows the adventure of a blue pixel which chases a red pixel across
  // your keyboard. Spoiler: the blue pixel never catches the red pixel
  // LEDChaseEffect,

  // These static effects turn your keyboard's LEDs a variety of colors
  // solidRed, solidOrange, solidYellow, 
  // solidGreen, 
  // solidBlue, solidIndigo, solidViolet,

  // The breathe effect slowly pulses all of the LEDs on your keyboard
  // LEDBreatheEffect,

  // The AlphaSquare effect prints each character you type, using your
  // keyboard's LEDs as a display
  // AlphaSquareEffect,


  LEDActiveLayerColorEffect,

  // The stalker effect lights up the keys you've pressed recently
  //StalkerEffect,

  // The numpad plugin is responsible for lighting up the 'numpad' mode
  // with a custom LED effect
  //NumPad,

  // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
  MouseKeys,
  // funColor1,
  
  
  // The HostPowerManagement plugin allows us to turn LEDs off when then host
  // goes to sleep, and resume them when it wakes up.
  // HostPowerManagement,

  // The MagicCombo plugin lets you use key combinations to trigger custom
  // actions - a bit like Macros, but triggered by pressing multiple keys at the
  // same time.
  MagicCombo,

  // The USBQuirks plugin lets you do some things with USB that we aren't
  // comfortable - or able - to do automatically, but can be useful
  // nevertheless. Such as toggling the key report protocol between Boot (used
  // by BIOSes) and Report (NKRO).
  USBQuirks,
  ActiveModColorEffect
);

void setup() {
  Kaleidoscope.setup();
  static const cRGB layerColormap[] PROGMEM = {
     CRGB(0, 128, 0),    // Primary
     //CRGB(128, 107, 0),  // Secondary
     CRGB(128, 0, 0),  // Numpad
     CRGB(0, 0, 128)     // Function
   };
  LEDActiveLayerColorEffect.setColormap(layerColormap);
  ActiveModColorEffect.highlight_color = CRGB(0x00, 0xff, 0x7f);
  ActiveModColorEffect.sticky_color = CRGB(0xff, 0x00, 0x00);
}

void loop() {
  Kaleidoscope.loop();
}
