/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

/*
 * Plover HID steno key bit indices.
 *
 * These indices correspond to the 64-bit bitmap in the Plover HID report.
 * The ordering follows the standard steno layout:
 *   # S- T- K- P- W- H- R- A O * E U -F -R -P -B -L -G -T -S -D -Z
 *
 * Indices 23–63 are available for additional keys (e.g., second number bar,
 * extra star keys, function keys) or left unused.
 */

#define PLV_SL 0
#define PLV_TL 1
#define PLV_KL 2
#define PLV_PL 3
#define PLV_WL 4
#define PLV_HL 5
#define PLV_RL 6
#define PLV_A 7
#define PLV_O 8
#define PLV_ST 9
#define PLV_E 10
#define PLV_U 11
#define PLV_FR 12
#define PLV_RR 13
#define PLV_PR 14
#define PLV_BR 15
#define PLV_LR 16
#define PLV_GR 17
#define PLV_TR 18
#define PLV_SR 19
#define PLV_DR 20
#define PLV_ZR 21
#define PLV_NM 22

#define PLV_SL2 23
#define PLV_ST2 24
#define PLV_ST3 25
#define PLV_ST4 26
#define PLV_NM2 27
#define PLV_NM3 28
#define PLV_NM4 29
#define PLV_NM5 30
#define PLV_NM6 31
#define PLV_NM7 32
#define PLV_NM8 33
#define PLV_NM9 34
#define PLV_NMA 35
#define PLV_NMB 36
#define PLV_NMC 37

#define PLV_X1  38
#define PLV_X2  39
#define PLV_X3  40
#define PLV_X4  41
#define PLV_X5  42
#define PLV_X6  43
#define PLV_X7  44
#define PLV_X8  45
#define PLV_X9  46
#define PLV_X10 47
#define PLV_X11 48
#define PLV_X12 49
#define PLV_X13 50
#define PLV_X14 51
#define PLV_X15 52
#define PLV_X16 53
#define PLV_X17 54
#define PLV_X18 55
#define PLV_X19 56
#define PLV_X20 57
#define PLV_X21 58
#define PLV_X22 59
#define PLV_X23 60
#define PLV_X24 61
#define PLV_X25 62
#define PLV_X26 63
