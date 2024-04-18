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
    _NAV,
    _MOUSE,
    _MEDIA,
    _NUM,
    _FUN,
};

#define LT_NAV(x) LT(_NAV, x)
#define LT_MSE(x) LT(_MOUSE, x)
#define LT_MED(x) LT(_MEDIA, x)
#define LT_NUM(x) LT(_NUM, x)
#define LT_FUN(x) LT(_FUN, x)


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
    KC_Q,           KC_W,           KC_F,           KC_P,           KC_B,
    KC_J,           KC_L,           KC_U,           KC_Y,           KC_QUOTE,
    MTLG(KC_A),     MTLA(KC_R),     MTLC(KC_S),     MTLS(KC_T),     KC_G,
    KC_M,           MTRS(KC_N),     MTRC(KC_E),     MTRA(KC_I),     MTRG(KC_O),
    KC_Z,           KC_X,           KC_C,           KC_D,           KC_V,
    KC_K,           KC_H,           KC_COMM,        KC_DOT,         KC_SLSH,
                                    LT_MED(KC_ESC), LT_NAV(KC_TAB), LT_MSE(KC_SPC),
    KC_ENT,         LT_NUM(KC_BSPC),LT_FUN(KC_DEL)
),
[_NAV] = LAYOUT_split_3x5_3(
//  redo,           paste,          copy,           cut,            undo
    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    KC_LGUI,        KC_LALT,        KC_LCTL,        KC_LSFT,        KC_TRNS,
    KC_CAPS,        KC_LEFT,        KC_DOWN,        KC_UP,          KC_RGHT,
    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    KC_INS,         KC_HOME,        KC_PGDN,        KC_PGUP,        KC_END,
                                    KC_TRNS,        KC_TRNS,        KC_TRNS,
    KC_TRNS,        KC_TRNS,        KC_TRNS
),
[_MOUSE] = LAYOUT_split_3x5_3(
//  redo,           paste,          copy,           cut,            undo
    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    KC_LGUI,        KC_LALT,        KC_LCTL,        KC_LSFT,        KC_TRNS,
    KC_TRNS,        KC_MS_L,        KC_MS_D,        KC_MS_U,        KC_MS_R,
    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    KC_TRNS,        KC_WH_L,        KC_WH_D,        KC_WH_U,        KC_WH_R,
                                    KC_TRNS,        KC_TRNS,        KC_TRNS,
    KC_BTN1,        KC_BTN2,        KC_BTN3
),
[_MEDIA] = LAYOUT_split_3x5_3(
    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    RGB_TOG,        RGB_MOD,        RGB_HUI,        RGB_SAI,        RGB_VAI,
    KC_LGUI,        KC_LALT,        KC_LCTL,        KC_LSFT,        KC_TRNS,
    KC_TRNS,        KC_MPRV,        KC_VOLD,        KC_VOLU,        KC_MNXT,
    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    NK_TOGG,        KC_MRWD,        KC_BRID,        KC_BRIU,        KC_MFFD,
                                    KC_TRNS,        KC_TRNS,        KC_TRNS,
    KC_MUTE,        KC_MPLY,        KC_MSTP
),
[_NUM] = LAYOUT_split_3x5_3(
    KC_LBRC,        KC_7,           KC_8,           KC_9,           KC_RBRC,
    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    KC_SCLN,        KC_4,           KC_5,           KC_6,           KC_EQL,
    KC_TRNS,        KC_LSFT,        KC_LCTL,        KC_LALT,        KC_LGUI,
    KC_GRV,         KC_1,           KC_2,           KC_3,           KC_BSLS,
    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
                                    KC_DOT,         KC_0,           KC_MINS,
    KC_TRNS,        KC_TRNS,        KC_TRNS
),
[_FUN] = LAYOUT_split_3x5_3(
    KC_F12,         KC_F7,          KC_F8,          KC_F9,          KC_PSCR,
    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    KC_F11,         KC_F4,          KC_F5,          KC_F6,          KC_SCRL,
    KC_TRNS,        KC_LSFT,        KC_LCTL,        KC_LALT,        KC_LGUI,
    KC_F10,         KC_F1,          KC_F2,          KC_F3,          KC_PAUS,
    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
                                    KC_TRNS,        KC_TRNS,        KC_TRNS,
    KC_TRNS,        KC_TRNS,        KC_TRNS
)
};

#ifdef OLED_ENABLE
const char _str_1[] PROGMEM = "q w f p b  j l u y '\na r s t g  m n e i o\nz x c d v  k h , . /\n ES TB SP  EN BK DL";
const char _str_2[] PROGMEM = "NOPE: __ __ __ __ __\nMVMT: CP LF DN UP RG\nBRUH: IN HO PG PG EN\n  ____  ____  ____";
const char _str_3[] PROGMEM = "NOPE: __ __ __ __ __\nMOUS: __ LF DN UP RG\nSCWL: __ LF DN UP RG\n  LFMB  RGMB  MDMB";
const char _str_4[] PROGMEM = "RGB : TG MD HU SA VA\nMEDI: __ PR VD VU NX\nBRIG: NK RW BD BU FF\n  MUTE  PLAY  STOP";
const char _str_5[] PROGMEM = "NUM : [{ 7& 8* 9( ]}\nNUM : ;: 4$ 5% 6^ =+\nNUM : `~ 1! 2@ 3# \\| \nNUM : .( 0) -_";
const char _str_6[] PROGMEM = "FUNC: 12 7 8 9 PRTSC\nFUNC: 11 4 5 6 SCRLK\nFUNC: 10 1 2 3 PAUSE\n  ____  ____  ____";
PGM_P const keymap_strings[] PROGMEM = {
    [_BASE] = _str_1, 
    [_NAV] = _str_2,
    [_MOUSE] = _str_3,
    [_MEDIA] = _str_4,
    [_NUM] = _str_5,
    [_FUN] = _str_6
};
const char undef_str[] PROGMEM = "UDF";

const char _layer_name_1[] PROGMEM = "DEFAULT";
const char _layer_name_2[] PROGMEM = "NAVIGATE";
const char _layer_name_3[] PROGMEM = "MOUSE";
const char _layer_name_4[] PROGMEM = "MEDIA";
const char _layer_name_5[] PROGMEM = "NUMBERS";
const char _layer_name_6[] PROGMEM = "FUNCTION";
PGM_P const layer_names[] PROGMEM = {
    [_BASE] = _layer_name_1, 
    [_NAV] = _layer_name_2, 
    [_MOUSE] = _layer_name_3, 
    [_MEDIA] = _layer_name_4, 
    [_NUM] = _layer_name_5, 
    [_FUN] = _layer_name_6
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
