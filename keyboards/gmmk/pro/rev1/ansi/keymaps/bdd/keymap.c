/* Copyright 2021 Berk D. Demir
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

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_END,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_HOME,
        MO(2),   KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RALT, KC_RCTL, MO(2),   KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          LALT(KC_M),
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          LALT(KC_R),
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          LALT(KC_V),
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, LALT(KC_E),
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

    [2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, TO(0)  , _______, _______, _______,          TO(1)  ,
        _______, _______, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,          TO(1)  ,
        KC_ESC , _______, RGB_VAD, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______,          _______,          TO(1)  ,
        _______,          _______, RGB_HUI, _______, _______, _______, _______, _______, _______, _______, _______,          _______, RGB_MOD, KC_PWR ,
        _______, _______, _______,                            _______,                            _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
    ),
};
// clang-format on

#define LED_ARR_END 255

const uint8_t left_side_leds[] =  { 67, 70, 73, 76, 80, 83, 87, 91, LED_ARR_END };
const uint8_t right_side_leds[] = { 68, 71, 74, 77, 81, 84, 88, 92, LED_ARR_END };
const uint8_t vc_key_leds[] =     { 72, 75, 82, 86, LED_ARR_END };

void rgb_matrix_set_color_led_array(const uint8_t leds[], uint8_t r, uint8_t g, uint8_t b) {
  for (uint8_t i = 0; leds[i] != LED_ARR_END; i++) {
    rgb_matrix_set_color(leds[i], r, g, b);
  }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
      case 0:
        rgb_matrix_set_color_led_array(left_side_leds, RGB_GOLD);
        rgb_matrix_set_color_led_array(right_side_leds, RGB_OFF);
        rgb_matrix_set_color_led_array(vc_key_leds, RGB_OFF);
        break;

      case 1:
        rgb_matrix_set_color_led_array(left_side_leds, RGB_OFF);
        rgb_matrix_set_color_led_array(right_side_leds, RGB_GOLD);
        rgb_matrix_set_color_led_array(vc_key_leds, RGB_GOLD);
        break;

      default:
        break;
    }

    return state;
}
