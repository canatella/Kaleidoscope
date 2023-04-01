/* -*- mode: c++; -*-
 * Quetch -- A very basic Kaleidoscope example for the DM Quetch keyboard
 * Copyright (C) 2018  Keyboard.io, Inc
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTabILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "Kaleidoscope.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-Qukeys.h"
#include "Kaleidoscope-CharShift.h"
#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope-LayerFocus.h"
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-HostOS.h"
#include "Kaleidoscope-Unicode.h"
// BEPO mappings

// Row 1
#define Bepo_Dollar         Key_Backtick  // $
#define Bepo_DoubleQuote    Key_1         // "
#define Bepo_LeftGuillemet  Key_2         // «
#define Bepo_RightGuillemet Key_3         // »
#define Bepo_LeftParen      Key_4         // (
#define Bepo_RightParen     Key_5         // )
#define Bepo_At             Key_6         // @
#define Bepo_Plus           Key_7         // +
#define Bepo_Minus          Key_8         // -
#define Bepo_Slash          Key_9         // /
#define Bepo_Asterisk       Key_0         // *
#define Bepo_Equal          Key_Minus     // =
#define Bepo_Percent        Key_Equals    // %
// Row 2
#define Bepo_B              Key_Q         // B
#define Bepo_EAcute         Key_W         // É
#define Bepo_P              Key_E         // P
#define Bepo_O              Key_R         // O
#define Bepo_EGrave         Key_T         // È
#define Bepo_DeadCirc       Key_Y         // ^ (dead)
#define Bepo_V              Key_U         // V
#define Bepo_D              Key_I         // D
#define Bepo_L              Key_O         // L
#define Bepo_J              Key_P         // J
#define Bepo_Z              Key_LeftBracket  // Z
#define Bepo_W              Key_RightBracket // W
// Row 3
#define Bepo_A              Key_A         // A
#define Bepo_U              Key_S         // U
#define Bepo_I              Key_D         // I
#define Bepo_E              Key_F         // E
#define Bepo_Comma          Key_G         // ,
#define Bepo_C              Key_H         // C
#define Bepo_T              Key_J         // T
#define Bepo_S              Key_K         // S
#define Bepo_R              Key_L         // R
#define Bepo_N              Key_Semicolon // N
#define Bepo_M              Key_Quote     // M
#define Bepo_CCedilla       Key_Backslash // Ç
// Row 4
#define Bepo_ECirc          Key_NonUsBackslashAndPipe // Ê
#define Bepo_AGrave         Key_Z         // À
#define Bepo_Y              Key_X         // Y
#define Bepo_X              Key_C         // X
#define Bepo_Period         Key_V         // .
#define Bepo_K              Key_B         // K
#define Bepo_Quote          Key_N         // '
#define Bepo_Q              Key_M         // Q
#define Bepo_G              Key_Comma     // G
#define Bepo_H              Key_Period    // H
#define Bepo_F              Key_Slash     // F

#define Bepo_Spacebar       Key_Spacebar

#define Bepo_Hash LSHIFT(Bepo_Dollar)          // #
#define Bepo_1    LSHIFT(Bepo_DoubleQuote)     // 1
#define Bepo_2    LSHIFT(Bepo_LeftGuillemet)   // 2
#define Bepo_3    LSHIFT(Bepo_RightGuillemet)  // 3
#define Bepo_4    LSHIFT(Bepo_LeftParen)       // 4
#define Bepo_5    LSHIFT(Bepo_RightParen)      // 5
#define Bepo_6    LSHIFT(Bepo_At)              // 6
#define Bepo_7    LSHIFT(Bepo_Plus)            // 7
#define Bepo_8    LSHIFT(Bepo_Minus)           // 8
#define Bepo_9    LSHIFT(Bepo_Slash)           // 9
#define Bepo_0    LSHIFT(Bepo_Asterisk)        // 0
#define Bepo_Degr LSHIFT(Bepo_Equal)           // °
#define Bepo_Backtick LSHIFT(Bepo_Percent)     // `
// Row 2
#define Bepo_ExclamationPoint LSHIFT(Bepo_DeadCirc) // !
// Row 3
#define Bepo_Semicolon LSHIFT(Bepo_Comma)      // ;
// Row 4
#define Bepo_Colon LSHIFT(Bepo_Period)         // :
#define Bepo_QuestionMark LSHIFT(Bepo_Quote)   // ?
// Row 5
#define Bepo_NonBreakingSpace LSHIFT(Bepo_Spacebar) // (non-breaking space)

// Row 1
#define Bepo_EnDash              RALT(Bepo_Dollar)
#define Bepo_EmDash              RALT(Bepo_DoubleQuote)
#define Bepo_LessThan            RALT(Bepo_LeftGuillemet)
#define Bepo_GreaterThan         RALT(Bepo_RightGuillemet)
#define Bepo_LeftBracket         RALT(Bepo_LeftParen)
#define Bepo_RightBracket        RALT(Bepo_RightParen)
#define Bepo_Carat               RALT(Bepo_At)
#define Bepo_PlusMinus           RALT(Bepo_Plus)
#define Bepo_MinusMath           RALT(Bepo_Minus)
#define Bepo_Division            RALT(Bepo_Slash)
#define Bepo_Multiply            RALT(Bepo_Asterisk)
#define Bepo_NotEqual            RALT(Bepo_Equal)
#define Bepo_Permille            RALT(Bepo_Percent)
// Row 2
#define Bepo_Pipe                RALT(Bepo_B)
#define Bepo_DeadEAcute          RALT(Bepo_EAcute)
#define Bepo_Ampersand           RALT(Bepo_P)
#define Bepo_OE                  RALT(Bepo_O)
#define Bepo_DeadGrave           RALT(Bepo_EGrave)
#define Bepo_InvertedExclamationPoint  RALT(Bepo_DeadCirc)
#define Bepo_DeadCaron           RALT(Bepo_V)
#define Bepo_DeadSci             RALT(Bepo_D)
#define Bepo_DeadStroke          RALT(Bepo_L)
#define Bepo_Peace               RALT(Bepo_J)
#define Bepo_HorizontalStroke    RALT(Bepo_Z)
#define Bepo_Lys                 RALT(Bepo_W)
// Row 3
#define Bepo_AE                  RALT(Bepo_A)
#define Bepo_UGrave              RALT(Bepo_U)
#define Bepo_DeadDiaeresis       RALT(Bepo_I)
#define Bepo_Euro                RALT(Bepo_E)
#define Bepo_Apostrophe          RALT(Bepo_Comma)
#define Bepo_DeadCedilla         RALT(Bepo_C)
#define Bepo_DeadExposant        RALT(Bepo_T)
#define Bepo_DeadLatin           RALT(Bepo_S)
#define Bepo_DeadBreve           RALT(Bepo_R)
#define Bepo_DeadTild            RALT(Bepo_N)
#define Bepo_DeadMacron          RALT(Bepo_M)
#define Bepo_Airplane            RALT(Bepo_CCedilla)
// Row 4
#define Bepo_OtherSlash          RALT(Bepo_ECirc)
#define Bepo_Backslash           RALT(Bepo_AGrave)
#define Bepo_LeftCurlyBrace      RALT(Bepo_Y)
#define Bepo_RightCurlyBrace     RALT(Bepo_X)
#define Bepo_Ellipsis            RALT(Bepo_Period)
#define Bepo_Tilde               RALT(Bepo_K)
#define Bepo_InvertedQuestionMark RALT(Bepo_Quote)
#define Bepo_DeadAboveRing       RALT(Bepo_Q)
#define Bepo_DeagGreek           RALT(Bepo_G)
#define Bepo_DeadBelowDot        RALT(Bepo_H)
#define Bepo_DeadOgonek          RALT(Bepo_F)

#define Bepo_Underscore          RALT(Bepo_Spacebar)

// Row 1
#define Bepo_Paragraph              LSHIFT(RALT(Bepo_Dollar))
#define Bepo_DoubleLowQuoteMark     LSHIFT(RALT(Bepo_DoubleQuote))
#define Bepo_LeftDoubleQuoteMark    LSHIFT(RALT(Bepo_LeftGuillemet))
#define Bepo_RightDoubleQuoteMark   LSHIFT(RALT(Bepo_RightGuillemet))
#define Bepo_LessThanOrEqaulTo      LSHIFT(RALT(Bepo_LeftParen))
#define Bepo_GreaterThanOrEqualTo   LSHIFT(RALT(Bepo_RightParen))
#define Bepo_U262D                  LSHIFT(RALT(Bepo_At))
#define Bepo_NotSign                LSHIFT(RALT(Bepo_Plus))
#define Bepo_OneQuarter             LSHIFT(RALT(Bepo_Minus))
#define Bepo_OneHalf                LSHIFT(RALT(Bepo_Slash))
#define Bepo_ThreQuarters           LSHIFT(RALT(Bepo_Asterisk))
#define Bepo_Minutes                LSHIFT(RALT(Bepo_Equal))
#define Bepo_Seconds                LSHIFT(RALT(Bepo_Percent))
// Row 2
#define Bepo_OtherUnderscore        LSHIFT(RALT(Bepo_B))
#define Bepo_Heart                  LSHIFT(RALT(Bepo_EAcute))
#define Bepo_Section                LSHIFT(RALT(Bepo_P))
#define Bepo_CapitalOE              LSHIFT(RALT(Bepo_O))
#define Bepo_Grave                  LSHIFT(RALT(Bepo_EGrave))
#define Bepo_U2620                  LSHIFT(RALT(Bepo_DeadCirc))
#define Bepo_U2622                  LSHIFT(RALT(Bepo_V))
#define Bepo_U2623                  LSHIFT(RALT(Bepo_D))
#define Bepo_Sterling               LSHIFT(RALT(Bepo_L))
#define Bepo_262F                   LSHIFT(RALT(Bepo_J))
#define Bepo_2619                   LSHIFT(RALT(Bepo_Z))
#define Bepo_267F                   LSHIFT(RALT(Bepo_W))
// Row 3
#define Bepo_CapitalAE              LSHIFT(RALT(Bepo_A))
#define Bepo_CapitalUGrave          LSHIFT(RALT(Bepo_U))
#define Bepo_DeadAboveDot           LSHIFT(RALT(Bepo_I))
#define Bepo_DeadCurrentcy          LSHIFT(RALT(Bepo_E))
#define Bepo_DeadCommaBelow         LSHIFT(RALT(Bepo_Comma))
#define Bepo_Copyright              LSHIFT(RALT(Bepo_C))
#define Bepo_Trademark              LSHIFT(RALT(Bepo_T))
#define Bepo_LongS                  LSHIFT(RALT(Bepo_S))
#define Bepo_Registered             LSHIFT(RALT(Bepo_R))
#define Bepo_U2693                  LSHIFT(RALT(Bepo_N))
#define Bepo_U26FD                  LSHIFT(RALT(Bepo_M))
#define Bepo_Copyleft               LSHIFT(RALT(Bepo_CCedilla))
// Row 4
#define Bepo_Circumflex             LSHIFT(RALT(Bepo_ECirc))
#define Bepo_SingleLowQuoteMark     LSHIFT(RALT(Bepo_AGrave))
#define Bepo_LeftSingleQuoteMark    LSHIFT(RALT(Bepo_Y))
#define Bepo_RightSingleQuoteMark   LSHIFT(RALT(Bepo_X))
#define Bepo_PeriodCentered         LSHIFT(RALT(Bepo_Period))
#define Bepo_NoBreakHypen           LSHIFT(RALT(Bepo_K))
#define Bepo_DeadHook               LSHIFT(RALT(Bepo_Quote))
#define Bepo_DeadHorn               LSHIFT(RALT(Bepo_Q))
#define Bepo_Dagger                 LSHIFT(RALT(Bepo_G))
#define Bepo_DoubleDagger           LSHIFT(RALT(Bepo_H))
#define Bepo_U26C4                  LSHIFT(RALT(Bepo_F))

#define Bepo_NonBreakableSpace      LSHIFT(RALT(Bepo_Spacebar))

// Row 1
#define Qwer_Dollar         LSHIFT(Key_4)     // $
#define Qwer_DoubleQuote    LSHIFT(Key_Quote) // "
#define Qwer_LeftParen      LSHIFT(Key_9)     // (
#define Qwer_RightParen     LSHIFT(Key_0)     // )
#define Qwer_At             LSHIFT(Key_2)     // @
#define Qwer_Plus           LSHIFT(Key_Equals)// +
#define Qwer_Minus          Key_Minus         // -
#define Qwer_Slash          Key_Slash         // /
#define Qwer_Asterisk       LSHIFT(Key_8)     // *
#define Qwer_Equal          Key_Equals        // =
#define Qwer_Percent        LSHIFT(Key_5)     // %
// Row 2
#define Qwer_B              Key_B         // B
#define Qwer_P              Key_P         // P
#define Qwer_O              Key_O         // O
#define Qwer_V              Key_V         // V
#define Qwer_D              Key_D         // D
#define Qwer_L              Key_L         // L
#define Qwer_J              Key_J         // J
#define Qwer_Z              Key_Z         // Z
#define Qwer_W              Key_W         // W
// Row 3
#define Qwer_A              Key_A         // A
#define Qwer_U              Key_U         // U
#define Qwer_I              Key_I         // I
#define Qwer_E              Key_E         // E
#define Qwer_Comma          Key_Comma     // ,
#define Qwer_C              Key_C         // C
#define Qwer_T              Key_T         // T
#define Qwer_S              Key_S         // S
#define Qwer_R              Key_R         // R
#define Qwer_N              Key_N         // N
#define Qwer_M              Key_M         // M
#define Qwer_CCedilla       Key_C         // Ç
// Row 4
#define Qwer_AGrave         Key_A         // À
#define Qwer_Y              Key_Y         // Y
#define Qwer_X              Key_X         // X
#define Qwer_Period         Key_Period    // .
#define Qwer_K              Key_K         // K
#define Qwer_Quote          Key_Quote     // '
#define Qwer_Q              Key_Q         // Q
#define Qwer_G              Key_G         // G
#define Qwer_H              Key_H         // H
#define Qwer_F              Key_F         // F

#define Qwer_Spacebar       Key_Spacebar

#define Qwer_Hash LSHIFT(Key_3)           // #
#define Qwer_1             Key_1          // 1
#define Qwer_2             Key_2          // 2
#define Qwer_3             Key_3          // 3
#define Qwer_4             Key_4          // 4
#define Qwer_5             Key_5          // 5
#define Qwer_6             Key_6          // 6
#define Qwer_7             Key_7          // 7
#define Qwer_8             Key_8          // 8
#define Qwer_9             Key_9          // 9
#define Qwer_0             Key_0          // 0
#define Qwer_Backtick      Key_Backtick   // `
// Row 2
#define Qwer_ExclamationPoint LSHIFT(Key_1) // !
// Row 3
#define Qwer_Semicolon Key_Semicolon      // ;
// Row 4
#define Qwer_Colon LSHIFT(Key_Semicolon)  // :
#define Qwer_QuestionMark LSHIFT(Key_Slash) // ?

// Row 1
#define Qwer_LessThan            LSHIFT(Key_Comma)
#define Qwer_GreaterThan         LSHIFT(Key_Period)
#define Qwer_LeftBracket         Key_LeftBracket
#define Qwer_RightBracket        Key_RightBracket
#define Qwer_Carat               LSHIFT(Key_6)
// Row 2
#define Qwer_Pipe                LSHIFT(Key_Backslash)
#define Qwer_Ampersand           LSHIFT(Key_7)
// Row 3
// Row 4
#define Qwer_Backslash           Key_Backslash
#define Qwer_LeftCurlyBrace      LSHIFT(Key_LeftBracket)
#define Qwer_RightCurlyBrace     LSHIFT(Key_RightBracket)
#define Qwer_Tilde               LSHIFT(Key_Backtick)

#define Qwer_Underscore          LSHIFT(Key_Minus)


#define LHYPR(k) LCTRL(LALT(LSHIFT(LGUI(k))))
#define MvToLayer(l) MoveToLayer(l)

enum {  _PROG,
        _BEPO,
        _BEPOS,
        _PROGS,
        _NAV,
        _NUM,
        _QWERTY,
        _QWERTYS,
        _QNUM,
        _GAME,
};

enum {
    _U_BB_EMPTY,
    _U_BB_CHECKED,
    _U_BB_CROSSED,
    _U_SMILEY,
    _U_SW_SMILE,
    _U_THUMBS_UP,
    _U_THUMBS_DOWN,
};


KEYMAPS(

[_PROG] = KEYMAP(
////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////
Key_Escape,       Bepo_B,           CS(2),            Bepo_P,           Bepo_O,           CS(4),            Key_Backspace,    CS(0),            Bepo_V,           Bepo_D,           Bepo_L,           Bepo_J,           Bepo_Z,
CS(1),            Bepo_A,           Bepo_U,           Bepo_I,           Bepo_E,           Bepo_Comma,       /**************/  Bepo_C,           Bepo_T,           Bepo_S,           Bepo_R,           Bepo_N,           Bepo_M,
Bepo_Equal,       CS(3),            Bepo_Y,           Bepo_X,           Bepo_Period,      Bepo_K,           Key_Enter,        Bepo_Quote,       Bepo_Q,           Bepo_G,           Bepo_H,           Bepo_F,           Bepo_W,
LockLayer(_NUM),  MvToLayer(_GAME), MvToLayer(_QWERTY),___,             ___,              Key_Space,        LockLayer(_BEPO), Key_Tab,          ___,              ___,              Key_VolumeDown,   Key_VolumeUp,     LockLayer(_NUM)
),

