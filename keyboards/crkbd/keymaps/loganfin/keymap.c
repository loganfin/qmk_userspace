#include QMK_KEYBOARD_H

// Notes:
// - Try to minimize inner column and pinky column use in layers other than the
// alpha layer
// - Maybe swap to thumb key layer switching since we have the repeat key (what
// does this mean?)
//   - Numpad plus nav via left thumb
//   - Symbol via right thumb?
//
// TODO:
// - [x] Shift isn't del during capsword, or make del a different key
// - [x] Change shifted forms of , and . to / and ?
// - [x] Create mouse layer for use with trackpoint
// - [x] Find a good place for home, end, pg_up, pg_dn
//      - For arrow keys, maybe ignore the position of the real hjkl keys
// - [ ] Numword
// - [ ] Investigate the usefulness of the alternatie repeat key as a "magic"
// key
// - [x] Disable shift on symbol layer keys and number layer
// - [ ] Setup trackpoint
// - [ ] Find better places for the MOUSE, CONTROL, and FUNCTION keys
// - [ ] Setup transport so slave can know when capsword is enabled?
// - [ ] Combos on the number layer for vim movements (10 j, 8 k)
// - [ ] Add combos for markdown (```)

typedef enum {
    _Alpha,
    _Symbol,
    _Number,
    _Navigation,
    _Function,
    _Mouse,
    _Control,
} LayerNames;

////////////////////////////////////////////////////////////////////////////////
// Key overrides

// key_override_t const shift_delete_override = ko_make_basic(MOD_MASK_SHIFT,
// KC_BSPC, KC_DEL);
key_override_t const shift_comma_override =
    ko_make_basic(MOD_MASK_SHIFT, KC_COMMA, KC_SLSH);
key_override_t const shift_dot_override =
    ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_QUES);

// The shifted versions of these keys are already available on the symbol
// layer, so they don't need a shifted version.
key_override_t const shift_grave_override =
    ko_make_basic(MOD_MASK_SHIFT, KC_GRV, KC_GRV);
key_override_t const shift_minus_override =
    ko_make_basic(MOD_MASK_SHIFT, KC_MINS, KC_MINS);
key_override_t const shift_left_bracket_override =
    ko_make_basic(MOD_MASK_SHIFT, KC_LBRC, KC_LBRC);
key_override_t const shift_right_bracket_override =
    ko_make_basic(MOD_MASK_SHIFT, KC_RBRC, KC_RBRC);
key_override_t const shift_slash_override =
    ko_make_basic(MOD_MASK_SHIFT, KC_SLSH, KC_SLSH);
key_override_t const shift_back_slash_override =
    ko_make_basic(MOD_MASK_SHIFT, KC_BSLS, KC_BSLS);

key_override_t const shift_one_override =
    ko_make_basic(MOD_MASK_SHIFT, KC_1, KC_1);
key_override_t const shift_two_override =
    ko_make_basic(MOD_MASK_SHIFT, KC_2, KC_2);
key_override_t const shift_three_override =
    ko_make_basic(MOD_MASK_SHIFT, KC_3, KC_3);
key_override_t const shift_four_override =
    ko_make_basic(MOD_MASK_SHIFT, KC_4, KC_4);
key_override_t const shift_five_override =
    ko_make_basic(MOD_MASK_SHIFT, KC_5, KC_5);
key_override_t const shift_six_override =
    ko_make_basic(MOD_MASK_SHIFT, KC_6, KC_6);
key_override_t const shift_seven_override =
    ko_make_basic(MOD_MASK_SHIFT, KC_7, KC_7);
key_override_t const shift_eight_override =
    ko_make_basic(MOD_MASK_SHIFT, KC_8, KC_8);
key_override_t const shift_nine_override =
    ko_make_basic(MOD_MASK_SHIFT, KC_9, KC_9);
key_override_t const shift_zero_override =
    ko_make_basic(MOD_MASK_SHIFT, KC_0, KC_0);

key_override_t const* key_overrides[] = {
    &shift_comma_override,
    &shift_dot_override,
    &shift_grave_override,
    &shift_minus_override,
    &shift_left_bracket_override,
    &shift_right_bracket_override,
    &shift_slash_override,
    &shift_back_slash_override,
    &shift_one_override,
    &shift_two_override,
    &shift_three_override,
    &shift_four_override,
    &shift_five_override,
    &shift_six_override,
    &shift_seven_override,
    &shift_eight_override,
    &shift_nine_override,
    &shift_zero_override,
};

////////////////////////////////////////////////////////////////////////////////
// Tap dance
// TODO: does this need the typedef?
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP,
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD,
} TapDanceState;

typedef struct {
    bool is_press_action;
    TapDanceState state;
} TapDanceTap;

