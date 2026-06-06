/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#define DT_DRV_COMPAT zmk_behavior_plover_hid

#include <zephyr/device.h>
#include <drivers/behavior.h>
#include <zephyr/logging/log.h>

#include <zmk/behavior.h>
#include <zmk/hid.h>

#include <zmk/hid-io/hid_plover_hid.h>
#include <zmk/hid-io/endpoints.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

static int behavior_plover_hid_init(const struct device *dev) { return 0; }

static int on_keymap_binding_pressed(struct zmk_behavior_binding *binding,
                                     struct zmk_behavior_binding_event event) {
    uint32_t key_index = binding->param1;
    LOG_DBG("position %d Plover HID key 0x%02X pressed", event.position, key_index);
    zmk_hid_plover_hid_set((uint8_t)key_index, true);
    zmk_endpoints_send_plover_hid_report_alt();
    return ZMK_BEHAVIOR_OPAQUE;
}

static int on_keymap_binding_released(struct zmk_behavior_binding *binding,
                                      struct zmk_behavior_binding_event event) {
    uint32_t key_index = binding->param1;
    LOG_DBG("position %d Plover HID key 0x%02X released", event.position, key_index);
    zmk_hid_plover_hid_set((uint8_t)key_index, false);
    zmk_endpoints_send_plover_hid_report_alt();
    return ZMK_BEHAVIOR_OPAQUE;
}

static const struct behavior_driver_api behavior_plover_hid_driver_api = {
    .binding_pressed = on_keymap_binding_pressed,
    .binding_released = on_keymap_binding_released,
};

#define PLV_INST(n)                                                        \
    BEHAVIOR_DT_INST_DEFINE(n, behavior_plover_hid_init, NULL,            \
                            NULL, NULL, POST_KERNEL,                       \
                            CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,           \
                            &behavior_plover_hid_driver_api);

DT_INST_FOREACH_STATUS_OKAY(PLV_INST)

#endif /* DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT) */