[_BEPO] = KEYMAP(
////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////
___,              ___,              Bepo_EAcute,      ___,              ___,              Bepo_EGrave,      ___,              Bepo_DeadCirc,    M(_U_BB_EMPTY),   M(_U_BB_CHECKED), M(_U_BB_CROSSED), ___,              ___,
Bepo_CCedilla,    ___,              ___,              ___,              ___,              ___,              /**************/  ___,              M(_U_SMILEY),     M(_U_SW_SMILE),   ___,              ___,              ___,
___,              Bepo_AGrave,      ___,              ___,              ___,              ___,              ___,              ___,              M(_U_THUMBS_UP),  M(_U_THUMBS_DOWN),___,              ___,              ___,
___,              ___,              ___,              ___,              ___,              Key_Space,        ___,              Key_Tab,          ___,              ___,              ___,              ___,              ___
),

[_BEPOS] = KEYMAP(
////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////,   ////////////////,    ////////////////
___,              ___,              CS(2),            Key_Insert,       Key_Delete,       CS(4),            ___,              CS(0),            Bepo_Tilde,       Bepo_Percent,     Bepo_Backslash,     Bepo_Backtick,       Key_International7,
CS(1),            Bepo_Ampersand,   Bepo_Pipe,        Bepo_Carat,       Key_Backspace,    ___,              /**************/  Bepo_At,          Bepo_Plus,        Bepo_Minus,       Bepo_Slash,         Bepo_Asterisk,       Key_International8,
___,              CS(3),            ___,              ___,              ___,              ___,              ___,              Bepo_DoubleQuote, Bepo_Hash,        Bepo_Dollar,      Bepo_LeftGuillemet, Bepo_RightGuillemet, Key_International9,
___,              ___,              ___,              ___,              ___,              ___,              ___,              ___,              ___,              ___,              ___,                ___,                 ___
),

