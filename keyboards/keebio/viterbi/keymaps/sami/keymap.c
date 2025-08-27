#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Layers
#define _QWERTY 0
#define _RAISE 1
#define _LOWER 2
#define _FRONT 3

// No-op and transparent aliases
#define KC_ KC_NO
#define _______ KC_TRNS

// Layer access aliases / thumb keys
#define KC_RAISE MO(_RAISE) //LT(_RAISE, KC_SPACE)
#define KC_LOWER MO(_LOWER) //LT(_LOWER, KC_ENTER)
#define KC_FRONT MO(_FRONT)
#define KC_THLSH MT(MOD_LSFT, KC_SPACE)
#define KC_THRSH MT(MOD_RSFT, KC_ENTER)
#define KC_SUPER KC_LGUI
//#define KC_SSUPR MT(MOD_LSFT | MOD_LGUI, KC_LGUI)

// Character aliases
#define KC_CRRNC RALT(KC_3)     // € £
#define KC_LPREN S(KC_8)        // (
#define KC_RPREN S(KC_9)        // )
#define KC_LBRCE RALT(KC_7)     // {
#define KC_RBRCE RALT(KC_0)     // }
#define KC_LBRKT RALT(KC_8)     // [
#define KC_RBRKT RALT(KC_9)     // ]
#define KC_LANGL RALT(S(KC_8))  // <
#define KC_RANGL RALT(S(KC_9))  // >
#define KC_BAR   RALT(KC_NUBS)  // |
#define KC_BKTCK RALT(KC_NUHS)  // `
#define KC_AUMLT RALT(KC_A)     // ä Ä
#define KC_OUMLT RALT(KC_O)     // ö Ö
// Regular Finnish layout safety characters
#define FI_ASTRK S(KC_BSLS)     // *
#define FI_TILDE RALT(KC_RBRC)  // ~

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


/******************************************************************************/
/****************************** CUSTOM KEYCODES *******************************/
/******************************************************************************/

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
    KC_CTQTB,
    KC_ENDER,
    KC_TMXCP,
    
    // Shift-Super key
    KC_SSUPR,
    
    // Email address macro
    KC_EMAIL,
    
    // Install script macro
    KC_INSTLL
};

// Timer for the Shift+Super key
static uint16_t SSUPR_timer;
// If the key is down and if it's held down
static bool SSUPR_down = false;
static bool SSUPR_held = false;


/*!
 * Process custom keycodes.
 */
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (keycode == KC_SSUPR) {
        SSUPR_down = record->event.pressed;
        
        if (SSUPR_down) {
            // Send LGUI
            register_code(KC_LGUI);
            
            // Not held down (yet)
            SSUPR_held = false;
            
            // "Start" timer
            SSUPR_timer = timer_read();
        }
        else {
            // Release super
            unregister_code(KC_LGUI);
            
            if (SSUPR_held) {
                // Key was held down, also release shift
                unregister_code(KC_LSFT);
            }
        }
    }
    else if (record->event.pressed) {
        // Handle other keys
        
        switch(keycode) {
            case KC_CTQTB: {
                // Ctrl+Q Ctrl+Tab
                SEND_STRING(SS_LCTL("q"));
                SEND_STRING(SS_LCTL(SS_TAP(X_TAB)));
                
                return false;
            }
            case KC_ENDER: {
                // End Enter
                SEND_STRING(SS_TAP(X_END));
                SEND_STRING(SS_TAP(X_ENTER));
                
                return false;
            }
            case KC_TMXCP: {
                // Ctrl+B [
                SEND_STRING(SS_LCTL("b"));
                SEND_STRING(SS_RALT(":"));
                
                return false;
            }
            case KC_EMAIL: {
                // sami@kankaristo.fi
                SEND_STRING("sami");
                SEND_STRING(SS_RALT("2"));
                SEND_STRING("kankaristo.fi");
                
                return false;
            }
            case KC_INSTLL: {
                // source <(curl -sL install.wrbl.fi)
                SEND_STRING("source ");
                SEND_STRING(SS_RALT("*"));
                SEND_STRING("*curl /sL install.wrbl.fi(");
                
                return false;
            }
        }
    }
    
    return true;
};


void matrix_scan_user(void) {
    if (SSUPR_down && !SSUPR_held && timer_elapsed(SSUPR_timer) > 200) {
        // The key has been pressed for enough time to be considered "held"
        SSUPR_held = true;
        
        // (Also) send shift
        register_code(KC_LSFT);
    }
}


const key_override_t override_shift_2 = ko_make_basic(
    MOD_MASK_SHIFT, KC_2, RALT(KC_2)
);
/*
const key_override_t override_altgr_2 = ko_make_basic(
    KC_RALT, KC_2, S(KC_2)
);
*/
const key_override_t override_shift_4 = ko_make_basic(
    MOD_MASK_SHIFT, KC_4, RALT(KC_4)
);
const key_override_t override_shift_apostrophe = ko_make_basic(
    MOD_MASK_SHIFT, KC_BACKSLASH, S(KC_2)
);
const key_override_t override_altgr_tilde = ko_make_basic(
    KC_RALT, KC_QUOT, RALT(KC_RBRC)
);
const key_override_t override_altgr_asterisk = ko_make_basic(
    KC_RALT, KC_RBRC, S(KC_BACKSLASH)
);

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
    &override_shift_2,
    //&override_altgr_2,
    &override_shift_4,
    &override_shift_apostrophe,
    &override_altgr_tilde,
    &override_altgr_asterisk
};