static TapDanceTap shift_tap_state = {
    .is_press_action = true,
    .state = TD_NONE,
};

// static TapDanceTap hash_tap_state = {
//     .is_press_action = true,
//     .state           = TD_NONE,
// };

TapDanceState current_dance(tap_dance_state_t* state);

void shift_tap_dance_finished(tap_dance_state_t* state, void* user_data);
void shift_tap_dance_reset(tap_dance_state_t* state, void* user_data);
// void hash_tap_dance_finished(tap_dance_state_t* state, void* user_data);
// void hash_tap_dance_reset(tap_dance_state_t* state, void* user_data);

typedef enum {
    TD_SFT_CAPS = 0,
    // TD_HASH_NUM = 1,
} TapDanceAction;

tap_dance_action_t tap_dance_actions[] = {
    [TD_SFT_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(
        NULL,
        shift_tap_dance_finished,
        shift_tap_dance_reset
    ),
    // Is this tap dance even useful?
    // [TD_HASH_NUM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,
    // hash_tap_dance_finished, hash_tap_dance_reset),
};

////////////////////////////////////////////////////////////////////////////////
// Home-row macros

#define HR_R LGUI_T(KC_R)
#define HR_T LALT_T(KC_T)
#define HR_S LCTL_T(KC_S)

#define HR_H RCTL_T(KC_H)
#define HR_A RALT_T(KC_A)
#define HR_E RGUI_T(KC_E)

////////////////////////////////////////////////////////////////////////////////
// Thumb cluster macros

#define TH_ENT LT(_Navigation, KC_ENT)
#define TH_SFT TD(TD_SFT_CAPS)
#define TH_REP QK_REP
#define TH_SPC KC_SPC

////////////////////////////////////////////////////////////////////////////////
// Non-thumb key layer switch macros

#define FUNCTION MO(_Function)
#define CONTROL MO(_Control)
#define MOUSE MO(_Mouse)

// #define NUM_HASH TD(TD_HASH_NUM)
#define NUM_HASH KC_HASH

#define SYM MO(_Symbol)

#define SYM_C LT(_Symbol, KC_C)
#define SYM_F LT(_Symbol, KC_F)
#define NUM_M LT(_Number, KC_M)

////////////////////////////////////////////////////////////////////////////////
// Combos

uint16_t const PROGMEM backspace_combo[] = {HR_H, HR_A, COMBO_END};
uint16_t const PROGMEM escape_combo[] = {HR_T, HR_S, COMBO_END};
uint16_t const PROGMEM tab_combo[] = {HR_R, HR_T, COMBO_END};
uint16_t const PROGMEM delete_combo[] = {HR_A, HR_E, COMBO_END};

combo_t key_combos[] = {
    COMBO(backspace_combo, KC_BSPC),
    COMBO(escape_combo, KC_ESC),
    COMBO(tab_combo, KC_TAB),
    COMBO(delete_combo, KC_DEL),
};

////////////////////////////////////////////////////////////////////////////////
// Layers
// clang-format off

uint16_t const PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // ,-----------------------------------------------.             ,-----------------------------------------------.
    // |       |   B   |   L   |   D   |   W   |   V   |             |   Z   |   Y   |   O   |   U   |  ,//  |       |
    // |-------+-------+-------+-------+-------+-------|             |-------+-------+-------+-------+-------+-------|
    // |       |   N   |   R   |   T   |   S   |   G   |             |   P   |   H   |   A   |   E   |   I   |       |
    // |-------+-------+-------+-------+-------+-------|             |-------+-------+-------+-------+-------+-------|
    // |       |   Q   |   X   |   M   |   C   |   J   |             |   K   |   F   |  '/"  |  ;/:  |  ./?  |       |
    // `-----------------------------------------------'             `-----------------------------------------------'
    //                              ,-----------------------.   ,-----------------------.
    //                              |       | enter | shift |   | repeat| space |       |
    //                              `-----------------------'   `-----------------------'

    [_Alpha] = LAYOUT_split_3x6_3(
        KC_NO, KC_B, KC_L, KC_D, KC_W, KC_V,                        KC_Z, KC_Y, KC_O, KC_U, KC_COMM, KC_NO,
        FUNCTION, KC_N, HR_R, HR_T, HR_S, KC_G,                        KC_P, HR_H, HR_A, HR_E, KC_I, MOUSE,
        CONTROL, KC_Q, KC_X, NUM_M, SYM_C, KC_J,                      KC_K, SYM_F, KC_QUOT, KC_SCLN, KC_DOT, KC_NO,
                                KC_NO, TH_ENT, TH_SFT,      TH_REP, TH_SPC, TH_SFT
    ),

    [_Symbol] = LAYOUT_split_3x6_3(
        KC_NO, KC_GRV, KC_LABK, KC_RABK, KC_MINS, KC_NO,            KC_NO, KC_AMPR, KC_LCBR, KC_RCBR, KC_DLR, KC_NO,
        KC_NO, KC_EXLM, KC_ASTR, KC_SLSH, KC_EQL, KC_UNDS,          KC_NO, KC_CIRC, KC_LPRN, KC_RPRN, KC_PERC, KC_NO,
        KC_NO, KC_TILD, KC_PLUS, NUM_HASH, KC_PIPE, KC_NO,           KC_NO, KC_AT, KC_LBRC, KC_RBRC, KC_BSLS, KC_NO,
                                KC_NO, TH_ENT, TH_SFT,        TH_REP, TH_SPC, KC_NO
    ),

    // [_Number] = LAYOUT_split_3x6_3(
    //     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_7, KC_8, KC_9, KC_NO, KC_NO,
    //     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_4, KC_5, KC_6, KC_0, KC_NO,
    //     KC_NO, KC_NO, KC_NO, KC_NO, SYM, KC_NO,                  KC_NO, KC_1, KC_2, KC_3, KC_NO, KC_NO,
    //                             KC_NO, TH_ENT, TH_SFT,        TH_REP, TH_SPC, KC_NO
    // ),

    [_Number] = LAYOUT_split_3x6_3(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_7, KC_8, KC_9, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_4, KC_5, KC_6, KC_DOT, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, SYM, KC_NO,                  KC_NO, KC_1, KC_2, KC_3, KC_NO, KC_NO,
                                KC_NO, TH_ENT, TH_SFT,        KC_0, TH_SPC, KC_NO
    ),

    [_Navigation] = LAYOUT_split_3x6_3(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_NO,
        KC_NO, KC_NO, KC_LGUI, KC_LALT, KC_LCTL, KC_NO,             KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                KC_NO, KC_NO, KC_NO,        KC_NO, KC_NO, KC_NO
    ),

    // TODO: How do we get here?
    [_Function] = LAYOUT_split_3x6_3(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_F7, KC_F8, KC_F9, KC_F10, KC_NO,
        KC_NO, KC_NO, KC_LGUI, KC_LALT, KC_LCTL, KC_NO,             KC_NO, KC_F4, KC_F5, KC_F6, KC_F11, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_F1, KC_F2, KC_F3, KC_F12, KC_NO,
                                KC_NO, KC_NO, KC_NO,        KC_NO, KC_NO, KC_NO
    ),

    // [_Mouse] = LAYOUT_split_3x6_3(
    //     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    //     KC_NO, KC_NO, KC_NO, MS_BTN1, MS_BTN2, KC_NO,               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    //     KC_NO, KC_NO, KC_NO, MS_WHLD, MS_WHLU, KC_NO,               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    //                             KC_NO, KC_NO, KC_NO,        KC_NO, KC_NO, KC_NO
    // ),

    // TODO: How do we get here?
    //      - When the trackpoint is touched
    //      - Also via a keyboard layer switch
    //      - We might want to keep a shift key in here for shift scrolling
    [_Mouse] = LAYOUT_split_3x6_3(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, KC_NO,           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                KC_NO, MS_BTN1, MS_BTN2,        KC_NO, KC_NO, KC_NO
    ),

    // TODO: How do we get here?
    [_Control] = LAYOUT_split_3x6_3(
        QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                 KC_NO, RM_HUED, RM_SATD, RM_SATU, RM_HUEU, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, RM_PREV, RM_VALD, RM_VALU, RM_NEXT, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, RM_SPDD, RM_SPDU, RM_TOGG, KC_NO, KC_NO,
                                KC_NO, KC_NO, KC_NO,        KC_NO, KC_NO, KC_NO
    ),

    // [_Symbol] = LAYOUT_split_3x6_3(
    //     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    //     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    //     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    //                             KC_NO, KC_NO, KC_NO,        KC_NO, KC_NO, KC_NO
    // ),
};

