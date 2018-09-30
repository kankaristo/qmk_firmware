#include "viterbi.h"
#include "action_layer.h"
#include "eeconfig.h"
#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#endif

extern keymap_config_t keymap_config;

// Layers
#define _QWERTY 0
#define _RAISE 1
#define _LOWER 2
#define _FRONT 3

// No-op and transparent aliases
#define KC_ KC_NO
#define KC______ KC_TRNS

// Layer access aliases
#define KC_RAISE LT(_RAISE, KC_SPACE)
#define KC_LOWER LT(_LOWER, KC_ENTER)
#define KC_FRONT MO(_FRONT)

// Character aliases
#define KC_CRRNC RALT(KC_3)
#define KC_LPREN KC_SCOLON
#define KC_RPREN KC_QUOTE
#define KC_LBRCE S(KC_SCOLON)
#define KC_RBRCE S(KC_QUOTE)
#define KC_LBRKT RALT(KC_SCOLON)
#define KC_RBRKT RALT(KC_QUOTE)

// Reset alias
#define KC_RESET RESET

// Script aliases
#define KC_FN_01 HYPR(KC_F1)
#define KC_FN_02 HYPR(KC_F2)
#define KC_FN_03 HYPR(KC_F3)
#define KC_FN_04 HYPR(KC_F4)
#define KC_FN_05 HYPR(KC_F5)
#define KC_FN_06 HYPR(KC_F6)
#define KC_FN_07 HYPR(KC_F7)
#define KC_FN_08 HYPR(KC_F8)
#define KC_FN_09 HYPR(KC_F9)
#define KC_FN_10 HYPR(KC_F10)
#define KC_FN_11 HYPR(KC_F11)
#define KC_FN_12 HYPR(KC_F12)

// Media aliases
#define KC_M_PLY LCAG(KC_MEDIA_SELECT)
#define KC_M_SEL HYPR(KC_MEDIA_SELECT)
#define KC_M_PRV HYPR(KC_MEDIA_PREV_TRACK)
#define KC_M_NXT HYPR(KC_MEDIA_NEXT_TRACK)
#define KC_M_BCK LCAG(KC_MEDIA_PREV_TRACK)
#define KC_M_FRW LCAG(KC_MEDIA_NEXT_TRACK)


// Custom keycodes
enum custom_keycodes {
    // Macros
    KC_MC_01 = SAFE_RANGE,
    KC_MC_02,
    KC_MC_03,
    KC_MC_04,
    KC_MC_05,
    KC_MC_06,
    KC_MC_07,
    KC_MC_08,
    KC_MC_09,
    KC_MC_10,
    KC_MC_11,
    KC_MC_12
};


/*!
 * Process custom keycodes.
 */
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
        switch(keycode) {
            case KC_MC_07: {
                SEND_STRING("790");
                
                return false;
            }
            case KC_MC_08: {
                SEND_STRING(SS_LCTRL("q"));
                SEND_STRING(SS_LCTRL(SS_TAP(X_TAB)));
                
                return false;
            }
        }
    }
    
    return true;
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // TODO: Dead diaeresis (with a leader key? IDK)
    [_QWERTY] = LAYOUT_kc(
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        GESC ,   1  ,   2  ,   3  ,   4  ,   5  ,   6  ,           7  ,   8  ,   9  ,   0  , MINUS, EQUAL, GRAVE,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
         TAB ,   Q  ,   W  ,   E  ,   R  ,   T  , SPACE,         BSPC ,   Y  ,   U  ,   I  ,   O  ,   P  , RBRC ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        LGUI ,   A  ,   S  ,   D  ,   F  ,   G  , SPACE,         ENTER,   H  ,   J  ,   K  ,   L  , BSLS , LBRC ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        LSFT ,   Z  ,   X  ,   C  ,   V  ,   B  , SPACE,              ,   N  ,   M  , COMMA,  DOT , SLASH, RSFT ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
         UP  , DOWN ,      , LCTRL, LSFT , LALT , RAISE,         LOWER, RCTRL, RSFT , RALT ,      , LEFT , RIGHT
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
    ),
    
    [_RAISE] = LAYOUT_kc(
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
         ESC ,  F1  ,  F2  ,  F3  ,  F4  ,  F5  ,  F6  ,          F7  ,  F8  ,  F9  ,  F10 ,  F11 ,  F12 ,      ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
             ,      ,      ,      ,      ,      ,      ,         PSCR , PGUP , HOME ,  UP  ,  END ,      ,      ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        _____,      ,      ,      ,      ,      ,      ,         PAUSE, PGDN , LEFT , DOWN , RIGHT,      ,      ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        _____,      ,      ,      ,      ,      ,      ,          INS , SLCK ,      ,      ,      ,      , _____,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        PGUP , PGDN ,      , _____, _____, _____,      ,         FRONT, _____, _____, _____,      , HOME ,  END
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
    ),
    
    [_LOWER] = LAYOUT_kc(
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
             , MC_01, MC_02, MC_03, MC_04, MC_05, MC_06,         MC_07, MC_08, MC_09, MC_10, MC_11, MC_12,      ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
             ,      ,      , CRRNC,      ,      ,      ,          DEL ,      , LPREN, RPREN,      ,      ,      ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        _____,      ,      ,      ,      ,      ,      ,              ,      , LBRCE, RBRCE,      ,      ,      ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        _____,      ,      ,      ,      ,      ,      ,              ,      , LBRKT, RBRKT,      ,      , _____,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
             ,      ,      , _____, _____, _____, FRONT,              , _____, _____, _____,      ,      ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
    ),
    
    [_FRONT] = LAYOUT_kc(
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
             , FN_01, FN_02, FN_03, FN_04, FN_05, FN_06,         FN_07, FN_08, FN_09, FN_10, FN_11, FN_12, ACL0 ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
             ,      , M_PRV, M_SEL, M_NXT,      , VOLU ,         BTN4 , WH_U ,      , MS_U ,      , BTN1 , ACL1 ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        _____,      , M_BCK, M_PLY, M_FRW,      , VOLD ,         BTN5 , WH_D , MS_L , MS_D , MS_R , BTN2 , ACL2 ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        _____,      ,      ,      ,      ,      , MUTE ,              ,      , WH_L ,      , WH_R , BTN3 , _____,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
             ,      ,      , _____, _____, _____,      ,              , _____, _____, _____,      ,      ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
    )
};

void led_set_user(uint8_t usb_led) {
    #ifdef RGBLIGHT_ENABLE
    if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
        rgblight_enable();
    }
    else {
        rgblight_disable();
    }
    #endif //RGBLIGHT_ENABLE
}