[_PROGS] = KEYMAP(
////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////,   ////////////////,    ////////////////
___,              ___,              Bepo_EAcute,      Key_Insert,       Key_Delete,       Bepo_EGrave,      ___,              Bepo_DeadCirc,    Bepo_Tilde,       Bepo_Percent,     Bepo_Backslash,     Bepo_Backtick,       Key_International7,
Bepo_CCedilla,    Bepo_Ampersand,   Bepo_Pipe,        Bepo_Carat,       Key_Backspace,    ___,              /**************/  Bepo_At,          Bepo_Plus,        Bepo_Minus,       Bepo_Slash,         Bepo_Asterisk,       Key_International8,
___,              Bepo_AGrave,      ___,              ___,              ___,              ___,              ___,              Bepo_DoubleQuote, Bepo_Hash,        Bepo_Dollar,      Bepo_LeftGuillemet, Bepo_RightGuillemet, Key_International9,
___,              ___,              ___,              ___,              ___,              ___,              ___,              ___,              ___,              ___,              ___,                ___,                 ___
),



[_NAV] = KEYMAP(
////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////
___,              ___,              ___,              ___,              ___,              ___,              ___,              Key_PageUp,       LHYPR(Bepo_Plus), Key_UpArrow,      LHYPR(Bepo_Minus), Key_Home,        Key_International4,
___,              ___,              ___,              ___,              ___,              ___,              /**************/  Key_PageDown,     Key_LeftArrow,    Key_DownArrow,    Key_RightArrow,    Key_End,         Key_International3,
___,              ___,              ___,              ___,              ___,              ___,              ___,              ___,              ___,              ___,              ___,               ___,             Key_CapsLock,
___,              ___,              ___,              ___,              ___,              ___,              ___,              ___,              ___,              ___,              ___,               ___,             ___
),

