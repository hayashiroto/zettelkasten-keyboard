/* Copyright 2020 e3w2q
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

#include "paw3204.h"
#include "pointing_device.h"

extern keymap_config_t keymap_config;

extern uint8_t is_master;

bool isScrollMode;

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  SEND_00 = SAFE_RANGE,
  SEND_000,
  // 884 add
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  KC_MBTN1,
  KC_MBTN2,
  KC_MBTN3,
  KC_SCROLL
};
// レイヤー定義を追加
enum layer_names {
    _BASE,   // デフォルトレイヤー
    _LOWER,  // 下レイヤー
    _RAISE,  // 上レイヤー
    _TB      // トラックボールレイヤー
};

// PAW3204 sensor pins
#define PAW3204_SCLK_PIN D0  // クロックピンの定義
#define PAW3204_SDIO_PIN D1  // データピンの定義


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Default Layer
   *  Master Side (USB Cable Connected Side)
   *  ,-----------------------------------------
   *  |MO(1) PtSc  Esc   F1   F2   F3   F4   F5
   *  |MO(2)  Ins Hank    1    2    3    4    5
   *  |MO(3) Home  Tab    Q    W    E    R    T
   *  |MO(4)  End Caps    A    S    D    F    G
   *  |MO(5) PgUp Shft    Z    X    C    V    B
   *  |MO(6) PgDn Ctrl  GUI  Alt MHEN Spce Spce
   *  `-----------------------------------------
   *  Slave Side (USB Cable Not Connected Side)
   *  ,-----------------------------------------
   *  |   F6   F7   F8   F9  F10  F11  F12  Del
   *  |    6    7    8    9    0    -    =   BS
   *  |    Y    U    I    O    P    [    ]    \
   *  |    H    J    K    L    ;    ' Entr PgUp
   *  |    N    M    ,    .    / Shft   Up PgDn
   *  | Spce  HEN KANA  Alt Ctrl Left Down Rght
   *  `-----------------------------------------
   */

  [_BASE] = LAYOUT( /* Base */
    MO(1),    KC_PSCR,  KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,
    MO(2),    KC_INS,   KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,
    MO(3),    KC_HOME,  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,
    MO(4),    KC_END,   KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,
    MO(5),    KC_PGUP,  KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,
    MO(6),    KC_PGDN,  KC_LCTL,  KC_LGUI,  KC_LALT,  KC_MHEN,  KC_SPC,   KC_SPC,

    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,
    KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,
    KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,
    KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,   KC_PGUP,
    KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_PGDN,
    KC_SPC,   KC_HENK,  KC_KANA,  KC_RALT,  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT
  ),

  [_RAISE] = LAYOUT(
    _______,  RGB_TOG,  RGB_MOD,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    _______,  RGB_HUI,  RGB_SAI,  RGB_VAI,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    _______,  RGB_HUD,  RGB_SAD,  RGB_VAD,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    _______,  EEP_RST,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    _______,  RESET,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,

    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
  ),

  [_LOWER] = LAYOUT(
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,

    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
  ),
  [_TB] = LAYOUT(
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,

    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  report_mouse_t currentReport = {};
  switch (keycode) {
    case SEND_00:
      if (record->event.pressed) {
        // when keycode SEND_00 is pressed
        SEND_STRING("00");
      } else {
        // when keycode SEND_00 is released
      }
      break;
    case SEND_000:
      if (record->event.pressed) {
        // when keycode SEND_000 is pressed
        //SEND_STRING("000" SS_TAP(X_ENTER));
        SEND_STRING("000");
      } else {
        // when keycode SEND_000 is released
      }
      break;
    case KC_MBTN1:
      currentReport = pointing_device_get_report();
      if (record->event.pressed) {
        currentReport.buttons |= MOUSE_BTN1;
      }
      else {
        currentReport.buttons &= ~MOUSE_BTN1;
      }
      pointing_device_set_report(currentReport);
      return false;
    case KC_MBTN2:
      currentReport = pointing_device_get_report();
      if (record->event.pressed) {
        currentReport.buttons |= MOUSE_BTN2;
      }
      else {
        currentReport.buttons &= ~MOUSE_BTN2;
      }
      pointing_device_set_report(currentReport);
      return false;
    case KC_MBTN3:
      currentReport = pointing_device_get_report();
      if (record->event.pressed) {
        currentReport.buttons |= MOUSE_BTN3;
      }
      else {
        currentReport.buttons &= ~MOUSE_BTN3;
      }
      pointing_device_set_report(currentReport);
      return false;
    case KC_SCROLL:
      if (record->event.pressed) {
        isScrollMode = true;
        dprint("scroll ON\n");
      }
      else {
        isScrollMode = false;
        dprint("scroll OFF\n");
      }
      return false;
  }
  return true;
}

