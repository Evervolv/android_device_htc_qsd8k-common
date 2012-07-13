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
TARGET_ARCH_VARIANT := armv7-a-neon
TARGET_CPU_ABI := armeabi-v7a
TARGET_CPU_ABI2 := armeabi
ARCH_ARM_HAVE_TLS_REGISTER := true

# Bionic optimizations
TARGET_USE_LINARO_STRING_ROUTINES := true

# Headers
TARGET_SPECIFIC_HEADER_PATH := device/htc/qsd8k-common/include

# Wifi
BOARD_WPA_SUPPLICANT_DRIVER := WEXT
BOARD_WPA_SUPPLICANT_PRIVATE_LIB := lib_driver_cmd_wext
WPA_SUPPLICANT_VERSION  := VER_0_8_X
BOARD_WLAN_DEVICE       := bcm4329
WIFI_DRIVER_MODULE_PATH := "/system/lib/modules/bcm4329.ko"
WIFI_DRIVER_FW_PATH_STA := "/system/vendor/firmware/fw_bcm4329.bin"
WIFI_DRIVER_FW_PATH_AP  := "/system/vendor/firmware/fw_bcm4329_apsta.bin"
WIFI_DRIVER_MODULE_ARG  := "iface_name=wlan firmware_path=/system/vendor/firmware/fw_bcm4329.bin nvram_path=/proc/calibration"
WIFI_DRIVER_MODULE_NAME := "bcm4329"

# Audio
BOARD_USES_GENERIC_AUDIO := false
COMMON_GLOBAL_CFLAGS += -DLEGACY_AUDIO_COMPAT

# Compass/Accelerometer
BOARD_VENDOR_USE_AKMD := akm8973

# Bluetooth
BOARD_HAVE_BLUETOOTH := true
BOARD_HAVE_BLUETOOTH_BCM := true

# Fm radio
BOARD_HAVE_FM_RADIO := true
BOARD_GLOBAL_CFLAGS += -DHAVE_FM_RADIO

# Qcom
BOARD_USES_QCOM_LIBS := true
BOARD_USES_QCOM_HARDWARE := true
BOARD_VENDOR_QCOM_AMSS_VERSION := 3200
COMMON_GLOBAL_CFLAGS += -DQCOM_HARDWARE -DREFRESH_RATE=60

# Hardware rendering
BOARD_EGL_CFG := device/htc/qsd8k-common/egl.cfg
USE_OPENGL_RENDERER := true
# We only have 2 buffers
TARGET_DISABLE_TRIPLE_BUFFERING := true
COMMON_GLOBAL_CFLAGS += -DMISSING_GRALLOC_BUFFERS
# Debuging egl
#COMMON_GLOBAL_CFLAGS += -DEGL_TRACE
# Legacy
TARGET_USES_MDP3 := true
TARGET_USES_PMEM := true

# Hacks for legacy mdp drivers
BOARD_ADRENO_DECIDE_TEXTURE_TARGET  := true
BOARD_ADRENO_AVOID_EXTERNAL_TEXTURE := true

# Webkit
TARGET_FORCE_CPU_UPLOAD := true

# Kernel directory
TARGET_KERNEL_SOURCE := kernel/htc/qsd8k

# Common
TARGET_RELEASETOOLS_EXTENSIONS := device/htc/common