[_NUM] = KEYMAP(
////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////,   ////////////////, ////////////////, ////////////////, ////////////////, ////////////////
___,              Key_F9,           Key_F10,          Key_F11,          Key_F12,          ___,              ___,              Bepo_Asterisk,      Bepo_7,           Bepo_8,           Bepo_9,           Bepo_Slash,       Bepo_Equal,
___,              Key_F5,           Key_F6,           Key_F7,           Key_F8,           ___,              /**************/  Bepo_Plus,          Bepo_4,           Bepo_5,           Bepo_6,           Bepo_Period,      Key_Enter,
___,              Key_F1,           Key_F2,           Key_F3,           Key_F4,           ___,              ___,              Bepo_Minus,         Bepo_1,           Bepo_2,           Bepo_3,           Bepo_Comma,       ___,
___,              ___,              ___,              ___,              ___,              ___,              ___,              Bepo_0,             ___,              ___,              ___,              ___,              ___
),

[_QWERTY] = KEYMAP(
////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////
Key_Escape,       Qwer_B,           CS(7),            Qwer_P,           Qwer_O,           CS(9),            Key_Backspace,    CS(5),            Qwer_V,           Qwer_D,           Qwer_L,           Qwer_J,           Qwer_Z,
CS(6),            Qwer_A,           Qwer_U,           Qwer_I,           Qwer_E,           CS(10),           /**************/  Qwer_C,           Qwer_T,           Qwer_S,           Qwer_R,           Qwer_N,           Qwer_M,
Qwer_Equal,       CS(8),            Qwer_Y,           Qwer_X,           CS(11),           Qwer_K,           Key_Enter,        CS(12),           Qwer_Q,           Qwer_G,           Qwer_H,           Qwer_F,           Qwer_W,
LockLayer(_QNUM), ___,              MvToLayer(_PROG), ___,              ___,              Key_Space,        ___,              Key_Tab,          ___,              ___,              ___,              ___,              LockLayer(_QNUM)
),

