/* Copyright 2023 Kartikay Bagla <kartikaybagla@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "keymap_steno.h"

#define MTLG(x) MT(MOD_LGUI, x)
#define MTLA(x) MT(MOD_LALT, x)
#define MTLC(x) MT(MOD_LCTL, x)
#define MTLS(x) MT(MOD_LSFT, x)
#define MTRG(x) MT(MOD_RGUI, x)
#define MTRA(x) MT(MOD_RALT, x)
#define MTRC(x) MT(MOD_RCTL, x)
#define MTRS(x) MT(MOD_RSFT, x)

enum layers {
    _BASE,
    _QWERTY,
    _NAV,
    _MOUSE,
    _MEDIA,
    _NUM,
    _FUN,
    _STENO
};


#define LT_NAV(x) LT(_NAV, x)
#define LT_MSE(x) LT(_MOUSE, x)
#define LT_MED(x) LT(_MEDIA, x)
#define LT_NUM(x) LT(_NUM, x)
#define LT_FUN(x) LT(_FUN, x)
#define LT_QWR(x) LT(_QWERTY, x)


// Define a type for as many tap dance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_TRIPLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    QUOT_LAYR, // Our custom tap dance key; add any other tap dance keys to this enum
    PLOV_LAYR,
};

// Declare the functions to be used with your tap dance key(s)

// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);


const key_override_t num_layer_shift_0_override = ko_make_with_layers(
    MOD_MASK_SHIFT,
    KC_DOT,
    LSFT(KC_9),
    (layer_state_t) (1UL << _NUM)
);
// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &num_layer_shift_0_override,
    NULL // Null terminate the array of overrides!
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_split_3x5_3(
    MTLG(KC_Q),     MTLA(KC_W),     MTLC(KC_F),     MTLS(KC_P),     KC_B,
    KC_J,           MTRS(KC_L),     MTRC(KC_U),     MTRA(KC_Y),     MTRG(KC_QUOTE),
    KC_A,           KC_R,           KC_S,           KC_T,           KC_G,
    KC_M,           KC_N,           KC_E,           KC_I,           KC_O,
    KC_Z,           KC_X,           KC_C,           KC_D,           KC_V,
    KC_K,           KC_H,           KC_COMM,        KC_DOT,         KC_SLSH,
                                    LT_MED(KC_ESC), LT_NAV(KC_TAB), LT_MSE(KC_SPC),
    TD(QUOT_LAYR), LT_NUM(KC_BSPC),LT_FUN(KC_DEL)
),
[_QWERTY] = LAYOUT_split_3x5_3(
    KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,
    KC_1,           KC_2,           KC_3,           KC_4,           KC_5,
    KC_LSFT,        KC_A,           KC_S,           KC_D,           KC_F,
    KC_6,           KC_7,           KC_8,           KC_9,           KC_0,
    KC_LCTL,        KC_Z,           KC_X,           KC_C,           KC_V,
    KC_N,           KC_M,           KC_COMM,        KC_DOT,         KC_SLSH,
                                    KC_ESC,         KC_LALT,         KC_SPC,
    TD(QUOT_LAYR),  KC_BSPC,        KC_DEL
),
[_NAV] = LAYOUT_split_3x5_3(
    KC_LGUI,        KC_LALT,        KC_LCTL,        KC_LSFT,        KC_TRNS,
    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    KC_CAPS,        KC_LEFT,        KC_DOWN,        KC_UP,          KC_RGHT,
    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    KC_INS,         KC_HOME,        KC_PGDN,        KC_PGUP,        KC_END,
                                    KC_TRNS,        KC_TRNS,        KC_TRNS,
    KC_TRNS,        KC_TRNS,        KC_TRNS
),
[_MOUSE] = LAYOUT_split_3x5_3(
    KC_LGUI,        KC_LALT,        KC_LCTL,        KC_LSFT,        KC_TRNS,
    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    KC_TRNS,        KC_MS_L,        KC_MS_D,        KC_MS_U,        KC_MS_R,
    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    KC_TRNS,        KC_WH_L,        KC_WH_D,        KC_WH_U,        KC_WH_R,
                                    KC_TRNS,        KC_TRNS,        KC_TRNS,
    KC_BTN1,        KC_BTN2,        KC_BTN3
),
[_MEDIA] = LAYOUT_split_3x5_3(
    KC_LGUI,        KC_LALT,        KC_LCTL,        KC_LSFT,        KC_TRNS,
    RGB_TOG,        RGB_MOD,        RGB_HUI,        RGB_SAI,        RGB_VAI,
    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    KC_TRNS,        KC_MPRV,        KC_VOLD,        KC_VOLU,        KC_MNXT,
    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    NK_TOGG,        KC_MRWD,        KC_BRID,        KC_BRIU,        KC_MFFD,
                                    KC_TRNS,        KC_TRNS,        KC_TRNS,
    KC_MUTE,        KC_MPLY,        KC_MSTP
),
[_NUM] = LAYOUT_split_3x5_3(
    KC_LBRC,        KC_7,           KC_8,           KC_9,           KC_RBRC,
    KC_TRNS,        KC_LSFT,        KC_LCTL,        KC_LALT,        KC_LGUI,
    KC_SCLN,        KC_4,           KC_5,           KC_6,           KC_EQL,
    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    KC_GRV,         KC_1,           KC_2,           KC_3,           KC_BSLS,
    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
                                    KC_DOT,         KC_0,           KC_MINS,
    KC_TRNS,        KC_TRNS,        KC_TRNS
),
[_FUN] = LAYOUT_split_3x5_3(
    KC_F12,         KC_F7,          KC_F8,          KC_F9,          KC_PSCR,
    KC_TRNS,        KC_LSFT,        KC_LCTL,        KC_LALT,        KC_LGUI,
    KC_F11,         KC_F4,          KC_F5,          KC_F6,          KC_SCRL,
    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    KC_F10,         KC_F1,          KC_F2,          KC_F3,          KC_PAUS,
    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
                                    KC_TRNS,        KC_TRNS,        KC_TRNS,
    KC_TRNS,        KC_TRNS,        KC_TRNS
),
[_STENO] = LAYOUT_split_3x5_3(
    STN_N1,         STN_N2,         STN_N3,         STN_N4,         STN_N5,
    STN_N6,         STN_N7,         STN_N8,         STN_N9,         STN_NA,
    STN_S1,         STN_TL,         STN_PL,         STN_HL,         STN_ST1,
    STN_FR,         STN_PR,         STN_LR,         STN_TR,         STN_DR,
    STN_S2,         STN_KL,         STN_WL,         STN_RL,         STN_ST2,
    STN_RR,         STN_BR,         STN_GR,         STN_SR,         STN_ZR,
                                    TG(_STENO),  STN_A,          STN_O,
    STN_E,          STN_U,          TG(_STENO)
)
};

#ifdef OLED_ENABLE
const char _str_1[] PROGMEM = "q w f p b  j l u y '\na r s t g  m n e i o\nz x c d v  k h , . /\n ES TB SP  EN BK DL";
const char _str_2[] PROGMEM = "NOPE: __ __ __ __ __\nMVMT: CP LF DN UP RG\nBRUH: IN HO PG PG EN\n  ____  ____  ____";
const char _str_3[] PROGMEM = "NOPE: __ __ __ __ __\nMOUS: __ LF DN UP RG\nSCWL: __ LF DN UP RG\n  LFMB  RGMB  MDMB";
const char _str_4[] PROGMEM = "RGB : TG MD HU SA VA\nMEDI: __ PR VD VU NX\nBRIG: NK RW BD BU FF\n  MUTE  PLAY  STOP";
const char _str_5[] PROGMEM = "NUM : [{ 7& 8* 9( ]}\nNUM : ;: 4$ 5% 6^ =+\nNUM : `~ 1! 2@ 3# \\|\nNUM : .( 0) -_";
const char _str_6[] PROGMEM = "FUNC: 12 7 8 9 PRTSC\nFUNC: 11 4 5 6 SCRLK\nFUNC: 10 1 2 3 PAUSE\n  ____  ____  ____";
const char _str_7[] PROGMEM = "TB q w e r 1 2 3 4 5\nSF a s d f 6 7 8 9 0\nCT z x c v n m , . /\n ES AL SP  EN BK DL";
const char _str_8[] PROGMEM = "steno               \ns-t-p-h-* -f-p-l-t-d\ns-k-w-r-* -r-b-g-s-z\n ES A  O    E  U ES";

PGM_P const keymap_strings[] PROGMEM = {
    [_BASE] = _str_1,
    [_NAV] = _str_2,
    [_MOUSE] = _str_3,
    [_MEDIA] = _str_4,
    [_NUM] = _str_5,
    [_FUN] = _str_6,
    [_QWERTY] = _str_7,
    [_STENO] = _str_8
};
const char undef_str[] PROGMEM = "UDF";

const char _layer_name_1[] PROGMEM = "COLEMAK-DH";
const char _layer_name_2[] PROGMEM = "NAVIGATE";
const char _layer_name_3[] PROGMEM = "MOUSE";
const char _layer_name_4[] PROGMEM = "MEDIA";
const char _layer_name_5[] PROGMEM = "NUMBERS";
const char _layer_name_6[] PROGMEM = "FUNCTION";
const char _layer_name_7[] PROGMEM = "QWERTY";
const char _layer_name_8[] PROGMEM = "STENO";
PGM_P const layer_names[] PROGMEM = {
    [_BASE] = _layer_name_1,
    [_NAV] = _layer_name_2,
    [_MOUSE] = _layer_name_3,
    [_MEDIA] = _layer_name_4,
    [_NUM] = _layer_name_5,
    [_FUN] = _layer_name_6,
    [_QWERTY] = _layer_name_7,
    [_STENO] = _layer_name_8
};

const char gui_logo[] = {
    128,129,160,161
};
const char alt_logo[] = {
    130,131,162,163
};
const char ctl_logo[] = {
    132,133,164,165
};
const char sft_logo[] = {
    134,135,166,167
};

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }

    return rotation;
}

void get_keymap_and_layer_str(uint8_t current_layer, const char** keymap_str, const char** layer_name_str) {
    switch (current_layer)
    {
    case _BASE:
        *keymap_str = keymap_strings[_BASE];
        *layer_name_str = layer_names[_BASE];
        break;
    case _NAV:
        *keymap_str = keymap_strings[_NAV];
        *layer_name_str = layer_names[_NAV];
        break;
    case _MOUSE:
        *keymap_str = keymap_strings[_MOUSE];
        *layer_name_str = layer_names[_MOUSE];
        break;
    case _MEDIA:
        *keymap_str = keymap_strings[_MEDIA];
        *layer_name_str = layer_names[_MEDIA];
        break;
    case _NUM:
        *keymap_str = keymap_strings[_NUM];
        *layer_name_str = layer_names[_NUM];
        break;
    case _FUN:
        *keymap_str = keymap_strings[_FUN];
        *layer_name_str = layer_names[_FUN];
        break;
    case _QWERTY:
        *keymap_str = keymap_strings[_QWERTY];
        *layer_name_str = layer_names[_QWERTY];
        break;
    case _STENO:
        *keymap_str = keymap_strings[_STENO];
        *layer_name_str = layer_names[_STENO];
        break;
    default:
        *keymap_str = undef_str;
        *layer_name_str = undef_str;
        break;
    }
    return;
}

void draw_2x2_symbol(const char* symbol, uint8_t col, uint8_t line, bool invert) {
    oled_set_cursor(col, line);
    oled_write_char(symbol[0], invert);
    oled_set_cursor(col+1, line);
    oled_write_char(symbol[1], invert);
    oled_set_cursor(col, line+1);
    oled_write_char(symbol[2], invert);
    oled_set_cursor(col+1, line+1);
    oled_write_char(symbol[3], invert);
}

void render_mod_status(uint8_t modifiers, uint8_t col, uint8_t line) {
    bool is_caps = host_keyboard_led_state().caps_lock;
    draw_2x2_symbol(gui_logo, col, line, (modifiers & MOD_BIT(KC_LGUI)));
    draw_2x2_symbol(alt_logo, col+2, line, (modifiers & MOD_BIT(KC_LALT)));
    draw_2x2_symbol(gui_logo, col+4, line, false);
    draw_2x2_symbol(alt_logo, col+6, line, true);
    draw_2x2_symbol(ctl_logo, col+4, line, (modifiers & MOD_BIT(KC_LCTL)));
    draw_2x2_symbol(sft_logo, col+6, line, (modifiers & MOD_BIT(KC_LSFT)) || is_caps);
    draw_2x2_symbol("NKRO", col+8, line, keymap_config.nkro);
    draw_2x2_symbol(sft_logo, col+10, line, (modifiers & MOD_BIT(KC_RSFT)) || is_caps);
    draw_2x2_symbol(ctl_logo, col+12, line, (modifiers & MOD_BIT(KC_RCTL)));
    draw_2x2_symbol(alt_logo, col+14, line, (modifiers & MOD_BIT(KC_RALT)));
    draw_2x2_symbol(gui_logo, col+16, line, (modifiers & MOD_BIT(KC_RGUI)));

}


bool oled_task_user(void) {
    uint8_t current_layer = get_highest_layer(layer_state);

    const char* keymap_str;
    const char* layer_name_str;
    get_keymap_and_layer_str(current_layer, &keymap_str, &layer_name_str);

    if (is_keyboard_master()) {
        oled_write_P(PSTR("LAYER: "), false);
        oled_write_ln_P(layer_name_str, false);
        render_mod_status(get_mods() | get_oneshot_mods(), 0, 2);
    } else {
        oled_write_ln_P(keymap_str, false);
    }

    return false;
}
#endif


// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) return TD_DOUBLE_TAP;
    else if (state->count == 3) return TD_TRIPLE_TAP;
    else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_ENT);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_QWERTY);
            break;
        case TD_DOUBLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(_QWERTY)) {
                // If already set, then switch it off
                layer_off(_QWERTY);
            } else {
                // If not already set, then switch the layer on
                layer_on(_QWERTY);
            }
            break;
        case TD_TRIPLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(_STENO)) {
                // If already set, then switch it off
                layer_off(_STENO);
            } else {
                // If not already set, then switch the layer on
                layer_on(_STENO);
            }
            break;
        default:
            break;
    }
}

void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_QWERTY);
    }
    ql_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [QUOT_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset)
};

// Set a long-ish tapping term for tap-dance keys
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            return 275;
        default:
            return TAPPING_TERM;
    }
}
