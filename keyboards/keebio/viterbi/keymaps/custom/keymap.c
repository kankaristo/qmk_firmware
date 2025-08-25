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
//#define KC_SSUPR MT(MOD_LSFT | MOD_LGUI, KC_LGUI)

// Character aliases
#define KC_CRRNC RALT(KC_3)             // € £
#define KC_LPREN S(KC_8)                // (
#define KC_RPREN S(KC_9)                // )
#define KC_LBRCE RALT(KC_7)             // {
#define KC_RBRCE RALT(KC_0)             // }
#define KC_LBRKT RALT(KC_8)             // [
#define KC_RBRKT RALT(KC_9)             // ]
#define KC_LANGL RALT(S(KC_8))          // <
#define KC_RANGL RALT(S(KC_9))          // >
#define KC_BAR   RALT(KC_NONUS_BSLASH)  // |
#define KC_BKTCK RALT(KC_NONUS_HASH)    // `
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
    KC_INSTALL
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
                SEND_STRING(SS_LCTRL("q"));
                SEND_STRING(SS_LCTRL(SS_TAP(X_TAB)));
                
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
                SEND_STRING(SS_LCTRL("b"));
                SEND_STRING(SS_RALT(":"));
                
                return false;
            }
            case KC_EMAIL: {
                // sami@kankaristo.fi
                SEND_STRING("sami@kankaristo.fi");
                
                return false;
            }
            case KC_INSTALL: {
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


/******************************************************************************/
/********************************** KEYMAPS ***********************************/
/******************************************************************************/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // TODO: Dead diaeresis (with a leader key? IDK)
    [_QWERTY] = LAYOUT_kc(
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        ESC  , 1    , 2    , 3    , 4    , 5    , QUOT ,         MINUS, 6    , 7    , 8    , 9    , 0    , BSPC ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        TAB  , Q    , W    , E    , R    , T    , RBRC ,         SLASH, Y    , U    , I    , O    , P    , DEL  ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        SUPER, A    , S    , D    , F    , G    , SCLN ,         DOT  , H    , J    , K    , L    , BSLS , ENTER,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        LSFT , Z    , X    , C    , V    , B    , NUBS ,         COMMA, N    , M    , HOME , END  , UP   , RSFT ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        LCTRL, RALT , LALT , LCTRL, SSUPR, RAISE, SPACE,         RSFT , LOWER, LALT , RCTRL, LEFT , DOWN , RIGHT
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
    ),
    
    [_RAISE] = LAYOUT_kc(
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        FN_00, F1   , F2   , F3   , F4   , F5   ,      ,         PSCR , F6   , F7   , F8   , F9   , F10  , F11  ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        PRVTB, CTQTB, M_PRV, M_SEL, M_NXT,      , VOLU ,         SLCK , PGUP , HOME , UP   , END  ,      , F12  ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        _____,      , M_BCK, M_PLY, M_FRW,      , VOLD ,         PAUSE, PGDN , LEFT , DOWN , RIGHT,      , ENDER,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        _____,      ,      , CTINS, SHINS, TMXCP, MUTE ,         INS  ,      ,      ,      ,      , PGUP , _____,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        _____, _____, _____, _____, _____,      , _____,         _____, FRONT, _____, _____, HOME , PGDN , END
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
    ),
    
    [_LOWER] = LAYOUT_kc(
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
             , MC_01, MC_02, MC_03, MC_04, MC_05,      ,              , MC_06, MC_07, MC_08, MC_09, MC_10,      ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
             ,      ,      , CRRNC,      ,      , BAR  ,         BAR  , LPREN, RPREN,      , OUMLT,      ,      ,
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
        FN_00, FN_01, FN_02, FN_03, FN_04, FN_05, EMAIL,              , FN_06, FN_07, FN_08, FN_09, FN_10, ACL0 ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
             ,      , M_PRV, M_SEL, M_NXT,      , VOLU ,         BTN4 , WH_U , WH_L , MS_U , WH_R , BTN1 , ACL1 ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        _____,      , M_BCK, M_PLY, M_FRW,      , VOLD ,         BTN5 , WH_D , MS_L , MS_D , MS_R , BTN2 , ACL2 ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        _____,INSTALL,     ,      ,      ,      , MUTE ,              ,      ,      ,      ,      , BTN3 , _____,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        _____, _____, _____, _____, _____,      , _____,         _____,      , _____, _____,      ,      ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
    )
};