[_QWERTYS] = KEYMAP(
////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////,   ////////////////,    ////////////////
___,              ___,              ___,              Key_Insert,       Key_Delete,       ___,              ___,              Qwer_Carat,       Qwer_Tilde,       Qwer_Percent,     Qwer_Backslash,     Qwer_Backtick,       Key_International7,
___,              Qwer_Ampersand,   Qwer_Pipe,        Qwer_Carat,       Key_Backspace,    ___,              /**************/  Qwer_At,          Qwer_Plus,        Qwer_Minus,       Qwer_Slash,         Qwer_Asterisk,       Key_International8,
___,              ___,              ___,              ___,              ___,              ___,              ___,              Qwer_DoubleQuote, Qwer_Hash,        Qwer_Dollar,      ___,                ___,                 Key_International9,
___,              ___,              ___,              ___,              ___,              ___,              ___,              ___,              ___,              ___,              ___,                ___,                 ___
),

[_QNUM] = KEYMAP(
////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////,   ////////////////, ////////////////, ////////////////, ////////////////, ////////////////
___,              Key_F9,           Key_F10,          Key_F11,          Key_F12,          ___,              ___,              Qwer_Asterisk,      Qwer_7,           Qwer_8,           Qwer_9,           Qwer_Slash,       Qwer_Equal,
___,              Key_F5,           Key_F6,           Key_F7,           Key_F8,           ___,              /**************/  Qwer_Plus,          Qwer_4,           Qwer_5,           Qwer_6,           Qwer_Period,      Key_Enter,
___,              Key_F1,           Key_F2,           Key_F3,           Key_F4,           ___,              ___,              Qwer_Minus,         Key_1,            Qwer_2,           Qwer_3,           Qwer_Comma,       ___,
___,              ___,              ___,              ___,              ___,              ___,              ___,              Qwer_0,             ___,              ___,              ___,              ___,              ___
),