// clang-format on

////////////////////////////////////////////////////////////////////////////////
// Tap dance implementation

TapDanceState current_dance(tap_dance_state_t* state)
{
    if (state->count == 1) {
        if (state->pressed) {
            return TD_SINGLE_HOLD;
        } else {
            return TD_SINGLE_TAP;
        }
    } else if (state->count == 2) {
        if (state->pressed) {
            return TD_DOUBLE_HOLD;
        } else {
            return TD_DOUBLE_TAP;
        }
    } else {
        return TD_UNKNOWN;
    }
}

void shift_tap_dance_finished(tap_dance_state_t* state, void* user_data)
{
    shift_tap_state.state = current_dance(state);

    switch (shift_tap_state.state) {
    case TD_SINGLE_TAP:
        set_oneshot_mods(MOD_BIT(KC_LSFT));
        break;
    case TD_SINGLE_HOLD:
        register_code(KC_LSFT);
        break;
    case TD_DOUBLE_TAP:
        caps_word_on();
        break;
    default:
        break;
    }
}

void shift_tap_dance_reset(tap_dance_state_t* state, void* user_data)
{
    switch (shift_tap_state.state) {
    case TD_SINGLE_HOLD:
        clear_oneshot_mods();
        unregister_code(KC_LSFT);
        break;
    default:
        break;
    }

    shift_tap_state.state = TD_NONE;
}

