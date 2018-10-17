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

// Layer access aliases / thumb keys
#define KC_RAISE MO(_RAISE) //LT(_RAISE, KC_SPACE)
#define KC_LOWER MO(_LOWER) //LT(_LOWER, KC_ENTER)
#define KC_FRONT MO(_FRONT)
#define KC_THLSH MT(MOD_LSFT, KC_SPACE)
#define KC_THRSH MT(MOD_RSFT, KC_ENTER)
#define KC_SUPER KC_LGUI
#define KC_SSUPR S(KC_LGUI)

// Character aliases
#define KC_CRRNC RALT(KC_3)             // € £
#define KC_LPREN KC_SCOLON              // (
#define KC_RPREN KC_QUOTE               // )
#define KC_LBRCE S(KC_SCOLON)           // {
#define KC_RBRCE S(KC_QUOTE)            // }
#define KC_LBRKT RALT(KC_SCOLON)        // [
#define KC_RBRKT RALT(KC_QUOTE)         // ]
#define KC_LANGL KC_NONUS_BSLASH        // <
#define KC_RANGL S(KC_NONUS_BSLASH)     // >
#define KC_BAR RALT(KC_NONUS_BSLASH)    // |
#define KC_BKTCK RALT(KC_GRAVE)         // `
#define KC_AUMLT RALT(KC_A)             // ä Ä
#define KC_OUMLT RALT(KC_O)             // ö Ö

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

// Key combo aliases
#define KC_CTINS RCTL(KC_INS)           // Copy
#define KC_SHINS RSFT(KC_INS)           // Paste
#define KC_PRVTB LCTL(LSFT(KC_TAB))     // Previous tab

// Custom keycodes
enum custom_keycodes {
    // Top row macros
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
    KC_MC_12,
    
    // Other macros
    KC_ENDER,
    KC_CTQTB
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
            case KC_ENDER: {
                SEND_STRING(SS_TAP(X_END));
                SEND_STRING(SS_TAP(X_ENTER));
                
                return false;
            }
            case KC_CTQTB: {
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
         ESC ,   1  ,   2  ,   3  ,   4  ,   5  , GRAVE,         MINUS,   6  ,   7  ,   8  ,   9  ,   0  , BSPC ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
         TAB ,   Q  ,   W  ,   E  ,   R  ,   T  , RBRC ,         EQUAL,   Y  ,   U  ,   I  ,   O  ,   P  ,  DEL ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        SUPER,   A  ,   S  ,   D  ,   F  ,   G  , LBRC ,          DOT ,   H  ,   J  ,   K  ,   L  , BSLS , ENTER,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        LSFT ,   Z  ,   X  ,   C  ,   V  ,   B  , ENTER,         COMMA,   N  ,   M  , HOME ,  END ,  UP  , RSFT ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        LCTRL, RALT , LALT , LCTRL, SSUPR, RAISE, SPACE,         RSFT , LOWER, LALT , RCTRL, LEFT , DOWN , RIGHT
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
    ),
    
    [_RAISE] = LAYOUT_kc(
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
         ESC ,  F1  ,  F2  ,  F3  ,  F4  ,  F5  ,      ,         PSCR ,  F6  ,  F7  ,  F8  ,  F9  ,  F10 ,  F11 ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        PRVTB, CTQTB, M_PRV, M_SEL, M_NXT,      , VOLU ,         SLCK , PGUP , HOME ,  UP  ,  END ,      ,  F12 ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        _____,      , M_BCK, M_PLY, M_FRW,      , VOLD ,         PAUSE, PGDN , LEFT , DOWN , RIGHT,      , ENDER,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        _____,      ,      , CTINS, SHINS,      , MUTE ,          INS ,      ,      ,      ,      , PGUP , _____,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        _____, _____, _____, _____, _____,      , _____,         _____, FRONT, _____, _____, HOME , PGDN ,  END
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
    ),
    
    [_LOWER] = LAYOUT_kc(
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
             , MC_01, MC_02, MC_03, MC_04, MC_05,      ,              , MC_06, MC_07, MC_08, MC_09, MC_10,      ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
             ,      ,      , CRRNC,      ,      ,  BAR ,          BAR , LPREN, RPREN,      , OUMLT,      ,      ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        _____, AUMLT,      ,      ,      ,      ,      ,              , LBRCE, RBRCE, LANGL, RANGL, BKTCK,      ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        _____,      ,      ,      ,      ,      ,      ,              , LBRKT, RBRKT,      ,      ,      , _____,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        _____, _____, _____, _____, _____, FRONT, _____,         _____,      , _____, _____,      ,      ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
    ),
    
    [_FRONT] = LAYOUT_kc(
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
             , FN_01, FN_02, FN_03, FN_04, FN_05,      ,              , FN_06, FN_07, FN_08, FN_09, FN_10, ACL0 ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
             ,      , M_PRV, M_SEL, M_NXT,      , VOLU ,         BTN4 , WH_U , WH_L , MS_U , WH_R , BTN1 , ACL1 ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        _____,      , M_BCK, M_PLY, M_FRW,      , VOLD ,         BTN5 , WH_D , MS_L , MS_D , MS_R , BTN2 , ACL2 ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        _____,      ,      ,      ,      ,      , MUTE ,              ,      ,      ,      ,      , BTN3 , _____,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        _____, _____, _____, _____, _____,      , _____,         _____,      , _____, _____,      ,      ,
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