[_GAME] = KEYMAP(
////////////////,   ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////, ////////////////
Key_Escape,         Bepo_B,           CS(2),            Bepo_P,           Bepo_O,           CS(4),            Key_Backspace,    CS(0),            Bepo_V,           Bepo_D,           Bepo_L,           Bepo_J,           Bepo_Z,
CS(1),              Bepo_A,           Bepo_U,           Bepo_I,           Bepo_E,           Bepo_Comma,       /**************/  Bepo_C,           Bepo_T,           Bepo_S,           Bepo_R,           Bepo_N,           Bepo_M,
Bepo_Equal,         CS(3),            Bepo_Y,           Bepo_X,           Bepo_Period,      Bepo_K,           Key_Enter,        Bepo_Quote,       Bepo_Q,           Bepo_G,           Bepo_H,           Bepo_F,           Bepo_W,
Key_LeftControl,    MvToLayer(_PROG), Bepo_Pipe,        Bepo_Carat,       Bepo_Dollar,      Key_Space,        Bepo_Slash,       Key_Tab,          Bepo_Asterisk,    Bepo_Hash,        Key_VolumeDown,   Key_VolumeUp,     Bepo_Percent
)

);

namespace kaleidoscope {
class FocusLayerEvent : public Plugin {
public:
    static void dumpLayerState(uint8_t index, uint8_t layer) {
        Serial.print(::Layer.isActive(layer) ? 1 : 0);
    }