void matrix_init_user(void) {
    init_paw3204_custom();
    setPinInputHigh(D3);
}

void keyboard_post_init_user() {
    debug_enable = true;
    debug_mouse = true;
}

void led_set_user(uint8_t usb_led) {

}

void matrix_scan_user(void) {
    static int  cnt;
    static bool paw_ready;
    static int  tb_layer;
    static int8_t scroll_remainder_x = 0;
    static int8_t scroll_remainder_y = 0;

    // レイヤーチェックの前にカウンタ処理
    cnt++;

    // トラックボールレイヤーの状態を確認
    if (cnt % 50 == 0) {
        uint8_t pid = read_pid_paw3204_custom();
        if (pid == 0x30) {
            dprint("paw3204 OK\n");
            paw_ready = true;
        } else {
            dprintf("paw3204 NG:%d\n", pid);
            paw_ready = false;
        }

        if (readPin(D3) == 1) {
            if (tb_layer == 0) {
                dprint("tb layer on\n");
                layer_on(_TB);
                tb_layer = 1;
            }
        } else {
            if (tb_layer == 1) {
                layer_off(_TB);
                dprint("tb layer off\n");
                tb_layer = 0;
            }
        }
    }

    // センサーが準備できていない場合は処理しない
    if (!paw_ready) {
        return;
    }

    uint8_t stat;
    int8_t x, y;

    // センサーからの読み取り
    read_paw3204_custom(&stat, &x, &y);

    // モーションデータが無効な場合は処理しない
    if (!(stat & 0x80)) {
        return;
    }

    // 現在のモードを確認
    isScrollMode = layer_state_is(_TB);

    // 新しいレポートを作成（ゼロクリア）
    report_mouse_t mouse_rep = {0};
    
    // 現在のボタン状態のみを保持
    mouse_rep.buttons = pointing_device_get_report().buttons;

    // 感度設定
    const float move_sensitivity = 3.5;    // カーソル移動時の感度
    const float scroll_sensitivity = 0.7;  // スクロール時の感度（少し下げる）
    const int scroll_interval = 5;         // スクロール更新間隔（小さくして滑らかに）

    if (isScrollMode) {
        // スクロールモード時はカーソル移動を完全に無効化
        mouse_rep.x = 0;
        mouse_rep.y = 0;

        // スクロール値の計算と累積
        scroll_remainder_x += (int8_t)(x * scroll_sensitivity);
        scroll_remainder_y += (int8_t)(y * scroll_sensitivity);

        // スクロール更新タイミング
        if (cnt % scroll_interval == 0) {
            // 水平スクロール
            if (abs(scroll_remainder_x) >= 1) {
                mouse_rep.v = -scroll_remainder_x;
                scroll_remainder_x = 0;
            }
            
            // 垂直スクロール
            if (abs(scroll_remainder_y) >= 1) {
                mouse_rep.h = -scroll_remainder_y;
                scroll_remainder_y = 0;
            }
        }
    } else {
        // カーソルモード: スクロールは完全に無効
        mouse_rep.v = 0;
        mouse_rep.h = 0;
        
        // スクロールの残り値をリセット
        scroll_remainder_x = 0;
        scroll_remainder_y = 0;
        
        // カーソル移動値の設定
        mouse_rep.x = (int8_t)(x * move_sensitivity);
        mouse_rep.y = (int8_t)(y * move_sensitivity);
    }

    // レポートの送信
    pointing_device_set_report(mouse_rep);
}
