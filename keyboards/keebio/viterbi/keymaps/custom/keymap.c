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


/******************************************************************************/
/*************************** TAP DANCE BOILERPLATE ****************************/
/******************************************************************************/

typedef struct {
    bool is_press_action;
    int state;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD = 2,
    DOUBLE_TAP = 3,
    DOUBLE_HOLD = 4,
    DOUBLE_SINGLE_TAP = 5, // Send two single taps
    TRIPLE_TAP = 6,
    TRIPLE_HOLD = 7
};

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //Assumes no one is trying to type the same letter three times (at least not quickly).
  //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}


/******************************************************************************/
/************************** TAP DANCE KEY FUNCTIONS ***************************/
/******************************************************************************/

//instanalize an instance of 'tap' for the 'x' tap dance.
static tap TD_SSUPR_state = {
  .is_press_action = true,
  .state = 0
};

void TD_SSUPR_finished (qk_tap_dance_state_t* state, void* user_data) {
    TD_SSUPR_state.state = cur_dance(state);
    
    switch (TD_SSUPR_state.state) {
        case SINGLE_TAP: {
            register_code(KC_LGUI);
            break;
        }
        case SINGLE_HOLD: {
            register_code(KC_LSFT);
            register_code(KC_LGUI);
            break;
        }
        /*/
        case DOUBLE_TAP: {
            register_code(KC_ESC);
            break;
        }
        case DOUBLE_HOLD: {
            register_code(KC_LALT);
            break;
        }
        case DOUBLE_SINGLE_TAP: {
            register_code(KC_X);
            unregister_code(KC_X);
            register_code(KC_X);
            break;
        }
        //*/
        //Last case is for fast typing. Assuming your key is `f`:
        //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
    }
}


void TD_SSUPR_reset(qk_tap_dance_state_t* state, void* user_data) {
    switch (TD_SSUPR_state.state) {
        case SINGLE_TAP: {
            unregister_code(KC_LGUI);
            break;
        }
        case SINGLE_HOLD: {
            unregister_code(KC_LSFT);
            unregister_code(KC_LGUI);
            break;
        }
        /*
        case DOUBLE_TAP: {
            unregister_code(KC_ESC);
            break;
        }
        case DOUBLE_HOLD: {
            unregister_code(KC_LALT);
            unregister_code(KC_X);
            break;
        }
        case DOUBLE_SINGLE_TAP: {
            unregister_code(KC_X);
            break;
        }
        //*/
    }
    
    TD_SSUPR_state.state = 0;
}


/******************************************************************************/
/******************************* TAP DANCE KEYS *******************************/
/******************************************************************************/

// Tap dance enums
enum {
    TD_SSUPR = 0
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_SSUPR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, TD_SSUPR_finished, TD_SSUPR_reset)
};

// Tap dance keys
#define KC_SSUPR TD(TD_SSUPR)


/******************************************************************************/
/********************************** KEYMAPS ***********************************/
/******************************************************************************/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // TODO: Dead diaeresis (with a leader key? IDK)
    [_QWERTY] = LAYOUT_kc(
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        ESC  , 1    , 2    , 3    , 4    , 5    , GRAVE,         MINUS, 6    , 7    , 8    , 9    , 0    , BSPC ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        TAB  , Q    , W    , E    , R    , T    , RBRC ,         EQUAL, Y    , U    , I    , O    , P    , DEL  ,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        SUPER, A    , S    , D    , F    , G    , LBRC ,         DOT  , H    , J    , K    , L    , BSLS , ENTER,
        //---+------+------+------+------+------+------|        |-----+------+------+------+------+------+------|
        LSFT , Z    , X    , C    , V    , B    , ENTER,         COMMA, N    , M    , HOME , END  , UP   , RSFT ,
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
        _____,      ,      , CTINS, SHINS,      , MUTE ,         INS  ,      ,      ,      ,      , PGUP , _____,
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
        FN_00, FN_01, FN_02, FN_03, FN_04, FN_05,      ,              , FN_06, FN_07, FN_08, FN_09, FN_10, ACL0 ,
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
