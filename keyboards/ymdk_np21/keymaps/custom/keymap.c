#include "ymdk_np21.h"
#include "action_layer.h"


#define _MACRO_DEFAULT 0
#define _MACRO_BACKLIGHT 1
#define _MACRO_MOUSE_KEYS 2


enum custom_keycodes {
    MACRO_DEFAULT = SAFE_RANGE,
    MACRO_BACKLIGHT,
    MACRO_MOUSE_KEYS
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ,-----------------------.
     * |   |   |   |   |   |   |
     * |---+---+---+---+---+---|
     * |   |   |   |   |   |   |---,
     * |---+---+---+---+---+---|USB|
     * |   |   |   |   |   |   |---'
     * |---+---+---+---+---+---|
     * |   |   |   |   |   |   |
     * `-----------------------'
     */
    
    // F19-F24 don't work properly on Fedora/Gnome,
    // so F13-F18 are re-used with modifiers
    [_MACRO_DEFAULT] = KEYMAP( \
        KC_F17,       LT(_MACRO_MOUSE_KEYS, KC_F16), LGUI(KC_A), LGUI(KC_Q), LGUI(KC_1), LT(_MACRO_BACKLIGHT, KC_ESC), \
        KC_F18,       LGUI(KC_X),                    LGUI(KC_S), LGUI(KC_W), LGUI(KC_2), KC_F13, \
        HYPR(KC_F13), LGUI(KC_C),                    LGUI(KC_D), LGUI(KC_E), LGUI(KC_3), KC_F14, \
        HYPR(KC_F14), LGUI(KC_V),                    LGUI(KC_F), LGUI(KC_R), LGUI(KC_4), KC_F15  \
    ),
    
    // Doesn't actually support breathing, but let's define the key anyway
    [_MACRO_BACKLIGHT] = KEYMAP( \
        XXXXXXX, TO(_MACRO_MOUSE_KEYS), XXXXXXX, XXXXXXX, BL_BRTG, XXXXXXX, \
        XXXXXXX, XXXXXXX,               XXXXXXX, XXXXXXX, XXXXXXX, BL_DEC,  \
        XXXXXXX, XXXXXXX,               XXXXXXX, XXXXXXX, XXXXXXX, BL_INC,  \
        XXXXXXX, XXXXXXX,               XXXXXXX, XXXXXXX, XXXXXXX, BL_TOGG  \
    ),
    
    [_MACRO_MOUSE_KEYS] = KEYMAP( \
        HYPR(KC_F16), XXXXXXX,     KC_MS_BTN3, KC_MS_BTN4,     KC_MS_BTN5,  TG(_MACRO_MOUSE_KEYS), \
        KC_MS_ACCEL0, KC_MS_LEFT,  KC_MS_BTN1, KC_MS_WH_LEFT,  XXXXXXX,     XXXXXXX, \
        KC_MS_ACCEL1, KC_MS_DOWN,  KC_MS_UP,   KC_MS_WH_DOWN,  KC_MS_WH_UP, XXXXXXX, \
        KC_MS_ACCEL2, KC_MS_RIGHT, KC_MS_BTN2, KC_MS_WH_RIGHT, XXXXXXX,     XXXXXXX  \
    )
};
