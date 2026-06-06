/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include "zmk/keys.h"

#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(hid_io, CONFIG_ZMK_HID_IO_LOG_LEVEL);

#include <zmk/hid.h>
#include <zmk/hid-io/hid.h>
#include <zmk/hid-io/hid_plover_hid.h>

#if IS_ENABLED(CONFIG_ZMK_HID_IO_PLOVER_HID)

static struct zmk_hid_plover_hid_report_alt plover_hid_report_alt = {
    .report_id = ZMK_HID_REPORT_ID__IO_PLOVER_HID,
    .body = {.keys = {0}}};

void zmk_hid_plover_hid_set(uint8_t key_index, bool pressed)
{
    if (key_index >= 64)
    {
        LOG_WRN("plover hid: key index %d out of range", key_index);
        return;
    }
    uint8_t byte = key_index / 8;
    uint8_t bit = key_index % 8;
    uint8_t mask = 1 << (7 - bit);

    if (pressed)
    {
        plover_hid_report_alt.body.keys[byte] |= mask;
    }
    else
    {
        plover_hid_report_alt.body.keys[byte] &= ~mask;
    }
    LOG_DBG("plover hid: key %d %s (byte[%d]=0x%02x)", key_index,
            pressed ? "pressed" : "released", byte,
            plover_hid_report_alt.body.keys[byte]);
}

void zmk_hid_plover_hid_clear(void)
{
    LOG_DBG("plover hid report cleared");
    memset(&plover_hid_report_alt.body, 0, sizeof(plover_hid_report_alt.body));
}

struct zmk_hid_plover_hid_report_alt *zmk_hid_get_plover_hid_report_alt(void)
{
    return &plover_hid_report_alt;
}

#endif /* IS_ENABLED(CONFIG_ZMK_HID_IO_PLOVER_HID) */
