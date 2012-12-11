# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# This file sets variables that control the way modules are built
# thorughout the system. It should not be used to conditionally
# disable makefiles (the proper mechanism to control what gets
# included in a build is to use PRODUCT_PACKAGES in a product
# definition file).

TARGET_NO_BOOTLOADER := true

# QSD8250
TARGET_BOARD_PLATFORM := qsd8k
TARGET_BOARD_PLATFORM_GPU := qcom-adreno200

# Arm (v7a) w/ neon
TARGET_ARCH := arm
TARGET_ARCH_VARIANT := armv7-a-neon
TARGET_CPU_ABI := armeabi-v7a
TARGET_CPU_ABI2 := armeabi
ARCH_ARM_HAVE_TLS_REGISTER := true

DEVICE_PACKAGE_OVERLAYS += device/htc/qsd8k-common/overlay

# Bionic optimizations
TARGET_USE_LINARO_STRING_ROUTINES := true

# Headers
TARGET_SPECIFIC_HEADER_PATH := device/htc/qsd8k-common/include

# Wifi
WIFI_BAND                        := 802_11_ABG
WPA_SUPPLICANT_VERSION           := VER_0_8_X
BOARD_WPA_SUPPLICANT_DRIVER      := NL80211
BOARD_WPA_SUPPLICANT_PRIVATE_LIB := lib_driver_cmd_bcmdhd
BOARD_HOSTAPD_DRIVER             := NL80211
BOARD_HOSTAPD_PRIVATE_LIB        := lib_driver_cmd_bcmdhd
BOARD_WLAN_DEVICE                := bcmdhd
WIFI_DRIVER_FW_PATH_STA          := "/vendor/firmware/fw_bcmdhd.bin"
WIFI_DRIVER_FW_PATH_AP           := "/vendor/firmware/fw_bcmdhd_apsta.bin"
WIFI_DRIVER_FW_PATH_P2P          := "/vendor/firmware/fw_bcmdhd_p2p.bin"
WIFI_DRIVER_FW_PATH_PARAM        := "/sys/module/bcmdhd/parameters/firmware_path"

# Audio
BOARD_USES_GENERIC_AUDIO := false

# Compass/Accelerometer
BOARD_VENDOR_USE_AKMD := akm8973

# Bluetooth
BOARD_HAVE_BLUETOOTH := true
BOARD_HAVE_BLUETOOTH_BCM := true

# Fm radio
#BOARD_HAVE_FM_RADIO := true
#BOARD_GLOBAL_CFLAGS += -DHAVE_FM_RADIO

# Qcom
BOARD_USES_LEGACY_QCOM := true
BOARD_VENDOR_QCOM_AMSS_VERSION := 3200

# Hardware rendering
BOARD_EGL_CFG := device/htc/qsd8k-common/egl.cfg
USE_OPENGL_RENDERER := true
# We only have 2 buffers
TARGET_DISABLE_TRIPLE_BUFFERING := true
BOARD_NEEDS_MEMORYHEAPPMEM := true
TARGET_NO_HW_VSYNC := true
COMMON_GLOBAL_CFLAGS += -DTARGET_8x50
BOARD_EGL_NEEDS_LEGACY_FB := true

# Webkit
TARGET_FORCE_CPU_UPLOAD := true
ENABLE_WEBGL := true

# Legacy ril
COMMON_GLOBAL_CFLAGS += -DRIL_VERSION_2_SUPPORT

# Camcorder
BOARD_USE_OLD_AVC_ENCODER := true
BOARD_NO_BFRAMES := true

# Kernel directory
TARGET_KERNEL_SOURCE := kernel/htc/qsd8k
BUILD_KERNEL := true

#BOARD_USES_LEGACY_CAMERA := true

# Override kernel toolchain. (4.6 is too unstable)
ifeq ($(LINARO_BUILD),)
#KERNEL_TOOLCHAIN_PREFIX:=$(ANDROID_BUILD_TOP)/prebuilt/linux-x86/toolchain/arm-eabi-4.4.3/bin/arm-eabi-
endif