    EventHandlerResult onLayerChange() {
        ::Focus.send(::Focus.COMMENT);
        for (uint8_t i = 0; i < 32; i++) {
            ::Focus.send(::Layer.isActive(i) ? 1 : 0);
        }
        ::Focus.send(::Focus.NEWLINE);
        return EventHandlerResult::OK;
    }
};
}
kaleidoscope::FocusLayerEvent FocusLayerEvent;

static void unicode(uint32_t character, uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Unicode.type(character);
  }
}

const macro_t *macroAction(uint8_t macro_id, KeyEvent &event) {
  switch (macro_id) {
  case _U_BB_EMPTY:
    unicode(0x2610, event.state);
    break;
  case _U_BB_CHECKED:
    unicode(0x2611, event.state);
    break;
  case _U_BB_CROSSED:
    unicode(0x2612, event.state);
    break;
  case _U_SMILEY:
    unicode(0x1f642, event.state);
    break;
  case _U_SW_SMILE:
    unicode(0x1f605, event.state);
    break;
  case _U_THUMBS_UP:
    unicode(0x1f4dd, event.state);
    break;
  case _U_THUMBS_DOWN:
    unicode(0x1f4df, event.state);
    break;
  }
  return MACRO_NONE;
}

__attribute__((weak)) Key hexToKeysWithNumpad(uint8_t hex) {
  uint8_t m;
  if (hex == 0x0) {
    return Key_Keypad0;
  }
  if (hex < 0xA) {
    m = Key_Keypad1.getKeyCode() + (hex - 0x1);
  } else {
    switch (hex) {
    case 0xA:
      m = Bepo_A.getKeyCode();
      break;
    case 0xB:
      m = Bepo_B.getKeyCode();
      break;
    case 0xC:
      m = Bepo_C.getKeyCode();
      break;
    case 0xD:
      m = Bepo_D.getKeyCode();
      break;
    case 0xE:
      m = Bepo_E.getKeyCode();
      break;
    case 0xF:
      m = Bepo_F.getKeyCode();
      break;
    default:
      m = Key_NoKey.getKeyCode();
      break;
    }
  }
  return { m, KEY_FLAGS };
}

KALEIDOSCOPE_INIT_PLUGINS(Macros, Qukeys, CharShift, Focus, LayerFocus, FocusLayerEvent, FocusHostOSCommand, EEPROMSettings, HostOS, Unicode);

