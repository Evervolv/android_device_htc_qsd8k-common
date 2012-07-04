#!/system/bin/sh
#
#
#
#
#
target=`getprop ro.board.platform`
case "$target" in
    "qsd8k")
        # Lower maximum frequency when screen is off
        echo 700000 > /sys/devices/system/cpu/cpu0/cpufreq/screen_off_max_freq
        # Cpu frequencies
        echo 245000 > /sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq
        echo 998400 > /sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq
        # Cpu Governor
        echo "ondemand" > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
        echo 40000 > /sys/devices/system/cpu/cpufreq/ondemand/sampling_rate
        # CpuGovernorService
        chown system /sys/devices/system/cpu/cpufreq/ondemand/sampling_rate
        chown system /sys/devices/system/cpu/cpufreq/ondemand/io_is_busy
        # /system/lib/libqct-opt JNI native will write
        # mfreq to set CPU freq to max for performance
        chown root.system /sys/devices/system/cpu/mfreq
        chmod 220 /sys/devices/system/cpu/mfreq
        # Ksm
        echo 3000 > /sys/kernel/mm/ksm/sleep_millisecs
        echo 256 > /sys/kernel/mm/ksm/pages_to_scan
        echo 1 > /sys/kernel/mm/ksm/run
    ;;
esac