// void hash_tap_dance_finished(tap_dance_state_t* state, void* user_data) {
//     hash_tap_state.state = current_dance(state);
//
//     switch (hash_tap_state.state) {
//         case TD_SINGLE_TAP:
//             tap_code16(KC_HASH);
//             break;
//         case TD_SINGLE_HOLD:
//             layer_on(_Number);
//             break;
//         default:
//             break;
//     }
// }
//
// void hash_tap_dance_reset(tap_dance_state_t* state, void* user_data) {
//     switch (hash_tap_state.state) {
//         case TD_SINGLE_HOLD:
//             layer_off(_Number);
//             break;
//         default:
//             break;
//     }
//
//     hash_tap_state.state = TD_NONE;
// }

////////////////////////////////////////////////////////////////////////////////
// Combo implementation

#ifdef COMBO_MUST_TAP_PER_COMBO
bool get_combo_must_tap(uint16_t combo_index, combo_t* combo)
{
    // If you want *all* combos, that have Mod-Tap/Layer-Tap/Momentary keys in
    // its chord, to be tap-only, this is for you:
    uint16_t key;
    uint8_t idx = 0;
    while ((key = pgm_read_word(&combo->keys[idx])) != COMBO_END) {
        switch (key) {
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:
            return true;
        }
        idx += 1;
    }
    return false;
}
#endif

////////////////////////////////////////////////////////////////////////////////
// Caps word

bool caps_word_press_user(uint16_t keycode)
{
    switch (keycode) {
    // Keycodes that continue Caps Word, with shift applied.
    case KC_A ... KC_Z:
        add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
        return true;

    // Keycodes that continue Caps Word, without shifting.
    case KC_MINS:
        return true;
    case KC_1 ... KC_0:
    case KC_BSPC:
    case KC_DEL:
    case KC_UNDS:
        return true;

    default:
        return false; // Deactivate Caps Word.
    }
}

void caps_word_set_user(bool active)
{
    static bool disable_rgb_on_inactive = false;

    if (active) {
        if (!rgb_matrix_is_enabled()) {
            disable_rgb_on_inactive = true;
            rgb_matrix_enable();
        } else {
            disable_rgb_on_inactive = false;
        }
    } else {
        if (disable_rgb_on_inactive) {
            rgb_matrix_disable();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// LED implementation

bool rgb_matrix_indicators_user()
{
    if (is_caps_word_on()) {
        hsv_t hsv = {0, 0, 120};
        rgb_t rgb = hsv_to_rgb(hsv);

        // This will only light up the master side since the slave side caps
        // word status isn't known on the slave controller.
        rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);

        return true;
    } else if (get_oneshot_mods() & MOD_MASK_SHIFT) {
        hsv_t hsv = {191, 255, 120};
        rgb_t rgb = hsv_to_rgb(hsv);

        rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);
        return true;
    } else {
        return false;
    }
}

////////////////////////////////////////////////////////////////////////////////
// OLED display

#ifdef OLED_ENABLE
bool oled_task_user(void)
{
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
    case _Alpha:
        oled_write_P(PSTR("Alpha\n"), false);
        break;
    case _Symbol:
        oled_write_P(PSTR("Symbol\n"), false);
        break;
    case _Number:
        oled_write_P(PSTR("Number\n"), false);
        break;
    case _Navigation:
        oled_write_P(PSTR("Navigation\n"), false);
        break;
    case _Function:
        oled_write_P(PSTR("Function\n"), false);
        break;
    case _Mouse:
        oled_write_P(PSTR("Mouse\n"), false);
        break;
    case _Control:
        oled_write_P(PSTR("Control\n"), false);
        break;
    default:
        // Or use the write_ln shortcut over adding '\n' to the end of your
        // string
        oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

    return false;
}
#endif

////////////////////////////////////////////////////////////////////////////////
// Debug code

// #define MY_DEBUG
#ifdef MY_DEBUG

void keyboard_post_init_user()
{
    debug_enable = true;
    debug_matrix = true;
    debug_keyboard = true;
}

#endif // MY_DEBUG