void setup() {
    QUKEYS(
           kaleidoscope::plugin::Qukey(_PROG, KeyAddr(1, 0), Key_LeftShift),
           kaleidoscope::plugin::Qukey(_PROG, KeyAddr(1, 1), ShiftToLayer(_NAV)),
           kaleidoscope::plugin::Qukey(_PROG, KeyAddr(1, 2), Key_LeftGui),
           kaleidoscope::plugin::Qukey(_PROG, KeyAddr(1, 3), Key_LeftAlt),
           kaleidoscope::plugin::Qukey(_PROG, KeyAddr(1, 4), Key_LeftControl),
           kaleidoscope::plugin::Qukey(_PROG, KeyAddr(1, 8), Key_RightControl),
           kaleidoscope::plugin::Qukey(_PROG, KeyAddr(1, 9), Key_LeftAlt),
           kaleidoscope::plugin::Qukey(_PROG, KeyAddr(1, 10), Key_RightGui),
           kaleidoscope::plugin::Qukey(_PROG, KeyAddr(1, 11), Key_RightAlt),
           kaleidoscope::plugin::Qukey(_PROG, KeyAddr(1, 12), Key_RightShift),
           // Shift to layer when hold, toggle otherwise
           kaleidoscope::plugin::Qukey(_PROG, KeyAddr(3, 0), ShiftToLayer(_NUM)),
           kaleidoscope::plugin::Qukey(_PROG, KeyAddr(3, 4), ShiftToLayer(_BEPO)),
           kaleidoscope::plugin::Qukey(_PROG, KeyAddr(3, 5), ShiftToLayer(_PROGS)),
           kaleidoscope::plugin::Qukey(_PROG, KeyAddr(3, 7), ShiftToLayer(_PROGS)),
           kaleidoscope::plugin::Qukey(_PROG, KeyAddr(3, 8), ShiftToLayer(_BEPO)),
           kaleidoscope::plugin::Qukey(_PROG, KeyAddr(3, 12), ShiftToLayer(_NUM)),
           // Shift to PROGS when on BEPO layer
           kaleidoscope::plugin::Qukey(_BEPO, KeyAddr(3, 5), ShiftToLayer(_BEPOS)),
           kaleidoscope::plugin::Qukey(_BEPO, KeyAddr(3, 7), ShiftToLayer(_BEPOS)),

           // Same for qwerty
           kaleidoscope::plugin::Qukey(_QWERTY, KeyAddr(1, 0), Key_LeftShift),
           kaleidoscope::plugin::Qukey(_QWERTY, KeyAddr(1, 1), ShiftToLayer(_NAV)),
           kaleidoscope::plugin::Qukey(_QWERTY, KeyAddr(1, 2), Key_LeftGui),
           kaleidoscope::plugin::Qukey(_QWERTY, KeyAddr(1, 3), Key_LeftAlt),
           kaleidoscope::plugin::Qukey(_QWERTY, KeyAddr(1, 4), Key_LeftControl),
           kaleidoscope::plugin::Qukey(_QWERTY, KeyAddr(1, 8), Key_RightControl),
           kaleidoscope::plugin::Qukey(_QWERTY, KeyAddr(1, 9), Key_LeftAlt),
           kaleidoscope::plugin::Qukey(_QWERTY, KeyAddr(1, 10), Key_RightGui),
           kaleidoscope::plugin::Qukey(_QWERTY, KeyAddr(1, 11), Key_RightAlt),
           kaleidoscope::plugin::Qukey(_QWERTY, KeyAddr(1, 12), Key_RightShift),
           // Shift to layer when hold, toggle otherwise
           kaleidoscope::plugin::Qukey(_QWERTY, KeyAddr(3, 0), ShiftToLayer(_QNUM)),
           kaleidoscope::plugin::Qukey(_QWERTY, KeyAddr(3, 5), ShiftToLayer(_QWERTYS)),
           kaleidoscope::plugin::Qukey(_QWERTY, KeyAddr(3, 7), ShiftToLayer(_QWERTYS)),
           kaleidoscope::plugin::Qukey(_QWERTY, KeyAddr(3, 12), ShiftToLayer(_QNUM))

);

    Qukeys.setOverlapThreshold(90);
    HostOS.os(kaleidoscope::hostos::Type::LINUX);
    Unicode.setLinuxKey(Bepo_U);
    Kaleidoscope.setup();
    CS_KEYS(
           kaleidoscope::plugin::CharShift::KeyPair(Bepo_Underscore, Bepo_ExclamationPoint),
           kaleidoscope::plugin::CharShift::KeyPair(Bepo_LeftParen, Bepo_RightParen),
           kaleidoscope::plugin::CharShift::KeyPair(Bepo_LeftCurlyBrace, Bepo_RightCurlyBrace),
           kaleidoscope::plugin::CharShift::KeyPair(Bepo_LeftBracket, Bepo_RightBracket),
           kaleidoscope::plugin::CharShift::KeyPair(Bepo_LessThan, Bepo_GreaterThan),
           // Qwerty version
           kaleidoscope::plugin::CharShift::KeyPair(Qwer_Underscore, Qwer_ExclamationPoint),
           kaleidoscope::plugin::CharShift::KeyPair(Qwer_LeftParen, Qwer_RightParen),
           kaleidoscope::plugin::CharShift::KeyPair(Qwer_LeftCurlyBrace, Qwer_RightCurlyBrace),
           kaleidoscope::plugin::CharShift::KeyPair(Qwer_LeftBracket, Qwer_RightBracket),
           kaleidoscope::plugin::CharShift::KeyPair(Qwer_LessThan, Qwer_GreaterThan),
           kaleidoscope::plugin::CharShift::KeyPair(Qwer_Comma, Qwer_Semicolon),
           kaleidoscope::plugin::CharShift::KeyPair(Qwer_Period, Qwer_Colon),
           kaleidoscope::plugin::CharShift::KeyPair(Qwer_Quote, Qwer_QuestionMark)
           );

}

void loop() {
    Kaleidoscope.loop();
}
