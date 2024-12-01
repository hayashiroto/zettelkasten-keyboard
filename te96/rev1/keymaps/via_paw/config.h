/* Copyright 2019 e3w2q
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

#pragma once

// place overrides here
#define DYNAMIC_KEYMAP_LAYER_COUNT 4

#define TAPPING_TERM 200
#define IGNORE_MOD_TAP_INTERRUPT

// トラックボールのために追加
#define SOFT_SERIAL_PIN D2

#undef MOUSEKEY_INTERVAL
#undef MOUSEKEY_DELAY
#undef MOUSEKEY_TIME_TO_MAX
#undef MOUSEKEY_MAX_SPEED
#undef MOUSEKEY_MOVE_DELTA
// #define MOUSEKEY_INTERVAL 20
// #define MOUSEKEY_DELAY 0
// #define MOUSEKEY_TIME_TO_MAX 20
// #define MOUSEKEY_MAX_SPEED 16
// #define MOUSEKEY_MOVE_DELTA 2

#define MOUSEKEY_INTERVAL 16                // より滑らかな動作のため
#define MOUSEKEY_DELAY 0                    // 遅延なし
#define MOUSEKEY_TIME_TO_MAX 15            // 加速を調整
#define MOUSEKEY_MAX_SPEED 24              // 最高速度を調整
#define MOUSEKEY_MOVE_DELTA 3              // 初期移動量を調整
// より滑らかな動作のための設定
// #define MOUSEKEY_INTERVAL 20      // 更新間隔を短く (20→16)
// #define MOUSEKEY_DELAY 0          // 初期遅延は変更なし
// #define MOUSEKEY_TIME_TO_MAX 20 // 最高速度までの時間を短く (20→15)
// #define MOUSEKEY_MAX_SPEED 8   // 最高速度を上げる (16→24)
// #define MOUSEKEY_MOVE_DELTA 2     // 初期移動量を若干増加 (2→3)

// センサーの向きは変更なし
#define POINTING_DEVICE_ROTATION_270

// トラックボールの精度向上のための追加設定
#define POINTING_DEVICE_TASK_THROTTLE_MS 1  // ポーリング間隔を短く