/******************************************************************************/
/********************************** KEYMAPS ***********************************/
/******************************************************************************/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // TODO: Dead diaeresis (with a leader key? IDK)
    [_QWERTY] = LAYOUT_ortho_5x14(
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        KC_ESC  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_QUOT ,         KC_MINUS, KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_BSPC ,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        KC_TAB  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , KC_SCLN ,         KC_SLASH, KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_DEL  ,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        KC_SUPER, KC_A    , KC_S    , KC_D    , KC_F    , KC_G    , KC_RBRC ,         KC_DOT  , KC_H    , KC_J    , KC_K    , KC_L    , KC_BSLS , KC_ENTER,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        KC_LSFT , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    , KC_NUBS ,         KC_COMMA, KC_N    , KC_M    , KC_HOME , KC_END  , KC_UP   , KC_RSFT ,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        KC_LCTL , KC_RALT , KC_LALT , KC_LCTL , KC_SSUPR, KC_RAISE, KC_SPACE,         KC_RSFT , KC_LOWER, KC_LALT , KC_RCTL , KC_LEFT , KC_DOWN , KC_RIGHT
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
    ),
    
    [_RAISE] = LAYOUT_ortho_5x14(
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        KC_FN_00, KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , _______ ,         KC_PSCR , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  ,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        KC_PRVTB, KC_CTQTB, KC_M_PRV, KC_M_SEL, KC_M_NXT, _______ , KC_VOLU ,         KC_SCRL , KC_PGUP , KC_HOME , KC_UP   , KC_END  , _______ , KC_F12  ,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        _______ , _______ , KC_M_BCK, KC_M_PLY, KC_M_FRW, _______ , KC_VOLD ,         KC_PAUSE, KC_PGDN , KC_LEFT , KC_DOWN , KC_RIGHT, _______ , KC_ENDER,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        _______ , _______ , _______ , KC_CTINS, KC_SHINS, KC_TMXCP, KC_MUTE ,         KC_INS  , _______ , _______ , _______ , _______ , KC_PGUP , _______ ,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        _______ , _______ , _______ , _______ , _______ , _______ , _______ ,         _______ , KC_FRONT, _______ , _______ , KC_HOME , KC_PGDN , KC_END
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
    ),
    
    [_LOWER] = LAYOUT_ortho_5x14(
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        _______ , KC_MC_01, KC_MC_02, KC_MC_03, KC_MC_04, KC_MC_05, FI_TILDE,         _______ , KC_MC_06, KC_MC_07, KC_MC_08, KC_MC_09, KC_MC_10, _______ ,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        _______ , _______ , _______ , KC_CRRNC, _______ , _______ , KC_BAR  ,         KC_BAR  , KC_LPREN, KC_RPREN, _______ , KC_OUMLT, _______ , _______ ,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        _______ , KC_AUMLT, _______ , _______ , _______ , _______ , FI_ASTRK,         _______ , KC_LBRCE, KC_RBRCE, KC_LANGL, KC_RANGL, KC_BKTCK, _______ ,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        _______ , _______ , _______ , _______ , _______ , _______ , _______ ,         _______ , KC_LBRKT, KC_RBRKT, _______ , _______ , _______ , _______ ,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        _______ , _______ , _______ , _______ , _______ , KC_FRONT, _______ ,         _______ , _______ , _______ , _______ , _______ , _______ , _______
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
    ),
    
    [_FRONT] = LAYOUT_ortho_5x14(
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        KC_FN_00, KC_FN_01, KC_FN_02, KC_FN_03, KC_FN_04, KC_FN_05, KC_EMAIL,         _______ , KC_FN_06, KC_FN_07, KC_FN_08, KC_FN_09, KC_FN_10, KC_ACL0 ,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        _______ , _______ , KC_M_PRV, KC_M_SEL, KC_M_NXT, _______ , KC_VOLU ,         KC_BTN4 , KC_WH_U , KC_WH_L , KC_MS_U , KC_WH_R , KC_BTN1 , KC_ACL1 ,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        _______ , _______ , KC_M_BCK, KC_M_PLY, KC_M_FRW, _______ , KC_VOLD ,         KC_BTN5 , KC_WH_D , KC_MS_L , KC_MS_D , KC_MS_R , KC_BTN2 , KC_ACL2 ,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        _______ ,KC_INSTLL, _______ , _______ , _______ , _______ , KC_MUTE ,         _______ , _______ , _______ , _______ , _______ , KC_BTN3 , _______ ,
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
        _______ , _______ , _______ , _______ , _______ , _______ , _______ ,         _______ , _______ , _______ , _______ , _______ , _______ , _______
        //------+---------+---------+---------+---------+---------+---------|        |--------+---------+---------+---------+---------+---------+---------|
    )
};
