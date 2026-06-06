/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <zmk/keys.h>
#include <zmk/hid.h>
#include <zmk/endpoints_types.h>

#if IS_ENABLED(CONFIG_ZMK_HID_IO_PLOVER_HID)

/* 64-bit bitmap: one bit per steno key (keys[0] bit7 = key 0, keys[0] bit0 = key 7, etc.) */
struct zmk_hid_plover_hid_report_body_alt {
    uint8_t keys[8];
} __packed;

struct zmk_hid_plover_hid_report_alt {
    uint8_t report_id;
    struct zmk_hid_plover_hid_report_body_alt body;
} __packed;

/**
 * Set (pressed=true) or release (pressed=false) a steno key by index (0–63).
 */
void zmk_hid_plover_hid_set(uint8_t key_index, bool pressed);

/**
 * Clear all steno key states (all bits to 0).
 */
void zmk_hid_plover_hid_clear(void);

/**
 * Get a pointer to the current Plover HID report.
 */
struct zmk_hid_plover_hid_report_alt *zmk_hid_get_plover_hid_report_alt(void);

#endif /* IS_ENABLED(CONFIG_ZMK_HID_IO_PLOVER_HID) */
