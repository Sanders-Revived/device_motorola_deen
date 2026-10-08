/*
 * SPDX-FileCopyrightText: 2024 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

package android.telephony;

/**
 * Compatibility API used by the proprietary Qualcomm IMS package.
 * Deen is not a MIUI device, so MIUI-only code paths stay disabled.
 */
public class TelephonyBaseUtilsStub {
    public static boolean isMiuiRom() {
        return false;
    }
}
