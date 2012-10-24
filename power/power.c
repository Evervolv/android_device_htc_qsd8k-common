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

#define BOOSTPULSE_ONDEMAND "/sys/devices/system/cpu/cpufreq/ondemand/boostpulse"
#define BOOSTPULSE_INTERACTIVE "/sys/devices/system/cpu/cpufreq/interactive/boostpulse"
#define FREQ_BUF_SIZE 10

static char scaling_max_freq[FREQ_BUF_SIZE]   = "998400";
static char screenoff_max_freq[FREQ_BUF_SIZE] = "614400";

struct qsd8k_power_module {
    struct power_module base;
    pthread_mutex_t lock;
    int boostpulse_fd;
    int boostpulse_warned;
};

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
    } else {
        s[len - 1] = '\0'; /* Kill the newline */
    }

    close(fd);
    return len;
}

static int get_scaling_governor(char *governor, size_t size)
{

    if (sysfs_read("/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor",
             governor, size) < 0)
        return -1;

    return 0;
}

static int boostpulse_open(struct qsd8k_power_module *qsd8k)
{
    char buf[80];
    char governor[80];

    pthread_mutex_lock(&qsd8k->lock);

    if (qsd8k->boostpulse_fd < 0) {
        if (get_scaling_governor(governor, sizeof(governor)) < 0) {
            ALOGE("Can't read scaling governor.");
            qsd8k->boostpulse_warned = 1;
        } else {
            if (strncmp(governor, "ondemand", 8) == 0)
                qsd8k->boostpulse_fd = open(BOOSTPULSE_ONDEMAND, O_WRONLY);
            else if (strncmp(governor, "interactive", 11) == 0)
                qsd8k->boostpulse_fd = open(BOOSTPULSE_INTERACTIVE, O_WRONLY);

            if (qsd8k->boostpulse_fd < 0 && !qsd8k->boostpulse_warned) {
                strerror_r(errno, buf, sizeof(buf));
                ALOGE("Error opening %s boostpulse interface: %s\n", governor, buf);
                qsd8k->boostpulse_warned = 1;
            } else if (qsd8k->boostpulse_fd > 0)
                ALOGD("Opened %s boostpulse interface", governor);
        }
    }

    pthread_mutex_unlock(&qsd8k->lock);
    return qsd8k->boostpulse_fd;
}

static void qsd8k_power_init(struct power_module *module)
{
}

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
        if (len > 0 && strncmp(buf, screenoff_max_freq,
                                strlen(screenoff_max_freq)) != 0) {
            strcpy(scaling_max_freq, buf);
        }
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

static void qsd8k_power_hint(struct power_module *module, power_hint_t hint,
                            void *data)
{
    struct qsd8k_power_module *qsd8k = (struct qsd8k_power_module *) module;
    char buf[80];
    int len;
    int duration = 1;

    switch (hint) {
    case POWER_HINT_INTERACTION:
    case POWER_HINT_CPU_BOOST:
        if (boostpulse_open(qsd8k) >= 0) {
            if (data != NULL)
                duration = (int) data;
            snprintf(buf, sizeof(buf), "%d", duration);
            len = write(qsd8k->boostpulse_fd, buf, strlen(buf));
            if (len < 0) {
                strerror_r(errno, buf, sizeof(buf));
                ALOGE("Error writing to boostpulse: %s\n", buf);
                pthread_mutex_lock(&qsd8k->lock);
                close(qsd8k->boostpulse_fd);
                qsd8k->boostpulse_fd = -1;
                qsd8k->boostpulse_warned = 0;
                pthread_mutex_unlock(&qsd8k->lock);
            }
        }
        break;

    case POWER_HINT_VSYNC:
        break;

    default:
        break;
    }
}

static struct hw_module_methods_t power_module_methods = {
    .open = NULL,
};

struct qsd8k_power_module HAL_MODULE_INFO_SYM = {
    base: {
        common: {
            tag: HARDWARE_MODULE_TAG,
            module_api_version: POWER_MODULE_API_VERSION_0_2,
            hal_api_version: HARDWARE_HAL_API_VERSION,
            id: POWER_HARDWARE_MODULE_ID,
            name: "QSD8x50 Power HAL",
            author: "The Evervolv Project",
            methods: &power_module_methods,
        },

        init: qsd8k_power_init,
        setInteractive: qsd8k_power_set_interactive,
        powerHint: qsd8k_power_hint,
    },

    lock: PTHREAD_MUTEX_INITIALIZER,
    boostpulse_fd: -1,
    boostpulse_warned: 0,
};
