# HID IO Module for ZMK

This module add new HID Usage Page for ZMK.

## What it does

It allow develop to add custom hid usage page to ZMK.

## Installation

Include this project on your ZMK's west manifest in `config/west.yml`:

```yaml
manifest:
  ...
  projects:
    ...
    - name: zmk-hid-io-plover-hid
      remote: petercpark
      revision: main
    ...
```

Now enable the config in your `<shield>.config` file (read the Kconfig file to find out all possible options):

```conf

# Zephyr Config
CONFIG_USB_DEVICE_HID=y

# Add one more USB_HID_DEVICE. 
# Hence, zmk default uses 1 HID, HID_0 for keyboard, 
# we use HID_1 for joystick, mouse. or output.
CONFIG_USB_HID_DEVICE_COUNT=2

# Module Config
CONFIG_ZMK_HID_IO=y

# Enable either one of hid joystick / mouse / hid haptic feedback
# CONFIG_ZMK_HID_IO_PLOVER_HID=y

# Enable logging
CONFIG_ZMK_HID_IO_LOG_LEVEL_DBG=y
```

While module is enabling, a new HID interface shall available from usage page `0xFF0C`. The actual value of usage page and report id could be modified in `include/zmk/hid-io/hid.h`.


## Local building

Replace `/workspaces/zmk-modules/zmk-keyboard-polyglot-w1` with the path to the polyglot w1 keyboard module, and replace `/workspaces/zmk-modules/zmk-hid-io-plover-hid` with the path to this module. Separate them with a semicolon as shown.

Also replace `/workspaces/zmk-config/config` with the folder where your config is.

```

west build -b nice_nano -- -DSHIELD=polyglot -DZMK_EXTRA_MODULES="/workspaces/zmk-modules/zmk-keyboard-polyglot-w1;/workspaces/zmk-modules/zmk-hid-io-plover-hid" -DZMK_CONFIG="/workspaces/zmk-config/config"

```

## How it actually works

This module is only convert input events form input subsystem into hid input/output reports.
See below config to explain how it cooperates with other input driver modules to setup a joystick/gamepad hid device.

ZMK modules that used and should add to your `config/west.yml` for below `shield.keymap` sample.
- [zmk-analog-input-driver](https://github.com/badjeff/zmk-analog-input-driver)

```keymap

// index of keymap layers
#define DEF 0 // default layer

#define HID_IO_USAGE_FWD_TO_MOUSE 1
#define HID_IO_USAGE_FWD_TO_JOYSTICK 2
#define ZIP_HID_IO_USAGE_FWD_TO_VOLUME_KNOB 3

/ {
        /* Setup input-processor to intecept input and forward to new usage page  */
        zip_fwd_to_hid_io: zip_forward_fwd_to_hid_io {
                compatible = "zmk,input-processor-fwd-to-hid-io";
                #input-processor-cells = <0>;
                usage = <HID_IO_USAGE_FWD_TO_JOYSTICK>;
        };

        /* input listener config for mouse move mode */
	analog_input_il {
		compatible = "zmk,input-listener";
		device = <&anin0>;
                input-processors = <&zip_fwd_to_hid_io>;
	};

        /* Setup joystick key press behavior and listener */
        /* listerer shall forward to JOYSTICK usage page if CONFIG_ZMK_HID_IO_JOYSTICK enabling */
        hidiokp: hid_io_key_press {
            compatible = "zmk,behavior-hid-io-key-press";
            #binding-cells = <1>;
        };
	hidiokp_ibl {
		compatible = "zmk,input-behavior-listener";
		device = <&hidiokp>;
                input-processors = <&zip_fwd_to_hid_io>;
	};

        keymap {
                compatible = "zmk,keymap";
                DEF_layer {
                        bindings = < .... 
                        
                        &hidiokp 0 /* joystick 1st button */
                        &hidiokp 0 /* joystick 2nd button */

                        ... >;
                };
       };

};
```
