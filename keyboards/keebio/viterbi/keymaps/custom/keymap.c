#include QMK_KEYBOARD_H

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
#define KC_SSUPR MT(KC_LGUI, S(KC_LGUI))

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
#define KC_FN_00 HYPR(KC_ESC)
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
    [_QWERTY] = LAYOUT_ortho_5x14(
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        KC_ESC  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_GRAVE,         KC_MINUS, KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_BSPC ,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        KC_TAB  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , KC_RBRC ,         KC_EQUAL, KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_DEL  ,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        KC_SUPER, KC_A    , KC_S    , KC_D    , KC_F    , KC_G    , KC_LBRC ,         KC_DOT  , KC_H    , KC_J    , KC_K    , KC_L    , KC_BSLS , KC_ENTER,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        KC_LSFT , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    , KC_ENTER,         KC_COMMA, KC_N    , KC_M    , KC_HOME , KC_END  , KC_UP   , KC_RSFT ,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        KC_LCTRL, KC_RALT , KC_LALT , KC_LCTRL, KC_SSUPR, KC_RAISE, KC_SPACE,         KC_RSFT , KC_LOWER, KC_LALT , KC_RCTRL, KC_LEFT , KC_DOWN , KC_RIGHT
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
    ),
    
    [_RAISE] = LAYOUT_ortho_5x14(
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        KC_FN_00, KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_     ,         KC_PSCR , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  ,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        KC_PRVTB, KC_CTQTB, KC_M_PRV, KC_M_SEL, KC_M_NXT, KC_     , KC_VOLU ,         KC_SLCK , KC_PGUP , KC_HOME , KC_UP   , KC_END  , KC_     , KC_F12  ,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        KC______, KC_     , KC_M_BCK, KC_M_PLY, KC_M_FRW, KC_     , KC_VOLD ,         KC_PAUSE, KC_PGDN , KC_LEFT , KC_DOWN , KC_RIGHT, KC_     , KC_ENDER,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        KC______, KC_     , KC_     , KC_CTINS, KC_SHINS, KC_     , KC_MUTE ,         KC_INS  , KC_     , KC_     , KC_     , KC_     , KC_PGUP , KC______,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        KC______, KC______, KC______, KC______, KC______, KC_     , KC______,         KC______, KC_FRONT, KC______, KC______, KC_HOME , KC_PGDN , KC_END
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
    ),
    
    [_LOWER] = LAYOUT_ortho_5x14(
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        KC_     , KC_MC_01, KC_MC_02, KC_MC_03, KC_MC_04, KC_MC_05, KC_     ,         KC_     , KC_MC_06, KC_MC_07, KC_MC_08, KC_MC_09, KC_MC_10, KC_     ,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        KC_     , KC_     , KC_     , KC_CRRNC, KC_     , KC_     , KC_BAR  ,         KC_BAR  , KC_LPREN, KC_RPREN, KC_     , KC_OUMLT, KC_     , KC_     ,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        KC______, KC_AUMLT, KC_     , KC_     , KC_     , KC_     , KC_     ,         KC_     , KC_LBRCE, KC_RBRCE, KC_LANGL, KC_RANGL, KC_BKTCK, KC_     ,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        KC______, KC_     , KC_     , KC_     , KC_     , KC_     , KC_     ,         KC_     , KC_LBRKT, KC_RBRKT, KC_     , KC_     , KC_     , KC______,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        KC______, KC______, KC______, KC______, KC______, KC_FRONT, KC______,         KC______, KC_     , KC______, KC______, KC_     , KC_     , KC_
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
    ),
    
    [_FRONT] = LAYOUT_ortho_5x14(
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        KC_FN_00, KC_FN_01, KC_FN_02, KC_FN_03, KC_FN_04, KC_FN_05, KC_     ,         KC_     , KC_FN_06, KC_FN_07, KC_FN_08, KC_FN_09, KC_FN_10, KC_ACL0 ,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        KC_     , KC_     , KC_M_PRV, KC_M_SEL, KC_M_NXT, KC_     , KC_VOLU ,         KC_BTN4 , KC_WH_U , KC_WH_L , KC_MS_U , KC_WH_R , KC_BTN1 , KC_ACL1 ,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        KC______, KC_     , KC_M_BCK, KC_M_PLY, KC_M_FRW, KC_     , KC_VOLD ,         KC_BTN5 , KC_WH_D , KC_MS_L , KC_MS_D , KC_MS_R , KC_BTN2 , KC_ACL2 ,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        KC______, KC_     , KC_     , KC_     , KC_     , KC_     , KC_MUTE ,         KC_     , KC_     , KC_     , KC_     , KC_     , KC_BTN3 , KC______,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        KC______, KC______, KC______, KC______, KC______, KC_     , KC______,         KC______, KC_     , KC______, KC______, KC_     , KC_     , KC_
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
    )
};
