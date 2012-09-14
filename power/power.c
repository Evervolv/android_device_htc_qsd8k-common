/*
 * Copyright (C) 2012 The Android Open Source Project
 * Copyright (C) 2012 The Evervolv Project
 *      Andrew Sutherland <dr3wsuth3rland@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define LOG_TAG "PowerHAL"
#include <utils/Log.h>

#include <hardware/hardware.h>
#include <hardware/power.h>

static void sysfs_write(char *path, char *s)
{
    char buf[80];
    int len;
    int fd = open(path, O_WRONLY);

    if (fd < 0) {
        strerror_r(errno, buf, sizeof(buf));
        ALOGE("Error opening %s: %s\n", path, buf);
        return;
    }

    len = write(fd, s, strlen(s));
    if (len < 0) {
        strerror_r(errno, buf, sizeof(buf));
        ALOGE("Error writing to %s: %s\n", path, buf);
    }

    close(fd);
}

static int sysfs_read(char *path, char *s, size_t l)
{
    char buf[80];
    int len = -1;
    int fd = open(path, O_RDONLY);

    if (fd < 0) {
        strerror_r(errno, buf, sizeof(buf));
        ALOGE("Error opening %s: %s\n", path, buf);
        return len;
    }

    do {
        len = read(fd, s, l);
    } while (len < 0 && errno == EINTR); // Retry if interrupted

    if (len < 0) {
        strerror_r(errno, buf, sizeof(buf));
        ALOGE("Error reading from %s: %s\n", path, buf);
    }

    close(fd);
    return len;
}

static void qsd8k_power_init(struct power_module *module)
{
}

#define FREQ_BUF_SIZE 8
static char scaling_max_freq[FREQ_BUF_SIZE]           = "998400";
static const char scaling_max_freq_def[FREQ_BUF_SIZE] = "998400";
static char screenoff_max_freq[FREQ_BUF_SIZE]         = "614400";

static void qsd8k_power_set_interactive(struct power_module *module, int on)
{
    /*
     * Dynamically change cpu settings depending on screen on/off state
     */

    char buf[FREQ_BUF_SIZE];
    int len = -1;

    if (!on) { /* store current max freq so it can be restored */
        len = sysfs_read("/sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq",
                              buf, sizeof(buf));
        if (len > 0 && strcmp(buf, screenoff_max_freq) != 0)
            strcpy(scaling_max_freq, buf);
        else /* set default */
            strcpy(scaling_max_freq, scaling_max_freq_def);
    }

    /* Reduce max frequency */
    sysfs_write("/sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq",
                on ? scaling_max_freq : screenoff_max_freq);

    /* Increase sampling rate */
    sysfs_write("/sys/devices/system/cpu/cpufreq/ondemand/sampling_rate",
                on ? "50000" : "500000");

    /* Increase ksm sleep interval */
    sysfs_write("/sys/kernel/mm/ksm/sleep_millisecs",
                on ? "1000" : "5000");

}

static struct hw_module_methods_t power_module_methods = {
    .open = NULL,
};

struct power_module HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .module_api_version = POWER_MODULE_API_VERSION_0_1,
        .hal_api_version = HARDWARE_HAL_API_VERSION,
        .id = POWER_HARDWARE_MODULE_ID,
        .name = "QSD8x50 Power HAL",
        .author = "The Android Open Source Project",
        .methods = &power_module_methods,
    },
    .init = qsd8k_power_init,
    .setInteractive = qsd8k_power_set_interactive,
};
